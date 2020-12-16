/*!
@file
Defines `boost::hana::one`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ONE_HPP
#define BOOST_HANA_ONE_HPP

#include <boost/hana/fwd/one.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/ring.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename R>
    constexpr decltype(auto) one_t<R>::operator()() const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Ring<R>::value,
        "hana::one<R>() requires 'R' to be a Ring");
    #endif

        using One = BOOST_HANA_DISPATCH_IF(one_impl<R>,
            hana::Ring<R>::value
        );

        return One::apply();
    }
    //! @endcond

    template <typename R, bool condition>
    struct one_impl<R, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for non-boolean arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct one_impl<T, when<std::is_arithmetic<T>::value &&
                            !std::is_same<bool, T>::value>> {
        static constexpr T apply()
        { return static_cast<T>(1); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over a Ring
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C>
        struct constant_from_one {
            static constexpr auto value = hana::one<typename C::value_type>();
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct one_impl<C, when<
        hana::Constant<C>::value &&
        Ring<typename C::value_type>::value
    >> {
        static constexpr decltype(auto) apply()
        { return hana::to<C>(detail::constant_from_one<C>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ONE_HPP

/* one.hpp
Apv2JrCoLlDc+TOunZpMai/xKsQ0BBoKMLh5MJooN3oTl4jF8LPjfSuOJ/RUfsW0ymSs2sSMYYBLJZc8Ob+ZoostlnB8gQpSWBVRXPpCuWXrehivvtcu8Pa7y+3Qx2d6bxB5UGRxg3HDE4m+G7OxN4GTFlkeK7IRPOPOo5RJIH0vap0ujUvKSTZ/+qfRDD98gONB74soCdJAzqJph14JKOi2l3raBaPjh+867clF4WdNFgGhi4hqmmHisRjvSvYuZ3r+TWmY53kc9nHtHxh8uJ6p38ybu8ZFvo8P7PnTYC1nRdVH1WX/wrMIFNVqUU+ASdC7F8cTJCJK/TypssJFZHfAJUjqh61frxL7GJ5XOXgCIfO4LGQ406CDjcnY+tm0FrD7YNlu3j7q4MlFnHmeFye58IqmYm9g7tPY2afq9zLBcgO+jecGzGVcFVVZCGUhRrGYKDfsA905rvNa5R4uZmlaXSJ6YtBQPvbbOj7sXhLKJC8Ej5l7cMKeXQ9y/cQkdmKJ5WfWx+J41MW6IfsmXqcUeVwkUVEkps4JXmlEfk+3c+dWhe3IwlrnhGsPV5Mrec/kLOTGa4Ll8eB4wkgkYZ4CVTiD5+yBfg3laLZ2uzPtnrwPAc7FVEbKdJfH920NLyFPHbUPrHvru0pAVZOs+E/HyaWYTQ4+yABlVNdelHJ8WutwSYyd/c3g9q6NUhOXubI4FP81fPHgkM5Fpz2N8LM8z2RUXhrHApqjH+xbF1jTP5JxHuLmWq6xV2RZXbKclaM9nURAWQtfIv0c8D3Qrq0H9XwngjqMmyY1h6TeBLG29T7W30+FMz6JSCD1ZXGpfGHV6BozJ+PTwsSQfv61rzpjlIlIJXQvotzkKbRxoc7o5+WFLuLzIcV2gFUGG6PBg10bwgL7TlUXtcJnQgtalMY+xLzZK5UGGyOKZ30Hdw7DMoKE+m/irju2k50Ih957772348E9ju5d27vrbV6SAEcNgQQuEJIoycFRRBOI3iSEEAKEgD9AQggEovfeexcgBAjRe++fvfbseH85moS49+69xPaMy7qMxzPf2CFtn0MUjECMB2Gfdh5GCJDL4v0N4JXEd+xak7dt5uPeecckEnCdi5ObnsEhh9ol4vzcS3jVItcWW1Rde16Y02gO+SrBAGh9+zRxoTP62slYaYGTtR1U1ceNh1v7LQBYYa+PdkgV55Mb0egqU0XWMD5HBuCk2A8JfS1M30tdtuZo+sQ/+jjZsSd9gbwhZdvVsiO8g3/SJzASJCckbRmEruvW2WARn3/RJ4pPdq10bQ2mqQewimtrezfE8pS0toj2WEIrITt1ZVsPTaRd31ggXSK73dk3zaUpy6bsqf3//JsukWwyW0eqVjpXRUV8/vW3ESRfXivlJY3ua9mHGKDkDvig4Cno962jZWmGM39nxlNXQpd1WeVlJx65vr8Ddm43JOCWOTI89hEuq566cyqrtpWp6wEH/2YaHwvbGLGkrQxzMI/7fcKncOdZrnPLEGT4Tgi2JPIyP93k23dYk2Wbt2oeqysaIIXny6kt1KeETy9km2Uyr+UCn3gWjTYAkdHxOvYp4TOICiPTq6qczWMC0ojnDnFi4/zyO6cyYV2DmWo7sRIbM06udXeEQRXB7zJ8jX70zukYQfowlerKic/hpsMbSlwDQoM4nx/M2mMzHM+NdfcxcCHL1qPZMVn30ndJ+ZT47hmUBQtjfTQfOh9OJHwMxqfUskYHp/v8Q7YegSPrGPHkF9hkrB+Q8OpErkzZQ3ZemNNH2kAzH61534bOVrhczPlwMH+60bF96a2cj8pF16lBydwEmZE8m3DaeVPmxMiZ2fH9gvO5nXZeawq7aialHlY=
*/