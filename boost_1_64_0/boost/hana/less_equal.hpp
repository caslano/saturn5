/*!
@file
Defines `boost::hana::less_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LESS_EQUAL_HPP
#define BOOST_HANA_LESS_EQUAL_HPP

#include <boost/hana/fwd/less_equal.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/less.hpp>
#include <boost/hana/not.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr auto less_equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using LessEqual = BOOST_HANA_DISPATCH_IF(
            decltype(less_equal_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::less_equal(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::less_equal(x, y) requires 'y' to be Orderable");
    #endif

        return LessEqual::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct less_equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_(hana::less(static_cast<Y&&>(y),
                                         static_cast<X&&>(x)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct less_equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::less_equal(hana::to<C>(static_cast<X&&>(x)),
                                    hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LESS_EQUAL_HPP

/* less_equal.hpp
xE0C3A60ugS4/ACCe6lBL7I8P7Pxtm1Q06PXPAcjlGYUnSsMvsVF7Lj4zzpJdLr6HqZBJ7FCvIYfB+gg9QvrMjQ07lvIN9/ki92KN5ai9RWDFq7XIF1IGFu99p2Yb3A418eFKjtIikLRGvTEvUgsht2tzUWSB9wdpTe7rYaHfYOHiePgUlQVWn2iN1B96zzGzIPiuDlelvcVD4eQ9e5Qy0Z/fXHYPHCsaF16mCHfkA7Pwyuwp4nWUI3XPoNWYBWek2W4dUe01teWthYxSFM0k/R9Yf1Gx82uBH2q3vFs3kT9inzrp8RlSrHro9r1w6o9vV78ZAwM1oubU/lfZLlTsOnbU2Wvfi3K1PyWJkJT9vCfibJZd1JXbMr+8FNRBjt3TNnjZb3Y821V2JS9EWVoS8Dbou/zGjzMrSB0E7uocou6NjOl75LiEu4E/uSLZ/GP/QcOK35eTcnaCQOXi5wRuEfrBKG6s4kfcUaDoq4F8zs1E0rWHmO+IZF54qllajxqohGK9oyym7KH8/s/cRr6WOx8okzgt8b9mnvs3UG/0p2HO9xW3ZNx6Hd1P8bTv19V/u7T7+o+TEC/q7swJf2u7sBU+vdd+B3bHvpd3XnBe6G0PlwV68qEIR/N2nD+Z9R2WKRN0xubac/H0H5990feHRocU+vBgvl2f1HgWeo8CfBY8eKpbjMk+BFkhBv/LCiByiTs85lJ+d8hqV91jhzg5fe4vSzB7WQkeThWP2KiUCH3Cqio0e4Uauwi482OFNdmK3E7EZ1c6g1a+RZ2D8z3vNO4iELPjdRbzzBvtxaFRquvRYIuyC71tlE0XGV31z7XNe4HR6WNRSHEtTzxfmhNckvRrAamDs09kV4jyS2brwW4zTwutRSj+SaDZpGGle2EJWg2aSW2dA6tgXmnFj4i+AZTW9AU4DuRQ0YTPTf0uxGga+RaKrMsiMTt3CNE2+zvrpNcTlIL118jHCfi0nmPLqxi2wOiuLLOnsdXTWjen5g+yelGeNm/QE8EWc7mzpTmM4f3cQ0ZbK6q0KTb6izluUBbGrqdzSsxulhZfVglAW67ErvadF8KXvN5gVQ+WQA7w+Q1qo/jNrsf+2GO53AcRQU8F7bFqWrYTxuwVWz78Ol5FlypzYAoWfiCIfMp7CwcGJRRQjlGYAfpe629TdFamA64VI9/Ad3MtHEP8xm7GC6YVLirFCTo8/LW+sIKngkChxV/enrODTn9xIJuDdMocSx7OOxu9IfgPgZI1ZZUmxloNW/3V0NTrycJ8sgFSJiA5RpvRaEP5lx/hEHXxlyPCq/AvPPWBrAczu40zbtihEBX8Rqiweddgv9izPV+Dxd/yYbbVDT7a+adazwa4CM1ibh+DFmjKugv0VlcXsbLwPIWNQpB01Fzfc18ayOO0jwOI98y7tbWnVZPjBDf+4pfn+Y40GvHC8Azi5R/8yCFovkNwHO7Ms4ceEhwWZg/9NN0okEAmko+LgEHk4+8wrRNM0cRXUFv1bxd1ne2H8npushFF5bQj6FF3asrwR7bWBtSXa2b9qGu8Q5FlDo5VvvF7eHqwnr3dHfdlIn9gDfeziriGO6sQNES9eAs0Z1V93JBHiLRyMQ8x3MoR/4Px4HluDgcrimurD5AyaHRvxjJeSoIUBS1+Nrt95bRzQaB2ied4fVBxIvdPLfdTDFVZIxhg7Gm6D4D9Yz3aZLEzdIKO5czuOtfJxLsdjHZWwjUWL4a9XmekDz0kE0hVmR5wpiBGssrDJq4Q4+0PD7yi4zQZLW1vPK6Rwo7C3Jk51Dk1vpq7LW8Ap7LaxlXcZBU3gituMLA1r5stZdSvL1k8hZKJfaqAIYsvHlQgQvLGHyMkOo=
*/