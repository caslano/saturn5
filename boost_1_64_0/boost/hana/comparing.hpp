/*!
@file
Defines `boost::hana::comparing`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_COMPARING_HPP
#define BOOST_HANA_COMPARING_HPP

#include <boost/hana/fwd/comparing.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F>
        struct equal_by {
            F f;

            template <typename X, typename Y>
            constexpr auto operator()(X&& x, Y&& y) const&
            { return hana::equal(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }

            template <typename X, typename Y>
            constexpr auto operator()(X&& x, Y&& y) &
            { return hana::equal(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }
        };
    }

    //! @cond
    template <typename F>
    constexpr auto comparing_t::operator()(F&& f) const {
        return detail::equal_by<typename detail::decay<F>::type>{static_cast<F&&>(f)};
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_COMPARING_HPP

/* comparing.hpp
iDrRducOD+cKlOLnafPY/DUm+53TR9NyuuGGp+m98oiUoFWROO2mdPE0BA4g9AuY7P7p42U27wSEjgRMwZuOaCcRrur61BybUeXQmI7bTos82B3LbNfPyerDXOGFciNqrfFsWfZiTmxBDRwAeaDlPjTMvhRRauVuS74to+ObjR3fImO7m/IVGtxuuk1BYKIEAwjeWISNVO7qe8r8UWgAuEix34/KUHlYRE9jMeTqFA/XwwtXAQR6V9QUZBj8y0l2W2kiHtye9OvTBwwjMv9MQCy8lWm3yAh8Xw1c80s0qiWEDLv/ybR4nw3I55ri3texmRERan84P1jKsEnPXBGqFVI3bkiMckfruO9nsgzSHVDeiZAPo7anbhKtR8n/jWsuz+27LyXlDnxxcMj+f9BvXpbtXx21bKGl0q4RQAN5JWztnE2Ej30J42TNk2DkUkj4u6gioKtQYinNX1cNRSRVAz62xy/kutC62FyzK+RPDOzyr0IbP/7ljSRsCHZGeutdiO918D6GpQuJ0VPzz7x5P/1qekW2n8qeQM46BUnyG1v9W3s+TWh4cYPvNg==
*/