/*!
@file
Defines `boost::hana::Metafunction`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_METAFUNCTION_HPP
#define BOOST_HANA_CONCEPT_METAFUNCTION_HPP

#include <boost/hana/fwd/concept/metafunction.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F, typename Tag = typename tag_of<F>::type>
        struct metafunction_dispatch
            : hana::integral_constant<bool,
                Metafunction<Tag>::value
            >
        { };

        template <typename F>
        struct metafunction_dispatch<F, F>
            : hana::integral_constant<bool, false>
        { };
    }

    template <typename F>
    struct Metafunction
        : detail::metafunction_dispatch<F>
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_METAFUNCTION_HPP

/* metafunction.hpp
jQJ90jHUk5p57nO0dY4WGCiwU0lKu0wIxz9PfVkT6+ooYer8USqduh4s5IdE24JWvo+mfKr08GHJHlfyF1U7BwZLqrp62H83cz3YsAnJjK9cD5KHtoZ7M13HXv5CZaRCJQNTZ8sQZdCAiTSpLIxh7sRKUL3CyaYDKJNMdynuXy5r3cv8rCop48hj0swVOfrzI3p/4gLCs5SenTOX5TgiYuvSq9bGLMbRSWz8y1KO9ucbn8MsxwgAj3Ms04x9qbI=
*/