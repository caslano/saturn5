/*!
@file
Defines `boost::hana::Logical`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_LOGICAL_HPP
#define BOOST_HANA_CONCEPT_LOGICAL_HPP

#include <boost/hana/fwd/concept/logical.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/eval_if.hpp>
#include <boost/hana/not.hpp>
#include <boost/hana/while.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename L>
    struct Logical
        : hana::integral_constant<bool,
            !is_default<eval_if_impl<typename tag_of<L>::type>>::value &&
            !is_default<not_impl<typename tag_of<L>::type>>::value &&
            !is_default<while_impl<typename tag_of<L>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_LOGICAL_HPP

/* logical.hpp
CmgeVoWYlN21SgGOW6/pW7mR/eHelKlMxLgKB6zlJ01aS7tkvM3WMo0L3GZm1FoQ42nQSjuOcsLIdodtUDnH0RLNxq25PG0c9e2q4shMSyIad0IbWdBYJuXdadHIZ2MnetDI9zTWczq49tvailbJ/i2Lztyxgs5z302hgxgXHeML+CgSIGys3xVYE97W6lzlGHvs+dwmi0YGIkHXTEboAeHv9ykC0VFA4D5L/9h4gSslAkp/
*/