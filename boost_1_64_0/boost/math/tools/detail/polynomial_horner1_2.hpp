//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_2_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_2_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_2.hpp
gAqJJjdDNDxvuiodKN+Y+V2AGiFtd51KO/Y57v4B+ed7pKDoX0nXHTFKQQlbE4vrPEjwWTU9rlrTaDYl+QVZy3y6sBrAzGJmsh/X/BXJQaRF0qTpngL9/2UTsffhRvEzNEYxsRP0YfUlrTWt3q7BpEH8aWnEFUgiElqNidO+SPRWwVc46WYeTdM/BR2Y/qwLNg+L/HELMT7KKCUeU8f237hHSQypKKpZuP9ixYto/xyqT7ONQ+eSFe6pKiL4TlMsVdDvxvjmBpYlZ4M1mrFvpSqTDpWwC58DK93FHVb+zvECtRqtS3PZmExF7yiGVHvSKdLcwPjp0cjfj/wI6g3IKAx6cgR315cUhpDeXotvSwd09y2IhEJWAyg8L92FcRr1pW8X3cgpZzgNpUCQhOsCTfkjwOwNUEJa0ti4FU7lfezpa8uwSU4MisI0CMypF7fic/hNLm0LvdFFZwWP4yF+dR2AValsoLxuNoil381X8Bkrkj+dKVHtXox8VMYRyvlq+mzMjAEjtC//19YxDJ0JbyZbErGVQAxTQsQlFFeV5ANltTPkjBBOT7yXBA==
*/