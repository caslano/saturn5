/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_PARENT_FROM_MEMBER_HPP
#define BOOST_INTRUSIVE_DETAIL_PARENT_FROM_MEMBER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <cstddef>

#if defined(_MSC_VER)
   #define BOOST_INTRUSIVE_MSVC_ABI_PTR_TO_MEMBER
   #include <boost/static_assert.hpp>
#endif

namespace boost {
namespace intrusive {
namespace detail {

template<class Parent, class Member>
BOOST_INTRUSIVE_FORCEINLINE std::ptrdiff_t offset_from_pointer_to_member(const Member Parent::* ptr_to_member)
{
   //The implementation of a pointer to member is compiler dependent.
   #if defined(BOOST_INTRUSIVE_MSVC_ABI_PTR_TO_MEMBER)

   //MSVC compliant compilers use their the first 32 bits as offset (even in 64 bit mode)
   union caster_union
   {
      const Member Parent::* ptr_to_member;
      int offset;
   } caster;

   //MSVC ABI can use up to 3 int32 to represent pointer to member data
   //with virtual base classes, in those cases there is no simple to
   //obtain the address of the parent. So static assert to avoid runtime errors
   BOOST_STATIC_ASSERT( sizeof(caster) == sizeof(int) );

   caster.ptr_to_member = ptr_to_member;
   return std::ptrdiff_t(caster.offset);
   //Additional info on MSVC behaviour for the future. For 2/3 int ptr-to-member
   //types dereference seems to be:
   //
   // vboffset = [compile_time_offset if 2-int ptr2memb] /
   //            [ptr2memb.i32[2] if 3-int ptr2memb].
   // vbtable = *(this + vboffset);
   // adj = vbtable[ptr2memb.i32[1]];
   // var = adj + (this + vboffset) + ptr2memb.i32[0];
   //
   //To reverse the operation we need to
   // - obtain vboffset (in 2-int ptr2memb implementation only)
   // - Go to Parent's vbtable and obtain adjustment at index ptr2memb.i32[1]
   // - parent = member - adj - vboffset - ptr2memb.i32[0]
   //
   //Even accessing to RTTI we might not be able to obtain this information
   //so anyone who thinks it's possible, please send a patch.

   //This works with gcc, msvc, ac++, ibmcpp
   #elif defined(__GNUC__)   || defined(__HP_aCC) || defined(BOOST_INTEL) || \
         defined(__IBMCPP__) || defined(__DECCXX)
   const Parent * const parent = 0;
   const char *const member = static_cast<const char*>(static_cast<const void*>(&(parent->*ptr_to_member)));
   return std::ptrdiff_t(member - static_cast<const char*>(static_cast<const void*>(parent)));
   #else
   //This is the traditional C-front approach: __MWERKS__, __DMC__, __SUNPRO_CC
   union caster_union
   {
      const Member Parent::* ptr_to_member;
      std::ptrdiff_t offset;
   } caster;
   caster.ptr_to_member = ptr_to_member;
   return caster.offset - 1;
   #endif
}

template<class Parent, class Member>
BOOST_INTRUSIVE_FORCEINLINE Parent *parent_from_member(Member *member, const Member Parent::* ptr_to_member)
{
   return static_cast<Parent*>
      (
         static_cast<void*>
         (
            static_cast<char*>(static_cast<void*>(member)) - offset_from_pointer_to_member(ptr_to_member)
         )
      );
}

template<class Parent, class Member>
BOOST_INTRUSIVE_FORCEINLINE const Parent *parent_from_member(const Member *member, const Member Parent::* ptr_to_member)
{
   return static_cast<const Parent*>
      (
         static_cast<const void*>
         (
            static_cast<const char*>(static_cast<const void*>(member)) - offset_from_pointer_to_member(ptr_to_member)
         )
      );
}

}  //namespace detail {
}  //namespace intrusive {
}  //namespace boost {

#include <boost/intrusive/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTRUSIVE_DETAIL_PARENT_FROM_MEMBER_HPP

/* parent_from_member.hpp
6yw9qM5uOYo6I2/4yVsDdWY+gxWluLezrAbrrHBxSWVJYUFp4/WWFdLWrLhh7Jk2sd6ygttaypHXm9SR5C2ytpaYGrjery3uxX+xdyZwVlV1HH9vGPYBhtkYFmEYFpF1QHYRBhhWWUZm2BRkmxFQYEYGiARzcEUjxbIiI0MzQzMdS02NDAsLi5JKi9RsSisqq8nItGz5vjO/e+e89857895AqzOfz5nvu/ee/zn/87/nnrucc/6HNFfGttuaCqYEBRKoaysjytW1CeUKu/92qY/ozaXuTniWeNWxdS0bsb5xPauTaEfC4qZ69cBxXqPjykeh22dedYSthifxfBezvbGfaVL9emH2pZt9kX4MVSdyo++Z3ySPmph2rmrUxjWjmn6/9OpqjUOvbxHvsFuvjVVr5Qglgfvm4dPQz6ufc7pG63eMeMfd+hk3gN51dG28Z40kdbvWodtJ6dbBmif4beLVunWr2FxWjuHWNqpb7Wno5p3X3d2i7fYd4tU5dZO7QNwiJNIG1SWpn+u89u3uPq+B0S79NKM5gfMaGJ2cbtc6niEPxdAt3a0bHVjljeqVfgb0Ku0RrddzxMuLoVfVqsbPZV6SernO5TvSq5MEOhJuJF6BWy8mQ1etr9jU+LlEPqz9viyJ9tt1vY7sWR/xYn3vvIjwXeIVR+tZlcx7C/J6NvH7DCRqfdM0cXKxUYxvmkojx6ThfdMMTyc3tNfEOy/Qz/qeOVTfM4cl8T1zesQ3f/UB+PnZbclOfcBYIrstJvyA+Mcddkv2HnHcKneWiWeLN9jv+Xj2s9LpZtLx7BeZlnyfmLhjw74JF8iGw5tgQ++bcJbZDs/Trn8H86Lr30vIFI5x2FH3skTaY+T1TOT1ORlR33ZFY+LbTvLss/ublIZsdskY1bvT7Gvyn6vsvibpa9tqT289jyqRboSXkT3ssJV1b23UVshHvEf4oi7bEL9p7WOO/dxo5WFfV0fzo6+rV9hX5yhj0vdoq5wjTZ2QR2DrmjoVr15YaeSYNLx6EZ5OLuw4Nvp6mq51vb7fhLrh2Y482VZ+EddSoG+E7XQtrRzrsp2eHxKwG/KR/bdG1LZb2di4diMNd/+tnU4ufF+93U67/3a6s/9W+UW8hwzo526DjjvspmebRm2GbET7s9bI+W13fHsh72h/TNZWmz02uv05JluNaEKbHdb+SF/bTsX9o+1Um8/+cdF2SvRZC9kIf16I2f2e4+LaCXnbn45vJ9Kwng/GRdvpXN3blmU03U6+f+TI8RVnR/fj/CxUn9x20rNf47Y6bpWVNPnli7psQ/ym9+VY14/SZdvKz16jZMKA6HUXdob8QIwLW3dh2pLSafNKZs2f5684Ib8/pxpZg6HOKveyBNacqBvX9DUn0CVqzYll4WtOvKt9zvx5f2j/C68c/M5nNhfNqb6q7+6vntNlcbPPmf8nnzO6UEw/WS3xSuQHsMAfH6rrjNCC0Nfy4RHib2Fr+DvoydXEkXtBcj+Q3A8tucOSa+2Qe0pyX4Gt4GHJbffGLMLFDp8GL0rux7Az/AnMhrUwD/4U9oU/gxPgq7AQ/gpOhr+Ac+Av4Xx4Ei7SceXP+L/Y+X9N+X9d+R9V/s8q/28q/28p/2PK/3vK/znlf1z5f1f5c9z3eVCj/Bc6fB48qPwfhh00RzYTfkl6fEF6PCI9HpUej8FCxZsMH4cXwCfgXPgkLNVxnT/GsMU+f32MHmzr/PXz5Qjnxq4vwyU3QvXlXEuuMI7caMmNkdxYy17F58a2V4bksmWvHNkrT/bqInvlyl5dZa9usFDxJsMestdZslcv2StPesz0xhjBAdKjFWGC5wNEc6IHSo9Bqj+DYQ84BJ4=
*/