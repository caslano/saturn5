/*!
@file
Defines `boost::hana::concat`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCAT_HPP
#define BOOST_HANA_CONCAT_HPP

#include <boost/hana/fwd/concat.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto concat_t::operator()(Xs&& xs, Ys&& ys) const {
        using M = typename hana::tag_of<Xs>::type;
        using Concat = BOOST_HANA_DISPATCH_IF(concat_impl<M>,
            hana::MonadPlus<M>::value &&
            std::is_same<typename hana::tag_of<Ys>::type, M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(std::is_same<typename hana::tag_of<Ys>::type, M>::value,
        "hana::concat(xs, ys) requires 'xs' and 'ys' to have the same tag");

        static_assert(hana::MonadPlus<M>::value,
        "hana::concat(xs, ys) requires 'xs' and 'ys' to be MonadPlus");
    #endif

        return Concat::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename M, bool condition>
    struct concat_impl<M, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct concat_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename Ys, std::size_t ...xi, std::size_t ...yi>
        static constexpr auto
        concat_helper(Xs&& xs, Ys&& ys, std::index_sequence<xi...>,
                                        std::index_sequence<yi...>)
        {
            return hana::make<S>(
                hana::at_c<xi>(static_cast<Xs&&>(xs))...,
                hana::at_c<yi>(static_cast<Ys&&>(ys))...
            );
        }

        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs&& xs, Ys&& ys) {
            constexpr std::size_t xi = decltype(hana::length(xs))::value;
            constexpr std::size_t yi = decltype(hana::length(ys))::value;
            return concat_helper(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys),
                                 std::make_index_sequence<xi>{},
                                 std::make_index_sequence<yi>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCAT_HPP

/* concat.hpp
luv/ZyDOQmHaPlinZNltJ1G2g+A2KFwdvl+5/ncm1tsVniMFb1TlskUjW4yckGduv6Jee8AeUNiOnG7cMJlj38vBjJyFOU8Js9Gp10bjuHajwL5+IeMfwe/y8MvsSubXoxT1XHM25pcl3CabW0vyZdxs2f+DfZDKTvLrl4h2te050C5WeJjyaKvXW8FsU5jYxIGuUQ93/XOx3ujDjZsGu+aDaE/Twb1B5ULS1ek/aIcUc56l//88rB2Nzo4VCsfnTGb7Qsb/gX/raHwN83q5/nk+1gbdbK1tuxPMFheT5AatFqbh3E/p/wO32ctl5omyTVyAeBSVByuDu2+U8f9gDilMW8rUHg/4zzSS8S8Xwl9SwiX7JpVP0cBvjcLsbUrwe8Ef85Gbr3sc3lXYPV2I//Hkv0zJP3oR9v01Mv4Jz/Dc6M/AHkcs838R4kwVtmIKYO2E6OTZ4T5jV+YfzzBbfYZGkXX7MWhHBm+s5Z7iXb8Y+1A+GpU9JWamnHKIF9l1hMRzfIXneHj0MpBVoeM5RHvIX4J9SEp5eF5F5eRaPbb5d3iGdT8c9Rm0+GUEP38p1iVG52PE49XzlvkH/0SVD61DIxG2Blwjq2GtQub/MvhpRucnDI3878DfWOVbs1C8CdAsiReZ11Pl+t/l0Jocha8j1kKu/4E9S/o/K5oimtaI5PrfFdijrDL/hfWhN8AtE2sXlYceQEOeFV/O/m4L5v7T0LYWKMyJ1RN1xmPNAXNbL5P26XDrlUv9mysRm+Rh6mi7Uv8GzIN6BLMuWsxFK5rqdoxS7E71gdWNrFyR1zWvcriV/ZJrvzE6bLZNhSYImIsHR5hmoS2VLPKewyTy+At4Kyhlmy8Y7aTLZsaYz1gQeWy7GjozvZKpJU5b8BaC99NnkofQB147Q5TphOmwMz4e4WXbM1piSzYUPjAwVx2pR/b4K1GeW10D7WCljdIqD8Uh8e7jELzp4C2t5C1ViJ5omDlWntR/uBZ20iIXj5poxuCO+RR5PBnM9wddzFyC2cckeF+BN33BCK/NmMq+P17YPm3XwfZTylTEsomS5Z4Hyvcf7HV7JFuLnS94NTPgM1XySoYte9mKd38OeMNK24ln9LyLm18P37fSblqy5W26YhCngVfT7+IlDOa4DKl/ewNs9B4XryXFXHeCVwRviTI2EYy9rUj9E/C6lPojl5AWm0bGP9/oMHdVxvsDq+uqKsma4h7zBXMemNt4mRrO8pHxD90Oc28v0zlDx9QVH/YEuGVerobYANFut70JWvqDkqlFy1bksRu8T0d42jRsZfzzzdAjnC+YtfXR480U95qX1D8E74J+hVc0CkV7SzqvrSr1/8B8alBhFnLxKZYOX0uK/Uw7UbbpWxBP/5mXyxtTIuyPYfA29/KihbZcezpB/oGiybyeKPu/W1GvXraGczFl/wfmC4OlzGRODzN8G/ZqzVeZWXtql2RuR4I5F8wZLqbhvDLMmlry/KPb8c585GHGKWC0JRafoqGvF+/rLLDn+rO17ZVY/w7odbraE01r02ktvC7w+lz1aoUC68nfEvBe+MjFS6bSvOtDot3mZ2KvnatPsGQwskZcU58wCOaMfhczFo8b7L5YUa6RO6HfqNYjrXFwa+0J3gvgvaHyaK869/q64O18F+aWC1y8AvcZDoJ3K3jbqPmze1he7RbBW/NujNP9Ki+nTUu+C7y5gyovRp77aFuOBGsNs0MLd8wsnOfcp3DJaddimLbJVzT06CucDO7+Plx6TbTNyb4Dd55azmS867DBRF7b7sG+zX43097g0dKe5M6r9P+AO3O+h5vk9ZFI/++96NtLeKk09xqJYD4D5gPe+ky0mjHmMVM=
*/