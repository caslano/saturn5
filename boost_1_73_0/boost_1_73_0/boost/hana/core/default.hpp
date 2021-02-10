/*!
@file
Defines `boost::hana::default_` and `boost::hana::is_default`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_DEFAULT_HPP
#define BOOST_HANA_CORE_DEFAULT_HPP

#include <boost/hana/fwd/core/default.hpp>

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename Method, typename>
    struct is_default : std::false_type { };

    template <typename Method>
    struct is_default<Method, decltype((void)
        static_cast<default_>(*(Method*)0)
    )>
        : std::true_type
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_DEFAULT_HPP

/* default.hpp
AE+EJQdOfHrtz1HUkCMxxtHtwQCuO5cjp9PljDfllqyNwJB2xOKkmxJ0oSZg3mc/inF5rbzddUR7A1YBQcwHgr8l7sbXmBjfsA0CNze/ggaxcFf3e7DX4ZT6UzVSLntF6L8oXqFN6iONXTM0qmLAFFVJgaBCwVp8atzhb6f+VAp2DRppQ5O6LYQtcCLrSFrJyjn6LBF+EFEKYxk84UbIJRT8AKbRgcDjXq63KAKCiOwFE7wxs0ZdVt7RSBraF1gwEJ+BHWWi2YRbVvOBt+FOG4+CDeX4zIzLDgBN301tUloBUPW6zhgspLAOTGL4KoS6J0aDmtRFd64S2QsYqXLjEBhaeAsoVHuaMt0fNMj2CCgxXkgIjYd70zvNQVLXXBInScWfpSaGytrMv9njrBrdcRHski1ANFKBy9QV2tOgns9dMkYDoBxG0RGHt3nZOWuOhF8nfsSeJzSVik02r0e9bIPJAHACAQtevAeY2AtCZ+V9Cj96yYrL6+OL1knnTRcNMN2eM2j/1mtRJ07rot16i5d01SddXivcOz+/JFunKl68kqc+8bmpEHINYQVHIPaVbTvz2Sb2GYm1zp991bCcRQzHijP2QC/0ZjPUY/7fYIh9SQqlm4K/zU63Mg5B/0dhTENXOJvN0ZOP5Koo
*/