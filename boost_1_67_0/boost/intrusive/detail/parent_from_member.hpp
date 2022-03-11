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