#lang racket/base

(require rackunit
         (only-in racket/port with-input-from-string))

;; read one character and do everything
(define (parse-group
         [group-count 0] ;; no need for stack since only groups can nest
         [group-score 0] ;; score of the group that immediately contains it
         [total-score 0])
  (define sym (let ([c (read-bytes 1)]) (if (eof-object? c) #f c)))
  (case sym
    [(#"{") (parse-group (add1 group-count) (add1 group-score) total-score)]
    [(#"}") (parse-group (sub1 group-count) (sub1 group-score) (+ group-score total-score))]
    [(#"<") (discard-garbage) (parse-group group-count group-score total-score)]
    [(#"," #"\n") (parse-group group-count group-score total-score)]
    [(#f) total-score]
    [else
     (eprintf "(~a, ~a, ~a, ~a)" sym group-count group-score total-score)
     (error "This shouldn't get here")]))

;; discard all garbage
(define (discard-garbage)
  (let loop ([sym (read-char)])
    (case sym
      [(#\!) (read-char) (loop (read-char))]
      [(#\>) (void)]
      [else (loop (read-char))])))

(define-simple-check (check-parse? str score)
  (= (with-input-from-string str parse-group) score))

(check-parse? "{}" 1)
(check-parse? "{{{}}}" 6)
(check-parse? "{{},{}}" 5)
(check-parse? "{{{},{},{{}}}}" 16)
(check-parse? "{<a>,<a>,<a>,<a>}" 1)
(check-parse? "{{<ab>},{<ab>},{<ab>},{<ab>}}" 9)
(check-parse? "{{<!!>},{<!!>},{<!!>},{<!!>}}" 9)
(check-parse? "{{<a!>},{<a!>},{<a!>},{<ab>}}" 3)

(parse-group)