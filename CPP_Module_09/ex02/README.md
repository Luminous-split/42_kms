# ex02 – PmergeMe

Sorts a sequence of positive integers with the **Ford-Johnson algorithm**
(also called *merge-insertion sort*), once with `std::vector` and once with
`std::deque`, and prints how long each container took.

---

## 1. Build and run

```sh
make
./PmergeMe 3 5 9 7 4
```

```
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector : 17 us
Time to process a range of 5 elements with std::deque  : 22 us
```

Bigger tests:

```sh
./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`      # Linux
./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`         # macOS
```

---

## 2. Files

| File | Content |
|------|---------|
| `PmergeMe.hpp` | Class `PmergeMe` (Orthodox Canonical Form): holds the `std::vector<int>`, the `std::deque<int>` and the two timings |
| `PmergeMe.cpp` | Input parsing, the Ford-Johnson sort (written once as a template), printing and timing |
| `main.cpp` | Creates a `PmergeMe`, calls `run()`, prints `Error` on any exception |

---

## 3. Why these two containers?

- The subject asks for **two different containers**, and forbids reusing the
  containers from ex00 (`std::map`) and ex01 (`std::stack`).
- Ford-Johnson needs **random access** (`[]` and binary search) and
  **insertion in the middle**. Both `std::vector` and `std::deque` have
  random-access iterators, so `std::lower_bound` does a real binary search on
  both. A `std::list` would make every binary search step walk the list.
- The sort is written **once** as a template
  (`fordJohnsonSort<V, I>`), and instantiated for
  `std::vector<int>` / `std::vector<size_t>` and
  `std::deque<int>` / `std::deque<size_t>`. Same algorithm, only the container
  changes, so the timings compare the containers fairly.

---

## 4. The algorithm, step by step

Ford-Johnson is designed to sort with **as few comparisons as possible**.
It has 4 steps (see `mergeInsert` in `PmergeMe.cpp`):

### Step 1 – Make pairs
Group the elements two by two and compare each pair once.
The bigger one goes into the **main chain**, the smaller one is remembered as
its partner. If the count is odd, the last element is the **straggler**
(left alone, inserted later).

### Step 2 – Sort the big ones recursively
Call `mergeInsert` again on the main chain (the bigger elements only).
This is the "merge" part: it recurses until there is 1 element.

### Step 3 – Build the pend chain
After the recursion the big elements are sorted: `a1 < a2 < ... < am`.
The pend chain is their partners in that same order: `b1, b2, ..., bm`
(plus the straggler at the end). We know `bi <= ai` for every pair.

`b1` is smaller than `a1`, and `a1` is the smallest big element, so `b1` is
put at the front **without any comparison**.

### Step 4 – Insert the rest in Jacobsthal order
The remaining `b`'s are inserted with a **binary search**, in this order:

```
Jacobsthal numbers: 1, 3, 5, 11, 21, 43, ...   (J(n) = J(n-1) + 2*J(n-2))

insert order:  b3 b2 | b5 b4 | b11 b10 ... b6 | b21 ... b12 | ...
```

Each group starts at the next Jacobsthal number and goes **down** to the
previous one.

**Why this order?** Each `bj` only needs to be searched in the part of the
main chain that is **before its partner `aj`** (we already know `bj <= aj`).
With this order, every search in a group happens in a range of at most
`2^k - 1` elements, which is the largest size a binary search can handle with
only `k` comparisons. So no comparison is wasted.

The straggler has no partner, so it is searched in the whole chain.

### Worked example: `3 5 9 7 4`

```
Pairs:            (3,5) (9,7)  straggler 4
Big elements:     5 9          -> recursion -> sorted: 5 9
Pend chain:       b1=3 (partner of 5), b2=7 (partner of 9), b3=4 (straggler)

Insert b1 free:   3 5 9
Insert b3 (=4):   search in all of [3 5 9]          -> 3 4 5 9
Insert b2 (=7):   search only before a2=9: [3 4 5]   -> 3 4 5 7 9
```

### Duplicates and indices
The sort does not move the numbers themselves. It sorts **indices** into the
value container (`I` is a container of `size_t`), and the comparator
`IndexLess` compares `vals[a] < vals[b]`. Every index is unique, so even with
duplicate values the algorithm always finds the right partner `aj` in the
main chain. At the end the values are copied in the sorted index order.
Duplicates are accepted (the subject leaves this to us).

---

## 5. Number of comparisons

Ford-Johnson's worst case for `n` elements is
`F(n) = sum for k = 1..n of ceil(log2(3k / 4))`.

Measured with a comparison counter on random inputs (worst of 10 runs):

| n | measured | theoretical max F(n) | plain merge sort worst case |
|---|---------:|---------------------:|----------------------------:|
| 5 | 7 | 7 | 8 |
| 21 | 66 | 66 | 74 |
| 100 | 530 | 534 | 573 |
| 3000 | 30404 | 30546 | 31905 |

So the implementation never goes over the Ford-Johnson limit.

---

## 6. Error handling

`Error` is printed on stderr (exit code 1) when:

- there is no argument,
- an argument is not only digits (`-1`, `abc`, `1.5`, `+3`, empty string),
- a number is bigger than `INT_MAX`.

```sh
./PmergeMe              # Error
./PmergeMe -1 2         # Error
./PmergeMe 1 abc        # Error
./PmergeMe 99999999999  # Error
```

---

## 7. Timing

- Measured with `std::clock()` and shown in microseconds (`us`).
- As the subject asks, the time includes the **data management** (parsing the
  arguments into the container) **and** the sort.
- `std::vector` is usually faster: its memory is one contiguous block, so it
  is cache friendly. `std::deque` is stored in several chunks, so
  each `[]` access and each insertion in the middle costs more.
  Example with 3000 numbers: vector ~17 ms, deque ~37 ms.

---

## 8. Quick checks for the evaluation

```sh
# Is the output really sorted?
ARGS=`shuf -i 1-100000 -n 3000 | tr "\n" " "`
./PmergeMe $ARGS | grep After | cut -d: -f2 | tr ' ' '\n' | sed '/^$/d' > got
echo $ARGS | tr ' ' '\n' | sort -n > expected
diff got expected && echo OK

# Duplicates
./PmergeMe 5 5 3 3 1 1 2
```
