/*!
@file
Defines `boost::hana::div`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DIV_HPP
#define BOOST_HANA_DIV_HPP

#include <boost/hana/fwd/div.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/euclidean_ring.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/value.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) div_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Div = BOOST_HANA_DISPATCH_IF(decltype(div_impl<T, U>{}),
            hana::EuclideanRing<T>::value &&
            hana::EuclideanRing<U>::value &&
            !is_default<div_impl<T, U>>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::EuclideanRing<T>::value,
        "hana::div(x, y) requires 'x' to be an EuclideanRing");

        static_assert(hana::EuclideanRing<U>::value,
        "hana::div(x, y) requires 'y' to be an EuclideanRing");

        static_assert(!is_default<div_impl<T, U>>::value,
        "hana::div(x, y) requires 'x' and 'y' to be embeddable "
        "in a common EuclideanRing");
    #endif

        return Div::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct div_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    // Cross-type overload
    template <typename T, typename U>
    struct div_impl<T, U, when<
        detail::has_nontrivial_common_embedding<EuclideanRing, T, U>::value
    >> {
        using C = typename common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::div(hana::to<C>(static_cast<X&&>(x)),
                             hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for integral data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct div_impl<T, T, when<std::is_integral<T>::value &&
                               !std::is_same<T, bool>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) / static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over an EuclideanRing
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C, typename X, typename Y>
        struct constant_from_div {
            static constexpr auto value = hana::div(hana::value<X>(), hana::value<Y>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct div_impl<C, C, when<
        hana::Constant<C>::value &&
        EuclideanRing<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const&, Y const&)
        { return hana::to<C>(detail::constant_from_div<C, X, Y>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DIV_HPP

/* div.hpp
v8nmu+L6VrHfgcr2WF/Locl3db8tV1/y8XH5v6gfNe24WtqxSp1311TMLvzx951cfeccQ21GM+3Vxmm+vauMdh0BfsV4pYnhenJtc8dWRewG2iEVFFsVcd7OieEL9dt2a281t2+/DdLe4qey5KFQfmafcfa5UL3OR59JSZvft8dWknx8bP5Ev1ujypf1u0ajX/NZvOalbaLnbW+/o3G8f4ae96YdMz69+cCAPWUHFn198uGwSce2DaSeNw09r3xh7P8fC2AXIz1COhj/dpDfIOaz8kg7pfwy0VkuF13kCtlzbbXobdeIDnY37ADYvbDDYQ/Aatn7bSbsIdhdoq/dL7raq6KrfSy62lewp2HLI44zsNVgz8LWh70I2xr2MuzH3oH8vm6ym8wN9JC5gZ5ynI+0Uo4bKceVQJoqx9UU3XEt2SuwtuzNVge2Mmw90Qc3lHZoDNsCthlsJ9g2sL1gO8AOge0i9TZQ8pyT59+C9967M1ziHZGjY70t5dt9RMfaR+LsK4+0fqJXHgzbFHYIbEvYAbC+6EUXLCiU+y6fd7SgI8cb7eTXa0IfjP64LrTdmELva0M/0IUuQF07EMthpHXIrxn/Vie6ZfyHOtFTCz6uFb2Nv4te9IO9i87Bz4c6USTzd61QRyH1fMHn3w/UFWU+tV9c0YVZfWhN2NZII5GWIO1AurSQ806EfI6CSBWl/z+g1/DBvQa2atnMLKwHzdBnLwJ7TsWUwm+gI+77ffaB/QYPUPRDP/RDP/Tz0/20VPmtH4wRWY49z66RVf3CoUFmCpb6Z4Le2o3mBnqojCeafuVPq59+6Id+6Id+/m0/hJD/i8/1//HWtXeeH6WQ5kz8tmfQt/gghBBCCCGEEEJIOhREqip999E9ho8aPLLfoF4tWjf/3jHEP9VXDZlDK5pPWU7Hc2hz9JxQ2/10U6lvgdR3Iqe+Kf7C1Oq7LfVdyK1vjv/T6/uZvppJ7IfyK8vVOHbH6eGEvp7iTfOmOKI7F702IYQQQgghhJBv41P9/0/O39tV+9/eJ/wWP4QQQgghhBBCCPm5FERqJP121/eazgmbYtespth8qSk2CpunYWe3aNqiqe3If8fcLn1zfIMQQgghhBBCyO+nIFKzj/d1dd48L8jkzdF57O8SQgghhBBCCCF/NZ/p/+NFSzpcGEZ6Trb7/wPru9P1TwghhBBCCCGEkC/3/+t/vH+ON1H7OT3zb++X06/4lf3t1uRTlgkvZH87+47tPD3fmZOZqrmvHSGEEEIIIYSQ9PjM+v/ZmSnubP2Dc/Px3u7rpPTopO+LpfTTvOnRjEC7U7NVKe7tTgghhBBCCCGEpMJn5v/nuNGMH5z3TsdvIxlTuCGlqyZjCmZCfW6oA1OFDviuOEIIIYQQQggh5Ivz/8HcvMibo39s77/a0ldfKaVnxH31CL10L8+Nsrr3VGP4W33XkLY7mk9Zrj2XttMLvEil3271pf6e+ZWlwjvrFlzfd6KF/i+5ftk4zuWX0jlxzHCwjQTuJUcv0OoXtEmavrvH51lAWYYm5xno6V5ozjIrl3GsXsacsuNG5mZwkJ092Z0yK/XzbykxTi2oLC+ffxBjJs+GNG1u3pTIy+Slf03i+/SuxNQkaTcvz4vMg8b5JfdG/KzzCylL/Q/iSD+G+PoUlGHPp89zY/Dc2d4iHV+hyJ08W/+CdmkrMW2RmB58LKY8Nwgy852cTWdTj6uDxNUOBxlqJtdruo7i2D4S2K+4l+Jn/2GJrWUSm7l06df/t/qOnwXPiypL/qTdUEX2aflLrl+avmNN5a1iynLn+buayrlB8nVyg+nzUj/X+F6dWlxZir5tczR3+t/j+Ll7W+rv/7Y=
*/