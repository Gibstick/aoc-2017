(ns registers.core
  (:require
    [clojure.pprint :as pprint]
    [clojure.string :as str]))


(def condition->fn
  {">" >
   "<" <
   "==" ==
   ">=" >=
   "<=" <=
   "!=" not=})

(def instr->fn
  {"inc" +
   "dec" -})


(time
  (loop [line (read-line)
         registers {}
         max-overall 0]
    (if-not line
      (do
        (println (apply max-key val registers))
        (println max-overall))
      (let [[dest instr amt _ src condition rhs]
            (str/split line #" ")

            dest        (keyword dest)
            src         (keyword src)

            dest-val    (dest registers 0)
            src-val     (src registers 0)
            rhs         (Integer/parseInt rhs)
            amt         (Integer/parseInt amt)

            modify?     ((condition->fn condition) src-val rhs)
            instr       (instr->fn instr)
            new-val     (if modify? (instr dest-val amt) dest-val)

            registers   (assoc registers dest new-val)
            max-overall (max new-val max-overall)]
        (recur (read-line) registers max-overall)))))
