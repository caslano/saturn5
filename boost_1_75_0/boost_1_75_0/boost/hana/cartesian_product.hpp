/*!
@file
Defines `boost::hana::cartesian_product`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CARTESIAN_PRODUCT_HPP
#define BOOST_HANA_CARTESIAN_PRODUCT_HPP

#include <boost/hana/fwd/cartesian_product.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/array.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto cartesian_product_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using CartesianProduct = BOOST_HANA_DISPATCH_IF(
            cartesian_product_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::cartesian_product(xs) requires 'xs' to be a Sequence");
    #endif

        return CartesianProduct::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    namespace detail {
        template <std::size_t ...Lengths>
        struct cartesian_product_indices {
            static constexpr std::size_t total_length() {
                std::size_t lengths[sizeof...(Lengths)] = {Lengths...};
                std::size_t r = 1;
                for (std::size_t len: lengths)
                    r *= len;
                return r;
            }

            static constexpr std::size_t length = total_length();

            static constexpr auto indices_of(std::size_t i) {
                constexpr std::size_t lengths[sizeof...(Lengths)] = {Lengths...};
                constexpr std::size_t n = sizeof...(Lengths);
                detail::array<std::size_t, n> result{};
                for (std::size_t j = n; j--;) {
                    result[j] = i % lengths[j];
                    i /= lengths[j];
                }
                return result;
            }

            template <typename S, std::size_t n, std::size_t ...k, typename ...Xs>
            static constexpr auto
            product_element(std::index_sequence<k...>, Xs&& ...xs) {
                constexpr auto indices = indices_of(n);
                return hana::make<S>(hana::at_c<indices[k]>(xs)...);
            }

            template <typename S, std::size_t ...n, typename ...Xs>
            static constexpr auto
            create_product(std::index_sequence<n...>, Xs&& ...xs) {
                return hana::make<S>(product_element<S, n>(
                    std::make_index_sequence<sizeof...(Xs)>{}, xs...
                )...);
            }
        };
    }

    // Credits: implementation adapted from http://github.com/alexk7/hel.
    template <typename S, bool condition>
    struct cartesian_product_impl<S, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs) {
            return hana::unpack(static_cast<Xs&&>(xs), cartesian_product_impl{});
        }

        template <typename ...Xs>
        constexpr auto operator()(Xs&& ...xs) const {
            using indices = detail::cartesian_product_indices<
                decltype(hana::length(xs))::value...
            >;
            return indices::template create_product<S>(
                        std::make_index_sequence<indices::length>{},
                        static_cast<Xs&&>(xs)...);
        }

        constexpr auto operator()() const {
            return hana::make<S>();
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CARTESIAN_PRODUCT_HPP

/* cartesian_product.hpp
eXuHAH3heNPS7HCWdobNltP/4pDvBP97ydeJu2sb6t88L9t/g2qWf1vyxf8Pz6tp/t3Uwc78XzSv5eMH5rFiq5WUqiXZepnRFKZNZSVVvGvKCWZCeqnhb+50yTpXGvOkwxvj5zlMOuou3yt5xRSY+PNp3sp/Q6tsFpVvVMykscIXQFOhs8JqlIpHl8Kat1N/8/3Gaj1fhnR46QKcDqBkTiCMQIpGhmxvZWc/erzCXgRcnpdATU+TW77wGVCx4P6f1WcAg97lVYf4pGbWNEalUI/IQZOyjgd/L6VkMDL28hmy3TDp+sqBWwBBgLcoqhF97vvaPzlSbftHG2ovTszB/B8HOUpGJHBGC+naWp95v3gwazUKSfLtp1lSeeWVKd+DFHBgajubxyvkj2KX7MqTeLbqhjhFzEr9pSmFfh/19N5Id5++HRVb0w955ee2qBKE9d3IoEs0dahQARKONgnWMtst4y2Tv3K/kZtwcq65hSAvqka8xk+17Dzj1zCmKoBGr6mQTznHQXsjf3Bnep5fEuF3pOQFM4xAbIdUDkVGUzMEbwEXdFS6lHD6cch+9I8P8K0/Gu9PI7vIfYTrGJvznrd21lIGBiXiwCU7fFcGRzyBKgbsM4ZUIA4nRi/6Nt5jSdsUakTEn56yelYIPqe66HGYw4eVkHRwrBiSRTzhoDgtRkm8xD9dSSPFoizGXz/iBEQHKCDh15LUotUS
*/