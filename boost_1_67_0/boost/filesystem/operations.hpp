//  boost/filesystem/operations.hpp  ---------------------------------------------------//

//  Copyright Beman Dawes 2002-2009
//  Copyright Jan Langer 2002
//  Copyright Dietmar Kuehl 2001
//  Copyright Vladimir Prus 2002

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

//--------------------------------------------------------------------------------------//

#ifndef BOOST_FILESYSTEM3_OPERATIONS_HPP
#define BOOST_FILESYSTEM3_OPERATIONS_HPP

#include <boost/config.hpp>

# if defined( BOOST_NO_STD_WSTRING )
#   error Configuration not supported: Boost.Filesystem V3 and later requires std::wstring support
# endif

#include <boost/filesystem/config.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/file_status.hpp>

#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
// These includes are left for backward compatibility and should be included directly by users, as needed
#include <boost/filesystem/exception.hpp>
#include <boost/filesystem/directory.hpp>
#endif

#include <boost/core/scoped_enum.hpp>
#include <boost/system/error_code.hpp>
#include <boost/cstdint.hpp>
#include <string>
#include <ctime>

#include <boost/config/abi_prefix.hpp> // must be the last #include

//--------------------------------------------------------------------------------------//

namespace boost {
namespace filesystem {

struct space_info
{
  // all values are byte counts
  boost::uintmax_t capacity;
  boost::uintmax_t free;      // <= capacity
  boost::uintmax_t available; // <= free
};

BOOST_SCOPED_ENUM_DECLARE_BEGIN(copy_option)
  {none=0, fail_if_exists = none, overwrite_if_exists}
BOOST_SCOPED_ENUM_DECLARE_END(copy_option)

//--------------------------------------------------------------------------------------//
//                             implementation details                                   //
//--------------------------------------------------------------------------------------//

namespace detail {

//  We cannot pass a BOOST_SCOPED_ENUM to a compled function because it will result
//  in an undefined reference if the library is compled with -std=c++0x but the use
//  is compiled in C++03 mode, or vice versa. See tickets 6124, 6779, 10038.
enum copy_option {none=0, fail_if_exists = none, overwrite_if_exists};

BOOST_FILESYSTEM_DECL
file_status status(const path&p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
file_status symlink_status(const path& p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
bool is_empty(const path& p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
path initial_path(system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
path canonical(const path& p, const path& base, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
void copy(const path& from, const path& to, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
void copy_directory(const path& from, const path& to, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
void copy_file(const path& from, const path& to,  // See ticket #2925
                detail::copy_option option, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
void copy_symlink(const path& existing_symlink, const path& new_symlink, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
bool create_directories(const path& p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
bool create_directory(const path& p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
void create_directory_symlink(const path& to, const path& from,
                              system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
void create_hard_link(const path& to, const path& from, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
void create_symlink(const path& to, const path& from, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
path current_path(system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
void current_path(const path& p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
bool equivalent(const path& p1, const path& p2, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
boost::uintmax_t file_size(const path& p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
boost::uintmax_t hard_link_count(const path& p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
std::time_t last_write_time(const path& p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
void last_write_time(const path& p, const std::time_t new_time,
                     system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
void permissions(const path& p, perms prms, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
path read_symlink(const path& p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
path relative(const path& p, const path& base, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
bool remove(const path& p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
boost::uintmax_t remove_all(const path& p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
void rename(const path& old_p, const path& new_p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
void resize_file(const path& p, uintmax_t size, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
space_info space(const path& p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
path system_complete(const path& p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
path temp_directory_path(system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
path unique_path(const path& p, system::error_code* ec=0);
BOOST_FILESYSTEM_DECL
path weakly_canonical(const path& p, system::error_code* ec = 0);

} // namespace detail

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                             status query functions                                   //
//                                                                                      //
//--------------------------------------------------------------------------------------//

inline
file_status status(const path& p)    {return detail::status(p);}
inline
file_status status(const path& p, system::error_code& ec)
                                     {return detail::status(p, &ec);}
inline
file_status symlink_status(const path& p) {return detail::symlink_status(p);}
inline
file_status symlink_status(const path& p, system::error_code& ec)
                                     {return detail::symlink_status(p, &ec);}
inline
bool exists(const path& p)           {return exists(detail::status(p));}
inline
bool exists(const path& p, system::error_code& ec)
                                     {return exists(detail::status(p, &ec));}
inline
bool is_directory(const path& p)     {return is_directory(detail::status(p));}
inline
bool is_directory(const path& p, system::error_code& ec)
                                     {return is_directory(detail::status(p, &ec));}
inline
bool is_regular_file(const path& p)  {return is_regular_file(detail::status(p));}
inline
bool is_regular_file(const path& p, system::error_code& ec)
                                     {return is_regular_file(detail::status(p, &ec));}
inline
bool is_other(const path& p)         {return is_other(detail::status(p));}
inline
bool is_other(const path& p, system::error_code& ec)
                                     {return is_other(detail::status(p, &ec));}
inline
bool is_symlink(const path& p)       {return is_symlink(detail::symlink_status(p));}
inline
bool is_symlink(const path& p, system::error_code& ec)
                                     {return is_symlink(detail::symlink_status(p, &ec));}
#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
inline
bool is_regular(const path& p)       {return is_regular(detail::status(p));}
inline
bool is_regular(const path& p, system::error_code& ec)
                                     {return is_regular(detail::status(p, &ec));}
#endif

inline
bool is_empty(const path& p)         {return detail::is_empty(p);}
inline
bool is_empty(const path& p, system::error_code& ec)
                                     {return detail::is_empty(p, &ec);}

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                             operational functions                                    //
//                  in alphabetical order, unless otherwise noted                       //
//                                                                                      //
//--------------------------------------------------------------------------------------//

//  forward declarations
path current_path();  // fwd declaration
path initial_path();

BOOST_FILESYSTEM_DECL
path absolute(const path& p, const path& base=current_path());
//  If base.is_absolute(), throws nothing. Thus no need for ec argument

inline
path canonical(const path& p, const path& base=current_path())
                                     {return detail::canonical(p, base);}
inline
path canonical(const path& p, system::error_code& ec)
                                     {return detail::canonical(p, current_path(), &ec);}
inline
path canonical(const path& p, const path& base, system::error_code& ec)
                                     {return detail::canonical(p, base, &ec);}

#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
inline
path complete(const path& p)
{
  return absolute(p, initial_path());
}

inline
path complete(const path& p, const path& base)
{
  return absolute(p, base);
}
#endif

inline
void copy(const path& from, const path& to) {detail::copy(from, to);}

inline
void copy(const path& from, const path& to, system::error_code& ec) BOOST_NOEXCEPT
                                     {detail::copy(from, to, &ec);}
inline
void copy_directory(const path& from, const path& to)
                                     {detail::copy_directory(from, to);}
inline
void copy_directory(const path& from, const path& to, system::error_code& ec) BOOST_NOEXCEPT
                                     {detail::copy_directory(from, to, &ec);}
inline
void copy_file(const path& from, const path& to,   // See ticket #2925
               BOOST_SCOPED_ENUM_NATIVE(copy_option) option)
{
  detail::copy_file(from, to, static_cast<detail::copy_option>(option));
}
inline
void copy_file(const path& from, const path& to)
{
  detail::copy_file(from, to, detail::fail_if_exists);
}
inline
void copy_file(const path& from, const path& to,   // See ticket #2925
               BOOST_SCOPED_ENUM_NATIVE(copy_option) option, system::error_code& ec) BOOST_NOEXCEPT
{
  detail::copy_file(from, to, static_cast<detail::copy_option>(option), &ec);
}
inline
void copy_file(const path& from, const path& to, system::error_code& ec) BOOST_NOEXCEPT
{
  detail::copy_file(from, to, detail::fail_if_exists, &ec);
}
inline
void copy_symlink(const path& existing_symlink,
                  const path& new_symlink) {detail::copy_symlink(existing_symlink, new_symlink);}

inline
void copy_symlink(const path& existing_symlink, const path& new_symlink,
                  system::error_code& ec) BOOST_NOEXCEPT
                                     {detail::copy_symlink(existing_symlink, new_symlink, &ec);}
inline
bool create_directories(const path& p) {return detail::create_directories(p);}

inline
bool create_directories(const path& p, system::error_code& ec) BOOST_NOEXCEPT
                                     {return detail::create_directories(p, &ec);}
inline
bool create_directory(const path& p) {return detail::create_directory(p);}

inline
bool create_directory(const path& p, system::error_code& ec) BOOST_NOEXCEPT
                                     {return detail::create_directory(p, &ec);}
inline
void create_directory_symlink(const path& to, const path& from)
                                     {detail::create_directory_symlink(to, from);}
inline
void create_directory_symlink(const path& to, const path& from, system::error_code& ec) BOOST_NOEXCEPT
                                     {detail::create_directory_symlink(to, from, &ec);}
inline
void create_hard_link(const path& to, const path& new_hard_link) {detail::create_hard_link(to, new_hard_link);}

inline
void create_hard_link(const path& to, const path& new_hard_link, system::error_code& ec) BOOST_NOEXCEPT
                                     {detail::create_hard_link(to, new_hard_link, &ec);}
inline
void create_symlink(const path& to, const path& new_symlink) {detail::create_symlink(to, new_symlink);}

inline
void create_symlink(const path& to, const path& new_symlink, system::error_code& ec) BOOST_NOEXCEPT
                                     {detail::create_symlink(to, new_symlink, &ec);}
inline
path current_path()                  {return detail::current_path();}

inline
path current_path(system::error_code& ec) {return detail::current_path(&ec);}

inline
void current_path(const path& p)     {detail::current_path(p);}

inline
void current_path(const path& p, system::error_code& ec) BOOST_NOEXCEPT {detail::current_path(p, &ec);}

inline
bool equivalent(const path& p1, const path& p2) {return detail::equivalent(p1, p2);}

inline
bool equivalent(const path& p1, const path& p2, system::error_code& ec) BOOST_NOEXCEPT
                                     {return detail::equivalent(p1, p2, &ec);}
inline
boost::uintmax_t file_size(const path& p) {return detail::file_size(p);}

inline
boost::uintmax_t file_size(const path& p, system::error_code& ec) BOOST_NOEXCEPT
                                     {return detail::file_size(p, &ec);}
inline
boost::uintmax_t hard_link_count(const path& p) {return detail::hard_link_count(p);}

inline
boost::uintmax_t hard_link_count(const path& p, system::error_code& ec) BOOST_NOEXCEPT
                                     {return detail::hard_link_count(p, &ec);}
inline
path initial_path()                  {return detail::initial_path();}

inline
path initial_path(system::error_code& ec) {return detail::initial_path(&ec);}

template <class Path>
path initial_path() {return initial_path();}
template <class Path>
path initial_path(system::error_code& ec) {return detail::initial_path(&ec);}

inline
std::time_t last_write_time(const path& p) {return detail::last_write_time(p);}

inline
std::time_t last_write_time(const path& p, system::error_code& ec) BOOST_NOEXCEPT
                                     {return detail::last_write_time(p, &ec);}
inline
void last_write_time(const path& p, const std::time_t new_time)
                                     {detail::last_write_time(p, new_time);}
inline
void last_write_time(const path& p, const std::time_t new_time,
                     system::error_code& ec) BOOST_NOEXCEPT
                                     {detail::last_write_time(p, new_time, &ec);}
inline
void permissions(const path& p, perms prms)
                                     {detail::permissions(p, prms);}
inline
void permissions(const path& p, perms prms, system::error_code& ec) BOOST_NOEXCEPT
                                     {detail::permissions(p, prms, &ec);}

inline
path read_symlink(const path& p)     {return detail::read_symlink(p);}

inline
path read_symlink(const path& p, system::error_code& ec)
                                     {return detail::read_symlink(p, &ec);}

inline
bool remove(const path& p)           {return detail::remove(p);}

inline
bool remove(const path& p, system::error_code& ec) BOOST_NOEXCEPT
                                     {return detail::remove(p, &ec);}

inline
boost::uintmax_t remove_all(const path& p) {return detail::remove_all(p);}

inline
boost::uintmax_t remove_all(const path& p, system::error_code& ec) BOOST_NOEXCEPT
                                     {return detail::remove_all(p, &ec);}
inline
void rename(const path& old_p, const path& new_p) {detail::rename(old_p, new_p);}

inline
void rename(const path& old_p, const path& new_p, system::error_code& ec) BOOST_NOEXCEPT
                                     {detail::rename(old_p, new_p, &ec);}
inline  // name suggested by Scott McMurray
void resize_file(const path& p, uintmax_t size) {detail::resize_file(p, size);}

inline
void resize_file(const path& p, uintmax_t size, system::error_code& ec) BOOST_NOEXCEPT
                                     {detail::resize_file(p, size, &ec);}
inline
path relative(const path& p, const path& base=current_path())
                                     {return detail::relative(p, base);}
inline
path relative(const path& p, system::error_code& ec)
                                     {return detail::relative(p, current_path(), &ec);}
inline
path relative(const path& p, const path& base, system::error_code& ec)
                                     {return detail::relative(p, base, &ec);}
inline
space_info space(const path& p)      {return detail::space(p);}

inline
space_info space(const path& p, system::error_code& ec) BOOST_NOEXCEPT
                                     {return detail::space(p, &ec);}

#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
inline bool symbolic_link_exists(const path& p)
                                     { return is_symlink(filesystem::symlink_status(p)); }
#endif

inline
path system_complete(const path& p)  {return detail::system_complete(p);}

inline
path system_complete(const path& p, system::error_code& ec)
                                     {return detail::system_complete(p, &ec);}
inline
path temp_directory_path()           {return detail::temp_directory_path();}

inline
path temp_directory_path(system::error_code& ec)
                                     {return detail::temp_directory_path(&ec);}
inline
path unique_path(const path& p="%%%%-%%%%-%%%%-%%%%")
                                     {return detail::unique_path(p);}
inline
path unique_path(const path& p, system::error_code& ec)
                                     {return detail::unique_path(p, &ec);}
inline
path weakly_canonical(const path& p)   {return detail::weakly_canonical(p);}

inline
path weakly_canonical(const path& p, system::error_code& ec)
                                     {return detail::weakly_canonical(p, &ec);}

//  test helper  -----------------------------------------------------------------------//

//  Not part of the documented interface since false positives are possible;
//  there is no law that says that an OS that has large stat.st_size
//  actually supports large file sizes.

namespace detail {

BOOST_FILESYSTEM_DECL bool possible_large_file_size_support();

} // namespace detail

} // namespace filesystem
} // namespace boost

#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#endif // BOOST_FILESYSTEM3_OPERATIONS_HPP

/* operations.hpp
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
*/