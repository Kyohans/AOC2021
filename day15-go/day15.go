package main

import (
	"bufio"
	"fmt"
	"os"
)

func getFile(filename string) *bufio.Scanner {
	readFile, err := os.Open(filename)
	if err != nil {
		panic("File not found!")
	}

	scanner := bufio.NewScanner(readFile)
	scanner.Split(bufio.ScanLines)

	return scanner
}

func min(vals ...int) int {
	min_val := vals[0]

	for _, v := range vals {
		if v < min_val {
			min_val = v
		}
	}

	return min_val
}

func calcRisk(x int, y int, grid [][]int) int {
	if x < 0 || x > len(grid) || y < 0 || y > len(grid[0]) {
		return 0
	}

	return grid[x][y] + min(calcRisk(x+1, y, grid), calcRisk(x, y+1, grid), calcRisk(x-1, y, grid), calcRisk(x, y-1, grid))
}

func partOne(filename string) {
	scanner := getFile(filename)
	grid := make([][]int, 0)

	for scanner.Scan() {
		line := scanner.Text()
		row := make([]int, 0)

		for _, v := range line {
			row = append(row, int(v))
		}

		grid = append(grid, row)
	}

	return go func(
		min(calcRisk(0, 1, grid), calcRisk(1, 0, grid)))
	)()
}

func main() {
	partOne("example")
}
