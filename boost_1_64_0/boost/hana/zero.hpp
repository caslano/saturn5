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
v1woq8U/Zy0htQJVmwNGEVYBcLTjS09zJqqlkqDIUqmeQv8Uz4ws9ds7LCi/CFn4nq9rtDRiM8a+ZvGMMzCULo9dSdBP6hBArhqqD3RLu6k+9VCveuITTc38UhyH9CHpCImU6asQcMJke2hBZuWVGSSmTDMXkzpvTKusKsmlsAsO6TKjd0osbsXjA7ZZsrvL96ZMoEdQQ7radBymYHiB/WJF0m8APLKLM31jKYjx6pMn49txf6EQJUlr9MUJxz/ay8494XiawnvQ1G5k6dEPBGkyu1vxCGGGquKlQCaJtp4hYP49Z4XOhY7pJs2iRZ4/yDZepVBmQfi3BWSsYwdIN4bR5n4FEE3siASsaDa33hSSdPBJcL7/2r130XcBIQspApBvIyX+op4B0Yk/ZVFoyoP8ef3fc3gXH1sbHuYiW9i7ojLyXwcRjLQlLwcTfEer960HCx7aAswsk3McVzOmuUMCLpGyVw91vgERM/A2Kzlp3cyQgUd1Icab6bAs/61DEkvgGbp0rexuof6kVtUy0RMSfaQh/cl3+KLVZBQJg3YlvNgTDPPf1P0o1w==
*/