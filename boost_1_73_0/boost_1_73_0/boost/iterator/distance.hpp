// Copyright (C) 2017 Michel Morin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ITERATOR_DISTANCE_HPP
#define BOOST_ITERATOR_DISTANCE_HPP

#include <boost/config.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>

namespace boost {
namespace iterators {

    namespace detail {
        template <typename SinglePassIterator>
        inline BOOST_CXX14_CONSTEXPR typename iterator_difference<SinglePassIterator>::type
        distance_impl(
            SinglePassIterator first
          , SinglePassIterator last
          , single_pass_traversal_tag
        )
        {
            typename iterator_difference<SinglePassIterator>::type n = 0;
            while (first != last) {
                ++first;
                ++n;
            }
            return n;
        }

        template <typename RandomAccessIterator>
        inline BOOST_CXX14_CONSTEXPR typename iterator_difference<RandomAccessIterator>::type
        distance_impl(
            RandomAccessIterator first
          , RandomAccessIterator last
          , random_access_traversal_tag
        )
        {
            return last - first;
        }
    }

    namespace distance_adl_barrier {
        template <typename SinglePassIterator>
        inline BOOST_CXX14_CONSTEXPR typename iterator_difference<SinglePassIterator>::type
        distance(SinglePassIterator first, SinglePassIterator last)
        {
            return detail::distance_impl(
                first, last, typename iterator_traversal<SinglePassIterator>::type()
            );
        }
    }

    using namespace distance_adl_barrier;

} // namespace iterators

using namespace iterators::distance_adl_barrier;

} // namespace boost

#endif

/* distance.hpp
uzDaqHhOEynDJfi4USZcH/zgA7HM3Sjax6HcgvOmdJfG6QY1KnAbCGIZHDzPJIwPt4vdaIcbO5w8RWKALae71yIWmcunwZyKR8dL4lW47geK0QN8oFHN54QJ1v4bk/owrEpTj510KfIixT7GOVHe3VomWZbcCb91dLSa26lCrEaeJE1uLV7spVl4C1VrXpp+4xiz2duxfslO3TMfRr3O3Fozk9fkTZDp28lZ9UfJD1GjbyfHU9OWYezM5tPLuX7D52MINM1avBmac37v91Xu1TSE6sIa1VA4xmI+dixbt01jbL5pgPRXoDQ8WhcxkjGYVGjduJ+FSntVWlDUb83xyOJcgCS8ypBdG1TK9tZ0MTdGrNdZe7+no9W5swykIEE96r0XcIpMM3ZKXagd6t0ZfbDnunXBG2eZuEX8EtS0SrllXBdcCtllEH/wvvhznbU0RckqvBnrk2tHtx3OfLZ5M+rscBp9mI1Nw7QdEDvD0cwqDzAe6sOh2nviFYPK1/uRSxfYdTOy9bEJ/izuQk2pA6hXTURS/N8sJ5ZVDy1rXA9/ZZWrsZI4Gdnvp3McdDJ0+JS1CqVNKyXqAGnKKacvSqKDMDprH3hMB6+Hu3bzbB7gWcRI65xSpcqoIuYuwe+qfIskS0iReejtsiry
*/