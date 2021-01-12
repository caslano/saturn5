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
hZqz3Dc8nGUZzsoNZ7+els6ZnteOUWpKjEPOxmTVBPf054cYr4dN92ogy6tFA+kNUQNZPc2xZx8u5z8AN3fUS3e6d0gmItytwx9AuF3rKQU7XXua4xFeo8MjEV6uw0MRXqBxgwhfq/WR15BXidZT/oBwoY5/FuF8bTv/NMIQCsNdCEPZmAPHh/rPO9Zm/klLHf/pUbo/NdePmVI7Y+gt2v8Zay7HtxFxFmDldf2oUr3rTrIs
*/