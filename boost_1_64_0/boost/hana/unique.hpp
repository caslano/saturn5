/*!
@file
Defines `boost::hana::unique`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNIQUE_HPP
#define BOOST_HANA_UNIQUE_HPP

#include <boost/hana/fwd/unique.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/equal.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/group.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto unique_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Unique = BOOST_HANA_DISPATCH_IF(unique_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::unique(xs) requires 'xs' to be a Sequence");
    #endif

        return Unique::apply(static_cast<Xs&&>(xs));
    }

    template <typename Xs, typename Predicate>
    constexpr auto unique_t::operator()(Xs&& xs, Predicate&& predicate) const {
        using S = typename hana::tag_of<Xs>::type;
        using Unique = BOOST_HANA_DISPATCH_IF(unique_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::unique(xs, predicate) requires 'xs' to be a Sequence");
    #endif

        return Unique::apply(static_cast<Xs&&>(xs),
                             static_cast<Predicate&&>(predicate));
    }
    //! @endcond

    template <typename S, bool condition>
    struct unique_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::transform(
                hana::group(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred)),
                hana::front
            );
        }

        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return unique_impl::apply(static_cast<Xs&&>(xs), hana::equal); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNIQUE_HPP

/* unique.hpp
Wy3tBGrnKjZlTWfbXP0VFtnaHZVQAVaKF1rTpEJDFOZ+xI6aGaHyAyuGQsC+Ft+W3LQV7YupNeZYZfZ0Vem7WcmdnSfCMWOKmCHiWb5vZNGLLTKVysJwqKA5Idi6+HBIAyylGMZm77EaV1MkTbZ6RyMDOKiA9xN6Y6r5xoWi8cQrw1nVMtQlqVupEzthGaWwDu7krV52puPSPMw9QgxPn8qFyJfvQm7hseOg4cUXHTbPl/Yr4MWgGAj7QYW8qX0rVMx01GzniwhvkJDT4ttAF3wOrYZkaoJZg1/ziU7WY3DFNusw1s1UzBYtpmlnmyqlDr+nU5qUsNz6yvXNz5Ke51CQGR4bo9F++AC+j1+71Xoy5Euo/7sNUclrE7vjJx0MamRSpw30iG0cVc1OFUT3dJl8QM9dwJNxmjcPj7LZ7Q1x8DSogTspmBrlzKd3DLLQvGskmguJx6hATZ/dL/iEwLV8iBW6fHb040+VlD7VI11ii5IlZj9fAxHDdu5MFKtEDmOPl/k4CCclXpgrZFhgIRIYkBw730z7qXWrzLjgrZd1/Q5IYnoT9g/cKg==
*/