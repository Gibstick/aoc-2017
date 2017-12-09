use std::io;
use std::io::prelude::*;
use std::collections::HashMap;

fn main() {
    let mut line = String::new();
    let stdin = io::stdin();
    stdin.lock().read_line(&mut line).unwrap();

    let mut banks : Vec<u32> = line
        .trim()
        .split_whitespace()
        .map(|x| u32::from_str_radix(x, 10).unwrap())
        .collect();


    let mut seen = HashMap::new();
    let mut counter = 0;
    loop {
        if seen.contains_key(&banks) {
            break;
        }

        seen.insert(banks.clone(), counter);
        counter += 1;

        // max_by breaks ties by taking the last one
        // but we need the first one
        let mut max = banks[0];
        let mut max_idx = 0;
        for (idx, &val) in banks.iter().enumerate() {
            if val > max {
                max = val;
                max_idx = idx;
            }
        }
        let max = max;
        let max_idx = max_idx;

        // redistribute
        banks[max_idx] = 0;
        let all_dist = max / banks.len() as u32;

        for val in banks.iter_mut() {
            *val = *val + all_dist;
        }

        for offset in 0..(max as usize) % banks.len() {
            let i = (max_idx + offset + 1) % banks.len();
            banks[i] += 1;
        }
    }
    println!("{}", counter);
    println!("{}", counter - seen.get(&banks).unwrap());

}
