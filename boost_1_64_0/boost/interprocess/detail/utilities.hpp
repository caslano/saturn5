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
template <int p, int n = 4>
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
   BOOST_INTERPROCESS_FORCEINLINE explicit pointer_offset_caster(OffsetType offset)
      : m_offset(offset)
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
OBt4FFgIPA28EtjcRPmrfACzVPmZ7D8DOAd4FXAucBEwH3gNsAC4jPg4PxOtO/kQh5RrBNkF+W8e+KJU3Qb4aPv5AR5/FgEvBV4l5btAym8hcJr4y7gs99ehT1D89nH5hMn19q3J7zmp+inwe2AH4A/AbOBpk+vjH9LukhHhNon3I5HHzUBxpuzh8BoVycDDQDVuf+jldB7xcn1/ArwC+ClwKfAocIUKj3HodmXLwvNG4DHgH4FfAv8k/u8rnQ3P3yv7CfBCvPMb4HDgCWCGyXyZwJN4LgF+r+IDngLeBfwBeB/wDPBV4E/AT4E/A48BzwK/BpqI50dgAHgH8hkFvAdYB/gAMAK4HRgLfA7YAPgnL79f9Be53wltiMrfrr80Ah+tZcr43Bioxv8mPu4HScBZwAskPkQk9w2RDEV88FP1JvF1x3gZrfoRsIEa14GqXvoAU4B9gV1UfwKmqrHez/XR38/9I83P9T0IOEfJB+AylQ8/189Q4DolH/xcP8P9PE6OAD4HHOnncXIU8HPVH/3cX8YAz6h+CYxV4wUwHni50ieAVwAvAk4E9gFOAfYHTvVzvU4DTgRe6dfyiO+6wfq6izyKAJ/yq+tnvTAK2ESVq+gv9dT7gPWlPGL8LAcb+lkuxQGnABOAhap+gNeq+pH8N5F07DLkXhUVp4fTQXepSDp+6+f+eiewn7Lb+rkfPAEcD7wXmAm8D1gM3AI8AnzAz/LmQSmnPwA7AR+hcuFwo0wONwl4P3CqyfHONTmed1QfVXqVuH8FvAv4szxLOcodFTSGO8rxH37Wp38WPS8ecuVpVR7AN5QcCHA9m8DvgB7gD0AfMKDmEsC6qv8AGwHrBLi+I9X4Y3J46SdynwF0QZd+ckbk1M9ApY+eBcaz4bGirXq/6OUej5arfIcA2rqLXG0h42LLALePiwLcX1oDVX9qE2A52FbGyXYB1psvDpGrxRL/cBe5+leUl0fJJ2CCkrN+1ku/9fO4dBI4SMlZ4DDgKamPg4ok3k7SnhqFzFV3g68V8GngAOCzftZrnwfeqviAdwBfBN4NfEn061f8PJ79CajifBX4JvA14KfqnX7WW99S6cTL3wGmA98FFgMP+VmOvu9nPfMvwMeBh4EfAz+Q9vWZtK/PgT4P5Ljka61HzpWmM7I5X6NByz1yn7mH29liD+sH13h43L/Ww+PyEuAm1Ta9PD4vw/N+Dl+hyuwGD+vfKz3czm4EDgDeBBwCXA0cCVwDzDcpPRXzgLcBb1LtHng78I/AO4H7gY8CXwY+DTwAfB74Z+CLwIPA94GvAz8Bvunh/L8FPKlspMCfVDl6WC9+F3gp8ENgX+BHwGHAI8BZwE+Ac4GfqnzLc5k8XyXPV8tzlBfl62H98UvgaODXwBnAb1S+gH8HXgP8DrgE+D1wOfCQyi/wPeCvgO8DNwL/AtwCPAx8GPgD8FngaeAbwH+q/AHXA78HbgBiDDR+C2wM/J3qf8DfAzsD7wL2B94NHAq8FzgWeB/wCuAWlW/gH1R6gduA1wMfA96sbB2qvoE7gY8BnwQ+A9wDfAX4NPDPwAeAbwEfBB4B1kX7gMw3zuK5KdDAc3OgCWwD9AI7+bkd/Z3tAnKOKcZOkX/1yK7Af9/4uN9+B1RyySdy/JSP9ZcffDxOnAZer+Ql8EbhW2+QXbPiIeBPwLeV3AL+rCKWcdAk+c78Mr7LOY90hqZjfJ8u6cn28XiVI+nI9fE4MtPH4zbKlsaTFcAlwNnA+4B5Ph6f5wDfEP+PgfnAfwALfDxfLfSxXaMI2MFkvt7AecCxwBIfj8elwAJgGXAhcD5wE/AqpR8BFwAfofA8v7wauA+4GPiuso8BPwM=
*/