/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    arg.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_ARGS_H
#define BOOST_HOF_GUARD_FUNCTION_ARGS_H

#include <boost/hof/detail/seq.hpp>
#include <boost/hof/returns.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <utility>

/// arg
/// ===
/// 
/// Description
/// -----------
/// 
/// The `arg` function returns a function object that returns the Nth argument
/// passed to it. It actually starts at 1, so it is not the zero-based index
/// of the argument.
/// 
/// Synopsis
/// --------
/// 
///     template<class IntegralConstant>
///     constexpr auto arg(IntegralConstant);
/// 
///     template<std::size_t N, class... Ts>
///     constexpr auto arg_c(Ts&&...);
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
///         assert(arg(std::integral_constant<int, 3>())(1,2,3,4,5) == 3);
///     }
/// 

namespace boost { namespace hof {

namespace detail {

template<class T>
struct perfect_ref
{
    typedef T type;
    typedef typename std::remove_reference<T>::type value_type;
    T&& value;
    constexpr perfect_ref(value_type& x) noexcept
    : value(BOOST_HOF_FORWARD(T)(x))
    {}
};

template<std::size_t N>
struct ignore
{
    template<class T>
    constexpr ignore(T&&...) noexcept
    {}
};

template<std::size_t... N>
struct args_at
{
    template<class T, class... Ts>
    constexpr auto operator()(ignore<N>..., T x, Ts...) const 
    BOOST_HOF_RETURNS(BOOST_HOF_FORWARD(typename T::type)(x.value));
};

template<std::size_t... N>
constexpr args_at<N...> make_args_at(seq<N...>) noexcept
{
    return {};
}

template<std::size_t N, class... Ts>
constexpr auto get_args(Ts&&... xs) BOOST_HOF_RETURNS
(
    boost::hof::detail::make_args_at(typename gens<N>::type())(nullptr, BOOST_HOF_RETURNS_CONSTRUCT(perfect_ref<Ts>)(xs)...)
);

template<class T, T N>
struct make_args_f
{
    template<class... Ts, class=typename std::enable_if<(N <= sizeof...(Ts))>::type>
    constexpr auto operator()(Ts&&... xs) const BOOST_HOF_RETURNS
    (
        boost::hof::detail::get_args<N>(BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

struct arg_f
{
    template<class IntegralConstant>
    constexpr make_args_f<std::size_t, IntegralConstant::value> operator()(IntegralConstant) const noexcept
    {
        return make_args_f<std::size_t, IntegralConstant::value>();
    }
};

}
#if BOOST_HOF_HAS_VARIABLE_TEMPLATES
template<std::size_t N>
BOOST_HOF_STATIC_CONSTEXPR detail::make_args_f<std::size_t, N> arg_c = {};
#else
template<std::size_t N, class... Ts>
constexpr auto arg_c(Ts&&... xs) BOOST_HOF_RETURNS
(
    boost::hof::detail::get_args<N>(BOOST_HOF_FORWARD(Ts)(xs)...)
);
#endif

BOOST_HOF_DECLARE_STATIC_VAR(arg, detail::arg_f);

}} // namespace boost::hof

#endif

/* arg.hpp
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
*/