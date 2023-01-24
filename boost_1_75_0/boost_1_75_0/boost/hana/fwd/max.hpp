/*!
@file
Forward declares `boost::hana::max`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MAX_HPP
#define BOOST_HANA_FWD_MAX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the greatest of its arguments according to the `less` ordering.
    //! @ingroup group-Orderable
    //!
    //!
    //! @todo Can't specify the signature here either. See `min` for details.
    //!
    //! Example
    //! -------
    //! @include example/max.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto max = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct max_impl : max_impl<T, U, when<true>> { };

    struct max_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr max_t max{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MAX_HPP

/* max.hpp
LbZIeGBIZfHRdAhAc9uE77HmcuO4560gaSYF8Neq4SHUaXt62v0c+4XtQJsn7zX/BIT+/e3XfdRHLbNPNv8wkrnGNQh71tri2fLcSmMICmb8QvKFbwbLBLUStRrdDL2T0oDARD7QlchVY8f1TxBRLXIrRSv6IUp7KK2s9aBkEn/82vdhfhmRUNde359kh6hPunTdjhtcZQjEUr0AbykwAl/+RqyuW0fmPko6ySBkaSTx/IesVrhmD/gwLioqedugsSvDPKjOwTxT/27QWhokKuQ5jumGf8+IGQZqDXm/AlYZGojSVhSbLaJT9j0ssGGpvl8nv4DsbDv0CFDjDcq3SycRy9FRx8jeOtSXiG3mU8rIviXJBt6SlMO/mFyoDv39IHYBkb+LSEZ9+w+KBNnfpWLHZfac5Bi3I4kgjhHHbv37Xk1cZo76kJmo8sTqDo0T7I8f2ldqPlCrM0xi9gQzpMYQ0wYVONTQajqRoql5n1yhCV7gyz5rFwQHAQWTbobiFVHVNUYPTIN9LhKG/i5mHeLeyw+2wr9YfXpHSUiETiOS8oGw68N8BSxy6vIs8JeVx+wx3kei6ZCngpp8xJw1Z876L/n+1zK/aGOpuBzhXIXIFObNegn+dcIfBJHfpMjX6JQiU2Os0tuJguaUvk+eubnLB/RC5yDLu1c3vE9UpmLsk8Hz2S+qS49B4Lu7fd97OzJMRxJ3lqxY2cfK
*/