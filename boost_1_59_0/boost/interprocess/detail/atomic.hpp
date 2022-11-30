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

#if !defined(_AIX)
#define BOOST_INTERPROCESS_DETAIL_PPC_ASM_LABEL(label) label ":\n\t"
#define BOOST_INTERPROCESS_DETAIL_PPC_ASM_JUMP(insn, label, offset) insn " " label "\n\t"
#else
#define BOOST_INTERPROCESS_DETAIL_PPC_ASM_LABEL(label)
#define BOOST_INTERPROCESS_DETAIL_PPC_ASM_JUMP(insn, label, offset) insn " $" offset "\n\t"
#endif

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

#define BOOST_INTERPROCESS_READ_WRITE_BARRIER \
            BOOST_INTERPROCESS_DISABLE_DEPRECATED_WARNING \
            _ReadWriteBarrier() \
            BOOST_INTERPROCESS_RESTORE_WARNING

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
{  return (boost::uint32_t)winapi::interlocked_decrement(reinterpret_cast<volatile long*>(mem)) + 1;  }

//! Atomically increment an apr_uint32_t by 1
//! "mem": pointer to the object
//! Returns the old value pointed to by mem
inline boost::uint32_t atomic_inc32(volatile boost::uint32_t *mem)
{  return (boost::uint32_t)winapi::interlocked_increment(reinterpret_cast<volatile long*>(mem))-1;  }

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
{  winapi::interlocked_exchange(reinterpret_cast<volatile long*>(mem), (long)val);  }

//! Compare an boost::uint32_t's value with "cmp".
//! If they are the same swap the value with "with"
//! "mem": pointer to the value
//! "with": what to swap it with
//! "cmp": the value to compare it to
//! Returns the old value of *mem
inline boost::uint32_t atomic_cas32
   (volatile boost::uint32_t *mem, boost::uint32_t with, boost::uint32_t cmp)
{  return (boost::uint32_t)winapi::interlocked_compare_exchange(reinterpret_cast<volatile long*>(mem), (long)with, (long)cmp);  }

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
   boost::uint32_t r;

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

   asm volatile
     (
         BOOST_INTERPROCESS_DETAIL_PPC_ASM_LABEL("1")
         "lwarx  %0,0,%2\n\t"
         "add    %1,%0,%3\n\t"
         "stwcx. %1,0,%2\n\t"
         BOOST_INTERPROCESS_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
         : "=&r" (prev), "=&r" (temp)
         : "b" (mem), "r" (val)
         : "cc", "memory"
      );
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

   asm volatile
     (
         BOOST_INTERPROCESS_DETAIL_PPC_ASM_LABEL("1")
         "lwarx  %0,0,%1\n\t"
         "cmpw   %0,%3\n\t"
         BOOST_INTERPROCESS_DETAIL_PPC_ASM_JUMP("bne-", "2f", "+12")
         "stwcx. %2,0,%1\n\t"
         BOOST_INTERPROCESS_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-16")
         BOOST_INTERPROCESS_DETAIL_PPC_ASM_LABEL("2")
         : "=&r"(prev)
	 : "b" (mem), "r" (with), "r" (cmp)
	 : "cc", "memory"
      );
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