//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_XSI_SHARED_MEMORY_HPP
#define BOOST_INTERPROCESS_XSI_SHARED_MEMORY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#if !defined(BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS)
#error "This header can't be used in operating systems without XSI (System V) shared memory support"
#endif

#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/utilities.hpp>

#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/xsi_key.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/simple_swap.hpp>
// move
#include <boost/move/utility_core.hpp>
// other boost
#include <boost/cstdint.hpp>
// std
#include <cstddef>
// OS
#include <sys/shm.h>


//!\file
//!Describes a class representing a native xsi shared memory.

namespace boost {
namespace interprocess {

//!A class that wraps XSI (System V) shared memory.
//!Unlike shared_memory_object, xsi_shared_memory needs a valid
//!xsi_key to identify a shared memory object.
//!
//!Warning: XSI shared memory and interprocess portable
//!shared memory (boost::interprocess::shared_memory_object)
//!can't communicate between them.
class xsi_shared_memory
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable and non-assignable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(xsi_shared_memory)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Default constructor.
   //!Represents an empty xsi_shared_memory.
   xsi_shared_memory();

   //!Initializes *this with a shmid previously obtained (possibly from another process)
   //!This lower-level initializer allows shared memory mapping without having a key.
   xsi_shared_memory(open_only_t, int shmid)
      : m_shmid (shmid)
   {}

   //!Creates a new XSI shared memory from 'key', with size "size" and permissions "perm".
   //!If the shared memory previously exists, throws an error.
   xsi_shared_memory(create_only_t, const xsi_key &key, std::size_t size, const permissions& perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoCreate, key, perm, size);  }

   //!Opens an existing shared memory with identifier 'key' or creates a new XSI shared memory from
   //!identifier 'key', with size "size" and permissions "perm".
   xsi_shared_memory(open_or_create_t, const xsi_key &key, std::size_t size, const permissions& perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoOpenOrCreate, key, perm, size);  }

   //!Tries to open a XSI shared memory with identifier 'key'
   //!If the shared memory does not previously exist, it throws an error.
   xsi_shared_memory(open_only_t, const xsi_key &key)
   {  this->priv_open_or_create(ipcdetail::DoOpen, key, permissions(), 0);  }

   //!Moves the ownership of "moved"'s shared memory object to *this.
   //!After the call, "moved" does not represent any shared memory object.
   //!Does not throw
   xsi_shared_memory(BOOST_RV_REF(xsi_shared_memory) moved)
      : m_shmid(-1)
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s shared memory to *this.
   //!After the call, "moved" does not represent any shared memory.
   //!Does not throw
   xsi_shared_memory &operator=(BOOST_RV_REF(xsi_shared_memory) moved)
   {
      xsi_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps two xsi_shared_memorys. Does not throw
   void swap(xsi_shared_memory &other);

   //!Destroys *this. The shared memory won't be destroyed, just
   //!this connection to it. Use remove() to destroy the shared memory.
   ~xsi_shared_memory();

   //!Returns the shared memory ID that
   //!identifies the shared memory
   int get_shmid() const;

   //!Returns the mapping handle.
   //!Never throws
   mapping_handle_t get_mapping_handle() const;

   //!Erases the XSI shared memory object identified by shmid
   //!from the system.
   //!Returns false on error. Never throws
   static bool remove(int shmid);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   //!Closes a previously opened file mapping. Never throws.
   bool priv_open_or_create( ipcdetail::create_enum_t type
                           , const xsi_key &key
                           , const permissions& perm
                           , std::size_t size);
   int            m_shmid;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline xsi_shared_memory::xsi_shared_memory()
   :  m_shmid(-1)
{}

inline xsi_shared_memory::~xsi_shared_memory()
{}

inline int xsi_shared_memory::get_shmid() const
{  return m_shmid; }

inline void xsi_shared_memory::swap(xsi_shared_memory &other)
{
   (simple_swap)(m_shmid, other.m_shmid);
}

inline mapping_handle_t xsi_shared_memory::get_mapping_handle() const
{  mapping_handle_t mhnd = { m_shmid, true};   return mhnd;   }

inline bool xsi_shared_memory::priv_open_or_create
   (ipcdetail::create_enum_t type, const xsi_key &key, const permissions& permissions, std::size_t size)
{
   int perm = permissions.get_permissions();
   perm &= 0x01FF;
   int shmflg = perm;

   switch(type){
      case ipcdetail::DoOpen:
         shmflg |= 0;
      break;
      case ipcdetail::DoCreate:
         shmflg |= IPC_CREAT | IPC_EXCL;
      break;
      case ipcdetail::DoOpenOrCreate:
         shmflg |= IPC_CREAT;
      break;
      default:
         {
            error_info err = other_error;
            throw interprocess_exception(err);
         }
   }

   int ret = ::shmget(key.get_key(), size, shmflg);
   int shmid = ret;
   if((type == ipcdetail::DoOpen) && (-1 != ret)){
      //Now get the size
      ::shmid_ds xsi_ds;
      ret = ::shmctl(ret, IPC_STAT, &xsi_ds);
      size = xsi_ds.shm_segsz;
   }
   if(-1 == ret){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }

   m_shmid = shmid;
   return true;
}

inline bool xsi_shared_memory::remove(int shmid)
{  return -1 != ::shmctl(shmid, IPC_RMID, 0); }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_XSI_SHARED_MEMORY_HPP

/* xsi_shared_memory.hpp
4WXYh9O3vZUZgBfg66Gs+98ALyE/DV6Dr4TVt7uVeQ9sgSdgJ3we7IMvEjsDRyH+APMW6SK/Fp6Hb4OL6N8OV5HfC6/DZ8Ga29/KTMI2+GzYDV8KB+A7oNwHeTecQH4+PAVH4Fk4C/EPeJ6AfCO/VfZHfg6U5yhm4FX04zCauhXPT3A++CY5H5yGPfAglHX/c2EG+Y2Q5x5Y3yPD18n50b8KnoSvhnPwNXJe+Ba4AV8u6dfdyrwCtsNDcD+cg/LcwZthFvmdUl/wqXAWnoJn4GG4Ap8Or8AJyfcdbsV6hHqHL5D6gc+QdOBxSQc+U+obvkvaER6Ba3e41f+UXfx3hux3dpjmT1ZzDYlryt/bbi613cqsPB7/C132Xrcy+3+y3bTfU8vP9eM2gx771LbrXqofYP6Q/jMI96A/APs13hUcm3zykfh7D8BXu5djnrtP3dJeUzTmr11jP+L9kzvkPkp8DHK++AmIHYhPQ+xcfAFit+JnIfYpfgEWznEAg3kJeRBemdzx99uvP7az5aV2eju7IOnt7IfkY+cY5Pw7T0LOv3MOYkd2noPYkZ0rEHu78wrEPuyMvAymynfWQOzzzl0Q+7uzC2J3d/ZB7MzOiZdpvgaZt+W5qgNwGv3T4Bx8OlyCT4Wr8CC8BidgzfQOMwQ74DDshRk4Bo/AKfgceAoehfJc0CQ8jTwCz8MsXIejMP7yHSYHG+AxuAceh2c57hmwH/mZkj58luQTPgXOw3FIPWN3yO/L/4H6/mfDenli/PWSbjxxAuIfJWYg/lFiDjKPJM5A5pXEBcg8kliDXKdMRE5J+8UTccj1zEQN5LpTYhfEjic6IPcNEt2Q62SJPsg8mMhA5rvEOKT9E1OQfpKYgfSTxDyknyTOQfpJYgXSXxNXIP0kcR3STxIVb7D7SaIZ0j8SbTbjiS5bH0/0Q9YDiQnI/JWYtfXliUVhhPJA5unEJWGKckHm1cQGpN8lzBvt/pVohsxjiS7oGpeJfuRBKPPSATiOfBBOwTE4C4fgaXgMnofH4WX4LLgBczD+Jtob7oLjsBtOwmnn/zSJDPLT4An4dDgPnw3PwWG4Ag/BVXgYrsMMjMzZ/ZUL1fRr2AKfAffAEbgfZuEAfA4cg0+GYt9H4UnkZ8KFuf9Av/tHw3Ssvvq03d71DZB2rm+H9IP6PZD2rx+AtE/9JMQu1M9B7EH9WUj71a9A+nf9FUg711+HtG999Xtse1HfAlk/1XdC+nl9L6R/1Gcg/aN+GtLP689A1pH1q5B+Vb8BGSf18ffa46S+QbhKOpD+X78fMk7qh6Cr39RPID8VzsBBaN+PhlPwIFxEPw6X4BC8Aodh9H20M2yGh2E7zMA98AjcD4/CMTgi6cEnw3k4Cs/BHFyGY3AdHoNmkX4Jd8GnwO7F/2B7T8brOj5m24W6/ZD6r5uEjO+6OYg9qDtn62N1y5B6rbsKsQt10Y/b9VpXA7EfdW0QO1HXC2mvugFIO9eNQ/pN3UnhIulC2r3uDKQd685D2qXuMqQf1G1A7Fdd9Jz0m/K6aoidqNsFad+6LluO1fVD+l/dGKSd607aJH1hJ+lD+kvdeYgdrVuF2JO66xC7V1fzCbuf1bVB+mtdzye0no/hl8o8NQ3l/3pjsJ/443ACzkJ5fvcp8BwcFBn9q+AifDVchuMw8kn6F6yFL4Pt8PWwFz4N8vws60Jk+Do4hj4HZ+HT4RJ8KZTnXofgZeQJGP/UDvNa2AxfLunAZ0HmP/on+78cuwWZ11iPoyd+RtKHz4br6A/BeeTD8DzMwFV4BEaX6L+SbzgC22AWyvOuT4Y9yKNwaOk/2D//wbB4yDI9I5ZJwXW2LL+n2SSu7y4=
*/