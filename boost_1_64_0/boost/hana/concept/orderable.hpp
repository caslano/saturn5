/*!
@file
Defines `boost::hana::Orderable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_ORDERABLE_HPP
#define BOOST_HANA_CONCEPT_ORDERABLE_HPP

#include <boost/hana/fwd/concept/orderable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename Ord>
    struct Orderable
        : hana::integral_constant<bool,
            !is_default<less_impl<typename tag_of<Ord>::type,
                                  typename tag_of<Ord>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_ORDERABLE_HPP

/* orderable.hpp
MgPMieI6DMkzQ5kvrChZt4KP5ygLghUiq+L55peyMJgp3e+0W6s7ysJheSjurf9+ySFSixvcKuy1sihYeYozb7N4qrKTWtze42VXS820uK2bzjZQZoIJtyLrOHvuV6kLrAxZu9Vm95QFwPzIvsZ8sJHcYervN2Y/58VP15QlwEpT3JBLa6orewcLoLgGOReuUOY3Gb8nTnFdP3fLpywYxn1oYuX6U2oNcyebWXL9JmUxWtyYiAmJ8pywImQHPft0V5YG8+SaOS1doMxyivHseoUP8ZRZ0mx84OmPygJhpTkuzGG95AArRvbPrl8yS3EwD5759ZvmSd9hPmQHBg64KbWG5SZL2u9XU2biH/zdL7L6/+Z5o8wflo+s8paA+8oaw8xoBv8z6ehd2RXNtlhUS1EWAutCfc9MafuXskSYP92v1LMjPZRlatZ2fpORMi/YjFN0zSmGTp4SB6tJca9ffZE++Eca55fUu259yQHmTRZZ8PRY6RGsEPehQ4kt/7OypWNg6lyyNhk49N235f2UJcBcyU7nLNZbWQrMmuzJiQPPlaXDHMgsRtZyVmaCr4f8ZBUP265V5gSzJIvtvnKXMg8YP8v1t183KqsGU+dnloW9rF9AWSDMi+J2nqnYVll/mAXFhS5uV1pZOKwQxc3t9fCs1Ex7zq3HRyYpi9XiBo6f7qYsEZabLKf5qjHKkmGlyLZ8fGotNZuOc5DrMtbKQ5kB5kk2InZGsDJ/LW6y6dJ9UhcY1zMzY+diZaEwZ7Ijv4eMUxYJsyX763fcN6kLjPOLTRzmpywOZkPW/YZDa5kzGM/L44PNV0hdtLjolbaHlKXB7Mj2TrTuoCwTVoLM+3lEsjLfGTizuH/fq9soC4YVJPNcscdMZgLmQfYoJOyA/HwMpuqSO+vPPD+5n6YsTrOj6/PsUZYAsyZb0OjcamUnZ8h8ZlvKilf9lSXD7CnOqtj5VGXpMB+ywaN6mykzzMQ+kGUUv5NXmT+sIFmfSn/+HGcwzJWsQdGPX5WFa9cccM/ipbJYmBXZyqIl1iuLhzmQNQs+3Udyh5lT7u658g1VdkGzLpWt+iq7rlnkxLl/K0uDudH9WnQ/M0OZySzMC9nVQ40Nyvxg/yG78vhTZ2VhmkU4zlos+Wk2znG25P4ONijbgrLtfbuiUrOQ2cb9u+7SZIWySJgH2fR6I+XX6HEwtX9ZA92gYsE6yhJgeciS/lrnoyxptsxZth1uXPSdsmSYDcX9M3rUDWVpMCuywKDvjZS9g9mSnbl9vZsykzmYebJaw9KslRlg3mRTZjedp8xfi0sZuuqVskAtbs7ImFzKwmD5ycyHXRSL1K7p1XFrmLIYmB/Z0t8mkl+SFpec7PJDWQrMh2zAvIkZknuUcR+ePHB+L7nD8pKVP7qomTIPmB1Zzl0ji0ldYAayuv2/TJS6wAqRzWw5paiyUJjv/y3rmTyGVCiuLArmRua9eXGUsvgonBNk9xc8vCDzAvMhG5n6oICyTFgpsosvitxU5jsX5wvZk5UbSkkOMBsyi655OyoLhhUj6zgkx07pLcyS7IFtQILkB/Mn+88ln6bSW5g72ZaGEyooS4eVI5uZWmyq9AiTaiDL7VxvuDI/GOdQ9eF46V8AzJusX3pzg/QI5kEWNCrpsOQHsyYzn7dupLIF8+SbNtvmdN395+/VaXHtLZfaKYuDcX7OwzbZyL5rcatNlt+VfdfirLynSc185+M6ZE72T6TWgTCepX9jFkVI7rDiZIX77HaTHGA8Z/eanLquLBHGff+0fo/sWBKM6+JewldySIblo7gNtVICpO8w7pHJhYW/ZG8XGNdlwIIpfWQmYIXJtvXOKKmsLsycnmU=
*/