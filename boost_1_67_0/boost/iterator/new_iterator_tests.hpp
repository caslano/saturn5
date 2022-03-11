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
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
*/