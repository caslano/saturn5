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
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
*/