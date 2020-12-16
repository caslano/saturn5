/*!
@file
Defines `boost::hana::unfold_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNFOLD_RIGHT_HPP
#define BOOST_HANA_UNFOLD_RIGHT_HPP

#include <boost/hana/fwd/unfold_right.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/empty.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/prepend.hpp>
#include <boost/hana/second.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename S>
    struct unfold_right_t {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::unfold_right<S> requires 'S' to be a Sequence");
    #endif

        template <typename State, typename F>
        constexpr auto operator()(State&& state, F&& f) const {
            return unfold_right_impl<S>::apply(
                static_cast<State&&>(state),
                static_cast<F&&>(f)
            );
        }
    };
    //! @endcond

    template <typename S, bool condition>
    struct unfold_right_impl<S, when<condition>> : default_ {
        struct unfold_right_helper {
            template <typename F, typename P>
            constexpr auto operator()(F&& f, P&& p) const {
                return hana::prepend(
                    unfold_right_impl::apply(
                        hana::second(static_cast<P&&>(p)),
                        static_cast<F&&>(f)
                    ),
                    hana::first(static_cast<P&&>(p))
                );
            }
        };

        template <typename Init, typename F>
        static constexpr auto apply(Init&& init, F&& f) {
            decltype(auto) elt = f(static_cast<Init&&>(init));
            return hana::maybe(hana::empty<S>(),
                hana::partial(unfold_right_helper{}, static_cast<F&&>(f)),
                static_cast<decltype(elt)&&>(elt)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNFOLD_RIGHT_HPP

/* unfold_right.hpp
wodU/gmt6gfJuWS7V2JmJoost3Gav5szKnPR9batukbE5uVInUuZ9zWU93FDI2Tf6YDM9fLESny030R5hQoYC6brLcc7m9OYcgdkZ6fz44h4DxDMp7MxMGRpk/h4UT/uvJZGpBvgVOgu3nMV/aeYbBoVAiHKfMllmuRpDoYfFjo6plQ91Kqd6uDGJRyVxRncKaIejJP6a9H+itXQfMMd8VHOSfkJ5v96qLvlvf9jyu+qa13lKzHFMUDViM4VantpiR3GJnqk6avKVm6J2ZYbG+aFHAOIHVfWkS3bfFjo7ZmUSommkUu96t8HJS2LiXd/GNNV6JSsafqmtqpPbU5CKZUUftvjsREU7eG9PdUzMC06r4wLfjAZW7m87/xWUW7FtKw6IYaOJQgFgg8COtANZzqu2Ga2uVJ93DMpaj0Y7rM+kl0a3WXRl77U+TTEGLuu9APxqqnr3te5b7CG4xEqvUAC/0N8Zi9PdA1OdTYEiXgYS+M0B1WEveYVcGxLE1CpaqnrRVSX7JgaBi/bkGBgdy8jX6IKkDavOJ3TYRt0PTWvP1QXr1kvtXKKdyysZCn2hGT9uzTNK/hZKv9YXXnXaj6wRm1jTAH6PRY4T1WtlbHDpC9Ta9OHVb5sbP9fr5usPbUdBPTDlTW51hFFnnQmnUfv89jSZ7yWXSuFrqcxdBMgJZw6sh5G9YiOybauG+/q/6lSs2UM65uK+jTM9bxuBB9xWFJGLKIAcYvwfRbyNRuEHZSv+ygPbm2z4zXixDfxs5P+cE5yqbwlADjQIPqWUC3CHuFcX/RJy6Su+85Ww//UJy9d9snNH1f6LkqtBmeVW/OO1sbRX6Dyj5MdN70cZMhMsVjxhbhMeYVhfV/xXlQ9mbtHVDfoDATsShPtPrq0Lcs+LMoWrmqUGeqIXprLnqPvFuV9vLK96YVUkRcKKnMxvjLzYt49KcK1IGI5BLfd2V7wrMNkM4e7eTbZSbm86x7+Wnpn/UGq9xKMvX6wLQ/oYo+/8EpAcMv9hXmBKP91doDxarSI/JmXYVwO5b3cVVXjdG9plkdM4bhAv9VCRmrfmc5Y0J/aCQLaRu8+3CLs5T76YTFuWmb6ptJWaba2T0Jv5G6x4Zm0UXu/cv/5Z6r3opDt0HolSJ2Sf1Bu9z/K8WdcazrfAv9q3QXen10scuLxvhuGABN4PVyKzfbK8a0LXtUobo2XbMvt+Gpbl7z+Iq2LEU61RmrWu0qu3JM+u+DVlZc9r2u2e342X42XobzcsaY3jW2Hih2EbzTO7FHu4mjCwDVlGjP4ukJPzWpZBVRYDC3BOWz9Vg7vYN9T6JFM28G3rezZloJwAwi62DF2W23WlVCILc3zOC1kNXPcd1JIx/bStg1OMymaeTr3VZgnttAhmPBVx7WQbG39I7gXhhgW+EqXSuzHrut63zjPDnB/Bgt+2Negm1yaleEGjW3gHHqB6uGK+eB8bJqG/WcIO4x1k1T+orW1Fo2vWQrXiz9wPkOf56LuLXNNbWzL1bTuFGcyDJExnm25V3xdUfee+VY3vmpLHMZTGGgYZxQf4WIwnbPeR/VdEkpXTlnOaIagp6HvAuV9/FC3sq7aLrc7uMGU39cnC929l56LrmMRcFDycqx/hfJKweqBV1VvW+wf3LGuwGAe70MdN/MYeXzZz32llZO8X9UTuihDAj+WgFFE5OIipvkC1dmzulWVVbpsOL52Gn9K5XjNYIzBeJU9eVfpjEc9CEsdL5ro0NY5zd0UPx6naPqWbV4fHz/BE+vUUBW42XoWP9/xcIQ4ZVfipWJ0eYz9gTaXoo81U3WtFR/I2esgQSUgvhnMeEUJhb4fFvpqpnxVOeXUUt/WS2c=
*/