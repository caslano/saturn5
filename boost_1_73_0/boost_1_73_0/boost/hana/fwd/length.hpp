/*!
@file
Forward declares `boost::hana::length`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LENGTH_HPP
#define BOOST_HANA_FWD_LENGTH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the number of elements in a foldable structure.
    //! @ingroup group-Foldable
    //!
    //! Given a `Foldable` `xs`, `length(xs)` must return an object of an
    //! unsigned integral type, or an `IntegralConstant` holding such an
    //! object, which represents the number of elements in the structure.
    //!
    //! @note
    //! Since only compile-time `Foldable`s are supported in the library
    //! right now, `length` must always return an `IntegralConstant`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/length.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto length = [](auto const& xs) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct length_impl : length_impl<T, when<true>> { };

    struct length_t {
        template <typename Xs>
        constexpr auto operator()(Xs const& xs) const;
    };

    constexpr length_t length{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LENGTH_HPP

/* length.hpp
yxhMW1Un8Wi2OP/o344oYWEx2PeSW+A9HUhDG8xAJUHsV+dy6J374ZKJDNTj4mqLeJHOFmnGbJkR9EpPHpv743g+0asv+dRT8dHX+/sYopU/ZDvWUtzmEka8gr3G0CBtJknYpJahRUV76go8ANolVyP1tMqkUmQSsvsSdqacsoBeQAxVL2TdClw/TJ7B/w9RxQ3BTjAaj+5KeftHuGpyBpVqCTuX2oDyWoTiH0sxzT4WZpeK8hOGDqlJloiNkX/IHuIpN7SvXq4jqC1JRsw+0nnlUIutAKUi1Y28F6qyoLmzWJjmuYN59QJBs8vXLB+OQ9bovissYC2YfWRTAX9zM2a2rZGA+OjnGU5MID1ypxjhcHVtJrDEg61rXPB0jXZO5bDEdTY4cXvyICIL+1q1qmqIhriuwQD8JEPPWqFtbe0IzIx/QLsCCvsBrgExeKYW+OPY+lyf4iIRajQy78U452hHT+qpTkIT17w40bm4ktaCZ0spV7ABp4NDwUGL+B5l7mG4oLOcamwW/CgjQ4ml0pRBZuSXRoULCwrBuTbnQVYzcBUbTYB5baz9tg1V9uTOoKmpoOMYvKtgHOhlPlggPz7lMQC9qEY1aJlk2ZDdElHXUp4X7VUb8+3GzKPD3JqLB49rfV2ihNpZqBu+
*/