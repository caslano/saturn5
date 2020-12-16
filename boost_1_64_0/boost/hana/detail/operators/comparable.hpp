/*!
@file
Defines operators for Comparables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_COMPARABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_COMPARABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/not_equal.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct comparable_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::comparable_operators<typename hana::tag_of<X>::type>::value ||
            detail::comparable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator==(X&& x, Y&& y)
        { return hana::equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::comparable_operators<typename hana::tag_of<X>::type>::value ||
            detail::comparable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator!=(X&& x, Y&& y)
        { return hana::not_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_COMPARABLE_HPP

/* comparable.hpp
eVrEVbT2qHidV78Y0wtU/fe6Mcu0I4X41Bzbr3BCMv+zFI7h+Rpn0M3PlUnecrw8jbaqWPNsvKrXMQr/oIrXdzbHVPw8lX6CPOoJktcQ9xzA9BsN54q5y3YQn6oz5+75ol1Q7yBPf4YqV7vqo+oKOca1zE2XE3YIij8bvAnVFxcB5zSna4jqmtqy8ZnMWC21WXeIPPfpOIhDe/hO32zuw59baSnsHx4bH8uNThqr+WFsPAZyY3ZnnicyvivEvVDMf/n+CcJ8zwOG82JvVCJ83jdyH3Rxah80PjiGHeAQvpHR4fFhsZsJxPDdFNkGnW31O2PhSba2ocG8WBhtQz1nsZ6XsJ5jw31n2wsBxv+nq6KGgzjKObpoJufrE4VP063x7wLlr3Ku8ldZ6PQVrZn6tNymu7Vpt7RX293S3p7QKQ6ciecrX4C8C+R9Zy504WxD267W5rbahpS9E5rPHP4pq/EwtK88YyenQJ6xSVPIqpaIsuGIHrdim7SDYhyvyIkzd11HU6ZRnrk7MrubusSZm3kJHTOJJDqPVnSt9EcZvwjQ3JRp9eKPKe4HbW8VfbyKMigHFr4p5ftK1H90NXdCOmWh1IEIn5Dp+0K7LFrqzlBLp0u3lmGpm18XkN+sd/Yj8O8gdSB4mM/4p0zl8fBAHFU96h5R5462XYmf02N9m0L41mnbeaOvl833ONtXnZiKDWhm0LdteryDsw70TdnR3g2mRNgjHUzcT3uUgxmZIKrs7jRt8vBmZG2I0F+lh7fg/vf2jrbudt/em90YOMHibnFhpSOscX24JVvjYCcksC3CfyVhkfBf2QCADW/1YXt382QfBmHW75SAn9tTbZ93dTN8WkBn+Rjlf/10Px8pxmEZHxu4N7YtcEfsccldQYIt7hlijkr8WqWPraMMznEvA6s3MCs7SsmWGgL31jKBO2qNskxi/G8XZZL4OywNzLx2OBqFqHm7hTfRD307ZYhnOr+oIGEWDFeGnW4sd3T5PmwWuPKuX0sMx7jDWOsi3291bdJSC+F0wtfbDoE3Z1xbtFv6LV2Cnz+estYn8M3LDosDRwKmJK24fN9R6/hDJ+9F7s62N7VnmsER7FztYn/UNqADGqOjvlSP+ns46u/hCP09/C/I1g3sYwtiPpEq48ctDO2UrHuf8LBk7fqkgMk17lMCLtfDTxOOrYNfXz/jcY1XKzuWP+thmJc7M75dPmfh5KzY25FHfZ7w5sz22npYPBombuDXpeBmlbH4XyC8rRVbfqihHP0v+nxFCsZ9iXGcWjHsesIwBXDD3PLQL1sYd4yMYVvfwDg+fBzDvkKYYWgNcYSFf9XCqX20sK8R1rDDPnpiYF+3MLshq+to28n0N7r0bUn9vkGY7P9vxrBGDOu6WnC6+s4e8v0FXFtbGnxffdvA7NiPYp4fhxtqWzNmQ1OLU0GL9zF/UxxX7/vuu6Tn2u57jG9u256Va/rNimZHR0NtV61N8/0kLpMBrbjRqDu7mme2Syunpztr9OfAeC9Ht+y1MRYcs7eA/ze5vpgVwHHjYEici1+EvE+fGDIPSfY/KoeXlx81Fe1ttmQPIYEp93W+3PF+JdvWaM87sxjGrsD392zC2tvaT/A6W8KaWmo9XgFhjUhqwnMZ7so0t2bcOZMwnCJ9unkCxklp7QQIl/u6YpdvR30kfc1dVsma1Lc1p3rMAZW+8zah15P6z1sX4c1//SZqrAeR7/7janCU3I1/mZAllFCWIEUIHsB74WFdijk3TEDSkR05p98lVTDqlq4Q8u5XVCZvqb5S6TCurMSndBhXUXb1KuJuyluWfa2yFAh5fd9rmDZ+L02U5XWEO5nh1cz7tZTLvZ55X1M=
*/