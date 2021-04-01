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
udI6x1xo5AqbJRhudIflCn6qbmnCFp3xpM8XU9ZEzgjjGhoNMsPrMsOEf03VQFDQX8JA2Mv+JlP7g8pSrrncm+ugIN++PBu9vMoNV5tvS/V0TEyr0VrBdSAnd/V174/M4EI4UFRUPaPP13hyDZ8cv617w3BqAzI1W8eFEH6cGaqwYsmPdxTPk+W8mvC3ppQpdOvj+U2ZYOwGoc99EHm6TOU09I/L0UfK5cfYUcqnCSSHfTcvIsEXXTN84XJEchHBwQcSQO4fFukMEwxw6917WCT+WQ7Nd9RsJWbdNXPMBM6HcLIBXREjD50NXjq/byReG1F4K7eAJMrtVD2DOOi2Won2dofU9ccDsb9nZHH5r9U1eNLi92Rs/wGaxKtwwu9QUjXdjqyvGub0qVn6wGWMTSBzhpHRHBTDEYqE5jp1khlY44hyyNbsFLhio2vfRRDyD8rN+Uau4QFJ5XnRe6fB3P3HlAT8bQWUtSL4j4KTpG3HYYzY0PPUxmpztKBP6ivke3KLZ+qrDcSLh4D/UMI0Ha4AXv0bW8Z9RW3199m4mH1QnGM5mBhZDx0+ig==
*/