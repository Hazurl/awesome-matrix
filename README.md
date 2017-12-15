# awesome-matrix

Library to manipulate Matrices and Vectors. Can be use with OpenGL.

## Matrices

The matrix type require a type and the size of each dimension
```c++
constexpr unsigned int row_size = 3; 
constexpr unsigned int column_size = 3; 
using type_of_element = float;
using M = Matrix<type_of_element, rwo_size, column_size>;
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
You can also use the sortcut `Matrix<float, 3, 3>::identity()` to create an identity matrix;

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
__Note__ : `[]` and `at` does not throw an exeption if you try to access an element out of the bounds.

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

There is two more function to read and write, they are useful with c-array
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
