#lang racket/base

(require rackunit
         (only-in racket/port with-input-from-string))

;; read one character and do everything
(define (parse-group
         [group-score 0] ;; score of the group that immediately contains it
         [total-score 0]
         [garbage-count 0])
  (define sym (let ([c (read-bytes 1)]) (if (eof-object? c) #f c)))
  (case sym
    [(#"{") (parse-group
             (add1 group-score)
             total-score
             garbage-count)]
    [(#"}") (parse-group
             (sub1 group-score)
             (+ group-score total-score)
             garbage-count)]
    [(#"<") (parse-group
             group-score
             total-score
             (+ garbage-count (discard-garbage)))]
    [(#"," #"\n") (parse-group
                   group-score
                   total-score
                   garbage-count)]
    [(#f) (list total-score garbage-count)]
    [else
     (eprintf "(~a, ~a, ~a)" sym group-score total-score)
     (error "This shouldn't get here")]))

;; discard all garbage and return the count of non-cancelled garbage
(define (discard-garbage)
  (let loop ([sym (read-char)] [count 0])
    (case sym
      [(#\!) (read-char) (loop (read-char) count)]
      [(#\>) count]
      [else (loop (read-char) (add1 count))])))

(define-simple-check (check-parse? str score)
  (= (car (with-input-from-string str parse-group)) score))

(check-parse? "{}" 1)
(check-parse? "{{{}}}" 6)
(check-parse? "{{},{}}" 5)
(check-parse? "{{{},{},{{}}}}" 16)
(check-parse? "{<a>,<a>,<a>,<a>}" 1)
(check-parse? "{{<ab>},{<ab>},{<ab>},{<ab>}}" 9)
(check-parse? "{{<!!>},{<!!>},{<!!>},{<!!>}}" 9)
(check-parse? "{{<a!>},{<a!>},{<a!>},{<ab>}}" 3)

(parse-group)