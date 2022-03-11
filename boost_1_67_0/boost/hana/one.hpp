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
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
*/