#ifndef BOOST_BIND_MEM_FN_HPP_INCLUDED
#define BOOST_BIND_MEM_FN_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  mem_fn.hpp - a generalization of std::mem_fun[_ref]
//
//  Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2001 David Abrahams
//  Copyright (c) 2003-2005 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/bind/mem_fn.html for documentation.
//

#include <boost/config.hpp>
#include <boost/get_pointer.hpp>
#include <boost/detail/workaround.hpp>

namespace boost
{

#if defined(BOOST_NO_VOID_RETURNS)

#define BOOST_MEM_FN_CLASS_F , class F
#define BOOST_MEM_FN_TYPEDEF(X)

namespace _mfi // mem_fun_impl
{

template<class V> struct mf
{

#define BOOST_MEM_FN_RETURN return

#define BOOST_MEM_FN_NAME(X) inner_##X
#define BOOST_MEM_FN_CC

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#if defined(BOOST_MEM_FN_ENABLE_CDECL) && !defined(_M_X64)

#define BOOST_MEM_FN_NAME(X) inner_##X##_cdecl
#define BOOST_MEM_FN_CC __cdecl

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#if defined(BOOST_MEM_FN_ENABLE_STDCALL) && !defined(_M_X64)

#define BOOST_MEM_FN_NAME(X) inner_##X##_stdcall
#define BOOST_MEM_FN_CC __stdcall

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#if defined(BOOST_MEM_FN_ENABLE_FASTCALL) && !defined(_M_X64)

#define BOOST_MEM_FN_NAME(X) inner_##X##_fastcall
#define BOOST_MEM_FN_CC __fastcall

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#undef BOOST_MEM_FN_RETURN

}; // struct mf<V>

template<> struct mf<void>
{

#define BOOST_MEM_FN_RETURN

#define BOOST_MEM_FN_NAME(X) inner_##X
#define BOOST_MEM_FN_CC

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#if defined(BOOST_MEM_FN_ENABLE_CDECL) && !defined(_M_X64)

#define BOOST_MEM_FN_NAME(X) inner_##X##_cdecl
#define BOOST_MEM_FN_CC __cdecl

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#ifdef BOOST_MEM_FN_ENABLE_STDCALL

#define BOOST_MEM_FN_NAME(X) inner_##X##_stdcall
#define BOOST_MEM_FN_CC __stdcall

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#ifdef BOOST_MEM_FN_ENABLE_FASTCALL

#define BOOST_MEM_FN_NAME(X) inner_##X##_fastcall
#define BOOST_MEM_FN_CC __fastcall

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#undef BOOST_MEM_FN_RETURN

}; // struct mf<void>

#undef BOOST_MEM_FN_CLASS_F
#undef BOOST_MEM_FN_TYPEDEF_F

#define BOOST_MEM_FN_NAME(X) X
#define BOOST_MEM_FN_NAME2(X) inner_##X
#define BOOST_MEM_FN_CC

#include <boost/bind/mem_fn_vw.hpp>

#undef BOOST_MEM_FN_NAME
#undef BOOST_MEM_FN_NAME2
#undef BOOST_MEM_FN_CC

#if defined(BOOST_MEM_FN_ENABLE_CDECL) && !defined(_M_X64)

#define BOOST_MEM_FN_NAME(X) X##_cdecl
#define BOOST_MEM_FN_NAME2(X) inner_##X##_cdecl
#define BOOST_MEM_FN_CC __cdecl

#include <boost/bind/mem_fn_vw.hpp>

#undef BOOST_MEM_FN_NAME
#undef BOOST_MEM_FN_NAME2
#undef BOOST_MEM_FN_CC

#endif

#ifdef BOOST_MEM_FN_ENABLE_STDCALL

#define BOOST_MEM_FN_NAME(X) X##_stdcall
#define BOOST_MEM_FN_NAME2(X) inner_##X##_stdcall
#define BOOST_MEM_FN_CC __stdcall

#include <boost/bind/mem_fn_vw.hpp>

#undef BOOST_MEM_FN_NAME
#undef BOOST_MEM_FN_NAME2
#undef BOOST_MEM_FN_CC

#endif

#ifdef BOOST_MEM_FN_ENABLE_FASTCALL

#define BOOST_MEM_FN_NAME(X) X##_fastcall
#define BOOST_MEM_FN_NAME2(X) inner_##X##_fastcall
#define BOOST_MEM_FN_CC __fastcall

#include <boost/bind/mem_fn_vw.hpp>

#undef BOOST_MEM_FN_NAME
#undef BOOST_MEM_FN_NAME2
#undef BOOST_MEM_FN_CC

#endif

} // namespace _mfi

#else // #ifdef BOOST_NO_VOID_RETURNS

#define BOOST_MEM_FN_CLASS_F
#define BOOST_MEM_FN_TYPEDEF(X) typedef X;

namespace _mfi
{

#define BOOST_MEM_FN_RETURN return

#define BOOST_MEM_FN_NAME(X) X
#define BOOST_MEM_FN_CC

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#if defined(BOOST_MEM_FN_ENABLE_CDECL) && !defined(_M_X64)

#define BOOST_MEM_FN_NAME(X) X##_cdecl
#define BOOST_MEM_FN_CC __cdecl

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#if defined(BOOST_MEM_FN_ENABLE_STDCALL) && !defined(_M_X64)

#define BOOST_MEM_FN_NAME(X) X##_stdcall
#define BOOST_MEM_FN_CC __stdcall

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#if defined(BOOST_MEM_FN_ENABLE_FASTCALL) && !defined(_M_X64)

#define BOOST_MEM_FN_NAME(X) X##_fastcall
#define BOOST_MEM_FN_CC __fastcall

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#undef BOOST_MEM_FN_RETURN

} // namespace _mfi

#undef BOOST_MEM_FN_CLASS_F
#undef BOOST_MEM_FN_TYPEDEF

#endif // #ifdef BOOST_NO_VOID_RETURNS

#define BOOST_MEM_FN_NAME(X) X
#define BOOST_MEM_FN_CC
#define BOOST_MEM_FN_NOEXCEPT

#include <boost/bind/mem_fn_cc.hpp>

#if defined( __cpp_noexcept_function_type ) || defined( _NOEXCEPT_TYPES_SUPPORTED )
#  undef BOOST_MEM_FN_NOEXCEPT
#  define BOOST_MEM_FN_NOEXCEPT noexcept
#  include <boost/bind/mem_fn_cc.hpp>
#endif

#undef BOOST_MEM_FN_NAME
#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NOEXCEPT

#if defined(BOOST_MEM_FN_ENABLE_CDECL) && !defined(_M_X64)

#define BOOST_MEM_FN_NAME(X) X##_cdecl
#define BOOST_MEM_FN_CC __cdecl
#define BOOST_MEM_FN_NOEXCEPT

#include <boost/bind/mem_fn_cc.hpp>

#undef BOOST_MEM_FN_NAME
#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NOEXCEPT

#endif

#if defined(BOOST_MEM_FN_ENABLE_STDCALL) && !defined(_M_X64)

#define BOOST_MEM_FN_NAME(X) X##_stdcall
#define BOOST_MEM_FN_CC __stdcall
#define BOOST_MEM_FN_NOEXCEPT

#include <boost/bind/mem_fn_cc.hpp>

#undef BOOST_MEM_FN_NAME
#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NOEXCEPT

#endif

#if defined(BOOST_MEM_FN_ENABLE_FASTCALL) && !defined(_M_X64)

#define BOOST_MEM_FN_NAME(X) X##_fastcall
#define BOOST_MEM_FN_CC __fastcall
#define BOOST_MEM_FN_NOEXCEPT

#include <boost/bind/mem_fn_cc.hpp>

#undef BOOST_MEM_FN_NAME
#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NOEXCEPT

#endif

// data member support

namespace _mfi
{

template<class R, class T> class dm
{
public:

    typedef R const & result_type;
    typedef T const * argument_type;

private:
    
    typedef R (T::*F);
    F f_;

    template<class U> R const & call(U & u, T const *) const
    {
        return (u.*f_);
    }

    template<class U> R const & call(U & u, void const *) const
    {
        return (get_pointer(u)->*f_);
    }

public:
    
    explicit dm(F f): f_(f) {}

    R & operator()(T * p) const
    {
        return (p->*f_);
    }

    R const & operator()(T const * p) const
    {
        return (p->*f_);
    }

    template<class U> R const & operator()(U const & u) const
    {
        return call(u, &u);
    }

#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) && !BOOST_WORKAROUND(__MWERKS__, < 0x3200)

    R & operator()(T & t) const
    {
        return (t.*f_);
    }

    R const & operator()(T const & t) const
    {
        return (t.*f_);
    }

#endif

    bool operator==(dm const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(dm const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

} // namespace _mfi

template<class R, class T> _mfi::dm<R, T> mem_fn(R T::*f)
{
    return _mfi::dm<R, T>(f);
}

} // namespace boost

#endif // #ifndef BOOST_BIND_MEM_FN_HPP_INCLUDED

/* mem_fn.hpp
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
*/