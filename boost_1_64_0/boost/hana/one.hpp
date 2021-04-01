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
uJzkFQrc0O+6XPZbaUl1dFOlBA9ex1mLOoyeI3Zz8Lr71cHHusT/wdwAPX9HEtdavNUvA2fpHpmb+t2gX15cNNotVCd95OZudbyjdMqHC3zpGGIWr9TQzR6mgK2Tt7c9EkACXAaaKe7m4XkUJ0TsRtsex6g568s9EdnNqMcEqVBRNqU3RYFiRUbvI1ocpRkQJfF5uE6xbciSDvKAMj/Vxi0Jf2LMktIOEfnOaUDpqYLmsRjQFLzNDz1XPxeBPTlXLi/Zk7y/QZD6clwLPI2tG5bMoE6ds/uDFP4c47ptd8SQL5mYxYpVKfZqWLsBrta29mzrFp5/Z9iYExOXY4Aou0Qz8HkiTVOZhmWqq55PPlvcLDApjsNqowJrhTmQR6/yF1RwBMODHdZb2Y5EVId9YI0ycMSBNVvI+ShqdI8Q0trKIBjPFwCNkFJtAPgQrk9bS/cT8pnUrOhk+2iKfq4lzfKcZaH1gH14VekM6QirNMi7BG4jQyX5343A4BfeR+BJbIyQz/Z6dk55PJvDr2C7z6eya9zlVXj1bsshPtMgfE4akguHnHI+R/HqWg==
*/