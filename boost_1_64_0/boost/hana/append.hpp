/*!
@file
Defines `boost::hana::append`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_APPEND_HPP
#define BOOST_HANA_APPEND_HPP

#include <boost/hana/fwd/append.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/lift.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename X>
    constexpr auto append_t::operator()(Xs&& xs, X&& x) const {
        using M = typename hana::tag_of<Xs>::type;
        using Append = BOOST_HANA_DISPATCH_IF(append_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::append(xs, x) requires 'xs' to be a MonadPlus");
    #endif

        return Append::apply(static_cast<Xs&&>(xs), static_cast<X&&>(x));
    }
    //! @endcond

    template <typename M, bool condition>
    struct append_impl<M, when<condition>> : default_ {
        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            return hana::concat(static_cast<Xs&&>(xs),
                                hana::lift<M>(static_cast<X&&>(x)));
        }
    };

    template <typename S>
    struct append_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename X, std::size_t ...i>
        static constexpr auto append_helper(Xs&& xs, X&& x, std::index_sequence<i...>) {
            return hana::make<S>(
                hana::at_c<i>(static_cast<Xs&&>(xs))..., static_cast<X&&>(x)
            );
        }

        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return append_helper(static_cast<Xs&&>(xs), static_cast<X&&>(x),
                                 std::make_index_sequence<N>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_APPEND_HPP

/* append.hpp
bqvvr47vGtH+LCS+lUrb6jTWz067SwzfnYPzcJmzuohZbBdNS6t1h4ruatFdty9Mt8JZU1KGcFADxOow6PR2yGllicFxL6WMXkilZLGm2f8XzYLGUE27+02nRXduiK7ZpqbYqq4tr7FH26v+ZfxuX6i2alvX8jQz5Wt1Pazv8VHRvn1vBG2b+kyFHQ3fSyNpTrFWU+erRtF8Y0+4pqfUWV5qW3s2p5O0sZrpqqUvWt4W7V2iPW9fZO0Sj7fM7bNWW6d3hqyP2RVyj+3rt+g6uUF03w1/jlWlqJ4k/8H6ltfJOt7Du8h75NH1LdXV9cUO0T0ZpittTH9O89V4/a1MWiQ29WFSukqbPjyv+6yvL/T9rhfNhPB4e91unznoZX0/RuunXGb4Hr43mn5RSZnTY3l+76nbgJeJ73D9udb2Y/Q97pxg+P52uJ7b56uyuM2p03idaB4O1yyp9dGNQXuR11npL1Ws1dfPVsLlhu+3IutDVhr67CnXknUaSBg+3RMtDKowt0U7vpvh+5nw+Ae6OeWeapvGv0R7S1i8Jb621dtxV8j5T2F15/kYR18i2q+FpLd9YyP6OTsrutvD0jq1qLrW663y1djcZqiRTTeGhpXlKRSmquq0uN7SuidEt+u+SLpF1SU11sZXlyveKw3fPw2Pb9CIUJEepbF4XErH/biEYWyzMLiclTSVyqudlurqvFZ2leE7PbKus5YpSGYFF1ud1/XzfVT0dzfTd5Z7K41Wk9Vpruvsgh6yJ3vwczbX57arjdIkekeD40qdyRNdNN+9mMEE/6gC/VxnuaX6Oo/lJMqUZPDz5apiOKPSRVdkvtXx1ro7RTc3uBw1s3WR02XxHLfWTb9azkoK11UD3HPLnRb397TuNtGd2EzXXekstn4cUufnpJ6G7ynB+aukxldusZ6O5wbRi98XoscwpETU4vuq277xveRMu9cDujI3ZPn4o07bpaLpCokrr8tY3NbWaXtG9I7sCdYrc5fMt6cfo3W9SbLfalAeUm2taiO2dukeF921Qc+MOc+oMrG1umb919vwPTM4vs5yIqyGJ4IXLtiif1z05zTXd7mrS2zT1/m6sI/he2dwvlbzjtb2I3Rb65DoJZjPbmBtl79YTg1M5Fv+LOs0n3WN7IEcKQxe0ltVx+VVpRbr99ftANHvszeKvsXj22b931fOCo4Qbzvm58z6X3S/vK+5rupPeaxt3+m2ZUY/WY8UKb7Sr7B6fk7HebtoD4hwj+1oY+rnK72/7LseSGvVV1Xrv9TYJ/lrbpUt86E6DA0ShrxIYfBWz+d+M1xBp6KozPK8rsOQea20ERpDwxC+Bs+fEFbfi8E630sY+oeFwe51gDoNsmWT0TZh+mFrAW3JC8k6DSQMSWFhsHM9otn+H2j4vn5vqLZda/TM/C+6HzdG0KXLQ9Xmj76aCbA63a/XZX2y4bsyPO6yVlDib6wVNBta1oZlpK7vJCyb90UOizm3alM49PNYMMjwXdwsTeyd4zX7/6JfFk2fxp67srSmzGJ9nSfmpMja+j1R9GUc2bvQZd4Jq/Nnsm4HSlhq9kYLS3GR02dtm3eoTodUGfcJy4/nYz2pDsNRCcN9jRHDwGwC9aPNz4NrsOH7eKR0uK3WE7Sq11J9XS6cEP2cSPq0E6S9Ylte1OGouU7Wce+JHA55LmwLh34mTko42rweGg471/uO1eMbafLOQKR7UVlVoxbeVPgHdfQTYiaHpeHRZVWHIYbvjIjhMYflqxk9XOBvSbFelCLD2rTR+WOdhGVb4znDIoPVBMPie6Sf185DDd+bIoXD36q3qbzQ6bBB9O+PdE9KWcfqozFn43o4HY6kYbL2MdLz6nI=
*/