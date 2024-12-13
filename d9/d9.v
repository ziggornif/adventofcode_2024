module main

import os
import strconv
import arrays

enum Value as i32 {
	disk_file
	disk_space
}

fn parse_file(path string) string {
	lines := os.read_lines(path) or {
		eprintln('File not found, continuing with an empty array.')
		[]string{}
	}
	return lines[0]
}

fn defrag(path string) int {
	mut result := 0
	line := parse_file(path)
	mut disk := []string{}
	println('Advent of code day 9 : Disk Fragmenter')
	mut block_kind := Value.disk_file
	mut f_id := 0
	for ch in line.runes() {
		numval := strconv.atoi(ch.str()) or { 1 }
		for _ in 0 .. numval {
			if block_kind == Value.disk_file {
				disk << f_id.str()
			} else {
				disk << '.'
			}
		}
		if block_kind == Value.disk_file {
			f_id++
			block_kind = Value.disk_space
		} else {
			block_kind = Value.disk_file
		}
	}
	disk_size := disk.len

	println('${disk}')

	mut cursor := disk_size - 1
	mut defragmented := false
	for !defragmented {
		current := disk[cursor].str()
		if current == '.' {
			cursor -= 1
			continue
		}
		free_index := arrays.index_of_first(disk, fn (idx int, ch string) bool {
			return ch == '.'
		})
		last_digit := arrays.index_of_last(disk, fn (idx int, ch string) bool {
			return ch != '.'
		})
		if free_index > last_digit {
			defragmented = true
			continue
		}
		disk[free_index] = current
		disk[cursor] = '.'
		cursor = disk_size - 1
		println('${disk}')
	}

	for i in 0 .. disk_size - 1 {
		if disk[i] == '.' {
			println('end')
			break
		}
		numval := strconv.atoi(disk[i]) or { 0 }
		println('$numval * $i')
		result += numval * i
	}

	return result
}

fn main() {
	defrag('input_test.txt')
}
