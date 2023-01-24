// -------------------------------------
//
//           (C) Copyright Gennaro Prota 2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// ------------------------------------------------------

#ifndef BOOST_NON_TYPE_HPP_GP_20030417
#define BOOST_NON_TYPE_HPP_GP_20030417


namespace boost {

  // Just a simple "envelope" for non-type template parameters. Useful
  // to work around some MSVC deficiencies.

 template <typename T, T n>
 struct non_type { };


}


#endif // include guard

/* non_type.hpp
L6nPsZVdiypbopz4r1766eXz9JtMvTaewObHsqfcY9Sn3P96xMCecl+pqzZySU76ivt5+ob7O0cMTCOUj+wCkuEhCAKxG/ESP/a/fzw8FiYTkimRErulRKqPRkKc1vXvfKxxkv7kwiOlIZazpSh3lZAElP8+puwLlMypRmDe22HYUo1y0cdXG7f3Sym9whKRJX9C9QW838I40xudFbBgZKqv47kmRZtjZkWD5pUnjpJkdSWGFQifxEMB3GVt97+H197nPbxsvFkQgTcLtnylI/QJ0knRFv/NAjO4XxdOZzcGsrJcVh8wjMi1IDyn46t7paTKQyo9vy2pfPV1MvzmjCd6MrPopOAvhHGuguO4/2oCFTQEBMMsI1364tz4WDQH8ZXxsComJuFT0e2adOVKl7PzUBn4+ku6vfQFrtB4nWyzF8uS2QbMEgxUqVs704C5CG67pbKiHSbcckyqK5q+vQ7DUhXbJjJHgGqFKZ7WY1T6jOgtfebmuTa04Ztu9Zlxh0pC6HbYKQgrwz97G59NrlKMOtQ3v91swEtnzjGfGkDhW6KfYOe4mlDeNxNWB4hyTXPzWzAfIHL9p4hwN96jQAlz5pfBwgLdU2rbEbSn9ORPl+0pVR016NiO1eXbSn5Ld+Ung2rp/i4jkToppSshuYsTZiZqd3OHbqC7DZe4jcmXcLdhZjOQ/Wt11EYdrywreBf51CfI+3rdRT4A
*/