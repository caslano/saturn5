/*!
@file
Forward declares `boost::hana::difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DIFFERENCE_HPP
#define BOOST_HANA_FWD_DIFFERENCE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct difference_impl : difference_impl<S, when<true>> { };
    //! @endcond

    struct difference_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr difference_t difference{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DIFFERENCE_HPP

/* difference.hpp
Nu8RIRhq9AulJgsJIiX2RCTQ9Mr0hmxu9tFKtk1qM+e/JmPMT4XI1+zcNSLNUnJL2GjBv0M2cJSFKPbfJvybj8pJa28jCnnTHemD29c/1CeiNxL77g28JlzZQdZSAZJj0ah22vy7+VOtCo8XW8wHIZc1vbZopeD/DE9ygdqpb0rHvxD4zVimAmEcn1o39Jk9ble3aq+BwrUsOCoqmp73N0Tg0fT4/KAMaO+V2xQ7E3AXxW5q
*/