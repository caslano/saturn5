/*!
@file
Defines `boost::hana::Orderable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_ORDERABLE_HPP
#define BOOST_HANA_CONCEPT_ORDERABLE_HPP

#include <boost/hana/fwd/concept/orderable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename Ord>
    struct Orderable
        : hana::integral_constant<bool,
            !is_default<less_impl<typename tag_of<Ord>::type,
                                  typename tag_of<Ord>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_ORDERABLE_HPP

/* orderable.hpp
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
*/