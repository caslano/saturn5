//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_ALGORITHM_HPP
#define BOOST_INTRUSIVE_DETAIL_ALGORITHM_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

struct algo_pred_equal
{
   template<class T>
   bool operator()(const T &x, const T &y) const
   {  return x == y;  }
};

struct algo_pred_less
{
   template<class T>
   bool operator()(const T &x, const T &y) const
   {  return x < y;  }
};

template<class InputIt1, class InputIt2, class BinaryPredicate>
bool algo_equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
{
    for (; first1 != last1; ++first1, ++first2) {
        if (!p(*first1, *first2)) {
            return false;
        }
    }
    return true;
}

template<class InputIt1, class InputIt2>
bool algo_equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{  return (algo_equal)(first1, last1, first2, algo_pred_equal());  }

template<class InputIt1, class InputIt2, class BinaryPredicate>
bool algo_equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate pred)
{
    for (; first1 != last1 && first2 != last2; ++first1, ++first2)
        if (!pred(*first1, *first2))
            return false;
    return first1 == last1 && first2 == last2;
}

template<class InputIt1, class InputIt2>
bool algo_equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{  return (algo_equal)(first1, last1, first2, last2, algo_pred_equal());  }

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  bool algo_lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                     InputIterator2 first2, InputIterator2 last2,
                                     BinaryPredicate pred)
{
   while (first1 != last1){
      if (first2 == last2 || *first2 < *first1) return false;
      else if (pred(*first1, *first2)) return true;
      ++first1; ++first2;
   }
   return (first2 != last2);
}

template <class InputIterator1, class InputIterator2>
  bool algo_lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                     InputIterator2 first2, InputIterator2 last2)
{  return (algo_lexicographical_compare)(first1, last1, first2, last2, algo_pred_less());  }

}  //namespace intrusive {
}  //namespace boost {

#endif   //#ifndef BOOST_INTRUSIVE_DETAIL_ALGORITHM_HPP

/* algorithm.hpp
dc06hvcZqJU4j4GPExZaSziU9x70seIEH+8grQB6Et4Ob6V1bS1yYA/nJzlOW0LevAG7oUpoJbof59pOjruQfxAshudFjkvBQ5z3QCehTuIJEJZ3FWUKNXC8HgxBBR9O9bSBz8MTInwPdLIDGcIOQ48vAaETUOkd1NGlKTxgJn2O/Y8hA94PFRD2ODgPLIKnBApAa6GDl6V6erhWwbXt0F6oBf07wJqlxA/uBPdAHdAh6BhhGbtopxxPBzMqyGNwGtgC7oJWctwAtVvn4DMW3zJ4oHlQG2FlYMF7SRssBQ8RthbcDj3P8R5wOXkQ5HoIaoXaCVtv5QvHuw+gL7oeJqwcez3ryB+OO600aKN1hBW/Dx0JLwOXg5VQF9dbOA9xfBD5veCLYA/h+whvpU/dD/VAvky+gQqthVqg3dB+6DB0AioaleYpg+qg3dB+6HnIn5XmmQ9VQjuhdug5KMNHOLQeCkH3QwehY5B/NNegSmgX1AG9CPnHEA5VQjuh/VAPlDY2zVMCrYQaoFaoA+qBfH5koDqoFdoPPQd5eKtsOlQO3Qw9CHVBx6GCnDRPAKqEQlAbdBB6EcrIJS1oLbQd2gt1Qs9DGXlcg8qh7dBeqBPqgTzjyCNoETT8G/4N/4Z/w7/h33/6Lw3imxvhNWsL1zcGa7c0N25tqq4NHzY3zNq4tb6hZtac2XNml26ata15bumc8+xr2+efO6u5jpV6NbOaatm7rLk2wlHddEOwpXG99bK1+mOrrpbZvFkfHnsvymagzPstucxRfqnKY+Pl9dVNjc2Nm1qKp6+ZUbw62FJ/Xf2N9VuuKV7GgsD6BrYLSveszM4f57H321ifwl/MfmGvM/HU85xaX2EvcufrJXPQgVUWc2tg0b9TY1pPgXzsGqwt9TXmdTTwxu4VptZ6GdZPmOKtbqrnwLBOAt74e3Dlabx5wquv5RnvYi8Xeffe/i5M1BowsTdq/zGxizB0FT7RnzB00vfuit6z9ubUcMKTw4BuxMlJr7OcrGLqt3x6tbz5g+Kr3e6Jt/7XkefsRgIa17fE5OOunOTzEb04Ry87HyXPJH19n5JKcRv1/YAqrbWtP4/OnxqaWUutlUX912FkDXYb8wjeaLvvHoTduo16HQiMcNronUx4jI3sDmbXgaty4tsXGIB9gRj79gzAPnSIb5/+Pf70sHCBRDIeettkytFon/ra5qpLyzz92ln5c/d9kfASZudJVXMLG1AZ6zv8MflSMOh8CeuWr9d3TQc9v9pGOvNro/WCcvz8Yi1t//kV0vJrtWof3HjirYEcYH6FYvLrw4PIL3TjHN0S5Je+R9wzGeb61RY/v6zOub66qqHfPCMO033JvE/aAPOsLbaODeDeZKxjSjd3dezmTOs/eo+q261vCsfJs+rGrSzB7L+OdcbYNCEJm/T+v0ccmCIRmAhdOonwOHrWzK3vV8eeAfQbUbxpdvkbytPAK+s0jT5MTD7NGcB+Xlfl9O+XkL7mg+hrAtEppv3s8jl9xZpi9DzSl8drLrpq9WUXlRn9xYL4eU0c7vPaf8S9v+g/4t5f9B9x7y/6jyTvLxa4KJdk/cVIe2gf7fQXN1n+kLmsrKLqt4yKj7j3GYuPuPcZi48k7zMW5AzcZ7T3wh7j9KfqrP0nnHmk+Y391+XyI+79qvIjyfuNhnpk9I1vHuu081rsDBrs1H3HwgQ2BgdgY/BI8r5jYQIb9b6p3e+8tzdgY6vZRt1/7NfW1gH0Ta1HBnZvbz2SvP9YmKT/aH9zLNuZZ1vIs/bEeYYP2X+etR9x70O2DzDP2o8k70MWJulDRr4hUJRrrmddhjwz+JH95lvXEfd+ZNcA863rSPJ+ZGE=
*/