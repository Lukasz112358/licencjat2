# Randomized Subset Sum Algorithm

Bachelor's thesis project developed at the University of Wrocław.

The project focuses on the implementation of a randomized algorithm for the
classical **Subset Sum problem**, developed by [Ce Jin and Hongxun Wu](https://arxiv.org/abs/2403.19117).

Given a multiset of natural numbers $S$ and a target value $t$, the goal is to
determine which sums up to $t$ can be obtained by selecting a subset of the
input elements.

The main implementation is written in C++ and combines generating functions,
formal power series, modular arithmetic and fast polynomial multiplication.

📄 [Bachelor's thesis (PDF)](./opis.pdf)

## Main idea

For a multiset

$$
S = \{s_1, s_2, ..., s_n\}
$$

consider the polynomial

$$
A(x) = (1 + x^{s_1})(1 + x^{s_2})...(1 + x^{s_n}).
$$

The coefficient of $x^k$ in this polynomial corresponds to the number of
subsets of $S$ whose elements sum to $k$. Therefore, a sum $k$ is achievable
if and only if the corresponding coefficient is non-zero.

Instead of multiplying all of these polynomials directly, the algorithm works
with the formal power series

$$
B(x) = \log(A(x)),
$$

and then reconstructs

$$
A(x) = \exp(B(x))
$$

Using the formal identity

$$
A'(x) = B'(x)A(x),
$$

the coefficients of $A(x)$ can be computed recursively. The resulting
recurrence contains polynomial convolutions, which can be accelerated using
fast polynomial multiplication.

## Number-Theoretic Transform

The algorithm requires efficient polynomial multiplication.

An initial implementation based on the classical Fast Fourier Transform (FFT)
suffered from floating-point precision problems. For this reason, the final
implementation uses a **Number-Theoretic Transform (NTT)**.

The NTT performs operations analogous to the FFT, but works in a finite field
$\mathbb{Z}_p$. This allows polynomial multiplication to be performed using exact
modular arithmetic instead of floating-point calculations.

## Prime modulus generation

The NTT requires a prime modulus with a suitable root of unity.

The implementation first chooses the smallest power of two $2^k$
such that $2^k > 2t$. It then repeatedly generates random values $r$
and constructs prime candidates of the form

$$
p = r  2^k + 1
$$

where $r$ is randomly generated.

Each candidate is tested for primality using the **Miller-Rabin primality
test**. Composite candidates are rejected and the process is repeated until
a suitable prime is found.

The randomized choice of the modulus also contributes to the probabilistic
nature of the algorithm. Calculations are performed modulo $p$, so a non-zero
coefficient can become zero if it happens to be divisible by the selected
prime. Choosing the modulus randomly makes such an event unlikely.

## Reference implementation

The repository also contains a standard dynamic-programming implementation of
Subset Sum.

It uses a bitset to maintain information about currently reachable sums. For
each input element, the set of reachable sums is updated using an operation
equivalent to

```text
DP = DP OR (DP << value)
```

The reference implementation is used to verify the results produced by the
randomized algorithm and to compare execution times.

## Main components

### `main.cpp`

Contains the main implementation of the randomized Subset Sum algorithm.

It also contains:

- computation of formal power-series coefficients,
- reconstruction of the generating function,
- the dynamic-programming reference implementation,
- execution-time measurements,
- comparison of the results produced by both algorithms.

### `field.h`

Implements arithmetic in the finite field `Z_p`.

It provides modular arithmetic operations required by the rest of the
algorithm.

### `find_prime.cpp`

Implements the search for a suitable prime modulus.

It includes:

- generation of large integer candidates,
- construction of candidates of the required form,
- Miller-Rabin primality testing.

### `fourier.cpp`

Implements the Number-Theoretic Transform and fast polynomial multiplication.

### `PrimesExperiment.jl`

Julia code used for numerical experiments concerning the availability of prime
numbers satisfying the conditions required by the NTT implementation.

### `losowanie_testu.jl`

Generates random test inputs.

### `opis.pdf`

The Bachelor's thesis describing the mathematical background, algorithm and
implementation.

## Technologies

- C++
- Julia
- LaTeX

## Topics

- algorithms and data structures
- Subset Sum
- probabilistic algorithms
- dynamic programming
- formal power series
- modular arithmetic
- finite fields
- Number-Theoretic Transform
- fast polynomial multiplication
- Miller-Rabin primality testing

## Implementation notes

The C++ implementation uses 128-bit integer arithmetic (`__int128`) for some
intermediate computations.

Because `__int128` is a compiler extension, the project is intended for
compilers such as GCC that support this type.
