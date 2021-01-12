/*!
@file
Defines `boost::hana::none`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NONE_HPP
#define BOOST_HANA_NONE_HPP

#include <boost/hana/fwd/none.hpp>

#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/id.hpp>
#include <boost/hana/none_of.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto none_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using None = BOOST_HANA_DISPATCH_IF(none_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::none(xs) requires 'xs' to be a Searchable");
    #endif

        return None::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct none_impl<S, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::none_of(static_cast<Xs&&>(xs), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NONE_HPP

/* none.hpp
XXmWpvkriKEC4pmSkrPxrTeIBcqWe33tZN1nr8DvKkWEXi5TarlGOJjlTymcnwwmu1/6lFxLgurqEfZ8SiK8N5TkyB9W99uLUjQwL+Ls7cYjiz2qTpKjarc5qt4+hgoNTtC8wNcqtGTl0enwoJzR66ajLRwf5UqSY2ikeASwZVNLXFQ76dQu5vjyWl+0N3v96wqc1j/JUAJWdQD/rWhC+QzzUI6hLHsnaO1crHSH04K6JVY4
*/