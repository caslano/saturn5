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
USSfN5fX0ZOZ5W7deNyQqdJW6soflCC9pmc3vxelnNndclrvJ7n+eIq1OfFaYbj5FWv+iK7Bgvr9LmIq4lkn8adSrDqx31tvtDbJE5OJj7Di45srU7qax8GcKvoNE2oDzHF0uc3B1y6bIYIrBgjoLrCZMxmXiys/dR60Cz1VjM3RZlbcYNGeKLc1FEensqczK1RaOce6hFNC+MVyD+Kz1ch6xIN6slZnoZ6FtKb10yEja0cq
*/