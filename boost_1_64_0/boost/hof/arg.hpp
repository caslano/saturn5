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
EruHBg3HzJBLG22jvEm2Z8x5voBdHWGPne/95gi7HL60/ZlCii+KhlJK8g4s3kapias/QO4VRZfHxM5rQua82r2miCNPNC+cbltpvvzq1bv7W5LpabWW7LEhMmTOXZjPAbvNFnPu1TLO7FH0uPQVFJVMUQhpNOcmRRy5CwcilBIkL/pVXvPtqcvyc5Oq+xXkNS89oK5GwDDRIA6NiY7p8vL5WCscuSHHYI7mtkufYJhZuzY2vQH/Tpf/p3tBXtZVFeXl5Yc6ykT9xduj2qiLY1j/3EZtuP3i1ysiZu/Fz43hnUCwjh7//f9m7lrAoyqu8G6yCQsEdoEACwSIsmgUlMCCJAQhgZBQRViMyWoRsK3idUsVZSNYw0MXWpZrKrTYaktrKbbValsfqMH6AFcJKAq+EIsPtNZOjLSLKG/Y/ufMnbt3l00IlH7t5Qt777zOmTNnzpw5c2YGlQt1wn+1HZcvsC3/nr05c/n3sBPkCJ0nlbFkSy1pJh2X/4haYJmz9DHc5P5R+B+Z+j7yNvqno+OBtEmOhf/mQgF/y8CZVB33pUkS/sdYDo0j9G4ztAQeRgu6Lc87f3nd+fbls8/PCL+Y2TQnzo45MMSRZD01fSD14fWacIltgYOaJRCcqA3+kk0tf55pGhdDlS535nrqncEpri7tyPmz0l3ckVO6pnSMTMmpd9QjFuPS53IMYvNhbffgVE4TEJdM4OCZBKOaVsxGLhwI+ntmrdDHO3THo7QG5Y+/g0PlyP7qeAzfORUlI+s+njEdOs+0KFpjfm9SE1folUb6bH/8LSRGzG3NrMMzKLLSfVAO1aWrDGFVnG2uHoz502f+Z8TCo/SpUmKspVvmF+k9Sl5ZMAyKaZWetyxQP3pZ/bh4yeaQZ9Ab9Tn30BmEU+unOKYG4t2LuPfmxDvr0ZnTZkRbMBdVEYAc35aA3mPpmwu76zMcepR6d3FRqHNZeIOj5JW6r+SKGIAPBegL9NE6QNbn6QZUB0P11493+KssUEFHcteJ028rVGD5HR4LfmABHhyi+OH+6Ql7xHCXu11whGz/LtkQzZDMemXOxt0ZfjGP0m0mHpjsgD2zc40460KWuSxt9XaUCK00VTgfZCdoCOZTEcLBDNM//A3Hiet7Vv/xx4z4tO030MIz0IwfGmflmRpx3zjmGW6idPnlHF+HMula9nu8XcwjwZLVNl4fKg2UbJ5XUj+6fcmhW867I45n7LyztLtsRvH1jue4txDgqy8zlhRqs2YSS2DMiizM0XtQm5ccXnDR0vh8Yq5B7278JOPyekeDHzzgl82qT3YYq3kRx/p4tp49k8ZOVlkRxat8EcdKijDDT89GaX1QLHVtQ3vTS1P9mrBOojjmQwvHnB+8UQa7ReN0i5ralSQYcc8maAEOxjFYa7RB97I22FUt8G5MDy+QBM/QOdLB+21pG+AZ9XfQ0KXbounGG2L7TOi1uh0K64GJ/qni4UIq2UqqVH0pNFFKxT4kj3NThRyJwuZpyVLuwNhkKfePscyx6Ewnbb94oVwg/zWjlRNNja8B5H7gcxByfo+SwgVddb+8MS7ncb2UMGuFkaj+0PWdepk7MtVd8mKoXWMZM180qf8YU7DOS7cs3K/XOOrL4gF9FKnoGEmk+Brn8F+eIr6MItL35/BCp622P1ZmUYrHH3TEL6Llru7b76EC3OgB6SdzQZspL1YOkeRI096hblLvm9+xxLmgHRNhGU1dWsanL8mGhT1J2gEEOnr/tcZpnbInnmx8GcA1qT2Lh4Ee1J+BIvTH4qGhQClO6ip5se4r8OCMKNe7xQpLt88dqB/ZuiHq3EZCv5g9TLkOPD2owrHxYEabRIPBP92/WNE=
*/