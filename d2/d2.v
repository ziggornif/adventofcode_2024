module main
import os
import strconv
import arrays

fn parse_file(path string) []string {
	lines := os.read_lines(path) or {
		eprintln('File not found, continuing with an empty array.')
		[]string{}
	}
	return lines
}

fn is_safe(numbers []int) bool {
	mut increase := numbers[1] - numbers[0] > 0
	mut safe := true
	for i in 0..numbers.len-1 {
		diff := numbers[i + 1] - numbers[i];
		if diff > 0 && diff < 4 {
			if !increase {
				safe = false
				break
			}
			increase = true
		} else if diff < 0 && diff > -4 {
			if increase {
				safe = false
				break
			}
		} else {
			safe = false
			break
		}
	}
	return safe
}

fn p1_safe_reports(path string) int {
	mut result := 0
	lines := parse_file(path)

	for line in lines {
		numbers := line.split(' ').map(fn (num string) int {
			return strconv.atoi(num) or { 0 }
		})
		if is_safe(numbers) {
			result += 1
		}
	}
	return result
}

fn p2_safe_reports(path string) int {
	mut result := 0
	lines := parse_file(path)

	for line in lines {
		numbers := line.split(' ').map(fn (num string) int {
			return strconv.atoi(num) or { 0 }
		})
		if is_safe(numbers) {
			result += 1
		} else {
			for i in 0..numbers.len -1 {
				arr := arrays.concat(numbers[..i].clone(), ...numbers[i + 1..].clone())
				if is_safe(arr) {
					result += 1
				}
			}
		}
	}
	return result
}

fn main() {
	result_p1 := p1_safe_reports('./input.txt')
	println('Result p1: ${result_p1}')
	result_p2 := p2_safe_reports('./input.txt')
	println('Result p1: ${result_p2}')
}