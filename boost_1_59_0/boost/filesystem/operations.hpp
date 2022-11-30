//  boost/filesystem/operations.hpp  ---------------------------------------------------//

//  Copyright Beman Dawes 2002-2009
//  Copyright Jan Langer 2002
//  Copyright Dietmar Kuehl 2001
//  Copyright Vladimir Prus 2002
//  Copyright Andrey Semashev 2020-2021

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

//--------------------------------------------------------------------------------------//

#ifndef BOOST_FILESYSTEM_OPERATIONS_HPP
#define BOOST_FILESYSTEM_OPERATIONS_HPP

#include <boost/filesystem/config.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/file_status.hpp>

#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
// These includes are left for backward compatibility and should be included directly by users, as needed
#include <boost/filesystem/exception.hpp>
#include <boost/filesystem/directory.hpp>
#endif

#include <boost/detail/bitmask.hpp>
#include <boost/core/scoped_enum.hpp>
#include <boost/system/error_code.hpp>
#include <boost/cstdint.hpp>
#include <string>
#include <ctime>

#include <boost/filesystem/detail/header.hpp> // must be the last #include

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

BOOST_SCOPED_ENUM_UT_DECLARE_BEGIN(copy_options, unsigned int)
{
    none = 0u, // Default. For copy_file: error if the target file exists. For copy: do not recurse, follow symlinks, copy file contents.

    // copy_file options:
    skip_existing = 1u,           // Don't overwrite the existing target file, don't report an error
    overwrite_existing = 1u << 1, // Overwrite existing file
    update_existing = 1u << 2,    // Overwrite existing file if its last write time is older than the replacement file
    synchronize_data = 1u << 3,   // Flush all buffered data written to the target file to permanent storage
    synchronize = 1u << 4,        // Flush all buffered data and attributes written to the target file to permanent storage

    // copy options:
    recursive = 1u << 8,          // Recurse into sub-directories
    copy_symlinks = 1u << 9,      // Copy symlinks as symlinks instead of copying the referenced file
    skip_symlinks = 1u << 10,     // Don't copy symlinks
    directories_only = 1u << 11,  // Only copy directory structure, do not copy non-directory files
    create_symlinks = 1u << 12,   // Create symlinks instead of copying files
    create_hard_links = 1u << 13, // Create hard links instead of copying files
    _detail_recursing = 1u << 14  // Internal use only, do not use
}
BOOST_SCOPED_ENUM_DECLARE_END(copy_options)

BOOST_BITMASK(BOOST_SCOPED_ENUM_NATIVE(copy_options))

#if !defined(BOOST_FILESYSTEM_NO_DEPRECATED)
BOOST_SCOPED_ENUM_DECLARE_BEGIN(copy_option)
{
    none = static_cast< unsigned int >(copy_options::none),
    fail_if_exists = none,
    overwrite_if_exists = static_cast< unsigned int >(copy_options::overwrite_existing)
}
BOOST_SCOPED_ENUM_DECLARE_END(copy_option)
#endif

//--------------------------------------------------------------------------------------//
//                             implementation details                                   //
//--------------------------------------------------------------------------------------//

namespace detail {

BOOST_FILESYSTEM_DECL
path absolute(path const& p, path const& base, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
file_status status(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
file_status symlink_status(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
bool is_empty(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
path initial_path(system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
path canonical(path const& p, path const& base, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
void copy(path const& from, path const& to, unsigned int options, system::error_code* ec = 0);
#if !defined(BOOST_FILESYSTEM_NO_DEPRECATED)
BOOST_FILESYSTEM_DECL
void copy_directory(path const& from, path const& to, system::error_code* ec = 0);
#endif
BOOST_FILESYSTEM_DECL
bool copy_file(path const& from, path const& to,                  // See ticket #2925
               unsigned int options, system::error_code* ec = 0); // see copy_options for options
BOOST_FILESYSTEM_DECL
void copy_symlink(path const& existing_symlink, path const& new_symlink, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
bool create_directories(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
bool create_directory(path const& p, const path* existing, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
void create_directory_symlink(path const& to, path const& from, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
void create_hard_link(path const& to, path const& from, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
void create_symlink(path const& to, path const& from, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
path current_path(system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
void current_path(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
bool equivalent(path const& p1, path const& p2, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
boost::uintmax_t file_size(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
boost::uintmax_t hard_link_count(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
std::time_t creation_time(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
std::time_t last_write_time(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
void last_write_time(path const& p, const std::time_t new_time, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
void permissions(path const& p, perms prms, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
path read_symlink(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
path relative(path const& p, path const& base, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
bool remove(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
boost::uintmax_t remove_all(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
void rename(path const& old_p, path const& new_p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
void resize_file(path const& p, uintmax_t size, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
space_info space(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
path system_complete(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
path temp_directory_path(system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
path unique_path(path const& p, system::error_code* ec = 0);
BOOST_FILESYSTEM_DECL
path weakly_canonical(path const& p, path const& base, system::error_code* ec = 0);

} // namespace detail

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                             status query functions                                   //
//                                                                                      //
//--------------------------------------------------------------------------------------//

inline file_status status(path const& p)
{
    return detail::status(p);
}

inline file_status status(path const& p, system::error_code& ec)
{
    return detail::status(p, &ec);
}

inline file_status symlink_status(path const& p)
{
    return detail::symlink_status(p);
}

inline file_status symlink_status(path const& p, system::error_code& ec)
{
    return detail::symlink_status(p, &ec);
}

inline bool exists(path const& p)
{
    return exists(detail::status(p));
}

inline bool exists(path const& p, system::error_code& ec)
{
    return exists(detail::status(p, &ec));
}

inline bool is_directory(path const& p)
{
    return is_directory(detail::status(p));
}

inline bool is_directory(path const& p, system::error_code& ec)
{
    return is_directory(detail::status(p, &ec));
}

inline bool is_regular_file(path const& p)
{
    return is_regular_file(detail::status(p));
}

inline bool is_regular_file(path const& p, system::error_code& ec)
{
    return is_regular_file(detail::status(p, &ec));
}

inline bool is_other(path const& p)
{
    return is_other(detail::status(p));
}

inline bool is_other(path const& p, system::error_code& ec)
{
    return is_other(detail::status(p, &ec));
}

inline bool is_symlink(path const& p)
{
    return is_symlink(detail::symlink_status(p));
}

inline bool is_symlink(path const& p, system::error_code& ec)
{
    return is_symlink(detail::symlink_status(p, &ec));
}

#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
inline bool is_regular(path const& p)
{
    return is_regular(detail::status(p));
}

inline bool is_regular(path const& p, system::error_code& ec)
{
    return is_regular(detail::status(p, &ec));
}
#endif

inline bool is_empty(path const& p)
{
    return detail::is_empty(p);
}

inline bool is_empty(path const& p, system::error_code& ec)
{
    return detail::is_empty(p, &ec);
}

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                             operational functions                                    //
//                                                                                      //
//--------------------------------------------------------------------------------------//

inline path initial_path()
{
    return detail::initial_path();
}

inline path initial_path(system::error_code& ec)
{
    return detail::initial_path(&ec);
}

template< class Path >
path initial_path()
{
    return initial_path();
}
template< class Path >
path initial_path(system::error_code& ec)
{
    return detail::initial_path(&ec);
}

inline path current_path()
{
    return detail::current_path();
}

inline path current_path(system::error_code& ec)
{
    return detail::current_path(&ec);
}

inline void current_path(path const& p)
{
    detail::current_path(p);
}

inline void current_path(path const& p, system::error_code& ec) BOOST_NOEXCEPT
{
    detail::current_path(p, &ec);
}

inline path absolute(path const& p, path const& base = current_path())
{
    return detail::absolute(p, base);
}

inline path absolute(path const& p, system::error_code& ec)
{
    path base = current_path(ec);
    if (ec)
        return path();
    return detail::absolute(p, base, &ec);
}

inline path absolute(path const& p, path const& base, system::error_code& ec)
{
    return detail::absolute(p, base, &ec);
}

inline path canonical(path const& p, path const& base = current_path())
{
    return detail::canonical(p, base);
}

inline path canonical(path const& p, system::error_code& ec)
{
    path base = current_path(ec);
    if (ec)
        return path();
    return detail::canonical(p, base, &ec);
}

inline path canonical(path const& p, path const& base, system::error_code& ec)
{
    return detail::canonical(p, base, &ec);
}

#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
inline path complete(path const& p)
{
    return absolute(p, initial_path());
}

inline path complete(path const& p, path const& base)
{
    return absolute(p, base);
}
#endif

inline void copy(path const& from, path const& to)
{
    detail::copy(from, to, static_cast< unsigned int >(copy_options::none));
}

inline void copy(path const& from, path const& to, system::error_code& ec) BOOST_NOEXCEPT
{
    detail::copy(from, to, static_cast< unsigned int >(copy_options::none), &ec);
}

inline void copy(path const& from, path const& to, BOOST_SCOPED_ENUM_NATIVE(copy_options) options)
{
    detail::copy(from, to, static_cast< unsigned int >(options));
}

inline void copy(path const& from, path const& to, BOOST_SCOPED_ENUM_NATIVE(copy_options) options, system::error_code& ec) BOOST_NOEXCEPT
{
    detail::copy(from, to, static_cast< unsigned int >(options), &ec);
}

#if !defined(BOOST_FILESYSTEM_NO_DEPRECATED)
inline void copy_directory(path const& from, path const& to)
{
    detail::copy_directory(from, to);
}

inline void copy_directory(path const& from, path const& to, system::error_code& ec) BOOST_NOEXCEPT
{
    detail::copy_directory(from, to, &ec);
}
#endif

inline bool copy_file(path const& from, path const& to)
{
    return detail::copy_file(from, to, static_cast< unsigned int >(copy_options::none));
}

inline bool copy_file(path const& from, path const& to, system::error_code& ec) BOOST_NOEXCEPT
{
    return detail::copy_file(from, to, static_cast< unsigned int >(copy_options::none), &ec);
}

inline bool copy_file(path const& from, path const& to, // See ticket #2925
                      BOOST_SCOPED_ENUM_NATIVE(copy_options) options)
{
    return detail::copy_file(from, to, static_cast< unsigned int >(options));
}

inline bool copy_file(path const& from, path const& to, // See ticket #2925
                      BOOST_SCOPED_ENUM_NATIVE(copy_options) options, system::error_code& ec) BOOST_NOEXCEPT
{
    return detail::copy_file(from, to, static_cast< unsigned int >(options), &ec);
}

#if !defined(BOOST_FILESYSTEM_NO_DEPRECATED)
inline bool copy_file(path const& from, path const& to, // See ticket #2925
                      BOOST_SCOPED_ENUM_NATIVE(copy_option) options)
{
    return detail::copy_file(from, to, static_cast< unsigned int >(options));
}

inline bool copy_file(path const& from, path const& to, // See ticket #2925
                      BOOST_SCOPED_ENUM_NATIVE(copy_option) options, system::error_code& ec) BOOST_NOEXCEPT
{
    return detail::copy_file(from, to, static_cast< unsigned int >(options), &ec);
}
#endif // !defined(BOOST_FILESYSTEM_NO_DEPRECATED)

inline void copy_symlink(path const& existing_symlink, path const& new_symlink)
{
    detail::copy_symlink(existing_symlink, new_symlink);
}

inline void copy_symlink(path const& existing_symlink, path const& new_symlink, system::error_code& ec) BOOST_NOEXCEPT
{
    detail::copy_symlink(existing_symlink, new_symlink, &ec);
}

inline bool create_directories(path const& p)
{
    return detail::create_directories(p);
}

inline bool create_directories(path const& p, system::error_code& ec) BOOST_NOEXCEPT
{
    return detail::create_directories(p, &ec);
}

inline bool create_directory(path const& p)
{
    return detail::create_directory(p, 0);
}

inline bool create_directory(path const& p, system::error_code& ec) BOOST_NOEXCEPT
{
    return detail::create_directory(p, 0, &ec);
}

inline bool create_directory(path const& p, path const& existing)
{
    return detail::create_directory(p, &existing);
}

inline bool create_directory(path const& p, path const& existing, system::error_code& ec) BOOST_NOEXCEPT
{
    return detail::create_directory(p, &existing, &ec);
}

inline void create_directory_symlink(path const& to, path const& from)
{
    detail::create_directory_symlink(to, from);
}

inline void create_directory_symlink(path const& to, path const& from, system::error_code& ec) BOOST_NOEXCEPT
{
    detail::create_directory_symlink(to, from, &ec);
}

inline void create_hard_link(path const& to, path const& new_hard_link)
{
    detail::create_hard_link(to, new_hard_link);
}

inline void create_hard_link(path const& to, path const& new_hard_link, system::error_code& ec) BOOST_NOEXCEPT
{
    detail::create_hard_link(to, new_hard_link, &ec);
}

inline void create_symlink(path const& to, path const& new_symlink)
{
    detail::create_symlink(to, new_symlink);
}

inline void create_symlink(path const& to, path const& new_symlink, system::error_code& ec) BOOST_NOEXCEPT
{
    detail::create_symlink(to, new_symlink, &ec);
}

inline bool equivalent(path const& p1, path const& p2)
{
    return detail::equivalent(p1, p2);
}

inline bool equivalent(path const& p1, path const& p2, system::error_code& ec) BOOST_NOEXCEPT
{
    return detail::equivalent(p1, p2, &ec);
}

inline boost::uintmax_t file_size(path const& p)
{
    return detail::file_size(p);
}

inline boost::uintmax_t file_size(path const& p, system::error_code& ec) BOOST_NOEXCEPT
{
    return detail::file_size(p, &ec);
}

inline boost::uintmax_t hard_link_count(path const& p)
{
    return detail::hard_link_count(p);
}

inline boost::uintmax_t hard_link_count(path const& p, system::error_code& ec) BOOST_NOEXCEPT
{
    return detail::hard_link_count(p, &ec);
}

inline std::time_t creation_time(path const& p)
{
    return detail::creation_time(p);
}

inline std::time_t creation_time(path const& p, system::error_code& ec) BOOST_NOEXCEPT
{
    return detail::creation_time(p, &ec);
}

inline std::time_t last_write_time(path const& p)
{
    return detail::last_write_time(p);
}

inline std::time_t last_write_time(path const& p, system::error_code& ec) BOOST_NOEXCEPT
{
    return detail::last_write_time(p, &ec);
}

inline void last_write_time(path const& p, const std::time_t new_time)
{
    detail::last_write_time(p, new_time);
}

inline void last_write_time(path const& p, const std::time_t new_time, system::error_code& ec) BOOST_NOEXCEPT
{
    detail::last_write_time(p, new_time, &ec);
}

inline void permissions(path const& p, perms prms)
{
    detail::permissions(p, prms);
}

inline void permissions(path const& p, perms prms, system::error_code& ec) BOOST_NOEXCEPT
{
    detail::permissions(p, prms, &ec);
}

inline path read_symlink(path const& p)
{
    return detail::read_symlink(p);
}

inline path read_symlink(path const& p, system::error_code& ec)
{
    return detail::read_symlink(p, &ec);
}

inline bool remove(path const& p)
{
    return detail::remove(p);
}

inline bool remove(path const& p, system::error_code& ec) BOOST_NOEXCEPT
{
    return detail::remove(p, &ec);
}

inline boost::uintmax_t remove_all(path const& p)
{
    return detail::remove_all(p);
}

inline boost::uintmax_t remove_all(path const& p, system::error_code& ec) BOOST_NOEXCEPT
{
    return detail::remove_all(p, &ec);
}

inline void rename(path const& old_p, path const& new_p)
{
    detail::rename(old_p, new_p);
}

inline void rename(path const& old_p, path const& new_p, system::error_code& ec) BOOST_NOEXCEPT
{
    detail::rename(old_p, new_p, &ec);
}

// name suggested by Scott McMurray
inline void resize_file(path const& p, uintmax_t size)
{
    detail::resize_file(p, size);
}

inline void resize_file(path const& p, uintmax_t size, system::error_code& ec) BOOST_NOEXCEPT
{
    detail::resize_file(p, size, &ec);
}

inline path relative(path const& p, path const& base = current_path())
{
    return detail::relative(p, base);
}

inline path relative(path const& p, system::error_code& ec)
{
    path base = current_path(ec);
    if (ec)
        return path();
    return detail::relative(p, base, &ec);
}

inline path relative(path const& p, path const& base, system::error_code& ec)
{
    return detail::relative(p, base, &ec);
}

inline space_info space(path const& p)
{
    return detail::space(p);
}

inline space_info space(path const& p, system::error_code& ec) BOOST_NOEXCEPT
{
    return detail::space(p, &ec);
}

#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
inline bool symbolic_link_exists(path const& p)
{
    return is_symlink(filesystem::symlink_status(p));
}
#endif

inline path system_complete(path const& p)
{
    return detail::system_complete(p);
}

inline path system_complete(path const& p, system::error_code& ec)
{
    return detail::system_complete(p, &ec);
}

inline path temp_directory_path()
{
    return detail::temp_directory_path();
}

inline path temp_directory_path(system::error_code& ec)
{
    return detail::temp_directory_path(&ec);
}

inline path unique_path(path const& p = "%%%%-%%%%-%%%%-%%%%")
{
    return detail::unique_path(p);
}

inline path unique_path(path const& p, system::error_code& ec)
{
    return detail::unique_path(p, &ec);
}

inline path weakly_canonical(path const& p, path const& base = current_path())
{
    return detail::weakly_canonical(p, base);
}

inline path weakly_canonical(path const& p, system::error_code& ec)
{
    path base = current_path(ec);
    if (ec)
        return path();
    return detail::weakly_canonical(p, base, &ec);
}

inline path weakly_canonical(path const& p, path const& base, system::error_code& ec)
{
    return detail::weakly_canonical(p, base, &ec);
}

//  test helper  -----------------------------------------------------------------------//

//  Not part of the documented interface since false positives are possible;
//  there is no law that says that an OS that has large stat.st_size
//  actually supports large file sizes.

namespace detail {

BOOST_FILESYSTEM_DECL bool possible_large_file_size_support();

} // namespace detail

} // namespace filesystem
} // namespace boost

#include <boost/filesystem/detail/footer.hpp>

#endif // BOOST_FILESYSTEM_OPERATIONS_HPP

/* operations.hpp
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
*/