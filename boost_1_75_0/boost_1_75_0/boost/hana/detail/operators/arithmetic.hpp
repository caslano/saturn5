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
n4spiBk9T0HN+3ZKIzzQoPY0ax81fi/hfnFaQ0aeaE/z20+6uF2gOFGL0y+eY6ItwH+cY8+g5n2jcYvTUWZxeiTQtWGyA+KLfBpkBVRW7E1vGmZvevowe9Ojh9mbxuUExeD0rWhwOqch0VFvj0C2Czd5Jy4s9Y6LmZum5jrrLegPIy1sUSxOx7CwdkBO/f1iUQ8pQhPG/tvba89SPA4IwSF4wPcQPOAb8WiThbNAX9vhytlofXS/mbgjtqaKNGpTrCpB2G8Km7nftxhhatAbr/tPmZ1osSgq/Z1DayhRtBadgnbGTgBtw/kwYQBGOnEBF8ChGWdJx91a89AJwiE5PIEagGZ2QS3ULmg4GUGG/o/Jx7U13boyri4TD+DaOxWboKFRg8o2kNAzifHJxFrKJ9NBlfEY1gFNb7S1AKdEkVPudcc45bm7r8wp3dJfH4hxShRtjCOncLuzjS0eczFUSapYFLMAfSLHDSzSRM0/m1JPKaafR4K443bfIrQYxBrkjpo04kxvsQ+grz5PdqnHsgY43Wzbz/lOGJh1561FBjTZi8Zh0QVTM7pguhVAe9giYYQTMvCLLRJC9GvwrFoAzRijP6Fm5oYpDaNE1CjGYVGoM6YQzF/3sOXDCHPlpI1C/TE1Y5TP1Ch7h0WhLpl+SXNJUaL8bHgu6HWpluaiRqkengtGcdNcUpUodw3PBX0zLaBR0pQoc4dHQfdL
*/