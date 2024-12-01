module main
import os
import math
import arrays

fn parse(line string) (int, int) {
	arr := line.split('   ')
	return arr[0].i32(), arr[1].i32()
}

fn distance(l int, r int) int {
	println("left ${l} right ${r} distance : ${math.abs(r-l)}")
	return math.abs(r - l)
}

fn similarity(left_arr []int, right_arr []int) int{
	mut result := 0
	r_map := arrays.map_of_counts(right_arr)
	for val in left_arr {
		if val in r_map {
			println("val ${val} r_map[val] ${r_map[val]} added ${val * r_map[val]}")
			result += val * r_map[val]
		}
	}
	return result
}

fn main() {
	mut result := 0
	mut left_arr := []int{}
	mut right_arr := []int{}

	lines := os.read_lines('./input.txt')!
	for line in lines {
		l, r := parse(line)
		left_arr.insert(left_arr.len, l)
		right_arr.insert(right_arr.len, r)
	}
	left_arr.sort()
	right_arr.sort()
	for i in 0..left_arr.len {
		result += distance(left_arr[i], right_arr[i])
	}
	println('Result p1: ${result}')

	result = similarity(left_arr, right_arr)
	println('Result p2: ${result}')
}