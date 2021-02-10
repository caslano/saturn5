/*!
@file
Defines `boost::hana::fuse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUSE_HPP
#define BOOST_HANA_FUSE_HPP

#include <boost/hana/fwd/fuse.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F>
        struct fused {
            F f;
            template <typename Xs>
            constexpr decltype(auto) operator()(Xs&& xs) const&
            { return hana::unpack(static_cast<Xs&&>(xs), f); }

            template <typename Xs>
            constexpr decltype(auto) operator()(Xs&& xs) &
            { return hana::unpack(static_cast<Xs&&>(xs), f); }

            template <typename Xs>
            constexpr decltype(auto) operator()(Xs&& xs) &&
            { return hana::unpack(static_cast<Xs&&>(xs), static_cast<F&&>(f)); }
        };
    }

    //! @cond
    template <typename F>
    constexpr auto fuse_t::operator()(F&& f) const {
        return detail::fused<typename detail::decay<F>::type>{static_cast<F&&>(f)};
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUSE_HPP

/* fuse.hpp
xVX7lVa+pnihk9+m6I70hDLMa5cgF5Ruzx9e9XGzfbXqmx6M7KLZlx1Zy7J50e/ud/td0NNoOcBpcsJ3dTd4W0IONlSOYZzM9MLUc1TeihBiJTbD9kW7NWqfVeKi8MALrEXO9xXoH/90bycj/3pjmhU24py2jlztt71Rp1nVffcP9i72DbMGydt3o1H/SEprbktBPPxC4CVjwjtn/kW7C4tEah1P5uF8PF/Uqj4XnL8KWt1SrWHhxeENrkS+vvKxoU4joKW9UO0Mglr440xx20P4D7p5O3rnwNv6TCDravoYJKGViSaJRSpxAtPEoYrG6UNDco7X+0ulfnd61T0DZr68uhh1+hftv3qv5CNYUPT0SpmLv1SXzvhOlc74zqmdtoL4HP0w4dc0X7tbiBoRNL6NNFNPKac7Y7Onr9hzjL5J0MPaEhoPnTrG+mexRXCQIGVU5i/od/5gy9Q80zu+viM8Yb6SPEL/zfbnPIzxhpE+t/EvRh3rLcLASW4SBmrKc9V4Vi+GohZUDzPE3ujHHp0JcG+s32H3atyr58wqFfBYxNDzNg3RqKp8XCbJfXyTBhhLkufAVRlftXAS7CMufMX+N0RXjwkL+g92I5NlH9NnFNy25w1hQ1gZsJPdJvc+VlwZ30R/iSavf3h5
*/