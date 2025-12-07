package main

import (
	"os"
	"path/filepath"
	"strings"
	"testing"
)

func runTest(testcase string) func(t *testing.T) {
	return func(t *testing.T) {
		inPath := filepath.Join("in", testcase+".txt")
		outPath := filepath.Join("out", testcase+".txt")
		expectPath := filepath.Join("expected", testcase+".txt")

		inFile, err := os.Open(inPath)
		if err != nil {
			t.Fatal(err)
		}
		outFile, err := os.Create(outPath)
		if err != nil {
			t.Fatal(err)
		}
		exam(inFile, outFile)

		actual, err := os.ReadFile(outPath)
		if err != nil {
			t.Fatalf("cannot read output file: %v", err)
		}

		expected, err := os.ReadFile(expectPath)
		if err != nil {
			t.Fatalf("cannot read expected file: %v", err)
		}

		actualLines := strings.Split(strings.ReplaceAll(string(actual), "\r\n", "\n"), "\n")
		expectedLines := strings.Split(strings.ReplaceAll(string(expected), "\r\n", "\n"), "\n")

		maxLen := max(len(actualLines), len(expectedLines))

		for i := 0; i < maxLen; i++ {
			var a, e string
			if i < len(actualLines) {
				a = actualLines[i]
			}
			if i < len(expectedLines) {
				e = expectedLines[i]
			}

			if a != e {
				t.Fatalf(
					"difference at line %d\nexpected: %q\nactual:   %q\n",
					i+1,
					e,
					a,
				)
			}
		}

	}
}

func TestRunFromFiles(t *testing.T) {
	files, err := os.ReadDir("in")
	if err != nil {
		t.Fatalf("cannot read in dir %v", err)
	}

	if err := os.MkdirAll("out", 0755); err != nil {
		t.Fatalf("cannot create out dir: %v", err)
	}

	for _, f := range files {
		if f.IsDir() || !strings.HasSuffix(f.Name(), ".txt") {
			continue
		}

		testcase := strings.TrimSuffix(f.Name(), ".txt")

		t.Run(testcase, runTest(testcase))
	}
}
