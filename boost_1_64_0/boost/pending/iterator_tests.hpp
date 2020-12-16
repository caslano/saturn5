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
# if !defined(__BORLANDC__) || (__BORLANDC__ > 0x551)
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
t4TpNyzgfof7g7yxpj2BV3PcjDH17vkE9xOV7Eeua86O4XqS88AR6m3LlfTbPMeKb+X+P5R2n8R6MV8/3gfYDTv3RuhziPNlDcKOcUk7LeT4ph1m0E+N53eP1Su4TxpMvWVzX8N+3RPI75O7Ob5d3yF5DjOD/b1gAtMncJ9zkN9TuH4NC6WfQ7qOdrP8s95eRk+cx85zn7eAejnIc41D/H6+n9/7jn7E/jnPeXIm9UL/7s/+jF7Eew/0N304jjxcfiSZ/ozzcwb3dRGu8yWeD6ydyv7+A+2W+7eh/ry3NZZ2yN+jXPeW+3KfN5z+Ipjz/jjXeOF3jkdpl3eyfNf9KNe+5nZ+j7qF+4i3eA4whvYLvfjIe+7rNwylPV1L/3qthwmn8zvAbK6z6CeOPc/9Fv1EIP1Dxlra08t8z34JpB1vor1O4zmvn+s+xSzOL+xXjzvYH0tc33m4T6HdrHCtL6+mnvI8eW7I9cJM+hvX/TiOj6PF+N8d76lX2uso2uuOeNPew5wfFjbQ/jAevREGduzjEL7D/dsOjqNc6v8c7XoF/TvPI8Ju5fw0nPtQ6mfQFLbzQ/pR3meYsZLjmHrLyaBfpn4iJjK//px/uN7KYn5L+F199Wx+t3CdX7P8kylGn0d4PnKC/mV/LecBrtcuPs7fOzkejnFdmelhwpn091ez/X25np/BdddrtI+b6Z+4vvcYSz26vgtxno29hf0xn+uYDPY/5+e8FLY7kXbD9W1WKuszgeU+TX8Uz3LTOU98TjtMY3vv577Mn/cGXOd9HEfR3+V8PtH4r73Lub6DPXT4GeaXk876BnLfN5vrwTKOg+foP5vp575H+6U+l0xnv8yinfbxNOFk+vEB/P7L/frhCSY8SrtdVM7znKVsD+3oCP3XXn43KKR9n+S+6iL9ZbTrXArrhc4S8p7h6vn0R7TrPqEsh35i4mIznvqwPzxc9xfZnu0cfwu5bjqRxPqc5PzAcezP+arnbezfAN5H4ro6nv52Bvf1S+/kvMh6ZLE9a29mO7Zz3zGT66RnuI99i/c9eV69dC/z4/nn7on8fvmsY8b7Zxyfru9QT7MfPqYdvGfuswydTf9Ne+6TQT+6lnriPNWd66Ac6iGD/Td3MsqQ+rKc5UuYD8fxoFv4/fMxji/6n/WcHyPCud75kPXiODs5hvPMefol+tVjs5h/Kuyo4/yPdkt9FdIf7OA92fE8Xz49mflxnZMznvM79yG7+N01mvd3Yh9n/yXTb81kPdiuLTyf9k+m3c8w5Q3pmJcQ8vvubo6TLVn0Gxx3PsPod2Zy3TiGdj2e51erXffL6AfvZz9xXHR3nSNfyfpQD6emcr/Zl+cXPXgPajb7ZwT9C+10VxLtnevWbXx/kXpazfVgYaXD+6rsB/bHiDLuC+gn8mjH4/m9sbvrPvZZ7otpn9Nc98au4njIpP/sx/ZkMj7vNyaW0q9ksFza+2HqZxDte/UfeD9nPv0S/d5+7kNmfEw7TOb8mEk/X8tyXPecXuX+M5ztzaDfW8Z2LaG+P6W/4nfKJZHsT+4rt9P+555ge9m/C7leHDqA8z/7cxPTR3N8j+rPdUGKsa+FtMcTM/mdie1ZzvV52C76m2MMmX7QWo63tdTjQd4rmcx9xtW8X8DxMo3zk4fr78TieH4WQj1SH6Nc+uP7/ZM4vyWzPVxv5bju0VMvS9I539VS3+doz0w35Bn2v+veAvM9RL2c53y70HWvxvV3b5x/9k7neOM86s97RT4DaP+8B788id+FeU7j8SHtmN+7TkNPHelbaMefsR4DqZdeLH8e/Q7bucmX9z9fZHuv4f7xPO1yKfVSw/HzNv1EBdtdyXOp12i/ru8=
*/