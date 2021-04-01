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
+jTKOBHlh7LsfP4dENgOlKO5mDE/OTfVFCJjbwOBjnBgpeZjU+qP8NvqDa+ZTGa+IqWD+zM/LvvamPuAcFWJapNu1Z2Z1SzsiddfMEOXfs9dst0OJhGwLiDVv8X9RqvMyDPeocXaxYSoYJMRQPbIZC6B53J3Qp1xlhii2ka8mGjNSlKZTx1PuB3Pif7RHxphWGuNcVbUcMTmBgmFnWDTl1ClgB7g+VOWqKXOELpwkHCB8p1MtlR99OUtK/a9r3gF/1HeZFIl9cs0CPNKBhtPptxU/0VUGA4tc0YUb8z6KzjAxzs9hv/3jobOYvAeDakzxKjtYLkLaLHHD1gEMSWmjsC8g3G+M47yhTLQso0Qlel4EcnwzGu5KWHo7JYH8EFIjCCB66UxKIaWxKpOo+GqHW+Go0a3IGaPKYsiC1XiEhqTnRN796I4ge8q8YryjDHyQdKzP2r/V4BmeQzYMA7HuyzuwcR6M1KNlsqx1qBdkD7PteZ6jRTecJgMzwNr18Fiq+U0eNNZzuxNRg/SC5eeKnuludjdQsfPtgXlMVtWB85Vhw0GR3MDWRbNQw==
*/