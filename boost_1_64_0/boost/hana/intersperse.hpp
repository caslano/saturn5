/*!
@file
Defines `boost::hana::intersperse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INTERSPERSE_HPP
#define BOOST_HANA_INTERSPERSE_HPP

#include <boost/hana/fwd/intersperse.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Z>
    constexpr auto intersperse_t::operator()(Xs&& xs, Z&& z) const {
        using S = typename hana::tag_of<Xs>::type;
        using Intersperse = BOOST_HANA_DISPATCH_IF(intersperse_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::intersperse(xs, z) requires 'xs' to be a Sequence");
    #endif

        return Intersperse::apply(static_cast<Xs&&>(xs), static_cast<Z&&>(z));
    }
    //! @endcond

    template <typename S, bool condition>
    struct intersperse_impl<S, when<condition>> : default_ {
        template <std::size_t i, typename Xs, typename Z>
        static constexpr decltype(auto)
        pick(Xs&&, Z&& z, hana::false_ /* odd index */)
        { return static_cast<Z&&>(z); }

        template <std::size_t i, typename Xs, typename Z>
        static constexpr decltype(auto)
        pick(Xs&& xs, Z&&, hana::true_ /* even index */)
        { return hana::at_c<(i + 1) / 2>(static_cast<Xs&&>(xs)); }

        template <typename Xs, typename Z, std::size_t ...i>
        static constexpr auto
        intersperse_helper(Xs&& xs, Z&& z, std::index_sequence<i...>) {
            return hana::make<S>(
                pick<i>(static_cast<Xs&&>(xs), static_cast<Z&&>(z),
                        hana::bool_c<(i % 2 == 0)>)...
            );
        }

        template <typename Xs, typename Z>
        static constexpr auto apply(Xs&& xs, Z&& z) {
            constexpr std::size_t size = decltype(hana::length(xs))::value;
            constexpr std::size_t new_size = size == 0 ? 0 : (size * 2) - 1;
            return intersperse_helper(static_cast<Xs&&>(xs), static_cast<Z&&>(z),
                                      std::make_index_sequence<new_size>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INTERSPERSE_HPP

/* intersperse.hpp
A78c2Y0McqfMYkVJ5fjP0ZQePivi9VwUdBeE1C7y6OPxe7ImrY6gscQK/ddNPR9M+GU5DjhB2ttlXrGuwas9p5qSh+uAEdJVOy9PGVagaITN1INIbsKPHhG9NDq4fwQipkUaOh/zfwIwyNd9SZA6AdlOg4LHtQGsayTeQchrOtVULXAXi6RnklsWMePI8vQC9MFViJ9UK6mNSYX7T9KTq65PY7vglKdfjZCq3ItKED01IqSmjIWEaQ/Dkp+BPvTbhh1w/jIYZ2wK8EX5jWuVhq+Adqx5SB63zI5vtEd8c8P4x4xXl/pyZeVBXcOCxxhPVQEc2TqODVatHa9NLf4rPUaqZ5zMpvqv2NA3t8Hy0k3Cwj4giDhskGyq/Ommv64jmlZt8a8Oe3OsHeRJBnF1oEqYNPXqT762AJtGEnbG/WaqZKpt6JBkaop093EXU/uwmdBVh2/yvLIIZHZMziXCoMJkNyysTBptYqjVCyKVBJ8tWQG/4Muua5B/SgAEZdgeIona9S9ahAk5HDc4NHsDyk1loewINZ7cdWRhxLRF1nCsMrt7kardTKDayg==
*/