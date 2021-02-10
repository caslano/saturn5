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
L2w98KkU8q/5f8t0ZN3zji2frFEU1VR1ld8/OuPLwrNzyel5F/Y2/sY/P5dr9WozlD6dNH+k2OgY798wgjQ1YDTMoCZE/7WVUBXWnsl21aXiqyWba0vRWvQu7twmeDE57TE0CEbh7uIbg2Tz8ePHjfRjJxsTkhJd5NgYX483FTJxuzPqtXl/b8P+3j5JRggo+JWcn5ZwwQntneObcXucjNjkJzp0idGTdO01Mv1WA3rQXjxoYxT3jEaO04yhLt1JB/RaCdLn0JFtnHUKi9gxd4eDABT0Im+LtaARrU1jSnhgbQd4R5ttiYSMiBSXe8GdwcCEYgamVy9i8uSw1Woe8HG8dXz+497563em5gTTOBFQH0wFhiBaMJeGXLaGgdpLB8v+qJEmORaQki6PTGC/hGfoKaNX0IH9uA8NvL2fCNgxjKsvwdxi3mMGgPnHOCiaB9lnKMtVZ3RDH/2U3EzTSXQwu7lOb0cJAnhiHeaoPewkAwyGojR8Jlxz03Fjf5LOxtlGP037g5jglejJpnxnUb8IC2qTL723OaCcWWeT/9jsfbv93V++63Xi7a2d7rfdv1r4PuaEZKfnWVIKzStEO2/F5sCXbVg5ts1KIS51ybvLV97plWEn4SPOW0afq6MkFVpY1WYgrgr6rJd2
*/