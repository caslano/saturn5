/*!
@file
Defines `boost::hana::zero`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZERO_HPP
#define BOOST_HANA_ZERO_HPP

#include <boost/hana/fwd/zero.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/monoid.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    constexpr decltype(auto) zero_t<M>::operator()() const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monoid<M>::value,
        "hana::zero<M>() requires 'M' to be a Monoid");
    #endif

        using Zero = BOOST_HANA_DISPATCH_IF(zero_impl<M>,
            hana::Monoid<M>::value
        );

        return Zero::apply();
    }
    //! @endcond

    template <typename M, bool condition>
    struct zero_impl<M, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for non-boolean arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct zero_impl<T, when<
        std::is_arithmetic<T>::value &&
        !std::is_same<T, bool>::value
    >> {
        static constexpr T apply()
        { return static_cast<T>(0); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over a Monoid
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C>
        struct constant_from_zero {
            static constexpr auto value = hana::zero<typename C::value_type>();
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct zero_impl<C, when<
        hana::Constant<C>::value &&
        Monoid<typename C::value_type>::value
    >> {
        static constexpr decltype(auto) apply()
        { return hana::to<C>(detail::constant_from_zero<C>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZERO_HPP

/* zero.hpp
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
*/