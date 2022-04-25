# Algorithm Design - Project 1

All problems were implemented in `C++`, using `STL` and `OOP design`.

## Task #1 - Walsh

This problem represents a classical example of `Divide and Conquer` approach,
a `Z-traversal` of the matrix. I abstract it as seen in the laboratory and came
 with a recursive solution.\
The idea is to start from the bigger picture of the initial matrix, break it in
the `four quadrans` and so on until reaching the `base level recursively`.\
The initial indexes are updated at each step in order to fit in the new quarter.

The **temporal complexity** of this algorithm is `O(n)`, as well as the
**spatial complexity**, as it is implemented recursively and the function
call parameters are saved on stack.\
We have to keep in mind that the `n` comes from the `2^n * 2^n` matrix
dimensions. It could've been implemented in `O(1)` spatial complexity, with an
iterative approach, but it would not make a difference, as `n` won't store
large values.


## Task #2 - Statistics

In this task I used a `Greedy` approach. Firstly, when the input is loaded
in the memory, a `bitset` containing all letters is created,
storing `true` for those letters which appeared in the words list,
and `false` - the other ones.\
The general idea is that each appearing letter is chosen and the program
calculates for that letter the maximum number of words respecting the rule
given in the task.\
The maximum number obtained is the final result.

In order to find how many words can follow the rule for a specific letter,
I used a `Greedy` approach - there is a function calculating the "advantage"
of a letter over the rest of the letter in a word.

```C
calculateLeverage("angabaaa, 'a') =
		5 (occurances of 'a') - 3 (other letters occurances) = 2;
```

When a letter is chosen, the above leverage is calculated for each of the words
in the input and stored in an array, which is then sorted. The array is then
traversed and all the leverages are summed until the sum is 0. The number of
words added to the sum is the maximum number of words that can be used to
follow the rule, for a specific letter.

Talking of `time complexity`, it is `O(L + N * L + N * logN + N)`, and it comes
from the population of the bitset, the calculation of the leverage for each word,
the sort and the calculation of the words number for a letter. The final
time complexity is `O(N * L + N * logN)`, where `N` is the number of words,
and `L` - total length of all words.


## Task #3 - Prinel

The solution starts by verifying if the sum of all operations costs is lower than
the capacity. If so, the maximum possible result is returned - the sum of all
elements in the points array.\
For the other case - a `Dynamic Programming` approach is used. I observed that
this problem perfectly respects the `Knapsack Problem` type, and I even
succeeded in optimizing it.

For `calculating the costs` for each target, I used a bottom-up approach.
I started from 1 and calculated for each number all divisors and always chose
the best cost for the next number - the previous stored one, or the cost for
the current number + 1 (because current number + divisor = next number).

I observed that there are a maximum of `1000 targets`, and for each target,
the minimum cost would not go above `20`. So, the total capacity of the knapsack
would be `20 * 10000 = 20000`, much smaller than the given capacity - `1000000`.

Considering all the techniques described above, the `temporal complexity`
of this program is `O(N * logN + N * 20000)` = `O(N * logN)`.
 

## License
[Adrian V. Croitoru](https://github.com/adriancroitoru97)