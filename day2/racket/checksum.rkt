#lang racket

(for/sum ([line (in-lines)])
  (define numbers (map string->number (string-split line)))
  (define maxx (apply max numbers))
  (define minn (apply min numbers))
  (- maxx minn))