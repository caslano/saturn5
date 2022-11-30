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
Ps+zECSRibVUuJ1VeNmImIq9OW+ijUjS3m9DQMOWi3b7E+uNp1igi7mpkrVZ7fH3PHtYk/xETr6s7AT9Ul59SaozEY/DQOX8elqVol0xI6s/Pz3bI4qpf3tB8F/9qBOtTE6DKySXLj+T/aDmTOc2AbcLJsXcYqOmAqbjoAWlJctfpZuBTGQhLd1+/RPSMx+drlcUAV1+iTpvLnT34lGkq1OZrDdtXV+j9kLPmXTzxKQRpxcTOU1v+jAn+s23ZKAFzIJpyuXKrjiL9MxgxvN/zTJkJ+qNiugHre/oXJIfxv+0G/0jvnxYOrJV5e0yUUhpMhR8Ce2bMbCAmj81oJwZPxN8QL7c0bygkBV3/KYxzdFWbkP53F4uQ13bRhmSTAbhTMfptp3VIQhfySpBXTG9LzobOB3esxv0muVhdvEvLm0i4oFJphIolKrDcCRWGYb3T5qh/yysvhTfR2t9WPhIOkrVAVQnM9FsByW8VnYSqEO9AhdESEauyCHACMegUMsXtp+/NPxoXqBc5iyeyfnWe5LnRHd9euI6mDVlweIY9z5h9MrjdwLmf1SbIIHswvpW/35nz/XxPIWFtxmL8JjX8EKzTyLwF9AbYnEUwFflLAf/jRuHMDgqWtGy1KStfIQK+i4E6aScXLERbmccsTGhKdpJ59H4iEEbC/w7LWZbccGiMSMk06xNedkIWl3Su0vnw3maNOxoJ8aUCs3/6714ffj9i+N1pLJj++cXKqFrpQn+AdsSbsLv7iHInSKiqMr/FhlSJcR1poippW66W7CIonx9O52o9rDkrKDBjLHpcLx3lY92MZmfMjMKF8h/s49CSliYVEJQs6vg/S9I2lUHwOs3wEYUJ8z1XS1a4sjisbIvahKcF26IgtqJFOV+f5oi9IA36w51NthwJOIHJZjzXjcDoLLPD6ZhiClhiPHeQus27jca+17ojwf/0OCeLsJWbgyKw0in6JOdhnpE3fWQsO/bBnK69Odhr+Fp5u5eu7q4sa2JfC3Jr3fWln6UbprQ65yyCyj9B2Bak5kK8r/DdS3StPNG3MrunsXPYbtXfr5vnVfJJ8vfrHyjWcfkJ574wKrmUTq0FVGCT3SVA/+OK71XrlU6zMtfC6hsPzqeWN8iP0R7nU7jWKUMCKKaLSXLX5jKbe2m8f14zP86c7Gq98MdnuQ7q7sDrFPSaHCa1vYmzSrYRHHsc1qbZn/CTJ/9C0k26MMVzwLV4dlOkc7PP9Cwgzxp6tB+yIsqvcFYjSbDtNhf+sU+ElVWHSpgM5QbXBnNXfaNqmytcOkKSc8nZKQ7WjiIYOdvPlxXX/jQsFRcys6FkPzV8HIBaGf0JBSlZrfSoYVo0lY4e7dVc5lybp1nnZrBiE0tYaRlGGElEu20HafG0wl+WKS4lwjAITkuHPThWf+GzbEKQWKl09VjOOzQo9jv2W4LWNRXDYSb+t1xItTQZY+gQpKPUG26+M9zMWNFq9mwAVDVAcNkpHedTuR9nV4Ti0S6J3KX1UfA7Pl2XAaz2pzbifPzTf5c768Huy2XP+kbyetfPY8AzL1L7GsUzGZnQ4TQPrr+cH7nRSPRwUpUa7zBjfIscThdT/4WpLVlSHw32on9V3XDxDsNobNfQzK/HCXdaUOlt+p6yemKkxzXVZyhB7j88WFflfOEpg9coWIavMZW0w0DDkQ2AfL7ARJUV8J5Qhsq1fO6C9pMbLdGQ1Wp69uGWyQf10frhx/GhGiiNHW6X4VMWyaFF0EJd3gmckLFz18PSuyUFqF1Wj+SVy+HkHjn2X8fDaRDCsFtt7nxEW5ftVQ0cHm7WTyyEm6TZOINlaHBCeialDJcAH9WAudpzunNkBh7g8weDBslD48hmNCDSCqAboqw6IOThYqw7QA5ftxvFlk7VKQF14ogmO8lWaMxKH4fPLJMSKpEW0j1It4y6y6YISUVv7/R0aJO9TtGpI7lvJUcCu54SZoKbxIwLHll3K4jVaxyTi419ie0gzj17C40W24/YiUHH2iK9IgeQ0mBTItK8lPppevTi70VG77y0Ojz6yDdHVeWSjsyy36Aot9rDg1oaHnOWCDw3/mJrTs9aWMoXTMnQyPTxJunOTlVwgTeyionbmpmXAjaDEkRozBOStkL+9naD9+pDNtGNG7KX9fBqR7U5+0eG8qNY0r6iVpauWLzw3CjJSqXJmQO3kRb1EFbK8xcR1NWfq3NIx5jgeU+PnxJgdKIEwRqbNIyAwLVlV8MrVLMud9L+owJ749jdBdNQxkkC9UstBZ17Jyslna+tmqmrmqoLB6b5E1fjmItTVr41J7yhQj8GI7kdqtRo0YrqjhGOb8YPZRjQFdRUXx0A8/1uKIvxPXZKZoxSCydkVenSa0gRp2ZD2uKour5GeuYojKBtPkovlToctPmbKXqOUkxQEG0UShA8SJkrrDtBJQfCO0ZDFM8Hzfx6FE2YROZjmwvb/9z2AmYPzcL3VNo5iaR+NGICDjmk5IhZ/BD8y3a8bXCZEiE8vswC+ggGNoXA2w66x/CPn6RU1mDR8639NwVoYzXH4VjF7AiT+VSG8PBgpthQZZnaqEa/qgT7ZcbRDPDF/+FAIdh9JyDREaXxKSMF7oLm8jg6F5khbiFJhwcP9WkXoNdWBTPyogEMbQY/gNKOpkyqn7wHEzoP3f2jMfclH8le5Fy7gcB3pnexaNLJfHrYTyHY0SugojhcDF4q32m4IrR6vsFwmBi8zdh+B2ChyJua2AoiRTITEp4cmh1xWFR9K3oiaA+IljIL5STT6AgC1Vw+yD3BPs23kUoo/TsFPZfkR/qPJRqiddydKiTE0rY5vq/sV+Wg9vs6tNU24S3ujpfy13D2mCXbK34RXn6/DgYDmQ12+TUgkSziDBR1TbkhiwqDIKwrwc0thvZ6F0+/I7zMgtJ4jLzv1AtwrHmsmoHO6+RfrUM4PJBPuBd/lwHy2VTTZo78Jztv16Heu0ZhKL78hsJ/B0fWPuZ8pKambWMcy639MWg3pErVqVkxKOldXHwMlSZnXrdEfUAFhlfXyoDqaKHlR2Gd3qRK41Ft4dq29sEP6XP/UJ/3OSbSNoZuf/KWtFP8SXu4YkwYs5W6esM8VSyeJld/yT9vqCbKrZ61PI2kgtVtTvV1YeTjenqjF4yTqfj/dLrhHQ6gSkI41CisbavxM8abh9aHP54zR7LU/QTPnIlGaniJZLGzEFURRzQeGmP/DGBe2CZzfjNdsk0PY6JvxM8z47/TlW+/aYv6oQerMd5gUHn9GeyCJSygx1laCredQs0tCvnbGd7qstN0luH8AkTsfI//ttL6d9LL/kTUyoRSr6ydxfIxqqyZ1He2p1KOX/SpD3zSmiFY2YzAsT4ee5nRVGoMVxp7i3USfZ99mARbwUjZr5HBd6dMBSW/b2+9XVbO+Qxaj1huwiB1wqC1MOPWGS0DRUihGcHS8VaknP+cLjPq5a4IaucNZ6YY4zi2NVZFkkwsxqG+qAV1+W90L7VavVLvsJzRD6YM4dS6xajiI6EllhJGAJxhRDueq5A/msDez5e14823pVhxwkhLIIMrj23CqsK3qnQgxU1E0kHV/2htZbB1TSaJDhETp9tfkPvoFr42XMdn57SESgkCyncw3SB/KvGI7VzSPt1J/40uEtF18FiSNMj3f2gLdWZ+Hl/lmGoosIeGnLE/soJ8qnPD1rMfomf7o+S5DRP+nZAxPVdwmJzcsj9cPsqVnOVL8Nsc7gOuOzy67vjkXgQaubz1FxKELSRqkmUUWdQwxtwvDYOQBUL3EcK5aTm5YSPmng9K5mJtYTgIddJwfVVBYd1KUis0bmQJUO/+C75AmnelrFUV/YwLaIUrtvrKoeQDEv9WxPuGta5UTsqccovDVLuXWjk61iW9ozVSsM+5GGDANMY3Wd8BBjHEIe652FIFwFWU0gvV0dqvWfIMnMxn3Ykr3pLW3OcFmzrutuVfVD/U0GD3RlENxcufj1cMeKw+xf04bgamF8fltw5Ey4TTfOryxcQknku/MD43swg/+dpaCEBPvSeilj5gDD4dpMt7jvBJkbTvFrAcVjeirtArrPdo3kOGUjSf44JRk2YwJ6PmXDbE+VMt9WyfZDpQJu35b7ki0vl6D879ey3HOd6R/+vtaiTrC+wsaZ9/IRD0a6j9isT50TVYvJVJOjOSJpZBh67ehp5JYdJYjm6x19IebNx9mLPafllv0t341uOYDeveGCzdvEhNoxxfWmzGx4hZ5ebMBTr+Al3qP5de52qKbznUGRmj2iATG6iw+bJq6nStXMvcKaoMlWXRkFbRZKe6SWoTC1mTtMLi2u7uazsaa/u+LwneF3+mvwoMYS5HMbX9qgf65nev9POh5kTJgNt+41OqAGc2XOT+Vf321uqfVWJJ25H2u8rv4neM2r8Z4tFoXcUnUE2pUZt/U5Ybxpj9wexFqFonT9oQnm0okK0G2pR0fxdngpqIrp0XLVtrZhY6+FjvOdCHH7Du5A4+0IcBexyZZxsGRMxBW5OyCk/LPv3DBqmZYNPycH6kBdOzTdhzDTnLsuTW6hh4ojvf7kVgYIJoKE3bUUpMN7ZvbAA70eLkiLYkXrjYNBHf2Va2V3tFZwoNWhdVPmz8vWODdqbAw8/SN8c2rXdJHQSvhpO6torkx4+evsWnwpeNyoCb5+SZXho3Nsy/u7LEO/tr/gDVMrb458pKPhrZuXJegrZsH9iSv6pjRloZPe27xbzI5OUcAS396HfovBs+MXp5V/XndH2HKSKsRRdVeICqQf5/L+g7jlUQpkII6PXEMu7uvJjm0x95ELGY8xBIJxr7vVoDQVXMfyiD6qyB4RhOPz0cuSDGNfUamms+y73DXX+0Y03bEYwRyQv4DfawRrutqVIidt2n1hgXqLjozFc3pWeJ5ZKN3u+vwMBhH98StD8Ma4K0hjOI8UfBPI/tnPdpG8QQwKPf0/2SN4WlgntbITz4MS3ZjWF8x/az9TbL19/byoFQb5/L94gqWnqL/YRlk2fPgqdy+ZJkDXvI3gVFRM+HLypYtwYG4HXED0yTJHApt8VzAmdRLq6lQvSBMQ+uUcOFJFtBz7SJc1AqSzEB1vachZce+1faWAdXUGzQmnYq+u09b3A6uecvv80nPQ86VRQB21G0AGaVT09STpgaF8p5R0Razn46QOfCtM9WegCn3rt3MLGlygIuj2SS2LQ/WZwughkQjxW7V09xCejNNKrOPfcNwjrK8XRLu2whDlvu+frV4dX1oSasXSyxJLB+LXKu1B+rZNH31DEf3sM4AhXH7kaiqvUW05f1U84fc0au17BDRmbK8+MFZWSzJYwd4+ltup3lDMEnh2+GlaUbk0E2XVSx1CSumC5ZsbHBB6XU4wJEIeG+0rdKUHqNOClxOYYnCzLOWXUs34R1IhkNW1VSkPB7rG/CdYySBr0aA8pjlgMjHBvpzjEqTPkHCmu87EypRmnxSU1+i5avjd8KGe4il/CjJLCh3JyLy/VrSLiEob4M/f3SxcUzHFKUqSx5lJ26PdjUz7rdOh867HeIVd8ZmnkJO40x0XWypl61WjCE2aGtEijduJCn1RemPAhn/3QkKzeIu/963xEa/O1AAIs/dMSXCLCxkdZJhx4RSBszE+hGNTqroDlk1CYcltHBzwv1F3frL1eXpgS+SCyQdzy6CjOTbICAOvQIG70nfRwQcjL7li7sFjsZdw1zP0cAcYezHDN6Zf9NJMBQ4wKzvZLjKVJk6fpyI4wBSbqx/6IeDZIdiudmeEj6lCcu5rM/vz5fQ7YsRhFI3WXhPIRGugxmF8RBpj0e4aYqD/Sfssx+AVgpv0e9U773afDkrJEdJZoQnCU6BL7jNgpMRMhDGO8dIodibT+s8ZPdXuRLrnWI7tHsDfU7P4knNnlzMxT4X0B+rKK3MWLi+AXqfq0OfK37RRdeOTwLiOxee7YIqV+DPJDFvG58YhcIn4hpG458JvB4ZLH6/ssLd8Ey9nxe2Z0IdnXbJIlF26oWm4p2YgdZAzYseXbn+hOicFpPD4jNwNhsSzuokMw2eZmxLc2Q4gWYkgXDKl1C4tu84HrntY0wPclXzwGhdRmbwktq/Ir7CvEexl931NmBmYmSuPop80vqHYpelbYDUZHubMvAxqZECXTaSlXyQPS+QV34oxDox0M1mhrOVQ7tCbS++9PzIdsGzg2Sc3uS5lK9/L6mDoRbZhtjrZlItGzsc51yh8jBTbuCQDCHo5Oewc0MN55y1PnA/hfYAe4CqlhK/DysRMAetg69wE0HH3E1R7dFN1hMfmU3tmOdOwkjWSLCEcJTn10Wk01/NoM1jf2QT0iPVJdrF6584xpOuoiaoHiDpEZTI2wWeQPyK3yhYf4XH+tnW17Q5Hpoxg6AkW0BDk7DBg7NoW67RuuOlcfho3SxcLO8g8E91Ar15jHc2M/0+7YPm7Xj+Qt0APeq89Dw1iHOcr44J2TCexMVTKZftyI/cLN7SpdoEMAu0ZQshYJS01Ory+WKsxtJpOSUZ/3z3BKFhlHEZb1RzVraQIZO+8bmkx6S9uxj5HKfkrHNv3KK5HgXbMwHIlynuPvHUvnfI8ivmUpVyZFLKVnxWS/EfJeJ00JbDXt2m7zdQWv7SMh40vTT41xdPnHqG8gc1Nf5MYW4ODaoAKllJPS656qeb9+Oyn3TEQ5NJ6T91JOExd84Ieihhr9XBlxerKISmMYsh7CuPXTy47PmymEWxY41BkUcOT+VQzam8UlEkWBh9hY8XAnnqeCaJr5ExgjfkFeBhwvGIRoQhy2cUAVomNgotPugB0WnFP6tS8nzotdQQLH6w2Sd700L1N+tn5+GxsKNZb0w1zh7LQa2BWhgxRlhkyXx1iB+EGwGjZmLtJXBn9JuP0jCn3NGInLrGYJc9nd6B8ARmq9y1mmNJxd6OtW5eYDQ/Q5HX1EcSQAyUSR5Q5yOw0FvYJEEQkl3HYaFfFYfPin6yIbOHPpxIU1eoXLGHbHSQjR626iGrTKoLu8siNA+N3Ii0EuOAgSKHuMZCnY20stqLPiH389ayhOvuNh3WC+7xSK51dUq6JmpNWfGHBaZ9QbP6GsTeGCzBtq1S/0TXKfMCcOOzEcXWMXOe1LKDpHqpsIhjSqbzvkr+N+WDNaNKDdaWuNHdSoVmVqeX2BQTnX3xDgvvcIxzRyJde1LHz6S1kePMQN5JIYgcVirIdPdYhZDBE+MblIJMX2YDxO6ARuImBjZAbSmJSHKtK0H4lNZN3JUU3n2Oovt+swCY+XVzTB1YshAAAean3QBr2vLG6NdP/QA4DXPXeWtlg2Y/QB4E2Bhdexq6xWkNC6m+vSFhwgXB9wJcTz8rrmvk1ZDbxuwLP/uAB3NYM8P8wqHo62ABSLW9V5xpUPT5P8N+9XKw1VwLyHPCKw30VND3gz4ggwpdQEUlKoB/E9GlqAnjwFwG8v+2dXzd1RI2BfZkKwn/wRAMy18PqDuJX8veat8AYo/nkba2t9wNKFMA/o6dY4CNxFMAXOzbD7qAoIwAQ9zUoeApz774B5St0gPeOO9PerIbwYsKQ76CmpfHEr7tEQHfRUFDUIht172YqbageB3taftyaBX8BE0UcA4Vy3jyaFXrCngQWIB30KHMg5
*/