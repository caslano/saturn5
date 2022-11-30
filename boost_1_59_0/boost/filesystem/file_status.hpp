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

#ifndef BOOST_FILESYSTEM_FILE_STATUS_HPP
#define BOOST_FILESYSTEM_FILE_STATUS_HPP

#include <boost/filesystem/config.hpp>
#include <boost/detail/bitmask.hpp>

#include <boost/filesystem/detail/header.hpp> // must be the last #include

//--------------------------------------------------------------------------------------//

namespace boost {
namespace filesystem {

//--------------------------------------------------------------------------------------//
//                                     file_type                                        //
//--------------------------------------------------------------------------------------//

enum file_type
{
    status_error,
#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
    status_unknown = status_error,
#endif
    file_not_found,
    regular_file,
    directory_file,
    // the following may not apply to some operating systems or file systems
    symlink_file,
    block_file,
    character_file,
    fifo_file,
    socket_file,
    reparse_file, // Windows: FILE_ATTRIBUTE_REPARSE_POINT that is not a symlink
    type_unknown  // file does exist, but isn't one of the above types or
                  // we don't have strong enough permission to find its type
};

//--------------------------------------------------------------------------------------//
//                                       perms                                          //
//--------------------------------------------------------------------------------------//

enum perms
{
    no_perms = 0, // file_not_found is no_perms rather than perms_not_known

    // POSIX equivalent macros given in comments.
    // Values are from POSIX and are given in octal per the POSIX standard.

    // permission bits

    owner_read = 0400,  // S_IRUSR, Read permission, owner
    owner_write = 0200, // S_IWUSR, Write permission, owner
    owner_exe = 0100,   // S_IXUSR, Execute/search permission, owner
    owner_all = 0700,   // S_IRWXU, Read, write, execute/search by owner

    group_read = 040,  // S_IRGRP, Read permission, group
    group_write = 020, // S_IWGRP, Write permission, group
    group_exe = 010,   // S_IXGRP, Execute/search permission, group
    group_all = 070,   // S_IRWXG, Read, write, execute/search by group

    others_read = 04,  // S_IROTH, Read permission, others
    others_write = 02, // S_IWOTH, Write permission, others
    others_exe = 01,   // S_IXOTH, Execute/search permission, others
    others_all = 07,   // S_IRWXO, Read, write, execute/search by others

    all_all = 0777, // owner_all|group_all|others_all

    // other POSIX bits

    set_uid_on_exe = 04000, // S_ISUID, Set-user-ID on execution
    set_gid_on_exe = 02000, // S_ISGID, Set-group-ID on execution
    sticky_bit = 01000,     // S_ISVTX,
                            // (POSIX XSI) On directories, restricted deletion flag
                            // (V7) 'sticky bit': save swapped text even after use
                            // (SunOS) On non-directories: don't cache this file
                            // (SVID-v4.2) On directories: restricted deletion flag
                            // Also see http://en.wikipedia.org/wiki/Sticky_bit

    perms_mask = 07777, // all_all|set_uid_on_exe|set_gid_on_exe|sticky_bit

    perms_not_known = 0xFFFF, // present when directory_entry cache not loaded

    // options for permissions() function

    add_perms = 0x1000,    // adds the given permission bits to the current bits
    remove_perms = 0x2000, // removes the given permission bits from the current bits;
                           // choose add_perms or remove_perms, not both; if neither add_perms
                           // nor remove_perms is given, replace the current bits with
                           // the given bits.

    symlink_perms = 0x4000, // on POSIX, don't resolve symlinks; implied on Windows

    // BOOST_BITMASK op~ casts to int32_least_t, producing invalid enum values
    _detail_extend_perms_32_1 = 0x7fffffff,
    _detail_extend_perms_32_2 = -0x7fffffff - 1
};

BOOST_BITMASK(perms)

//--------------------------------------------------------------------------------------//
//                                    file_status                                       //
//--------------------------------------------------------------------------------------//

class file_status
{
public:
    BOOST_CONSTEXPR file_status() BOOST_NOEXCEPT :
        m_value(status_error),
        m_perms(perms_not_known)
    {
    }
    explicit BOOST_CONSTEXPR file_status(file_type v) BOOST_NOEXCEPT :
        m_value(v),
        m_perms(perms_not_known)
    {
    }
    BOOST_CONSTEXPR file_status(file_type v, perms prms) BOOST_NOEXCEPT :
        m_value(v),
        m_perms(prms)
    {
    }

    //  As of October 2015 the interaction between noexcept and =default is so troublesome
    //  for VC++, GCC, and probably other compilers, that =default is not used with noexcept
    //  functions. GCC is not even consistent for the same release on different platforms.

    BOOST_CONSTEXPR file_status(const file_status& rhs) BOOST_NOEXCEPT :
        m_value(rhs.m_value),
        m_perms(rhs.m_perms)
    {
    }
    BOOST_CXX14_CONSTEXPR file_status& operator=(const file_status& rhs) BOOST_NOEXCEPT
    {
        m_value = rhs.m_value;
        m_perms = rhs.m_perms;
        return *this;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    // Note: std::move is not constexpr in C++11, that's why we're not using it here
    BOOST_CONSTEXPR file_status(file_status&& rhs) BOOST_NOEXCEPT :
        m_value(static_cast< file_type&& >(rhs.m_value)),
        m_perms(static_cast< enum perms&& >(rhs.m_perms))
    {
    }
    BOOST_CXX14_CONSTEXPR file_status& operator=(file_status&& rhs) BOOST_NOEXCEPT
    {
        m_value = static_cast< file_type&& >(rhs.m_value);
        m_perms = static_cast< enum perms&& >(rhs.m_perms);
        return *this;
    }
#endif

    // observers
    BOOST_CONSTEXPR file_type type() const BOOST_NOEXCEPT { return m_value; }
    BOOST_CONSTEXPR perms permissions() const BOOST_NOEXCEPT { return m_perms; }

    // modifiers
    BOOST_CXX14_CONSTEXPR void type(file_type v) BOOST_NOEXCEPT { m_value = v; }
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
    file_type m_value;
    enum perms m_perms;
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
    return filesystem::exists(f) && !filesystem::is_regular_file(f) && !filesystem::is_directory(f) && !filesystem::is_symlink(f);
}

#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
inline bool is_regular(file_status f) BOOST_NOEXCEPT
{
    return filesystem::is_regular_file(f);
}
#endif

} // namespace filesystem
} // namespace boost

#include <boost/filesystem/detail/footer.hpp> // pops abi_prefix.hpp pragmas

#endif // BOOST_FILESYSTEM_FILE_STATUS_HPP

/* file_status.hpp
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
*/