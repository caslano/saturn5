/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    always.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_ALWAYS_H
#define BOOST_HOF_GUARD_FUNCTION_ALWAYS_H

#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/unwrap.hpp>
#include <boost/hof/detail/static_const_var.hpp>

/// always
/// ======
/// 
/// Description
/// -----------
/// 
/// The `always` function returns a function object that will always return
/// the value given to it, no matter what parameters are passed to the
/// function object. The nullary version(i.e. `always(void)`) will return
/// `void`. On compilers, that don't support constexpr functions returning
/// `void`, a private empty type is returned instead. This return type is
/// specified as `BOOST_HOF_ALWAYS_VOID_RETURN`.
/// 
/// Synopsis
/// --------
/// 
///     template<class T>
///     constexpr auto always(T value);
/// 
///     template<class T>
///     constexpr auto always(void);
/// 
/// 
/// Semantics
/// ---------
/// 
///     assert(always(x)(xs...) == x);
/// 
/// Requirements
/// ------------
/// 
/// T must be:
/// 
/// * CopyConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <algorithm>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     int main() {
///         int ten = 10;
///         assert( always(ten)(1,2,3,4,5) == 10 );
///     }
/// 
///     // Count all
///     template<class Iterator, class T>
///     auto count(Iterator first, Iterator last)
///     {
///         return std::count_if(first, last, always(true));
///     }
/// 


#ifndef BOOST_HOF_NO_CONSTEXPR_VOID
#if defined(__clang__) && BOOST_HOF_HAS_RELAXED_CONSTEXPR
#define BOOST_HOF_NO_CONSTEXPR_VOID 0
#else
#define BOOST_HOF_NO_CONSTEXPR_VOID 1
#endif
#endif

namespace boost { namespace hof { namespace always_detail {

template<class T, class=void>
struct always_base
{
    T x;

    BOOST_HOF_DELEGATE_CONSTRUCTOR(always_base, T, x)

    typedef typename detail::unwrap_reference<T>::type result_type;

    template<class... As>
    constexpr result_type
    operator()(As&&...) const
    noexcept(std::is_reference<result_type>::value || BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(result_type))
    {
        return this->x;
    }
};

template<class T>
struct always_base<T, typename std::enable_if<!BOOST_HOF_IS_EMPTY(T)>::type>
{
    T x;

    constexpr always_base(T xp) noexcept(BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(T))
    : x(xp)
    {}

    typedef typename detail::unwrap_reference<T>::type result_type;

    template<class... As>
    constexpr result_type 
    operator()(As&&...) const 
    noexcept(std::is_reference<result_type>::value || BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(result_type))
    {
        return this->x;
    }
};

#if BOOST_HOF_NO_CONSTEXPR_VOID
#define BOOST_HOF_ALWAYS_VOID_RETURN boost::hof::always_detail::always_base<void>::void_
#else
#define BOOST_HOF_ALWAYS_VOID_RETURN void
#endif

template<>
struct always_base<void>
{
    
    constexpr always_base() noexcept
    {}

    struct void_ {};

    template<class... As>
    constexpr BOOST_HOF_ALWAYS_VOID_RETURN 
    operator()(As&&...) const noexcept
    {
#if BOOST_HOF_NO_CONSTEXPR_VOID
        return void_();
#endif
    }
};

struct always_f
{
    template<class T>
    constexpr always_detail::always_base<T> operator()(T x) const noexcept(BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(T))
    {
        return always_detail::always_base<T>(x);
    }

    constexpr always_detail::always_base<void> operator()() const noexcept
    {
        return always_detail::always_base<void>();
    }
};

struct always_ref_f
{
    template<class T>
    constexpr always_detail::always_base<T&> operator()(T& x) const noexcept
    {
        return always_detail::always_base<T&>(x);
    }
};

}
BOOST_HOF_DECLARE_STATIC_VAR(always, always_detail::always_f);
BOOST_HOF_DECLARE_STATIC_VAR(always_ref, always_detail::always_ref_f);

}} // namespace boost::hof

#endif

/* always.hpp
DyLFsOi+lOjuYalvUIieol2dbKeJCtGgFjjc5ERwo909zaG285E2vDU3jxlnp9HEODhJA/Z4zryydo0ljPS1HRZeQofktUfttrufezcWqz3qs0UWJZOrUTsxAOmyyb/mRp96UEybAneAjeJd0JUWfW0QsTeNCXLAYwUoIe5tIKvYHtvRP7pbUQ+mvhHddwHNc6QeFkACI+ePr6JRtCZ1TbSzPx8A4QgjWt0u7nuabRe1p2KvOIbWNHWLqOHUB2krlj3R10bJREhiatsDP4EaeoN47+NUO0nj1X2s84/Vp0DH1W0wP4LAa1S60kCVgHjQHh6m1PDk2z68p6fdRyOCSsFCQidt8mLCKDzNHC7AgGIR9E5slroJLI+lboNidqshhCMVkXhxHoUAnymka1DDvboagg+kiFDD1KOno4hOUkSoHqldRtpUMxOxBprHeG409M/ZS/+gcT1VENpHmrefQhi9dJrVlZpHPgRgMOsf61Wm1MK4/mXF9S/1DWgghch0rHZxJST9g/JBBUnzALOddA81ZQM0z8GaB0yhcaKebSj0rrae1a/mqKVrKLTvIWgfaS6icsCZfB7F9abtFwXWcJqYbDGVWcRke1qh1VRmF5Od4UKrKHCkFTpMZVSdSsOFDuIDNj8qdAH1Ih7VLUxHqXYwPlzmAX9NZRliclZaYaapLEtMzgkXoupmpxVmm8rwnC0K8tMK84W0tuH55nBhPtqG5V1HeAQY4WRkp+Ob/Du19E1uUd5/837u+oAv7G9nTioLTsXdmhSczNvdBcdrb06gA/CXbw9eUaE9NU2ekR/8eFkMFk3/pVdoi5Co9lkHNqNLrdCql8oD6A+WaZll/CgaZ8HRevVJ+y3G/udLef9z9aD6up+sZm7QA6/t3YgiRxXyHKXOI0I9trp18inDVreasl6tY2qre5xeBwNZquTovS3STIS5tvz14C3awak6EV8u88cAB7+scu1P43UKggUUmuHX3knhTiVAUOiYMr8P4dlEr3ZJPLGDYTjLK7SG0gQW3LokzoJPXdsVI0ZpC9HTKtduxX+GMYmTwNdKLoyzNOAOFp29PTj18+8Wy/3k1ZhsTKkNygUdtrovmww+TsMTeaAsf91W93mTwdNC+ZRpq8uVTxjz+SyetJeuNvicTq8/9xt8ttVtpyLv9yP+MInqeXq9k+KZibrXbznz0eDl5VcTHzj2+4ilyMxy7fb+BvOdFFPL+UgALr/2J4PTwa+WlftJfAzo6rhQppbpgfkcsaWCOY2IK3SNzfZrbg60IvAi7ZUKXSNGSXiuCu2XidJ85OtxaU736dL8dV1XzK89gv9cxsPyIUNbyGkdhlitUqwfxukZEDpqUSyX3PPqHpNVxW6r+4l8ctjqyLVMVq97kroV4A5itfZuiV7r52iN5VKcwXKWnId+fu2uEoPbl0umpfu1kUYYeHpveTdPuT5VaFNKEnjq+1qcpymTiJXTainAIhqng2MNNNp4Rt7VGJ/Ow0KQhPdV6bw95KLE9TmuMvKtYt8vfBpQhUny01QuMeKnUG5S4odxJ2X/Fu4V2jKdruq0WbNnTqe5XrR2v1wsNw4N0DddYDXa6nJt/00IW50CGh+qfTlFqY8eVnxaHSe0GtVlkIlc0TUTxrt9FdqfwxxJEW8BDjyDJptWmArqVlcfGbNuMhg4Z0U8wUYkqDQF9n8lzV6hlcpwo4KJZmS8/t7urGUV2seNJCx2FEobgaLM1+6Khy/jcC04l5HJNJAJ3gTxgR7HAjJfwyVV3SRJ+9/IqZ1IfVmlQwf9hziET8WLW2gUFzxfhlU6fFoGIOuGNnC/wUCyqtplX+yKVWjbEE/dRtThBJ5nf13yHK8=
*/