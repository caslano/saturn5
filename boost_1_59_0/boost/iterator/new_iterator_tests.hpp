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