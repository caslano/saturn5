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
33+Cvcw7brb9uifW3yejAd3wGzRZPeM9M8+Uuey1IWmNzQJ7JTdb8WKpfL6/qLndmxPhVv0OPVgfF/ZmupjPUerre8C9zMNN9KXV/IrnbbE6dl1UXf/lD/jC4x52Nnew7Hq6Adxl3DZDRMiW6UsVxO7Dyv5ELHg8wBapBaLv/8B908tVfrDSQBBYT9TXy/yF2OOEnyvno2n9G7BHAjYrgwV94nn+hq6mx2bbI3Pe3zLHWYl7GLj1Bq7yDtjv0mmMfwV3GwPXPh3tkeaNrW5BNv8DzXIPO9rYsn1zxK6tZDfAGlBDXsF9Rmr70YabPG0o0ltblPZwrk/gzkbr/yqi7SMZ2BL6zsSdBrfTyJWLVSXndLgvj3u5O1Hhsk2LjpGMzaNg//m2gS24n3TM5XAXeMfE7SkUcjLcl8Gdy8QViLuSv90895zOr41ce0H3qFi+JXVuPA3+Nb65rTKElFAQf80s4lbP43APMXEF59c94A6auALjrPNf53W4tR+buGqc1b4tFS+7AeyC22Y7FayxXiJ3Qvt/8zncNg9XadQ31hU3T/b7UH3/C+4uZq7I3aS+/53fYVeOELt2h1hhoFCR7dxPinksmLsM+5gZfl9X138D844PXMx8poL73b6Ofy7g8DZx96vqU0kbR8Bc381UvIo8r54Y2di8oMNbxceTmDtk4yNgrulnpnltpD2hciH4cO/M8Kg2iTLTSjDXoNH6z8Qd9nNlfLeyhR1e85iL11Kjyjcks6pwXzqWz/YVLN61ovc/sJM0pjr9N9rW1CijPajznxdx2NOfmtj8WnzkR50D7qiZa1dU6++U06VeYlGHP2nky34XDYH9tZHN/12k9a8Wc7g58zzrlupzsnsQ/LuMfP7vMrJ7jsUd7tvm/u7corKo35dNcvtVxB8Ef7+RUH7SEuTPsYTDT9N3qfl5Abt/twX5O+D3leaL+Hna/0EbcrOpDcWKZvxrTfs/Szq8w7y8dFYgz5vW1wSYQ16mWtcy9VyIu9tSDvfoABeV4phjf8R9Hdzj3wlwVYpdp4qI8O4nNJe2XdrhHuixl3//Wg28W8CrpP1rx/rNudeJfv+4DMaSWI31Ebu4CyROJWoiaf17sA9zsyHwz52voP2fZbFm3EzBOkxk6xC4zcRt2LGmLrZzTklAsu+BxPwTzO08zEaVsKguM5iZtFbSyznMdg9zu1SGuUavfv8B3tZuntAdKDE7lneY27qZQveQtCfMAvOKKReT2T4d/10Bd8uUb7p9pCXSXtNsfx8J3Dlq/S9wz5lt4NrBZztdnn296PzPFR3+zya7BcZW3/+BO9d7Bm6U32chbtlKuMs3cvnPN9ojzgD39/fBjeyi0vR64ty1BYk3x8oObzkfT6q+YAG8HT5x8fpSOas3uekW5bxMGssvwdxvzM1UkQlVQxfeICuX+navVRxuvdvW3mSigrlvifcyePt96OGx+0fEq17V4W3jtY+9JpB+/wbeHKMuXreued55sKquwv3dSOzK1eAbjfnYiVSux+oTYdP8vQXsWe+62EkrH7OS1mZK/CQuFFdce3WH+5CRm+jkzlsl7iXgvunmxhVXbYK2uULcZcoc7nmTQa4yV+zN3yngvuy3d9OtKiTtnWcNh/tsgFtRJcHdgvx9cKs+cnHblKoCqd73qRsg9UeVTsf+flff/62JvatkG/hrjWv9e/A3DuFL2E7j/ifYFWY2e04dnf25tRzufKN+rioIK+Q/ToNZ5rfVvs7nr3Gu6x+u7XDX9XMF8r/1+z8wO4f9TDvfRokXyXCb13G4I6NGbj03l9bQ8+Au4O9j5zvMKUnLXD+D2PXrImYzFsJWWi1S8blZYE+GsCV0Sog=
*/