/*!
@file
Defines `boost::hana::_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_PLACEHOLDER_HPP
#define BOOST_HANA_FUNCTIONAL_PLACEHOLDER_HPP

#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>
#include <boost/hana/detail/decay.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Create simple functions representing C++ operators inline.
    //!
    //! Specifically, `_` is an object used as a placeholder to build
    //! function objects representing calls to C++ operators. It works
    //! by overloading the operators between `_` and any object so that
    //! they return a function object which actually calls the corresponding
    //! operator on its argument(s). Hence, for any supported operator `@`:
    //! @code
    //!     (_ @ _)(x, y) == x @ y
    //! @endcode
    //!
    //! Operators may also be partially applied to one argument inline:
    //! @code
    //!     (x @ _)(y) == x @ y
    //!     (_ @ y)(x) == x @ y
    //! @endcode
    //!
    //! When invoked with more arguments than required, functions created with
    //! `_` will discard the superfluous instead of triggering an error:
    //! @code
    //!     (_ @ _)(x, y, z...) == x @ y
    //! @endcode
    //!
    //! This makes functions created with `_` easier to use in higher-order
    //! algorithms, which sometime provide more information than necessary
    //! to their callbacks.
    //!
    //! ### Supported operators
    //! - Arithmetic: binary `+`, binary `-`, `/`, `*`, `%`, unary `+`, unary `-`
    //! - Bitwise: `~`, `&`, `|`, `^`, `<<`, `>>`
    //! - Comparison: `==`, `!=`, `<`, `<=`, `>`, `>=`
    //! - %Logical: `||`, `&&`, `!`
    //! - Member access: `*` (dereference), `[]` (array subscript)
    //! - Other: `()` (function call)
    //!
    //! More complex functionality like the ability to compose placeholders
    //! into larger function objects inline are not supported. This is on
    //! purpose; you should either use C++14 generic lambdas or a library
    //! like [Boost.Phoenix][] if you need bigger guns. The goal here is
    //! to save you a couple of characters in simple situations.
    //!
    //! ### Example
    //! @include example/functional/placeholder.cpp
    //!
    //! [Boost.Phoenix]: http://www.boost.org/doc/libs/release/libs/phoenix/doc/html/index.html
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr unspecified _{};
#else
    namespace placeholder_detail {
        template <typename I>
        struct subscript {
            I i;

            template <typename Xs, typename ...Z>
            constexpr auto operator()(Xs&& xs, Z const& ...) const&
                -> decltype(static_cast<Xs&&>(xs)[i])
            { return static_cast<Xs&&>(xs)[i]; }

            template <typename Xs, typename ...Z>
            constexpr auto operator()(Xs&& xs, Z const& ...) &
                -> decltype(static_cast<Xs&&>(xs)[i])
            { return static_cast<Xs&&>(xs)[i]; }

            template <typename Xs, typename ...Z>
            constexpr auto operator()(Xs&& xs, Z const& ...) &&
                -> decltype(static_cast<Xs&&>(xs)[std::declval<I>()])
            { return static_cast<Xs&&>(xs)[std::move(i)]; }
        };

        template <typename F, typename Xs, std::size_t ...i>
        constexpr decltype(auto) invoke_impl(F&& f, Xs&& xs, std::index_sequence<i...>) {
            return static_cast<F&&>(f)(hana::at_c<i>(static_cast<Xs&&>(xs).storage_)...);
        }

        template <typename ...X>
        struct invoke;

        struct placeholder {
            struct secret { };

            template <typename X>
            constexpr decltype(auto) operator[](X&& x) const
            { return detail::create<subscript>{}(static_cast<X&&>(x)); }

            template <typename ...X>
            constexpr invoke<typename detail::decay<X>::type...>
            operator()(X&& ...x) const {
                return {secret{}, static_cast<X&&>(x)...};
            }
        };

        template <typename ...X>
        struct invoke {
            template <typename ...Y>
            constexpr invoke(placeholder::secret, Y&& ...y)
                : storage_{static_cast<Y&&>(y)...}
            { }

            basic_tuple<X...> storage_;

            template <typename F, typename ...Z>
            constexpr auto operator()(F&& f, Z const& ...) const& -> decltype(
                static_cast<F&&>(f)(std::declval<X const&>()...)
            ) {
                return invoke_impl(static_cast<F&&>(f), *this,
                                   std::make_index_sequence<sizeof...(X)>{});
            }

            template <typename F, typename ...Z>
            constexpr auto operator()(F&& f, Z const& ...) & -> decltype(
                static_cast<F&&>(f)(std::declval<X&>()...)
            ) {
                return invoke_impl(static_cast<F&&>(f), *this,
                                   std::make_index_sequence<sizeof...(X)>{});
            }

            template <typename F, typename ...Z>
            constexpr auto operator()(F&& f, Z const& ...) && -> decltype(
                static_cast<F&&>(f)(std::declval<X&&>()...)
            ) {
                return invoke_impl(static_cast<F&&>(f), static_cast<invoke&&>(*this),
                                   std::make_index_sequence<sizeof...(X)>{});
            }
        };

#define BOOST_HANA_PLACEHOLDER_BINARY_OP(op, op_name)                           \
    template <typename X>                                                       \
    struct op_name ## _left {                                                   \
        X x;                                                                    \
                                                                                \
        template <typename Y, typename ...Z>                                    \
        constexpr auto operator()(Y&& y, Z const& ...) const& -> decltype(      \
            std::declval<X const&>() op static_cast<Y&&>(y))                    \
        { return x op static_cast<Y&&>(y); }                                    \
                                                                                \
        template <typename Y, typename ...Z>                                    \
        constexpr auto operator()(Y&& y, Z const& ...) & -> decltype(           \
            std::declval<X&>() op static_cast<Y&&>(y))                          \
        { return x op static_cast<Y&&>(y); }                                    \
                                                                                \
        template <typename Y, typename ...Z>                                    \
        constexpr auto operator()(Y&& y, Z const& ...) && -> decltype(          \
            std::declval<X>() op static_cast<Y&&>(y))                           \
        { return std::move(x) op static_cast<Y&&>(y); }                         \
    };                                                                          \
                                                                                \
    template <typename Y>                                                       \
    struct op_name ## _right {                                                  \
        Y y;                                                                    \
                                                                                \
        template <typename X, typename ...Z>                                    \
        constexpr auto operator()(X&& x, Z const& ...) const& -> decltype(      \
            static_cast<X&&>(x) op std::declval<Y const&>())                    \
        { return static_cast<X&&>(x) op y; }                                    \
                                                                                \
        template <typename X, typename ...Z>                                    \
        constexpr auto operator()(X&& x, Z const& ...) & -> decltype(           \
            static_cast<X&&>(x) op std::declval<Y&>())                          \
        { return static_cast<X&&>(x) op y; }                                    \
                                                                                \
        template <typename X, typename ...Z>                                    \
        constexpr auto operator()(X&& x, Z const& ...) && -> decltype(          \
            static_cast<X&&>(x) op std::declval<Y>())                           \
        { return static_cast<X&&>(x) op std::move(y); }                         \
    };                                                                          \
                                                                                \
    struct op_name {                                                            \
        template <typename X, typename Y, typename ...Z>                        \
        constexpr auto operator()(X&& x, Y&& y, Z const& ...) const -> decltype(\
            static_cast<X&&>(x) op static_cast<Y&&>(y))                         \
        { return static_cast<X&&>(x) op static_cast<Y&&>(y); }                  \
    };                                                                          \
                                                                                \
    template <typename X>                                                       \
    constexpr decltype(auto) operator op (X&& x, placeholder)                   \
    { return detail::create<op_name ## _left>{}(static_cast<X&&>(x)); }         \
                                                                                \
    template <typename Y>                                                       \
    constexpr decltype(auto) operator op (placeholder, Y&& y)                   \
    { return detail::create<op_name ## _right>{}(static_cast<Y&&>(y)); }        \
                                                                                \
    inline constexpr decltype(auto) operator op (placeholder, placeholder)      \
    { return op_name{}; }                                                       \
/**/

#define BOOST_HANA_PLACEHOLDER_UNARY_OP(op, op_name)                        \
    struct op_name {                                                        \
        template <typename X, typename ...Z>                                \
        constexpr auto operator()(X&& x, Z const& ...) const                \
            -> decltype(op static_cast<X&&>(x))                             \
        { return op static_cast<X&&>(x); }                                  \
    };                                                                      \
                                                                            \
    inline constexpr decltype(auto) operator op (placeholder)               \
    { return op_name{}; }                                                   \
/**/
            // Arithmetic
            BOOST_HANA_PLACEHOLDER_UNARY_OP(+, unary_plus)
            BOOST_HANA_PLACEHOLDER_UNARY_OP(-, unary_minus)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(+, plus)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(-, minus)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(*, times)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(/, divide)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(%, modulo)

            // Bitwise
            BOOST_HANA_PLACEHOLDER_UNARY_OP(~, bitwise_not)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(&, bitwise_and)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(|, bitwise_or)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(^, bitwise_xor)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(<<, left_shift)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(>>, right_shift)

            // Comparison
            BOOST_HANA_PLACEHOLDER_BINARY_OP(==, equal)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(!=, not_equal)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(<, less)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(<=, less_equal)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(>, greater)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(>=, greater_equal)

            // Logical
            BOOST_HANA_PLACEHOLDER_BINARY_OP(||, logical_or)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(&&, logical_and)
            BOOST_HANA_PLACEHOLDER_UNARY_OP(!, logical_not)

            // Member access (array subscript is a member function)
            BOOST_HANA_PLACEHOLDER_UNARY_OP(*, dereference)

            // Other (function call is a member function)

#undef BOOST_HANA_PREFIX_PLACEHOLDER_OP
#undef BOOST_HANA_BINARY_PLACEHOLDER_OP
    } // end namespace placeholder_detail

    constexpr placeholder_detail::placeholder _{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_PLACEHOLDER_HPP

/* placeholder.hpp
pZ8qiGDwS8vNV/q7rb6+GbWcFJiND+kE+PDg3vT8ZGeOFnvTSVM+XKKWQ7icfjE3LhRy+y3e+Q4xay9D0dHilJWpHO3KoaKciLO6wK6UPFpSAeG9Vn4Xd7PkIQrsDzoP6/6zPurqiBQtBc7f/cKGyzKYURB1r1VAWcJOr9oxQKolUaLd7SobO/DO9MhjG0JSmO1gkUgH2z4BkPQ6UHrI2oSoxKXUtAoBvvXPeMPb6+K9w/Awbn3fDlsWSvNomU5gUF0HY1LfzBMDOXJ6AZRSHyHrusPjvhNMuMWZbnCDeD++PuNso2BktSgem8sHKxWcqGSkIvGuC6b36pVdOV1qjF9EaTC4Z1zcbi8MIPd17/QbyXoUyATYuqafO/9qgIC0/YD9WX3pCzbY39wWQXp4tmQtzzde6+VQlZIbzkLcoy+q1Swe5xHcZ0vXHvB1xhDTQz3UtxpR5zozeQxUpLLWbT8pV5q1Pq3JaEOnSUA9GlRsfwZZ2h9Bg0jDMRebDESKAiv1b/6LTKq3Emg/Izah5fUup7Z5cfw55lM3ymIkyvrXir/4fuRw8kB92rypOa5QpUw1UiTrrMvl2cqxpu2KRpQHIRoU3doJQYMgmKEc6trA9mBpdVVpEzJKC1aRMf0ttzF82QGTEsoSXudj895Bhrqsmj3dBbyjPIr+c6B0nc0OjePUusbRUTGnaXWO1IB1RbHEW1cLosc813N9krQ9VYUTEC2HcmhCWMH1JMkMG+csxut0y7Y1frZxtt8UYzOOikcaThFPGjhObT21bsLCyrENPKn7VTapNDWBeplsM1kF9cSCYxGS+hS5GttVNDd87PkdBf52hasvryJknkQwTO/NnS6CbEu9Vf44j2t1j+wizk34bJeKmFAlY46qUextLf0dsh0pHCnRNkXcFyA6CsdcqTlSVAmTEC1QsJuFgpH1PuwCYF1neuSpU0pT4x+ABovHbLtuiLoaxWQEIhMDami8BQAQEA3lRTvmoDxy0z4WcpdEXdofyNtxFCsoos6goTADgxoYIHEIOAAPYMZb0JJ2ULPUaBToeAt/3wACC3TKgX4hGlTVtpLEgjDITBEoCxO6u4stl3RdQMWClrTASBO7cpKy+NuneKsSzZxb5f5zdhem+N/yF2DtnY+LYjPe6PFGxS08JOX6c0v1u3dB22y1OgqKXOpLFtXyOq77is7wW2PlngY2tPzy/1J1IwirK2njP79hU8HSRjOBJvttV0xKjVdPpbN9t9s0v6grCR7XCMI+LZ+PZIz0uLx1Ujma/Y2hUfMqPCo6r08PUDYoTbssBGESD1X47DaSU9UapnlR2qUQschb8WFuDOvFeWizOVOq7OiaqujNIkW4ThmYkWoqr0h6XrmiUg2+jtLQSAPCSz78qUAEXp05dTWRpmaXHtCFqdAQ/xOu+aGPktlGGuSIKMVh4AgAEoDtAAACEQGeBAXRNb8AKZGnuA7P159JlPxIPiKdHwtvKfS5Bh5fAOdcWzofEu+xMYlKdfAPenD7aL5B4zOC8AioHuVXQbtkrKm1jiWvNXxhEUCzHCtn54i0hFbf0e31b8t4Yjq7t7celcm0KJEdc9IY2F4NNIxIdtOz5Vr2nd/bYVPaUR4WPTw8Ni9m+Zbisml61eDfdnF/UM7GohL9N9up8CZ6TLwSmuwTXOf4BiKXmMzrfn8xly+SkoI3CLdDzhEgNhjpFIRT9HEsfdPt5zJ/pfB+xLVvYLyNQt1QyalKiXIIDxvcsIiQ4tPXlEDWYhCp/4NPZ9lvhESxSaXlKKTBYapVpG9i1hCb8ya8+6lXccss/WMipcTUnd5r02Kgq5XI7nKptwQRabnwuXiWGQRr14HQCKndreT2U38huMpHoKUKMx4O9j6slM6EZ87SC78RdYIO78DugaNkDrkiCco1jkWduDbaGQMIXSWFzpT1pAOxdMyzxY3YeLXJk2IbEUvLh0uSMiZpcTWzqhZR6hXvZ4ruDjeMDVKdZZDNwrSnKzmB4eVbEYC33nAK8gb7UYZB6bLX1chxYsvnCW7mhcGdMp9tl6kroqN5Y3mMP5R1Dtha6Wuu838gv9YndoUv/t+yJogdoM3CdVSz2jkjI/cjK9U38nosN5BM5fkKJ4GQ+xqxBDwLicIpDsxa8uFZNB05//NDNoAhGlTdspTDocDYSEEjvplEas0VlpFzC6vGsGgdnIa3a5dWS5AhPSVTkfXI1iBdNEB6+87vwzC/eYrv3rNw1sWzEdjXabe/KeJ969qxAs3pfP7trlJJr5/QCKqrkcM4wm2lfscetdluns2ymKYSR7tdhV1IarycBmM5In4cQvNHrWhRGCG6pjpIrlGou/N22Hg8FAIaXYOJkKpbHIWUhN3p9TK8ffvvbMyrEPAnyMxIGAsVmgSUJwpB3MsllOSUXT27WJMrCxic8idOfeS7ymb5LRil+A01bK2qN9hTXYxY5cqhOJhAWSkeV/x7CDu7umS6FzR3bEZa39mO+V3kep/sZsyHvk9eEKPFvKa/cgWH5QxaH7gUArDwAAAkHQAAAmcBngQJ0TW/ACoZ0SnfLtRts2Gjx2woJ+BD3Eynd7yHltFQ7zKRTOQDPt6ocsyShLOeUmaPXOqF1HqhslJ/YpwQwOnGdwVYkvHoICIxwf/VstFSHRvoBszFYSsyDIAKpTPiBua50grcvbwmidmn3GudxlRDgK2CqCX2YZMnE/FHte9f62CLgxoRA8Ce2l7zbk2pYAbpXc3+baf0BKCKDWmtTnNYTVpDZR3KC5Q2mwlxM6cSUYi4sbX0PsF3FGZk/7zKAP77V5OqEmXm7mLmQDFt4B+cVMSkNM87U+g0qnAUtQTnE+yIzais90YhOJofRlDfLi+UB/RlFK+3C5lIclqAaEmbCfiFzZIueioXquLvA/3KKpIWj+89iVBrcxD+sPmYiwk+uZNUK63PTjpV6dyzMOgZNGIpw3tPirGs9uDjjXp/JA3AxmAJJ0t1zMMZ4UnVG71ADzyOMgYGZOcDCS5hVl9VXgIl8Qu10tljEjv6kbpwewPNyNc7OH92iSLvNuxd1cpY0MXegT6QA18xL2NxsSaquZL+QaOXJ3RM9WsQFBwKycE8Aj3D0p0mB7aGQQpWDFlKGrdMZV24mZmP0+5gPcGPjY8adDUm2xI2i2BLZ+wcMAVmU66DHc1ib0vRFKAHXwoBsLWQ2eiuQdT2wa9WlOKOprZy8Ve+KuDXoprIvXyhh9Agqr5Yr17lkjG/VAfZDvt5BNBJWKWMZ7+N3dVyxlZ+PA7BefWvg+/6/Ctyw/c0aDHpEIsFO5h6FRaqbJ6XSEOAMobSbTo4xN9vI5RzRirAUcQW4kbKATA5Dp9QLTTywl8hxoAhGlTFzhDGITCEgBDGlRsudYytJeLUWXKtAAxIAKw/VSJaFB2LOASh4AhNF8qRUMnOGSGInDyVZm/dElDog/62sS0WjaVrnogmdXZUnEAFn0UqC5S+pc3vzePNBj5i9NQduR6sN1bGHSCrB9vO9xRHMmGVXvhQg4+euCt3r1O22be5qb+heGGMZyBlGGE6jkHCm1DehIWo6BlGjgRAcBJU3ZXbQdt2zxdqA8YQJhcGlu9mP8y8RMlIQLAOFHdWb5lKv0cXNGQaKUezEwwzxoHyaZpEYTB1tlYUstm77JPCj1+QfYkSN9N8t5EJGbBM51d3MoRxgyzu/b9u0zBfAzxEt/S2IpeJpb+pW74mRn7f/+WwTrQqIZCRSnECdFYeAAuVaABiQAQBEc0hGdTlso1hobCgjDgSigSiAE0XqrrC7uZUlqLygOyb5NHgTYh09g8XrdWJGmVIgiEWdCbLU4HzQ+O0v4+XyLZkx4Cz+r+hoebt6vGJvFr2qfjH2Qzs6deHLaPUVV8u21NjeBhNldxes28Hgjq5b9uAte6Ye2b3w3A3XXPH5bf1JVbmp/JhvlogpHQ0VyBlGTcXSapTr6N6Ka2L0V6gVJmp1p1wk33jvCuvv1O1aoChW5RjmOQUwZV4CszhIFRSNYiwJVPJCANYkCHCWjV7qv9ol5AMTxzY9Ve1FZXF6vQyt6+XhuigWrkoy1GPfHx4zHzVgu6UARnPlxfEsiEYnJLjsvXjm0rxrqpixZSiuhIBLiRjD+nec5heBM2Uq4q6pKCfFIeAAAUdAAAB3gGeBA3RNb8AKhpT4PIwFUlT+EAUqaxyPsMmgZ/wOFQz5JPollWGJFsGMnw832Q2fVd7y84SlXpRZVBh9euP/RjvMBxCjLyJGBs+t7sp6V6Uq1ZBYsqQKYcujU8y5CXIO64ZBBFq/LvAWsfh8SLEPJiuWxRdnalftHvTuSIhbJucIgIIB32woT2z3kRWUik9h8l2+adwj1jLgwBiCFyh3SQgawujBdjEp3FhnoFOKDurNVRiK5JvZ0XrtDazdumhe4Jr0fddnZRz2xBedsfwoEntEXtr7YQfOv3/dJqZDpiRmVccdd47BVXlwahQ/syxgB0NNeN5FB+n8raM4/irbNhlB2mf/PyogDfjfl8mH1quUB/IkcU7OpQFIiTQ4bt2my4ct8jWyyIV/NRtAZkhOYIUX4cQcjinpioSQ73qPA4Q32Iv4GOGkJAbJzRyFttJYi+I3vcMmmMSQ2xqp4UKt9PbCyQ9pcmVaE7lUm+52+kOhXMFzifHtV7UM1HwrrNmJpip5R8ejZ/1grlO8gXeCHuxT6R+JChen2eRYnqSXWZX8kt2LM2p0kw8dGLLGi4dZ+Vjht5MWZ4ttJ99vqGyvhCsd7YJCHIFwjiL+C7GsXpEUKgN65CuidpCRNrjScghGhS13cVCgTCgjCEbkpoZ8FzGC+C0jJU3FBS9t/0SFMzv40IJwdTqx1neWQyTJYBWxyT00QBms4A7POXMCLv6yeyenJplr17VCaE4Q6VmMowg1/ikYzDCFiDL1gZmkbqSOluYj+zahB4b3F8BnLdMU26odlcsUlxi+P/Xf27tlP10wl+NRbUdOvaQYBtXHci4MMsq604nyuFRlOs/iXsNd5isEr0wSj11aBXmRpvrqmN+1XFYpjINJJFlBeGCwvlOTnH1U9pz2hsbsX0zmYGDm4wzPDqjm1GrPQpLBp7WQfnSzUROBfPITRqSI5qEsbzxEOkkY4Yr7bR1jJHCkNxZnLU46BxgrW0dUGrdRoQWtRyoz4293Bchmrr4NMDuQhhy5WH2+/8PT68+vUKAjSMAVBBMBAZBBghBQCb+VBgQu9DgZx0hGlSdto7FgLIQQlAKa8xNcu3PHVzbpeVVNjRcJlkg99dlAmCWCdiOQEYgYBLd6GztMRUQg9ZHKYIjQVbgZbJdJpZHdxLpHYo7xIhERKTlV0/pcBE2PP8ei3rHe++ubqjlu2aN/tDzulSblPG5VVpKdpY6tJ65ypu+Tzh5GdmZzrklt7Sy7iviQDnkCKjslsGaOpBC68OqJySvinNK+h5VoO5hJUdcERkgiIxHGqtMDtgspookOrLjRlqkqu8IuRrsOqF6Z2WFl1cpzRQhystJ0uOV6pSwzDAVrGRgOGOCgoCieK5HKuxO01NAEEIYgFIpLyDY7/8NDWCk/F8dPvQzQSrMIZ4+9Ba1pyHOcp3y9gCYAUIAMCYppQYpAQadGmpW1GtC61lFELhMskHhFa2ccD4xxjzJhF9Nx5jxcZnnWVQEVPe8xmSLmJIaqNPf4x1cazG/vLY0zse9sdPAebzIBA+vq/ypRkCMPwLYjFfgP/CzoH/8+AUaHH9+epLQrpZ40p+8K8LADgsiAA7sxCEJRzVWcAfL4gAAqUa4pAeAAIBDSwEAgP9/C7xBmgQhTBLbPmXDgAAAUKAdgAGU9e4b3IrHi1G7KNVUpfmIGe7uAuIdlSmnckHuBTmXMZK2z6BErK12xo2h6mJSS4EZGdXQSGpDGdmlyMwMWd/TfAkFmoae08VGWB+8QXfQZvJzWTXOpGI0/yoppS6C4O8QBHyNFEExb/8FKcwS+nGASHRhnu0fV3Hdn/5lrr9HEfyuKjv8VxGwNG9ltetZjLHnQZvypZPdIA4sLoybGuT+lezDluPIS66XrMvhYN6C0YFDN04L1NMGKaydE+dk0ZYfk4G6q+mHMODYtTkPi6QWYe2GQLxmg25VFlDNMy1ZpbvoPMJe8YhT0dU8qiI1vebvjRexYDTrUNp1vGut5Hp/XYUiAif40h7wclYknYsEmhrJ0+qSXz+63LTSqsNQIUg1a4yjmhYvGfvT4bU/arMUWuVf2Ta6raFz2xoFbp9+DhD1CjQWnQqd/YFXxNJd3wWHLrKSg/WsDTpWqJ/naR94XrZLN+T4E07spKN56xjfyn6A+WTL6acBFry7TjUEtCQFUwwQIOUe4qdJq1jF4hk9jH+KrU51nWIpgvMGPQVGq8OB0I4cdcoemuz2KoTEq1Cq1/B2Q/+l7hg7Y9Ybx0sbK6f2HdryKnMwHXaqPnkczWC9tAZiyANS9RKJU9Un32OJJZPErRiULVv6HGHN6mwymQDIBTuZ/SoLJgBH0e8tEka1vjJfhszNRJ6AwezGBiNeQu4FendGjJtXIGi6Eps1CGLjzJeQ3lnVGMRVLjXs5A6LElOlkfiT0fa/yFq9Jm8lCNuPX/T7RJ63Y4cx278B4D6fjrpVX47uf+iboyclqtM/HAL2X9f6waupCKZ33K5gah/RWYJiMjTZPozw792R6tlE+q/kR+waBxiYccH+oOlJStXawN/Cz5QPPdQwae/zDA5DDsZ0M+sFdjoO2t9C4P8yXWXvTuqtbavb9copwOnEO9eX2SlGhcPnJrCjJiwZy8NRFQg4I65GAp046l5DlDvutNgQ0HoFQ5DAv7bT254Ix6Vr4Kpt0skigVk1DjBpK9C/Vw1dajEfOb4arE4iC9tk5CODG7+jCWEpzqDe1rLYZxtvVYwhfB4tvoBaazsC0Lc+SNo1W4DM6dxzydeJcjLX8WkFAVbfLDpbyqzOubFnkzVuR3p3vPxoGQSBs1wGpsPV/9a9bPgPu+st6ePZvT1lqB48vyJjw7OhXigayJQn+4hHqMU73PsO7Isw2RnIGuC2n/7aPY5QgYtxKWj2j7wShCc4xr89GTtnIVMe3wLBr72VW/Ho6YkZPoFFiMfep7842pNrQg3F8FQMvQmD0moYYmcI6sDks3pjdzLQWfAEiyxAyvvQR8voUC02fzSnh0YHelqmc82qxfO3lfQByDYvC7mTsPM+25THOoOhyMjNzvvSYsR5pXXuOEGIrF0PrfMMmMg4hAnlaC9sDm3CT5HPQRNF2nd6jX9X/RfrXODf0kH8U8LId+ExtOkcfhWUVdnFIFm0tWtQFM7NRiRvAB86sOGxq0xcJa6cUM6PltDpwb9ghTWU5Z5xK8dWqrCb1Z8khYPGTLviN72BH3Oa4eQhE/ZTI7wEIZ2pVlB0u0Uj65znjLJXCQ/UKNevnavXuOQIvS56t7sXDN2Mc1eFQ1Ya85BkFP+M7UbuM+UNr4Gw5DYZjQhFJhRMNsRkk7O/Dh2nYUFvfYRqdiqf6FzTW44FWfciMMrZwcEvYXGDbbfCFRAcaiK234B/MwuZqOvzLfBVWk2VFloU+DswvGZnzMK81FFUELuWxDQbFucvHKBLRjXX4elIbI6AHRFPwZnxesahNs8yvoLyb4ss0qzGmDnGRFCT5GooN4KrwYws1p8NfU9b0BR13rVgzH1bRbTK0odDNb2HmwugizgTPOCgcOS84y3FnSU1WETntCWVO+PEX8jfVnNwagzqWF/ddIjtJ0minEunzkDDXcRCP7S/9JDEBpl33hjc5avPIST4xJnOkfpwlFm0C9VPXr+KUlmA6xtwwMwrKFSBksNwh1yYV3LRwzEEUiWepCaxfiwr97j05FshpxKDnyAnP838webQ+YpARrMcQgrfjuZ2ouFG8THsHx/llwZ1CD/X/Ca9uTVJz2eSNN1jfx4ZQ7RyUgL58lsqamRPoP/VnrZTTWWyn1K+t1ScnUBhAOw65QMffRLWxQdkmtm5wmM7gXXOvoyeepF+iudKZTXwgmhGmaUIJjtBt0g9r6lbk+eMsB6DsnorLjzJcaa7zK/zrj14tDoa4AQtAmlqvPT4fGEr5tMqZNrHtpzdf9BDlWkpWfLMRIkhByUYVcVFu67HD/I5M4k8KxG4yK8ZC2NGhb7b/50ffDKpG3efm8P929KVGlvAFpwkNcz9ltXOppLW1aZsGW8Mbc9kgfp9xA9w5ksM4WUiXHAs8ks+X92a2ECjVusLL2WoxsHRUl/0T8LURk7h8WYoxZuvo0BeEOgfPpkqJrOAQbenD8VraBEAnNP/sO8vYN0PWAe5QXk9tRdMPKiuEVgqyra5JcNw1uTxHoXGn+l/r99EMrubwGPbQ/XyWwgntbtQQRd1Ore4Zm67q5tx6tkArpHl8WgpMBGipoq6eUQgrf0ujypQ0R8ZCECbhBeJ2U8+AMlW+z1yR2hYkuq5Xk5eLJsTDNQ2S9H2F3hBxgxzj08kV4RvBFIvEKtktcGPYqQxz4RPnneSQI1auXZkuPaiqa8RBzBYUeSkxrKhCySxuINMzFqQME5wXB8hc1R5if5A/ccO2p+tOFEa7TvRQucFZsm1gK6p1JjcccDcgJhDyR7Vct8e781zsEon7Qhmvb1zvY7PqJz0AV8Lu/q+ze2wtfi+ryKv47aVPtFBcrrhVsCS/kQTXbjrqZzAwzBR/lgwF+jRsoCG5rVZAARGa5C8tXs3CGdHOcYtTedLuC+tvEFILizya0TJZzyIA4gPwbQ9rENdS+AtFxsHXNC9Tf8HVDtUZ/D3mjLcxlFANiMMk0lgzdpRlllojHCzHkZnaqwEZKfzEamhNQM0AL9gbqtQQe4TJyvXDStqn3fbWBCG9YOWf6bReF9pZumKg3dSXrJWLkWs+o50A7nXTNvsnHT4wCOySQcGwb4nRgViFr6nhgELM9PX50W2A3pHKNmCLQOuBCo0mYOP0Ykm2X+akvXi0kWDEyKnYg/3AoW6BVRfTQGl2gFwKEQWrEdZBW+k8N9yE22BK+y6VwCOprucHwtqEVhkiX7axbWR3S3N+jY4zhPNRhZnXtYh3sif58b4Fu4B0PApNiasxZVYgDhW64RKz3ZjM508f6YB8CW7tPfR64jldZMnJJWfE0MwPaZ5/IDIhMD1Kr0UW528ba37BlrLAmNTz9xAXCQ=
*/