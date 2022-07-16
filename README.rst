######
c_libs
######

This repository contains libraries for the c programming language. The library is divided into different 
header files that execute different functionalities. The library contains a ``vector.h`` library, and an
``array.h`` library.

************
Contributing
************
Pull requests are welcome.  For major changes, please open an issue first to discuss
what you would like to change.  Please make sure to include and update tests
as well as relevant doc-string and sphinx updates.

*******
License
*******
The License is included in the **c_libs** package

************
Requirements
************
CLI or greater

************
Installation
************
In order to download this repository from github, follow these instructions

1. Ensure you have .git installed on your computer
2. At your desired location create a directory titled ``c_libs``
3. Open a terminal (Bash, zsh, Linux, or DOS) and cd to the ``c_libs`` directory and type
   ``close https://github.com/jillyep/c_libs.git c_libs``

******
Vector
******
The ``vector.h`` library contains functions that enable the user to create and operate on a 
dynamically allocated vector that is allocated in heap memory.

***********
init_vector
***********
The most basic function in ``vector.h``
library is the ``init_vector(size_t num_bytes, size_t num_indices)`` function, which takes as
arguements ``num_bytes`` which represents the number of bytes consumed by a single indice, and
``num_indices``, which is a user defined number of indices that the vector is expected to require. 
The ``init_vector`` returns a ``Vector`` data type, which represents a ``struct`` containing vector
parameters. The following code snippet shows how a user can instantiate an integer and double vector
that may require 20 indices. An integer data point consumes 4 bytes of memory and double type
consumes 8 bytes of memory. The returned variable should be considered as a fector container, and
not just a vector.

.. code-block:: c

   // Integer vector
   Vector init_vec = init_vector(4, 20);

   //Double vector
   Vector double_vec = init_vector(8, 20);

However, it is better to use the ``init_type_vector(dtype data_type, size_t num_indices)`` function
where the user passes an enum value to represent the ``data_type``. The enum types can be ``INT``,
``FLOAT``, ``DOUBLE``, ``CHAR``, ``STRING``, ``SHORTINT``, ``LONG``, ``LONGLONG``, and ``NONE``. 
The enum types guide the software to automatically determine the number of bytes consumed by a
single vector indice, and does not care about signed vs. unsigned data types. The ``NONE`` 
data type is automatically used for the ``init_type_vector`` function. The user can use it for the
``init_type_vector`` function; however, it will be degraded to an ``INT`` data type. The code example
below demonstrates the instantiation of an integer and double vector with the ``init_type_vector`` function.

.. code-block:: c

   // Integer vector
   Vector init_vec = init_type_vector(4, 20);

   //Double vector
   Vector double_vec = init_type_vector(8, 20);


***********
push_vector
***********
This function pushes an array or scalar to a vector. The vector must first be instantiated via
the ``init_vector`` or ``init_type_vector`` functions. The user passes the the pointer to the instantiated vector,
the pointer to an array or scalar value to be pushed to the vector, and the size of the elements to be pushed 
to the vector. The function supports pushing data types as specified in the enum. The enum types can be ``INT``,
``FLOAT``, ``DOUBLE``, ``CHAR``, ``STRING``, ``SHORTINT``, ``LONG``, ``LONGLONG``, and ``NONE``. 
The enum types guide the software to automatically determine the number of bytes consumed by a
single vector indice, and does not care about signed vs. unsigned data types. The ``NONE`` 
data type is automatically used for the ``init_type_vector`` function. 

.. code-block:: c

    // Instantiating a vector
    Vector vec = init_type_vector(INT, 10);

    //Pushing scalar value to the vector
    int a = 1;
    scalar_length = 1;
    push(&vec, &a, scalar_length);

    // Pushing array of integers to the vector
    int b[] = {4, 5, 6};
    array_length = 3;
    push(&vec, &b, array_length);

***********
free_vector
***********
This function frees the heap memory that was previously assigned to the vector. The user inputs the 
address to the vector. 

.. code-block:: c
   free_vector(&vec);


