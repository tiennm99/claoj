package main

import (
	"fmt"
	"math"
)

func main() {
	var a, b, c int64
	fmt.Scan(&a, &b, &c)
	perimeter := 4 * float64(a*b+b*c+c*a) / math.Sqrt(float64(a*b*c))
	fmt.Println(perimeter)
}
