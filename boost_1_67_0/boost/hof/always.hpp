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