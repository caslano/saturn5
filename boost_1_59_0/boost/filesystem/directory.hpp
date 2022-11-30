//  boost/filesystem/directory.hpp  ---------------------------------------------------//

//  Copyright Beman Dawes 2002-2009
//  Copyright Jan Langer 2002
//  Copyright Dietmar Kuehl 2001
//  Copyright Vladimir Prus 2002
//  Copyright Andrey Semashev 2019

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

//--------------------------------------------------------------------------------------//

#ifndef BOOST_FILESYSTEM_DIRECTORY_HPP
#define BOOST_FILESYSTEM_DIRECTORY_HPP

#include <boost/filesystem/config.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/file_status.hpp>

#include <cstddef>
#include <string>
#include <vector>
#include <utility> // std::move

#include <boost/assert.hpp>
#include <boost/core/scoped_enum.hpp>
#include <boost/detail/bitmask.hpp>
#include <boost/system/error_code.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/smart_ptr/intrusive_ref_counter.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <boost/filesystem/detail/header.hpp> // must be the last #include

//--------------------------------------------------------------------------------------//

namespace boost {
namespace filesystem {

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                 directory_entry                                      //
//                                                                                      //
//--------------------------------------------------------------------------------------//

//  GCC has a problem with a member function named path within a namespace or
//  sub-namespace that also has a class named path. The workaround is to always
//  fully qualify the name path when it refers to the class name.

class directory_entry
{
public:
    typedef boost::filesystem::path::value_type value_type; // enables class path ctor taking directory_entry

    directory_entry() BOOST_NOEXCEPT {}

    explicit directory_entry(boost::filesystem::path const& p) :
        m_path(p), m_status(file_status()), m_symlink_status(file_status())
    {
    }

    directory_entry(boost::filesystem::path const& p, file_status st, file_status symlink_st = file_status()) :
        m_path(p), m_status(st), m_symlink_status(symlink_st)
    {
    }

    directory_entry(directory_entry const& rhs) :
        m_path(rhs.m_path), m_status(rhs.m_status), m_symlink_status(rhs.m_symlink_status)
    {
    }

    directory_entry& operator=(directory_entry const& rhs)
    {
        m_path = rhs.m_path;
        m_status = rhs.m_status;
        m_symlink_status = rhs.m_symlink_status;
        return *this;
    }

    //  As of October 2015 the interaction between noexcept and =default is so troublesome
    //  for VC++, GCC, and probably other compilers, that =default is not used with noexcept
    //  functions. GCC is not even consistent for the same release on different platforms.

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    directory_entry(directory_entry&& rhs) BOOST_NOEXCEPT :
        m_path(std::move(rhs.m_path)),
        m_status(std::move(rhs.m_status)),
        m_symlink_status(std::move(rhs.m_symlink_status))
    {
    }

    directory_entry& operator=(directory_entry&& rhs) BOOST_NOEXCEPT
    {
        m_path = std::move(rhs.m_path);
        m_status = std::move(rhs.m_status);
        m_symlink_status = std::move(rhs.m_symlink_status);
        return *this;
    }
#endif

    void assign(boost::filesystem::path const& p, file_status st = file_status(), file_status symlink_st = file_status())
    {
        m_path = p;
        m_status = st;
        m_symlink_status = symlink_st;
    }

    void replace_filename(boost::filesystem::path const& p, file_status st = file_status(), file_status symlink_st = file_status())
    {
        m_path.remove_filename();
        m_path /= p;
        m_status = st;
        m_symlink_status = symlink_st;
    }

#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
    void replace_leaf(boost::filesystem::path const& p, file_status st, file_status symlink_st)
    {
        replace_filename(p, st, symlink_st);
    }
#endif

    boost::filesystem::path const& path() const BOOST_NOEXCEPT
    {
        return m_path;
    }
    operator boost::filesystem::path const&() const BOOST_NOEXCEPT { return m_path; }
    file_status status() const { return get_status(); }
    file_status status(system::error_code& ec) const BOOST_NOEXCEPT { return get_status(&ec); }
    file_status symlink_status() const { return get_symlink_status(); }
    file_status symlink_status(system::error_code& ec) const BOOST_NOEXCEPT { return get_symlink_status(&ec); }

    bool operator==(directory_entry const& rhs) const BOOST_NOEXCEPT { return m_path == rhs.m_path; }
    bool operator!=(directory_entry const& rhs) const BOOST_NOEXCEPT { return m_path != rhs.m_path; }
    bool operator<(directory_entry const& rhs) const BOOST_NOEXCEPT { return m_path < rhs.m_path; }
    bool operator<=(directory_entry const& rhs) const BOOST_NOEXCEPT { return m_path <= rhs.m_path; }
    bool operator>(directory_entry const& rhs) const BOOST_NOEXCEPT { return m_path > rhs.m_path; }
    bool operator>=(directory_entry const& rhs) const BOOST_NOEXCEPT { return m_path >= rhs.m_path; }

private:
    BOOST_FILESYSTEM_DECL file_status get_status(system::error_code* ec = 0) const;
    BOOST_FILESYSTEM_DECL file_status get_symlink_status(system::error_code* ec = 0) const;

private:
    boost::filesystem::path m_path;
    mutable file_status m_status;         // stat()-like
    mutable file_status m_symlink_status; // lstat()-like
};                                        // directory_entry

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                            directory_entry overloads                                 //
//                                                                                      //
//--------------------------------------------------------------------------------------//

//  Without these functions, calling (for example) 'is_directory' with a 'directory_entry' results in:
//  - a conversion to 'path' using 'operator boost::filesystem::path const&()',
//  - then a call to 'is_directory(path const& p)' which recomputes the status with 'detail::status(p)'.
//
//  These functions avoid a costly recomputation of the status if one calls 'is_directory(e)' instead of 'is_directory(e.status())'

inline file_status status(directory_entry const& e)
{
    return e.status();
}
inline file_status status(directory_entry const& e, system::error_code& ec) BOOST_NOEXCEPT
{
    return e.status(ec);
}
inline bool type_present(directory_entry const& e)
{
    return filesystem::type_present(e.status());
}
inline bool type_present(directory_entry const& e, system::error_code& ec) BOOST_NOEXCEPT
{
    return filesystem::type_present(e.status(ec));
}
inline bool status_known(directory_entry const& e)
{
    return filesystem::status_known(e.status());
}
inline bool status_known(directory_entry const& e, system::error_code& ec) BOOST_NOEXCEPT
{
    return filesystem::status_known(e.status(ec));
}
inline bool exists(directory_entry const& e)
{
    return filesystem::exists(e.status());
}
inline bool exists(directory_entry const& e, system::error_code& ec) BOOST_NOEXCEPT
{
    return filesystem::exists(e.status(ec));
}
inline bool is_regular_file(directory_entry const& e)
{
    return filesystem::is_regular_file(e.status());
}
inline bool is_regular_file(directory_entry const& e, system::error_code& ec) BOOST_NOEXCEPT
{
    return filesystem::is_regular_file(e.status(ec));
}
inline bool is_directory(directory_entry const& e)
{
    return filesystem::is_directory(e.status());
}
inline bool is_directory(directory_entry const& e, system::error_code& ec) BOOST_NOEXCEPT
{
    return filesystem::is_directory(e.status(ec));
}
inline bool is_symlink(directory_entry const& e)
{
    return filesystem::is_symlink(e.symlink_status());
}
inline bool is_symlink(directory_entry const& e, system::error_code& ec) BOOST_NOEXCEPT
{
    return filesystem::is_symlink(e.symlink_status(ec));
}
inline bool is_other(directory_entry const& e)
{
    return filesystem::is_other(e.status());
}
inline bool is_other(directory_entry const& e, system::error_code& ec) BOOST_NOEXCEPT
{
    return filesystem::is_other(e.status(ec));
}
#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
inline bool is_regular(directory_entry const& e)
{
    return filesystem::is_regular(e.status());
}
#endif

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                            directory_iterator helpers                                //
//                                                                                      //
//--------------------------------------------------------------------------------------//

BOOST_SCOPED_ENUM_UT_DECLARE_BEGIN(directory_options, unsigned int)
{
    none = 0u,
    skip_permission_denied = 1u,        // if a directory cannot be opened because of insufficient permissions, pretend that the directory is empty
    follow_directory_symlink = 1u << 1, // recursive_directory_iterator: follow directory symlinks
    skip_dangling_symlinks = 1u << 2,   // non-standard extension for recursive_directory_iterator: don't follow dangling directory symlinks,
    pop_on_error = 1u << 3,             // non-standard extension for recursive_directory_iterator: instead of producing an end iterator on errors,
                                        // repeatedly invoke pop() until it succeeds or the iterator becomes equal to end iterator
    _detail_no_follow = 1u << 4,        // internal use only
    _detail_no_push = 1u << 5           // internal use only
}
BOOST_SCOPED_ENUM_DECLARE_END(directory_options)

BOOST_BITMASK(BOOST_SCOPED_ENUM_NATIVE(directory_options))

class directory_iterator;

namespace detail {

struct dir_itr_imp :
    public boost::intrusive_ref_counter< dir_itr_imp >
{
#ifdef BOOST_WINDOWS_API
    unsigned char extra_data_format;
    std::size_t current_offset;
#endif
    directory_entry dir_entry;
    void* handle;

    dir_itr_imp() BOOST_NOEXCEPT :
#ifdef BOOST_WINDOWS_API
        extra_data_format(0u),
        current_offset(0u),
#endif
        handle(NULL)
    {
    }
    BOOST_FILESYSTEM_DECL ~dir_itr_imp() BOOST_NOEXCEPT;

    BOOST_FILESYSTEM_DECL static void* operator new(std::size_t class_size, std::size_t extra_size) BOOST_NOEXCEPT;
    BOOST_FILESYSTEM_DECL static void operator delete(void* p, std::size_t extra_size) BOOST_NOEXCEPT;
    BOOST_FILESYSTEM_DECL static void operator delete(void* p) BOOST_NOEXCEPT;
};

BOOST_FILESYSTEM_DECL void directory_iterator_construct(directory_iterator& it, path const& p, unsigned int opts, system::error_code* ec);
BOOST_FILESYSTEM_DECL void directory_iterator_increment(directory_iterator& it, system::error_code* ec);

} // namespace detail

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                directory_iterator                                    //
//                                                                                      //
//--------------------------------------------------------------------------------------//

class directory_iterator :
    public boost::iterator_facade<
        directory_iterator,
        directory_entry,
        boost::single_pass_traversal_tag
    >
{
    friend class boost::iterator_core_access;

    friend BOOST_FILESYSTEM_DECL void detail::directory_iterator_construct(directory_iterator& it, path const& p, unsigned int opts, system::error_code* ec);
    friend BOOST_FILESYSTEM_DECL void detail::directory_iterator_increment(directory_iterator& it, system::error_code* ec);

public:
    directory_iterator() BOOST_NOEXCEPT {} // creates the "end" iterator

    // iterator_facade derived classes don't seem to like implementations in
    // separate translation unit dll's, so forward to detail functions
    explicit directory_iterator(path const& p, BOOST_SCOPED_ENUM_NATIVE(directory_options) opts = directory_options::none)
    {
        detail::directory_iterator_construct(*this, p, static_cast< unsigned int >(opts), 0);
    }

    directory_iterator(path const& p, system::error_code& ec) BOOST_NOEXCEPT
    {
        detail::directory_iterator_construct(*this, p, static_cast< unsigned int >(directory_options::none), &ec);
    }

    directory_iterator(path const& p, BOOST_SCOPED_ENUM_NATIVE(directory_options) opts, system::error_code& ec) BOOST_NOEXCEPT
    {
        detail::directory_iterator_construct(*this, p, static_cast< unsigned int >(opts), &ec);
    }

    BOOST_DEFAULTED_FUNCTION(directory_iterator(directory_iterator const& that), : m_imp(that.m_imp) {})
    BOOST_DEFAULTED_FUNCTION(directory_iterator& operator=(directory_iterator const& that), { m_imp = that.m_imp; return *this; })

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    directory_iterator(directory_iterator&& that) BOOST_NOEXCEPT :
        m_imp(std::move(that.m_imp))
    {
    }

    directory_iterator& operator=(directory_iterator&& that) BOOST_NOEXCEPT
    {
        m_imp = std::move(that.m_imp);
        return *this;
    }
#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    directory_iterator& increment(system::error_code& ec) BOOST_NOEXCEPT
    {
        detail::directory_iterator_increment(*this, &ec);
        return *this;
    }

private:
    boost::iterator_facade<
        directory_iterator,
        directory_entry,
        boost::single_pass_traversal_tag
    >::reference dereference() const
    {
        BOOST_ASSERT_MSG(!is_end(), "attempt to dereference end directory iterator");
        return m_imp->dir_entry;
    }

    void increment() { detail::directory_iterator_increment(*this, 0); }

    bool equal(directory_iterator const& rhs) const BOOST_NOEXCEPT
    {
        return m_imp == rhs.m_imp || (is_end() && rhs.is_end());
    }

    bool is_end() const BOOST_NOEXCEPT
    {
        // Note: The check for handle is needed because the iterator can be copied and the copy
        // can be incremented to end while the original iterator still refers to the same dir_itr_imp.
        return !m_imp || !m_imp->handle;
    }

private:
    // intrusive_ptr provides the shallow-copy semantics required for single pass iterators
    // (i.e. InputIterators). The end iterator is indicated by is_end().
    boost::intrusive_ptr< detail::dir_itr_imp > m_imp;
};

//  enable directory_iterator C++11 range-based for statement use  --------------------//

// begin() and end() are only used by a range-based for statement in the context of
// auto - thus the top-level const is stripped - so returning const is harmless and
// emphasizes begin() is just a pass through.
inline directory_iterator const& begin(directory_iterator const& iter) BOOST_NOEXCEPT
{
    return iter;
}

inline directory_iterator end(directory_iterator const&) BOOST_NOEXCEPT
{
    return directory_iterator();
}

// enable C++14 generic accessors for range const iterators
inline directory_iterator const& cbegin(directory_iterator const& iter) BOOST_NOEXCEPT
{
    return iter;
}

inline directory_iterator cend(directory_iterator const&) BOOST_NOEXCEPT
{
    return directory_iterator();
}

//  enable directory_iterator BOOST_FOREACH  -----------------------------------------//

inline directory_iterator& range_begin(directory_iterator& iter) BOOST_NOEXCEPT
{
    return iter;
}

inline directory_iterator range_begin(directory_iterator const& iter) BOOST_NOEXCEPT
{
    return iter;
}

inline directory_iterator range_end(directory_iterator&) BOOST_NOEXCEPT
{
    return directory_iterator();
}

inline directory_iterator range_end(directory_iterator const&) BOOST_NOEXCEPT
{
    return directory_iterator();
}

} // namespace filesystem

//  namespace boost template specializations
template< typename C, typename Enabler >
struct range_mutable_iterator;

template<>
struct range_mutable_iterator< boost::filesystem::directory_iterator, void >
{
    typedef boost::filesystem::directory_iterator type;
};

template< typename C, typename Enabler >
struct range_const_iterator;

template<>
struct range_const_iterator< boost::filesystem::directory_iterator, void >
{
    typedef boost::filesystem::directory_iterator type;
};

namespace filesystem {

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                      recursive_directory_iterator helpers                            //
//                                                                                      //
//--------------------------------------------------------------------------------------//

#if !defined(BOOST_FILESYSTEM_NO_DEPRECATED)
// Deprecated enum, use directory_options instead
BOOST_SCOPED_ENUM_UT_DECLARE_BEGIN(symlink_option, unsigned int)
{
    none = static_cast< unsigned int >(directory_options::none),
    no_recurse = none,                                                                  // don't follow directory symlinks (default behavior)
    recurse = static_cast< unsigned int >(directory_options::follow_directory_symlink), // follow directory symlinks
    _detail_no_push = static_cast< unsigned int >(directory_options::_detail_no_push)   // internal use only
}
BOOST_SCOPED_ENUM_DECLARE_END(symlink_option)

BOOST_BITMASK(BOOST_SCOPED_ENUM_NATIVE(symlink_option))
#endif // BOOST_FILESYSTEM_NO_DEPRECATED

class recursive_directory_iterator;

namespace detail {

struct recur_dir_itr_imp :
    public boost::intrusive_ref_counter< recur_dir_itr_imp >
{
    typedef directory_iterator element_type;
    std::vector< element_type > m_stack;
    // directory_options values, declared as unsigned int for ABI compatibility
    unsigned int m_options;

    explicit recur_dir_itr_imp(unsigned int opts) BOOST_NOEXCEPT : m_options(opts) {}
};

BOOST_FILESYSTEM_DECL void recursive_directory_iterator_construct(recursive_directory_iterator& it, path const& dir_path, unsigned int opts, system::error_code* ec);
BOOST_FILESYSTEM_DECL void recursive_directory_iterator_increment(recursive_directory_iterator& it, system::error_code* ec);
BOOST_FILESYSTEM_DECL void recursive_directory_iterator_pop(recursive_directory_iterator& it, system::error_code* ec);

} // namespace detail

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                           recursive_directory_iterator                               //
//                                                                                      //
//--------------------------------------------------------------------------------------//

class recursive_directory_iterator :
    public boost::iterator_facade<
        recursive_directory_iterator,
        directory_entry,
        boost::single_pass_traversal_tag
    >
{
    friend class boost::iterator_core_access;

    friend BOOST_FILESYSTEM_DECL void detail::recursive_directory_iterator_construct(recursive_directory_iterator& it, path const& dir_path, unsigned int opts, system::error_code* ec);
    friend BOOST_FILESYSTEM_DECL void detail::recursive_directory_iterator_increment(recursive_directory_iterator& it, system::error_code* ec);
    friend BOOST_FILESYSTEM_DECL void detail::recursive_directory_iterator_pop(recursive_directory_iterator& it, system::error_code* ec);

public:
    recursive_directory_iterator() BOOST_NOEXCEPT {} // creates the "end" iterator

    explicit recursive_directory_iterator(path const& dir_path)
    {
        detail::recursive_directory_iterator_construct(*this, dir_path, static_cast< unsigned int >(directory_options::none), 0);
    }

    recursive_directory_iterator(path const& dir_path, system::error_code& ec)
    {
        detail::recursive_directory_iterator_construct(*this, dir_path, static_cast< unsigned int >(directory_options::none), &ec);
    }

    recursive_directory_iterator(path const& dir_path, BOOST_SCOPED_ENUM_NATIVE(directory_options) opts)
    {
        detail::recursive_directory_iterator_construct(*this, dir_path, static_cast< unsigned int >(opts), 0);
    }

    recursive_directory_iterator(path const& dir_path, BOOST_SCOPED_ENUM_NATIVE(directory_options) opts, system::error_code& ec)
    {
        detail::recursive_directory_iterator_construct(*this, dir_path, static_cast< unsigned int >(opts), &ec);
    }

#if !defined(BOOST_FILESYSTEM_NO_DEPRECATED)
    // Deprecated constructors
    recursive_directory_iterator(path const& dir_path, BOOST_SCOPED_ENUM_NATIVE(symlink_option) opts)
    {
        detail::recursive_directory_iterator_construct(*this, dir_path, static_cast< unsigned int >(opts), 0);
    }

    recursive_directory_iterator(path const& dir_path, BOOST_SCOPED_ENUM_NATIVE(symlink_option) opts, system::error_code& ec) BOOST_NOEXCEPT
    {
        detail::recursive_directory_iterator_construct(*this, dir_path, static_cast< unsigned int >(opts), &ec);
    }
#endif // BOOST_FILESYSTEM_NO_DEPRECATED

    BOOST_DEFAULTED_FUNCTION(recursive_directory_iterator(recursive_directory_iterator const& that), : m_imp(that.m_imp) {})
    BOOST_DEFAULTED_FUNCTION(recursive_directory_iterator& operator=(recursive_directory_iterator const& that), { m_imp = that.m_imp; return *this; })

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    recursive_directory_iterator(recursive_directory_iterator&& that) BOOST_NOEXCEPT :
        m_imp(std::move(that.m_imp))
    {
    }

    recursive_directory_iterator& operator=(recursive_directory_iterator&& that) BOOST_NOEXCEPT
    {
        m_imp = std::move(that.m_imp);
        return *this;
    }
#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    recursive_directory_iterator& increment(system::error_code& ec) BOOST_NOEXCEPT
    {
        detail::recursive_directory_iterator_increment(*this, &ec);
        return *this;
    }

    int depth() const BOOST_NOEXCEPT
    {
        BOOST_ASSERT_MSG(!is_end(), "depth() on end recursive_directory_iterator");
        return static_cast< int >(m_imp->m_stack.size() - 1u);
    }

    bool recursion_pending() const BOOST_NOEXCEPT
    {
        BOOST_ASSERT_MSG(!is_end(), "recursion_pending() on end recursive_directory_iterator");
        return (m_imp->m_options & static_cast< unsigned int >(directory_options::_detail_no_push)) == 0u;
    }

#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
    int level() const BOOST_NOEXCEPT
    {
        return depth();
    }
    bool no_push_pending() const BOOST_NOEXCEPT { return !recursion_pending(); }
    bool no_push_request() const BOOST_NOEXCEPT { return !recursion_pending(); }
#endif

    void pop()
    {
        detail::recursive_directory_iterator_pop(*this, 0);
    }

    void pop(system::error_code& ec) BOOST_NOEXCEPT
    {
        detail::recursive_directory_iterator_pop(*this, &ec);
    }

    void disable_recursion_pending(bool value = true) BOOST_NOEXCEPT
    {
        BOOST_ASSERT_MSG(!is_end(), "disable_recursion_pending() on end recursive_directory_iterator");
        if (value)
            m_imp->m_options |= static_cast< unsigned int >(directory_options::_detail_no_push);
        else
            m_imp->m_options &= ~static_cast< unsigned int >(directory_options::_detail_no_push);
    }

#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
    void no_push(bool value = true) BOOST_NOEXCEPT
    {
        disable_recursion_pending(value);
    }
#endif

    file_status status() const
    {
        BOOST_ASSERT_MSG(!is_end(), "status() on end recursive_directory_iterator");
        return m_imp->m_stack.back()->status();
    }

    file_status symlink_status() const
    {
        BOOST_ASSERT_MSG(!is_end(), "symlink_status() on end recursive_directory_iterator");
        return m_imp->m_stack.back()->symlink_status();
    }

private:
    boost::iterator_facade<
        recursive_directory_iterator,
        directory_entry,
        boost::single_pass_traversal_tag
    >::reference dereference() const
    {
        BOOST_ASSERT_MSG(!is_end(), "dereference of end recursive_directory_iterator");
        return *m_imp->m_stack.back();
    }

    void increment() { detail::recursive_directory_iterator_increment(*this, 0); }

    bool equal(recursive_directory_iterator const& rhs) const BOOST_NOEXCEPT
    {
        return m_imp == rhs.m_imp || (is_end() && rhs.is_end());
    }

    bool is_end() const BOOST_NOEXCEPT
    {
        // Note: The check for m_stack.empty() is needed because the iterator can be copied and the copy
        // can be incremented to end while the original iterator still refers to the same recur_dir_itr_imp.
        return !m_imp || m_imp->m_stack.empty();
    }

private:
    // intrusive_ptr provides the shallow-copy semantics required for single pass iterators
    // (i.e. InputIterators). The end iterator is indicated by is_end().
    boost::intrusive_ptr< detail::recur_dir_itr_imp > m_imp;
};

#if !defined(BOOST_FILESYSTEM_NO_DEPRECATED)
typedef recursive_directory_iterator wrecursive_directory_iterator;
#endif

//  enable recursive directory iterator C++11 range-base for statement use  ----------//

// begin() and end() are only used by a range-based for statement in the context of
// auto - thus the top-level const is stripped - so returning const is harmless and
// emphasizes begin() is just a pass through.
inline recursive_directory_iterator const& begin(recursive_directory_iterator const& iter) BOOST_NOEXCEPT
{
    return iter;
}

inline recursive_directory_iterator end(recursive_directory_iterator const&) BOOST_NOEXCEPT
{
    return recursive_directory_iterator();
}

// enable C++14 generic accessors for range const iterators
inline recursive_directory_iterator const& cbegin(recursive_directory_iterator const& iter) BOOST_NOEXCEPT
{
    return iter;
}

inline recursive_directory_iterator cend(recursive_directory_iterator const&) BOOST_NOEXCEPT
{
    return recursive_directory_iterator();
}

//  enable recursive directory iterator BOOST_FOREACH  -------------------------------//

inline recursive_directory_iterator& range_begin(recursive_directory_iterator& iter) BOOST_NOEXCEPT
{
    return iter;
}

inline recursive_directory_iterator range_begin(recursive_directory_iterator const& iter) BOOST_NOEXCEPT
{
    return iter;
}

inline recursive_directory_iterator range_end(recursive_directory_iterator&) BOOST_NOEXCEPT
{
    return recursive_directory_iterator();
}

inline recursive_directory_iterator range_end(recursive_directory_iterator const&) BOOST_NOEXCEPT
{
    return recursive_directory_iterator();
}

} // namespace filesystem

//  namespace boost template specializations
template<>
struct range_mutable_iterator< boost::filesystem::recursive_directory_iterator, void >
{
    typedef boost::filesystem::recursive_directory_iterator type;
};

template<>
struct range_const_iterator< boost::filesystem::recursive_directory_iterator, void >
{
    typedef boost::filesystem::recursive_directory_iterator type;
};

} // namespace boost

#include <boost/filesystem/detail/footer.hpp>

#endif // BOOST_FILESYSTEM_DIRECTORY_HPP

/* directory.hpp
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
*/