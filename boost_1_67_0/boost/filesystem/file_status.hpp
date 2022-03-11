//  boost/filesystem/file_status.hpp  --------------------------------------------------//

//  Copyright Beman Dawes 2002-2009
//  Copyright Jan Langer 2002
//  Copyright Dietmar Kuehl 2001
//  Copyright Vladimir Prus 2002
//  Copyright Andrey Semashev 2019

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

//--------------------------------------------------------------------------------------//

#ifndef BOOST_FILESYSTEM3_FILE_STATUS_HPP
#define BOOST_FILESYSTEM3_FILE_STATUS_HPP

#include <boost/config.hpp>

# if defined( BOOST_NO_STD_WSTRING )
#   error Configuration not supported: Boost.Filesystem V3 and later requires std::wstring support
# endif

#include <boost/filesystem/config.hpp>

#include <boost/detail/bitmask.hpp>

#include <boost/config/abi_prefix.hpp> // must be the last #include

//--------------------------------------------------------------------------------------//

namespace boost {
namespace filesystem {

//--------------------------------------------------------------------------------------//
//                                     file_type                                        //
//--------------------------------------------------------------------------------------//

enum file_type
{
  status_error,
# ifndef BOOST_FILESYSTEM_NO_DEPRECATED
  status_unknown = status_error,
# endif
  file_not_found,
  regular_file,
  directory_file,
  // the following may not apply to some operating systems or file systems
  symlink_file,
  block_file,
  character_file,
  fifo_file,
  socket_file,
  reparse_file,  // Windows: FILE_ATTRIBUTE_REPARSE_POINT that is not a symlink
  type_unknown,  // file does exist, but isn't one of the above types or
                 // we don't have strong enough permission to find its type

  _detail_directory_symlink  // internal use only; never exposed to users
};

//--------------------------------------------------------------------------------------//
//                                       perms                                          //
//--------------------------------------------------------------------------------------//

enum perms
{
  no_perms = 0,       // file_not_found is no_perms rather than perms_not_known

  // POSIX equivalent macros given in comments.
  // Values are from POSIX and are given in octal per the POSIX standard.

  // permission bits

  owner_read = 0400,  // S_IRUSR, Read permission, owner
  owner_write = 0200, // S_IWUSR, Write permission, owner
  owner_exe = 0100,   // S_IXUSR, Execute/search permission, owner
  owner_all = 0700,   // S_IRWXU, Read, write, execute/search by owner

  group_read = 040,   // S_IRGRP, Read permission, group
  group_write = 020,  // S_IWGRP, Write permission, group
  group_exe = 010,    // S_IXGRP, Execute/search permission, group
  group_all = 070,    // S_IRWXG, Read, write, execute/search by group

  others_read = 04,   // S_IROTH, Read permission, others
  others_write = 02,  // S_IWOTH, Write permission, others
  others_exe = 01,    // S_IXOTH, Execute/search permission, others
  others_all = 07,    // S_IRWXO, Read, write, execute/search by others

  all_all = 0777,     // owner_all|group_all|others_all

  // other POSIX bits

  set_uid_on_exe = 04000, // S_ISUID, Set-user-ID on execution
  set_gid_on_exe = 02000, // S_ISGID, Set-group-ID on execution
  sticky_bit     = 01000, // S_ISVTX,
                          // (POSIX XSI) On directories, restricted deletion flag
                          // (V7) 'sticky bit': save swapped text even after use
                          // (SunOS) On non-directories: don't cache this file
                          // (SVID-v4.2) On directories: restricted deletion flag
                          // Also see http://en.wikipedia.org/wiki/Sticky_bit

  perms_mask = 07777,     // all_all|set_uid_on_exe|set_gid_on_exe|sticky_bit

  perms_not_known = 0xFFFF, // present when directory_entry cache not loaded

  // options for permissions() function

  add_perms = 0x1000,     // adds the given permission bits to the current bits
  remove_perms = 0x2000,  // removes the given permission bits from the current bits;
                          // choose add_perms or remove_perms, not both; if neither add_perms
                          // nor remove_perms is given, replace the current bits with
                          // the given bits.

  symlink_perms = 0x4000, // on POSIX, don't resolve symlinks; implied on Windows

  // BOOST_BITMASK op~ casts to int32_least_t, producing invalid enum values
  _detail_extend_perms_32_1 = 0x7fffffff,
  _detail_extend_perms_32_2 = -0x7fffffff-1
};

BOOST_BITMASK(perms)

//--------------------------------------------------------------------------------------//
//                                    file_status                                       //
//--------------------------------------------------------------------------------------//

class file_status
{
public:
  BOOST_CONSTEXPR file_status() BOOST_NOEXCEPT :
    m_value(status_error), m_perms(perms_not_known)
  {
  }
  explicit BOOST_CONSTEXPR file_status(file_type v) BOOST_NOEXCEPT :
    m_value(v), m_perms(perms_not_known)
  {
  }
  BOOST_CONSTEXPR file_status(file_type v, perms prms) BOOST_NOEXCEPT :
    m_value(v), m_perms(prms)
  {
  }

  //  As of October 2015 the interaction between noexcept and =default is so troublesome
  //  for VC++, GCC, and probably other compilers, that =default is not used with noexcept
  //  functions. GCC is not even consistent for the same release on different platforms.

  BOOST_CONSTEXPR file_status(const file_status& rhs) BOOST_NOEXCEPT :
    m_value(rhs.m_value), m_perms(rhs.m_perms)
  {
  }
  BOOST_CXX14_CONSTEXPR file_status& operator=(const file_status& rhs) BOOST_NOEXCEPT
  {
    m_value = rhs.m_value;
    m_perms = rhs.m_perms;
    return *this;
  }

# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  // Note: std::move is not constexpr in C++11, that's why we're not using it here
  BOOST_CONSTEXPR file_status(file_status&& rhs) BOOST_NOEXCEPT :
    m_value(static_cast< file_type&& >(rhs.m_value)), m_perms(static_cast< enum perms&& >(rhs.m_perms))
  {
  }
  BOOST_CXX14_CONSTEXPR file_status& operator=(file_status&& rhs) BOOST_NOEXCEPT
  {
    m_value = static_cast< file_type&& >(rhs.m_value);
    m_perms = static_cast< enum perms&& >(rhs.m_perms);
    return *this;
  }
# endif

  // observers
  BOOST_CONSTEXPR file_type  type() const BOOST_NOEXCEPT            { return m_value; }
  BOOST_CONSTEXPR perms      permissions() const BOOST_NOEXCEPT     { return m_perms; }

  // modifiers
  BOOST_CXX14_CONSTEXPR void type(file_type v) BOOST_NOEXCEPT       { m_value = v; }
  BOOST_CXX14_CONSTEXPR void permissions(perms prms) BOOST_NOEXCEPT { m_perms = prms; }

  BOOST_CONSTEXPR bool operator==(const file_status& rhs) const BOOST_NOEXCEPT
  {
    return type() == rhs.type() && permissions() == rhs.permissions();
  }
  BOOST_CONSTEXPR bool operator!=(const file_status& rhs) const BOOST_NOEXCEPT
  {
    return !(*this == rhs);
  }

private:
  file_type   m_value;
  enum perms  m_perms;
};

inline BOOST_CONSTEXPR bool type_present(file_status f) BOOST_NOEXCEPT
{
  return f.type() != status_error;
}
inline BOOST_CONSTEXPR bool permissions_present(file_status f) BOOST_NOEXCEPT
{
  return f.permissions() != perms_not_known;
}
inline BOOST_CONSTEXPR bool status_known(file_status f) BOOST_NOEXCEPT
{
  return filesystem::type_present(f) && filesystem::permissions_present(f);
}
inline BOOST_CONSTEXPR bool exists(file_status f) BOOST_NOEXCEPT
{
  return f.type() != status_error && f.type() != file_not_found;
}
inline BOOST_CONSTEXPR bool is_regular_file(file_status f) BOOST_NOEXCEPT
{
  return f.type() == regular_file;
}
inline BOOST_CONSTEXPR bool is_directory(file_status f) BOOST_NOEXCEPT
{
  return f.type() == directory_file;
}
inline BOOST_CONSTEXPR bool is_symlink(file_status f) BOOST_NOEXCEPT
{
  return f.type() == symlink_file;
}
inline BOOST_CONSTEXPR bool is_other(file_status f) BOOST_NOEXCEPT
{
  return filesystem::exists(f) && !filesystem::is_regular_file(f)
    && !filesystem::is_directory(f) && !filesystem::is_symlink(f);
}

# ifndef BOOST_FILESYSTEM_NO_DEPRECATED
inline bool is_regular(file_status f) BOOST_NOEXCEPT { return filesystem::is_regular_file(f); }
# endif

} // namespace filesystem
} // namespace boost

#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#endif // BOOST_FILESYSTEM3_FILE_STATUS_HPP

/* file_status.hpp
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
*/