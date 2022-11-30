// Copyright (C) 2017 Michel Morin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ITERATOR_ADVANCE_HPP
#define BOOST_ITERATOR_ADVANCE_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
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

#if BOOST_WORKAROUND(BOOST_GCC_VERSION, >= 40600)
// type-limits warning issued below when n is an unsigned integral
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif

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

#if BOOST_WORKAROUND(BOOST_GCC_VERSION, >= 40600)
#pragma GCC diagnostic pop
#endif

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