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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_ZERO_HPP

/* zero.hpp
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
*/