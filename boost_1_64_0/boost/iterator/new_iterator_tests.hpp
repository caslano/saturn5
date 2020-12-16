#ifndef BOOST_NEW_ITERATOR_TESTS_HPP
# define BOOST_NEW_ITERATOR_TESTS_HPP

//
// Copyright (c) David Abrahams 2001.
// Copyright (c) Jeremy Siek 2001-2003.
// Copyright (c) Thomas Witt 2002.
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

// This is meant to be the beginnings of a comprehensive, generic
// test suite for STL concepts such as iterators and containers.
//
// Revision History:
// 28 Oct 2002  Started update for new iterator categories
//              (Jeremy Siek)
// 28 Apr 2002  Fixed input iterator requirements.
//              For a == b a++ == b++ is no longer required.
//              See 24.1.1/3 for details.
//              (Thomas Witt)
// 08 Feb 2001  Fixed bidirectional iterator test so that
//              --i is no longer a precondition.
//              (Jeremy Siek)
// 04 Feb 2001  Added lvalue test, corrected preconditions
//              (David Abrahams)

# include <iterator>
# include <boost/static_assert.hpp>
# include <boost/concept_archetype.hpp> // for detail::dummy_constructor
# include <boost/pending/iterator_tests.hpp>
# include <boost/iterator/is_readable_iterator.hpp>
# include <boost/iterator/is_lvalue_iterator.hpp>
# include <boost/type_traits/is_same.hpp>
# include <boost/mpl/bool.hpp>
# include <boost/mpl/and.hpp>

# include <boost/iterator/detail/config_def.hpp>
# include <boost/detail/is_incrementable.hpp>
# include <boost/core/lightweight_test.hpp>

namespace boost {


// Do separate tests for *i++ so we can treat, e.g., smart pointers,
// as readable and/or writable iterators.
template <class Iterator, class T>
void readable_iterator_traversal_test(Iterator i1, T v, mpl::true_)
{
    T v2(*i1++);
    BOOST_TEST(v == v2);
}

template <class Iterator, class T>
void readable_iterator_traversal_test(const Iterator i1, T v, mpl::false_)
{}

template <class Iterator, class T>
void writable_iterator_traversal_test(Iterator i1, T v, mpl::true_)
{
    ++i1;  // we just wrote into that position
    *i1++ = v;
    Iterator x(i1++);
    (void)x;
}

template <class Iterator, class T>
void writable_iterator_traversal_test(const Iterator i1, T v, mpl::false_)
{}


// Preconditions: *i == v
template <class Iterator, class T>
void readable_iterator_test(const Iterator i1, T v)
{
  Iterator i2(i1); // Copy Constructible
  typedef typename std::iterator_traits<Iterator>::reference ref_t;
  ref_t r1 = *i1;
  ref_t r2 = *i2;
  T v1 = r1;
  T v2 = r2;
  BOOST_TEST(v1 == v);
  BOOST_TEST(v2 == v);

# if !BOOST_WORKAROUND(__MWERKS__, <= 0x2407)
  readable_iterator_traversal_test(i1, v, detail::is_postfix_incrementable<Iterator>());
      
  // I think we don't really need this as it checks the same things as
  // the above code.
  BOOST_STATIC_ASSERT(is_readable_iterator<Iterator>::value);
# endif 
}

template <class Iterator, class T>
void writable_iterator_test(Iterator i, T v, T v2)
{
  Iterator i2(i); // Copy Constructible
  *i2 = v;

# if !BOOST_WORKAROUND(__MWERKS__, <= 0x2407)
  writable_iterator_traversal_test(
      i, v2, mpl::and_<
          detail::is_incrementable<Iterator>
        , detail::is_postfix_incrementable<Iterator>
      >());
# endif 
}

template <class Iterator>
void swappable_iterator_test(Iterator i, Iterator j)
{
  Iterator i2(i), j2(j);
  typename std::iterator_traits<Iterator>::value_type bi = *i, bj = *j;
  iter_swap(i2, j2);
  typename std::iterator_traits<Iterator>::value_type ai = *i, aj = *j;
  BOOST_TEST(bi == aj && bj == ai);
}

template <class Iterator, class T>
void constant_lvalue_iterator_test(Iterator i, T v1)
{
  Iterator i2(i);
  typedef typename std::iterator_traits<Iterator>::value_type value_type;
  typedef typename std::iterator_traits<Iterator>::reference reference;
  BOOST_STATIC_ASSERT((is_same<const value_type&, reference>::value));
  const T& v2 = *i2;
  BOOST_TEST(v1 == v2);
# ifndef BOOST_NO_LVALUE_RETURN_DETECTION
  BOOST_STATIC_ASSERT(is_lvalue_iterator<Iterator>::value);
  BOOST_STATIC_ASSERT(!is_non_const_lvalue_iterator<Iterator>::value);
# endif 
}

template <class Iterator, class T>
void non_const_lvalue_iterator_test(Iterator i, T v1, T v2)
{
  Iterator i2(i);
  typedef typename std::iterator_traits<Iterator>::value_type value_type;
  typedef typename std::iterator_traits<Iterator>::reference reference;
  BOOST_STATIC_ASSERT((is_same<value_type&, reference>::value));
  T& v3 = *i2;
  BOOST_TEST(v1 == v3);
  
  // A non-const lvalue iterator is not neccessarily writable, but we
  // are assuming the value_type is assignable here
  *i = v2;
  
  T& v4 = *i2;
  BOOST_TEST(v2 == v4);
# ifndef BOOST_NO_LVALUE_RETURN_DETECTION
  BOOST_STATIC_ASSERT(is_lvalue_iterator<Iterator>::value);
  BOOST_STATIC_ASSERT(is_non_const_lvalue_iterator<Iterator>::value);
# endif 
}

template <class Iterator, class T>
void forward_readable_iterator_test(Iterator i, Iterator j, T val1, T val2)
{
  Iterator i2;
  Iterator i3(i);
  i2 = i;
  BOOST_TEST(i2 == i3);
  BOOST_TEST(i != j);
  BOOST_TEST(i2 != j);
  readable_iterator_test(i, val1);
  readable_iterator_test(i2, val1);
  readable_iterator_test(i3, val1);

  BOOST_TEST(i == i2++);
  BOOST_TEST(i != ++i3);

  readable_iterator_test(i2, val2);
  readable_iterator_test(i3, val2);

  readable_iterator_test(i, val1);
}

template <class Iterator, class T>
void forward_swappable_iterator_test(Iterator i, Iterator j, T val1, T val2)
{
  forward_readable_iterator_test(i, j, val1, val2);
  Iterator i2 = i;
  ++i2;
  swappable_iterator_test(i, i2);
}

// bidirectional
// Preconditions: *i == v1, *++i == v2
template <class Iterator, class T>
void bidirectional_readable_iterator_test(Iterator i, T v1, T v2)
{
  Iterator j(i);
  ++j;
  forward_readable_iterator_test(i, j, v1, v2);
  ++i;

  Iterator i1 = i, i2 = i;

  BOOST_TEST(i == i1--);
  BOOST_TEST(i != --i2);

  readable_iterator_test(i, v2);
  readable_iterator_test(i1, v1);
  readable_iterator_test(i2, v1);

  --i;
  BOOST_TEST(i == i1);
  BOOST_TEST(i == i2);
  ++i1;
  ++i2;

  readable_iterator_test(i, v1);
  readable_iterator_test(i1, v2);
  readable_iterator_test(i2, v2);
}

// random access
// Preconditions: [i,i+N) is a valid range
template <class Iterator, class TrueVals>
void random_access_readable_iterator_test(Iterator i, int N, TrueVals vals)
{
  bidirectional_readable_iterator_test(i, vals[0], vals[1]);
  const Iterator j = i;
  int c;

  for (c = 0; c < N-1; ++c)
  {
    BOOST_TEST(i == j + c);
    BOOST_TEST(*i == vals[c]);
    typename std::iterator_traits<Iterator>::value_type x = j[c];
    BOOST_TEST(*i == x);
    BOOST_TEST(*i == *(j + c));
    BOOST_TEST(*i == *(c + j));
    ++i;
    BOOST_TEST(i > j);
    BOOST_TEST(i >= j);
    BOOST_TEST(j <= i);
    BOOST_TEST(j < i);
  }

  Iterator k = j + N - 1;
  for (c = 0; c < N-1; ++c)
  {
    BOOST_TEST(i == k - c);
    BOOST_TEST(*i == vals[N - 1 - c]);
    typename std::iterator_traits<Iterator>::value_type x = j[N - 1 - c];
    BOOST_TEST(*i == x);
    Iterator q = k - c; 
    BOOST_TEST(*i == *q);
    BOOST_TEST(i > j);
    BOOST_TEST(i >= j);
    BOOST_TEST(j <= i);
    BOOST_TEST(j < i);
    --i;
  }
}

} // namespace boost

# include <boost/iterator/detail/config_undef.hpp>

#endif // BOOST_NEW_ITERATOR_TESTS_HPP

/* new_iterator_tests.hpp
quJyHyJwD3gx+AzYE0S8zAeOOXI8NjAfbmX6bgdrgovBduBS8A/gHTxjdzn3s7oT7A/eDQ6kPfOB41R4hsB84P5FdcFPGO/X3O/pe3A9+BO4iftcbQF/5nktyr4DqMy9QeV+Fc0DQA/KexgYBo4Hy4I3guXAJWB5ysPVekwBupT5EInLN05Ui3owBawA1geTwYbguWBjsBXYBDwfrA22pVnFn6f72hg3YPxRuEbi4vuJnG3cgvt4tQQ7cj1rF7AV95E6n3qxDTic59tkqDSD4xhuItjBMZ6L9/3B8lwD4a88OBhM5ZnFA2m+j+YXaD5G83fgUMbfUfdnkAeW9qMz9f6lYFmeqVybZyk3cor311ok7/TMf8pHJVw3Mp4M+EsAM7mOOBtsDU6m/E0BB3MfqRHgHObHNO6jNp3rimfg/59o/gfNHu4vVQOczbOX5zBd3fV7GsqIz6eeoz3TFcf6UQuM5zrnamBtlmNdtm/1wKKAdca9RkeEPHtn+OiIs3b+zmTEtQzXE7hO4IrMjHCa4uqNqwDXElzbcR3G9T2uuKwIJxVXr6zS9cqlv9Jf6a/0V/or/ZX+Sn+lv9Jf6e//6/ebrP8fnZ59Ntb/J+AspGVqDW+Umj+Yn5E9rNUITFCWfQGeNPYFaM99AV/knJAXcP0R4fKuM+eEIFEB+wJs4jdA83vdBAmzD+6usxuX2lsv3GFcuMMs3FV/96C9dZ8AfkPcLO6Ftu9+DBt6rtXN4v6ws9nx2M/6u86yhx2/tzzifXacyhCm3c3vW5+Ie0X9fTjuemVO1N/eKoq5Ae6bSD+YYSx2WL/BPPla4ugGs143Iw+QYMzNXyB+ijD2M8XvDPp5Yr8NYzFXOTXFvyv+d4p9gczgSsa9mjgX+503/5G494ZdFNwS9RrsvyQhbFLJ55Vu+hfWrZtr1upxOGE/bq4s9oIPq3n111tkjtMFbXKXxLJeKuG2erI9NbHyLNzZiMs6x/5669o1Xe4NpskaJM8Bt4NV5hDePneC8lpLwlf1vOW2sskcwttltjHl6FZxf9JzFVK7Gk+3x6knpwfd5tZzduLL+mfuPj2X7/MblN82tjka5n34HZtnLVF+14l7WX0+0AYxr/GYdSGJ35l/Frfunp7IgfHOCLcV8lbcYJsvz7vLreqswIyTafh2kC5xfqvWfIjbhR7fHpNOwBmXyyXe8vr8p5Vi3uSx1bdz5Fkr6vr1hJhnO1Hih/4hE/mGLoqV+zfweFAb3nI7GfUsO6iebZR7r/A0dbI9CcbZ/4vE/glPHyfdU9moZ1+LfTjXx+AvbVfeeq5+a0lLnNWtzHTl1oRmnKIi5jCezSd1U66dRh2N+1V19MzWaan5hH+a5r+2avAN/uZ9MJvzDTuxnn/P8/NGeRC3kgBwa1MloKHr+TAU43ktg+q61usJM7zy2MmD7+6iSxkf7rIeo8zf4EuUrvN0s9f5TvKsK8T9KXeyM07rgWVid6f7D6e5Pm/xslkSj30ez4wQeoHpWy/uj7id4ds3f/sLseuMfVUu1GfzrRU7yCrlvOUs1lPlrtNgPfOTabC3hwlgJXG/ytMT9ZfPrvNtBZ7fFxft9ZyajSWYq07/IfVN8gw+B/f2TRHzJaa+0fV2jri95LZHHZiGlaiVud/wQrF/AWXyF7NN1vk5dybcIblVZD4P7HR+ldN7Ft8qfl4M0hk1qX+nyD3+5HrgozlkaarzHL5XVtM6N0zCYzcB8e/qci3r1EXbVgHt8Sx8d+qJb6dN8X0yUevCxeLvOfdUOqiO+PmDpynaH7OtjxX7fp5uThk/HZQh9pHmHBPahVv1zGZxqyv57AlK+2i3OE+v1fNO7pTnbW6N7/w=
*/