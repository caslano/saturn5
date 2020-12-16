//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_2_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_2_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((a[0] * z + a[1]) / (b[0] * z + b[1]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_2.hpp
CjqfRBvTgOn5cRvfTWy8Bn6DQI4PLvnrqdXXwu+rW0vbO4v6ZRyEinHpXH8dYGtXBmvb6CPkHeY3GN3++4v3mt/1iaD/+/wH4fdtHYj4xIz/O/sQ/L6zdXVz9UF/3z/l6/g9TSSStMhgzCfpzOw1e8wTRb5vgMO+zKkGHGQ3hWKaOGfJW5Z7t889WTZ5LkQJXEx2znKPEm4etbIoZdKVZcWQ55x/WjLvSJYlMo8iJTt2Pyg+r8+rKBHnz57Q89h5mMfMyQvu8Zif3lyZpkXLIzFsh5MXz56yNiK+T7JDwzOVq1e2vff6e/zfF1eW/bhoewm25tuVbUwRzBpZ4vdy3xgckvc4g9vGcbpscK13u+XogCHmONnXk5k7Ae8W1+TN0cKr3O+QIs49/tvtFGJbD2p9/bl0qfcpdnIe11c/DdZh9robXAhZzpM+B/YajjTrOE8E6cBHHSiQmfNT9vXOPvvS0jpUsPtsf0r/DDpp4lGb95z4HDF4S41vrtVNuODVyurujW/CWukszNXs7ImzZ0nmjJ1hZ/Db9/jDwRoxyngaK3Wr3z6b3gsP0zvqOmlqntV8/DdleWmdfksq60jjrfZdyKepLbkx9cS3IYDD2xCkBK9DcD/yarcfucCVWSu++rBu1+T8wjmY+8zbUNu4EawZzZtwad6T3q9x5Qio7xNa9+6YJF1jbt+R89NRzvB6yI/xPhlyaDzg43sD3Bgd2zyeH8XtZZTj/GAKOYEauXcd1b6QE6ol1mt6/wjXGhDgO3XCcU/Mcc45QHDbLmgLPE1xaJN3WxtpitlbbjujoM3wQcID00GHvXAbYL5FKdZv43aCbS8NLpu0kXPoEOHsLH3JdT+2wR0hB4qA+KOvCnHYR3j+wQ4T3Nzfu6Lgmv3VhGf7zaVz5DUED908oC9dwqP9T+KPv9bwzABE3YB3lhajhoH+Gcy1NwHHtzJGbPUtgJnJFx5RLm2786T7jwI2OvZ9XwDPEE44P3h1eDvw6DQNcS53Pqx17yrMactrnWAQ5/LOyTjttm3avf9E8MblVYBtrS2fntUesbsJk+KHAV9ZXkEU0/7DtMFXeyPYv28zmCfn4mwNqK1s0VRtydmyDny+tj50KaQfDDivQqQ8r+7SXFkeV55nJw2+td1FEgjr+pquLrSu9hun7u++W0vgjWvxS0vr8C7jmnn6vKJXgQPPX+sNv/yJYnWWpFlevOL3q5AJM3M517GFh5murS/v9Lrzy1T/Bi9OO40+v9CeizKxWOWdX4CjH/Ew2ZyG3yGd+7RMdP6+Jlks2hjqrX97QP+mA1W7n7unSHCtbvDeKH5l2+CQV+HS/FQkF8wZuf79cigHMx3I+b6g9XfktZNU2j6V8t+XPDIZ8tD/+vvs+Nw7hnPJxK5dA0+66Dt5Zt8u3JXLEOBj1fDxndaB8XzNc5x/Twcc9PWO7zIPjnJgzIEuQWKEeztwb6ZquN94qU/fIpRcJnq4sE4aBJ2ZJY6viUFgo5PypIqzgnXFgxnCepGm9pl30XGZJC1vVFqbvD6/tezywj3ncZJXxIRUVVlwZfLaXtLmPCAa2vfdOwjs+6KqKOPMVqzzht+ZgAR1U0F+DS9yFaWmbkYO83M2jauDwO4tzRWP8pSZhV5n0KJ7AAzHtjboHfVXiWzO2kQkeZlERBbimnf2cwO91KHxuR4P+qNuoyrOm9oaJZo85+CbZW0dYG354EeHZ2p7zSj0rWIA/+1pfU6POLGKebfVXfiWok1MR8QvGO5L7iU+pb60rnfa4E9Kv/ii577M5/HehjaUMyw89+U+J9ElspwTJ918+0Bt5ls39ZlD0/X+9pLOvLeDe4pnLZdqhg7vvgmFu+w=
*/