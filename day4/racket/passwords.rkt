#lang racket/base

(require racket/string
         racket/set
         racket/list)

(define result
  (for/list ([line (in-lines)])
    (define words (string-split line))
    (define sorted-words
      (map (lambda (s) (sort (string->list s) char<=?)) words))
    (define len (length words))
    (list
     (if (= (set-count (list->set words)) len) 1 0)
     (if (= (set-count (list->set sorted-words)) len) 1 0))))

(displayln (foldl + 0 (map first result)))
(displayln (foldl + 0 (map second result)))