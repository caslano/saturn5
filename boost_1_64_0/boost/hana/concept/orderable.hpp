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
awypR2+9RDNQTQIV4D04/edTuaqNP7g00KbRv1ZGasZjgXVizdEawm/cfoo1xmR2Em7KaMKCiCFW++pxG4aAvHaL+tXK3vPmhgZd9Q6OQddgFBUiQ70WnZKoqtEnjlq5Du2mrI6YFL6vYKki4EFA0zoUhGkeqV5As4KUiF4qIcg+sTpfk2dDjRG3TPr32YG++KkJlVJZwqpeuctcD7+yKkMc0tRQTldyiL6L/+Hi7RjF4/p7VXAZa0jWxQ97ppd8r2HfgjXVCNvCiDeVuvq/gcKTcDK7nsRD2XFXl5ALxxiMuALwCCyidoLZNoNQ5lRHzBosKN3Yh7TaEYrlT6KRLRoCT7JVwCwsTbu3jAf8nx+e+vSFI3pFvRo78iPRwVFDQlWJsSd46fHvxDXLLdzGS2MhhAaI55c4K1YhQzb3IH7CklC23HuFj+Ua6yrRhSv2+po4+FY8+rrKAPd++/3YmklWm1uiOHZmK/z6/U63ld9vWhJNelf2Havibphr70FEqS43P/4xkV9RX97QbYWjfZm/s0aiGv9JLALron0NWj3q1yWRDvL/pw6ymw==
*/