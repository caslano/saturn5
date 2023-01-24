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
3G5a2WFa2XE63Fm9F1qjWxapS/lLUomSb4XyQpzOHmJSVR0H1PgBEJ+fi8hIBgyx1EzOOhZcjftOhLI62ap8jaj+gf3NuSl1fDmOnggZR0nS1fhr6t8Uq5bMmeIqyVemwz1T7t4M9t5McfWecEGQ3Dxxfm5TtyXtD8I/MWevZqk3PWJliL6COtrT9eOI0/NcEKlqhwczM07qzzfruIQ1UVwbXulcv36aPZhiYerHtaWtcf2qBD3Y5C3e4vqNHOYatDEDPNi88ij6xLxKrcL8wCKb4jbd5GbUbsR0l3rTiPTTuOO3QPoHk5oqJHHIdfpbp8sm4mpKTDHvbV4bu2ReZMAXOqW2AYEYZ/n8EEztAxdpEVe7riDyfK17tT8aw/YYm44LXqu7rBsyAlrG/y2UxoR37619vmtdtmqm7jIq9upPKHHlrgLb4ju2/Ip7CO2Ds/Ul10K1XllrF872JNiyFXiKpThnadfzj8fSbtX6pVdTDdSFLf9OZ33SLBrlWXRNGQCGd0XOLrmpqp0EKnjMgxTzrxOWjF3+anuXSdmHLO0dLhYfAcz9YIEKmhYt+TDB6kVjlzNZn7LG1wItcJZSgyW3wp6jI8Aj4TeU+cpenVEX8phVdRfLzcA/OfzX9xXGdubVXeqcD39I1ZYo7lYtxbM3FTr23VdIb3ahzE9SaIyCya78O+F8HTSd0z2ruDdug8oHBIo6ChwVMbel
*/