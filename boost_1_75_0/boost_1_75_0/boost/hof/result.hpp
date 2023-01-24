/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    result.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_RESULT_H
#define BOOST_HOF_GUARD_RESULT_H

/// result
/// ======
/// 
/// Description
/// -----------
/// 
/// The `result` function adaptor sets the return type for the function, which
/// can be useful when dealing with multiple overloads. Since the return type
/// is no longer dependent on the parameters passed to the function, the
/// `result_adaptor` provides a nested `result_type` that is the return type
/// of the function.
/// 
/// Synopsis
/// --------
/// 
///     template<class Result, class F>
///     constexpr result_adaptor<Result, F> result(F f);
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct id
///     {
///         template<class T>
///         T operator()(T x) const
///         {
///             return x;
///         }
///     };
/// 
///     int main() {
///         auto int_result = boost::hof::result<int>(id());
///         static_assert(std::is_same<decltype(int_result(true)), int>::value, "Not the same type");
///     }
/// 

#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/is_invocable.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/reveal.hpp>

namespace boost { namespace hof {

template<class Result, class F>
struct result_adaptor : detail::callable_base<F>
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(result_adaptor, detail::callable_base<F>)

    typedef Result result_type;

    struct failure
    : failure_for<detail::callable_base<F>>
    {};

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    template<class... Ts, class=typename std::enable_if<(boost::hof::is_invocable<F, Ts...>::value)>::type>
    constexpr result_type operator()(Ts&&... xs) const
    {
        return this->base_function(xs...)(BOOST_HOF_FORWARD(Ts)(xs)...);
    };
};

template<class F>
struct result_adaptor<void, F> : detail::callable_base<F>
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(result_adaptor, detail::callable_base<F>)

    typedef void result_type;

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    template<class... Ts, class=typename std::enable_if<(boost::hof::is_invocable<F, Ts...>::value)>::type>
    constexpr typename detail::holder<Ts...>::type operator()(Ts&&... xs) const
    {
        return (typename detail::holder<Ts...>::type)this->base_function(xs...)(BOOST_HOF_FORWARD(Ts)(xs)...);
    };
};

#if BOOST_HOF_HAS_VARIABLE_TEMPLATES
namespace result_detail {
template<class Result>
struct result_f
{
    template<class F>
    constexpr result_adaptor<Result, F> operator()(F f) const
    {
        return result_adaptor<Result, F>(boost::hof::move(f));
    }
};

}

template<class Result>
static constexpr auto result = result_detail::result_f<Result>{};
#else
template<class Result, class F>
constexpr result_adaptor<Result, F> result(F f)
{
    return result_adaptor<Result, F>(boost::hof::move(f));
}
#endif

}} // namespace boost::hof

#endif

/* result.hpp
asgf3MAqJWixll7n+dHbdoHWPb9OrDEVrdk1s5/shRLgdRSU8hn6XTGZPN4qZYNGD+5rPbDdulH1h8ioa6QlNs2Y/T4/nRkRtaLjb6qTiqcQA5wsRsDvVV7TKpUUgc2pLESBWVMci64M0T2D2tw3EDpx+lGvic8U/kDquFt6hizDtnT1psnONfWPlf9Rvc88SB009cG0MWE65FcZ0wvjgg8/RQ6DkV2vrt/59r27njq6GNOleqkZqLynFp7psgLkoNN3SDDK37mCsKzNJOg98yr5ujl1eRK/Ybxwb33CcMpG9FlwLu+ed5Xg9aPMFYZO0+G3ZD6uRJbetqyqquk7ugXp2NbGG0eGQxRvmccoe81eWJBUJhwRxxSouukfR6uf3Fs7qrwugTlibU3jL/kKZqFada3OT00CXy/7TF1ixYOUcCX5cRU4+2DOdJz5D7dyYtljaN7QKWeraTlH/N6rJIwOYpuitd54UHyjHGJx32E/dK3iBLkdfeEEjp/Gv11cHtAr8Ijulmq89Jsaatr10tknelpEWkn8g7FQpirjjsjh1XIX/Nhh3+iEv0Ozergc/WHgCQgSoynAZ6o8Bnr/NljWVplELIGkbX1yTOvS8ZJBAzRMj7ypX5a67NZhWT1qtTQdSI3BDkwL7YvU1DwvLauc9AvIpzYN23rk0YuNnjSYNY00sIzPmHj/hFVs5e4ZRzeNQ4dxP+8mbYtQ
*/