package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
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

func part_one(filename string) int {
	scanner := getFile(filename)

	stack := make([]rune, 0)
	dict := map[rune]rune{
		')': '(',
		'}': '{',
		']': '[',
		'>': '<',
	}

	points := map[rune]int{
		')': 3,
		']': 57,
		'}': 1197,
		'>': 25137,
	}

	var ans int
	for scanner.Scan() {
		line := scanner.Text()

		for _, v := range line {
			if len(stack) > 0 {
				_, exists := dict[v]

				if exists && stack[len(stack)-1] == dict[v] {
					stack = stack[0 : len(stack)-1]
				} else if exists && stack[len(stack)-1] != dict[v] {
					ans += points[v]
					break
				} else {
					stack = append(stack, v)
				}
			} else {
				stack = append(stack, v)
			}
		}

		stack = make([]rune, 0)
	}

	return ans
}

func part_two(filename string) int {
	scanner := getFile(filename)

	stack := make([]rune, 0)
	dict := map[rune]rune{
		')': '(',
		'}': '{',
		']': '[',
		'>': '<',
	}
	incomplete := make([][]rune, 0)
	points := map[rune]int{
		'(': 1,
		'[': 2,
		'{': 3,
		'<': 4,
	}

	var ans int
	for scanner.Scan() {
		line := scanner.Text()
		// [({(<(())[]>[[{[]{<()<>>
		// [({([[{{
		//
		// <{([{{}}[<[[[<>{}]]]>[]]
		// <{([
		for _, v := range line {
			if len(stack) > 0 {
				_, exists := dict[v]

				if exists && stack[len(stack)-1] == dict[v] {
					stack = stack[:len(stack)-1]
				} else if exists && stack[len(stack)-1] != dict[v] {
					stack = make([]rune, 0)
					break
				} else {
					stack = append(stack, v)
				}
			} else {
				stack = append(stack, v)
			}
		}

		if len(stack) > 0 {
			incomplete = append(incomplete, stack)
			stack = make([]rune, 0)
		}
	}

	scores := make([]int, 0)
	for _, row := range incomplete {
		for i := len(row) - 1; i >= 0; i-- {
			ans = (ans * 5) + points[row[i]]
		}
		scores = append(scores, ans)
		ans = 0
	}

	sort.Ints(scores)

	return scores[len(scores)/2]
}

func main() {
	//fmt.Println("Part One Example: ", part_one("example"))
	//fmt.Println("Part One Answer:", part_one("input"))
	fmt.Println(part_two("example"))
	fmt.Println(part_two("input"))
}
