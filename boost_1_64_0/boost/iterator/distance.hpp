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
kwupGoe6p8DsaKqRFI0c+2epQ1EjNeZqAxSsb6LLM8EOHqAM2VaffQA89jdtWrusTcLys4M0s4cceyjZ0HeBmWeMh6HxvQtNYnGoMbBJ3FRU7ZayTNGMKoKpJPakUzuLLdGuU5DP/obs4y0H6aKSfOqcpfCvz2J46+h3wQKXwp8kIMUtx+CbDSCZku9Uz3b/0WBMuVt3/cgpiQ9EGPJQH2o5hpNq0wYRAcmzj4l1bbW9OOvdwJYh5ri38NmOS2Adm3So6ZRqVx+QzeTJVJTqxDViS1X/Tr7JC+4bY/vmg5MJlVlh0DXnH3pDCNEpnfbDge62I1W8loUgcmPmQ0cRVhbXXWrF6Sz0IHDRsS6DITy3pZU2ZbKrphnSa8c9EG2mMLj699f361MitCleJMq5M5tQ7NqxAOpExCR3gKKlKVe2guMgMivI+hJZG8tLL2fwDO+UcSLlGMxSlxt4PxzFWk95GBJKqio6mDhLP57MK9bMUQW/SLShouT8C2W5+XQdKB/O4XtrFKjrHIPb7U6Efrx9BO4bGZ+azzcTJZfny8bcTid0tifmySamOg==
*/