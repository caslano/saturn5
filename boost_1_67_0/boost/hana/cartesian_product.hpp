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
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
*/