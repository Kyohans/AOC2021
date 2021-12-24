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

func createGrid(scanner *bufio.Scanner) [10][10]int {
	var grid [10][10]int
	var r, c int
	for scanner.Scan() {
		line := scanner.Text()

		for _, v := range line {
			grid[r][c] = int(v - '0')
			c += 1
		}
		r += 1
		c = 0
	}

	return grid
}

func validCoord(x int, y int) bool {
	return x >= 0 && x < 10 && y >= 0 && y < 10
}

func increaseEnergy(grid *[10][10]int, x int, y int, flash *int) {
	if x < 0 || x >= 10 || y < 0 || y >= 10 {
		return
	}

	if grid[x][y] > 9 {
		grid[x][y] = 0
		*flash += 1

		increaseEnergy(grid, x-1, y, flash)
		increaseEnergy(grid, x-1, y+1, flash)
		increaseEnergy(grid, x-1, y-1, flash)
		increaseEnergy(grid, x+1, y, flash)
		increaseEnergy(grid, x+1, y+1, flash)
		increaseEnergy(grid, x+1, y-1, flash)
		increaseEnergy(grid, x, y-1, flash)
		increaseEnergy(grid, x, y+1, flash)
	} else {
		grid[x][y] += 1

		if grid[x][y] > 9 {
			increaseEnergy(grid, x, y, flash)
		}
	}
}

func incrementEnergy(grid *[10][10]int, flashed *[10][10]bool, flash *int) {
	for x, row := range grid {
		for y, _ := range row {
			grid[x][y]++
		}
	}

	for x, row := range grid {
		for y, _ := range row {
			if grid[x][y] > 9 {
				flashed[x][y] = true
				(*flash)++
				for drow := -1; drow <= 1; drow++ {
					for dcol := -1; dcol <= 1; dcol++ {
						if drow != 0 || dcol != 0 {
							nrow := x + drow
							ncol := y + dcol

							if validCoord(nrow, ncol) && !flashed[nrow][ncol] {
								grid[nrow][ncol]++
							}
						}
					}
				}
			}
		}
	}
}

func part_one(filename string) {
	grid := createGrid(getFile(filename))

	var steps, flash int
	for steps < 100 {
		var flashed [10][10]bool
		incrementEnergy(&grid, &flashed, &flash)
		steps += 1
	}
	fmt.Println(flash)

}

func main() {
	part_one("example")
	part_one("input")
}
