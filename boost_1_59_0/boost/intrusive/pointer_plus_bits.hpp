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

#ifndef BOOST_INTRUSIVE_POINTER_PLUS_BITS_HPP
#define BOOST_INTRUSIVE_POINTER_PLUS_BITS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/mpl.hpp> //ls_zeros
#include <boost/intrusive/detail/assert.hpp> //BOOST_INTRUSIVE_INVARIANT_ASSERT

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif


//GCC reports uninitialized values when an uninitialized pointer plus bits type
//is asigned some bits or some pointer value, but that's ok, because we don't want
//to default initialize parts that are not being updated.
#if defined(BOOST_GCC)
#  if (BOOST_GCC >= 40600)
#     pragma GCC diagnostic push
#     pragma GCC diagnostic ignored "-Wuninitialized"
#     if (BOOST_GCC >= 40700)
#        pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#     endif
#  endif
#endif

namespace boost {
namespace intrusive {

//!This trait class is used to know if a pointer
//!can embed extra bits of information if
//!it's going to be used to point to objects
//!with an alignment of "Alignment" bytes.
template<class VoidPointer, std::size_t Alignment>
struct max_pointer_plus_bits
{
   static const std::size_t value = 0;
};

//!This is a specialization for raw pointers.
//!Raw pointers can embed extra bits in the lower bits
//!if the alignment is multiple of 2pow(NumBits).
template<std::size_t Alignment>
struct max_pointer_plus_bits<void*, Alignment>
{
   static const std::size_t value = detail::ls_zeros<Alignment>::value;
};

//!This is class that is supposed to have static methods
//!to embed extra bits of information in a pointer.
//!This is a declaration and there is no default implementation,
//!because operations to embed the bits change with every pointer type.
//!
//!An implementation that detects that a pointer type whose
//!has_pointer_plus_bits<>::value is non-zero can make use of these
//!operations to embed the bits in the pointer.
template<class Pointer, std::size_t NumBits>
struct pointer_plus_bits
   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   {}
   #endif
;

//!This is the specialization to embed extra bits of information
//!in a raw pointer. The extra bits are stored in the lower bits of the pointer.
template<class T, std::size_t NumBits>
struct pointer_plus_bits<T*, NumBits>
{
   static const uintptr_t Mask = uintptr_t((uintptr_t(1u) << NumBits) - 1);
   typedef T*        pointer;

   BOOST_INTRUSIVE_FORCEINLINE static pointer get_pointer(pointer n) BOOST_NOEXCEPT
   {  return pointer(uintptr_t(n) & uintptr_t(~Mask));  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_pointer(pointer &n, pointer p) BOOST_NOEXCEPT
   {
      BOOST_INTRUSIVE_INVARIANT_ASSERT(0 == (uintptr_t(p) & Mask));
      n = pointer(uintptr_t(p) | (uintptr_t(n) & Mask));
   }

   BOOST_INTRUSIVE_FORCEINLINE static std::size_t get_bits(pointer n) BOOST_NOEXCEPT
   {  return std::size_t(uintptr_t(n) & Mask);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_bits(pointer &n, std::size_t c) BOOST_NOEXCEPT
   {
      BOOST_INTRUSIVE_INVARIANT_ASSERT(uintptr_t(c) <= Mask);
      n = pointer(uintptr_t((get_pointer)(n)) | uintptr_t(c));
   }
};

} //namespace intrusive
} //namespace boost

#if defined(BOOST_GCC) && (BOOST_GCC >= 40600)
#  pragma GCC diagnostic pop
#endif

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_POINTER_PLUS_BITS_HPP

/* pointer_plus_bits.hpp
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
*/