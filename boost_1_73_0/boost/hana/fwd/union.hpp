/*!
@file
Forward declares `boost::hana::union_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_UNION_HPP
#define BOOST_HANA_FWD_UNION_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename T, typename = void>
    struct union_impl : union_impl<T, when<true>> { };
    //! @endcond

    struct union_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr union_t union_{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_UNION_HPP

/* union.hpp
jEbNeCSXuMJAfGCVn8gMfIvWDy2IDKC33kZDQYiabujnLn1XZzfcDY/U25c26wToZBS2bYkuv42Pmhlr4K70XckLrCeYut4plPNyNMA5tJ7nhWiyTZkVBW6vsScIZ/ejronfAT/X9J6tHvfU/luts5bPNf04gsIdnnu26ZQFV2osNYha1WtFhdNqUf+Cro3sT6pzpqcxZ6E04AbTAEpS4I7d0wDEeLxCtm2vthFI3VbTMQA0
*/