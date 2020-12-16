//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_RELATIONAL_HPP
#define BOOST_COMPUTE_FUNCTIONAL_RELATIONAL_HPP

#include <boost/compute/functional/detail/macros.hpp>

namespace boost {
namespace compute {

BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isequal, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isnotequal, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isgreater, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isgreaterequal, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isless, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(islessequal, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(islessgreater, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isfinite, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isinf, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isnan, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isnormal, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isordered, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isunordered, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(signbit, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(any, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(all, int (T), class T)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_RELATIONAL_HPP

/* relational.hpp
9QhbA9bUmIor1lKYfkux/qyLA5uZnBqTF0sIXoPuSfBcycnOhk9bzKlq4I4Y17DfPIznY4JgHA3nDTY2aGfBva/eHQk67f/yw7EX2x6bqd/wMgVl2TqM1wlPlLEMbP+PsusObuSnwkvvEHqHo3cIgaNDdu1d22uvd5c4oYPjJA4xJLaJneOOGsoAQ5ujDL1k6G2Y/EGvR5thqKHXgcDAUIZytKGXp/ap7DoAx+V+2fdJepKenp70nqRZeHWGaSpi4NEP6Qy8PN2CmI+Z+e4NuWHdN86vleWJ9+snwF1Ang5O9Adw43wWjvphYpytXpqFQ/sDO79SjjVW2sB6LyvH8uo4b+3PzcAKS1eAce72RKxgesPo2/kT8bKDCb+gxsXJeK1TzDtvZ6bB2FzHOJmFxTARZ+rRjzPw4hyJN0Uc+ok4mkPH0y3zroDzpXgrrnsL9x3Nxo7ZnT5TNKNuk6MZaeiv6n7wcjwbCzWAMwWzsNuj0WP3xnK06P0h7+Un4uVo0Pi5Wfjh3o4ethp/8KAiXm3hm+MCuqM8f9x4j7F2Mo5dTvAYrPlcrD4ouIs116uKGHUvCur+6hLMeG93PJr0KT86GkFZmmf3XlPEqyu7qVW3MIfMxG30hn2NWy3FFfX7wUyc7B7Sw/QmvN6bLsXbenhByeIsrLpIUF6GZc5L868tTaPGsrYLy3Hu2B9Cr5TjERngGXPSwWwsjXzjTcBSXFGfHJXjXH0CXo9L8bY+wb7a62ysc9i0hzEwA6dk0sxztQyLY8PGe5SlOOx0AXehFFccp0elOGucIsZ3/GAbiweOjXF66qFFjNSXwBw/rIiR+ky/w/IIGyPtvxHa4ZEW3Yr3nBi+h4MiDuMRe8cOxpnnu2hTB+fM8V20qYsrzu9bkDsXW5zbtzB3uNjyeR3rc+9RNt6d0yHPRRzk3sTNOzhnPgTOd3DuXAj94OLcedC8m8fFFufAEeS0iIXcwxYvxUDmJ1jPBzZOXMm4LRt7ot//dPMjyGONeKwLDl3OXeD5qGvRRfyvI6cXCxjbHkW/r7o4S0613VrEuXKK9j9VxLpyOoLNWsCeLKd+AW/LKcZKxcXpuYSaaro1MXzITp5lc8l+AVN+PvagiIOuh24ow2Bs6DKPCrjysXFcwM0eGxcL2OLYgGz0bKwzH+n3lYs4zDGw2wqY4jjLyzEYZ9jTd3F7Qz6CML4cuoq0w/h6AujLSysddXbP03ffO3QtX13k4WDk+ZAx2uQpLh3eNP1ul4uBh0xjzrsYeL005qiAgcwBc1zAoI/0W/kORrgrvT19F49Nd+yzCc7G/gb7Og8KEnsf6dCi2ftBFyya0HrQKX9D2eKWDfH2owi2l1oF672TsNPeGsWMaezfZ2LptcfRZGrezVaOtV5ZxNgtx4rGMO5tOfWPUpwUJ32X4bgcZzlpsT4+CTvu93cFfog9pNn4bm+Pgmi3KWRg2/CVlONNh+wZ6KZZWKhYjb1YjtXiTFisdf85G0vLN4UHz3Oz8DCb9X2xp8qxWBZiTvh3KU6qU90fc961SnE7ozN9sz8w5svx9l035RhuCpjvuPuXmIWD83AHMjYbq8bCDnTBSdiB4Uc6GccvUsdYvORsrCvjc5eajcX1y4aM55eehS+X8dWZ+KLcjmdii3J7fjaWN7HEg++DmfhyOT8sx1tTN9YeM7EYE9rGmI1F4ATG5mVKsUL16sl0iLkUvhPblwZZE2fQQN/t08oNgZfGPWVPtHCcL8AIh/tyrfJYccZ53ychDx4dLRXxGvwzDl0OONDH19R5752FX3YNc/7NkZ6ZZrTLQiZuXwSNwQ46jTz4/ot90kvft7t6Lxvn2jmHiF+ROfQeO7A=
*/