/*!
@file
Defines arithmetic operators.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ARITHMETIC_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ARITHMETIC_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/div.hpp>
#include <boost/hana/fwd/minus.hpp>
#include <boost/hana/fwd/mod.hpp>
#include <boost/hana/fwd/mult.hpp>
#include <boost/hana/fwd/negate.hpp>
#include <boost/hana/fwd/plus.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct arithmetic_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::arithmetic_operators<typename hana::tag_of<X>::type>::value ||
            detail::arithmetic_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator+(X&& x, Y&& y)
        { return hana::plus(static_cast<X&&>(x), static_cast<Y&&>(y)); }


        template <typename X, typename Y, typename = typename std::enable_if<
            detail::arithmetic_operators<typename hana::tag_of<X>::type>::value ||
            detail::arithmetic_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator-(X&& x, Y&& y)
        { return hana::minus(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename = typename std::enable_if<
            detail::arithmetic_operators<typename hana::tag_of<X>::type>::value
        >::type>
        constexpr auto operator-(X&& x)
        { return hana::negate(static_cast<X&&>(x)); }


        template <typename X, typename Y, typename = typename std::enable_if<
            detail::arithmetic_operators<typename hana::tag_of<X>::type>::value ||
            detail::arithmetic_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator*(X&& x, Y&& y)
        { return hana::mult(static_cast<X&&>(x), static_cast<Y&&>(y)); }


        template <typename X, typename Y, typename = typename std::enable_if<
            detail::arithmetic_operators<typename hana::tag_of<X>::type>::value ||
            detail::arithmetic_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator/(X&& x, Y&& y)
        { return hana::div(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::arithmetic_operators<typename hana::tag_of<X>::type>::value ||
            detail::arithmetic_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator%(X&& x, Y&& y)
        { return hana::mod(static_cast<X&&>(x), static_cast<Y&&>(y)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_ARITHMETIC_HPP

/* arithmetic.hpp
z1+o+mORSyPW/GMCvG9xYM8R9k2KMopylwZ44dLAW0jL2Odd9Tt4N5O0djR0yLuZ2uf+ysC6Uqb0a+Vq/a5waeraqJd2ejJ04SlaR5aUu9LdFxTlXmPr0l13Ju9i+nCm3qWrFvsJrysTb+Ots/Xqbu5qwqXL7ky2owHtLvVl5jqi1JV1ZvzdR6kvs9YyxnE1+Ie6g4ko12bHqrf/jnPvCkxzLjm+30P9+SL+l/KmdVp3jhH7ccejBZ7m0Z9cnfh1G52Sftqv26fFWjF6GPnZZxVuKb/Q3YfPi/NZj1hXpJ85fab8gqSv0yj6XxI8mLiBtiuIvizwdpUn9wfq8Um8r4g1brzE4so17msqv3x0bhR0RgN0viniDwbiv+36Wvhc1L5wbvLnWJZF9bO+F/E9VaZSZf/yfd9XjGd78r+iyXepV6dtKfqxF2ff+X2NKeBV2ncH+u4n6nx5I9twlHKun6k2qlX7jVtFX9y4DHIK6kpGle+m26Rsi/HrdF2A94vV3reGlj3Ax4nyXYL8fw18vYeU3xzl6+gO4L9xRueUmaybU8jO1LmlKHCOLQ6sX/MD6xz9IHTW2uUXufLMq+BuLVkUeGfmmMA7M4vzvDNTotamJWqtKA2seUuVr/JlymZHytF+O02eLvfOxo+K5su/93IQxKu7cnchTtr53bs8PS/OVrqCe9W88fScz/sZy2jt+Dnsu8TC14Y+0xYGzrTzuN/ZFaXkKbWZdulnA5750uML+l15Bt596glbOKbUGXlRYC9zjDoLL2b9QudeCVui5kRp4Cy/VJ2Dw2deuae0Y2slx9Z90xxbUtZRMpv8VazP1YV2jOi18QHQv5bnjt/MidsuZc99B2Gu/HcybGrpyv9bwqSt7e8kDP6em5qtz+nfi/SST/0hycf777+LMG83K84kD67OYzcr35yZlQ5fjnXnzJSP5v7cCGxzEh/NBycGcuM+DDua0dHhUR9eaN4KmRgdylrwPdtow/PP1dKuBu+RDOw9Lzscm994f3mHQFFYWbYRZYd/qyp7pOuiwtdE+d4kNY76cuca9z+uLALi7W0KK63M9xup9jE45l2VxE91kYUNDHrf1rRzitHu9XhlMQxoAlYd9e3vHRiKoYDF6/XGmJ6lZfYmm006pHF+lU6xaXwfnBGZdwH6szGUePNQ9h3RUO5c0HHhdthZ5SZtmyxAHxVVCgumabUJfNoKO5j5lWm7iVboPhYAptdy7d9qYSXf3WT601K+uocnxqWvbjN29gyPuTY7BmlKomFT2z2YJ/F4M34eF4u6lEXwYzAxOjB+XrY/t2diHyph66Oh0n+BHh/mGZ298tVaCXNvSBYyLX2MZ+GrdpT4XUkYuFx3rG3AXGVjtBRll/Hjar+2HPFcJ9HGofvlOI8CR66FbXzbdB7bWN4prwBM0l9VyTVWxyFdpYgDrZQeoorhkUIbvmWpzXMJ8/R+IxGuX2nvk8q1fb2oN3AQn7b9eThggkbgTVecKUX51qmyH4ew3F+cuvLQ/cUjVBq0G8cz8dV7sNX85HjeJPJBmqBd9WaO+VK2jYmrqUz7op2V6rtZwE3m2kmqTbciPCcgSz1ZtMdW1m2tu4OOMOuGsxd9OAu5piw3fsd1e4ygV6P6/7Gu/wQNaSfxON8ufKOXPh39OEV5a0WZJN+g/TraU909Q5nqXb6ij+S4yVTy3CLiS8W5opTnlu2KzqfYD++gbVQT4uW9BuDdw3jfT9JuCWFJDz2YLlery8+PR3UPHfEsn6cn5/RpK9PjbLZ+/xnt2VXJs5UYi+77tKmHOlv1qPH/gOI9mTLZls6HgLaThI2MasuDis6TVbyWgT8V8dyfgQ+k89H7s6c=
*/