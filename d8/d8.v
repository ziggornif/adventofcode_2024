module main

import os

struct Point {
	x int
	y int
}

fn parse_file(path string) []string {
	lines := os.read_lines(path) or {
		eprintln('File not found, continuing with an empty array.')
		[]string{}
	}
	return lines
}

fn antinodes(path string) int {
	mut result := 0
	mut nodes := map[rune][]Point{}
	lines := parse_file(path)
	height := lines.len
	width := lines[0].len

	for i, line in lines {
		for j, ch in line.runes() {
			if ch.str() != '.' {
				nodes[ch] << Point{
					x: i
					y: j
				}
			}
		}
	}

	mut antinodes := map[string]bool{}

	for key, indexes in nodes {
		println('${key} -> ${indexes}')
		for _, a_ind in indexes {
			for _, b_ind in indexes {
				if a_ind.x == b_ind.x && a_ind.y == b_ind.y {
					continue
				}
				distance_x := b_ind.x - a_ind.x
				distance_y := b_ind.y - a_ind.y

				antinode_a := Point{
					x: a_ind.x - distance_x
					y: a_ind.y - distance_y
				}
				antinode_b := Point{
					x: b_ind.x + distance_x
					y: b_ind.y + distance_y
				}
				if antinode_a.x >= 0 && antinode_a.x < width && antinode_a.y >= 0
					&& antinode_a.y < height {
					antinodes['${antinode_a.x}:${antinode_a.y}'] = true
				}
				if antinode_b.x >= 0 && antinode_b.x < width && antinode_b.y >= 0
					&& antinode_b.y < height {
					antinodes['${antinode_b.x}:${antinode_b.y}'] = true
				}
			}
		}
	}
	return antinodes.keys().len
}
