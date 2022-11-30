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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_ONE_HPP

/* one.hpp
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
*/