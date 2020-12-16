/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    unpack.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_UNPACK_H
#define BOOST_HOF_GUARD_UNPACK_H

/// unpack
/// ======
/// 
/// Description
/// -----------
/// 
/// The `unpack` function adaptor takes a sequence and uses the elements of
/// the sequence for the arguments to the function. Multiple sequences can be
/// passed to the function. All elements from each sequence will be passed
/// into the function. 
/// 
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     unpack_adaptor<F> unpack(F f);
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
///         int r = unpack(sum())(std::make_tuple(3,2));
///         assert(r == 5);
///     }
/// 
/// References
/// ----------
/// 
/// * [std::apply](http://en.cppreference.com/w/cpp/utility/apply) - C++17 function to unpack a tuple
/// * [`unpack_sequence`](unpack_sequence)
/// 

#include <boost/hof/unpack_sequence.hpp>
#include <boost/hof/is_unpackable.hpp>
#include <boost/hof/detail/seq.hpp>
#include <boost/hof/capture.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/and.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/holder.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

namespace detail {

template<class F, class Sequence>
constexpr auto unpack_simple(F&& f, Sequence&& s) BOOST_HOF_RETURNS
(
    detail::unpack_impl(BOOST_HOF_FORWARD(F)(f), BOOST_HOF_FORWARD(Sequence)(s))
)

template<class F, class... Sequences>
constexpr auto unpack_join(F&& f, Sequences&&... s) BOOST_HOF_RETURNS
(
    boost::hof::pack_join(unpack_simple(boost::hof::pack_forward, BOOST_HOF_FORWARD(Sequences)(s))...)(BOOST_HOF_FORWARD(F)(f))
);

}

template<class F>
struct unpack_adaptor : detail::callable_base<F>
{
    typedef unpack_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(unpack_adaptor, detail::callable_base<F>);

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    struct unpack_failure
    {
        template<class Failure>
        struct apply
        {
            struct deducer
            {
                template<class... Ts>
                typename Failure::template of<Ts...> operator()(Ts&&...) const;
            };

            template<class T, class=typename std::enable_if<(
                is_unpackable<T>::value
            )>::type>
            static auto deduce(T&& x)
            BOOST_HOF_RETURNS
            (
                boost::hof::detail::unpack_simple(deducer(), BOOST_HOF_FORWARD(T)(x))
            );

            template<class T, class... Ts, class=typename std::enable_if<(
                is_unpackable<T>::value && BOOST_HOF_AND_UNPACK(is_unpackable<Ts>::value)
            )>::type>
            static auto deduce(T&& x, Ts&&... xs) BOOST_HOF_RETURNS
            (
                boost::hof::detail::unpack_join(deducer(), BOOST_HOF_FORWARD(T)(x), BOOST_HOF_FORWARD(Ts)(xs)...)
            );
#ifdef _MSC_VER
            template<class... Ts>
            struct nop_failure;
            template<class... Ts, class=typename std::enable_if<(
                !BOOST_HOF_AND_UNPACK(is_unpackable<Ts>::value)
            )>::type>
            static as_failure<nop_failure> deduce(Ts&&... xs);
#endif
            template<class... Ts>
            struct of
#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7) || defined (_MSC_VER)
            : std::enable_if<true, decltype(apply::deduce(std::declval<Ts>()...))>::type
#else
            : decltype(apply::deduce(std::declval<Ts>()...))
#endif
            {};
        };
    };

    struct failure
    : failure_map<unpack_failure, detail::callable_base<F>>
    {};

    BOOST_HOF_RETURNS_CLASS(unpack_adaptor);
    template<class T, class=typename std::enable_if<(
        is_unpackable<T>::value
    )>::type>
    constexpr auto operator()(T&& x) const
    BOOST_HOF_RETURNS
    (
        boost::hof::detail::unpack_simple(BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(x)), BOOST_HOF_FORWARD(T)(x))
    );

    template<class T, class... Ts, class=typename std::enable_if<(
        is_unpackable<T>::value && BOOST_HOF_AND_UNPACK(is_unpackable<Ts>::value)
    )>::type>
    constexpr auto operator()(T&& x, Ts&&... xs) const BOOST_HOF_RETURNS
    (
        boost::hof::detail::unpack_join(BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(x)), BOOST_HOF_FORWARD(T)(x), BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

BOOST_HOF_DECLARE_STATIC_VAR(unpack, detail::make<unpack_adaptor>);

}} // namespace boost::hof

#endif

/* unpack.hpp
hntyOyPtbiUWrpWmuR/HdzO+N+LrHpbm/iX+v8S3GM/vD/vPrUmmZjNyc4uJ3MzT7peH42kWE7mRfmWBdvfQd3nZGtY3WIG1DMP/FChPc4svX22VxLnt2q+ieJIq6i1Q9bmoqYw2wFnqRh5eNjDzBzP9tSr9w0jv1womIswmAp/zbaa5C9KFB0wJV4CaR+WEYODD4g+kit9AEKQlWYzh89GOeDo6/kCn/Uqz6Dmq6LGxRfc0iia1dLYFC3uRdoX0XKGtUdm125GgeX401eNmqgptvZnqViKDTRK3ZJJIfdhnh0h9nr6xcZiVbs2Mf1mHEXzOJbk+/8Vi+YeK2dEhPEBfO4V6pb0WHb4Wl/aSWfjvUbjqxJJDPJ5Aazr4RNs73G/kpqlatrkszf218R2Gqfkj/8v3Kfh2L/vPrbfED+tXe30wGpQfoUP2fSl5HYw1Y1VFHiQ6F4134uIsvaU7qsUo0L1aHJFZTrHNJWVsBO7PsDL3RjfTzFX9k8uAun30dStZ1xPBXXSFHf8B703QnElOLpCGBGuA4fvFdZL5MAbt2BYYK/ptplwQPCj3sxflWig4rEulFom79qg7eS8f1fjDaI1zl6LdpNHRpE2OmcVemjfmzamVmm831F2H2XzqIM+mXwzALRlWKl9qPVFMrRqpEEWUh2fZ46I1cJ3O+6XhCbxjCGHqv9KlSBBT2dnR6++qDgc94svnW5WvvcAMklY+16XEvc6QZnDF651ZTDmAgZfs/SwIGXdyKSHjd/zibEnJqJUgEqNli45P3fW0/w/wiEgGmHbAomLnc+zNcbG7zNgFHDtTxh6XH+qjjxcvTSH6GKSJcjrVGHf/1Xs8EMwOH6mdY1Pb9OfUnGVym364XxJBtGkfdSdw8/CnDG584v4XeAD8XNJkPvkc5FwR3bGCwwwAc1UvU9YwsJH45+HZRvKzVfLjMQzAH0WvrCuB+aPSW3q7lSuPJBAOa8TGl9EjnJvMcgsMIfy3CXCGubM4dcUbycxeQ5ukpmCm1kf1Oncv5n10K/KjRDdKTGExGrohipUbWimbdopK7Atbhb+VA/lMKLJOqnXd/p3kbVa46X7ynj32fuJEkN6QTSghcMVM/JHvK7vuDu3HmeW20Zl1++pRfO+wx947LvjcvHd8glyQKUZ+p0RAn0wlNJNqa1LZ1EVknQpQF5Hl8mphj15E0j4BtLpfBZsXkf0fI7hRBZsXkQ8R3HwNcGp1F0nnu8hFX5p3kUsQybWSyIVxF7ngeO4i2Qai/igfmZlmWQaW/+Uh4y5yF9Ms/GuBy+M6MuOw+0h69D4yHUWRkvVR7iOZ7biPZB79PoK1ntjI0WgkhcVeRQrNq0i60cP7eu4wr21ZxlVk3GfyKtIVqdnD8BpMtNsqpcI3JZszPWPZ3Remuffg23lkmvtV/A/B/8f4z8b/VfgGRv33nKXt+TSTTZ3Y90AC/6SXI/499Fo8/a42IX9BQv6cBH7QVQn8KOyj2Pc6SyxxDjQO73OtsUI+ftHayaC/ZWqBmENiDqDrIj5gTPw03cuKk/c51Hl0HhHeoC9ZgTrJiChBYlTx1bO85gmAgVT1MgARLGpewbmcOJ5eNuhTBsXL38GkeLXPBUTch+QwAHPrHSD3ow99tJ1RNLsuiD6sAX9M+dhnWAFb3QcUaixNzDcvZY+OHHePGZcq+bFzAEko4icxETaKmKINnkgRV8ZEOCiiXCvliHHRCMnhzdXKOaIkJsJOEV01D0f0MyP6MBbsoeuX+orFDEoyqB9JNtXJIHfybaBePsWbeGA7n4HH5Za23R/pf2HjIULxF0/KcCtX22JIN8NFMKhUNBP9tH00E/WT+ZbyW3lcF+w=
*/