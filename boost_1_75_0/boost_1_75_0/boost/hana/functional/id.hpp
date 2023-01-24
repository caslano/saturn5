/*!
@file
Defines `boost::hana::id`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ID_HPP
#define BOOST_HANA_FUNCTIONAL_ID_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! The identity function -- returns its argument unchanged.
    //!
    //! ### Example
    //! @include example/functional/id.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto id = [](auto&& x) -> decltype(auto) {
        return forwarded(x);
    };
#else
    struct id_t {
        template <typename T>
        constexpr T operator()(T&& t) const {
            return static_cast<T&&>(t);
        }
    };

    constexpr id_t id{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ID_HPP

/* id.hpp
VjUt8x/Pg8wSMM8Oxa/bcDpmYpZ/vAgBsLYO1wcKYMAjHZxMdDWkLsRRAkcfCM5smsjk4FjyNjQS/f86u/hovDTvbHLxwOvqhWS054/DP0xURbHBai7edZZ04/k0+PnMmY0HnykiEcwIIFx5UXBK/+yYXW55CxDwFLNgH+v2mj/heiy4AcXGAnNnFal5GWCE8f/z2G4cq8TYRTp1ICJ3OPvYgsP09VKeJXxkvTFUr4U3/ZG7MTzAEaRUYH7vO3R/OeJ0sRTsgxZmK0mFqFcbfkN1/IrxvVvE5BcbAQGfNVLQUNwP2N4NoVXfGTZ9TTvZ33XTJQyg39SE8fV8GHms250IbZQVgMPUHZEwXdVJAwm83akz+aYSCwqF0LRBE57gwUQuguRgOrmr0cFMXszy+rwf34gV31fs2BdEV8L8fSQOfvXtdFpkqA6QJgoigCH2IQpSqPbp18N/H9R7tu91mFvk/s+iFXtcOlarC8iABd3mmpQViqgTFUfQWVXxiD3Fjj1Be0IkzqWFFLJyVkLEEgIICB86vwGqSy6CQf7YXr/ppNDQigaHUiWh/Yx0D8DaeWxwfejkM5FNZcSwxAnKZPaoRUQ2RXIAKr5vOonKxZFNeP8HOP2lHJAF5htCZgOM/Px59UsHX/ZotYed5ncBUNyss9Uap8JPZGGmlGuWcg21uRYNrJ5rc22VQA/+zkPdcji6fojcf7HQ0ujl
*/