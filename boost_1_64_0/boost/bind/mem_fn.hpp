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
7sTt9f2YCKRz8+kZ7/1qembS1Re+s3hm2lQne3FOdvOc7Lk52ZFzsvPmZAfPyf6esz26L3Ufcn7yHSnaLc8z8u07lb/b8/cvbH/fy9+V/D2Mv+/z/S3zHBJhHi7W9nec7e8W+ve7uHjb3wm2vyOSfOdy2/7+1nauY7a/Gyd58tyFv5P07wa4+vr3izizX521pkGf1aID9r9rbts3LlPlUmqRK1W5aUFyUOXW4/ar3GqVi4VrvHVOh9AUlsCWcC5sDefBFHgZTIPzYVdYCnvDBXAQLIfjYAWcCC+BuXARLIWL4SJN53J4KVyhfs0faxec8/eI5u9Rzd9vNH+Paf52af4e1/w9ofn7reZvh+bvSc3f05q/nZq/ZzR/uzR/z2n+8Os+szrHH76s+bPvM3uF5mMZ7Aivht3gTXAgXAGz4Ep4AbwG5sBVcL6GXw5/rOetgtfBn8AquBaug+vgLZruA7p/7264WvOZ7dL56vBMyScOjvPuB4tcHHxR63G31uMrsB2sgZ3hSzAdvgx7SbjPBt4mTf8MTd9uA289cgnwVng63ADbwttgF/gzrZeNtvwe1PSGhMjvq5rfvZrPfZrPN2AHPd5T/X3hm3CAyh2CR1w671jaxJO+lc4BHD/ZjzURzoWpcB7sAG+CPeACOBouhNPgJfAiuAheBRfDq1V+DbxU95ddCrfBy+Fz8Ar4mu4v/Be4DLp1n+AYaMWPV38S/DHspMd7qr8vtOJlwp/AQrgWzla5Ut1/+FL1W+X/0KXzbuFkLX+yra+lrkRvB8L2cBDsDAfDIjgELoDD4M3wIrgZ5sCtcCr8JTwfPgTHw8fgBPgEvAA+A6drPYyGf4Qz4R6YD9+AxfAj9X8GC+Hf4Sx4DBbr/rojYSy0/KkwEw5VP+Xli7XOJYV7VZ/i4f1a3p+pjdCNMAPeA/vDX8BB8HE4FG6GE9Q/Gd4Bs9V/kcZfAB+Bl8Lt8Fb4KLxN5X4OH4IPqH8brIY71P+snvdl9ZN/yqNzTGGa5j8K9tX8/1ltSv5Fy/EebAnfh8nwA00nw6XzPGE9TScSptlsplpMhJEwSeNtseJqvOc0nt1W4Ttu9BTu1+v8Pe333oft4RG9Hj/Q/u5DeCH8CM6EH8PZ8BPt9w7ACvg5XA7/Dq/X+Bvgl3CLprsNHoRPw79Bk9+XnPP7jeb3qObXFeHJrxu2h81hTxgJs2A9eCGMgjNhfTgbNoDzYTSsgI3hctgUXq/xN8A4uEXT3QZj4NOwCfTsA65z0GBPza99H/CvtX2PwhbwmLbrt/B0GKH933e6vz9+s098qaabq+kaG7lqqzEBHtDr/VO93j/T/u4rvR4+t9l0zISH4Ah4GI6HX8As+CWcAr8yNiN1XpTWfXSAzcgot6c8DXRciNZyNIIdYWPYAybAs2AyHAGbwrEwFp4Hm8FsmAgXwyR4qcqvgC3gKvVrvTC/SfMVol5a6z7XKbANxMl9RCrsA9vBM9Q/QP1XwDTt/zvAa/T4Wj1+sx4/BLnIdC4ObannbwIrvP2vXj+DYAb8kZRfbazCoXq/cg4shOPhjfBcHf+H6fg/AtbAiXA/nAA/Vb/mQ+efcE8TIh9tkGsO28NOMA0Ogx3gKNgRToWdtf67wiLYDV4Ne8KVsI/mLx0+BHvBx/S43ufpPA3GhBD3eZ1V/7to/9ZV+7czYGvYXdunB+wC+8B0Dc9Qfz/YGw6E/eDZGj5C/WNUbpIen6r+Q3Lt6HwKWKT5awgna/6m6P3IVL3fzIPDYT4cCWdpu82Ak9V/AZym/R9+s2//fj3PRj2Pfd/+nVr+Z7Rcu3WcehsOhn+AI9U/Dr4EJ6v/Ao1XBN+Aq+Cb8DoNr4J74Ho=
*/