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
O5QX7Bk5FIQ91sK720c8SZqB9oInz6SvoU/Ooq8B40Z0I5+bmad9ThFJrIszn/QgHd7ErlESEekiZ/D9Xop+0u/7ys5qHLtzPVTRODBYhOpIid8vVLjyebJz5g0Fag72ZYpC2Ui26cn4mcE/v95IMvihw7B5HImZFtlmIzILbiEl+6ofE7GGNiMhnpDKCzcfN1PO+ptSny7QdNL/8YVc8XAbZX+1Mc1hhPgUA4v3pjupqtDpB8uqqUGCJ9LKRHGN26ykIXK6yvykKnFmWxEeMFqua8tVdZ4Z4sKrqaKF6SpS9RVTNnXKI26MJqnYzOdFo9rKeSs8A6c6RfiH1x++naqZc39yQ5nL22fEC8fL/hXiLP6yebOu0jlq+/1kE5W5PSxf6+j5Pw5R/ktV/iP1vye2sCCyLY+6/3iu5dr7DnsrehfKn5C3cyPlHWZ6i9T5PWIn5x65Lm3//ySp/0fB6Qb3/whz/6/4Eb7UEFjxMB5SjYIJQaousLwrZ19cf3YwcTysXG0aD0i1iTkYMyqelxGEJRf/ZKBv8cyOND1qHk+etvKJajxV4x+2Qr94gAh23Hv08aQKx8tezWXXP5a2dmWf1eyG44hwtU80XaVEEGO/4Wp2e8iP3UmMbPX13HJpVy2ihf75Z5xmcfmH5ViwzY3IGDJdzR9a2pX8vQap/G9dc2z5+3cJ/+IByD+2BPlXdgl/PP+jS7qS/4nxKv/wLuGP56/tCn7x1k+pu/LuVuPVDG9h+APb08D9t5Whvm+fTe+/sgv1JeR/dHFX8h83Dvmvnkfv3yX88fy1XcK/oBb5vxiB/C0rji3/x4u6kv+001X+i7qEP55/fVfwi0038jpyZ7r+izL879vSwV/XuP/Tln9C4/5PV94fuRD0fnkG9X9jF+hNyP9oqAv5xe7LqP6GH6aj70GG90z7fqctIHhp2vK9Gf7sU+ngY68k+Od3pIMPYvjadOX9nYV41RfCCpwavjqYFl7TF/AbwkeGV6UvP5Saenr4yPDu6cuPI/qc4SPD265OBxcr76P2eWNluva7iOFzb0qCK33/j3+j9P2soZFKNv8CqrJhOatn1Kw9snpG4atNj892tcR3VdfwKfpl4Y4GRX5q+E+/lxa+KR/wXzQcGX5J+vJLSwFf0HBk+Mnpyz88GvAzGo4M/9tVafv3lGbqvy8b0/VvD4YvX5cOPnc1wZ9MW34cw8elK+//rJbef5kCp4afnJ7+yy4h/OPT1j+Z4U/ckA7+uwC/fzgd/CGGL09b/tVL+f3Tln+M4ePM5b3+0spcl3h4q9I3s62bHOWnXi+3kFni1wFdx3ySjyLMjbjJcP+hjJCx7w4watYwMFKvWAS9HNTLd+lGJ11RPZB8K0k6+8epNC4MkwxzQyr4VoK3mvKLl34d1zymxmf8EydxvYxDwQ1xfMpWc//vH4Z10XhK3m/xRsvf5AYB2yJpNgBbC/j+8718GDGSpOMin9MFh0+5zuyJqPH4nylRf3hsSxPlnQwRC2DhRsV60uJrmCw2vyPQdYuMo7qldnlRuwDaTgL1lycd8KRPcZomrvNR4paNrEGspjs+ay9VJwPDcJdNXJ6lggcORs4q8YdN6grPM3NnK9QgvZTtqHJx9Lwszz53Nk5n6ssIdvQeP/KH9m6sW8mD1QG++tPRdmaojz//ETK/tTBDssttV7ryXm0kfXHYqLUcPwqx5M7Rf6zajh8wWPR7ROw2TBGv+DaanEIKs0Nmr1jPB2L5HHgx2BPwXXY2BqYsgQu9IgQ4/56Fi21TxMX6o/86edVtjpjJCEbiugsbaobnwJ/RymnVKwCHBvrKvOK9tVEcS4rvb1Rmhn5fTa0YDoFZE3A=
*/