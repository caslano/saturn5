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
jZij2Ev3ArQ44jYjY1x9Z5mTz5c4hNLuHundctZFUAfZLzK/OpWj3OUdPNRtvXvlvhCnioO+usuF0r/9icqr0D1lDysoZdzSKBT+LvJ3Hw6D7UhdwMMraWMM8rLNsKvFGwEa+RXQ1Ab7JjnlwYyv/013dXUCaBprZD0zOoriE1bsA0sbkLpX5MWZvIu64XMUuDcikszAfl+FPNbqKoZ3vprG0HGahdJrUiYXYqa/xCXWR8MHDlUWhP3ZwqZxqPcFDzj9izDEbhKoRjP6qX8z01U10qt4NhbayQcslEgC1+yBqJ1qyzeydlcEf++FuF/hFdvqJ42R3tmJjLiE66cOGxwZ/JwXTIEUeBSONHo2v0mRc81/o7U0Qa90uZ8X2FpY1RrhlTSyaHIJ6XwSB2k5OIkOQwg8lZda+5+0cenOC4dzRbbwX5Ojca+DxqAKMmlJGq3SL2yY8sO20xSncOdg8cV/4ht8KfqO/2B222sBHQ5pDZ6hjuonFOBXsJ0aLdkQuSmczSRq/sg1EmHEuCq8keR0z1TVmBoEjATJ072JYn8k2sB8HpDHCXRVHmXnerXYTFbEHOX2zUgyq6RQy5q8uGSTk4xgHAs3BbUsWctxC4mo3K4RtwOw+5sbxMS2kAplrgTEY9w8JzWq0l8mtqdOhOn3IzdW5Kdb5M67O5gpYj78PcQBhIjEbylymlTIVtt3TeW1Ul9b2cEqKp8f
*/