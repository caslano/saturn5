/*!
@file
Defines logical operators.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP
#define BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/and.hpp>
#include <boost/hana/fwd/not.hpp>
#include <boost/hana/fwd/or.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct logical_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value ||
            detail::logical_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator||(X&& x, Y&& y)
        { return hana::or_(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value ||
            detail::logical_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator&&(X&& x, Y&& y)
        { return hana::and_(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value
        >::type>
        constexpr auto operator!(X&& x)
        { return hana::not_(static_cast<X&&>(x)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP

/* logical.hpp
wV/Ve8XlzpWrqHkHefWd2Q15ynUxHn262lofzAIUrEHpW3wEiMbftyT37h/jCxzsZRzd3XdxQJeNeKV2kK14vgOsvdmMNWP5ZXuibq/QkYm9tKh7CgNYLa2gpZGKlykkrR1xg3z/2E3xnAT/lnc/1jMjfoDHLt6fsftx9hgcgonwrsU2bghlp8ojbVn831LXBUIPM9q8hubrV9KqY643+jWTza+HqWrjVL9WEtNFlNK6s6lKERXXGolaG6Us4YG3v1YZi+b6Ijz+Y/VRoyGTqNP+WatnsEKbwrvO9x58U3sBOg/LFmPq2cLZUU6D+D1VdFv5hU/iECZwRAgcC90BTJI71nktkig5kfVATiIhpfyCutZbhPDwh73tQrxfgr/1Q57g/7zXzd1j6biuO8J/XjnCzw/oB6ZlsdP59tpkKnuTi4CKsZbECOtdo4hEAWMX+VIM3UPSciya6bnxHaTONGPVTew9KEUydsOatxr3GxybEV4ALW0IL/wrPBtdK6Iw4She9qlUX4KG+yAc/k1Eel1xO/u03rGzKwTd3vSIXUGpxyor7KH5cc15V/HRCkEx3lFWr8YKG5RwNrBI4Ry5XFA2q7l8pCLyjSskG2KIfHzNSx3UGuAm3bKZtmdvZtAx+ZZLcnOtZOH8rHyP
*/