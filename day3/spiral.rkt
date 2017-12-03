#lang racket/base

(define (get-taxicab-distance n)
  (if (= n 1) 0
      (let loop ([i 1] [min 0] [max 0] [cur 0] [next-fn add1])
        ;(eprintf "i: ~a min: ~a max: ~a cur: ~a\n" i min max cur)
        (define square-root (sqrt i))
        (cond
          [(= i n) cur]
          [(and (= square-root (floor square-root))
                (= (remainder (floor square-root) 2) 1))
           ;(eprintf "NEXT LEVEL AT ~a\n" i)
           (loop (add1 i) (add1 min) (+ max 2) (add1 cur) sub1)]
          [(= cur max)
           (loop (add1 i) min max (sub1 cur) sub1)]
          [(= cur min)
           (loop (add1 i) min max (add1 cur) add1)]
          [else
           (loop (add1 i) min max (next-fn cur) next-fn)]))))

(time (get-taxicab-distance 277678))