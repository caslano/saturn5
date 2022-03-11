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
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
*/