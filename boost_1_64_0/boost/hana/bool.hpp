/*!
@file
Defines the `Logical` and `Comparable` models of `boost::hana::integral_constant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_BOOL_HPP
#define BOOST_HANA_BOOL_HPP

#include <boost/hana/fwd/bool.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/operators/arithmetic.hpp>
#include <boost/hana/detail/operators/comparable.hpp>
#include <boost/hana/detail/operators/logical.hpp>
#include <boost/hana/detail/operators/orderable.hpp>
#include <boost/hana/eval.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/eval_if.hpp>
#include <boost/hana/fwd/if.hpp>
#include <boost/hana/fwd/value.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // integral_constant
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    namespace ic_detail {
        template <typename T, T N, typename = std::make_integer_sequence<T, N>>
        struct go;

        template <typename T, T N, T ...i>
        struct go<T, N, std::integer_sequence<T, i...>> {
            using swallow = T[];

            template <typename F>
            static constexpr void with_index(F&& f)
            { (void)swallow{T{}, ((void)f(integral_constant<T, i>{}), i)...}; }

            template <typename F>
            static constexpr void without_index(F&& f)
            { (void)swallow{T{}, ((void)f(), i)...}; }
        };

        template <typename T, T v>
        template <typename F>
        constexpr void with_index_t<T, v>::operator()(F&& f) const
        { go<T, ((void)sizeof(&f), v)>::with_index(static_cast<F&&>(f)); }

        template <typename T, T v>
        template <typename F>
        constexpr void times_t<T, v>::operator()(F&& f) const
        { go<T, ((void)sizeof(&f), v)>::without_index(static_cast<F&&>(f)); }

        // avoid link-time error
        template <typename T, T v>
        constexpr with_index_t<T, v> times_t<T, v>::with_index;
    }

    // avoid link-time error
    template <typename T, T v>
    constexpr ic_detail::times_t<T, v> integral_constant<T, v>::times;

    template <typename T, T v>
    struct tag_of<integral_constant<T, v>> {
        using type = integral_constant_tag<T>;
    };
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // Operators
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename T>
        struct comparable_operators<integral_constant_tag<T>> {
            static constexpr bool value = true;
        };
        template <typename T>
        struct orderable_operators<integral_constant_tag<T>> {
            static constexpr bool value = true;
        };
        template <typename T>
        struct arithmetic_operators<integral_constant_tag<T>> {
            static constexpr bool value = true;
        };
        template <typename T>
        struct logical_operators<integral_constant_tag<T>> {
            static constexpr bool value = true;
        };
    }

#define BOOST_HANA_INTEGRAL_CONSTANT_BINARY_OP(op)                          \
    template <typename U, U u, typename V, V v>                             \
    constexpr integral_constant<decltype(u op v), (u op v)>                 \
    operator op(integral_constant<U, u>, integral_constant<V, v>)           \
    { return {}; }                                                          \
    /**/

#define BOOST_HANA_INTEGRAL_CONSTANT_UNARY_OP(op)                           \
    template <typename U, U u>                                              \
    constexpr integral_constant<decltype(op u), (op u)>                     \
    operator op(integral_constant<U, u>)                                    \
    { return {}; }                                                          \
    /**/

    // Arithmetic
    BOOST_HANA_INTEGRAL_CONSTANT_UNARY_OP(+)

    // Bitwise
    BOOST_HANA_INTEGRAL_CONSTANT_UNARY_OP(~)
    BOOST_HANA_INTEGRAL_CONSTANT_BINARY_OP(&)
    BOOST_HANA_INTEGRAL_CONSTANT_BINARY_OP(|)
    BOOST_HANA_INTEGRAL_CONSTANT_BINARY_OP(^)
    BOOST_HANA_INTEGRAL_CONSTANT_BINARY_OP(<<)
    BOOST_HANA_INTEGRAL_CONSTANT_BINARY_OP(>>)

#undef BOOST_HANA_INTEGRAL_CONSTANT_UNARY_OP
#undef BOOST_HANA_INTEGRAL_CONSTANT_BINARY_OP


    //////////////////////////////////////////////////////////////////////////
    // User-defined literal
    //////////////////////////////////////////////////////////////////////////
    namespace ic_detail {

        constexpr int to_int(char c) {
            int result = 0;

            if (c >= 'A' && c <= 'F') {
                result = static_cast<int>(c) - static_cast<int>('A') + 10;
            }
            else if (c >= 'a' && c <= 'f') {
                result = static_cast<int>(c) - static_cast<int>('a') + 10;
            }
            else {
                result = static_cast<int>(c) - static_cast<int>('0');
            }

            return result;
        }

        template<std::size_t N>
        constexpr long long parse(const char (&arr)[N]) {
            long long base = 10;
            std::size_t offset = 0;

            if (N > 2) {
                bool starts_with_zero = arr[0] == '0';
                bool is_hex = starts_with_zero && arr[1] == 'x';
                bool is_binary = starts_with_zero && arr[1] == 'b';

                if (is_hex) {
                    //0xDEADBEEF (hexadecimal)
                    base = 16;
                    offset = 2;
                }
                else if (is_binary) {
                    //0b101011101 (binary)
                    base = 2;
                    offset = 2;
                }
                else if (starts_with_zero) {
                    //012345 (octal)
                    base = 8;
                    offset = 1;
                }
            }

            long long number = 0;
            long long multiplier = 1;

            for (std::size_t i = 0; i < N - offset; ++i) {
                char c = arr[N - 1 - i];
                if (c != '\'') { // skip digit separators
                    number += to_int(c) * multiplier;
                    multiplier *= base;
                }
            }

            return number;
        }
    }

    namespace literals {
        template <char ...c>
        constexpr auto operator"" _c() {
            return hana::llong<ic_detail::parse<sizeof...(c)>({c...})>{};
        }
    }

    //////////////////////////////////////////////////////////////////////////
    // Model of Constant/IntegralConstant
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct IntegralConstant<integral_constant_tag<T>> {
        static constexpr bool value = true;
    };

    template <typename T, typename C>
    struct to_impl<integral_constant_tag<T>, C, when<hana::IntegralConstant<C>::value>>
        : embedding<is_embedded<typename C::value_type, T>::value>
    {
        template <typename N>
        static constexpr auto apply(N const&)
        { return integral_constant<T, N::value>{}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Optimizations
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct eval_if_impl<integral_constant_tag<T>> {
        template <typename Cond, typename Then, typename Else>
        static constexpr decltype(auto)
        apply(Cond const&, Then&& t, Else&& e) {
            constexpr bool cond = static_cast<bool>(Cond::value);
            return eval_if_impl::apply(hana::bool_<cond>{},
                                       static_cast<Then&&>(t),
                                       static_cast<Else&&>(e));
        }

        template <typename Then, typename Else>
        static constexpr decltype(auto)
        apply(hana::true_ const&, Then&& t, Else&&)
        { return hana::eval(static_cast<Then&&>(t)); }

        template <typename Then, typename Else>
        static constexpr decltype(auto)
        apply(hana::false_ const&, Then&&, Else&& e)
        { return hana::eval(static_cast<Else&&>(e)); }
    };

    template <typename T>
    struct if_impl<integral_constant_tag<T>> {
        template <typename Cond, typename Then, typename Else>
        static constexpr decltype(auto)
        apply(Cond const&, Then&& t, Else&& e) {
            constexpr bool cond = static_cast<bool>(Cond::value);
            return if_impl::apply(hana::bool_<cond>{},
                                  static_cast<Then&&>(t),
                                  static_cast<Else&&>(e));
        }

        //! @todo We could return `Then` instead of `auto` to sometimes save
        //! a copy, but that would break some code that would return a
        //! reference to a `type` object. I think the code that would be
        //! broken should be changed, but more thought needs to be given.
        template <typename Then, typename Else>
        static constexpr auto
        apply(hana::true_ const&, Then&& t, Else&&)
        { return static_cast<Then&&>(t); }

        template <typename Then, typename Else>
        static constexpr auto
        apply(hana::false_ const&, Then&&, Else&& e)
        { return static_cast<Else&&>(e); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_BOOL_HPP

/* bool.hpp
mCv4mNGa7SK1Nds7dblTvHfUtG9UP4+88RLszni3GP8R8NcO529a9Ei446Xa/hegL2bmi2uMPgL+hqX4xZ2b+Q5A2/8i7ulK8XP7J/JVMvxHwC8vya9KZZi1dbX9LyEuZOaL3cFo+8Ff5D/43FpYOv/xZbyJMvNF9nmy/QGwf9X3bZEdcUWsHsrYxeXsNyUtkV1Z+Tr++Yrz6+9L80XYd4B91bvh7Lp2Xq0dYm/8KuIQn4eza3bejZWt3z+CfV643axcXf/5NefXlVNGrh1V27lW3UAKzfVrwN8klN9mJxs0Mb8p0e8/8Re6xkP5TuC/id+32obuOfAXfp40tmGmAbFCXzyZKsb94ty1dWg8Kt/AuTNesi3scXPi3wN+dQi/mJJrKdlJqfcm5W9Cu8W498msha1p3wf725B50BSICPC2Q+//byFvtkQ7uNeCHn+wb/s4lK1uygvqq6OXla/Hfxja9u+H87ltp33gEbCPNc59ddx3ROtq2iKxukh7Rywa2WnnSEtdhLkt2v+b7fz6pg+MbYnUYSlw94X2/8C/LIyPnUjqXNj2beROhvKbxPYi6oNZaMM25jbUR2vsFwrsd1fE3/YdxH1D+FK+AY3B0+D/OWrmS57N1Af1I7grDmlDw4DMGOj3f+A/G8a38bxxLT3+7+K96XtGtkrtt3disTcy94D/e8A35NcY0vv/e9BIcPvhysak59NHhn0L2K/PDmOrTx/mvDZir/++8+sXw9nq04eXrfWfwR4YN7AFaqnT/C4bxRWu32bfpwd3DiPxrwB/1MiX39vKPsAdl7Hf9fEmtrddAv6kyX4h/4J87bXH8FZq0sc2uNoSeSi6/gvaMRbeDhHuMuPQ3gnlbsnK3YbmPLhHBOZcuIvLPQe0/u8ENIc/MLVFu7is7Aoad7AvCGFj9bPvPVvQ2v8Q9z5jIfym/2H9ow0PjZraoNw7Ad8GbBVTQv6XkQ23ivlum9beGWCv+56Jrdwq5v7W738/gpbEOz6ugP6Sfv8L5tPuPV4d6ajXbNO5636SvT+CPa1zKmub6reraKtpr9kxxvzeWevfTuFMMzAl8zcnwH19hhuBoey57MTs+Bg+o58poFVAzOfBHHUxaUS5Y6HErP4EfmKAyZ/jp/OfwRz+DEy8aiFBvlimv5d7XGkOl3+Ke8iPDWxJ/Qtw05PEbYu0KK5K1klV9Be6qoS4ZdOIAZi48Tx7DglxLwA3/ZaPq76q04kcu99P3CU+g7bLOyZunH2/IO4QuC0Be/cXqf0HrnLy8V7i/SA335Pq4t43iDsAbpfB3lx/voe7n7X+O7j7mrjZnEjsWusffoFcwyBbbVkyd/ZTYHaYmNZBiptmz4umMd7rS+T3Bdki/UzcYXAP/DDITVppSyonq+0rvOma8HGVggyEucS0Hp8H+4Z3fewea0BtXRWd/V2sXK1/9zV0DcaCXCX91leRyrDvmbr+D9jn+edXMiU2t8q/wd2An5lIW3EBDW59/oO7r/8cVmdwhTqLpbhl38Lf8dvb3FA8Envi+R5Wrv7+Bfe9iSC3z1JKJNaB7H1N82qJ75xfPx9ks2um6vMfzOEgU6TOkz7/v3d+/WqQK7pHD4A7a5y4dXaRhkxSCS0LvOcg7rfgPmvmssdO6E4r9wNiphNuLin3a4kdsZy9L8H/czycLxWrTf+IWKnRdmidxfOpBDOfbJ8Gv8rIt9O02evFke09P6G2VoA98/ZOdX0fN1/7f+AvFuSrN3FJ0bo/e/2M3C3fnDug38rbosDMurC6/g24606YuNmMpf5o9z5znxN/r19QA6YUP5Ht59at0faDP2Xsd/Vcb1Nbxp99b9f6378ibhPGL+evXaA=
*/