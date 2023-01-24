/*!
@file
Defines `boost::hana::common` and `boost::hana::common_t`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_COMMON_HPP
#define BOOST_HANA_CORE_COMMON_HPP

#include <boost/hana/fwd/core/common.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/canonical_constant.hpp>
#include <boost/hana/detail/std_common_type.hpp>
#include <boost/hana/detail/void_t.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // common
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    template <typename T, typename U, typename>
    struct common : common<T, U, when<true>> { };
    //! @endcond

    template <typename T, typename U, bool condition>
    struct common<T, U, when<condition>>
        : detail::std_common_type<T, U>
    { };

    template <typename T>
    struct common<T, T> {
        using type = T;
    };

    //////////////////////////////////////////////////////////////////////////
    // has_common
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U, typename>
    struct has_common : std::false_type { };

    template <typename T, typename U>
    struct has_common<T, U, detail::void_t<typename common<T, U>::type>>
        : std::true_type
    { };

    //////////////////////////////////////////////////////////////////////////
    // Provided common data types for Constants
    //////////////////////////////////////////////////////////////////////////
    namespace constant_detail {
        //! @todo
        //! This is an awful hack to avoid having
        //! @code
        //!     common<integral_constant_tag<int>, integral_constant_tag<long>>
        //!         ==
        //!     CanonicalConstant<long>
        //! @endcode
        template <typename A, typename B, typename C>
        struct which {
            using type = detail::CanonicalConstant<C>;
        };

        template <template <typename ...> class A, typename T, typename U, typename C>
        struct which<A<T>, A<U>, C> {
            using type = A<C>;
        };
    }

    template <typename A, typename B>
    struct common<A, B, when<
        hana::Constant<A>::value &&
        hana::Constant<B>::value &&
        has_common<typename A::value_type, typename B::value_type>::value
    >> {
        using type = typename constant_detail::which<
            A, B,
            typename common<typename A::value_type,
                            typename B::value_type>::type
        >::type;
    };

    template <typename A, typename B>
    struct common<A, B, when<
        hana::Constant<A>::value &&
        !hana::Constant<B>::value &&
        has_common<typename A::value_type, B>::value
    >> {
        using type = typename common<typename A::value_type, B>::type;
    };

    template <typename A, typename B>
    struct common<A, B, when<
        !hana::Constant<A>::value &&
        hana::Constant<B>::value &&
        has_common<A, typename B::value_type>::value
    >> {
        using type = typename common<A, typename B::value_type>::type;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_COMMON_HPP

/* common.hpp
bf+RtIQbKORQsZSuSgPeBM9AAe5kOvOuXt/RyOvcMVkS5Zbwj00gdGdVWKWHcO0cB3PTj02o0rn5Yc4gazBtG0WxP7t2P9YpQT4QzmryTcf9QHxeZteENQd5lBOc4aREbjiKV1t+LAbNP74KgfOp2pO4DJpgxQveeQ3s6eiRBairxrjVQJay0vDUhwAYZU3HXKl4wTvo7Fs0hRb0SxQqrNGswfhw0pOQTy91HubKwAveeY1s2r/N+mhM1usx12K84J3XxLoHI1mt35n78ZjcN2HGlXjBO6+ZdqvozU36jq0uQav+jLvMAIybrUFVbR3oRr7h0YJY8tuaNOpAJla92YystTJe3JNrKW1Ucy2lERMgCB6WsziYq/CNHOAQXbgCE/OMZnj051xkVtZaiwqdK0uAR4FItD/c1ritAzofatMb1nYHxlbmfqyMCsO6G0QqtW36IXmvyW3va/jcmNVATvB7fSOBfecpo/1LzVk9Uh8JaJShujvdFHNA1QB6uBb7huGEk3IYyMqLh8drjs1/A4XIw32dM77lr/Z+RufRk9aXrNS2D+BjBh1Vj76I/AhlhU7hVp5oJx/ow+QD3UY+0Pu5D3SI+0B3cx/oFu4DvY/7QAe4D/Ru7gPdo/tAM90Hupd8oLFIzQda4SdGO6wK1Qut3OQRSNm6cf1Ic31WQ5qTM1U76ud8Ae4IQzxwNCQBwyyhgzZWs4UHAA6a
*/