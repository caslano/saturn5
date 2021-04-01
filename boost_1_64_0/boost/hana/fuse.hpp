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
Q2c9UzEU0iA7AQoRF8biAoc1SOelSCzo1tQwzvxFlaEHD3S1Y9OfXETYcX9OuX0xXp3TXsB3lX0we1Dv/mQvAHDRzgpdlLgvyhRcpATmxeYZj5fl0lXhAOrB8F2K3mnfWMBCXjofCmoQhNJa6B8IwdqpOP21bzD8CEwqnJbywNnyHJm1MStowPVO5j6xiMoOC6nVlgLcrvBUUUb+qG2EouOJ5B07D22cqpLg/Naxk9LeNgRi+nERbBvGBeJcwUJFRRyp8Slrw8M1UOZ0/4W9stzuujMxpDjNYIrEgCuw6HpHcyzVkvGWOwiPvnfi5LWKrbn8CW6UvMuax2GDSNWthaB4HV7OrjkNfFr/D7DwpEGcRSPvLhDUr4Xm0Tl9DKlYErqulGgaA5i/6BvTv4Xpgf6fwLD7DwURF6fkolXWbKmuVcKUEq7MACnJsAo4vdES9MpPq/2yVe6Qe9USL3vzkh60AW6RyxC6GxyOr4kQLjWAtEzC3MtDrWwAURrJIdyku/SDFccDy+e4ASoK5Fns3aAQmlRVcntyswoKY8WxUKX67njF+FqRH4TDlg==
*/