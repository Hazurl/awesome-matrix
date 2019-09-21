# awesome-matrix

Library to manipulate Matrices and Vectors. Can be use with OpenGL.
Everythig is in the aws namespace.

## Matrices

The matrix type requires a type and the size of each dimensions:
```c++
constexpr unsigned int row_size = 3; 
constexpr unsigned int column_size = 3; 
using type_of_element = float;
using M = Matrix<type_of_element, row_size, column_size>;
```  

### Constructor

There is 4 differents way to initialize a matrix.

* Uninitialized :
```c++
// each element is undefined
Matrix<float, 3, 3> m;
```
* By copy of a value :
```c++
// each element is 0
Matrix<float, 3, 3> m (0);
```

* By an initializer list :
```c++
Matrix<float, 3, 3> m {
  1, 0, 0,
  0, 1, 0,
  0, 0, 1
};
```
* By copy of an array :
```c++
float array[] = {
  1, 0, 0,
  0, 1, 0,
  0, 0, 1
};
// each element is a copy of the array
Matrix<float, 3, 3> m (array);
```
`Matrix<T, R, C>::identity()` creates an identity matrix, it must be a square matrix.
`Matrix<T, R, C>::diagonal(il)` creates an amtrix whose diagonal is filled with the value of the initializer list passed in parameter.

### Read/Write

You can access to a reference to an element with `at`
```c++
matrix.at(row, column) = 42;
float f = matrix.at(row, column);
```
The [ ] operator returns a Row
```c++
auto matrix_row = matrix[row];
matrix_row[column] = 42;
// or simply
matrix[row][column] = 42;
```
__Note__ : `[]` does not throw an exception but `at` does if you try to access an element out of the bounds.

The Row can be convertible to a `Matrix<T, 1, C>` 
```c++
Matrix<float, 3, 3> m(0); // all 0
Matrix<float, 1, 3> row = m[1]; // get second row
``` 
__Note__ : Row still have a reference to the matrix, while the conversion create a copy.

You can access the raw data like that
```c++
float* raw_data = matrix.data();
``` 

You can access individual elements with the members `m00`, `m10`, `m01`..., and the members `x`, `y`, `z`, `w`are accessible if your matrix is a column or a row vector.
These only apply for R<=4 and C<=4.

There is two more functions to read and write, they are useful with c-array
```c++
Matrix<float, 2, 2> matrix;
float array[] = {
  1, 0, 
  0, 1
};
// to read from an array (copy each element) :
matrix.read_from(array); 
// same as 
// Matrix<float, 2, 2> matrix(array);

// to write to an array (copy each element) :
matrix.write_to(array);
```
### Iterators

The class provides all standard iterators `begin`, `cbegin`, `crbegin`, `rbegin` and there respectives with `end`.
```c++
for(auto it = matrix.begin(); it != matrix.end(); ++it)
  *it *= 2;
// or
for(auto& f : matrix) 
  f *= 2;
```
You can retrieve the indices from an iterator with `getIndices` : 
```c++
Matrix<float, 3, 3> m;
auto it = m.begin() + 3;
std::pair<unsigned int, unsigned int> indices = m.getIndices(it);
auto row = indices.first;
auto col = indices.second;
```

### Size

You can get the size of each dimension with `matrix.row()` and `matrix.columns()`, the total size (row*col) is `matrix.size()`. They are constexpr.

## Operations

### Add column

`Matrix<T, R, C + 1> add_column(unsigned int d, Matrix<T, R, 1> const& col) const`

**Condition:** No condition.

**Parameter:**
- `unsigned int d`: The position in which `col` will be copied.
- `Matrix<T, R, 1> const& col`: The column added to `this`.

**Return type:**
- `Matrix<T, R, C + 1>`: The new matrix with the `d+1`th column equals to `col` and the other a copy of the `this` columns in the same order.

### Add row

`Matrix<T, R + 1, C> add_row(unsigned int d, Matrix<T, 1, C> const& row) const`

**Condition:** No condition.

**Parameter:**
- `unsigned int d`: The position in which `row` will be copied.
- `Matrix<T, 1, C> const& row`: The column added to `this`.

**Return type:**
- `Matrix<T, R + 1, C>`: The new matrix with the `d+1`th row equals to `row` and the other a copy of the `this` rows in the same order.

## Adjugate

`Matrix<T_, C, R> adjugate() const`

**Condition:** Must be a square matrix.

**Return type:**
- `Matrix<T_, C, R>`: The [adjugate matrix](https://en.wikipedia.org/wiki/Adjugate_matrix) of `this`.
- `T_` is the same type as the determinant of a `Matrix<T, R-1, C-1>` which should be `T` if the operators `*` and `+` haven't be overloaded.

### Cofactors

`Matrix<T_, R, C> cofactors() const`

**Condition:** Must be a square matrix.

**Return type:**
- `Matrix<T_, R, C>`: The [cofactors matrix](https://en.wikipedia.org/wiki/Minor_(linear_algebra)) of `this`.
- `T_` is the same type as the determinant of a `Matrix<T, R-1, C-1>` which should be `T` if the operators `*` and `+` haven't be overloaded.

### Cross product

`Matrix<T, R, C> cross_product(Matrix<T, R, C> const& v) const`

**Condition:** ![(R, C) in {(1, 2), (1, 3), (3, 1), (2, 1)}](https://latex.codecogs.com/gif.latex?%28R%2C%20C%29%20%5Cin%20%5C%7B%281%2C%202%29%2C%20%281%2C%203%29%2C%20%283%2C%201%29%2C%20%282%2C%201%29%5C%7D) (It must be a column/row vector of size 2 or 3).

**Parameter:**
- `Matrix<T, R, C> const& v`: The other vector with the same dimension.

**Return type:**
- `Matrix<T, R, C>`: The new vector cross-product of `this` and `v`.

### Delete column

`Matrix<T, R, C - 1> delete_column(unsigned int d) const`

**Condition:** C > 0.

**Parameter:**
- `unsigned int d`: The position of the column that will be deleted.

**Return type:**
- `Matrix<T, R, C - 1>`: The new matrix with the `d+1`th column removed.

### Delete row

`Matrix<T, R - 1, C> delete_row(unsigned int d) const`

**Condition:** R > 0.

**Parameter:**
- `unsigned int d`: The position of the row that will be deleted.

**Return type:**
- `Matrix<T, R - 1, C>`: The new matrix with the `d+1`th row removed.

### Determinant

`T_ determinant() const`

**Condition:** Must be a square matrix.

**Return type:**
- `T_` is the same type as `T` if the operators `*` and `+` haven't be overloaded. Other wise it's deduced.

### Dot product

`T_ dot_product(Matrix<T, R, C> const& v) const`

**Condition:** Must be a column vector or a row column (C==1 or R==1).

**Parameter:**
- `Matrix<T, R, C> const& v`: The other vector with the same dimension.

**Return type:**
- `T_` is the same type as `T` if the operators `*` and `+` haven't be overloaded. Other wise it's deduced.

### Extract column

`Matrix<T, R, 1> extract_column(unsigned int cc) const`

**Condition:** C > 0.

**Parameter:**
- `unsigned int cc`: The position of the column that will be copied.

**Return type:**
- `Matrix<T, R, 1>`: The new column vector which is a copy of the `cc+1`th column.

### Extract row

`Matrix<T, 1, C> extract_row(unsigned int rr) const`

**Condition:** R > 0.

**Parameter:**
- `unsigned int rr`: The position of the row that will be copied.

**Return type:**
- `Matrix<T, 1, C>`: The new row vector which is a copy of the `rr+1`th row.

### Inverse

`Matrix<T_, C, R> inversed() const`

**Condition:** Must be a square matrix.

**Exception:** Throw `std::overflow_error` if the determinant is `0`.

**Return type:**
- `Matrix<T_, C, R>`: The inverse of `this`.
- `T_` is the same type as the determinant of a `Matrix<T, R-1, C-1>` which should be `T` if the operators `*` and `+` haven't be overloaded.

### Is diagonal

`bool is_diagonal() const`

**Condition:** Must be a square matrix.

**Return type:**
- `bool`: `true` if and only if only the first diagonal contains non-zero values.

### Is upper/lower triangle

`bool is_upper_triangular() const`
`bool is_lower_triangular() const`

**Condition:** Must be a square matrix.

**Return type:**
- `bool`: `true` if and only if only the upper/lower triangle contains non-zero values.

### Minors

`Matrix<T, R, C> minors() const`

**Condition:** Must be a square matrix.

**Return type:**
- `Matrix<T, R, C>`: The [minors matrix](https://en.wikipedia.org/wiki/Minor_(linear_algebra)) of `this`.

### Multiply column

`Matrix<D, R, C> multiply_column(unsigned int col, T_ const& t) const`

**Parameter:**
- `unsigned int col`: The position of the column that will be multiplied by `t`.
- `T_ const& t`: The factor.

**Return type:**
- `Matrix<D, R, C>`: A copy of `this` with the `col+1`th column multipled by `t`.
- `D`: The deduced type of `operator*(T, T_)`, it can be forced with the second template argument of `multiply_column`: `decltype(m.multiply_column<double, float>(0, 1.0)) == Matrix<float, R, C>`.

### Multiply row

`Matrix<D, R, C> multiply_row(unsigned int row, T_ const& t) const`

**Parameter:**
- `unsigned int row`: The position of the row that will be multiplied by `t`.
- `T_ const& t`: The factor.

**Return type:**
- `Matrix<D, R, C>`: A copy of `this` with the `row+1`th row multipled by `t`.
- `D`: The deduced type of `operator*(T, T_)`, it can be forced with the second template argument of `multiply_row`: `decltype(m.multiply_row<double, float>(0, 1.0)) == Matrix<float, R, C>`.

## Sub matrix

`template<unsigned int RR, unsigned int CC> Matrix<T, RR, CC> submatrix(unsigned int r0, unsigned int c0) const`

**Parameter:**
- template `unsigned int RR`: The number of rows of the submatrix.
- template `unsigned int C`: The number of columns of the submatrix.
- `unsigned int r0`: the row offset.
- `unsigned int c0`: the column offset.

**Return type:**
- `Matrix<T, RR, CC>`: A copy of the submatrix of size `RR, CC` starting at `r0, c0`.

### Switch columns

`Matrix<T, R, C> switch_columns(unsigned int c0, unsigned int c1) const`

**Condition:** C > 0.

**Parameter:**
- `unsigned int c0`: The index of the first column.
- `unsigned int c1`: The index of the second column.

**Return type:**
- `Matrix<T, R, C>`: A copy of `this` with the `c0+1`th and the `c1+1`th columns switched.

### Switch rows

`Matrix<T, R, C> switch_rows(unsigned int r0, unsigned int r1) const`

**Condition:** R > 0.

**Parameter:**
- `unsigned int r0`: The index of the first row.
- `unsigned int r1`: The index of the second row.

**Return type:**
- `Matrix<T, R, C>`: A copy of `this` with the `r0+1`th and the `r1+1`th rows switched.

### Transpose

`Matrix<T, C, R> transposed() const`

**Return type:**
- `Matrix<T, C, R>`: A matrix where each element at `i,j` is the value of `this->at(j, i)`.

### Without

`Matrix<T, R-1, C-1> without(unsigned int rr, unsigned int cc) const`

**Parameter:**
- `unsigned int rr`: The index of the row to remove.
- `unsigned int cc`: The index of the column to remove.

**Return type:**
- `Matrix<T, R-1, C-1>`: A copy of `this` without the `rr+1`th row and the `cc+1`th column.