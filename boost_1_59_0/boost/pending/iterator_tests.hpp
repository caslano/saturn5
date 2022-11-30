// Copyright David Abrahams and Jeremy Siek 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_ITERATOR_TESTS_HPP
# define BOOST_ITERATOR_TESTS_HPP

// This is meant to be the beginnings of a comprehensive, generic
// test suite for STL concepts such as iterators and containers.
//
// Revision History:
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
# include <boost/implicit_cast.hpp>
# include <boost/core/ignore_unused.hpp>
# include <boost/core/lightweight_test.hpp>
# include <boost/type_traits/is_same.hpp>
# include <boost/type_traits/is_pointer.hpp>
# include <boost/type_traits/is_reference.hpp>

namespace boost {

  // use this for the value type
struct dummyT {
  dummyT() { }
  dummyT(detail::dummy_constructor) { }
  dummyT(int x) : m_x(x) { }
  int foo() const { return m_x; }
  bool operator==(const dummyT& d) const { return m_x == d.m_x; }
  int m_x;
};

}

namespace boost {
namespace iterators {

// Tests whether type Iterator satisfies the requirements for a
// TrivialIterator.
// Preconditions: i != j, *i == val
template <class Iterator, class T>
void trivial_iterator_test(const Iterator i, const Iterator j, T val)
{
  Iterator k;
  BOOST_TEST(i == i);
  BOOST_TEST(j == j);
  BOOST_TEST(i != j);
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
  T v = *i;
#else
  typename std::iterator_traits<Iterator>::value_type v = *i;
#endif
  BOOST_TEST(v == val);
  boost::ignore_unused(v);
#if 0
  // hmm, this will give a warning for transform_iterator...  perhaps
  // this should be separated out into a stand-alone test since there
  // are several situations where it can't be used, like for
  // integer_range::iterator.
  BOOST_TEST(v == i->foo());
#endif
  k = i;
  BOOST_TEST(k == k);
  BOOST_TEST(k == i);
  BOOST_TEST(k != j);
  BOOST_TEST(*k == val);
  boost::ignore_unused(k);
}


// Preconditions: i != j
template <class Iterator, class T>
void mutable_trivial_iterator_test(const Iterator i, const Iterator j, T val)
{
  *i = val;
  trivial_iterator_test(i, j, val);
}


// Preconditions: *i == v1, *++i == v2
template <class Iterator, class T>
void input_iterator_test(Iterator i, T v1, T v2)
{
  Iterator i1(i);

  BOOST_TEST(i == i1);
  BOOST_TEST(!(i != i1));

  // I can see no generic way to create an input iterator
  // that is in the domain of== of i and != i.
  // The following works for istream_iterator but is not
  // guaranteed to work for arbitrary input iterators.
  //
  //   Iterator i2;
  //
  //   BOOST_TEST(i != i2);
  //   BOOST_TEST(!(i == i2));

  BOOST_TEST(*i1 == v1);
  BOOST_TEST(*i  == v1);

  // we cannot test for equivalence of (void)++i & (void)i++
  // as i is only guaranteed to be single pass.
  BOOST_TEST(*i++ == v1);
  boost::ignore_unused(i1);

  i1 = i;

  BOOST_TEST(i == i1);
  BOOST_TEST(!(i != i1));

  BOOST_TEST(*i1 == v2);
  BOOST_TEST(*i  == v2);
  boost::ignore_unused(i1);

  // i is dereferencable, so it must be incrementable.
  ++i;

  // how to test for operator-> ?
}

// how to test output iterator?


template <bool is_pointer> struct lvalue_test
{
    template <class Iterator> static void check(Iterator)
    {
# ifndef BOOST_NO_STD_ITERATOR_TRAITS
        typedef typename std::iterator_traits<Iterator>::reference reference;
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
# else
        typedef typename Iterator::reference reference;
        typedef typename Iterator::value_type value_type;
# endif
        BOOST_STATIC_ASSERT(boost::is_reference<reference>::value);
        BOOST_STATIC_ASSERT((boost::is_same<reference,value_type&>::value
                             || boost::is_same<reference,const value_type&>::value
            ));
    }
};

# ifdef BOOST_NO_STD_ITERATOR_TRAITS
template <> struct lvalue_test<true> {
    template <class T> static void check(T) {}
};
#endif

template <class Iterator, class T>
void forward_iterator_test(Iterator i, T v1, T v2)
{
  input_iterator_test(i, v1, v2);

  Iterator i1 = i, i2 = i;

  BOOST_TEST(i == i1++);
  BOOST_TEST(i != ++i2);

  trivial_iterator_test(i, i1, v1);
  trivial_iterator_test(i, i2, v1);

  ++i;
  BOOST_TEST(i == i1);
  BOOST_TEST(i == i2);
  ++i1;
  ++i2;

  trivial_iterator_test(i, i1, v2);
  trivial_iterator_test(i, i2, v2);

 // borland doesn't allow non-type template parameters
# if !defined(BOOST_BORLANDC) || (BOOST_BORLANDC > 0x551)
  lvalue_test<(boost::is_pointer<Iterator>::value)>::check(i);
#endif
}

// Preconditions: *i == v1, *++i == v2
template <class Iterator, class T>
void bidirectional_iterator_test(Iterator i, T v1, T v2)
{
  forward_iterator_test(i, v1, v2);
  ++i;

  Iterator i1 = i, i2 = i;

  BOOST_TEST(i == i1--);
  BOOST_TEST(i != --i2);

  trivial_iterator_test(i, i1, v2);
  trivial_iterator_test(i, i2, v2);

  --i;
  BOOST_TEST(i == i1);
  BOOST_TEST(i == i2);
  ++i1;
  ++i2;

  trivial_iterator_test(i, i1, v1);
  trivial_iterator_test(i, i2, v1);
}

// mutable_bidirectional_iterator_test

template <class U> struct undefined;

// Preconditions: [i,i+N) is a valid range
template <class Iterator, class TrueVals>
void random_access_iterator_test(Iterator i, int N, TrueVals vals)
{
  bidirectional_iterator_test(i, vals[0], vals[1]);
  const Iterator j = i;
  int c;

  typedef typename std::iterator_traits<Iterator>::value_type value_type;
  boost::ignore_unused<value_type>();

  for (c = 0; c < N-1; ++c) {
    BOOST_TEST(i == j + c);
    BOOST_TEST(*i == vals[c]);
    BOOST_TEST(*i == boost::implicit_cast<value_type>(j[c]));
    BOOST_TEST(*i == *(j + c));
    BOOST_TEST(*i == *(c + j));
    ++i;
    BOOST_TEST(i > j);
    BOOST_TEST(i >= j);
    BOOST_TEST(j <= i);
    BOOST_TEST(j < i);
  }

  Iterator k = j + N - 1;
  for (c = 0; c < N-1; ++c) {
    BOOST_TEST(i == k - c);
    BOOST_TEST(*i == vals[N - 1 - c]);
    BOOST_TEST(*i == boost::implicit_cast<value_type>(j[N - 1 - c]));
    Iterator q = k - c;
    boost::ignore_unused(q);
    BOOST_TEST(*i == *q);
    BOOST_TEST(i > j);
    BOOST_TEST(i >= j);
    BOOST_TEST(j <= i);
    BOOST_TEST(j < i);
    --i;
  }
}

// Precondition: i != j
template <class Iterator, class ConstIterator>
void const_nonconst_iterator_test(Iterator i, ConstIterator j)
{
  BOOST_TEST(i != j);
  BOOST_TEST(j != i);

  ConstIterator k(i);
  BOOST_TEST(k == i);
  BOOST_TEST(i == k);

  k = i;
  BOOST_TEST(k == i);
  BOOST_TEST(i == k);
  boost::ignore_unused(k);
}

} // namespace iterators

using iterators::undefined;
using iterators::trivial_iterator_test;
using iterators::mutable_trivial_iterator_test;
using iterators::input_iterator_test;
using iterators::lvalue_test;
using iterators::forward_iterator_test;
using iterators::bidirectional_iterator_test;
using iterators::random_access_iterator_test;
using iterators::const_nonconst_iterator_test;

} // namespace boost

#endif // BOOST_ITERATOR_TESTS_HPP

/* iterator_tests.hpp
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
*/