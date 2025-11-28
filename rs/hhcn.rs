use std::io::{self, BufRead};

fn main() {
    let mut input = String::new();
    io::stdin().lock().read_line(&mut input).unwrap();

    let mut nums = input.split_whitespace().map(|x| x.parse::<f64>().unwrap());

    let a = nums.next().unwrap();
    let b = nums.next().unwrap();
    let c = nums.next().unwrap();

    let result = 4.0 * (a * b + b * c + c * a) / (a * b * c).sqrt();
    println!("{}", result);
}
