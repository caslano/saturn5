/*!
@file
Forward declares `boost::hana::make`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_MAKE_HPP
#define BOOST_HANA_FWD_CORE_MAKE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-core
    //! Create an object of the given tag with the given arguments.
    //!
    //! This function serves the same purpose as constructors in usual C++.
    //! However, instead of creating an object of a specific C++ type, it
    //! creates an object of a specific tag, regardless of the C++ type
    //! of that object.
    //!
    //! This function is actually a variable template, so `make<T>` can be
    //! passed around as a function object creating an object of tag `T`.
    //! Also, it uses tag-dispatching so this is how it should be customized
    //! for user-defined tags.
    //!
    //! Finally, the default implementation of `make` is equivalent to calling
    //! the constructor of the given tag with the corresponding arguments.
    //! In other words, by default,
    //! @code
    //!     make<T>(args...) == T(args...)
    //! @endcode
    //!
    //! Note that the arguments are perfectly forwarded and the form of
    //! construction which is used is exactly as documented, i.e. `T(args...)`.
    //! However, if `T(args...)` is not a valid expression, a compilation
    //! error is triggered. This default behavior is useful because it makes
    //! foreign C++ types that have no notion of tag constructible with `make`
    //! out-of-the-box, since their tag is exactly themselves.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/make.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename Tag>
    constexpr auto make = [](auto&& ...x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename Tag, typename = void>
    struct make_impl;

    template <typename Tag>
    struct make_t {
        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) const {
            return make_impl<Tag>::apply(static_cast<X&&>(x)...);
        }
    };

    template <typename Tag>
    constexpr make_t<Tag> make{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CORE_MAKE_HPP

/* make.hpp
dqRxetuEye3x5JYeoPqiJCzt098pBtnUc+09tYCXgKQyEFcXqFb8uJbunC/P1pjNrdjxWJKs+KYITx7FmK9hXAQnAuXZw/bkzp50LcqJKCXN8rlInNU9yYvBRrWo8otzlQrRBWFdqSaEuBzfuwnbVxgwtaSe2ZcvxurRZGnDipzCh9cjeST/fjTptv95KkIwf3Au44Eji+2frEdrRbn1ZFhKkQ3OZg1ggs+zoAiwTfAK/uk45AoMZbVv4j3G6A1kSeV6wNFkgAst7aKlj8/xkqAjy//l1EoWzMuPpOoAo2jNj6q1s6WIRIpCcfHkd07bY5bYULoE+hYCWBT4Lf4AsLbNWcoDnAJt5npFfRU8iO+FNmrMQ33u3mHseghLDCLyksoKHS+qm25EVX0fi3zCr7oOQ/lesqVab3H+s4r2Rr0uzQcL5TviRHtOISPCGin9YJvCWHLCpNG5rTlhrebOIGXoin9Aawb1Rkl0Msw9WX9HWRdgpDJ7EQoSP5mbLI5hCznwF0q6WYhh3YaC3prGaR0+vu4S0oOb4n1q5tL16oKleBA6LELz8DR+hDTGQ5EM5VB8o/gBWopwA9vLHHoU0D2/hhJwyeRfP3ydxyyCwy8FUfvNUV++xpg/PtxuH3Q/njjs7iTIPO8rYdlB
*/