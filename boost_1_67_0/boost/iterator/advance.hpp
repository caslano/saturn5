// Copyright (C) 2017 Michel Morin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ITERATOR_ADVANCE_HPP
#define BOOST_ITERATOR_ADVANCE_HPP

#include <boost/config.hpp>
#include <boost/iterator/iterator_categories.hpp>

namespace boost {
namespace iterators {

    namespace detail {
        template <typename InputIterator, typename Distance>
        inline BOOST_CXX14_CONSTEXPR void
        advance_impl(
            InputIterator& it
          , Distance n
          , incrementable_traversal_tag
        )
        {
            while (n > 0) {
                ++it;
                --n;
            }
        }

        template <typename BidirectionalIterator, typename Distance>
        inline BOOST_CXX14_CONSTEXPR void
        advance_impl(
            BidirectionalIterator& it
          , Distance n
          , bidirectional_traversal_tag
        )
        {
            if (n >= 0) {
                while (n > 0) {
                    ++it;
                    --n;
                }
            }
            else {
                while (n < 0) {
                    --it;
                    ++n;
                }
            }
        }

        template <typename RandomAccessIterator, typename Distance>
        inline BOOST_CXX14_CONSTEXPR void
        advance_impl(
            RandomAccessIterator& it
          , Distance n
          , random_access_traversal_tag
        )
        {
            it += n;
        }
    }

    namespace advance_adl_barrier {
        template <typename InputIterator, typename Distance>
        inline BOOST_CXX14_CONSTEXPR void
        advance(InputIterator& it, Distance n)
        {
            detail::advance_impl(
                it, n, typename iterator_traversal<InputIterator>::type()
            );
        }
    }

    using namespace advance_adl_barrier;

} // namespace iterators

using namespace iterators::advance_adl_barrier;

} // namespace boost

#endif

/* advance.hpp
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
*/