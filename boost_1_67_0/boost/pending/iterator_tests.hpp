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
HUZ3STjgKg9zPJiPINdVNoZO27Dz+grua0bRjmX8XLViQXwN2OcPT3X/2Bmm52+8A/70esF7byZb2YIJ8OYfYBjyr29Mx2YGl3KoYXWIODGTTokxpgGjq9EYi3zqAR6fmh5eUbPjkH34GxhVv1V76JLC4dZrwH9B1b1mgVx4+ryumUBulRna5Wa+GWbTs0OA4tqWAEsgy9w8mL7B4SI6+rlqqDQHnSdMf161a0CeMyi3Lz1bHsLaXdWiEXniP5+/f8Ga0J1Nb6ue3A1tQagDvVsWb2Oe3/impKj6LI8Ki8VuC8Aysd5t2LGL1mf3z04o11IUPf+fdqqr4KrlLED8JrBUreWXEKIRakPSFyY+vNXXbSNdFM5TrpFVJugH5xX7dgsd63VVnwM0hegX0d6biU4lfNT5vQ8XnNdDnQm/+OT5QcxdMbmKjQqj/Y1Sr6S9W+ta5woMsacuam5BtsUwqWq71vBXGj0vvSP/QWp2+Iqb9JaFnyY7CW33kCg69LO0sw/kcMJVwizBeoevwodnuhOg+PjwkB9fzAUNmsG2k+LYAoCOUEqPhgbihTRjq+CNxmX2VErHh8ESIBTVucqxEmYxa1Fvnke7ievQXjZvwOPO1l8u2pvCE7a0FVpPsZF5EGcny6DesVezVWmWSLG8bwxc5gWSTkLI6/2N6K7qQ0L5csVJfyRb3ikONoGhw2kx2ioEOcrTP9rpAnRjUQTj36GVpzRKzXGrJEeukH3290ASz/EqO0gl9381StSAzNRteCdusWALjkiA/woVc1EsuvM3zofrM/m+gJ9hwwtldhKis/vV8C8GJMEVO0SkoErsnOngsIFCfGLgMpG3Rzh/NQqVi2mqnbUZojGj01cx7EnIv3xz65FP4To6CtxkM3UDN16KePEDPuZcTLBa5AvabZ2G/DxsJZ0av5reKBTM3oSm9AVJmV8JFviLk727qwyAST167bhJDP4MwKr4A42XX9oqbcywA4zjx1+O3aiazqqzEI2jcxfDrhA07wq1RQkkMJUnJm7YGSgRGqlfO+2bBKVOwB0O0oUPXHR4jzOSvNs3fQlG2r/LRebWznlXhlp3sLXLFx/loBG9mJC8tFpsp/CEnvzTCz3xRsmgt20POlkNs+wxpciYXYAEc8ZWKnsg901Acbp7Pq2AuNfn//MAxQZejwk9lWBQmXURRNmvRrvGDlm8CfqBHeSbarBLtOYO9Wwb5FtrsGtTX+pUOFzLFp7EV3s+/zr44c1rh5vh9CDNIrSTMyxTHQZfVAeD/8fQ+E2ABnsY/IAz+7no5iHhURShknf8ZYgRex63O+ncKhLL2MkUl/rEG8a6wLA4xW3BPWxNWRIGcUfQKsoQbkSDV0dFUiW/NgZ9ce2oCYwtJ0dKwIho1Md7bF5sk+wScTfqs0GWymnpBSiJIul6QEi9l0nEsgMp254eX8LYfwjcznBU+2Jdi48h6k0VEusB1Ab7wOPFzZq48c7wlW7+I8uSXPqgawlPICzJM0avwEu0/y8xvCzLBeao0t/ZzcPsiMFSl1R7I0b8uqr0vtQex22qsLVK0k1s9mXplnMpVqQ+vcgUI+uviuf+UKZmO5oXv6ZNqCLGmNLTSdq/wLzqXmewSsX2BqhCZ2jXbgSU3mUMz0H2PNVsoWrWQVz5Zlq0RRUq4VS8sMkA11u0CmAmfwzZZpLKgEP0C+K3fbuDfOXbooy6GsDvWNhAvQZEvI04yNg98EcgPtx4Wk5xBWPpvf4NxCp0LKKjAlVkugsrAg6eY52eS0q1V1YSTrTG0ssq1jPn2az6filQeiNYeSQ33Rd3CoBVocj8HSwNxZPUsqjvrvdS9Sznt+pu2T1BzzNsOafpK7whJ60XEPKRpzn8ZMVaxg+amJ7uYUSBR8a3B6vBcuA1sCw/HZdTKZ/4S4jjcxTlxUyOeLxvywemzIyNLziq3//qrMfNelYt5sI8qwqIw9dt4g9MNT1AjI6u2yK8jvQCtvNDwseMGrpie8L2HTef0Nqtcmi/uvGsde/mpFVNO57QGrpYsp5gTgAx9XCYX4bp7eth8IjmATsjFWQb2xzj+IeDdPhj8+wviCGC8bj00aOZe70Bt8n45iDHd4h5k8G4lqUdcQtvzgKv1s4Dwi4m7Rp1fcgVB2N7dI3Jk1+6reWxpSV/dsqOE+oVuaf4tB3OJ1vSCCg2jc5vnE/H7J7EVBJRjcx7DyOKrktXKLm3E6AKrOtYPFdeHr8vbi0kXWs8JZbklFx+dprhQdMN2fc0Yn20fkbCbleC78Ezxb0lsVeZNT6AG9QOie269IGanYnVdsec3B6BHY286JCWhmRAh9RGFsh9xCtiXnJVs/AstknHxbzektilq9Ua1wprVgJas64YDrKJtkoTbLApaaMtsSPHxR6I0IB+UsLVQbA4B6qJPiPrfdxuae8haLYJ5Lwol5bZcle8aWBXYF1/leCLjmSyfgIVy8PIat+WmOTGUdxsGWJN3oJcPSnnIeKpdR7EOV7cSV5TM0AsL/VHd0zRDQXfjRNFz1Dp/nUzfYPuat5uE5KLUvXwWKL4iqS2+wkdN2fGsdo/Glpgn4MywtH1YR5gww2IvNiKizIb4rnmCkROihxMXor8rMgFCcsjQ06qVDhxQZyDcp0vQ5K8ONZBiSua5+zIz1PJSotz/nIkYvQZzIWocRj4i0M+pZCKx+W9Hv9OMyriyiTrC7ZIMohkCWAOumWQYRP3KTrUztWNWXvrs4FMdYVkCjMU8800XCXoCkK/Q3yYwzzvq/oKQhk6CqIm8Aj3+Q/Zbiy2bWa576qGMzsouHxBSmYmIQZ84huGR78eM/uhr8GJndL5n0ZbpBULtOA4ZGmbzChQMYq5Sed9JMYXyGMK6cAkGy/M76UKxhLuPXvqT18If/R9+0Csgb0b19fKsF7x/ZuJQloS+og12YloA1DoKVtoNJq4tiGct8vREoCN8Al3KLx3MFudkj3bIK1vDJnT7qJ4KT1/Lx4WVmX01VsJOdTcbuAr8kp2Z/iQoA53SSQflJxnNL+tdV+L58VWQxXxrk3OmSTizuERk1GLBgEOTZUIM0I9vNQI+GKysfRe/eJzKu4nSKJLWY9kmhaRazqdEz5fKRv74S5FeWb8lkF/RWW9LJsCNl6M7/3ya2HmCFpJN8Q3w4/y2m7xOZGtnDFTIzdrDm8cs3CPrdHXU5QwQzE6OUpH6pNYqXD1OK9ubEtLtMz4TKNxZofi0p7rMeZ5J4wgtoMJ9JQ+ujAj0V2hqO2xY8ODS3hbMkxpC2Tv8wshCR2JDBOKMNBMgAszu89yud00A0UcuuJ2kL+zQR65cFGh9/wyBa3UVCkUTv+YPh5rqtz/3fKuVs/fX6OY6VdZb3e+3CP5eSll2amZP9WVphZ5DhDVQMo+3WlMnOc+SxaN7fEMyqK82MFUZ6318FEumL/7mTj1MLH4OLo5lxcwZ7ngkeDu5WrIdQLYG+hm/nkOay/Ifqd43k55RgSoZC7U9GnxcPPnnyMAkuff3ZW3N8w6TALYAfgQ1AIYcwjg3427C1u3jRjo1GwfR8sETPH5/jfw/eP9QQIloMj7iO7dMra5IS/vpyCMvy5dx2iD+gTbXIdHusKD3mTriwVFAPsI4xFYPFZnFvIqRGHHGP3gSBCFnk41yqTNy0zrNpiB4fjkvHTwBQOlm+PXYz6QYeaEAut6OGVuxnpq7zit/rEpGds+PYv5Js1YWThxAeWzcd/xOGHIbC4ILqoZBUPN3y+uEqx3/FEL1mylt3xK5Xpc55k871zNSz07maq8gnn8sfG2IGKAB0a3cqZXSq+YOvReEERuDQDiSENAYNIaZMnJS1Chkg0Zb3EOrzkvsrqLL0WW6w2ZQuiHEbM/izk9/baCJ7BgZj72/cMkqoSLq1OynCscvpZIhWlWyb1oxAwolMJJKRSDrE10c/0PGHnFYy4JkgI22uUzLgN3n595YBHBN8o6umN+JUpmYZfOQTJoW4KbmpFbnef8NDWkAMCS3NUH3mg6WOOhSJ0MIDGDGTlSKMr1H+aKQXOmWlDcUieEPhJ2geoABCz704F5zFxz/g44AH7A6huDX4WMKmRy4Yk6FhOodkKzISmBhaOzbgFVSFWRRpyQ7UjD2pNiALPVRugoZUPwPxQKXF+oV00kNlSm0FjGudP3P6fUoRk+zux/mANiOEGDbBsrm5BFseywUS0rylWAiabdqBZs4kUz5mMQfHPPBLHZ7cNoFgI4lIvHJQyjMRmrCIlTlk2HnDe8fXu2VhcrWV6UKMk0U4xoBstRlOGoTXghGF/e+PDqYnqlaaEZpqcE2WuyRk1MKZmmvJIMY96fUyyggoWm6FCM9jZfaimGHZaPBQlPfgA8lzzF+7j++zHAsi+sh8py8zMJpgEBMLNFQJmgEXJyxZJFHVAgUiCgCpAkIaROhEhoGrYg5QyBFlA/5IQJhqx2hcIZbcuamGgx7UQZy1EsCQniQCwGCEsfwT8GQPC/4wTCJ9o3G+ZkzOR3O172Ny8++PCa3rOcN1of/6qanzfMcxvlyzimDHaw/TvfxA/F0+1x1G2/PXhk9a9JDA9lK8G26h18QvaHM4eOhp8FBJs6NVRmbgeAnrpMdULyXxG5OGq0uvTDJKPiiSuZXp4OR2t6cv7BAXv0CI0MNKJafbadDyjzHhlICbl6RZyrEPEjpmVoTNikVKdoI9BCyzmHc6eQ+E8kFAInAJtD617H2leSpdyxwHsqTQnvnHhKpKaFo1Auxql33PLxvpA/g6Ayx0Makd1T50TYHKVLhKVFVA3IDDUM45KeO7zFdI5cpHDjO+wSidD5m+s0e7PLC5RAlseAf6YFL8Vd4qYFJykGaEZySki/4AxhZAVPFfjle/5Jw83quzTAkxXF20sf85sSmSh3yIjQEaeNHeUp2jpMc1Q3wFvQZ/lycUBqWMfl9avaP8ax4RsspZvA9IBMIMdpjCSrIMMBFnN6rZThYHtOc7D50k93QHlJc0D5yYMcfcZn2Kf48jcdqI8nxzE1Gqifz9EMgxw9uYYcXekLMYaWFQNCjsHtluVw+wM5GhMHOar2W3Vdq42TYX/tVJ46+PnLXp6j5acROebqp5UMp/jnOKTwUZ9/f23uI8RY2GCgntBnoD6GDIdlEuEhGpblSeEEG+cgVytPhiPsIhw7t6A39nRW1l8SOBz74cye9MtXyh/1kd1wzuFw+9HdaQ8+18FDiAyncdZnNsR4JmiuGK9TjifSBv8EgzftoCnuX0aixVTvPJ9ulHggdwc+6HVa5Kyxe1xNkdH4aE71VX87yj5Qbm5xVFrNxfdBa/P01jbaoFzifB3z4lirIjIVpV0EcZTj1r9ZKYuZRjS7eZNNJ7bV9Iy7iAuuRcP4JhZW3XQJY5KO3a1WN6cjitYUC57hqWch3Z2N4BTvs4za7dhu5K+wZteuoAx2NlvpHNpIotKa96HAjVfXROKHczJxUZJluevC/nfTJjiqVRuNjwoPpIwYRLxOEJTiJe33+6hw9r1ghAyVyea34VoyjO1G4NzDHJf4oNDgojntKUZrOuSigYLRLBOVb6k9sPgA/P2XWx/mLzeZFTQY2dQj00D0m6zmxML3Nvsx/S3fBkqPe1YuSTp1P6BOpiubOvyvl+4RlgpD22IU7bMVzqbE3DIJZ5SLx3/uzape5eyGjC1NaoPXKQH8Nzxih4o5tA9Z0/fJ1bdJtLaFDtPWsbzWDvfvYUNp0a84CaidqGlsM/Xsanr9kWH5r3d9XiNi3sW0tqlOk9qtNnXbhxRVnoewWH5jmasbMp2357XMPsfXAk4n7ffXqIraZum8DzoD8SG+RYxh2brHAwuxGFX+hvY9swZfsWNzydELY3HJsMR6qYk2aKnTC1T4fyG4Hi2zySj35nQdTqsjhfnJ7Y3De2adbA1ghxbwoQk26iVPcNk1W+6sxEI1ptfMZqv6rEbcnPbTYzCBtetT7bHac2BZtrDdzscqxkM3G33CXs6ro1qscDYAKVWL7pId9rVDoXcr6mVhq8yTEqB3Beh8uO1Iq7/X7DaGLzA3Py1RvtUs1Li9dGcZKC8wn0/KIqU8RVg4u90ybg0lC4Oy2jUWGHxnvcRweTxFk9jrcvaHvMJITXgPgVbEgS4wFz0tQS4wyUobchBvjzRmJR6qOMdzPu9fas19KHg8sWrN07xqzClytqw9vultwi6nJ23I0L0f1JLZUz0Ku5tDuy7+qFBi8w8sikf+BRt88O9DU+DMVc5L84mrUXZ4msp587yfD3kPOWEtVfQfPQVswcFylOQ8h13BjB+oq06kPESJPGbs8oD3gxy+53kgGABBV5XAwx63z9ONpKOZPJSPaN6UKS37sS2pvbcJ/fda7OWDSm9fVfx3JDmOcdgswaSqLe4gvhs+F2tu3Ho0QydF0Fi2OuW7Kj63UYxN2whyfgCCyzNtaWHJhkIvBvZLZtNDUbOs2DKTtzqIKIqFPPoZnmtBy+Je6E60krd6qm4Ro6FPjFF0KyBpVpIwNoy+jhaiiipVVKu+56QJjYu10t1ZAlFlRH3YiyklgbLo1kliPpMKrDByI4/IjaDolEC0ShWtUBLROpTICyiyDTdSA6Pgj764Ppzq0EAAkd3PKsXB0o2iiDxD0dp7t9QY4XCxxeRKDpQBJ7lQpDGOUtuAcKSaj0HNIAq24eyWDftVHfrI0TrRtCR2YRm7+g/GNwXTXAWtp2uixeUZXjSZ6IrceWF87gg7y6ewmigqjKZBq0Qy+l9rOhfZo7solXC6ihjVguWcw4bSdjgaq2IL+nMNllA/pJR36gLqL8tOG046n7OaULqh7Wz9qjcoevtqLEmEUOuIkLQZ2Bo1HSjKDieyh6YFVRtHmSiHz8yVFGGwemPb0P3ilzdfgHPw1MGFie9vWKpVvbXIBUnMx4xTMO8SkxcVPQxEV4b3P90LjB38qpP5vSM5mspvT39OvajIOxYZ+ZiGJ+WdhrlKxEjwZcqLLQaiLA72SDrNrwSdh3zdlLuJycZT2qmPIQAzc2Pa6KmqJTUnXf/mSMjt2q2bBhv/iT6nqJBpWFXknM9xnU+0ZCMxS6vRSswkY9MgoU6/bO0gHt1V5vgDM8ZbTGFaVexvq7IQTMmJKq9fQImkdHXE01tCfd6SQuSelN/luL1VtkGJqHW+/7S92zspVKWSlGBy9kCgqQbOEcv3BQn7wnYofuBkZlcuGx3J8NlSUZl/utRXUPHqehbfjKJZtIDq2628jkNIDEyo7TSaIbQNIesfbYqzk9/9r7kwFAWk+G0lK4shyGgK8rISi2ZwdId4m2XBomf01i4mVcZ8ejySDkuIHn1bglD+c9rPn9y+IYH0DDr5JWMauOFWfoNS94l/66u75wjK5hBV1SBrU7GcVVzzwhU3matoI0aKeEHisl3MEoTt9ZxZoXDe0gzbDW+sgT3p0PQuxHe9k5WF9ROjViLDngi6KC8tGGdBpDEGbCVw3vX6e37Z7oA0NvE2nZPrOE6UHyH3vo/x4ILl7JaMNDRAJ0At+KWdqyL65M9SjFUx07LUcQVxPBZ3BXHciLtaoZCOvPeheJmEkLAa5ypp4HkA7GRYyWUhETbNKpyI77YKU8+dIKhh4rBYmlvSSJW4ilhNob1LNTdTx7nh2LKVAm5F2mkV0rwm8rT7zy2ecHAkPB90yfqWsua6NTyjvTmqO8YaZSXyusQEliibETtW/TOzKIIXL3r3jC6ufJphUokSVnQNXtn+sNj51dhpB6i1XHHCu+ZssdKoXuuJzrBV32kp6G7mvIhKsBhjtEi4Oua0b9aacFyBb42JePIMDqbutmIxa9T1edkB2FlclAJX+IX407BpnpBiP0XN3p+kr6WXaB3G8w+d+ZfygpvykzVmMivBgcBwfK3gL3OiKWHOaBZ4CU4DRpiQYxXtC+VK8ALEn0jpOH0RNJLjtk59jNkxryuR/NqhI2k+DTiZdZGH2EmN295kQbvgGhgj7CbTuA0ETbB8WETT+KUF4hXIOoHoN740A8kM9aXLGXylxrHTjVOqruZJsHRS1Z+aSXt5LjctLUfrVH2Vl21nFd0MSdhm+WU3JVRiB0jnQ1bX8ohPPcfmRxLChBelZfGIitnDihtU1V3qih51FV/6ih33ab0VkmPmRkwV31zX+NqBW7uSWpLpl93rvT2g5QzRd0TFDoph5viDG1j1T7H81+TtSP316tdkwWF68+FddIVP4E7NO37i4R85xc8blOEfGp0768l8RsiPKqeKtzBWpsruHD8BaMnZvNAiz0tvlvhnmS6/jLiSG560ORzfgIG+A/7DZ7vM2Rv5UsgyFqkS6AC+BvP3ILHPWayb0a0wYcFD2TV7OZXL5/e87etWDNGnD/gjXpXxI6SYuHSl41nKZP5V72PhnYLppXkIzpwlTfUg7U1+DVwb4KGEhPbcRzT7UawtHp5gmaM1StHN4cZNG0ZN/i2TPKQVUb2yjZ8hozGtb9BIqULaG5pUH4W/BsbM0WEHNB16GE4Pl5x8eMZlukaXlnMR9WWCUfGQshdlaLaDaUvussAi2G5qmxfJjvM+UUwYI2EwYasi/id4Iho65rcGIlXM2GS3YMAcgYrxoaJCa5lVkp+ZQTE4NLCkaY/Z4Uh8sXaSb1sKf7ebi8zo8fjyHaa8XSJSqeQbce3vGT0sKr6Eb3cUV8RwsziLtdo8pYi5KxQ+RiBeH3ussUSvsC+TIZtPRL43yjzXQIo3mlWu6Ms3oqWasds3PqbFrNLK3AuVbsTwZiqTtNidqmXFLl2KW9FG4p4/I/8dEXkwotQW6LMPqq/J4C3AZoy0oKv39eH5JYbfUlzwbWdGRlwt9pRrrPWMsaMCb6LfkcHf+a5eGn9UoPMZ9b6xDY8doBAvJsbDkiJU2SAUF+B+9H0yckdZVSZZxWAPn7DF3f8N64Y9YImcd0Any7gkSXM5oo0RYS/FqX9sXJ3Y9OxenIQbpHjTGTDcA14fBw99+GC/ty4QhN2Oqc3fvGN14e4JyztUdomkk8Slg9xwHgQp5nRNsT6lyWAWmCdjqg0Ra+vaj5zEhkhlR2Fqw4SVYsZqw1R9bsLQDumM3UYxltaK07lzOBfuN/8xsviEXwPgy7rfrQv6jeTqgrTYqvVYK0oJQ6yW/O0gQx02njtmTkIqQr7S3M7rM27pzIholYZbrbzH7r5fNgU=
*/