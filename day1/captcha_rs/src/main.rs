use std::collections::VecDeque;
use std::io;

fn rotate(vecdeque: &mut VecDeque<u32>, rotations: usize) -> () {
    for _ in 0..rotations {
        let front = vecdeque.pop_front().unwrap();
        vecdeque.push_back(front);
    }
}

fn rotate_and_captcha(digits: &VecDeque<u32>, rotations: usize) -> u32
{
    let mut shifted = digits.clone();
    rotate(&mut shifted, rotations);

    return digits.iter().zip(shifted.iter())
        .fold(0, |sum, (&x, &y)|
            if x == y { x + sum } else { sum }
        );
}

fn main() {
    // TOOD: initialize without using mut at first?
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let input = input.trim();

    let digits: VecDeque<u32> = input
        .chars()
        .map(|c| c.to_digit(10).unwrap())
        .collect();

    println!("Sum1: {}", rotate_and_captcha(&digits, 1));
    println!("Sum2: {}", rotate_and_captcha(&digits, digits.len() / 2));
}
