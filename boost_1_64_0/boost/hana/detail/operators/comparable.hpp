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
TpfVFexixH7ksLxXy5IrG820R9BjNugfogJZCzXIdsPQ5CTAyI+9DWSe2sJV2KoSUQmF4af+vj1l/gaTz1hMTBHGI08EpXISJXxW7/tHmCugQGnjCZUWhvMkUURKcRfatb4eVR7QONQ1qKt85yYyZAZadLElrI9g3niWGGBY0e8GNOAgdOHmlA5RjRdi6JtsPlT2PcrE04c0Dyoji0tyqEa9PPcNqBetkMnqXLgbrVS29EzMbxFng64Yob4RytBvTxzHXV23iSVdgdhM6+B3u+hzeOqbkhq+f47ZK4zueBEQaMp8qy3MsnOHUDFUarjeMeVQgZTJuxxdngKEgCs4g5bPL7xSMj2jxf9OskTelIE4bm22sh7SmgmCR5WNdv/PzrXI5Xo2l/t+sfxGKstq0DsX//zVvepuKz2z2sAORc8Zkbpd4+5p/ZRH5zdyc3+Kd7CmRBBvtIEGJFlPNL2+WTJGyp7GNsYbg8VGKIkaZ7U+ZDZ33hCQAwKTNl/mhzCo4lKgz3FiTOUY++9vpS/8xuz1Fs+zLAwFtfsF7YPSY56+hpoUO7lDDpR60g==
*/