/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    pack.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_PACK_H
#define BOOST_HOF_GUARD_FUNCTION_PACK_H

/// pack
/// ====
/// 
/// Description
/// -----------
/// 
/// The `pack` function returns a higher order function object that takes a
/// function that will be passed the initial elements. The function object is
/// a sequence that can be unpacked with `unpack_adaptor` as well. Also,
/// `pack_join` can be used to join multiple packs together.
/// 
/// Synopsis
/// --------
/// 
///     // Decay everything before capturing
///     template<class... Ts>
///     constexpr auto pack(Ts&&... xs);
/// 
///     // Capture lvalues by reference and rvalue reference by reference
///     template<class... Ts>
///     constexpr auto pack_forward(Ts&&... xs);
/// 
///     // Capture lvalues by reference and rvalues by value.
///     template<class... Ts>
///     constexpr auto pack_basic(Ts&&... xs);
/// 
///     // Join multiple packs together
///     template<class... Ts>
///     constexpr auto pack_join(Ts&&... xs);
/// 
/// Semantics
/// ---------
/// 
///     assert(pack(xs...)(f) == f(xs...));
///     assert(unpack(f)(pack(xs...)) == f(xs...));
/// 
///     assert(pack_join(pack(xs...), pack(ys...)) == pack(xs..., ys...));
/// 
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     struct sum
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     int main() {
///         int r = pack(3, 2)(sum());
///         assert(r == 5);
///     }
/// 
/// See Also
/// --------
/// 
/// * [unpack](unpack)
/// 

#include <boost/hof/detail/seq.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/remove_rvalue_reference.hpp>
#include <boost/hof/detail/unwrap.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/unpack_sequence.hpp>
#include <boost/hof/returns.hpp>
#include <boost/hof/alias.hpp>
#include <boost/hof/decay.hpp>

namespace boost { namespace hof { namespace detail {

template<class...>
struct pack_tag
{};

template<class T, class Tag>
struct pack_holder
: detail::alias_empty<T, Tag>
{};

template<class Seq, class... Ts>
struct pack_base;

template<class T>
struct is_copyable
: std::integral_constant<bool, (
    BOOST_HOF_IS_CONSTRUCTIBLE(T, const T&)
)>
{};

template<class T>
struct is_copyable<T&>
: std::true_type
{};

template<class T>
struct is_copyable<T&&>
: std::true_type
{};

template<class T, class Tag, class X, class... Ts, typename std::enable_if<
    is_copyable<T>::value && !std::is_lvalue_reference<T>::value
, int>::type = 0>
constexpr T pack_get(X&& x, Ts&&... xs) noexcept(BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(T))
{
    return static_cast<T>(boost::hof::alias_value<Tag, T>(BOOST_HOF_FORWARD(X)(x), xs...));
}

template<class T, class Tag, class X, class... Ts, typename std::enable_if<
    std::is_lvalue_reference<T>::value
, int>::type = 0>
constexpr T pack_get(X&& x, Ts&&... xs) noexcept
{
    return boost::hof::alias_value<Tag, T>(x, xs...);
}

template<class T, class Tag, class X, class... Ts, typename std::enable_if<
    !is_copyable<T>::value
, int>::type = 0>
constexpr auto pack_get(X&& x, Ts&&... xs) BOOST_HOF_RETURNS
(
    boost::hof::alias_value<Tag, T>(BOOST_HOF_FORWARD(X)(x), xs...)
);

#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7) || defined(_MSC_VER)
template<class... Ts>
struct pack_holder_base
: Ts::type...
{
    template<class... Xs, class=typename std::enable_if<(sizeof...(Xs) == sizeof...(Ts))>::type>
    constexpr pack_holder_base(Xs&&... xs) 
    BOOST_HOF_NOEXCEPT(BOOST_HOF_AND_UNPACK(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(typename Ts::type, Xs&&)))
    : Ts::type(BOOST_HOF_FORWARD(Xs)(xs))...
    {}
#ifndef _MSC_VER
    // BOOST_HOF_INHERIT_DEFAULT(pack_holder_base, typename std::remove_cv<typename std::remove_reference<typename Ts::type>::type>::type...)
    BOOST_HOF_INHERIT_DEFAULT(pack_holder_base, typename Ts::type...)
#endif
};

template<class T>
struct pack_holder_base<T>
: T::type
{
    typedef typename T::type base;
    BOOST_HOF_INHERIT_CONSTRUCTOR(pack_holder_base, base);
};

template<class... Ts>
struct pack_holder_builder
{
    template<class T, std::size_t N>
    struct apply
    : pack_holder<T, pack_tag<seq<N>, Ts...>>
    {};
};

template<std::size_t... Ns, class... Ts>
struct pack_base<seq<Ns...>, Ts...>
: pack_holder_base<typename pack_holder_builder<Ts...>::template apply<Ts, Ns>...>
{
    typedef pack_holder_base<typename pack_holder_builder<Ts...>::template apply<Ts, Ns>...> base;
    template<class X1, class X2, class... Xs>
    constexpr pack_base(X1&& x1, X2&& x2, Xs&&... xs)
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(base, X1&&, X2&&, Xs&...))
    : base(BOOST_HOF_FORWARD(X1)(x1), BOOST_HOF_FORWARD(X2)(x2), BOOST_HOF_FORWARD(Xs)(xs)...)
    {}

    template<class X1, typename std::enable_if<(BOOST_HOF_IS_CONSTRUCTIBLE(base, X1)), int>::type = 0>
    constexpr pack_base(X1&& x1)
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(base, X1&&))
    : base(BOOST_HOF_FORWARD(X1)(x1))
    {}

    // BOOST_HOF_INHERIT_DEFAULT(pack_base, typename std::remove_cv<typename std::remove_reference<Ts>::type>::type...);
    BOOST_HOF_INHERIT_DEFAULT(pack_base, Ts...);

    BOOST_HOF_RETURNS_CLASS(pack_base);
  
    template<class F>
    constexpr auto operator()(F&& f) const BOOST_HOF_RETURNS
    (
        f(boost::hof::detail::pack_get<Ts, pack_tag<seq<Ns>, Ts...>>(*BOOST_HOF_CONST_THIS, f)...)
    );

    typedef std::integral_constant<std::size_t, sizeof...(Ts)> fit_function_param_limit;

    template<class F>
    struct apply
    : F::template apply<Ts...>
    {};
};

template<class T>
struct pack_base<seq<0>, T>
: pack_holder_base<pack_holder<T, pack_tag<seq<0>, T>>>
{
    typedef pack_holder_base<pack_holder<T, pack_tag<seq<0>, T>>> base;

    template<class X1, typename std::enable_if<(BOOST_HOF_IS_CONSTRUCTIBLE(base, X1)), int>::type = 0>
    constexpr pack_base(X1&& x1) 
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(base, X1&&))
    : base(BOOST_HOF_FORWARD(X1)(x1))
    {}

    BOOST_HOF_INHERIT_DEFAULT(pack_base, T);

    BOOST_HOF_RETURNS_CLASS(pack_base);
  
    template<class F>
    constexpr auto operator()(F&& f) const BOOST_HOF_RETURNS
    (
        f(boost::hof::detail::pack_get<T, pack_tag<seq<0>, T>>(*BOOST_HOF_CONST_THIS, f))
    );

    typedef std::integral_constant<std::size_t, 1> fit_function_param_limit;

    template<class F>
    struct apply
    : F::template apply<T>
    {};
};

#else

template<std::size_t... Ns, class... Ts>
struct pack_base<seq<Ns...>, Ts...>
: pack_holder<Ts, pack_tag<seq<Ns>, Ts...>>::type...
{
    // BOOST_HOF_INHERIT_DEFAULT(pack_base, typename std::remove_cv<typename std::remove_reference<Ts>::type>::type...);
    BOOST_HOF_INHERIT_DEFAULT(pack_base, Ts...);
    
    template<class... Xs, BOOST_HOF_ENABLE_IF_CONVERTIBLE_UNPACK(Xs&&, typename pack_holder<Ts, pack_tag<seq<Ns>, Ts...>>::type)>
    constexpr pack_base(Xs&&... xs) 
    BOOST_HOF_NOEXCEPT(BOOST_HOF_AND_UNPACK(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(typename pack_holder<Ts, pack_tag<seq<Ns>, Ts...>>::type, Xs&&)))
    : pack_holder<Ts, pack_tag<seq<Ns>, Ts...>>::type(BOOST_HOF_FORWARD(Xs)(xs))...
    {}

    // typedef pack_base<seq<Ns...>, Ts...> self_t;

    BOOST_HOF_RETURNS_CLASS(pack_base);
  
    template<class F>
    constexpr auto operator()(F&& f) const BOOST_HOF_RETURNS
    (
        f(boost::hof::detail::pack_get<Ts, pack_tag<seq<Ns>, Ts...>>(*BOOST_HOF_CONST_THIS, f)...)
    );

    typedef std::integral_constant<std::size_t, sizeof...(Ts)> fit_function_param_limit;

    template<class F>
    struct apply
    : F::template apply<Ts...>
    {};
};

#endif

template<>
struct pack_base<seq<> >
{
    template<class F>
    constexpr auto operator()(F&& f) const BOOST_HOF_RETURNS
    (f());

    typedef std::integral_constant<std::size_t, 0> fit_function_param_limit;

    template<class F>
    struct apply
    : F::template apply<>
    {};
};

#define BOOST_HOF_DETAIL_UNPACK_PACK_BASE(ref, move) \
template<class F, std::size_t... Ns, class... Ts> \
constexpr auto unpack_pack_base(F&& f, pack_base<seq<Ns...>, Ts...> ref x) \
BOOST_HOF_RETURNS(f(boost::hof::alias_value<pack_tag<seq<Ns>, Ts...>, Ts>(move(x), f)...))
BOOST_HOF_UNARY_PERFECT_FOREACH(BOOST_HOF_DETAIL_UNPACK_PACK_BASE)

template<class P1, class P2>
struct pack_join_base;

// TODO: Extend to join more than two packs at a time
template<std::size_t... Ns1, class... Ts1, std::size_t... Ns2, class... Ts2>
struct pack_join_base<pack_base<seq<Ns1...>, Ts1...>, pack_base<seq<Ns2...>, Ts2...>>
{
    static constexpr long total_size = sizeof...(Ts1) + sizeof...(Ts2);
    typedef pack_base<typename detail::gens<total_size>::type, Ts1..., Ts2...> result_type;

    template<class P1, class P2>
    static constexpr result_type call(P1&& p1, P2&& p2)
    BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(
        result_type(
            boost::hof::detail::pack_get<Ts1, pack_tag<seq<Ns1>, Ts1...>>(BOOST_HOF_FORWARD(P1)(p1))..., 
            boost::hof::detail::pack_get<Ts2, pack_tag<seq<Ns2>, Ts2...>>(BOOST_HOF_FORWARD(P2)(p2))...)
    )
    {
        return result_type(
            boost::hof::detail::pack_get<Ts1, pack_tag<seq<Ns1>, Ts1...>>(BOOST_HOF_FORWARD(P1)(p1))..., 
            boost::hof::detail::pack_get<Ts2, pack_tag<seq<Ns2>, Ts2...>>(BOOST_HOF_FORWARD(P2)(p2))...);
    }
};

template<class P1, class P2>
struct pack_join_result 
: pack_join_base<
    typename std::remove_cv<typename std::remove_reference<P1>::type>::type, 
    typename std::remove_cv<typename std::remove_reference<P2>::type>::type
>
{};


struct pack_basic_f
{
    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const BOOST_HOF_RETURNS
    (
        pack_base<typename gens<sizeof...(Ts)>::type, typename remove_rvalue_reference<Ts>::type...>(BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

struct pack_forward_f
{
    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const BOOST_HOF_RETURNS
    (
        pack_base<typename gens<sizeof...(Ts)>::type, Ts&&...>(BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

struct pack_f
{
    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const BOOST_HOF_RETURNS
    (
        pack_basic_f()(boost::hof::decay(BOOST_HOF_FORWARD(Ts)(xs))...)
    );
};

template<class P1, class P2>
constexpr typename pack_join_result<P1, P2>::result_type make_pack_join_dual(P1&& p1, P2&& p2)
BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(pack_join_result<P1, P2>::call(BOOST_HOF_FORWARD(P1)(p1), BOOST_HOF_FORWARD(P2)(p2)))
{
    return pack_join_result<P1, P2>::call(BOOST_HOF_FORWARD(P1)(p1), BOOST_HOF_FORWARD(P2)(p2));
}

// Manually compute join return type to make older gcc happy
template<class... Ts>
struct join_type;

template<class T>
struct join_type<T>
{
    typedef T type;
};

template<class T, class... Ts>
struct join_type<T, Ts...>
{
    typedef typename pack_join_result<T, typename join_type<Ts...>::type>::result_type type;
};

template<class P1>
constexpr P1 make_pack_join(P1&& p1) BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(P1, P1&&)
{
    return BOOST_HOF_FORWARD(P1)(p1);
}

template<class P1, class... Ps>
constexpr typename join_type<P1, Ps...>::type make_pack_join(P1&& p1, Ps&&... ps)
BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(make_pack_join_dual(BOOST_HOF_FORWARD(P1)(p1), make_pack_join(BOOST_HOF_FORWARD(Ps)(ps)...)))
{
    return make_pack_join_dual(BOOST_HOF_FORWARD(P1)(p1), make_pack_join(BOOST_HOF_FORWARD(Ps)(ps)...));
}

struct pack_join_f
{

    template<class... Ps>
    constexpr auto operator()(Ps&&... ps) const BOOST_HOF_RETURNS
    (
        make_pack_join(BOOST_HOF_FORWARD(Ps)(ps)...)
    );
};

}

BOOST_HOF_DECLARE_STATIC_VAR(pack_basic, detail::pack_basic_f);
BOOST_HOF_DECLARE_STATIC_VAR(pack_forward, detail::pack_forward_f);
BOOST_HOF_DECLARE_STATIC_VAR(pack, detail::pack_f);

BOOST_HOF_DECLARE_STATIC_VAR(pack_join, detail::pack_join_f);

template<class T, class... Ts>
struct unpack_sequence<detail::pack_base<T, Ts...>>
{
    template<class F, class P>
    constexpr static auto apply(F&& f, P&& p) BOOST_HOF_RETURNS
    (
        boost::hof::detail::unpack_pack_base(BOOST_HOF_FORWARD(F)(f), BOOST_HOF_FORWARD(P)(p))
    );
};

}} // namespace boost::hof

#endif

/* pack.hpp
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
*/