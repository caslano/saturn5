//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_OFFSET_PTR_HPP
#define BOOST_INTERPROCESS_OFFSET_PTR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_constructible.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_unsigned.hpp>

#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/cast_tags.hpp>
#include <boost/interprocess/detail/mpl.hpp>
#include <boost/container/detail/type_traits.hpp>  //alignment_of, aligned_storage
#include <boost/assert.hpp>
#include <iosfwd>

#if defined(BOOST_GCC) && (BOOST_GCC >= 40600)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif


//!\file
//!Describes a smart pointer that stores the offset between this pointer and
//!target pointee, called offset_ptr.

namespace boost {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

//Predeclarations
template <class T>
struct has_trivial_destructor;

#endif   //#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
namespace ipcdetail {

   template<class OffsetType, std::size_t OffsetAlignment>
   union offset_ptr_internal
   {
      BOOST_STATIC_ASSERT(sizeof(OffsetType) >= sizeof(uintptr_t));
      BOOST_STATIC_ASSERT(boost::is_integral<OffsetType>::value && boost::is_unsigned<OffsetType>::value);

      explicit offset_ptr_internal(OffsetType off)
         : m_offset(off)
      {}

      OffsetType m_offset; //Distance between this object and pointee address

      typename ::boost::container::dtl::aligned_storage
         < sizeof(OffsetType)//for offset_type_alignment m_offset will be enough
         , (OffsetAlignment == offset_type_alignment) ? 1u : OffsetAlignment
         >::type alignment_helper;
   };

   //Note: using the address of a local variable to point to another address
   //is not standard conforming and this can be optimized-away by the compiler.
   //Non-inlining is a method to remain illegal but correct

   //Undef BOOST_INTERPROCESS_OFFSET_PTR_INLINE_XXX if your compiler can inline
   //this code without breaking the library

   ////////////////////////////////////////////////////////////////////////
   //
   //                      offset_ptr_to_raw_pointer
   //
   ////////////////////////////////////////////////////////////////////////
   #define BOOST_INTERPROCESS_OFFSET_PTR_BRANCHLESS_TO_PTR
   template <class OffsetType>
   BOOST_INTERPROCESS_FORCEINLINE void * offset_ptr_to_raw_pointer(const volatile void *this_ptr, OffsetType offset)
   {
      typedef pointer_offset_caster<void*, OffsetType> caster_t;
      #ifndef BOOST_INTERPROCESS_OFFSET_PTR_BRANCHLESS_TO_PTR
         if(offset == 1){
            return 0;
         }
         else{
            return caster_t(caster_t(this_ptr).offset() + offset).pointer();
         }
      #else
         OffsetType mask = offset == 1;
         --mask;
         OffsetType target_offset = caster_t(this_ptr).offset() + offset;
         target_offset &= mask;
         return caster_t(target_offset).pointer();
      #endif
   }

   ////////////////////////////////////////////////////////////////////////
   //
   //                      offset_ptr_to_offset
   //
   ////////////////////////////////////////////////////////////////////////
   #define BOOST_INTERPROCESS_OFFSET_PTR_BRANCHLESS_TO_OFF
   template<class OffsetType>
   BOOST_INTERPROCESS_FORCEINLINE OffsetType offset_ptr_to_offset(const volatile void *ptr, const volatile void *this_ptr)
   {
      typedef pointer_offset_caster<void*, OffsetType> caster_t;
      #ifndef BOOST_INTERPROCESS_OFFSET_PTR_BRANCHLESS_TO_OFF
         //offset == 1 && ptr != 0 is not legal for this pointer
         if(!ptr){
            return 1;
         }
         else{
            OffsetType offset = caster_t(ptr).offset()- caster_t(this_ptr).offset();
            BOOST_ASSERT(offset != 1);
            return offset;
         }
      #else
         //const OffsetType other = -OffsetType(ptr != 0);
         //const OffsetType offset = (caster_t(ptr).offset() - caster_t(this_ptr).offset()) & other;
         //return offset + OffsetType(!other);
         //
         OffsetType offset = caster_t(ptr).offset() - caster_t(this_ptr).offset();
         --offset;
         OffsetType mask = ptr == 0;
         --mask;
         offset &= mask;
         return ++offset;
      #endif
   }

   ////////////////////////////////////////////////////////////////////////
   //
   //                      offset_ptr_to_offset_from_other
   //
   ////////////////////////////////////////////////////////////////////////
   #define BOOST_INTERPROCESS_OFFSET_PTR_BRANCHLESS_TO_OFF_FROM_OTHER
   template<class OffsetType>
   BOOST_INTERPROCESS_FORCEINLINE OffsetType offset_ptr_to_offset_from_other
      (const volatile void *this_ptr, const volatile void *other_ptr, OffsetType other_offset)
   {
      typedef pointer_offset_caster<void*, OffsetType> caster_t;
      #ifndef BOOST_INTERPROCESS_OFFSET_PTR_BRANCHLESS_TO_OFF_FROM_OTHER
      if(other_offset == 1){
         return 1;
      }
      else{
         OffsetType offset = caster_t(other_ptr).offset() - caster_t(this_ptr).offset() + other_offset;
         BOOST_ASSERT(offset != 1);
         return offset;
      }
      #else
      OffsetType mask = other_offset == 1;
      --mask;
      OffsetType offset = caster_t(other_ptr).offset() - caster_t(this_ptr).offset();
      offset &= mask;
      return offset + other_offset;

      //OffsetType mask = -OffsetType(other_offset != 1);
      //OffsetType offset = caster_t(other_ptr).offset() - caster_t(this_ptr).offset();
      //offset &= mask;
      //return offset + other_offset;
      #endif
   }

   ////////////////////////////////////////////////////////////////////////
   //
   // Let's assume cast to void and cv cast don't change any target address
   //
   ////////////////////////////////////////////////////////////////////////
   template<class From, class To>
   struct offset_ptr_maintains_address
   {
      static const bool value =    ipcdetail::is_cv_same<From, To>::value
                                || ipcdetail::is_cv_same<void, To>::value
                                || ipcdetail::is_cv_same<char, To>::value
                                ;
   };

   template<class From, class To, class Ret = void>
   struct enable_if_convertible_equal_address
      : enable_if_c< ::boost::is_convertible<From*, To*>::value
                     && offset_ptr_maintains_address<From, To>::value
                  , Ret>
   {};

   template<class From, class To, class Ret = void>
   struct enable_if_convertible_unequal_address
      : enable_if_c< ::boost::is_convertible<From*, To*>::value
                     && !offset_ptr_maintains_address<From, To>::value
                   , Ret>
   {};

}  //namespace ipcdetail {
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!A smart pointer that stores the offset between between the pointer and the
//!the object it points. This allows offset allows special properties, since
//!the pointer is independent from the address of the pointee, if the
//!pointer and the pointee are still separated by the same offset. This feature
//!converts offset_ptr in a smart pointer that can be placed in shared memory and
//!memory mapped files mapped in different addresses in every process.
//!
//! \tparam PointedType The type of the pointee.
//! \tparam DifferenceType A signed integer type that can represent the arithmetic operations on the pointer
//! \tparam OffsetType An unsigned integer type that can represent the
//!   distance between two pointers reinterpret_cast-ed as unsigned integers. This type
//!   should be at least of the same size of std::uintptr_t. In some systems it's possible to communicate
//!   between 32 and 64 bit processes using 64 bit offsets.
//! \tparam OffsetAlignment Alignment of the OffsetType stored inside. In some systems might be necessary
//!   to align it to 64 bits in order to communicate 32 and 64 bit processes using 64 bit offsets.
//!
//!<b>Note</b>: offset_ptr uses implementation defined properties, present in most platforms, for
//!performance reasons:
//!   - Assumes that OffsetType representation of nullptr is (OffsetType)zero.
//!   - Assumes that incrementing a OffsetType obtained from a pointer is equivalent
//!     to incrementing the pointer and then converting it back to OffsetType.
template <class PointedType, class DifferenceType, class OffsetType, std::size_t OffsetAlignment>
class offset_ptr
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef offset_ptr<PointedType, DifferenceType, OffsetType, OffsetAlignment>   self_t;
   void unspecified_bool_type_func() const {}
   typedef void (self_t::*unspecified_bool_type)() const;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   typedef PointedType                       element_type;
   typedef PointedType *                     pointer;
   typedef typename ipcdetail::
      add_reference<PointedType>::type       reference;
   typedef typename ipcdetail::
      remove_volatile<typename ipcdetail::
         remove_const<PointedType>::type
            >::type                          value_type;
   typedef DifferenceType                    difference_type;
   typedef std::random_access_iterator_tag   iterator_category;
   typedef OffsetType                        offset_type;

   public:   //Public Functions

   //!Default constructor (null pointer).
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr() BOOST_NOEXCEPT
      : internal(1)
   {}

   //!Constructor from raw pointer (allows "0" pointer conversion).
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr(pointer ptr) BOOST_NOEXCEPT
      : internal(ipcdetail::offset_ptr_to_offset<OffsetType>(ptr, this))
   {}

   //!Constructor from other pointer.
   //!Never throws.
   template <class T>
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr( T *ptr
             , typename ipcdetail::enable_if< ::boost::is_convertible<T*, PointedType*> >::type * = 0) BOOST_NOEXCEPT
      : internal(ipcdetail::offset_ptr_to_offset<OffsetType>(static_cast<PointedType*>(ptr), this))
   {}

   //!Constructor from other offset_ptr
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr(const offset_ptr& ptr) BOOST_NOEXCEPT
      : internal(ipcdetail::offset_ptr_to_offset_from_other(this, &ptr, ptr.internal.m_offset))
   {}

   //!Constructor from other offset_ptr. Only takes part in overload resolution
   //!if T2* is convertible to PointedType*. Never throws.
   template<class T2>
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr( const offset_ptr<T2, DifferenceType, OffsetType, OffsetAlignment> &ptr
             #ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
             , typename ipcdetail::enable_if_convertible_equal_address<T2, PointedType>::type* = 0
             #endif
             ) BOOST_NOEXCEPT
      : internal(ipcdetail::offset_ptr_to_offset_from_other(this, &ptr, ptr.get_offset()))
   {}

   #ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   template<class T2>
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr( const offset_ptr<T2, DifferenceType, OffsetType, OffsetAlignment> &ptr
             , typename ipcdetail::enable_if_convertible_unequal_address<T2, PointedType>::type* = 0) BOOST_NOEXCEPT
      : internal(ipcdetail::offset_ptr_to_offset<OffsetType>(static_cast<PointedType*>(ptr.get()), this))
   {}

   #endif

   //!Constructor from other offset_ptr. Only takes part in overload resolution
   //!if PointedType* is constructible from T2* other than via a conversion (e.g. cast to a derived class). Never throws.
   template<class T2>
   BOOST_INTERPROCESS_FORCEINLINE explicit offset_ptr(const offset_ptr<T2, DifferenceType, OffsetType, OffsetAlignment> &ptr
             #ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
             , typename ipcdetail::enable_if_c<
                !::boost::is_convertible<T2*, PointedType*>::value && ::boost::is_constructible<T2*, PointedType*>::value
             >::type * = 0
             #endif
             ) BOOST_NOEXCEPT
      : internal(ipcdetail::offset_ptr_to_offset<OffsetType>(static_cast<PointedType*>(ptr.get()), this))
   {}

   //!Emulates static_cast operator.
   //!Never throws.
   template<class T2, class P2, class O2, std::size_t A2>
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr(const offset_ptr<T2, P2, O2, A2> & r, ipcdetail::static_cast_tag) BOOST_NOEXCEPT
      : internal(ipcdetail::offset_ptr_to_offset<OffsetType>(static_cast<PointedType*>(r.get()), this))
   {}

   //!Emulates const_cast operator.
   //!Never throws.
   template<class T2, class P2, class O2, std::size_t A2>
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr(const offset_ptr<T2, P2, O2, A2> & r, ipcdetail::const_cast_tag) BOOST_NOEXCEPT
      : internal(ipcdetail::offset_ptr_to_offset<OffsetType>(const_cast<PointedType*>(r.get()), this))
   {}

   //!Emulates dynamic_cast operator.
   //!Never throws.
   template<class T2, class P2, class O2, std::size_t A2>
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr(const offset_ptr<T2, P2, O2, A2> & r, ipcdetail::dynamic_cast_tag) BOOST_NOEXCEPT
      : internal(ipcdetail::offset_ptr_to_offset<OffsetType>(dynamic_cast<PointedType*>(r.get()), this))
   {}

   //!Emulates reinterpret_cast operator.
   //!Never throws.
   template<class T2, class P2, class O2, std::size_t A2>
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr(const offset_ptr<T2, P2, O2, A2> & r, ipcdetail::reinterpret_cast_tag) BOOST_NOEXCEPT
      : internal(ipcdetail::offset_ptr_to_offset<OffsetType>(reinterpret_cast<PointedType*>(r.get()), this))
   {}

   //!Obtains raw pointer from offset.
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE pointer get() const BOOST_NOEXCEPT
   {  return static_cast<pointer>(ipcdetail::offset_ptr_to_raw_pointer(this, this->internal.m_offset));   }

   BOOST_INTERPROCESS_FORCEINLINE offset_type get_offset() const BOOST_NOEXCEPT
   {  return this->internal.m_offset;  }

   //!Pointer-like -> operator. It can return 0 pointer.
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE pointer operator->() const BOOST_NOEXCEPT
   {  return this->get(); }

   //!Dereferencing operator, if it is a null offset_ptr behavior
   //!   is undefined. Never throws.
   BOOST_INTERPROCESS_FORCEINLINE reference operator* () const BOOST_NOEXCEPT
   {
      pointer p = this->get();
      reference r = *p;
      return r;
   }

   //!Indexing operator.
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE reference operator[](difference_type idx) const BOOST_NOEXCEPT
   {  return this->get()[idx];  }

   //!Assignment from pointer (saves extra conversion).
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr& operator= (pointer from) BOOST_NOEXCEPT
   {
      this->internal.m_offset = ipcdetail::offset_ptr_to_offset<OffsetType>(from, this);
      return *this;
   }

   //!Assignment from other offset_ptr.
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr& operator= (const offset_ptr & ptr) BOOST_NOEXCEPT
   {
      this->internal.m_offset = ipcdetail::offset_ptr_to_offset_from_other(this, &ptr, ptr.internal.m_offset);
      return *this;
   }

   //!Assignment from related offset_ptr. If pointers of pointee types
   //!   are assignable, offset_ptrs will be assignable. Never throws.
   template<class T2> BOOST_INTERPROCESS_FORCEINLINE 
   #ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   typename ipcdetail::enable_if_c
      < ::boost::is_convertible<T2*, PointedType*>::value, offset_ptr&>::type
   #else
   offset_ptr&
   #endif
      operator= (const offset_ptr<T2, DifferenceType, OffsetType, OffsetAlignment> &ptr) BOOST_NOEXCEPT
   {
      this->assign(ptr, ipcdetail::bool_<ipcdetail::offset_ptr_maintains_address<T2, PointedType>::value>());
      return *this;
   }

   public:

   //!offset_ptr += difference_type.
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr &operator+= (difference_type offset) BOOST_NOEXCEPT
   {  this->inc_offset(offset * difference_type(sizeof(PointedType)));   return *this;  }

   //!offset_ptr -= difference_type.
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr &operator-= (difference_type offset) BOOST_NOEXCEPT
   {  this->dec_offset(offset * difference_type(sizeof(PointedType)));   return *this;  }

   //!++offset_ptr.
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr& operator++ (void) BOOST_NOEXCEPT
   {  this->inc_offset(difference_type(sizeof(PointedType)));   return *this;  }

   //!offset_ptr++.
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr operator++ (int) BOOST_NOEXCEPT
   {
      offset_ptr tmp(*this);
      this->inc_offset(sizeof (PointedType));
      return tmp;
   }

   //!--offset_ptr.
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr& operator-- (void) BOOST_NOEXCEPT
   {  this->dec_offset(sizeof (PointedType));   return *this;  }

   //!offset_ptr--.
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr operator-- (int) BOOST_NOEXCEPT
   {
      offset_ptr tmp(*this);
      this->dec_offset(sizeof (PointedType));
      return tmp;
   }

   //!safe bool conversion operator.
   //!Never throws.
   #if defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)
   BOOST_INTERPROCESS_FORCEINLINE operator unspecified_bool_type() const BOOST_NOEXCEPT
   {  return this->internal.m_offset != 1? &self_t::unspecified_bool_type_func : 0;   }
   #else
   explicit operator bool() const BOOST_NOEXCEPT
   {  return this->internal.m_offset != 1;  }
   #endif
   
   //!Not operator. Not needed in theory, but improves portability.
   //!Never throws
   BOOST_INTERPROCESS_FORCEINLINE bool operator! () const BOOST_NOEXCEPT
   {  return this->internal.m_offset == 1;   }

   //!Compatibility with pointer_traits
   //!
   #if defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
   template <class U>
   struct rebind
   {  typedef offset_ptr<U, DifferenceType, OffsetType, OffsetAlignment> other;  };
   #else
   template <class U>
   using rebind = offset_ptr<U, DifferenceType, OffsetType, OffsetAlignment>;
   #ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   typedef offset_ptr<PointedType, DifferenceType, OffsetType, OffsetAlignment> other;
   #endif //BOOST_INTERPROCESS_DOXYGEN_INVOKED
   #endif

   //!Compatibility with pointer_traits
   //!
   BOOST_INTERPROCESS_FORCEINLINE static offset_ptr pointer_to(reference r) BOOST_NOEXCEPT
   { return offset_ptr(&r); }

   //!difference_type + offset_ptr
   //!operation
   BOOST_INTERPROCESS_FORCEINLINE friend offset_ptr operator+(difference_type diff, offset_ptr right) BOOST_NOEXCEPT
   {  right += diff;  return right;  }

   //!offset_ptr + difference_type
   //!operation
   BOOST_INTERPROCESS_FORCEINLINE friend offset_ptr operator+(offset_ptr left, difference_type diff) BOOST_NOEXCEPT
   {  left += diff;  return left; }

   //!offset_ptr - diff
   //!operation
   BOOST_INTERPROCESS_FORCEINLINE friend offset_ptr operator-(offset_ptr left, difference_type diff) BOOST_NOEXCEPT
   {  left -= diff;  return left; }

   //!offset_ptr - diff
   //!operation
   BOOST_INTERPROCESS_FORCEINLINE friend offset_ptr operator-(difference_type diff, offset_ptr right) BOOST_NOEXCEPT
   {  right -= diff; return right; }

   //!offset_ptr - offset_ptr
   //!operation
   BOOST_INTERPROCESS_FORCEINLINE friend difference_type operator-(const offset_ptr &pt, const offset_ptr &pt2) BOOST_NOEXCEPT
   {  return difference_type(pt.get()- pt2.get());   }

   //Comparison
   BOOST_INTERPROCESS_FORCEINLINE friend bool operator== (const offset_ptr &pt1, const offset_ptr &pt2) BOOST_NOEXCEPT
   {  return pt1.get() == pt2.get();  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator!= (const offset_ptr &pt1, const offset_ptr &pt2) BOOST_NOEXCEPT
   {  return pt1.get() != pt2.get();  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator<(const offset_ptr &pt1, const offset_ptr &pt2) BOOST_NOEXCEPT
   {  return pt1.get() < pt2.get();  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator<=(const offset_ptr &pt1, const offset_ptr &pt2) BOOST_NOEXCEPT
   {  return pt1.get() <= pt2.get();  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator>(const offset_ptr &pt1, const offset_ptr &pt2) BOOST_NOEXCEPT
   {  return pt1.get() > pt2.get();  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator>=(const offset_ptr &pt1, const offset_ptr &pt2) BOOST_NOEXCEPT
   {  return pt1.get() >= pt2.get();  }

   //Comparison to raw ptr to support literal 0
   BOOST_INTERPROCESS_FORCEINLINE friend bool operator== (pointer pt1, const offset_ptr &pt2) BOOST_NOEXCEPT
   {  return pt1 == pt2.get();  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator!= (pointer pt1, const offset_ptr &pt2) BOOST_NOEXCEPT
   {  return pt1 != pt2.get();  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator<(pointer pt1, const offset_ptr &pt2) BOOST_NOEXCEPT
   {  return pt1 < pt2.get();  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator<=(pointer pt1, const offset_ptr &pt2) BOOST_NOEXCEPT
   {  return pt1 <= pt2.get();  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator>(pointer pt1, const offset_ptr &pt2) BOOST_NOEXCEPT
   {  return pt1 > pt2.get();  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator>=(pointer pt1, const offset_ptr &pt2) BOOST_NOEXCEPT
   {  return pt1 >= pt2.get();  }

   //Comparison
   BOOST_INTERPROCESS_FORCEINLINE friend bool operator== (const offset_ptr &pt1, pointer pt2) BOOST_NOEXCEPT
   {  return pt1.get() == pt2;  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator!= (const offset_ptr &pt1, pointer pt2) BOOST_NOEXCEPT
   {  return pt1.get() != pt2;  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator<(const offset_ptr &pt1, pointer pt2) BOOST_NOEXCEPT
   {  return pt1.get() < pt2;  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator<=(const offset_ptr &pt1, pointer pt2) BOOST_NOEXCEPT
   {  return pt1.get() <= pt2;  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator>(const offset_ptr &pt1, pointer pt2) BOOST_NOEXCEPT
   {  return pt1.get() > pt2;  }

   BOOST_INTERPROCESS_FORCEINLINE friend bool operator>=(const offset_ptr &pt1, pointer pt2) BOOST_NOEXCEPT
   {  return pt1.get() >= pt2;  }

   BOOST_INTERPROCESS_FORCEINLINE friend void swap(offset_ptr &left, offset_ptr &right) BOOST_NOEXCEPT
   {
      pointer ptr = right.get();
      right = left;
      left = ptr;
   }

   private:
   template<class T2>
   BOOST_INTERPROCESS_FORCEINLINE void assign(const offset_ptr<T2, DifferenceType, OffsetType, OffsetAlignment> &ptr, ipcdetail::bool_<true>) BOOST_NOEXCEPT
   {  //no need to pointer adjustment
      this->internal.m_offset = ipcdetail::offset_ptr_to_offset_from_other<OffsetType>(this, &ptr, ptr.get_offset());
   }

   template<class T2>
   BOOST_INTERPROCESS_FORCEINLINE void assign(const offset_ptr<T2, DifferenceType, OffsetType, OffsetAlignment> &ptr, ipcdetail::bool_<false>) BOOST_NOEXCEPT
   {  //we must convert to raw before calculating the offset
      this->internal.m_offset = ipcdetail::offset_ptr_to_offset<OffsetType>(static_cast<PointedType*>(ptr.get()), this);
   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   BOOST_INTERPROCESS_FORCEINLINE void inc_offset(DifferenceType bytes) BOOST_NOEXCEPT
   {  internal.m_offset += OffsetType(bytes);   }

   BOOST_INTERPROCESS_FORCEINLINE void dec_offset(DifferenceType bytes) BOOST_NOEXCEPT
   {  internal.m_offset -= OffsetType(bytes);   }

   ipcdetail::offset_ptr_internal<OffsetType, OffsetAlignment> internal;

   public:
   BOOST_INTERPROCESS_FORCEINLINE const OffsetType &priv_offset() const BOOST_NOEXCEPT
   {  return internal.m_offset;   }

   BOOST_INTERPROCESS_FORCEINLINE       OffsetType &priv_offset() BOOST_NOEXCEPT
   {  return internal.m_offset;   }

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

//!operator<<
//!for offset ptr
template<class E, class T, class W, class X, class Y, std::size_t Z>
inline std::basic_ostream<E, T> & operator<<
   (std::basic_ostream<E, T> & os, offset_ptr<W, X, Y, Z> const & p)
{  return os << p.get_offset();   }

//!operator>>
//!for offset ptr
template<class E, class T, class W, class X, class Y, std::size_t Z>
inline std::basic_istream<E, T> & operator>>
   (std::basic_istream<E, T> & is, offset_ptr<W, X, Y, Z> & p)
{  return is >> p.get_offset();  }

//!Simulation of static_cast between pointers. Never throws.
template<class T1, class P1, class O1, std::size_t A1, class T2, class P2, class O2, std::size_t A2>
BOOST_INTERPROCESS_FORCEINLINE boost::interprocess::offset_ptr<T1, P1, O1, A1>
   static_pointer_cast(const boost::interprocess::offset_ptr<T2, P2, O2, A2> & r) BOOST_NOEXCEPT
{
   return boost::interprocess::offset_ptr<T1, P1, O1, A1>
            (r, boost::interprocess::ipcdetail::static_cast_tag());
}

//!Simulation of const_cast between pointers. Never throws.
template<class T1, class P1, class O1, std::size_t A1, class T2, class P2, class O2, std::size_t A2>
BOOST_INTERPROCESS_FORCEINLINE boost::interprocess::offset_ptr<T1, P1, O1, A1>
   const_pointer_cast(const boost::interprocess::offset_ptr<T2, P2, O2, A2> & r) BOOST_NOEXCEPT
{
   return boost::interprocess::offset_ptr<T1, P1, O1, A1>
            (r, boost::interprocess::ipcdetail::const_cast_tag());
}

//!Simulation of dynamic_cast between pointers. Never throws.
template<class T1, class P1, class O1, std::size_t A1, class T2, class P2, class O2, std::size_t A2>
BOOST_INTERPROCESS_FORCEINLINE boost::interprocess::offset_ptr<T1, P1, O1, A1>
   dynamic_pointer_cast(const boost::interprocess::offset_ptr<T2, P2, O2, A2> & r) BOOST_NOEXCEPT
{
   return boost::interprocess::offset_ptr<T1, P1, O1, A1>
            (r, boost::interprocess::ipcdetail::dynamic_cast_tag());
}

//!Simulation of reinterpret_cast between pointers. Never throws.
template<class T1, class P1, class O1, std::size_t A1, class T2, class P2, class O2, std::size_t A2>
BOOST_INTERPROCESS_FORCEINLINE boost::interprocess::offset_ptr<T1, P1, O1, A1>
   reinterpret_pointer_cast(const boost::interprocess::offset_ptr<T2, P2, O2, A2> & r) BOOST_NOEXCEPT
{
   return boost::interprocess::offset_ptr<T1, P1, O1, A1>
            (r, boost::interprocess::ipcdetail::reinterpret_cast_tag());
}

}  //namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

///has_trivial_destructor<> == true_type specialization for optimizations
template <class T, class P, class O, std::size_t A>
struct has_trivial_destructor< ::boost::interprocess::offset_ptr<T, P, O, A> >
{
   static const bool value = true;
};

namespace move_detail {

///has_trivial_destructor<> == true_type specialization for optimizations
template <class T, class P, class O, std::size_t A>
struct is_trivially_destructible< ::boost::interprocess::offset_ptr<T, P, O, A> >
{
   static const bool value = true;
};

}  //namespace move_detail {

namespace interprocess {

//!to_raw_pointer() enables boost::mem_fn to recognize offset_ptr.
//!Never throws.
template <class T, class P, class O, std::size_t A>
BOOST_INTERPROCESS_FORCEINLINE T * to_raw_pointer(boost::interprocess::offset_ptr<T, P, O, A> const & p) BOOST_NOEXCEPT
{  return ipcdetail::to_raw_pointer(p);   }

}  //namespace interprocess


#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
}  //namespace boost {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace boost{

//This is to support embedding a bit in the pointer
//for intrusive containers, saving space
namespace intrusive {

//Predeclaration to avoid including header
template<class VoidPointer, std::size_t N>
struct max_pointer_plus_bits;

template<std::size_t OffsetAlignment, class P, class O, std::size_t A>
struct max_pointer_plus_bits<boost::interprocess::offset_ptr<void, P, O, A>, OffsetAlignment>
{
   //The offset ptr can embed one bit less than the alignment since it
   //uses offset == 1 to store the null pointer.
   static const std::size_t value = ::boost::interprocess::ipcdetail::ls_zeros<OffsetAlignment>::value - 1;
};

//Predeclaration
template<class Pointer, std::size_t NumBits>
struct pointer_plus_bits;

template<class T, class P, class O, std::size_t A, std::size_t NumBits>
struct pointer_plus_bits<boost::interprocess::offset_ptr<T, P, O, A>, NumBits>
{
   typedef boost::interprocess::offset_ptr<T, P, O, A>      pointer;
   //Bits are stored in the lower bits of the pointer except the LSB,
   //because this bit is used to represent the null pointer.
   static const O Mask = ((static_cast<O>(1) << NumBits) - static_cast<O>(1)) << 1;
   BOOST_STATIC_ASSERT(0 ==(Mask&1));

   //We must ALWAYS take argument "n" by reference as a copy of a null pointer
   //with a bit (e.g. offset == 3) would be incorrectly copied and interpreted as non-null.

   BOOST_INTERPROCESS_FORCEINLINE static pointer get_pointer(const pointer &n) BOOST_NOEXCEPT
   {
      pointer p;
      O const tmp_off = n.priv_offset() & ~Mask;
      p.priv_offset() = boost::interprocess::ipcdetail::offset_ptr_to_offset_from_other(&p, &n, tmp_off);
      return p;
   }

   BOOST_INTERPROCESS_FORCEINLINE static void set_pointer(pointer &n, const pointer &p) BOOST_NOEXCEPT
   {
      BOOST_ASSERT(0 == (get_bits)(p));
      O const stored_bits = n.priv_offset() & Mask;
      n = p;
      n.priv_offset() |= stored_bits;
   }

   BOOST_INTERPROCESS_FORCEINLINE static std::size_t get_bits(const pointer &n) BOOST_NOEXCEPT
   {
      return std::size_t((n.priv_offset() & Mask) >> 1u);
   }

   BOOST_INTERPROCESS_FORCEINLINE static void set_bits(pointer &n, std::size_t const b) BOOST_NOEXCEPT
   {
      BOOST_ASSERT(b < (std::size_t(1) << NumBits));
      O tmp = n.priv_offset();
      tmp &= ~Mask;
      tmp |= O(b << 1u);
      n.priv_offset() = tmp;
   }
};

}  //namespace intrusive

//Predeclaration
template<class T, class U>
struct pointer_to_other;

//Backwards compatibility with pointer_to_other
template <class PointedType, class DifferenceType, class OffsetType, std::size_t OffsetAlignment, class U>
struct pointer_to_other
   < ::boost::interprocess::offset_ptr<PointedType, DifferenceType, OffsetType, OffsetAlignment>, U >
{
   typedef ::boost::interprocess::offset_ptr<U, DifferenceType, OffsetType, OffsetAlignment> type;
};

}  //namespace boost{
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

#include <boost/interprocess/detail/config_end.hpp>

#if defined(BOOST_GCC) && (BOOST_GCC >= 40600)
#pragma GCC diagnostic pop
#endif

#endif //#ifndef BOOST_INTERPROCESS_OFFSET_PTR_HPP

/* offset_ptr.hpp
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
*/