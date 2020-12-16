/*!
@file
Defines `boost::hana::unpack`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNPACK_HPP
#define BOOST_HANA_UNPACK_HPP

#include <boost/hana/fwd/unpack.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/at.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/fwd/fold_left.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/second.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr decltype(auto) unpack_t::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using Unpack = BOOST_HANA_DISPATCH_IF(unpack_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::unpack(xs, f) requires 'xs' to be Foldable");
    #endif

        return Unpack::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    template <typename T, bool condition>
    struct unpack_impl<T, when<condition>> : default_ {
        template <typename Xs, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, F&& f) {
            return hana::fold_left(static_cast<Xs&&>(xs),
                                   static_cast<F&&>(f),
                                   hana::partial)();
        }
    };

    template <typename It>
    struct unpack_impl<It, when<
        hana::Iterable<It>::value && !is_default<length_impl<It>>::value
    >> {
        template <typename Xs, typename F, std::size_t ...i>
        static constexpr decltype(auto)
        unpack_helper(Xs&& xs, F&& f, std::index_sequence<i...>) {
            return static_cast<F&&>(f)(hana::at_c<i>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, F&& f) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return unpack_helper(static_cast<Xs&&>(xs), static_cast<F&&>(f),
                                 std::make_index_sequence<N>{});
        }
    };

    template <typename T, std::size_t N>
    struct unpack_impl<T[N]> {
        template <typename Xs, typename F, std::size_t ...i>
        static constexpr decltype(auto)
        unpack_helper(Xs&& xs, F&& f, std::index_sequence<i...>) {
            return static_cast<F&&>(f)(static_cast<Xs&&>(xs)[i]...);
        }

        template <typename Xs, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, F&& f) {
            return unpack_impl::unpack_helper(static_cast<Xs&&>(xs),
                                              static_cast<F&&>(f),
                                              std::make_index_sequence<N>{});
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Products
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct unpack_impl<T, when<hana::Product<T>::value>> {
        template <typename P, typename F>
        static constexpr decltype(auto) apply(P&& p, F&& f) {
            return static_cast<F&&>(f)(
                hana::first(static_cast<P&&>(p)),
                hana::second(static_cast<P&&>(p))
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Structs
    //////////////////////////////////////////////////////////////////////////
    namespace struct_detail {
        // This is equivalent to `demux`, except that `demux` can't forward
        // the `udt` because it does not know the `g`s are accessors. Hence,
        // this can result in faster code.
        struct almost_demux {
            template <typename F, typename Udt, typename ...Members>
            constexpr decltype(auto)
            operator()(F&& f, Udt&& udt, Members&& ...g) const {
                return static_cast<F&&>(f)(hana::make_pair(
                    hana::first(static_cast<Members&&>(g)),
                    hana::second(static_cast<Members&&>(g))
                                                (static_cast<Udt&&>(udt))
                )...);
            }
        };
    }

    template <typename S>
    struct unpack_impl<S, when<hana::Struct<S>::value>> {
        template <typename Udt, typename F>
        static constexpr decltype(auto) apply(Udt&& udt, F&& f) {
            return hana::unpack(hana::accessors<S>(),
                hana::partial(struct_detail::almost_demux{},
                              static_cast<F&&>(f),
                              static_cast<Udt&&>(udt)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNPACK_HPP

/* unpack.hpp
NuCkSi4ovnXgnPFEk1WAocDdDuCoGSbSrG7k424I1+LzQDwX7T5kI4pVpxMunZY3zUTVCftZu41mf4Jyzrt8yDjRF/vEm3Y9IlOK1hvQsTbGGOWYE+5F7TZjP6UbVoc+sHmRKBAzpYLtjewQ+iaIJ0tXw8ab9t6z+0PvseK8ED1BF+cNNYyn5MYTMhfGs0GLRY8M6HL/u+/ZY/Bir7UR5sv7JczHE2EMhziKPd52mFesG2i/gX1juH5mrqGf8qJsrdvUHkKvhSqtX7RfmzF1SMD3BhdqnJqalEJtg/tgD/I2PSf4jdS5USH0DfYGO3+Twt16ECvPVhF7w/v8jvjUmunHPzzLw8rz0xnk+3l2GEfqhcRMsefdAnwXr4f5EsjYxKIzlziw7IEf0Inwt3L/J75rIOfOs3b+LiXW9Btj8DQpOYGqwpt6TZ5MxJv1uvcOYWOG/4Isx/1uVd2axbFkE6G2h8+Uq+abu89O+qYxUouY6KtVtP3h8Dd0oylPug3IeLheal6YMzRKMd+UZH/Z35j+wjfPNrIerhfOv68x+4IEXKcbhURvqQUGvYZiIJ9XEtojbyfqTXbtpHMoXz3WX2bG89k7fWuOp/SZkM8bCd8pLSSqiD4/Ga4jUuvJsxry/7h9Ho6KtnXe7r7hyGvTB1PPGvuNzgjBPmQ1ur/Ed+dFWbuJrIb+CX7n47FvlH0n8eTs0G6ZJvH4rCGOdfw36Hb6Ct9cD48p5JsEyBjv15DrKyy77p6/jfNBqO3Y9zMY82cjoPtxO0IVx5oSbqvY0jIcdfgQ2unj9XxBHW6FZeOUtrJ18b50mOc0FBftjKOMF3Hf3QjWezDQuRC2uhd5fIawk43D0yZFgXFmG4flQ9RqHFtvjwkCq+Fb6dPD2QaE/N0J9Md6WI+vwVf7OYFvzHjzNVO83t2y24eUUXoSMVrpK7O3m/XbYPZXsFff9Xnq3T1xpRgYg7vny4R1njBl7vPLxJnCYO75ZRqHHuzPS36/6DOBlcOiARucXz9379+CvvTHSZ2wMOdH1JNbNTb7rqHO7jfLxQWVbkPuVf8QwGCi0Z0D1WNbFQ8b/4kwXpzlqKrabhDAQmjFee1+AIeBl7iEumqjZXyOcPt1ealEQocLbcS3ufwKpXyubJkR0Zbpk0EsuBrcyWRcuynOjqnnBHEqY3DsvxnE8AGu3+4NuX7IvSnaUsot6UsoMpCpL3EzFOPnJF5mU5JwwmMuibosl3JFBaNeZxkhcgU2T7HOZOky6eIpXitaHTl/Jca/mKoY3Pln2Tgt7MAdM/xE3XRmPa4WcoqcsOlrutLwN+Yxe6+5ZKup17dr1fxK8Uzk64m8G1/n+zmm+5d0Mb+bh+PyBjpLOTwyRTzc+8fd9zX6l3rD7lJWyMy+A+DLd4jIPJeKfacnHrIxJmObxl2CneXRPs5k0jKYOwEMpzVD3xHmCTYGWfN0eWYMbgd40c+L0PvPtOnVCtW6UmI2mDM+Bi3DvaHdfpVsTGbPu4S9hY3zMvURZAl2OB/rJhZbgo56so11gG3YQY9YOFnHVdi8n+ZgzmQqswoiz1RBTKlcOFtT/ArFhWX+AufCp/v4lysEnz75PrKGMZkIY6n8IWwxTvk6KxqBRF6bp9gYnfmlUlouqvTiW5ClMO71K7lKNSVwt55o43IZ0X3iPvqOh/NzLcIG52PPlNTWsTVUtuYu7n0dXLaS5h2myi8JO5GPkRXs4m7Kx9kVFGPRO+Rg89so12DOexgNEXU793gbk1mqyNFvY1z3C5x8TUHwOmnVf9XOpCd00pSN8+aE0RHTNg6Z99C+x0l6ParT8vzrcplqfBbZa2Ns3Svm32NinMziSaQy9hE=
*/