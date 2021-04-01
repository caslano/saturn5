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
vTR/8axfuPwKLkk1jjN1dIPTi8OYC/dvklTVvM03fF/ScjzNn/kBcODp62s2xbmjzK2yPB/RfiAwBu7qWhd3MsWCtkNjv0K7+e6D2Snhn4OPzju60uWIZaDvMbn1496dyqTwxag3jK2fB6+bvm45y1MeP3tMyKqTqYwbQQsvTZVRXrISGjYTpxukmNA+4KqTRzYmCE7r+w0qsrVmxWxSPNrBRXxHTN8bIl8T2GJQRRqv0WV7096PEM7Mp6NOtYced12KV3bh0jR/jh+PKPuzQ1TkJl8Dry9BJ7fM4NygI9Xzcgc06zohR+Tm6BFWmrlrGV2J6EdDyJVwQpb4MsRSoXvj7HfB4h+xF0xWnCXu7aQb0oXCyOv5/rAqBAcMMNIKgxdd86zfYBlwtiEcEmEQRBfgD4RRlPHN721OgDSfQgoqJPBBKyF7TYk2fk0be7ghE1pMfFQek73wmV/DyXo0dC/9qD/KNgyHmmixz5MAAo80IWLYDPLDrJ3ecao1SV0L1r1dXBIQIscuaXBENj1IOYs8SKmZnqx5sNvnr4lmVBQ5OKr+SsPu84/rxg==
*/