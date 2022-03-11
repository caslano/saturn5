//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
// Parts of this code are taken from boost::filesystem library
//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2002 Beman Dawes
//  Copyright (C) 2001 Dietmar Kuehl
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
//  at http://www.boost.org/LICENSE_1_0.txt)
//
//  See library home page at http://www.boost.org/libs/filesystem
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BOOST_INTERPROCESS_ERRORS_HPP
#define BOOST_INTERPROCESS_ERRORS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <stdarg.h>
#include <string>

#if defined (BOOST_INTERPROCESS_WINDOWS)
#  include <boost/interprocess/detail/win32_api.hpp>
#else
#  ifdef BOOST_HAS_UNISTD_H
#    include <errno.h>        //Errors
#    include <cstring>        //strerror
#  else  //ifdef BOOST_HAS_UNISTD_H
#    error Unknown platform
#  endif //ifdef BOOST_HAS_UNISTD_H
#endif   //#if defined (BOOST_INTERPROCESS_WINDOWS)

//!\file
//!Describes the error numbering of interprocess classes

namespace boost {
namespace interprocess {
#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
inline int system_error_code() // artifact of POSIX and WINDOWS error reporting
{
   #if defined (BOOST_INTERPROCESS_WINDOWS)
   return winapi::get_last_error();
   #else
   return errno; // GCC 3.1 won't accept ::errno
   #endif
}


#if defined (BOOST_INTERPROCESS_WINDOWS)
inline void fill_system_message(int sys_err_code, std::string &str)
{
   void *lpMsgBuf;
   unsigned long ret = winapi::format_message(
      winapi::format_message_allocate_buffer |
      winapi::format_message_from_system |
      winapi::format_message_ignore_inserts,
      0,
      sys_err_code,
      winapi::make_lang_id(winapi::lang_neutral, winapi::sublang_default), // Default language
      reinterpret_cast<char *>(&lpMsgBuf),
      0,
      0
   );
   if (ret != 0){
      str += static_cast<const char*>(lpMsgBuf);
      winapi::local_free( lpMsgBuf ); // free the buffer
      while ( str.size()
         && (str[str.size()-1] == '\n' || str[str.size()-1] == '\r') )
         str.erase( str.size()-1 );
   }
   else{
      str += "WinApi FormatMessage returned error";
   }
}
# else
inline void fill_system_message( int system_error, std::string &str)
{  str = std::strerror(system_error);  }
# endif
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

enum error_code_t
{
   no_error = 0,
   system_error,     // system generated error; if possible, is translated
                     // to one of the more specific errors below.
   other_error,      // library generated error
   security_error,   // includes access rights, permissions failures
   read_only_error,
   io_error,
   path_error,
   not_found_error,
//   not_directory_error,
   busy_error,       // implies trying again might succeed
   already_exists_error,
   not_empty_error,
   is_directory_error,
   out_of_space_error,
   out_of_memory_error,
   out_of_resource_error,
   lock_error,
   sem_error,
   mode_error,
   size_error,
   corrupted_error,
   not_such_file_or_directory,
   invalid_argument,
   timeout_when_locking_error,
   timeout_when_waiting_error,
   owner_dead_error
};

typedef int    native_error_t;

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
struct ec_xlate
{
   native_error_t sys_ec;
   error_code_t   ec;
};

static const ec_xlate ec_table[] =
{
   #if defined (BOOST_INTERPROCESS_WINDOWS)
   { /*ERROR_ACCESS_DENIED*/5L, security_error },
   { /*ERROR_INVALID_ACCESS*/12L, security_error },
   { /*ERROR_SHARING_VIOLATION*/32L, security_error },
   { /*ERROR_LOCK_VIOLATION*/33L, security_error },
   { /*ERROR_LOCKED*/212L, security_error },
   { /*ERROR_NOACCESS*/998L, security_error },
   { /*ERROR_WRITE_PROTECT*/19L, read_only_error },
   { /*ERROR_NOT_READY*/21L, io_error },
   { /*ERROR_SEEK*/25L, io_error },
   { /*ERROR_READ_FAULT*/30L, io_error },
   { /*ERROR_WRITE_FAULT*/29L, io_error },
   { /*ERROR_CANTOPEN*/1011L, io_error },
   { /*ERROR_CANTREAD*/1012L, io_error },
   { /*ERROR_CANTWRITE*/1013L, io_error },
   { /*ERROR_DIRECTORY*/267L, path_error },
   { /*ERROR_INVALID_NAME*/123L, path_error },
   { /*ERROR_FILE_NOT_FOUND*/2L, not_found_error },
   { /*ERROR_PATH_NOT_FOUND*/3L, not_found_error },
   { /*ERROR_DEV_NOT_EXIST*/55L, not_found_error },
   { /*ERROR_DEVICE_IN_USE*/2404L, busy_error },
   { /*ERROR_OPEN_FILES*/2401L, busy_error },
   { /*ERROR_BUSY_DRIVE*/142L, busy_error },
   { /*ERROR_BUSY*/170L, busy_error },
   { /*ERROR_FILE_EXISTS*/80L, already_exists_error },
   { /*ERROR_ALREADY_EXISTS*/183L, already_exists_error },
   { /*ERROR_DIR_NOT_EMPTY*/145L, not_empty_error },
   { /*ERROR_HANDLE_DISK_FULL*/39L, out_of_space_error },
   { /*ERROR_DISK_FULL*/112L, out_of_space_error },
   { /*ERROR_OUTOFMEMORY*/14L, out_of_memory_error },
   { /*ERROR_NOT_ENOUGH_MEMORY*/8L, out_of_memory_error },
   { /*ERROR_TOO_MANY_OPEN_FILES*/4L, out_of_resource_error },
   { /*ERROR_INVALID_ADDRESS*/487L, busy_error }
   #else    //#if defined (BOOST_INTERPROCESS_WINDOWS)
   { EACCES, security_error },
   { EROFS, read_only_error },
   { EIO, io_error },
   { ENAMETOOLONG, path_error },
   { ENOENT, not_found_error },
   //    { ENOTDIR, not_directory_error },
   { EAGAIN, busy_error },
   { EBUSY, busy_error },
   { ETXTBSY, busy_error },
   { EEXIST, already_exists_error },
   { ENOTEMPTY, not_empty_error },
   { EISDIR, is_directory_error },
   { ENOSPC, out_of_space_error },
   { ENOMEM, out_of_memory_error },
   { EMFILE, out_of_resource_error },
   { ENOENT, not_such_file_or_directory },
   { EINVAL, invalid_argument }
   #endif   //#if defined (BOOST_INTERPROCESS_WINDOWS)
};

inline error_code_t lookup_error(native_error_t err)
{
   const ec_xlate *cur  = &ec_table[0],
                  *end  = cur + sizeof(ec_table)/sizeof(ec_xlate);
   for  (;cur != end; ++cur ){
      if ( err == cur->sys_ec ) return cur->ec;
   }
   return system_error; // general system error code
}

struct error_info
{
   error_info(error_code_t ec = other_error )
      :  m_nat(0), m_ec(ec)
   {}

   error_info(native_error_t sys_err_code)
      :  m_nat(sys_err_code), m_ec(lookup_error(sys_err_code))
   {}

   error_info & operator =(error_code_t ec)
   {
      m_nat = 0;
      m_ec = ec;
      return *this;
   }

   error_info & operator =(native_error_t sys_err_code)
   {
      m_nat = sys_err_code;
      m_ec = lookup_error(sys_err_code);
      return *this;
   }

   native_error_t get_native_error()const
   {  return m_nat;  }

   error_code_t   get_error_code()const
   {  return m_ec;  }

   private:
   native_error_t m_nat;
   error_code_t   m_ec;
};
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  // namespace interprocess {
}  // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_ERRORS_HPP

/* errors.hpp
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
*/