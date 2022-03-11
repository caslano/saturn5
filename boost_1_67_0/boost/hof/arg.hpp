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