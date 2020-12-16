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
1VOD3yRf0Fp6YIG6vXFGaWdzEPcau3BwlKqTKpKRaPiMyzNwyIj0qUQv+GEnSmc8uTmJL57yoWkWhoQGr96931eDu/ct3v+93fu+2MMl03nDvAF5v0qeA+GzIdCvvBSE2Dwzt4tyqhdSreowWcAVtmixdbZln0F107GIIi9ykgjRfSKgyGR5GwJ5y4iCBpHauIZ4M9RCKgEbxZ6tW5pG31e8f67qHW/qtlpgRfLzke8wllisltxavk2iXtv/OedDGhVuFIUrVeHjcQqcwI/4wcG/5H0L80PTHZP3PXOMxqzJ3zwsmr7Q4FK1nicPwh0+5ZAZaC4Vmcsgc5fKhKzg2jHo/6kFiKLQy8NUoVv5VDj2EGi91P8HdJe9VI0Cr5LDjvVwnmGvotpCHs1GrfG0nKek1TlYeq1TaRqBA7r0hVA6wJH5QOczhyjUlhXxkA7bQ1hNJgcaFjIc0wIi+tjZCtZpWAzsd2AdaDWUL3pKx2v95dIRHlnTdMleVddKrKneANVlpQOJj1HpJqzMTWtij7du2pMzdAda6bZSJaqpGrNVDY43dq5ZYQiKXkZXkjYsaCs9AJwUTQN7BrVv6JNaAplDIHUc9Kbt1Nkcp627vMF0ucXKRkMYlx5b4H+IDoIFsASew1o1WwohOyBzEsUOgIzr755cy/nk/Bz9yTtQ/k8lJY5u7YIOA/e+5TbEG/91GCwIOtXNqTXDMUxm0wNgxftkzhmYE/8QbboWJO48137TynkFuBvKV1x9P18V2GGOwV18PvpQKwxZsNMUp5MU0yvQTTC9gFab5MQC7bWZqH0Lj/4GfAtNQNW1xrcQLsNK/8n3eAzSRWcilhKT0HoE27nS0P37c+x03ygBvFeVF1R/cU4vVK8diwSszWeqVxEkvNfvD7DhyS/3v3wYsbaYlB2U0mhSbqaUBpMSp5SISVlGKfUmJYYpbCJDex5WS6Bp7uGz7c29TWXXYW0Ml6RrN7dj87WIeT5C+1mNAR3+Q1ec1Rlu+HueueWsDt1pdanfKfh13uKbNmF8pU/e6YmisLaIgA4JkIeLFEdxx9KqVw7rMn/P01ZEu9lwIMzmPqcWPQRHj1GNb6savIeVDKsXIEcF4VzvFa3kepFEYjpRc1MekJvTg9xPFlKB5XmS3ExkRfQq18BknZ7n0Nm8PsQSd79M5f4zoBfIMXF8fSRDflrVEJt74wqI3kd6g9RouqA+ceAoQbqxtxoRUnegxue4RgxqcHooUTWGLYdzB4hReDjX3qndo7ngoAGyV7V96aMNgmFr0U4Pm/3XMTOpbc8qiMlHpVjaWHmkW0XzqZB7Lrx8ChX+ikSPWd5K3HWNRWkg8FhFiQrU/AWcA6PbFlPFKmHLZE6Qw8bqXfd2zEAsF+Qy9IOTUEKWW2lfxhdYjFIF66iXxQb2oGJczptAsepem5s84tdKFoWo7Sf596yT/FObA8nvUXlv81D8zE4HHxx6R/HWB9VNLgg3jrAOalgfQlhXWWH9ZbCCda1fb+LXicvG2gJ8G4g/E+/HaACOEJdM8nPXDHgRkjQVz2sq/vhzhxZ9AKj4Z47l+6F3+YmAX+Uwr6+cqNcimlhO83vsLL4NxdSarmuVc8BOl/ILG15dB7dOl4kbIO8P8/yHnIvd54eYUR88TC0P5TCYx6oQ6QhG+k6JND/HUTiwdbGZO/I5Xy9d3yJiZ1/7J9V4MGMNmtLf5xprIVi+Q8XJF296RfWChrfobzhup4u5PmskT+GFPjHXnyAfkdfjIu9ox4t7aJCPh+WFv2LSVWnuBQ4EpU/PgHO8yC/f/Cnwy5VWfjknqPjlu94M4otF5+9eIuS3wknADSIuZMUIahSeEaeAhzo=
*/