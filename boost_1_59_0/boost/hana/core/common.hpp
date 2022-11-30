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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_CORE_COMMON_HPP

/* common.hpp
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
*/