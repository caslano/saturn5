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
#include <string>

#if defined (BOOST_INTERPROCESS_WINDOWS)
#  include <boost/interprocess/detail/win32_api.hpp>
#else
#  ifdef BOOST_HAS_UNISTD_H
#    include <cerrno>         //Errors
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
   return (int)winapi::get_last_error();
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
      (unsigned long)sys_err_code,
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
   owner_dead_error,
   not_recoverable
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