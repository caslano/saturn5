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
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
*/