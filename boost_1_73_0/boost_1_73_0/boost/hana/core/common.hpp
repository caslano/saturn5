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
x601jGlToeNeAiQhAXUBCJ48z7XWyT8+Dtm2hpFt5cOLruZAEKJHNl1T2bk7+YgepcNup6FBjpcSJnswiXWuaFl4hfRRRVhQnUnGFiYYRH/VfTakPvl9hsERge2Ow0/o1I6fJnr4+zGbhl6EbtGR5y0QNgNhqEFBq0A8aAlDKmHj9Q37288vjgX2hJfO7iuYIgd5lyL+sR9He/E8cjw6uOUvnz6l3p+88eL+Kpw0Yc17UVSDn1fhdD33LgBMUMq5tBLE0/l8u54jnWwDnXoOKmligrbrsvlCcv6xwY4fQM6Smt8M2k00z2sEnbADGzZmLrxLGICYU+z3+Mh512rrs3zV7EKDaNPsnH9wmv0On3Lk4eicD8ot++TO/SmpozjlrXZmAu/C1UdGlzJO2J33PV6jAKkAbz3AbM9CUJIBIzfMZaAje0DJAXoqA9uboPu2ZVJ5CeLzjtb5KQP+rTjh34SLvXCuXwEgIa0WXAHCv578qiM/Vp3isBifJUlpMCDlpCtaLsYOMK+0T0mric7gis2UsbcfH8jeCklCdr4ZLrH8V2XUUU3keCbQPR7JnICbyOXvRzbsbxtD2jZIChHjcxsH++S7rNWEZY4Lkd+CKXJzaJLM8bp5dt65bJt+DkrQr4YCtU54tfKJzUEL
*/