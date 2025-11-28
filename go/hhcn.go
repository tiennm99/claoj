package main

import (
	"fmt"
	"math"
)

func main() {
	var A, B, C int64
	fmt.Scan(&A, &B, &C)

	a := math.Sqrt(float64(A*C) / float64(B))
	b := math.Sqrt(float64(A*B) / float64(C))
	c := math.Sqrt(float64(B*C) / float64(A))

	perimeter := 4 * (int64(a) + int64(b) + int64(c))
	fmt.Println(perimeter)
}
