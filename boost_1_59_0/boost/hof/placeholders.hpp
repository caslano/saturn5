/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    placeholders.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_PLACEHOLDERS_H
#define BOOST_HOF_GUARD_FUNCTION_PLACEHOLDERS_H

/// placeholders
/// ============
/// 
/// Description
/// -----------
/// 
/// The placeholders provide `std::bind` compatible placeholders that
/// additionally provide basic C++ operators that creates bind expressions.
/// Each bind expression supports `constexpr` function evaluation.
/// 
/// Synopsis
/// --------
/// 
///     namespace placeholders {
///         placeholder<1> _1 = {};
///         placeholder<2> _2 = {};
///         placeholder<3> _3 = {};
///         placeholder<4> _4 = {};
///         placeholder<5> _5 = {};
///         placeholder<6> _6 = {};
///         placeholder<7> _7 = {};
///         placeholder<8> _8 = {};
///         placeholder<9> _9 = {};
///     }
/// 
/// Operators
/// ---------
/// 
/// * Binary operators: +,-,*,/,%,>>,<<,>,<,<=,>=,==,!=,&,^,|,&&,||
/// * Assign operators: +=,-=,*=,/=,%=,>>=,<<=,&=,|=,^=
/// * Unary operators: !,~,+,-,*,++,--
/// 
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     int main() {
///         auto sum = _1 + _2;
///         assert(3 == sum(1, 2));
///     }
/// 
/// 
/// unamed placeholder
/// ==================
/// 
/// Description
/// -----------
/// 
/// The unamed placeholder can be used to build simple functions from C++
/// operators. 
/// 
/// Note: The function produced by the unamed placeholder is not a bind expression.
/// 
/// Synopsis
/// --------
/// 
///     namespace placeholders {
///         /* unspecified */ _ = {};
///     }
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     int main() {
///         auto sum = _ + _;
///         assert(3 == sum(1, 2));
///     }
/// 

#include <boost/hof/returns.hpp>
#include <boost/hof/lazy.hpp>
#include <boost/hof/protect.hpp>

#if defined(_MSC_VER) && _MSC_VER >= 1910
#include <boost/hof/detail/pp.hpp>
#endif

namespace boost { namespace hof { namespace detail {
    template<int N>
    struct simple_placeholder
    {};
}}} // namespace boost::hof

namespace std {
    template<int N>
    struct is_placeholder<boost::hof::detail::simple_placeholder<N>>
    : std::integral_constant<int, N>
    {};
}


namespace boost { namespace hof {

#define BOOST_HOF_FOREACH_BINARY_OP(m) \
    m(+, add) \
    m(-, subtract) \
    m(*, multiply) \
    m(/, divide) \
    m(%, remainder) \
    m(>>, shift_right) \
    m(<<, shift_left) \
    m(>, greater_than) \
    m(<, less_than) \
    m(<=, less_than_equal) \
    m(>=, greater_than_equal) \
    m(==, equal) \
    m(!=, not_equal) \
    m(&, bit_and) \
    m(^, xor_) \
    m(|, bit_or) \
    m(&&, and_) \
    m(||, or_)

#define BOOST_HOF_FOREACH_ASSIGN_OP(m) \
    m(+=, assign_add) \
    m(-=, assign_subtract) \
    m(*=, assign_multiply) \
    m(/=, assign_divide) \
    m(%=, assign_remainder) \
    m(>>=, assign_right_shift) \
    m(<<=, assign_left_shift) \
    m(&=, assign_bit_and) \
    m(|=, assign_bit_or) \
    m(^=, assign_xor)

#ifndef _MSC_VER
#define BOOST_HOF_FOREACH_UNARY_OP(m) \
    m(!, not_) \
    m(~, compl_) \
    m(+, unary_plus) \
    m(-, unary_subtract) \
    m(*, dereference) \
    m(++, increment) \
    m(--, decrement)
#else
#define BOOST_HOF_FOREACH_UNARY_OP(m) \
    m(!, not_) \
    m(~, compl_) \
    m(+, unary_plus) \
    m(-, unary_subtract) \
    m(*, dereference)
#endif

namespace operators {

struct call
{
    template<class F, class... Ts>
    constexpr auto operator()(F&& f, Ts&&... xs) const BOOST_HOF_RETURNS
    (f(BOOST_HOF_FORWARD(Ts)(xs)...));
};

// MSVC 2017 ICEs on && and || in conxtexpr, so we fallback on bitwise operators
#if defined(_MSC_VER) && _MSC_VER >= 1910
#define BOOST_HOF_BINARY_OP_SKIP_and_ ()
#define BOOST_HOF_BINARY_OP_SKIP_or_ ()

struct and_
{
    template<class T, class U>
    constexpr auto operator()(T&& x, U&& y) const 
    noexcept(noexcept(BOOST_HOF_FORWARD(T)(x) && BOOST_HOF_FORWARD(U)(y)))
    -> decltype(BOOST_HOF_FORWARD(T)(x) && BOOST_HOF_FORWARD(U)(y)) 
    { return BOOST_HOF_FORWARD(T)(x) & BOOST_HOF_FORWARD(U)(y); }
};

struct or_
{
    template<class T, class U>
    constexpr auto operator()(T&& x, U&& y) const 
    noexcept(noexcept(BOOST_HOF_FORWARD(T)(x) || BOOST_HOF_FORWARD(U)(y)))
    -> decltype(BOOST_HOF_FORWARD(T)(x) || BOOST_HOF_FORWARD(U)(y)) 
    { return BOOST_HOF_FORWARD(T)(x) | BOOST_HOF_FORWARD(U)(y); }
};

#define BOOST_HOF_BINARY_OP_IMPL(op, name) \
    struct name \
    { \
        template<class T, class U> \
        BOOST_HOF_USING(ex_failure, decltype(std::declval<T>() op std::declval<U>())); \
        struct failure : as_failure<ex_failure> {}; \
        template<class T, class U> \
        constexpr auto operator()(T&& x, U&& y) const BOOST_HOF_RETURNS \
        (BOOST_HOF_FORWARD(T)(x) op BOOST_HOF_FORWARD(U)(y)); \
    };

#define BOOST_HOF_BINARY_OP(op, name) \
    BOOST_HOF_PP_IIF(BOOST_HOF_PP_IS_PAREN(BOOST_HOF_PP_CAT(BOOST_HOF_BINARY_OP_SKIP_, name))) \
    (BOOST_HOF_PP_EMPTY, BOOST_HOF_BINARY_OP_IMPL)(op, name)

#else

#define BOOST_HOF_BINARY_OP(op, name) \
    struct name \
    { \
        template<class T, class U> \
        constexpr auto operator()(T&& x, U&& y) const BOOST_HOF_RETURNS \
        (BOOST_HOF_FORWARD(T)(x) op BOOST_HOF_FORWARD(U)(y)); \
    };

#endif

BOOST_HOF_FOREACH_BINARY_OP(BOOST_HOF_BINARY_OP)
BOOST_HOF_FOREACH_ASSIGN_OP(BOOST_HOF_BINARY_OP)

#define BOOST_HOF_UNARY_OP(op, name) \
    struct name \
    { \
        template<class T> \
        constexpr auto operator()(T&& x) const BOOST_HOF_RETURNS \
        (op(BOOST_HOF_FORWARD(T)(x))); \
    };


BOOST_HOF_FOREACH_UNARY_OP(BOOST_HOF_UNARY_OP)


}

template<int N>
struct placeholder
{
#if BOOST_HOF_HAS_MANGLE_OVERLOAD
    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const BOOST_HOF_RETURNS 
    ( boost::hof::lazy(operators::call())(detail::simple_placeholder<N>(), BOOST_HOF_FORWARD(Ts)(xs)...) );
#else
    template<class... Ts>
    struct result_call
    { typedef decltype(boost::hof::lazy(operators::call())(detail::simple_placeholder<N>(), std::declval<Ts>()...)) type; };
    template<class... Ts>
    constexpr typename result_call<Ts...>::type operator()(Ts&&... xs) const 
    { return boost::hof::lazy(operators::call())(detail::simple_placeholder<N>(), BOOST_HOF_FORWARD(Ts)(xs)...); };

#endif

#define BOOST_HOF_PLACEHOLDER_UNARY_OP(op, name) \
    constexpr auto operator op () const BOOST_HOF_RETURNS \
    ( boost::hof::lazy(operators::name())(detail::simple_placeholder<N>()) );

BOOST_HOF_FOREACH_UNARY_OP(BOOST_HOF_PLACEHOLDER_UNARY_OP)

#define BOOST_HOF_PLACEHOLDER_ASSIGN_OP(op, name) \
    template<class T> \
    constexpr auto operator op (T&& x) const BOOST_HOF_RETURNS \
    ( boost::hof::lazy(operators::name())(detail::simple_placeholder<N>(), BOOST_HOF_FORWARD(T)(x)) );

BOOST_HOF_FOREACH_ASSIGN_OP(BOOST_HOF_PLACEHOLDER_ASSIGN_OP)

};

#if BOOST_HOF_HAS_MANGLE_OVERLOAD

#define BOOST_HOF_PLACEHOLDER_BINARY_OP(op, name) \
    template<class T, int N> \
    constexpr inline auto operator op (const placeholder<N>&, T&& x) BOOST_HOF_RETURNS \
    ( boost::hof::lazy(operators::name())(detail::simple_placeholder<N>(), BOOST_HOF_FORWARD(T)(x)) ); \
    template<class T, int N> \
    constexpr inline auto operator op (T&& x, const placeholder<N>&) BOOST_HOF_RETURNS \
    ( boost::hof::lazy(operators::name())(BOOST_HOF_FORWARD(T)(x), detail::simple_placeholder<N>()) ); \
    template<int N, int M> \
    constexpr inline auto operator op (const placeholder<N>&, const placeholder<M>&) BOOST_HOF_RETURNS \
    ( boost::hof::lazy(operators::name())(detail::simple_placeholder<N>(), detail::simple_placeholder<M>()) );

#else

#define BOOST_HOF_PLACEHOLDER_BINARY_OP(op, name) \
    template<class T, class U> \
    struct result_ ## name \
    { typedef decltype(boost::hof::lazy(operators::name())(std::declval<T>(), std::declval<U>())) type; }; \
    template<class T, int N> \
    constexpr inline typename result_ ## name<detail::simple_placeholder<N>, T>::type operator op (const placeholder<N>&, T&& x) \
    { return boost::hof::lazy(operators::name())(detail::simple_placeholder<N>(), BOOST_HOF_FORWARD(T)(x)); } \
    template<class T, int N> \
    constexpr inline typename result_ ## name<T, detail::simple_placeholder<N>>::type operator op (T&& x, const placeholder<N>&) \
    { return boost::hof::lazy(operators::name())(BOOST_HOF_FORWARD(T)(x), detail::simple_placeholder<N>()); } \
    template<int N, int M> \
    constexpr inline typename result_ ## name<detail::simple_placeholder<N>, detail::simple_placeholder<M>>::type operator op (const placeholder<N>&, const placeholder<M>&) \
    { return boost::hof::lazy(operators::name())(detail::simple_placeholder<N>(), detail::simple_placeholder<M>()); }

#endif

BOOST_HOF_FOREACH_BINARY_OP(BOOST_HOF_PLACEHOLDER_BINARY_OP)

namespace placeholders {
BOOST_HOF_DECLARE_STATIC_VAR(_1, placeholder<1>);
BOOST_HOF_DECLARE_STATIC_VAR(_2, placeholder<2>);
BOOST_HOF_DECLARE_STATIC_VAR(_3, placeholder<3>);
BOOST_HOF_DECLARE_STATIC_VAR(_4, placeholder<4>);
BOOST_HOF_DECLARE_STATIC_VAR(_5, placeholder<5>);
BOOST_HOF_DECLARE_STATIC_VAR(_6, placeholder<6>);
BOOST_HOF_DECLARE_STATIC_VAR(_7, placeholder<7>);
BOOST_HOF_DECLARE_STATIC_VAR(_8, placeholder<8>);
BOOST_HOF_DECLARE_STATIC_VAR(_9, placeholder<9>);
}

using placeholders::_1;
using placeholders::_2;
using placeholders::_3;
using placeholders::_4;
using placeholders::_5;
using placeholders::_6;
using placeholders::_7;
using placeholders::_8;
using placeholders::_9;

namespace detail {



struct unamed_placeholder
{
template<class T, class Invoker>
struct partial_ap
{
    T val;

    BOOST_HOF_INHERIT_DEFAULT_EMPTY(partial_ap, T)

    template<class X, class... Xs, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, X&&, Xs&&...)>
    constexpr partial_ap(X&& x, Xs&&... xs) : val(BOOST_HOF_FORWARD(X)(x), BOOST_HOF_FORWARD(Xs)(xs)...)
    {}

    BOOST_HOF_RETURNS_CLASS(partial_ap);

    struct partial_ap_failure
    {
        template<class Failure>
        struct apply
        {
            template<class... Xs>
            struct of;

            template<class X>
            struct of<X>
            : Failure::template of<typename std::add_const<T>::type, X>
            {};
        };
    };

    struct failure
    : failure_map<partial_ap_failure, Invoker>
    {};

    template<class X>
    constexpr BOOST_HOF_SFINAE_RESULT(const Invoker&, id_<T>, id_<X>) 
    operator()(X&& x) const BOOST_HOF_SFINAE_RETURNS
    (
        Invoker()(BOOST_HOF_CONST_THIS->val, BOOST_HOF_FORWARD(X)(x))
    );
};

template<class Invoker, class T>
static constexpr partial_ap<T, Invoker> make_partial_ap(T&& x)
{
    return {BOOST_HOF_FORWARD(T)(x)};
}

template<class Op>
struct left
{
    struct failure
    : failure_for<Op>
    {};
    template<class T, class X>
    constexpr BOOST_HOF_SFINAE_RESULT(const Op&, id_<T>, id_<X>) 
    operator()(T&& val, X&& x) const BOOST_HOF_SFINAE_RETURNS
    (Op()(BOOST_HOF_FORWARD(T)(val), BOOST_HOF_FORWARD(X)(x)));
};

template<class Op>
struct right
{
    struct right_failure
    {
        template<class Failure>
        struct apply
        {
            template<class T, class U, class... Ts>
            struct of
            : Failure::template of<U, T, Ts...>
            {};
        };
    };

    struct failure
    : failure_map<right_failure, Op>
    {};

    template<class T, class X>
    constexpr BOOST_HOF_SFINAE_RESULT(const Op&, id_<X>, id_<T>) 
    operator()(T&& val, X&& x) const BOOST_HOF_SFINAE_RETURNS
    (Op()(BOOST_HOF_FORWARD(X)(x), BOOST_HOF_FORWARD(T)(val)));
};

#define BOOST_HOF_UNAMED_PLACEHOLDER_UNARY_OP(op, name) \
    constexpr auto operator op () const BOOST_HOF_RETURNS \
    ( operators::name() );

BOOST_HOF_FOREACH_UNARY_OP(BOOST_HOF_UNAMED_PLACEHOLDER_UNARY_OP)

#define BOOST_HOF_UNAMED_PLACEHOLDER_ASSIGN_OP(op, name) \
    template<class T> \
    constexpr auto operator op (const T& x) const BOOST_HOF_RETURNS \
    ( partial_ap<T, left<operators::name>>(x) );

BOOST_HOF_FOREACH_ASSIGN_OP(BOOST_HOF_UNAMED_PLACEHOLDER_ASSIGN_OP)
};
#define BOOST_HOF_UNAMED_PLACEHOLDER_BINARY_OP(op, name) \
    template<class T> \
    constexpr inline auto operator op (const unamed_placeholder&, const T& x) BOOST_HOF_RETURNS \
    ( unamed_placeholder::make_partial_ap<unamed_placeholder::right<operators::name>>(boost::hof::decay(x)) ); \
    template<class T> \
    constexpr inline auto operator op (const T& x, const unamed_placeholder&) BOOST_HOF_RETURNS \
    ( unamed_placeholder::make_partial_ap<unamed_placeholder::left<operators::name>>(boost::hof::decay(x)) ); \
    constexpr inline auto operator op (const unamed_placeholder&, const unamed_placeholder&) BOOST_HOF_RETURNS \
    ( operators::name() );

BOOST_HOF_FOREACH_BINARY_OP(BOOST_HOF_UNAMED_PLACEHOLDER_BINARY_OP)
}

namespace placeholders {
BOOST_HOF_DECLARE_STATIC_VAR(_, detail::unamed_placeholder);
}

using placeholders::_;

}} // namespace boost::hof

namespace std {
    template<int N>
    struct is_placeholder<boost::hof::placeholder<N>>
    : std::integral_constant<int, N>
    {};
}

namespace boost {

    template<class T> 
    struct is_placeholder;

    template<int N>
    struct is_placeholder<boost::hof::placeholder<N>>
    : std::integral_constant<int, N>
    {};


}

#endif

/* placeholders.hpp
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
*/