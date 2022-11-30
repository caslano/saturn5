//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2015.
// (C) Copyright Gennaro Prota 2003 - 2004.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_UTILITIES_HPP
#define BOOST_INTERPROCESS_DETAIL_UTILITIES_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/interprocess/detail/min_max.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/detail/mpl.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/static_assert.hpp>
#include <boost/cstdint.hpp>
#include <climits>

namespace boost {
namespace interprocess {
namespace ipcdetail {

template <class T>
inline T* to_raw_pointer(T* p)
{  return p; }

template <class Pointer>
inline typename boost::intrusive::pointer_traits<Pointer>::element_type*
to_raw_pointer(const Pointer &p)
{  return boost::interprocess::ipcdetail::to_raw_pointer(p.operator->());  }

//Rounds "orig_size" by excess to round_to bytes
template<class SizeType>
inline SizeType get_rounded_size(SizeType orig_size, SizeType round_to)
{
   return ((orig_size-1)/round_to+1)*round_to;
}

//Truncates "orig_size" to a multiple of "multiple" bytes.
template<class SizeType>
inline SizeType get_truncated_size(SizeType orig_size, SizeType multiple)
{
   return orig_size/multiple*multiple;
}

//Rounds "orig_size" by excess to round_to bytes. round_to must be power of two
template<class SizeType>
inline SizeType get_rounded_size_po2(SizeType orig_size, SizeType round_to)
{
   return ((orig_size-1)&(~(round_to-1))) + round_to;
}

//Truncates "orig_size" to a multiple of "multiple" bytes. multiple must be power of two
template<class SizeType>
inline SizeType get_truncated_size_po2(SizeType orig_size, SizeType multiple)
{
   return (orig_size & (~(multiple-1)));
}

template <std::size_t OrigSize, std::size_t RoundTo>
struct ct_rounded_size
{
   BOOST_STATIC_ASSERT((RoundTo != 0));
   static const std::size_t intermediate_value = (OrigSize-1)/RoundTo+1;
   BOOST_STATIC_ASSERT(intermediate_value <= std::size_t(-1)/RoundTo);
   static const std::size_t value = intermediate_value*RoundTo;
};

// Gennaro Prota wrote this. Thanks!
template <std::size_t p, std::size_t n = 4>
struct ct_max_pow2_less
{
   static const std::size_t c = 2*n < p;

   static const std::size_t value =
         c ? (ct_max_pow2_less< c*p, 2*c*n>::value) : n;
};

template <>
struct ct_max_pow2_less<0, 0>
{
   static const std::size_t value = 0;
};

}  //namespace ipcdetail {

//!Trait class to detect if an index is a node
//!index. This allows more efficient operations
//!when deallocating named objects.
template <class Index>
struct is_node_index
{
   static const bool value = false;
};

//!Trait class to detect if an index is an intrusive
//!index. This will embed the derivation hook in each
//!allocation header, to provide memory for the intrusive
//!container.
template <class Index>
struct is_intrusive_index
{
   static const bool value = false;
};

template <typename T>
BOOST_INTERPROCESS_FORCEINLINE T* addressof(T& v)
{
  return reinterpret_cast<T*>(
       &const_cast<char&>(reinterpret_cast<const volatile char &>(v)));
}

template<class SizeType>
struct sqrt_size_type_max
{
   static const SizeType value = (SizeType(1) << (sizeof(SizeType)*(CHAR_BIT/2)))-1;
};

template<class SizeType>
inline bool multiplication_overflows(SizeType a, SizeType b)
{
   const SizeType sqrt_size_max = sqrt_size_type_max<SizeType>::value;
   return   //Fast runtime check
         (  (a | b) > sqrt_size_max &&
            //Slow division check
            b && a > SizeType(-1)/b
         );
}

template<std::size_t SztSizeOfType, class SizeType>
BOOST_INTERPROCESS_FORCEINLINE bool size_overflows(SizeType count)
{
   //Compile time-check
   BOOST_STATIC_ASSERT(SztSizeOfType <= SizeType(-1));
   //Runtime check
   return multiplication_overflows(SizeType(SztSizeOfType), count);
}

template<class RawPointer, class OffsetType>
class pointer_offset_caster;

template<class T, class OffsetType>
class pointer_offset_caster<T*, OffsetType>
{
   public:
   BOOST_INTERPROCESS_FORCEINLINE explicit pointer_offset_caster(OffsetType off)
      : m_offset(off)
   {}

   BOOST_INTERPROCESS_FORCEINLINE explicit pointer_offset_caster(const volatile T *p)
      : m_offset(reinterpret_cast<OffsetType>(p))
   {}

   BOOST_INTERPROCESS_FORCEINLINE OffsetType offset() const
   {   return m_offset;   }

   BOOST_INTERPROCESS_FORCEINLINE T* pointer() const
   {   return reinterpret_cast<T*>(m_offset);   }

   private:
   OffsetType m_offset;
};


template<class SizeType>
inline bool sum_overflows(SizeType a, SizeType b)
{  return SizeType(-1) - a < b;  }

//Anti-exception node eraser
template<class Cont>
class value_eraser
{
   public:
   value_eraser(Cont & cont, typename Cont::iterator it)
      : m_cont(cont), m_index_it(it), m_erase(true){}
   ~value_eraser()
   {  if(m_erase) m_cont.erase(m_index_it);  }

   BOOST_INTERPROCESS_FORCEINLINE void release() {  m_erase = false;  }

   private:
   Cont                   &m_cont;
   typename Cont::iterator m_index_it;
   bool                    m_erase;
};

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_UTILITIES_HPP


/* utilities.hpp
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
*/