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
khtZMhRNPGdbJJJnDoPj6d1u8gSnKzWHLl6TLnS9CAfxxK5nzO3bEfvv+GH9tzpItf7Ab0HYvp1UIkx7Na5nkqWNT8Cnx+j8QPR583cQfxNnB6JX4O/4OYCfg/8L8FZyQSCa+cn0v8X4W1kYiI75VCB6wqC/As/fFebvj/irx9+T+Os2f2OA03/tv0T9d6iHCq+Ndvia8Jf5eTt7+lfsx5QjfiiYYT9S8fEpv1FiffD9zyns
*/