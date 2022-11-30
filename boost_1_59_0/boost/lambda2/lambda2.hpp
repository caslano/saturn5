#ifndef BOOST_LAMBDA2_LAMBDA2_HPP_INCLUDED
#define BOOST_LAMBDA2_LAMBDA2_HPP_INCLUDED

// Copyright 2020, 2021 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <functional>
#include <type_traits>
#include <utility>
#include <tuple>
#include <cstddef>
#include <iosfwd>

// Same format as BOOST_VERSION:
//   major * 100000 + minor * 100 + patch
#define BOOST_LAMBDA2_VERSION 107900

namespace boost
{
namespace lambda2
{

namespace lambda2_detail
{

struct subscript
{
    template<class T1, class T2> decltype(auto) operator()(T1&& t1, T2&& t2) const
    {
        return std::forward<T1>(t1)[ std::forward<T2>(t2) ];
    }
};

template<int I> struct get
{
    template<class T> decltype(auto) operator()( T&& t ) const
    {
        return std::get<I>( std::forward<T>(t) );
    }
};

} // namespace lambda2_detail

// placeholders

template<int I> struct lambda2_arg
{
    template<class... A> decltype(auto) operator()( A&&... a ) const noexcept
    {
        return std::get<std::size_t{I-1}>( std::tuple<A&&...>( std::forward<A>(a)... ) );
    }

    template<class T> auto operator[]( T&& t ) const
    {
        return std::bind( lambda2_detail::subscript(), *this, std::forward<T>( t ) );
    }
};

#if defined(__cpp_inline_variables) && __cpp_inline_variables >= 201606L
# define BOOST_LAMBDA2_INLINE_VAR inline
#else
# define BOOST_LAMBDA2_INLINE_VAR
#endif

BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<1> _1{};
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<2> _2{};
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<3> _3{};
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<4> _4{};
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<5> _5{};
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<6> _6{};
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<7> _7{};
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<8> _8{};
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<9> _9{};

// first, second

BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_detail::get<0> first{};
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_detail::get<1> second{};

#undef BOOST_LAMBDA2_INLINE_VAR

} // namespace lambda2
} // namespace boost

namespace std
{

template<int I> struct is_placeholder< boost::lambda2::lambda2_arg<I> >: integral_constant<int, I>
{
};

} // namespace std

namespace boost
{
namespace lambda2
{

namespace lambda2_detail
{

// additional function objects

#define BOOST_LAMBDA2_UNARY_FN(op, fn) \
    struct fn \
    { \
        template<class T> decltype(auto) operator()(T&& t) const \
        { \
            return op std::forward<T>(t); \
        } \
    };

#define BOOST_LAMBDA2_POSTFIX_FN(op, fn) \
    struct fn \
    { \
        template<class T> decltype(auto) operator()(T&& t) const \
        { \
            return std::forward<T>(t) op; \
        } \
    };

#define BOOST_LAMBDA2_BINARY_FN(op, fn) \
    struct fn \
    { \
        template<class T1, class T2> decltype(auto) operator()(T1&& t1, T2&& t2) const \
        { \
            return std::forward<T1>(t1) op std::forward<T2>(t2); \
        } \
    };

BOOST_LAMBDA2_BINARY_FN(<<, left_shift)
BOOST_LAMBDA2_BINARY_FN(>>, right_shift)

BOOST_LAMBDA2_UNARY_FN(+, unary_plus)
BOOST_LAMBDA2_UNARY_FN(*, dereference)

BOOST_LAMBDA2_UNARY_FN(++, increment)
BOOST_LAMBDA2_UNARY_FN(--, decrement)

BOOST_LAMBDA2_POSTFIX_FN(++, postfix_increment)
BOOST_LAMBDA2_POSTFIX_FN(--, postfix_decrement)

BOOST_LAMBDA2_BINARY_FN(+=, plus_equal)
BOOST_LAMBDA2_BINARY_FN(-=, minus_equal)
BOOST_LAMBDA2_BINARY_FN(*=, multiplies_equal)
BOOST_LAMBDA2_BINARY_FN(/=, divides_equal)
BOOST_LAMBDA2_BINARY_FN(%=, modulus_equal)
BOOST_LAMBDA2_BINARY_FN(&=, bit_and_equal)
BOOST_LAMBDA2_BINARY_FN(|=, bit_or_equal)
BOOST_LAMBDA2_BINARY_FN(^=, bit_xor_equal)
BOOST_LAMBDA2_BINARY_FN(<<=, left_shift_equal)
BOOST_LAMBDA2_BINARY_FN(>>=, right_shift_equal)

// operators

template<class T> using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

template<class T, class T2 = remove_cvref_t<T>> using is_lambda_expression =
    std::integral_constant<bool, std::is_placeholder<T2>::value || std::is_bind_expression<T2>::value>;

template<class A> using enable_unary_lambda =
    std::enable_if_t<is_lambda_expression<A>::value>;

template<class A, class B> using enable_binary_lambda =
    std::enable_if_t<is_lambda_expression<A>::value || is_lambda_expression<B>::value>;

template<class T> using is_stream = std::is_base_of<std::ios_base, remove_cvref_t<T>>;

} // namespace lambda2_detail

#define BOOST_LAMBDA2_UNARY_LAMBDA(op, fn) \
    template<class A, class = lambda2_detail::enable_unary_lambda<A>> \
    auto operator op( A&& a ) \
    { \
        return std::bind( fn(), std::forward<A>(a) ); \
    }

#define BOOST_LAMBDA2_POSTFIX_LAMBDA(op, fn) \
    template<class A, class = lambda2_detail::enable_unary_lambda<A>> \
    auto operator op( A&& a, int ) \
    { \
        return std::bind( fn(), std::forward<A>(a) ); \
    }

#define BOOST_LAMBDA2_BINARY_LAMBDA(op, fn) \
    template<class A, class B, class = lambda2_detail::enable_binary_lambda<A, B>> \
    auto operator op( A&& a, B&& b ) \
    { \
        return std::bind( fn(), std::forward<A>(a), std::forward<B>(b) ); \
    }

// standard

BOOST_LAMBDA2_BINARY_LAMBDA(+, std::plus<>)
BOOST_LAMBDA2_BINARY_LAMBDA(-, std::minus<>)
BOOST_LAMBDA2_BINARY_LAMBDA(*, std::multiplies<>)
BOOST_LAMBDA2_BINARY_LAMBDA(/, std::divides<>)
BOOST_LAMBDA2_BINARY_LAMBDA(%, std::modulus<>)
BOOST_LAMBDA2_UNARY_LAMBDA(-, std::negate<>)

BOOST_LAMBDA2_BINARY_LAMBDA(==, std::equal_to<>)
BOOST_LAMBDA2_BINARY_LAMBDA(!=, std::not_equal_to<>)
BOOST_LAMBDA2_BINARY_LAMBDA(>, std::greater<>)
BOOST_LAMBDA2_BINARY_LAMBDA(<, std::less<>)
BOOST_LAMBDA2_BINARY_LAMBDA(>=, std::greater_equal<>)
BOOST_LAMBDA2_BINARY_LAMBDA(<=, std::less_equal<>)

BOOST_LAMBDA2_BINARY_LAMBDA(&&, std::logical_and<>)
BOOST_LAMBDA2_BINARY_LAMBDA(||, std::logical_or<>)
BOOST_LAMBDA2_UNARY_LAMBDA(!, std::logical_not<>)

BOOST_LAMBDA2_BINARY_LAMBDA(&, std::bit_and<>)
BOOST_LAMBDA2_BINARY_LAMBDA(|, std::bit_or<>)
BOOST_LAMBDA2_BINARY_LAMBDA(^, std::bit_xor<>)
BOOST_LAMBDA2_UNARY_LAMBDA(~, std::bit_not<>)

// additional

BOOST_LAMBDA2_UNARY_LAMBDA(+, lambda2_detail::unary_plus)
BOOST_LAMBDA2_UNARY_LAMBDA(*, lambda2_detail::dereference)

BOOST_LAMBDA2_UNARY_LAMBDA(++, lambda2_detail::increment)
BOOST_LAMBDA2_UNARY_LAMBDA(--, lambda2_detail::decrement)

BOOST_LAMBDA2_POSTFIX_LAMBDA(++, lambda2_detail::postfix_increment)
BOOST_LAMBDA2_POSTFIX_LAMBDA(--, lambda2_detail::postfix_decrement)

// compound assignment

BOOST_LAMBDA2_BINARY_LAMBDA(+=, lambda2_detail::plus_equal)
BOOST_LAMBDA2_BINARY_LAMBDA(-=, lambda2_detail::minus_equal)
BOOST_LAMBDA2_BINARY_LAMBDA(*=, lambda2_detail::multiplies_equal)
BOOST_LAMBDA2_BINARY_LAMBDA(/=, lambda2_detail::divides_equal)
BOOST_LAMBDA2_BINARY_LAMBDA(%=, lambda2_detail::modulus_equal)
BOOST_LAMBDA2_BINARY_LAMBDA(&=, lambda2_detail::bit_and_equal)
BOOST_LAMBDA2_BINARY_LAMBDA(|=, lambda2_detail::bit_or_equal)
BOOST_LAMBDA2_BINARY_LAMBDA(^=, lambda2_detail::bit_xor_equal)
BOOST_LAMBDA2_BINARY_LAMBDA(<<=, lambda2_detail::left_shift_equal)
BOOST_LAMBDA2_BINARY_LAMBDA(>>=, lambda2_detail::right_shift_equal)

// operator<<

template<class A, class = std::enable_if_t<!lambda2_detail::is_stream<A>::value>,
    class B, class = lambda2_detail::enable_binary_lambda<A, B>>
auto operator<<( A&& a, B&& b )
{
    return std::bind( lambda2_detail::left_shift(), std::forward<A>(a), std::forward<B>(b) );
}

template<class A, class = std::enable_if_t<lambda2_detail::is_stream<A>::value>,
    class B, class = lambda2_detail::enable_unary_lambda<B>>
auto operator<<( A& a, B&& b )
{
    return std::bind( lambda2_detail::left_shift(), std::ref(a), std::forward<B>(b) );
}

// operator>>

template<class A, class = std::enable_if_t<!lambda2_detail::is_stream<A>::value>,
    class B, class = lambda2_detail::enable_binary_lambda<A, B>>
auto operator>>( A&& a, B&& b )
{
    return std::bind( lambda2_detail::right_shift(), std::forward<A>(a), std::forward<B>(b) );
}

template<class A, class = std::enable_if_t<lambda2_detail::is_stream<A>::value>,
    class B, class = lambda2_detail::enable_unary_lambda<B>>
auto operator>>( A& a, B&& b )
{
    return std::bind( lambda2_detail::right_shift(), std::ref(a), std::forward<B>(b) );
}

// operator->*

template<class A, class B, class = lambda2_detail::enable_unary_lambda<A>>
auto operator->*( A&& a, B&& b )
{
    return std::bind( std::forward<B>(b), std::forward<A>(a) );
}

} // namespace lambda2
} // namespace boost

#endif // #ifndef BOOST_LAMBDA2_LAMBDA2_HPP_INCLUDED

/* lambda2.hpp
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
*/