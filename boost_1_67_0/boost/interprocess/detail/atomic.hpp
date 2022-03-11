//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2012
// (C) Copyright Markus Schoepflin 2007
// (C) Copyright Bryce Lelbach 2010
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_ATOMIC_HPP
#define BOOST_INTERPROCESS_DETAIL_ATOMIC_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/cstdint.hpp>

namespace boost{
namespace interprocess{
namespace ipcdetail{

//! Atomically increment an boost::uint32_t by 1
//! "mem": pointer to the object
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_inc32(volatile boost::uint32_t *mem);

//! Atomically read an boost::uint32_t from memory
inline boost::uint32_t atomic_read32(volatile boost::uint32_t *mem);

//! Atomically set an boost::uint32_t in memory
//! "mem": pointer to the object
//! "param": val value that the object will assume
inline void atomic_write32(volatile boost::uint32_t *mem, boost::uint32_t val);

//! Compare an boost::uint32_t's value with "cmp".
//! If they are the same swap the value with "with"
//! "mem": pointer to the value
//! "with": what to swap it with
//! "cmp": the value to compare it to
//! Returns the old value of *mem
inline boost::uint32_t atomic_cas32
   (volatile boost::uint32_t *mem, boost::uint32_t with, boost::uint32_t cmp);

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#if defined (BOOST_INTERPROCESS_WINDOWS)

#include <boost/interprocess/detail/win32_api.hpp>

#if defined( _MSC_VER )
   extern "C" void _ReadWriteBarrier(void);
   #pragma intrinsic(_ReadWriteBarrier)
   #define BOOST_INTERPROCESS_READ_WRITE_BARRIER _ReadWriteBarrier()
#elif defined(__GNUC__)
   #if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) > 40100
      #define BOOST_INTERPROCESS_READ_WRITE_BARRIER __sync_synchronize()
   #else
      #define BOOST_INTERPROCESS_READ_WRITE_BARRIER __asm__ __volatile__("" : : : "memory")
   #endif
#endif

namespace boost{
namespace interprocess{
namespace ipcdetail{

//! Atomically decrement an boost::uint32_t by 1
//! "mem": pointer to the atomic value
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_dec32(volatile boost::uint32_t *mem)
{  return winapi::interlocked_decrement(reinterpret_cast<volatile long*>(mem)) + 1;  }

//! Atomically increment an apr_uint32_t by 1
//! "mem": pointer to the object
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_inc32(volatile boost::uint32_t *mem)
{  return winapi::interlocked_increment(reinterpret_cast<volatile long*>(mem))-1;  }

//! Atomically read an boost::uint32_t from memory
inline boost::uint32_t atomic_read32(volatile boost::uint32_t *mem)
{
    const boost::uint32_t val = *mem;
    BOOST_INTERPROCESS_READ_WRITE_BARRIER;
    return val;
}

//! Atomically set an boost::uint32_t in memory
//! "mem": pointer to the object
//! "param": val value that the object will assume
inline void atomic_write32(volatile boost::uint32_t *mem, boost::uint32_t val)
{  winapi::interlocked_exchange(reinterpret_cast<volatile long*>(mem), val);  }

//! Compare an boost::uint32_t's value with "cmp".
//! If they are the same swap the value with "with"
//! "mem": pointer to the value
//! "with": what to swap it with
//! "cmp": the value to compare it to
//! Returns the old value of *mem
inline boost::uint32_t atomic_cas32
   (volatile boost::uint32_t *mem, boost::uint32_t with, boost::uint32_t cmp)
{  return winapi::interlocked_compare_exchange(reinterpret_cast<volatile long*>(mem), with, cmp);  }

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__)) && !defined(_CRAYC)

namespace boost {
namespace interprocess {
namespace ipcdetail{

//! Compare an boost::uint32_t's value with "cmp".
//! If they are the same swap the value with "with"
//! "mem": pointer to the value
//! "with" what to swap it with
//! "cmp": the value to compare it to
//! Returns the old value of *mem
inline boost::uint32_t atomic_cas32
   (volatile boost::uint32_t *mem, boost::uint32_t with, boost::uint32_t cmp)
{
   boost::uint32_t prev = cmp;
   // This version by Mans Rullgard of Pathscale
   __asm__ __volatile__ ( "lock\n\t"
                          "cmpxchg %2,%0"
                        : "+m"(*mem), "+a"(prev)
                        : "r"(with)
                        : "cc");

   return prev;
}

//! Atomically add 'val' to an boost::uint32_t
//! "mem": pointer to the object
//! "val": amount to add
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_add32
   (volatile boost::uint32_t *mem, boost::uint32_t val)
{
   // int r = *pw;
   // *mem += val;
   // return r;
   int r;

   asm volatile
   (
      "lock\n\t"
      "xadd %1, %0":
      "+m"( *mem ), "=r"( r ): // outputs (%0, %1)
      "1"( val ): // inputs (%2 == %1)
      "memory", "cc" // clobbers
   );

   return r;
}

//! Atomically increment an apr_uint32_t by 1
//! "mem": pointer to the object
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_inc32(volatile boost::uint32_t *mem)
{  return atomic_add32(mem, 1);  }

//! Atomically decrement an boost::uint32_t by 1
//! "mem": pointer to the atomic value
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_dec32(volatile boost::uint32_t *mem)
{  return atomic_add32(mem, (boost::uint32_t)-1);  }

//! Atomically read an boost::uint32_t from memory
inline boost::uint32_t atomic_read32(volatile boost::uint32_t *mem)
{
   const boost::uint32_t val = *mem;
   __asm__ __volatile__ ( "" ::: "memory" );
   return val;
}

//! Atomically set an boost::uint32_t in memory
//! "mem": pointer to the object
//! "param": val value that the object will assume
inline void atomic_write32(volatile boost::uint32_t *mem, boost::uint32_t val)
{
   __asm__ __volatile__
   (
      "xchgl %0, %1"
      : "+r" (val), "+m" (*mem)
      :: "memory"
   );
}

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#elif defined(__GNUC__) && (defined(__PPC__) || defined(__ppc__))

namespace boost {
namespace interprocess {
namespace ipcdetail{

//! Atomically add 'val' to an boost::uint32_t
//! "mem": pointer to the object
//! "val": amount to add
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_add32(volatile boost::uint32_t *mem, boost::uint32_t val)
{
   boost::uint32_t prev, temp;

   asm volatile ("1:\n\t"
                 "lwarx  %0,0,%2\n\t"
                 "add    %1,%0,%3\n\t"
                 "stwcx. %1,0,%2\n\t"
                 "bne-   1b"
                 : "=&r" (prev), "=&r" (temp)
                 : "b" (mem), "r" (val)
                 : "cc", "memory");
   return prev;
}

//! Compare an boost::uint32_t's value with "cmp".
//! If they are the same swap the value with "with"
//! "mem": pointer to the value
//! "with" what to swap it with
//! "cmp": the value to compare it to
//! Returns the old value of *mem
inline boost::uint32_t atomic_cas32
   (volatile boost::uint32_t *mem, boost::uint32_t with, boost::uint32_t cmp)
{
   boost::uint32_t prev;

   asm volatile ("1:\n\t"
                 "lwarx  %0,0,%1\n\t"
                 "cmpw   %0,%3\n\t"
                 "bne-   2f\n\t"
                 "stwcx. %2,0,%1\n\t"
                 "bne-   1b\n\t"
                 "2:"
                 : "=&r"(prev)
                 : "b" (mem), "r" (with), "r" (cmp)
                 : "cc", "memory");
   return prev;
}

//! Atomically increment an apr_uint32_t by 1
//! "mem": pointer to the object
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_inc32(volatile boost::uint32_t *mem)
{  return atomic_add32(mem, 1);  }

//! Atomically decrement an boost::uint32_t by 1
//! "mem": pointer to the atomic value
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_dec32(volatile boost::uint32_t *mem)
{  return atomic_add32(mem, boost::uint32_t(-1u));  }

//! Atomically read an boost::uint32_t from memory
inline boost::uint32_t atomic_read32(volatile boost::uint32_t *mem)
{
   const boost::uint32_t val = *mem;
   __asm__ __volatile__ ( "" ::: "memory" );
   return val;
}

//! Atomically set an boost::uint32_t in memory
//! "mem": pointer to the object
//! "param": val value that the object will assume
inline void atomic_write32(volatile boost::uint32_t *mem, boost::uint32_t val)
{  *mem = val; }

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#elif (defined(sun) || defined(__sun))

#include <atomic.h>

namespace boost{
namespace interprocess{
namespace ipcdetail{

//! Atomically add 'val' to an boost::uint32_t
//! "mem": pointer to the object
//! "val": amount to add
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_add32(volatile boost::uint32_t *mem, boost::uint32_t val)
{   return atomic_add_32_nv(reinterpret_cast<volatile ::uint32_t*>(mem), (int32_t)val) - val;   }

//! Compare an boost::uint32_t's value with "cmp".
//! If they are the same swap the value with "with"
//! "mem": pointer to the value
//! "with" what to swap it with
//! "cmp": the value to compare it to
//! Returns the old value of *mem
inline boost::uint32_t atomic_cas32
   (volatile boost::uint32_t *mem, boost::uint32_t with, boost::uint32_t cmp)
{  return atomic_cas_32(reinterpret_cast<volatile ::uint32_t*>(mem), cmp, with);  }

//! Atomically increment an apr_uint32_t by 1
//! "mem": pointer to the object
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_inc32(volatile boost::uint32_t *mem)
{  return atomic_add_32_nv(reinterpret_cast<volatile ::uint32_t*>(mem), 1) - 1; }

//! Atomically decrement an boost::uint32_t by 1
//! "mem": pointer to the atomic value
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_dec32(volatile boost::uint32_t *mem)
{  return atomic_add_32_nv(reinterpret_cast<volatile ::uint32_t*>(mem), (boost::uint32_t)-1) + 1; }

//! Atomically read an boost::uint32_t from memory
inline boost::uint32_t atomic_read32(volatile boost::uint32_t *mem)
{  return *mem;   }

//! Atomically set an boost::uint32_t in memory
//! "mem": pointer to the object
//! "param": val value that the object will assume
inline void atomic_write32(volatile boost::uint32_t *mem, boost::uint32_t val)
{  *mem = val; }

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#elif defined(__osf__) && defined(__DECCXX)

#include <machine/builtins.h>
#include <c_asm.h>

namespace boost{
namespace interprocess{
namespace ipcdetail{

//! Atomically decrement a uint32_t by 1
//! "mem": pointer to the atomic value
//! Returns the old value pointed to by mem
//! Acquire, memory barrier after decrement.
inline boost::uint32_t atomic_dec32(volatile boost::uint32_t *mem)
{  boost::uint32_t old_val = __ATOMIC_DECREMENT_LONG(mem); __MB(); return old_val; }

//! Atomically increment a uint32_t by 1
//! "mem": pointer to the object
//! Returns the old value pointed to by mem
//! Release, memory barrier before increment.
inline boost::uint32_t atomic_inc32(volatile boost::uint32_t *mem)
{  __MB(); return __ATOMIC_INCREMENT_LONG(mem); }

// Rational for the implementation of the atomic read and write functions.
//
// 1. The Alpha Architecture Handbook requires that access to a byte,
// an aligned word, an aligned longword, or an aligned quadword is
// atomic. (See 'Alpha Architecture Handbook', version 4, chapter 5.2.2.)
//
// 2. The CXX User's Guide states that volatile quantities are accessed
// with single assembler instructions, and that a compilation error
// occurs when declaring a quantity as volatile which is not properly
// aligned.

//! Atomically read an boost::uint32_t from memory
//! Acquire, memory barrier after load.
inline boost::uint32_t atomic_read32(volatile boost::uint32_t *mem)
{  boost::uint32_t old_val = *mem; __MB(); return old_val;  }

//! Atomically set an boost::uint32_t in memory
//! "mem": pointer to the object
//! "param": val value that the object will assume
//! Release, memory barrier before store.
inline void atomic_write32(volatile boost::uint32_t *mem, boost::uint32_t val)
{  __MB(); *mem = val; }

//! Compare an boost::uint32_t's value with "cmp".
//! If they are the same swap the value with "with"
//! "mem": pointer to the value
//! "with" what to swap it with
//! "cmp": the value to compare it to
//! Returns the old value of *mem
//! Memory barrier between load and store.
inline boost::uint32_t atomic_cas32(
  volatile boost::uint32_t *mem, boost::uint32_t with, boost::uint32_t cmp)
{
  // Note:
  //
  // Branch prediction prefers backward branches, and the Alpha Architecture
  // Handbook explicitely states that the loop should not be implemented like
  // it is below. (See chapter 4.2.5.) Therefore the code should probably look
  // like this:
  //
  // return asm(
  //   "10: ldl_l %v0,(%a0) ;"
  //   "    cmpeq %v0,%a2,%t0 ;"
  //   "    beq %t0,20f ;"
  //   "    mb ;"
  //   "    mov %a1,%t0 ;"
  //   "    stl_c %t0,(%a0) ;"
  //   "    beq %t0,30f ;"
  //   "20: ret ;"
  //   "30: br 10b;",
  //   mem, with, cmp);
  //
  // But as the compiler always transforms this into the form where a backward
  // branch is taken on failure, we can as well implement it in the straight
  // forward form, as this is what it will end up in anyway.

  return asm(
    "10: ldl_l %v0,(%a0) ;"    // load prev value from mem and lock mem
    "    cmpeq %v0,%a2,%t0 ;"  // compare with given value
    "    beq %t0,20f ;"        // if not equal, we're done
    "    mb ;"                 // memory barrier
    "    mov %a1,%t0 ;"        // load new value into scratch register
    "    stl_c %t0,(%a0) ;"    // store new value to locked mem (overwriting scratch)
    "    beq %t0,10b ;"        // store failed because lock has been stolen, retry
    "20: ",
    mem, with, cmp);
}

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#elif defined(__IBMCPP__) && (__IBMCPP__ >= 800) && defined(_AIX)

#include <builtins.h>

namespace boost {
namespace interprocess {
namespace ipcdetail{

//first define boost::uint32_t versions of __lwarx and __stwcx to avoid poluting
//all the functions with casts

//! From XLC documenation :
//! This function can be used with a subsequent stwcxu call to implement a
//! read-modify-write on a specified memory location. The two functions work
//! together to ensure that if the store is successfully performed, no other
//! processor or mechanism can modify the target doubleword between the time
//! lwarxu function is executed and the time the stwcxu functio ncompletes.
//! "mem" : pointer to the object
//! Returns the value at pointed to by mem
inline boost::uint32_t lwarxu(volatile boost::uint32_t *mem)
{
   return static_cast<boost::uint32_t>(__lwarx(reinterpret_cast<volatile int*>(mem)));
}

//! "mem" : pointer to the object
//! "val" : the value to store
//! Returns true if the update of mem is successful and false if it is
//!unsuccessful
inline bool stwcxu(volatile boost::uint32_t* mem, boost::uint32_t val)
{
   return (__stwcx(reinterpret_cast<volatile int*>(mem), static_cast<int>(val)) != 0);
}

//! "mem": pointer to the object
//! "val": amount to add
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_add32
   (volatile boost::uint32_t *mem, boost::uint32_t val)
{
   boost::uint32_t oldValue;
   do
   {
      oldValue = lwarxu(mem);
   }while (!stwcxu(mem, oldValue+val));
   return oldValue;
}

//! Atomically increment an apr_uint32_t by 1
//! "mem": pointer to the object
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_inc32(volatile boost::uint32_t *mem)
{  return atomic_add32(mem, 1);  }

//! Atomically decrement an boost::uint32_t by 1
//! "mem": pointer to the atomic value
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_dec32(volatile boost::uint32_t *mem)
{  return atomic_add32(mem, (boost::uint32_t)-1);   }

//! Atomically read an boost::uint32_t from memory
inline boost::uint32_t atomic_read32(volatile boost::uint32_t *mem)
{  return *mem;   }

//! Compare an boost::uint32_t's value with "cmp".
//! If they are the same swap the value with "with"
//! "mem": pointer to the value
//! "with" what to swap it with
//! "cmp": the value to compare it to
//! Returns the old value of *mem
inline boost::uint32_t atomic_cas32
   (volatile boost::uint32_t *mem, boost::uint32_t with, boost::uint32_t cmp)
{
   boost::uint32_t oldValue;
   boost::uint32_t valueToStore;
   do
   {
      oldValue = lwarxu(mem);
   } while (!stwcxu(mem, (oldValue == with) ? cmp : oldValue));

   return oldValue;
}

//! Atomically set an boost::uint32_t in memory
//! "mem": pointer to the object
//! "param": val value that the object will assume
inline void atomic_write32(volatile boost::uint32_t *mem, boost::uint32_t val)
{  *mem = val; }

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#elif defined(__GNUC__) && ( __GNUC__ * 100 + __GNUC_MINOR__ >= 401 )

namespace boost {
namespace interprocess {
namespace ipcdetail{

//! Atomically add 'val' to an boost::uint32_t
//! "mem": pointer to the object
//! "val": amount to add
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_add32
   (volatile boost::uint32_t *mem, boost::uint32_t val)
{  return __sync_fetch_and_add(const_cast<boost::uint32_t *>(mem), val);   }

//! Atomically increment an apr_uint32_t by 1
//! "mem": pointer to the object
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_inc32(volatile boost::uint32_t *mem)
{  return atomic_add32(mem, 1);  }

//! Atomically decrement an boost::uint32_t by 1
//! "mem": pointer to the atomic value
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_dec32(volatile boost::uint32_t *mem)
{  return atomic_add32(mem, (boost::uint32_t)-1);   }

//! Atomically read an boost::uint32_t from memory
inline boost::uint32_t atomic_read32(volatile boost::uint32_t *mem)
{  boost::uint32_t old_val = *mem; __sync_synchronize(); return old_val;  }

//! Compare an boost::uint32_t's value with "cmp".
//! If they are the same swap the value with "with"
//! "mem": pointer to the value
//! "with" what to swap it with
//! "cmp": the value to compare it to
//! Returns the old value of *mem
inline boost::uint32_t atomic_cas32
   (volatile boost::uint32_t *mem, boost::uint32_t with, boost::uint32_t cmp)
{  return __sync_val_compare_and_swap(const_cast<boost::uint32_t *>(mem), cmp, with);   }

//! Atomically set an boost::uint32_t in memory
//! "mem": pointer to the object
//! "param": val value that the object will assume
inline void atomic_write32(volatile boost::uint32_t *mem, boost::uint32_t val)
{  __sync_synchronize(); *mem = val;  }

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{
#elif defined(__VXWORKS__)

#include <vxAtomicLib.h>
// VxWorks atomic32_t is not volatile, for some unknown reason
#define vx_atomic_cast(_i)   (reinterpret_cast< ::atomic32_t *>( const_cast<boost::uint32_t *>(_i)))

namespace boost {
namespace interprocess {
namespace ipcdetail{

//! Atomically add 'val' to an boost::uint32_t
//! "mem": pointer to the object
//! "val": amount to add
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_add32
   (volatile boost::uint32_t *mem, boost::uint32_t val)
{  return ::vxAtomic32Add( vx_atomic_cast(mem), val);   }

//! Atomically increment an apr_uint32_t by 1
//! "mem": pointer to the object
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_inc32(volatile boost::uint32_t *mem)
{  return ::vxAtomic32Inc( vx_atomic_cast(mem) );  }

//! Atomically decrement an boost::uint32_t by 1
//! "mem": pointer to the atomic value
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_dec32(volatile boost::uint32_t *mem)
{  return ::vxAtomic32Dec( vx_atomic_cast(mem) );   }

//! Atomically read an boost::uint32_t from memory
inline boost::uint32_t atomic_read32(volatile boost::uint32_t *mem)
{  return ::vxAtomic32Get( vx_atomic_cast(mem) );  }

//! Compare an boost::uint32_t's value with "cmp".
//! If they are the same swap the value with "with"
//! "mem": pointer to the value
//! "with" what to swap it with
//! "cmp": the value to compare it to
//! Returns the old value of *mem
inline boost::uint32_t atomic_cas32
   (volatile boost::uint32_t *mem, boost::uint32_t with, boost::uint32_t cmp)
{  return ::vxAtomic32Cas( vx_atomic_cast(mem), cmp, with);  }

//! Atomically set an boost::uint32_t in memory
//! "mem": pointer to the object
//! "param": val value that the object will assume
inline void atomic_write32(volatile boost::uint32_t *mem, boost::uint32_t val)
{  ::vxAtomic32Set( vx_atomic_cast(mem), val);  }


}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#else

#error No atomic operations implemented for this platform, sorry!

#endif

namespace boost{
namespace interprocess{
namespace ipcdetail{

inline bool atomic_add_unless32
   (volatile boost::uint32_t *mem, boost::uint32_t value, boost::uint32_t unless_this)
{
   boost::uint32_t old, c(atomic_read32(mem));
   while(c != unless_this && (old = atomic_cas32(mem, c + value, c)) != c){
      c = old;
   }
   return c != unless_this;
}

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost


#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_ATOMIC_HPP

/* atomic.hpp
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
*/