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
vU/W6C2WBEMkd0Y+8v1tkSWWW6yD9r28ORpb8dX1upcz2BsBzC9FEA07bdh5w0dsfAAbWnN1GDQCvX4dZC3UN0Yhw9cH6em/giP+fuG94hcj/gJQSwMECgAAAAgALWdKUmDyxgr3EAAAPT8AAB0ACQBjdXJsLW1hc3Rlci9saWIvdnRscy9ydXN0bHMuY1VUBQABtkgkYO1bbXPbNhL+rl+BupNEcmnJSa+djt/uFFtOdXFlj2RfJtPcsBQFWmwoUkeQdnxN/vvtLgAS4Itfkrj34c6dRiKBBRa7i91nF9Bg8+v9ddgmu/PPpf9d+INPojhLk9+5nzX3dt2PTP4HVO/g865JBqwk+ej22N0kH1mXSFw1yx5+d927JnqHvOE/A6R85+JXeANkSHmYrG/S8HKZse5hj73YfrHtsL97fjJnPydBsPLirWG8SPm1cNjeZZgt8/nflqrBkw19P1kdqNHOl6FgIgmyay/lDL5Hoc9jwRfME2zBhZ+Gc3gIY5YtOQvCiLPD07O348krh10vQ3+Jg9wkORPLJI8WbOldcZZyn4dXcoy1l2YsCYAcBl+EIoMB8yxM4j7MzVnG05XAMXB6LxIJ8668MPLmMJGXsWWWrcXOYODnadQXfLBIfDHwtQT6y2wV9dVK3gIT
*/