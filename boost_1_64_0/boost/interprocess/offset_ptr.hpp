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
   {  this->inc_offset(offset * sizeof (PointedType));   return *this;  }

   //!offset_ptr -= difference_type.
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr &operator-= (difference_type offset) BOOST_NOEXCEPT
   {  this->dec_offset(offset * sizeof (PointedType));   return *this;  }

   //!++offset_ptr.
   //!Never throws.
   BOOST_INTERPROCESS_FORCEINLINE offset_ptr& operator++ (void) BOOST_NOEXCEPT
   {  this->inc_offset(sizeof (PointedType));   return *this;  }

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
   {  internal.m_offset += bytes;   }

   BOOST_INTERPROCESS_FORCEINLINE void dec_offset(DifferenceType bytes) BOOST_NOEXCEPT
   {  internal.m_offset -= bytes;   }

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

#endif //#ifndef BOOST_INTERPROCESS_OFFSET_PTR_HPP

/* offset_ptr.hpp
4vH2e+uekOGiWya4gzZJeJwOmWCcFi8kjgVG8Xidw3xRui7xx+hM44+QDz3eoArC2922cKFqvawSHqkNHowbzhaPsf9sViRWcx6I078ShcbfuHFzxRtQbVx4nF3OovE3buCACQvGhje/GrlgnDMMPfbIe+VDNaODrDYKN0VU76TsU+sFEue2mTMIVdaOQlWPuy4hud+qppfMnXWq9wkC1bvNbX6fmw4PD7jlJ93kkvI9URX53qcyPU4lTy8LzrvBK5qq1uZSlTaE3unhx+bKWtsQrUr+C0zuK6ObF5mckqkhdL5/woQReD+aRvudJj06cGFKlUdHxu5/gOcfvaoHDB4oXCcIXnZVhfNShDHXwd6+pScKubDlu3SrukIhaAJ7gtSIsSfm5AD+LqdK7bW+Ex4bHiiIarRUHnlSzqnq8MvC+phufk13E3dFi0Rx27Z4DHfhjofH6l3h8KjQIwv9U0/qX3J7LhSGXSAMuzBY/IJg8EJg4AKgXsceGLT/yOp82mkzTnueWkQiwh64QBlMwFmt8tUal2J0ZPypIWrtpiqz3+YLzDUq2B+DV9iDarVk4Vfdg1fcURzxjzJU/lGmX39yZO+DM8FhryYnEKV3X931qwe4lOG7eu/Xbi4Sqcn8t/hcstp/x5sq+D/auVXv03l321yH2COThHUqya8/HbPr1jgTu50l+5NiwThbXei7GumoD+oF1fDIvKJI5JOP3ZRhgiv0Kve1VzW9Lq1zmJOv8DhdzIRHH6OBi+/jpOwurFah92aO5265KlRyho1rYsrbdWfdbmvshteOrSpvxw64kOEPWuUKY9q2EKoLjnP/baXwmwbhN5oCN5n0BpP35pIOePvT/X6d1queQ4eYanU0hat1kBGVzdqfKlNj6USoWXBL7JVX6PcJ8gqmQ087uS8fuhdYm46x/rZHaUDh+UuOHXvTmN5MDih0qgnqmW5UH7wbjT5w8xjVwcKzwL4k0Pv3C+ZA1UWOdg2Y43ffXPGqOGrr1PHy6rNU5/B4QD16E0+TebRPuon/8w0/zaN08nBg2K8LHl44f86rzOWTZbb2RNDR6Opu1eZbe+zBFBpDz3DeA/QE97G54YHCG0ToBJoxjQtWDvpgeVEGS4EyvBREaClUFSyFxhQvhX/JjYZaDhG15/i1dBzVhi+VNCrfpR6f/zMfv/J/5uNX9yMe/mD7h/7Vj5+FaJ7ou4kH+p7QtXuf6/2PN7U6L+3JPwqEPOzIux/+6IftftT9e3kOGZ3nJSWqcF7hZcsP3v1wdu+2H46yFXt77t/Vxf+x93mlJzz8gZEnouh5zEPtfzzy2/VNF5+4uYd+sUWlQvwAGt6tQtpStgfyitBenuB01Pv2Djxi9FF2zyrITMn21PrAoZHhJwXVOTT50j1g7+ZLylT3sB5V+WtKdfna2Pv43V29vMAoEOFPY+/976EqT2Wr4uGP7u7OS9peyMF3qqnWfuHH/R/QvTtE5dt38+NCvMX+cW5tr1fRe8+7+Y90FxHpcT0u6dG+cqB5+F6uLuzzVwIRvQ/0piR/UPPv9Ji9+/b6M+9q4Efzh4RH7e113hed7xa+GByxvfmm4mvY2tls1QPoCw90v+dYtPZfLvY+aO8DaWT74be9u/N6Xt36QOe93Hv5I+mm7lGDTxoczo49ynn/RUFd6K32E9ldvKaOJ+kKp9CPVjnCuFvay5v+uWb8OFehObyn+/58/H6/0wc0OZ/oDEh03u9cBTVO7gLaA9mCUsdgXpH3an2ipqMqTUQenij8dhVx9wNdcb6PaOVVAYVmUhW+sqAMFAWdZtwluY7xZZuP5nMdrPdxmzVJn8q/bLqrIOe/AJH/+sOmlhI9nCY=
*/