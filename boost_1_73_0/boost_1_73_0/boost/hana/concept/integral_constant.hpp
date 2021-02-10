/*!
@file
Defines `boost::hana::IntegralConstant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_INTEGRAL_CONSTANT_HPP
#define BOOST_HANA_CONCEPT_INTEGRAL_CONSTANT_HPP

#include <boost/hana/fwd/concept/integral_constant.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename C, typename Tag = typename tag_of<C>::type>
        struct integral_constant_dispatch
            : hana::integral_constant<bool,
                hana::IntegralConstant<Tag>::value
            >
        { };

        template <typename C>
        struct integral_constant_dispatch<C, C>
            : hana::integral_constant<bool, false>
        { };
    }

    //! @cond
    template <typename C>
    struct IntegralConstant
        : detail::integral_constant_dispatch<C>
    { };
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_INTEGRAL_CONSTANT_HPP

/* integral_constant.hpp
eXFaXhXebbLGOlm3DK6lNI06WHNQr4wTJd7CBX8LQkGH7OIYZZi3OzuG1syQcZ/IXvFB+CCv1SADkCEDj/CMdxDCIPRBLML0TI1LCFJusNrSSa+TPrv2y16v5tmMY9zhITgsvFtwPD4Z2f6uoSLxAGnH4MyuuBR6laP/banSR+F91KWbO0TayMJuLfAU3k06pZ4uodwKfHGTVYtWciZHuehlIrJ+7K0gD3taL1c/uFp9n2K1djLNNevSBHysOnFVq9SAfYeporYepaG2bSntEFHd5FzfajCBczVMIP4sAwaruDlsrbhDfplkoZfRVZGyZId3EwYS7VFokzcOsBay9OKFWHrv5V06dKZJahaQriV+RDig4B8Aw+7urpY2nWMxuoGpmSgLsRy4pGuFeOvRx9oegsmiwNNnM45SjBcDxLFqIOQo4qmQFwPy9QIXShzRklceXtXC+4DUm+4D+kvuv6dpUUeIYiPEs3PuezkmIsLVy8T5YZw0E1S6DDzwN44aCuaIValX4D7nEPg4FS6DMBUqkjFpE1ZfGoV5l4Cw1FAJYvNG8Sq+B9qev2neJTbLteyyAr6PUG9Gf7MyDNqnZqrUWSxJ8edrSh7Q8Eh8Wh14V5UWa6D+u6wPxLGOuEQBuv/WAerWgFwIpORF
*/