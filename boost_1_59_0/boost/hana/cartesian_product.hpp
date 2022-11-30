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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_CARTESIAN_PRODUCT_HPP

/* cartesian_product.hpp
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
*/