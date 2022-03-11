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