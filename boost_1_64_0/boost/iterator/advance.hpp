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
nMOc89VDSfjnEKED7rTSFBAPCpe2jg3PeBXOZQ2zeg8U+MCVDXuTZS3gI8TLTB5LVf5fWF4zKIgNDJGzWoOGxRQvjq94oz1KnfwiDzYrswwRKLOvMh/ja0OtPx5yRJusVOFLhkjFf3Cda2eeQVwspM2VMRkoFUpsEfWqjSO0tG09s7pRd+DAr0fugsPGPB++5wzpJjvBkkTYr2VTv6/Z6RTH1WYUAazFycbnU/qyBI58siomr6EurpyMgawadmYfvguNOVQpj7DHVMZNBeEsQE9Gta04N0A8Nrwd1N5lU4ShmuBh2BNVQs0r4rIBuuKnv8RBHSptDP3ijytIKgaDZCgqzvjd38ceGYwjenzI5EvQKTB435LkA9HS7Oh3x8u7SESi6qKt1agC6keytuziRhCHzA2ad4lxuKquTyfzzUiXbvoO0LmL37tMk0HndG+KRW1vXiAuoe0PjkG3QtaYmhVzjz7jfApvP7ZPbsHo5yBvhAvHpymGpEsh7ZDpVFJ2rqkZJrmPsO24HyE9DpAfvIC3jyIPaK8EcMUJBEn92itBRR7oBcwtim/8oQ==
*/