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