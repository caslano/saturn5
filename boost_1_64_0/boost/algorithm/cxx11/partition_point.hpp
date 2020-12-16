/* 
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  partition_point.hpp
/// \brief Find the partition point in a sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_PARTITION_POINT_HPP
#define BOOST_ALGORITHM_PARTITION_POINT_HPP

#include <iterator>    // for std::distance, advance

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn partition_point ( ForwardIterator first, ForwardIterator last, Predicate p )
/// \brief Given a partitioned range, returns the partition point, i.e, the first element 
///     that does not satisfy p
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param p        The predicate to test the values with
/// \note           This function is part of the C++2011 standard library.
template <typename ForwardIterator, typename Predicate>
ForwardIterator partition_point ( ForwardIterator first, ForwardIterator last, Predicate p )
{
    std::size_t dist = std::distance ( first, last );
    while ( first != last ) {
        std::size_t d2 = dist / 2;
        ForwardIterator ret_val = first;
        std::advance (ret_val, d2);
        if (p (*ret_val)) {
            first = ++ret_val;
            dist -= d2 + 1;
            }
        else {
            last = ret_val;
            dist = d2;
            }
        }
    return first;
}

/// \fn partition_point ( Range &r, Predicate p )
/// \brief Given a partitioned range, returns the partition point
/// 
/// \param r        The input range
/// \param p        The predicate to test the values with
///
template <typename Range, typename Predicate>
typename boost::range_iterator<Range>::type partition_point ( Range &r, Predicate p )
{
    return boost::algorithm::partition_point (boost::begin(r), boost::end(r), p);
}


}}

#endif  // BOOST_ALGORITHM_PARTITION_POINT_HPP

/* partition_point.hpp
fddeSTU8tFrUcBGA6zoUV62oa1++GZRw+Euc9tfFTQjusjTmE7xU/IN5pm12MFMq65ynItr7JmfZH1SwATq1YJkYtZ3+YUiPswdSi0QienV2WmGaGK/QXYYA3WXoJe4yUP29uf5kqbJND6P2vIIfcOSB2wM08jGvQKmS89FMq9ty2Cl/WZfgKgi6LfWOjM9oO0T6jzeS4bFfKj+IXrJgc/AeB6N+ESJ5nQc3bcAl3wNExVm6HwDlGJQLQJAFkGzoFAtPnxtx1yI7hF8PZ+nnMy8ARswcNZzueLk1nMzgQDQOJL49ATcs1DnfYVFDWnrtJiRAA/bR8X+HieZ/9MeQ/3aFy3+ZJP9dGyn/mSPkv+2tyX+Z0eW/7OFC/lt4gvIf7UereD/6vy//hevnl3/AfQ7LuIR9eKIdfaPyKt/r2ILDw2rQrhz8CWW6bp9Z8IG+I4Y16jnKJx8zD0yibWd7sCsaJrDxC0DgwmBQKl6vsvkFrizQ5UXly2W0a8XNomTqBWRocGwn76IlVt4JsMm04hTUo7exYCOxCTCmNCtfpPJ7xDlH5avJJiV5vsEub5ZWcXXE6x0yXbNDR+g+MccoL39OkHgi7NwymWsMBloO4YNkHNHeOODwh7dJe3u/+EQBPkGxstFhN9ZRcWABFBg5Ru3XNZA8Nfve19/n0XLIZlhPZcTYSlmXjYMdHARaWanzKC0kWOQKHfy7vQT7Zc/FEK8y+vFJIW3orNSl3akIqbizcDQzdq52OHNl6HBGAJtp6aZb8Nr7aWS1HGYWgMLM/7Xy7ZqW5xnGT27sGwnnfime9vhyGpBO42OK0kusphOyEKCfEzj/2a7TM3WLfDoamI0bJYXn0a/Ti4+aC407RQ70St1tfCx2906iFn8dbmQmKLdqL1fLUoob7vzxLAX2pkB5fDlYE/gN6QMkeX2+7xqzbswpFQcsgaMx4SZqloxqCB391O17HVn+PAoJvlG24HI+XXoI7O0sJZ7M9elmPzSMVbl25nt4LHalJwcj89Vce7DZ/e9t3D+UjT4qHmc3exK4Cx5ZQpMDpyl8zricJsdGRrD2D6GD02bnn9t0e5EJ+RH2IqjFRcujL/mPEBeUx59sUImvx/UHIEkRj7Vkid7s/HNr6DzrslUtnP+G5V/+fAvnv2H5619p4fw3LP/gE83znWH5y8ADm7U/LP/Lv4XnyzEQS7bMTzLRrg3TCNrRGlrvEJlTny/9eieZ9PP4+p8+j0d9s365+rT212jUkLxskFi1h2FV6YSWIOmJQcI+DqOorHqTk+4XSc9Q0gsiaYpIeoqS/iKSxiBJWbEQz1Vxg/GMn5Oe4tr4bzHsHRJo/YVh2pQnuQ+q8wryUuQA8ZNO2HnEcf3EWNxyIE/nLRf0OGHeotk/Nf+e5SS+t+qiE/4ej+eLT0SMpwnDOfaUxpPrG/bL1afR/3uiP5L77oZplOkdYXzWkfwGIwFL6nUb2R7sb+LtCryVm09otDX7h81cf6uLw7jurXUo+Blr9J9DDZH3RTNHBg9J6czYguKVL8AqF7zKVrP6XUZpqVDad+KbZrf4XFDa5yYrY1aFrr5yYcRPLK5O9g5IdxX0xypAVg+D0tDbZpSnKE6rzidEPvgLh0BIY8WS3D/FOyAFhkHeAXZAW2lm/UYqv0hw1+qXIN0UzmN4XotRYyKBXCWhUQyyiECuZpB4wvdS2lkfeK5BrbhFOwO4TGhnZgDQN/A5nAF8pLxQHoG5fkOX3k51oTkB+1NeWM7apC8Fkwak0O67Uf4W5tAXYgEYHEuiCzcm7jpkusRljkhLYxTtS0U9aSjTh8oUiTLdRJnCTVL5rWEW1E+8TIop10Ll87mGVqE=
*/