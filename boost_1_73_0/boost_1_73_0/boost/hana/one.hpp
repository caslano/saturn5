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
Uoq8i67YZywrqTVs7JcR0Mccus6RB9IelAHK7jVL65sw5cKISrGlR/rAvgHIeczTqtTs9tZogd1RM3KDh/MOHMzynBk/NeebvyffOL/9PfmjZu4zJUW/GvvFTykL/tQJQ9wbS2Br6glm6ECG98UDbwEdKU55Kaq0D+4nUxZ0dKOhyBpEfvMuDGUdkmtgGpFKVNys893LjAFmO9sM4UEY4m/C/oKhL5jkqAYYvddZRrGPESiMNZOBNWzQJcMkZ+9ITRqtdnRABCL/RtF41ZiLo1GN5nbyvxmWFKtx2h1J/e1iEGn0JDHIAzuDcZ59PJ/3Z1njBftHlTZHngosBCoEkLVivjJsqfgRB5LdFfxjvzGOL+JAPRyNQUBzB2cUkK2BtsNcLVwzSoa1RERsGLqAFwvq+DcRKd5ALPobrfJW0gLyCkunJmAVdpitbRQoTZGyIAd+VVb0oCxYTk0mTnB4ZCNFhLHH1spUYvk28AZC1yI4XphXM04UiMy5VqYQ4wfbpSU5X21N/fKFqYnOiKg11m+0QpTpRs8cHIs+NZIRQ4M75b0wqAzaqNBBnBrPLSINd+3iiHOTZvSsVuegr85kEU0aeL2uDDlFAd5aTu7Fyy75Ado9lpfA4RLgc+1DU2XDbTkO4F+0bVUS1eOc
*/