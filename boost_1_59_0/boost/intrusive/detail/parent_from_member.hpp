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
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
*/