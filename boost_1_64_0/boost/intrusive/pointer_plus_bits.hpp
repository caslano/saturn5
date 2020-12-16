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

   BOOST_INTRUSIVE_FORCEINLINE static pointer get_pointer(pointer n)
   {  return pointer(uintptr_t(n) & uintptr_t(~Mask));  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_pointer(pointer &n, pointer p)
   {
      BOOST_INTRUSIVE_INVARIANT_ASSERT(0 == (uintptr_t(p) & Mask));
      n = pointer(uintptr_t(p) | (uintptr_t(n) & Mask));
   }

   BOOST_INTRUSIVE_FORCEINLINE static std::size_t get_bits(pointer n)
   {  return std::size_t(uintptr_t(n) & Mask);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_bits(pointer &n, std::size_t c)
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
7YR/PJpe/9Tv9xT0Od505w+sv6+pzAtPjmq8Nnmr/6KAI846Zx95Wn9OgXlJ72ENpre8a/lzYT3uqlb8r68djn/6KPPwF+YsP9804dklOYN2LH7miSPsMRKozLeNuiXhdJW7Hpq7pXbxkYfvPsA8q5cyv7lRq4hddfN3/Dpr99I3b/9hOHnpVObDdm8Z+snvjw38buu9a/y3XX4/PWmGMvfbkN8s4Rq/Pq/7XtN8y8zhxPHeKsr80Y0P9Vng4/2v3uO6bp36Wdcx5K02P7084r62B6aen//D5qdv29zoMcY3OvyMoimLfypp8eo791zTIPJkN+Y1a2v3u1fcvDJy+Z7xn9b9bftPLRtHs4LDV5nXCUwZ+Oa1p6e0vnz17XNmbf2JMtT5ufCR+9794mBU1PyDI3LS7nz4NO8pdLp6RqSevTVxQhvvGRMC5nyV+g5zxdr8/btPvto7NW3j/B9vGftkk0cJe6OfMo+Keij+y7f/GTb82OwGwzc0OMRYTKf3oSer7G1x1V2/dr7fb9uo+HW8fxk8UZmPnrD2raBNI7+c81PiuUUNE3jfP7eqMj9/4kW/tXPn5/X/4OyYtBsuL2athjbvN3Rc+MmEM5HVMhoUz+t8jvQW6/Re9t64gPSbBi/4uNrijGat4h5gTVJVfd3V44fv8vnmo2cfbP77uvylrOc8os1fDqy9Lyk6+qWrfdt0v7lh3/rks46/14NpTZrNPds9/Fx4rdCnxtJubtD14Zbg1S++eHP4yKJNk54qbnVDF/bx0vm5s2fsmfNXdHln1VefHhznHMdze3+dn9nht/80/9p1oxe1vn5DUHS1z7nf6HDenv3Oq7//tOLMrGWN6u5cfgNxX+itzDdd94pP9cX/fLzJrveatNww6GrWVKv7gtOh/25Q+5fCul7G/HoBHIP+D8vvASHu3/fL788c1E+Lm+8tv3+0/G6L+wgn90a195Pl91hLmCnu3/obuzD4EBJr+b23tnbDyiLyx/J7XQhpgZNJ7wRLOOMtvzdZ4vyA5fdjEv4RZLvldyJuColnJ/X9nOX3GLlWFnKj/N6ATJXfTyDz5fdDXONO+T2Qcpguv+/ld7z8vp76MlJ+j+V3jvw+VQ138vsLf/o7+d0lgLOI5PfGQPpZWEzcYsKM/qyeN3Zy3uBRKd/8qo7cALgWtlTxhT3ggzARboYzVXzhbPgLvBVugXfCR6HK/63wUbHfpvILPqfyEH4AH4cfif0ncAf8Hj4JA4nLThjkNOxrw6dgV7gHDodPw+vFfjTcB8fAZ+EcuB/mw5fgdvgyPAAPw0/h27AEHoU/w3dhgJdhXg9+CBvDj2Az0VuKHg0/gVfBz2Ec/ALeCL9U8YCn4DRxPx+WwE3wR/gwVPHeAr+Cu+BZ+Cr8Gb4Nz8Fj4u443Ah/ggXwFzH/J1wHa3vTx8O6UJlTzrqNRjQwyjnTYZRzTWSha+Oaao5cLzgYVoexUO+dBMPhMNgYxsEW8FoYBYfDrjAe9oTXwf5wJBwq+giYANPgKHgzHA1VvGKQQolXM4mXLxIt8XqIT52V3cOwmqpPUMV7K2wKt0EVjopLsYTjJ+F4S5h6lxWupzgVVoXToMtfiUd/kPAVL4fKX3PL9RyXefbXWfx1EX9dLf6CKvAXJf46iL+OFn8RFfj7TNJ3UtL3uZk+pAJ/V8j1rpTr9bBcL6YCf4fleq/J9Y5YrhdXgb9M8Zcl/rLFXzckWfyFij8fJFL8tZJ4toYBsC0MVPaW+OZWcN0dct0n5bo7LfHNq8DfdvH3mPh73OKvoAJ/94u/DeJvo8VfYQX+nhJ/u8XfHou//RX4e0D8PSj+Nlv8FVXg72Xx94r4O2jxV1w=
*/