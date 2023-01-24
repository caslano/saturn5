// (C) Copyright Jeremy Siek 2001.
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#ifndef BOOST_ALGORITHM_HPP
#define BOOST_ALGORITHM_HPP
#include <boost/detail/iterator.hpp>
// Algorithms on sequences
//
// The functions in this file have not yet gone through formal
// review, and are subject to change. This is a work in progress.
// They have been checked into the detail directory because
// there are some graph algorithms that use these functions.

#include <algorithm>
#include <vector>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/stable_sort.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/count.hpp>
#include <boost/range/algorithm/count_if.hpp>
#include <boost/range/algorithm_ext/is_sorted.hpp>
#include <boost/range/algorithm_ext/iota.hpp>

namespace boost
{

template < typename InputIterator, typename Predicate >
bool any_if(InputIterator first, InputIterator last, Predicate p)
{
    return std::find_if(first, last, p) != last;
}

template < typename Container, typename Predicate >
bool any_if(const Container& c, Predicate p)
{
    return any_if(boost::begin(c), boost::end(c), p);
}

template < typename InputIterator, typename T >
bool container_contains(InputIterator first, InputIterator last, T value)
{
    return std::find(first, last, value) != last;
}
template < typename Container, typename T >
bool container_contains(const Container& c, const T& value)
{
    return container_contains(boost::begin(c), boost::end(c), value);
}

} // namespace boost

#endif // BOOST_ALGORITHM_HPP

/* algorithm.hpp
AuorEA5P2Bs5I4zYthtW/lfEhtwJi73f+ZcTDHxauNe78X8MTrpYzVgP0yaOgOyHJdQE2E7efbdXSUuuUJdUGVGHljvPxKSVqxinprY2+y2pz4Jerj33eEBq9cZUP/96JoHsBCJOxW67ekbuJ+97AprNn35+PWLqbN1a+ZB5My3pz26udqV2GCmXTYsjlXfrc3kfWCyOrIbXqspgOxi0sTowmP7wm6gOE+41smAAoNYzgl74Yp9rzIGFhPW+PegidjWC0lEWS3VCt37w0vLK4JWrq43qQq+cmDVFf40hIBITUmVBdGbrh88fLwnfD52o5YtTRXEoDKDIz0ij8GmEMavNL5IriEkTPhGWqot72PZfBYQGCFVAGQKRz7F2CT4BgD2BrHL/GYwzsjUywTLknwCsFPtn60+ZdWMhvH+yQzRlhmDXV3Mgn5/s0F8hrR6kd9cFsBmEZIOlBW3lwXEj7T/3z3pIDGREf/cs1AGVyyIxQ9QglGcea47Pzmu6BWcIkfH4hLKUQoiqNLOd6rr8B3g1JoI7CHjvijGJaauU/82N6JKJoxjynKseFiR2NraUh8RB/UQCeCX2HAFBdsZ6yTUTgOh9RQGY54zuTsEUAGEAoRZ2LeuI3Xf5HkZf/nqaRbmutjgRtDN0FzQXrFa0lVDj0JNeoiI6EMUiLhQLWrt3LNdDBsIH0YGwF2uW8fZ1z7qeHm2ci1NvsbWk
*/