/*!
@file
Defines `boost::hana::negate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NEGATE_HPP
#define BOOST_HANA_NEGATE_HPP

#include <boost/hana/fwd/negate.hpp>

#include <boost/hana/concept/group.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/fwd/minus.hpp>
#include <boost/hana/zero.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X>
    constexpr decltype(auto) negate_t::operator()(X&& x) const {
        using G = typename hana::tag_of<X>::type;
        using Negate = BOOST_HANA_DISPATCH_IF(negate_impl<G>,
            hana::Group<G>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Group<G>::value,
        "hana::negate(x) requires 'x' to be in a Group");
    #endif

        return Negate::apply(static_cast<X&&>(x));
    }
    //! @endcond

    template <typename T, bool condition>
    struct negate_impl<T, when<condition>> : default_ {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return hana::minus(hana::zero<T>(), static_cast<X&&>(x)); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct negate_impl<T, when<std::is_arithmetic<T>::value &&
                               !std::is_same<bool, T>::value>> {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return -static_cast<X&&>(x); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NEGATE_HPP

/* negate.hpp
hx1xtM/rvYnK1vE6N9YBl+25v/BZnHmYSxyLh+Carh2fV99V08zhzu58N4p7fv0F9okqjS/zDUj3TC0yinHK8aW+aJIw8KVKcjdBq7pHwdGmeSZL26lXP4eV/rPkRUMxYDi/6uAMRelHQZzm5f+DU73fDJS/ox7Doq5zZCwIihQvFlR2FV62KlewlvS6es0dBt3o4kVCrzezVj6AP/fiY2++P+8a+O6OPe19N3s3t4ksmrj0mkIK6Bc63TfF4ryPG6MngUYmkJintQBbcopABKhm0ktqrtEXMPOCqM4qRrfguE6VTV5K3PZbfrLnOMUG4rCyEWEgqzjNCqJrBBB1KCrRyOR5tI1x7Oj+zHUzi0nYxLUMS2gedy7SPY/OI0438ERd5H5T4XJ8JaBV9CfsR+ieXlim26YD6LbBZu96C1dluI5DcevXUM0sko2qlfuWOVwt6iCKZRzHrflZ2lxYVLjBVqbe1OJPHPxhEuZJmUTCHkAXLP7GxZ9EZRYlsiH8p3r47bh91Zmv0Mv8MsmlaHfdFvqA9EHOuKWiqL0adEoRgREgM+rBxoXYVFbxKCdKIDBDqeeLfE/4G4+foMHSi+okVO82/+nJJrK8w/sbxCp5ZdYkQXOZ+gFB9pe8HaeqUPplXRsHGDNYY4qXwWHDVJRBnfl5WV4uTeJ7jgdNLiEdKrEz4NVc7RpXhzl8/yrnrSz0qyiJsc73+Yoj+3bAOjYjNSZQppWgxEBg9C0YP+qNLoSzuCOrOv4pn7+eI/PXWRmVdSPaHWpnf+ug9zb4KYe2FDKLwyIs81Z3xqqRsT8bR56Dms/7clPJuMijWChIVCF774PKtpPDQ8xNkyrLk6Ligz3P/h7U8WDbGkZxPeavHR7AeYHRLpMaijVr0J8rmybjGGDE+zOqeTSHgr8pH7uf276gKuoyKXIBNLPtWtCtapun9spK2haSje8b+L7v+6GXyiQRYxxntPYj0gu5c1JWZRPEWWb7wu2zlhQG/L19uK4TSB8w/5aC92HJD33pZwlyX6pe9+2WHsVhQ5zhYVaVIGt0bJjzSy8CPQxgZ8oTynGdCbwyi4NUgq7LDDsUW9ehHYqwhNq0ShtG+z/yBHBlkd0LOS6/hJ4zLfIUI12MpmqczKv7gVavIlUAJow//0GXZM4tjmcxy9EFPxObGHhn7WLhueNWeNJL8ig3bXcdSuYOHMulyXEtZ4HMExmGmigbti7vdcLhAZjFUZZWaWpog+R/5VVnz3oGx7fUREWUNWkkNhmTUpzbF3HYoBB54TdB6Ze835fm1a7Pz7kG55Um9AJf26Wr93I4Pszw6UcdulIknswgykE2AbC5aGtNLJb5vgmdrI86jUxvGYLOWE57MZJ+mIVepe3UZ/Tn3wWsqxPGwRbHmXqPxhYJ1EVEiuB2295Vu4xOF7HSrcmr87zXS3EUhGmY1IhtD8W7IRrZN/Cf3t99AwcbBzIpams7sndw2E+evmv591a8vSfjooHkGEmxNznn3q+PAY6f93EelXmTVWJ1Wykw7N2KTC8NI9C9f5nXP+17YJkkzhUdNeXuWhEcNsygfwkriV1GRLQq8JLOTOIOttQmDVyaW/FjN47v4biWktDP01AKrZuk/Oy2j391xlGlkcDV3CtDO45gF/P6oetbXt/L7Fg+oPd2VwZVJCNy/sNaNr6GrtOOXnIe+JC9e0w/x+e/KX2vDqD7UEpT4vVTdrwe4Oo+lDIuy2qo4+zJzGefxct36kmRV7hnQACBt4f28cbNfgS9+B4CtO4amusUL/8BriylMnd4eRl3zh8bOn//OSP0T3eUMD5pT9aR6OIWOmOWihpXl6ZIPOVvNMYGYcR39c7Zaps=
*/