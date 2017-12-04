use std::io;
use std::io::prelude::*;
use std::cmp;

fn main() {
    let stdin = io::stdin();

    let mut minmax_sum = 0;  // part 1
    let mut divides_sum = 0; // part 2

    for line in stdin.lock().lines() {
        // parse stuff
        let line = line.unwrap();
        let splitv : Vec<u32> = line.trim()
            .split_whitespace()
            .map(|x| u32::from_str_radix(x, 10).unwrap())
            .collect();

        let min = splitv.iter().min().unwrap();
        let max = splitv.iter().max().unwrap();
        minmax_sum += max - min;

        // all (x, y) pairs in the vector
        for (i, x) in splitv.iter().enumerate() {
            for y in &splitv[i+1..] {
                let min = cmp::min(x, y);
                let max = cmp::max(x, y);

                if max % min == 0 {
                    divides_sum += max / min;
                    break;
                }
            }
        }
    }

    println!("{}", minmax_sum);
    println!("{}", divides_sum);
}
