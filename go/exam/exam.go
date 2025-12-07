package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
)

type Pair struct {
	val int64
	str string
}

func calc(a int64, op byte, b int64) int64 {
	if op == '+' {
		return a + b
	}
	if op == '-' {
		return a - b
	}
	return a * b
}

func ts(x int64) string {
	return strconv.FormatInt(x, 10)
}

func getAll(nums []int64, ops []byte) []Pair {
	sz := len(nums)
	var all []Pair

	if sz == 2 {
		v := calc(nums[0], ops[0], nums[1])
		all = append(all, Pair{v, ts(nums[0]) + string(ops[0]) + ts(nums[1])})
	} else if sz == 3 {
		a, b, c := nums[0], nums[1], nums[2]
		o1, o2 := ops[0], ops[1]
		v1 := calc(a, o1, calc(b, o2, c))
		v2 := calc(calc(a, o1, b), o2, c)
		s1 := ts(a) + string(o1) + "(" + ts(b) + string(o2) + ts(c) + ")"
		s2 := "(" + ts(a) + string(o1) + ts(b) + ")" + string(o2) + ts(c)
		all = append(all, Pair{v1, s1}, Pair{v2, s2})
	} else {
		a, b, c, d := nums[0], nums[1], nums[2], nums[3]
		o1, o2, o3 := ops[0], ops[1], ops[2]
		all = []Pair{
			{calc(a, o1, calc(b, o2, calc(c, o3, d))), ts(a) + string(o1) + "(" + ts(b) + string(o2) + "(" + ts(c) + string(o3) + ts(d) + "))"},
			{calc(a, o1, calc(calc(b, o2, c), o3, d)), ts(a) + string(o1) + "((" + ts(b) + string(o2) + ts(c) + ")" + string(o3) + ts(d) + ")"},
			{calc(calc(a, o1, b), o2, calc(c, o3, d)), "(" + ts(a) + string(o1) + ts(b) + ")" + string(o2) + "(" + ts(c) + string(o3) + ts(d) + ")"},
			{calc(calc(a, o1, calc(b, o2, c)), o3, d), "(" + ts(a) + string(o1) + "(" + ts(b) + string(o2) + ts(c) + "))" + string(o3) + ts(d)},
			{calc(calc(calc(a, o1, b), o2, c), o3, d), "((" + ts(a) + string(o1) + ts(b) + ")" + string(o2) + ts(c) + ")" + string(o3) + ts(d)},
		}
	}

	sort.SliceStable(all, func(i, j int) bool {
		return all[i].val < all[j].val
	})

	var result []Pair
	seen := make(map[int64]bool)
	for _, p := range all {
		if !seen[p.val] {
			seen[p.val] = true
			result = append(result, p)
		}
	}

	return result
}

func exam(in *os.File, out *os.File) {
	reader := bufio.NewReader(in)
	writer := bufio.NewWriter(out)
	defer writer.Flush()

	var n int
	fmt.Fscan(reader, &n)

	exprs := make([][]Pair, n)

	for i := 0; i < n; i++ {
		var s string
		fmt.Fscan(reader, &s)
		var nums []int64
		var ops []byte
		var num int64 = 0
		for j := 0; j < len(s); j++ {
			c := s[j]
			if c >= '0' && c <= '9' {
				num = num*10 + int64(c-'0')
			} else {
				nums = append(nums, num)
				num = 0
				ops = append(ops, c)
			}
		}
		nums = append(nums, num)
		exprs[i] = getAll(nums, ops)
	}

	order := make([]int, n)
	for i := 0; i < n; i++ {
		order[i] = i
	}

	sort.Slice(order, func(i, j int) bool {
		li, lj := len(exprs[order[i]]), len(exprs[order[j]])
		if li != lj {
			return li < lj
		}
		return order[i] < order[j]
	})

	result := make([]string, n)
	used := make(map[int64]bool)

	var solve func(idx int) bool
	solve = func(idx int) bool {
		if idx == n {
			return true
		}
		i := order[idx]
		for _, p := range exprs[i] {
			if !used[p.val] {
				used[p.val] = true
				result[i] = p.str
				if solve(idx + 1) {
					return true
				}
				delete(used, p.val)
			}
		}
		return false
	}

	if solve(0) {
		for _, s := range result {
			fmt.Fprintln(writer, s)
		}
	} else {
		fmt.Fprintln(writer, "NO SOLUTION")
	}
}

func main() {
	exam(os.Stdin, os.Stdout)
}
