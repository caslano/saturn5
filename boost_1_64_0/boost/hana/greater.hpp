/*!
@file
Defines `boost::hana::greater`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_GREATER_HPP
#define BOOST_HANA_GREATER_HPP

#include <boost/hana/fwd/greater.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/concepts.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) greater_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Greater = BOOST_HANA_DISPATCH_IF(decltype(greater_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::greater(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::greater(x, y) requires 'y' to be Orderable");
    #endif

        return Greater::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond
    template <typename T, typename U, bool condition>
    struct greater_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::less(static_cast<Y&&>(y),
                              static_cast<X&&>(x));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct greater_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::greater(hana::to<C>(static_cast<X&&>(x)),
                                 hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_GREATER_HPP

/* greater.hpp
umcP3a4Iyw3EM0C1voKq8UeA8OCstA1v6l2Ngfw/UFfDVpE3KpDdWhfPonwHC5yenT5XPCo87T+4VmpkG7Gtaz065lgg/WyTLeaekxkrFGXN5PTTMX9fFjMQGNUVfM6Q+AZAEjPwhK/yd3XrUcOIxfDDnJjOzxHr9cjZRLipH+qfiTmyTkP3usY9gpmhchMXQBYPcZd31Kc+LmbYMaWGeJ8LNidFC5tWF7XF5MnLNqBTUXbp58FD7PGWaw0acG7h5T8cRUc/mRULgzFywSZjvH7JQfcz0VbrCOV7c5Ml8ZXGPu/fvynoYwvW6DB5hEYBBUWWeFgsDHyg4ppdcImPkWYfGLQN3itghicEsrJCmJ3GV6htkQ6PqxbeBu89qvIj58//B5MhkQ0x2ew6f14jIM24RZcwuXjAq8bqKFfj1lWXBoBK/vGaXACUwrgL7nGU4aUKdx1559x6zQ0uqysW5SJC+OJHTH5+MuBdJSS9zsvnWacxwSIXouNoDUT7d+VUO8KmVuQ1x7S6jCEQL0L7+RuwMoqiw5y3ghKhij2J222PTuuIaW4nVVTKlw==
*/