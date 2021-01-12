/*!
@file
Defines `boost::hana::Hashable`.

@copyright Louis Dionne 2016
@copyright Jason Rice 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_HASHABLE_HPP
#define BOOST_HANA_CONCEPT_HASHABLE_HPP

#include <boost/hana/fwd/concept/hashable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/hash.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Hashable
        : hana::integral_constant<bool,
            !is_default<hash_impl<typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_HASHABLE_HPP

/* hashable.hpp
iIt+TTCFfn6u3wJM8VsaTMuwOHzfKmggvupJVIgRs4XdH2Z6Z8Di+FLAotAe1JYT4GVGV/RX7WqW4bO6v2p3NtKpMPTm/Uoz/L7Pb3ATr9t/9Rv8p6N2l1BiZiYTuUiHxwTDxBGYHKzlF7aVVXMRchtaaH4QptWFuRShWRZmIX8YmCfcAfGIS/InJcTUX0qIJSxGKBE0uGySaOK7Tgibb2ppJJX9Wss2BNtst1xItAzYKvyA
*/