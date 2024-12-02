module main
import os
import math
import arrays

fn parse_line(line string) (int, int) {
	arr := line.split('   ')
	return arr[0].i32(), arr[1].i32()
}

fn parse_file(path string) ([]int, []int) {
	mut left_arr := []int{}
	mut right_arr := []int{}

	lines := os.read_lines('./input.txt') or {
		eprintln('File not found, continuing with an empty array.')
		[]string{}
	}

	for line in lines {
		l, r := parse_line(line)
		left_arr.insert(left_arr.len, l)
		right_arr.insert(right_arr.len, r)
	}

	left_arr.sort()
	right_arr.sort()

	return left_arr, right_arr
}

fn distance(left_arr []int, right_arr []int) int {
	mut result := 0
	for i in 0..left_arr.len {
		// println("left ${left_arr[i]} right ${right_arr[i]} distance : ${math.abs(right_arr[i]-left_arr[i])}")
		result += math.abs(right_arr[i] - left_arr[i])
	}
	return result
}

fn similarity(left_arr []int, right_arr []int) int{
	mut result := 0
	r_map := arrays.map_of_counts(right_arr)
	for val in left_arr {
		if val in r_map {
			// println("val ${val} r_map[val] ${r_map[val]} added ${val * r_map[val]}")
			result += val * r_map[val]
		}
	}
	return result
}

fn main() {
	left_arr, right_arr := parse_file('./input.txt')

	result_p1 := distance(left_arr, right_arr)
	println('Result p1: ${result_p1}')
	result_p2 := similarity(left_arr, right_arr)
	println('Result p2: ${result_p2}')
}