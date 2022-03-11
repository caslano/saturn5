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

#ifndef BOOST_FILESYSTEM3_DIRECTORY_HPP
#define BOOST_FILESYSTEM3_DIRECTORY_HPP

#include <boost/config.hpp>

# if defined( BOOST_NO_STD_WSTRING )
#   error Configuration not supported: Boost.Filesystem V3 and later requires std::wstring support
# endif

#include <boost/filesystem/config.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/file_status.hpp>

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

#include <boost/config/abi_prefix.hpp> // must be the last #include

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
  typedef boost::filesystem::path::value_type value_type;   // enables class path ctor taking directory_entry

  directory_entry() BOOST_NOEXCEPT {}
  explicit directory_entry(const boost::filesystem::path& p) :
    m_path(p), m_status(file_status()), m_symlink_status(file_status())
  {
  }
  directory_entry(const boost::filesystem::path& p,
    file_status st, file_status symlink_st = file_status()) :
    m_path(p), m_status(st), m_symlink_status(symlink_st)
  {
  }

  directory_entry(const directory_entry& rhs) :
    m_path(rhs.m_path), m_status(rhs.m_status), m_symlink_status(rhs.m_symlink_status)
  {
  }

  directory_entry& operator=(const directory_entry& rhs)
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
    m_path(std::move(rhs.m_path)), m_status(std::move(rhs.m_status)), m_symlink_status(std::move(rhs.m_symlink_status))
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

  void assign(const boost::filesystem::path& p,
    file_status st = file_status(), file_status symlink_st = file_status())
  {
    m_path = p;
    m_status = st;
    m_symlink_status = symlink_st;
  }

  void replace_filename(const boost::filesystem::path& p,
    file_status st = file_status(), file_status symlink_st = file_status())
  {
    m_path.remove_filename();
    m_path /= p;
    m_status = st;
    m_symlink_status = symlink_st;
  }

# ifndef BOOST_FILESYSTEM_NO_DEPRECATED
  void replace_leaf(const boost::filesystem::path& p, file_status st, file_status symlink_st)
  {
    replace_filename(p, st, symlink_st);
  }
# endif

  const boost::filesystem::path& path() const BOOST_NOEXCEPT { return m_path; }
  operator const boost::filesystem::path&() const BOOST_NOEXCEPT { return m_path; }
  file_status status() const { return get_status(); }
  file_status status(system::error_code& ec) const BOOST_NOEXCEPT { return get_status(&ec); }
  file_status symlink_status() const { return get_symlink_status(); }
  file_status symlink_status(system::error_code& ec) const BOOST_NOEXCEPT { return get_symlink_status(&ec); }

  bool operator==(const directory_entry& rhs) const BOOST_NOEXCEPT { return m_path == rhs.m_path; }
  bool operator!=(const directory_entry& rhs) const BOOST_NOEXCEPT { return m_path != rhs.m_path; }
  bool operator< (const directory_entry& rhs) const BOOST_NOEXCEPT { return m_path < rhs.m_path; }
  bool operator<=(const directory_entry& rhs) const BOOST_NOEXCEPT { return m_path <= rhs.m_path; }
  bool operator> (const directory_entry& rhs) const BOOST_NOEXCEPT { return m_path > rhs.m_path; }
  bool operator>=(const directory_entry& rhs) const BOOST_NOEXCEPT { return m_path >= rhs.m_path; }

private:
  BOOST_FILESYSTEM_DECL file_status get_status(system::error_code* ec=0) const;
  BOOST_FILESYSTEM_DECL file_status get_symlink_status(system::error_code* ec=0) const;

private:
  boost::filesystem::path   m_path;
  mutable file_status       m_status;           // stat()-like
  mutable file_status       m_symlink_status;   // lstat()-like
}; // directory_entry


//--------------------------------------------------------------------------------------//
//                                                                                      //
//                            directory_entry overloads                                 //
//                                                                                      //
//--------------------------------------------------------------------------------------//

//  Without these functions, calling (for example) 'is_directory' with a 'directory_entry' results in:
//  - a conversion to 'path' using 'operator const boost::filesystem::path&()',
//  - then a call to 'is_directory(const path& p)' which recomputes the status with 'detail::status(p)'.
//
//  These functions avoid a costly recomputation of the status if one calls 'is_directory(e)' instead of 'is_directory(e.status)'

inline file_status status         (const directory_entry& e) BOOST_NOEXCEPT { return e.status(); }
inline bool        type_present   (const directory_entry& e) BOOST_NOEXCEPT { return filesystem::type_present(e.status()); }
inline bool        status_known   (const directory_entry& e) BOOST_NOEXCEPT { return filesystem::status_known(e.status()); }
inline bool        exists         (const directory_entry& e) BOOST_NOEXCEPT { return filesystem::exists(e.status()); }
inline bool        is_regular_file(const directory_entry& e) BOOST_NOEXCEPT { return filesystem::is_regular_file(e.status()); }
inline bool        is_directory   (const directory_entry& e) BOOST_NOEXCEPT { return filesystem::is_directory(e.status()); }
inline bool        is_symlink     (const directory_entry& e) BOOST_NOEXCEPT { return filesystem::is_symlink(e.status()); }
inline bool        is_other       (const directory_entry& e) BOOST_NOEXCEPT { return filesystem::is_other(e.status()); }
#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
inline bool        is_regular     (const directory_entry& e) BOOST_NOEXCEPT { return filesystem::is_regular(e.status()); }
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
  _detail_no_push = 1u << 4           // internal use only
}
BOOST_SCOPED_ENUM_DECLARE_END(directory_options)

BOOST_BITMASK(BOOST_SCOPED_ENUM_NATIVE(directory_options))

class directory_iterator;

namespace detail {

BOOST_FILESYSTEM_DECL
system::error_code dir_itr_close(// never throws()
  void*& handle
#if defined(BOOST_POSIX_API)
  , void*& buffer
#endif
) BOOST_NOEXCEPT;

struct dir_itr_imp :
  public boost::intrusive_ref_counter< dir_itr_imp >
{
  directory_entry  dir_entry;
  void*            handle;

#if defined(BOOST_POSIX_API)
  void*            buffer;  // see dir_itr_increment implementation
#endif

  dir_itr_imp() BOOST_NOEXCEPT :
    handle(0)
#if defined(BOOST_POSIX_API)
    , buffer(0)
#endif
  {
  }

  ~dir_itr_imp() BOOST_NOEXCEPT
  {
    dir_itr_close(handle
#if defined(BOOST_POSIX_API)
       , buffer
#endif
    );
  }
};

// see path::iterator: comment below
BOOST_FILESYSTEM_DECL void directory_iterator_construct(directory_iterator& it, const path& p, unsigned int opts, system::error_code* ec);
BOOST_FILESYSTEM_DECL void directory_iterator_increment(directory_iterator& it, system::error_code* ec);

}  // namespace detail

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

  friend BOOST_FILESYSTEM_DECL void detail::directory_iterator_construct(directory_iterator& it, const path& p, unsigned int opts, system::error_code* ec);
  friend BOOST_FILESYSTEM_DECL void detail::directory_iterator_increment(directory_iterator& it, system::error_code* ec);

public:
  directory_iterator() BOOST_NOEXCEPT {}  // creates the "end" iterator

  // iterator_facade derived classes don't seem to like implementations in
  // separate translation unit dll's, so forward to detail functions
  explicit directory_iterator(const path& p, BOOST_SCOPED_ENUM_NATIVE(directory_options) opts = directory_options::none)
  {
    detail::directory_iterator_construct(*this, p, static_cast< unsigned int >(opts), 0);
  }

  directory_iterator(const path& p, system::error_code& ec) BOOST_NOEXCEPT
  {
    detail::directory_iterator_construct(*this, p, static_cast< unsigned int >(directory_options::none), &ec);
  }

  directory_iterator(const path& p, BOOST_SCOPED_ENUM_NATIVE(directory_options) opts, system::error_code& ec) BOOST_NOEXCEPT
  {
    detail::directory_iterator_construct(*this, p, static_cast< unsigned int >(opts), &ec);
  }

  BOOST_DEFAULTED_FUNCTION(directory_iterator(directory_iterator const& that), : m_imp(that.m_imp) {})
  BOOST_DEFAULTED_FUNCTION(directory_iterator& operator= (directory_iterator const& that), { m_imp = that.m_imp; return *this; })

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  directory_iterator(directory_iterator&& that) BOOST_NOEXCEPT :
    m_imp(std::move(that.m_imp))
  {
  }

  directory_iterator& operator= (directory_iterator&& that) BOOST_NOEXCEPT
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

  bool equal(const directory_iterator& rhs) const BOOST_NOEXCEPT
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

//  begin() and end() are only used by a range-based for statement in the context of
//  auto - thus the top-level const is stripped - so returning const is harmless and
//  emphasizes begin() is just a pass through.
inline const directory_iterator& begin(const directory_iterator& iter) BOOST_NOEXCEPT { return iter; }
inline directory_iterator end(const directory_iterator&) BOOST_NOEXCEPT { return directory_iterator(); }

// enable C++14 generic accessors for range const iterators
inline const directory_iterator& cbegin(const directory_iterator& iter) BOOST_NOEXCEPT { return iter; }
inline directory_iterator cend(const directory_iterator&) BOOST_NOEXCEPT { return directory_iterator(); }

//  enable directory_iterator BOOST_FOREACH  -----------------------------------------//

inline directory_iterator& range_begin(directory_iterator& iter) BOOST_NOEXCEPT { return iter; }
inline directory_iterator range_begin(const directory_iterator& iter) BOOST_NOEXCEPT { return iter; }
inline directory_iterator range_end(directory_iterator&) BOOST_NOEXCEPT { return directory_iterator(); }
inline directory_iterator range_end(const directory_iterator&) BOOST_NOEXCEPT { return directory_iterator(); }

} // namespace filesystem

//  namespace boost template specializations
template<typename C, typename Enabler>
struct range_mutable_iterator;

template<>
struct range_mutable_iterator<boost::filesystem::directory_iterator, void>
{
  typedef boost::filesystem::directory_iterator type;
};

template<typename C, typename Enabler>
struct range_const_iterator;

template<>
struct range_const_iterator<boost::filesystem::directory_iterator, void>
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
  no_recurse = none,                                                                      // don't follow directory symlinks (default behavior)
  recurse = static_cast< unsigned int >(directory_options::follow_directory_symlink),     // follow directory symlinks
  _detail_no_push = static_cast< unsigned int >(directory_options::_detail_no_push)       // internal use only
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

BOOST_FILESYSTEM_DECL void recursive_directory_iterator_construct(recursive_directory_iterator& it, const path& dir_path, unsigned int opts, system::error_code* ec);
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

  friend BOOST_FILESYSTEM_DECL void detail::recursive_directory_iterator_construct(recursive_directory_iterator& it, const path& dir_path, unsigned int opts, system::error_code* ec);
  friend BOOST_FILESYSTEM_DECL void detail::recursive_directory_iterator_increment(recursive_directory_iterator& it, system::error_code* ec);
  friend BOOST_FILESYSTEM_DECL void detail::recursive_directory_iterator_pop(recursive_directory_iterator& it, system::error_code* ec);

public:
  recursive_directory_iterator() BOOST_NOEXCEPT {}  // creates the "end" iterator

  explicit recursive_directory_iterator(const path& dir_path)
  {
    detail::recursive_directory_iterator_construct(*this, dir_path, static_cast< unsigned int >(directory_options::none), 0);
  }

  recursive_directory_iterator(const path& dir_path, system::error_code& ec)
  {
    detail::recursive_directory_iterator_construct(*this, dir_path, static_cast< unsigned int >(directory_options::none), &ec);
  }

  recursive_directory_iterator(const path& dir_path, BOOST_SCOPED_ENUM_NATIVE(directory_options) opts)
  {
    detail::recursive_directory_iterator_construct(*this, dir_path, static_cast< unsigned int >(opts), 0);
  }

  recursive_directory_iterator(const path& dir_path, BOOST_SCOPED_ENUM_NATIVE(directory_options) opts, system::error_code& ec)
  {
    detail::recursive_directory_iterator_construct(*this, dir_path, static_cast< unsigned int >(opts), &ec);
  }

#if !defined(BOOST_FILESYSTEM_NO_DEPRECATED)
  // Deprecated constructors
  recursive_directory_iterator(const path& dir_path, BOOST_SCOPED_ENUM_NATIVE(symlink_option) opts)
  {
    detail::recursive_directory_iterator_construct(*this, dir_path, static_cast< unsigned int >(opts), 0);
  }

  recursive_directory_iterator(const path& dir_path, BOOST_SCOPED_ENUM_NATIVE(symlink_option) opts, system::error_code& ec) BOOST_NOEXCEPT
  {
    detail::recursive_directory_iterator_construct(*this, dir_path, static_cast< unsigned int >(opts), &ec);
  }
#endif // BOOST_FILESYSTEM_NO_DEPRECATED

  BOOST_DEFAULTED_FUNCTION(recursive_directory_iterator(recursive_directory_iterator const& that), : m_imp(that.m_imp) {})
  BOOST_DEFAULTED_FUNCTION(recursive_directory_iterator& operator= (recursive_directory_iterator const& that), { m_imp = that.m_imp; return *this; })

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  recursive_directory_iterator(recursive_directory_iterator&& that) BOOST_NOEXCEPT :
    m_imp(std::move(that.m_imp))
  {
  }

  recursive_directory_iterator& operator= (recursive_directory_iterator&& that) BOOST_NOEXCEPT
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
  int level() const BOOST_NOEXCEPT { return depth(); }
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
  void no_push(bool value = true) BOOST_NOEXCEPT { disable_recursion_pending(value); }
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

  bool equal(const recursive_directory_iterator& rhs) const BOOST_NOEXCEPT
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

//  begin() and end() are only used by a range-based for statement in the context of
//  auto - thus the top-level const is stripped - so returning const is harmless and
//  emphasizes begin() is just a pass through.
inline const recursive_directory_iterator& begin(const recursive_directory_iterator& iter) BOOST_NOEXCEPT { return iter; }
inline recursive_directory_iterator end(const recursive_directory_iterator&) BOOST_NOEXCEPT { return recursive_directory_iterator(); }

// enable C++14 generic accessors for range const iterators
inline const recursive_directory_iterator& cbegin(const recursive_directory_iterator& iter) BOOST_NOEXCEPT { return iter; }
inline recursive_directory_iterator cend(const recursive_directory_iterator&) BOOST_NOEXCEPT { return recursive_directory_iterator(); }

//  enable recursive directory iterator BOOST_FOREACH  -------------------------------//

inline recursive_directory_iterator& range_begin(recursive_directory_iterator& iter) BOOST_NOEXCEPT { return iter; }
inline recursive_directory_iterator range_begin(const recursive_directory_iterator& iter) BOOST_NOEXCEPT { return iter; }
inline recursive_directory_iterator range_end(recursive_directory_iterator&) BOOST_NOEXCEPT { return recursive_directory_iterator(); }
inline recursive_directory_iterator range_end(const recursive_directory_iterator&) BOOST_NOEXCEPT { return recursive_directory_iterator(); }

} // namespace filesystem

//  namespace boost template specializations
template<>
struct range_mutable_iterator<boost::filesystem::recursive_directory_iterator, void>
{
  typedef boost::filesystem::recursive_directory_iterator type;
};
template<>
struct range_const_iterator<boost::filesystem::recursive_directory_iterator, void>
{
  typedef boost::filesystem::recursive_directory_iterator type;
};

} // namespace boost

#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#endif // BOOST_FILESYSTEM3_DIRECTORY_HPP

/* directory.hpp
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
*/