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
zwaDEj6cl9Dx4C4raxs7nb1hZ3gw6AzGTfYN1NvrxfT+3rHVK2RQCsQx+gMJD3p7IS8MZ4VP8sIm0/lwMtZNWA/mLuvOHQd3cxjxY2wxvsusO/WkEDub/eNm290xxRqFCYCmIhIVNfRgPB/uDwez9dtPhj2bLMdJnaN5JjpPr9Ok2qbaOtZZ27oFXBO+5uZuZ2d3e3PrOp3e7Qe9O6Zok3MGHqCdvUIWBWjcPRx0prPhOGchUI4tDjtd3ctw2qOEleNG0t3wRllNBMtjiVDHHXeDjbUtH2Vj6yY33Nhe2924VpNTBqKTEtah5pe7TMop5UrJGUZVcqw10/mkc80tg147Ff86G1vEusHmLTeutbt5w41Ot3+HIsObQc5y9c45raVQpyLDW0TOon7tjI6ek/Ag4ofNm+OpaGkzb65dNssALEkMkiXc2t24zsZ2p3c4jYH+IgZ8xoJgFxEghpLDiwI+jJPnQqGqBCgXoMsFhJa0dZMb3KCpgpCUL4QUftw1r7exvtvpzQbd+SCCSB4BZBCRksX67obvx1vX2rg2MQscdJ6jKD5GpVlzuJhvWQ5R5o3Wd29u8hPyAA32BrN5Z3/UPdARo4yND4vwZNgv4hh8hiNmQOk2CWDkWFkC3SKBLkiwjZGsXfMGG7F+cw4qLuOInzBKmeTJSwnnd5vahDtx4+w4BXan006/O+/GsNRIMEocHCYQyHSEOQcwUgSUzovYuPFNNrbWN+w4m4AC7IYRnK01tcI59wtobzTojrHxnIOkIdrEnIkykm4j9GR6txCQSqRdKu9MMhO4VJ4MlBnVfncxmncOu/qOEXM0GB/Mb1+ApKOJoYS0GTQyhInaXYtgZz8WnuxT+lIJwMThbp2tzWvFcFKbI5l2RiIRcKU32b32FWIMq80Aqe7u5Y6l+hYMi0kRSZiO+vFQL+N7QPeH+/tCBiVGA3s8mqdDeDxuJ4O1gOgC0xgPZt3R8O6D/nx46Iq6xY0QDOsUCjlCJhYVU4xmuKzefDD3pQi3jUMFAmra7d0ROe+0YKIfloXoMXUsJI8qGm4Lh8VDobibbG3edGN7J53D5BzaoYxTozIDVQcyYILrsS0AiDnEEA3RWbZNZx7jIh1IZB3QsYEApDYCZA0jB2JR6S25PgBTVQClWrjp5s5mOjTlODnkqGSC920Gw8NJfzEaeAwhu3ujQQTvjaWKUIv9gDSqxVj2h2NGFpaTfYuz8Jy3cvurQ1YvE094L9ZnWatN1t4v2+5E+jG57ifYnS/tAKxy7w6Dnk09XO1LERC+CAQ5XJYplBMnRqIEXjABFiEbR0ySCPAtIwhixADNIUCagNgxFcuYV2qMj45TxQU0ziAkacawSnp4ME7ITm9+V4Ho4EkWdx7Mhvt2fD3cMxZO209TaOwx20jkfndTWaSa6TCIap2XnC4Y4yY9R8QtLOJSyKoMWvPuwSpLYyFgN4RIG+1jBHsY4f7FLbbWOzdbY8XNDMhNNvoJbrMQzE/IRiNi6wKLPrEspN/CzssoiaOJeJfuMIi9N5r07oj+FtrKY2dSeLnbs1ax0YwAi9lsgHe/w2TPoS47WttCyw4bJx3qTq87xTvYAkxhQS64jlmQK8YSCXWT3eset725ewvWX9c+rmN31tBfC4sGaWGgj4Bz/Y1bbJrdihQkhwwi7co12TJa76wft4VPXGOObaTIYdLnoMnh2tFeHyTbeJe7TAAwXXLBcBcPMgxOklRux44gTWw25a65eR02P5CFECq41rXw4+gCXz0baB2D+93D4ehuCUbdIoQa3DXODEcwmU96k1GMahqPOZukNr3Ak2lxcVGd20/0vNkYMy5AGGjQExgHc+I0xqx7F6k=
*/