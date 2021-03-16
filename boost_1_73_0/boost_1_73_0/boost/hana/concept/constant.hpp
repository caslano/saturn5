/*!
@file
Defines `boost::hana::Constant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_CONSTANT_HPP
#define BOOST_HANA_CONCEPT_CONSTANT_HPP

#include <boost/hana/fwd/concept/constant.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/value.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename C>
    struct Constant
        : hana::integral_constant<bool,
            !is_default<value_impl<typename tag_of<C>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_CONSTANT_HPP

/* constant.hpp
9NW7O9OJ1CoewHQiWO3MU7Da9zOCUGxGDPuHxCgxKiTVPRrIMhxoGLrGVXtN2M4mhPaQo+1ute9jejHN3EWas/vssZK1T6PQJF873KLL5W+H05W0w6n493T6dthtG2xqY+zaBhtsC+Yr2BbHmLb4qmmLCtMWxwL5bSWQ5TjetMU5ri3OCdseS2jrHW3XzdC+I6xbodyjXTZtzTEKJkmsCGlSV27+lq5Nu6V+EipVPhqVqJ9Z+Pdo+nbZndHbgFQ=
*/