---------------------------------------------
<font size=16><b>Lab1. Simplex Method</b></font>

How to use:

In your shell run

```Shell
>>make main(or just make)
>>main input output
```
E.g

```Shell
>>make
>>main simplex.in simplex.out
>>less simplex.out
```

In simplex.out there will be a resulting simplex table, where the lowest-left element is minimal or maximal value of target function

<b>Input and output format</b>

On the first line input file contains four numbers: number of rows, columns, basis variables and slack variables. On second rows' lines it contains columns digits - initial simplex table. First column is column of constants, last column is sum of rows' elements. Last row is target row, containing coefficients before variables in target function. 

Input file example

```
4 7 3 3
1 1 1 1 0 0 4
-1 -4 -3 0 1 0 -7
1 -2 2 0 0 1 2
-1 5 3 0 0 0 7
```

Input file example comment. We want to minimize function f(x) = 6x1 + 4x2 + x3 having constraints such as:
```
x1 + x2 + x3 = 1
200x1 + 175x2 + 100x3 >= 125
5x1 + x2 + 3x3 >= 2
```

Because we want to minimize target function(classic linear programming problem works with maximization), we need to do some precalc. We add three basis variables - x4, x5, x6 and rewrite constraints system in way like:
```
x1 + x2 + x3 = 1
-8x1 - 7x2 -4x3 <= -5
-5x1 - x2 - 3x3 <= 2
```
Transform inequalities into equalities
```
x1 + x2 + x3 = 1
-8x1 - 7x2 -4x3 + x4 = -5
-5x1 - x2 - 3x3 + x5 = 2
```
We have x3 in three equations, but we want to have it in one equation with coefficient 1 before. Make x3 a new basis variable
```
x3 = 1 - x2 - x1
```
Finally, our system will be like:
```
x1 + x2 + x3 = 1
-4x1 - 3x2  + x4 = -1
-2x1 + 2x2 + x5 = 1
```
And target function(we want to miximize it, remember):
```
Z(x) = -1 - 5x1 - 3x2
```

