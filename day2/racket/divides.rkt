#lang racket

(for/sum ([line (in-lines)])
  (define numbers (map string->number (string-split line)))
  (define pairs (for*/list ([x numbers] [y numbers]) (list x y)))
  (define wat
    (filter (lambda (x) (and (not (= (first x) (second x)))
                             (zero? (modulo (first x) (second x)))))
            pairs))
  (displayln pairs)
  (displayln wat)
  (define res (/ (apply max (first wat)) (apply min (first wat))))
  res)