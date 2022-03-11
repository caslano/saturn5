//  filesystem path.hpp  ---------------------------------------------------------------//

//  Copyright Beman Dawes 2002-2005, 2009
//  Copyright Vladimir Prus 2002

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

//  path::stem(), extension(), and replace_extension() are based on
//  basename(), extension(), and change_extension() from the original
//  filesystem/convenience.hpp header by Vladimir Prus.

#ifndef BOOST_FILESYSTEM_PATH_HPP
#define BOOST_FILESYSTEM_PATH_HPP

#include <boost/config.hpp>

# if defined( BOOST_NO_STD_WSTRING )
#   error Configuration not supported: Boost.Filesystem V3 and later requires std::wstring support
# endif

#include <boost/assert.hpp>
#include <boost/filesystem/config.hpp>
#include <boost/filesystem/path_traits.hpp>  // includes <cwchar>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/io/quoted.hpp>
#include <boost/functional/hash_fwd.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <string>
#include <iterator>
#include <cstring>
#include <iosfwd>
#include <stdexcept>
#include <cassert>
#include <locale>
#include <algorithm>

#include <boost/config/abi_prefix.hpp> // must be the last #include

namespace boost
{
namespace filesystem
{
namespace path_detail // intentionally don't use filesystem::detail to not bring internal Boost.Filesystem functions into ADL via path_constants
{

  template< typename Char, Char Separator, Char PreferredSeparator, Char Dot >
  struct path_constants
  {
    typedef path_constants< Char, Separator, PreferredSeparator, Dot > path_constants_base;
    typedef Char                                    value_type;
    static BOOST_CONSTEXPR_OR_CONST value_type      separator = Separator;
    static BOOST_CONSTEXPR_OR_CONST value_type      preferred_separator = PreferredSeparator;
    static BOOST_CONSTEXPR_OR_CONST value_type      dot = Dot;
  };

#if defined(BOOST_NO_CXX17_INLINE_VARIABLES)
  template< typename Char, Char Separator, Char PreferredSeparator, Char Dot >
  BOOST_CONSTEXPR_OR_CONST typename path_constants< Char, Separator, PreferredSeparator, Dot >::value_type
  path_constants< Char, Separator, PreferredSeparator, Dot >::separator;
  template< typename Char, Char Separator, Char PreferredSeparator, Char Dot >
  BOOST_CONSTEXPR_OR_CONST typename path_constants< Char, Separator, PreferredSeparator, Dot >::value_type
  path_constants< Char, Separator, PreferredSeparator, Dot >::preferred_separator;
  template< typename Char, Char Separator, Char PreferredSeparator, Char Dot >
  BOOST_CONSTEXPR_OR_CONST typename path_constants< Char, Separator, PreferredSeparator, Dot >::value_type
  path_constants< Char, Separator, PreferredSeparator, Dot >::dot;
#endif

} // namespace path_detail

  //------------------------------------------------------------------------------------//
  //                                                                                    //
  //                                    class path                                      //
  //                                                                                    //
  //------------------------------------------------------------------------------------//

  class path :
    public filesystem::path_detail::path_constants<
#ifdef BOOST_WINDOWS_API
      wchar_t, L'/', L'\\', L'.'
#else
      char, '/', '/', '.'
#endif
    >
  {
  public:

    //  value_type is the character type used by the operating system API to
    //  represent paths.

    typedef path_constants_base::value_type value_type;
    typedef std::basic_string<value_type>  string_type;
    typedef std::codecvt<wchar_t, char,
                         std::mbstate_t>   codecvt_type;


    //  ----- character encoding conversions -----

    //  Following the principle of least astonishment, path input arguments
    //  passed to or obtained from the operating system via objects of
    //  class path behave as if they were directly passed to or
    //  obtained from the O/S API, unless conversion is explicitly requested.
    //
    //  POSIX specfies that path strings are passed unchanged to and from the
    //  API. Note that this is different from the POSIX command line utilities,
    //  which convert according to a locale.
    //
    //  Thus for POSIX, char strings do not undergo conversion.  wchar_t strings
    //  are converted to/from char using the path locale or, if a conversion
    //  argument is given, using a conversion object modeled on
    //  std::wstring_convert.
    //
    //  The path locale, which is global to the thread, can be changed by the
    //  imbue() function. It is initialized to an implementation defined locale.
    //
    //  For Windows, wchar_t strings do not undergo conversion. char strings
    //  are converted using the "ANSI" or "OEM" code pages, as determined by
    //  the AreFileApisANSI() function, or, if a conversion argument is given,
    //  using a conversion object modeled on std::wstring_convert.
    //
    //  See m_pathname comments for further important rationale.

    //  TODO: rules needed for operating systems that use / or .
    //  differently, or format directory paths differently from file paths.
    //
    //  **********************************************************************************
    //
    //  More work needed: How to handle an operating system that may have
    //  slash characters or dot characters in valid filenames, either because
    //  it doesn't follow the POSIX standard, or because it allows MBCS
    //  filename encodings that may contain slash or dot characters. For
    //  example, ISO/IEC 2022 (JIS) encoding which allows switching to
    //  JIS x0208-1983 encoding. A valid filename in this set of encodings is
    //  0x1B 0x24 0x42 [switch to X0208-1983] 0x24 0x2F [U+304F Kiragana letter KU]
    //                                             ^^^^
    //  Note that 0x2F is the ASCII slash character
    //
    //  **********************************************************************************

    //  Supported source arguments: half-open iterator range, container, c-array,
    //  and single pointer to null terminated string.

    //  All source arguments except pointers to null terminated byte strings support
    //  multi-byte character strings which may have embedded nulls. Embedded null
    //  support is required for some Asian languages on Windows.

    //  "const codecvt_type& cvt=codecvt()" default arguments are not used because this
    //  limits the impact of locale("") initialization failures on POSIX systems to programs
    //  that actually depend on locale(""). It further ensures that exceptions thrown
    //  as a result of such failues occur after main() has started, so can be caught.

    //  -----  constructors  -----

    path() BOOST_NOEXCEPT {}
    path(const path& p) : m_pathname(p.m_pathname) {}

    template <class Source>
    path(Source const& source,
      typename boost::enable_if<path_traits::is_pathable<
        typename boost::decay<Source>::type> >::type* =0)
    {
      path_traits::dispatch(source, m_pathname);
    }

    path(const value_type* s) : m_pathname(s) {}
    path(value_type* s) : m_pathname(s) {}
    path(const string_type& s) : m_pathname(s) {}
    path(string_type& s) : m_pathname(s) {}

  //  As of October 2015 the interaction between noexcept and =default is so troublesome
  //  for VC++, GCC, and probably other compilers, that =default is not used with noexcept
  //  functions. GCC is not even consistent for the same release on different platforms.

# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    path(path&& p) BOOST_NOEXCEPT : m_pathname(std::move(p.m_pathname)) {}
    path& operator=(path&& p) BOOST_NOEXCEPT
      { m_pathname = std::move(p.m_pathname); return *this; }
# endif

    template <class Source>
    path(Source const& source, const codecvt_type& cvt)
    {
      path_traits::dispatch(source, m_pathname, cvt);
    }

    template <class InputIterator>
    path(InputIterator begin, InputIterator end)
    {
      if (begin != end)
      {
        // convert requires contiguous string, so copy
        std::basic_string<typename std::iterator_traits<InputIterator>::value_type>
          seq(begin, end);
        path_traits::convert(seq.c_str(), seq.c_str()+seq.size(), m_pathname);
      }
    }

    template <class InputIterator>
    path(InputIterator begin, InputIterator end, const codecvt_type& cvt)
    {
      if (begin != end)
      {
        // convert requires contiguous string, so copy
        std::basic_string<typename std::iterator_traits<InputIterator>::value_type>
          seq(begin, end);
        path_traits::convert(seq.c_str(), seq.c_str()+seq.size(), m_pathname, cvt);
      }
    }

    //  -----  assignments  -----

    path& operator=(const path& p)
    {
      m_pathname = p.m_pathname;
      return *this;
    }

    template <class Source>
      typename boost::enable_if<path_traits::is_pathable<
        typename boost::decay<Source>::type>, path&>::type
    operator=(Source const& source)
    {
      m_pathname.clear();
      path_traits::dispatch(source, m_pathname);
      return *this;
    }

    //  value_type overloads

    path& operator=(const value_type* ptr)  // required in case ptr overlaps *this
                                          {m_pathname = ptr; return *this;}
    path& operator=(value_type* ptr)  // required in case ptr overlaps *this
                                          {m_pathname = ptr; return *this;}
    path& operator=(const string_type& s) {m_pathname = s; return *this;}
    path& operator=(string_type& s)       {m_pathname = s; return *this;}

    path& assign(const value_type* ptr, const codecvt_type&)  // required in case ptr overlaps *this
                                          {m_pathname = ptr; return *this;}
    template <class Source>
    path& assign(Source const& source, const codecvt_type& cvt)
    {
      m_pathname.clear();
      path_traits::dispatch(source, m_pathname, cvt);
      return *this;
    }

    template <class InputIterator>
    path& assign(InputIterator begin, InputIterator end)
    {
      m_pathname.clear();
      if (begin != end)
      {
        std::basic_string<typename std::iterator_traits<InputIterator>::value_type>
          seq(begin, end);
        path_traits::convert(seq.c_str(), seq.c_str()+seq.size(), m_pathname);
      }
      return *this;
    }

    template <class InputIterator>
    path& assign(InputIterator begin, InputIterator end, const codecvt_type& cvt)
    {
      m_pathname.clear();
      if (begin != end)
      {
        std::basic_string<typename std::iterator_traits<InputIterator>::value_type>
          seq(begin, end);
        path_traits::convert(seq.c_str(), seq.c_str()+seq.size(), m_pathname, cvt);
      }
      return *this;
    }

    //  -----  concatenation  -----

    template <class Source>
      typename boost::enable_if<path_traits::is_pathable<
        typename boost::decay<Source>::type>, path&>::type
    operator+=(Source const& source)
    {
      return concat(source);
    }

    //  value_type overloads. Same rationale as for constructors above
    path& operator+=(const path& p)         { m_pathname += p.m_pathname; return *this; }
    path& operator+=(const value_type* ptr) { m_pathname += ptr; return *this; }
    path& operator+=(value_type* ptr)       { m_pathname += ptr; return *this; }
    path& operator+=(const string_type& s)  { m_pathname += s; return *this; }
    path& operator+=(string_type& s)        { m_pathname += s; return *this; }
    path& operator+=(value_type c)          { m_pathname += c; return *this; }

    template <class CharT>
      typename boost::enable_if<boost::is_integral<CharT>, path&>::type
    operator+=(CharT c)
    {
      CharT tmp[2];
      tmp[0] = c;
      tmp[1] = 0;
      return concat(tmp);
    }

    template <class Source>
    path& concat(Source const& source)
    {
      path_traits::dispatch(source, m_pathname);
      return *this;
    }

    template <class Source>
    path& concat(Source const& source, const codecvt_type& cvt)
    {
      path_traits::dispatch(source, m_pathname, cvt);
      return *this;
    }

    template <class InputIterator>
    path& concat(InputIterator begin, InputIterator end)
    {
      if (begin == end)
        return *this;
      std::basic_string<typename std::iterator_traits<InputIterator>::value_type>
        seq(begin, end);
      path_traits::convert(seq.c_str(), seq.c_str()+seq.size(), m_pathname);
      return *this;
    }

    template <class InputIterator>
    path& concat(InputIterator begin, InputIterator end, const codecvt_type& cvt)
    {
      if (begin == end)
        return *this;
      std::basic_string<typename std::iterator_traits<InputIterator>::value_type>
        seq(begin, end);
      path_traits::convert(seq.c_str(), seq.c_str()+seq.size(), m_pathname, cvt);
      return *this;
    }

    //  -----  appends  -----

    //  if a separator is added, it is the preferred separator for the platform;
    //  slash for POSIX, backslash for Windows

    BOOST_FILESYSTEM_DECL path& operator/=(const path& p);

    template <class Source>
      typename boost::enable_if<path_traits::is_pathable<
        typename boost::decay<Source>::type>, path&>::type
    operator/=(Source const& source)
    {
      return append(source);
    }

    BOOST_FILESYSTEM_DECL path& operator/=(const value_type* ptr);
    path& operator/=(value_type* ptr)
    {
      return this->operator/=(const_cast<const value_type*>(ptr));
    }
    path& operator/=(const string_type& s) { return this->operator/=(path(s)); }
    path& operator/=(string_type& s)       { return this->operator/=(path(s)); }

    path& append(const value_type* ptr)  // required in case ptr overlaps *this
    {
      this->operator/=(ptr);
      return *this;
    }

    path& append(const value_type* ptr, const codecvt_type&)  // required in case ptr overlaps *this
    {
      this->operator/=(ptr);
      return *this;
    }

    template <class Source>
    path& append(Source const& source);

    template <class Source>
    path& append(Source const& source, const codecvt_type& cvt);

    template <class InputIterator>
    path& append(InputIterator begin, InputIterator end);

    template <class InputIterator>
    path& append(InputIterator begin, InputIterator end, const codecvt_type& cvt);

    //  -----  modifiers  -----

    void clear() BOOST_NOEXCEPT { m_pathname.clear(); }
#   ifdef BOOST_POSIX_API
    path& make_preferred() { return *this; }  // POSIX no effect
#   else // BOOST_WINDOWS_API
    BOOST_FILESYSTEM_DECL path& make_preferred();  // change slashes to backslashes
#   endif
    BOOST_FILESYSTEM_DECL path& remove_filename();
    BOOST_FILESYSTEM_DECL path& remove_trailing_separator();
    BOOST_FILESYSTEM_DECL path& replace_extension(const path& new_extension = path());
    void swap(path& rhs) BOOST_NOEXCEPT { m_pathname.swap(rhs.m_pathname); }

    //  -----  observers  -----

    //  For operating systems that format file paths differently than directory
    //  paths, return values from observers are formatted as file names unless there
    //  is a trailing separator, in which case returns are formatted as directory
    //  paths. POSIX and Windows make no such distinction.

    //  Implementations are permitted to return const values or const references.

    //  The string or path returned by an observer are specified as being formatted
    //  as "native" or "generic".
    //
    //  For POSIX, these are all the same format; slashes and backslashes are as input and
    //  are not modified.
    //
    //  For Windows,   native:    as input; slashes and backslashes are not modified;
    //                            this is the format of the internally stored string.
    //                 generic:   backslashes are converted to slashes

    //  -----  native format observers  -----

    const string_type&  native() const BOOST_NOEXCEPT  { return m_pathname; }
    const value_type*   c_str() const BOOST_NOEXCEPT   { return m_pathname.c_str(); }
    string_type::size_type size() const BOOST_NOEXCEPT { return m_pathname.size(); }

    template <class String>
    String string() const;

    template <class String>
    String string(const codecvt_type& cvt) const;

#   ifdef BOOST_WINDOWS_API
    const std::string string() const
    {
      std::string tmp;
      if (!m_pathname.empty())
        path_traits::convert(m_pathname.c_str(), m_pathname.c_str()+m_pathname.size(),
        tmp);
      return tmp;
    }
    const std::string string(const codecvt_type& cvt) const
    {
      std::string tmp;
      if (!m_pathname.empty())
        path_traits::convert(m_pathname.c_str(), m_pathname.c_str()+m_pathname.size(),
          tmp, cvt);
      return tmp;
    }

    //  string_type is std::wstring, so there is no conversion
    const std::wstring& wstring() const { return m_pathname; }
    const std::wstring& wstring(const codecvt_type&) const { return m_pathname; }
#   else   // BOOST_POSIX_API
    //  string_type is std::string, so there is no conversion
    const std::string& string() const { return m_pathname; }
    const std::string& string(const codecvt_type&) const { return m_pathname; }

    const std::wstring wstring() const
    {
      std::wstring tmp;
      if (!m_pathname.empty())
        path_traits::convert(m_pathname.c_str(), m_pathname.c_str()+m_pathname.size(),
          tmp);
      return tmp;
    }
    const std::wstring wstring(const codecvt_type& cvt) const
    {
      std::wstring tmp;
      if (!m_pathname.empty())
        path_traits::convert(m_pathname.c_str(), m_pathname.c_str()+m_pathname.size(),
          tmp, cvt);
      return tmp;
    }
#   endif

    //  -----  generic format observers  -----

    //  Experimental generic function returning generic formatted path (i.e. separators
    //  are forward slashes). Motivation: simpler than a family of generic_*string
    //  functions.
#   ifdef BOOST_WINDOWS_API
    BOOST_FILESYSTEM_DECL path generic_path() const;
#   else
    path generic_path() const { return path(*this); }
#   endif

    template <class String>
    String generic_string() const;

    template <class String>
    String generic_string(const codecvt_type& cvt) const;

#   ifdef BOOST_WINDOWS_API
    const std::string   generic_string() const { return generic_path().string(); }
    const std::string   generic_string(const codecvt_type& cvt) const { return generic_path().string(cvt); }
    const std::wstring  generic_wstring() const { return generic_path().wstring(); }
    const std::wstring  generic_wstring(const codecvt_type&) const { return generic_wstring(); }
#   else // BOOST_POSIX_API
    //  On POSIX-like systems, the generic format is the same as the native format
    const std::string&  generic_string() const  { return m_pathname; }
    const std::string&  generic_string(const codecvt_type&) const  { return m_pathname; }
    const std::wstring  generic_wstring() const { return this->wstring(); }
    const std::wstring  generic_wstring(const codecvt_type& cvt) const { return this->wstring(cvt); }
#   endif

    //  -----  compare  -----

    BOOST_FILESYSTEM_DECL int compare(const path& p) const BOOST_NOEXCEPT;  // generic, lexicographical
    int compare(const std::string& s) const { return compare(path(s)); }
    int compare(const value_type* s) const  { return compare(path(s)); }

    //  -----  decomposition  -----

    BOOST_FILESYSTEM_DECL path  root_path() const;
    BOOST_FILESYSTEM_DECL path  root_name() const;         // returns 0 or 1 element path
                                                           // even on POSIX, root_name() is non-empty() for network paths
    BOOST_FILESYSTEM_DECL path  root_directory() const;    // returns 0 or 1 element path
    BOOST_FILESYSTEM_DECL path  relative_path() const;
    BOOST_FILESYSTEM_DECL path  parent_path() const;
    BOOST_FILESYSTEM_DECL path  filename() const;          // returns 0 or 1 element path
    BOOST_FILESYSTEM_DECL path  stem() const;              // returns 0 or 1 element path
    BOOST_FILESYSTEM_DECL path  extension() const;         // returns 0 or 1 element path

    //  -----  query  -----

    bool empty() const BOOST_NOEXCEPT { return m_pathname.empty(); }
    bool filename_is_dot() const;
    bool filename_is_dot_dot() const;
    bool has_root_path() const       { return has_root_directory() || has_root_name(); }
    bool has_root_name() const       { return !root_name().empty(); }
    bool has_root_directory() const  { return !root_directory().empty(); }
    bool has_relative_path() const   { return !relative_path().empty(); }
    bool has_parent_path() const     { return !parent_path().empty(); }
    bool has_filename() const        { return !m_pathname.empty(); }
    bool has_stem() const            { return !stem().empty(); }
    bool has_extension() const       { return !extension().empty(); }
    bool is_relative() const         { return !is_absolute(); }
    bool is_absolute() const
    {
      // Windows CE has no root name (aka drive letters)
#     if defined(BOOST_WINDOWS_API) && !defined(UNDER_CE)
      return has_root_name() && has_root_directory();
#     else
      return has_root_directory();
#     endif
    }

    //  -----  lexical operations  -----

    BOOST_FILESYSTEM_DECL path lexically_normal() const;
    BOOST_FILESYSTEM_DECL path lexically_relative(const path& base) const;
    path lexically_proximate(const path& base) const
    {
      path tmp(lexically_relative(base));
      return tmp.empty() ? *this : tmp;
    }

    //  -----  iterators  -----

    class iterator;
    typedef iterator const_iterator;
    class reverse_iterator;
    typedef reverse_iterator const_reverse_iterator;

    BOOST_FILESYSTEM_DECL iterator begin() const;
    BOOST_FILESYSTEM_DECL iterator end() const;
    reverse_iterator rbegin() const;
    reverse_iterator rend() const;

    //  -----  static member functions  -----

    static BOOST_FILESYSTEM_DECL std::locale imbue(const std::locale& loc);
    static BOOST_FILESYSTEM_DECL const codecvt_type&  codecvt();

    //  -----  deprecated functions  -----

# if defined(BOOST_FILESYSTEM_DEPRECATED) && defined(BOOST_FILESYSTEM_NO_DEPRECATED)
#   error both BOOST_FILESYSTEM_DEPRECATED and BOOST_FILESYSTEM_NO_DEPRECATED are defined
# endif

# if !defined(BOOST_FILESYSTEM_NO_DEPRECATED)
    //  recently deprecated functions supplied by default
    path&  normalize()              {
                                      path tmp(lexically_normal());
                                      m_pathname.swap(tmp.m_pathname);
                                      return *this;
                                    }
    path&  remove_leaf()            { return remove_filename(); }
    path   leaf() const             { return filename(); }
    path   branch_path() const      { return parent_path(); }
    path   generic() const          { return generic_path(); }
    bool   has_leaf() const         { return !m_pathname.empty(); }
    bool   has_branch_path() const  { return !parent_path().empty(); }
    bool   is_complete() const      { return is_absolute(); }
# endif

# if defined(BOOST_FILESYSTEM_DEPRECATED)
    //  deprecated functions with enough signature or semantic changes that they are
    //  not supplied by default
    const std::string file_string() const               { return string(); }
    const std::string directory_string() const          { return string(); }
    const std::string native_file_string() const        { return string(); }
    const std::string native_directory_string() const   { return string(); }
    const string_type external_file_string() const      { return native(); }
    const string_type external_directory_string() const { return native(); }

    //  older functions no longer supported
    //typedef bool (*name_check)(const std::string & name);
    //basic_path(const string_type& str, name_check) { operator/=(str); }
    //basic_path(const typename string_type::value_type* s, name_check)
    //  { operator/=(s);}
    //static bool default_name_check_writable() { return false; }
    //static void default_name_check(name_check) {}
    //static name_check default_name_check() { return 0; }
    //basic_path& canonize();
# endif

//--------------------------------------------------------------------------------------//
//                            class path private members                                //
//--------------------------------------------------------------------------------------//

  private:

#   if defined(_MSC_VER)
#     pragma warning(push) // Save warning settings
#     pragma warning(disable : 4251) // disable warning: class 'std::basic_string<_Elem,_Traits,_Ax>'
#   endif                            // needs to have dll-interface...
/*
      m_pathname has the type, encoding, and format required by the native
      operating system. Thus for POSIX and Windows there is no conversion for
      passing m_pathname.c_str() to the O/S API or when obtaining a path from the
      O/S API. POSIX encoding is unspecified other than for dot and slash
      characters; POSIX just treats paths as a sequence of bytes. Windows
      encoding is UCS-2 or UTF-16 depending on the version.
*/
    string_type  m_pathname;  // Windows: as input; backslashes NOT converted to slashes,
                              // slashes NOT converted to backslashes
#   if defined(_MSC_VER)
#     pragma warning(pop) // restore warning settings.
#   endif

    //  Returns: If separator is to be appended, m_pathname.size() before append. Otherwise 0.
    //  Note: An append is never performed if size()==0, so a returned 0 is unambiguous.
    BOOST_FILESYSTEM_DECL string_type::size_type m_append_separator_if_needed();

    BOOST_FILESYSTEM_DECL void m_erase_redundant_separator(string_type::size_type sep_pos);
    BOOST_FILESYSTEM_DECL string_type::size_type m_parent_path_end() const;

    // Was qualified; como433beta8 reports:
    //    warning #427-D: qualified name is not allowed in member declaration
    friend class iterator;
    friend bool operator<(const path& lhs, const path& rhs);

    // see path::iterator::increment/decrement comment below
    static BOOST_FILESYSTEM_DECL void m_path_iterator_increment(path::iterator& it);
    static BOOST_FILESYSTEM_DECL void m_path_iterator_decrement(path::iterator& it);

  };  // class path

  namespace detail
  {
    BOOST_FILESYSTEM_DECL
      int lex_compare(path::iterator first1, path::iterator last1,
        path::iterator first2, path::iterator last2);
    BOOST_FILESYSTEM_DECL
      const path&  dot_path();
    BOOST_FILESYSTEM_DECL
      const path&  dot_dot_path();
  }

# ifndef BOOST_FILESYSTEM_NO_DEPRECATED
  typedef path wpath;
# endif

  //------------------------------------------------------------------------------------//
  //                             class path::iterator                                   //
  //------------------------------------------------------------------------------------//

  class path::iterator
    : public boost::iterator_facade<
      path::iterator,
      path const,
      boost::bidirectional_traversal_tag >
  {
  private:
    friend class boost::iterator_core_access;
    friend class boost::filesystem::path;
    friend class boost::filesystem::path::reverse_iterator;
    friend void m_path_iterator_increment(path::iterator & it);
    friend void m_path_iterator_decrement(path::iterator & it);

    const path& dereference() const { return m_element; }

    bool equal(const iterator & rhs) const
    {
      return m_path_ptr == rhs.m_path_ptr && m_pos == rhs.m_pos;
    }

    // iterator_facade derived classes don't seem to like implementations in
    // separate translation unit dll's, so forward to class path static members
    void increment() { m_path_iterator_increment(*this); }
    void decrement() { m_path_iterator_decrement(*this); }

    path                    m_element;   // current element
    const path*             m_path_ptr;  // path being iterated over
    string_type::size_type  m_pos;       // position of m_element in
                                         // m_path_ptr->m_pathname.
                                         // if m_element is implicit dot, m_pos is the
                                         // position of the last separator in the path.
                                         // end() iterator is indicated by
                                         // m_pos == m_path_ptr->m_pathname.size()
  }; // path::iterator

  //------------------------------------------------------------------------------------//
  //                         class path::reverse_iterator                               //
  //------------------------------------------------------------------------------------//

  class path::reverse_iterator
    : public boost::iterator_facade<
      path::reverse_iterator,
      path const,
      boost::bidirectional_traversal_tag >
  {
  public:
    explicit reverse_iterator(iterator itr) : m_itr(itr)
    {
      if (itr != itr.m_path_ptr->begin())
        m_element = *--itr;
    }

  private:
    friend class boost::iterator_core_access;
    friend class boost::filesystem::path;

    const path& dereference() const { return m_element; }
    bool equal(const reverse_iterator& rhs) const { return m_itr == rhs.m_itr; }
    void increment()
    {
      --m_itr;
      if (m_itr != m_itr.m_path_ptr->begin())
      {
        iterator tmp = m_itr;
        m_element = *--tmp;
      }
    }
    void decrement()
    {
      m_element = *m_itr;
      ++m_itr;
    }

    iterator m_itr;
    path     m_element;

  }; // path::reverse_iterator

  //------------------------------------------------------------------------------------//
  //                                                                                    //
  //                              non-member functions                                  //
  //                                                                                    //
  //------------------------------------------------------------------------------------//

  //  std::lexicographical_compare would infinitely recurse because path iterators
  //  yield paths, so provide a path aware version
  inline bool lexicographical_compare(path::iterator first1, path::iterator last1,
    path::iterator first2, path::iterator last2)
    { return detail::lex_compare(first1, last1, first2, last2) < 0; }

  inline bool operator==(const path& lhs, const path& rhs)              {return lhs.compare(rhs) == 0;}
  inline bool operator==(const path& lhs, const path::string_type& rhs) {return lhs.compare(rhs) == 0;}
  inline bool operator==(const path::string_type& lhs, const path& rhs) {return rhs.compare(lhs) == 0;}
  inline bool operator==(const path& lhs, const path::value_type* rhs)  {return lhs.compare(rhs) == 0;}
  inline bool operator==(const path::value_type* lhs, const path& rhs)  {return rhs.compare(lhs) == 0;}

  inline bool operator!=(const path& lhs, const path& rhs)              {return lhs.compare(rhs) != 0;}
  inline bool operator!=(const path& lhs, const path::string_type& rhs) {return lhs.compare(rhs) != 0;}
  inline bool operator!=(const path::string_type& lhs, const path& rhs) {return rhs.compare(lhs) != 0;}
  inline bool operator!=(const path& lhs, const path::value_type* rhs)  {return lhs.compare(rhs) != 0;}
  inline bool operator!=(const path::value_type* lhs, const path& rhs)  {return rhs.compare(lhs) != 0;}

  // TODO: why do == and != have additional overloads, but the others don't?

  inline bool operator<(const path& lhs, const path& rhs)  {return lhs.compare(rhs) < 0;}
  inline bool operator<=(const path& lhs, const path& rhs) {return !(rhs < lhs);}
  inline bool operator> (const path& lhs, const path& rhs) {return rhs < lhs;}
  inline bool operator>=(const path& lhs, const path& rhs) {return !(lhs < rhs);}

  inline std::size_t hash_value(const path& x) BOOST_NOEXCEPT
  {
# ifdef BOOST_WINDOWS_API
    std::size_t seed = 0;
    for(const path::value_type* it = x.c_str(); *it; ++it)
      hash_combine(seed, *it == L'/' ? L'\\' : *it);
    return seed;
# else   // BOOST_POSIX_API
    return hash_range(x.native().begin(), x.native().end());
# endif
  }

  inline void swap(path& lhs, path& rhs) BOOST_NOEXCEPT { lhs.swap(rhs); }

  inline path operator/(const path& lhs, const path& rhs)
  {
    path p = lhs;
    p /= rhs;
    return p;
  }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  inline path operator/(path&& lhs, const path& rhs)
  {
    lhs /= rhs;
    return std::move(lhs);
  }
# endif

  //  inserters and extractors
  //    use boost::io::quoted() to handle spaces in paths
  //    use '&' as escape character to ease use for Windows paths

  template <class Char, class Traits>
  inline std::basic_ostream<Char, Traits>&
  operator<<(std::basic_ostream<Char, Traits>& os, const path& p)
  {
    return os
      << boost::io::quoted(p.template string<std::basic_string<Char> >(), static_cast<Char>('&'));
  }

  template <class Char, class Traits>
  inline std::basic_istream<Char, Traits>&
  operator>>(std::basic_istream<Char, Traits>& is, path& p)
  {
    std::basic_string<Char> str;
    is >> boost::io::quoted(str, static_cast<Char>('&'));
    p = str;
    return is;
  }

  //  name_checks

  //  These functions are holdovers from version 1. It isn't clear they have much
  //  usefulness, or how to generalize them for later versions.

  BOOST_FILESYSTEM_DECL bool portable_posix_name(const std::string & name);
  BOOST_FILESYSTEM_DECL bool windows_name(const std::string & name);
  BOOST_FILESYSTEM_DECL bool portable_name(const std::string & name);
  BOOST_FILESYSTEM_DECL bool portable_directory_name(const std::string & name);
  BOOST_FILESYSTEM_DECL bool portable_file_name(const std::string & name);
  BOOST_FILESYSTEM_DECL bool native(const std::string & name);

  namespace detail
  {
    //  For POSIX, is_directory_separator() and is_element_separator() are identical since
    //  a forward slash is the only valid directory separator and also the only valid
    //  element separator. For Windows, forward slash and back slash are the possible
    //  directory separators, but colon (example: "c:foo") is also an element separator.

    inline bool is_directory_separator(path::value_type c) BOOST_NOEXCEPT
    {
      return c == path::separator
#     ifdef BOOST_WINDOWS_API
        || c == path::preferred_separator
#     endif
      ;
    }
    inline bool is_element_separator(path::value_type c) BOOST_NOEXCEPT
    {
      return c == path::separator
#     ifdef BOOST_WINDOWS_API
        || c == path::preferred_separator || c == L':'
#     endif
      ;
    }
  }  // namespace detail

  //------------------------------------------------------------------------------------//
  //                  class path miscellaneous function implementations                 //
  //------------------------------------------------------------------------------------//

  inline path::reverse_iterator path::rbegin() const { return reverse_iterator(end()); }
  inline path::reverse_iterator path::rend() const   { return reverse_iterator(begin()); }

  inline bool path::filename_is_dot() const
  {
    // implicit dot is tricky, so actually call filename(); see path::filename() example
    // in reference.html
    path p(filename());
    return p.size() == 1 && *p.c_str() == dot;
  }

  inline bool path::filename_is_dot_dot() const
  {
    return size() >= 2 && m_pathname[size()-1] == dot && m_pathname[size()-2] == dot
      && (m_pathname.size() == 2 || detail::is_element_separator(m_pathname[size()-3]));
      // use detail::is_element_separator() rather than detail::is_directory_separator
      // to deal with "c:.." edge case on Windows when ':' acts as a separator
  }

//--------------------------------------------------------------------------------------//
//                     class path member template implementation                        //
//--------------------------------------------------------------------------------------//

  template <class InputIterator>
  path& path::append(InputIterator begin, InputIterator end)
  {
    if (begin == end)
      return *this;
    string_type::size_type sep_pos(m_append_separator_if_needed());
    std::basic_string<typename std::iterator_traits<InputIterator>::value_type>
      seq(begin, end);
    path_traits::convert(seq.c_str(), seq.c_str()+seq.size(), m_pathname);
    if (sep_pos)
      m_erase_redundant_separator(sep_pos);
    return *this;
  }

  template <class InputIterator>
  path& path::append(InputIterator begin, InputIterator end, const codecvt_type& cvt)
  {
    if (begin == end)
      return *this;
    string_type::size_type sep_pos(m_append_separator_if_needed());
    std::basic_string<typename std::iterator_traits<InputIterator>::value_type>
      seq(begin, end);
    path_traits::convert(seq.c_str(), seq.c_str()+seq.size(), m_pathname, cvt);
    if (sep_pos)
      m_erase_redundant_separator(sep_pos);
    return *this;
  }

  template <class Source>
  path& path::append(Source const& source)
  {
    if (path_traits::empty(source))
      return *this;
    string_type::size_type sep_pos(m_append_separator_if_needed());
    path_traits::dispatch(source, m_pathname);
    if (sep_pos)
      m_erase_redundant_separator(sep_pos);
    return *this;
  }

  template <class Source>
  path& path::append(Source const& source, const codecvt_type& cvt)
  {
    if (path_traits::empty(source))
      return *this;
    string_type::size_type sep_pos(m_append_separator_if_needed());
    path_traits::dispatch(source, m_pathname, cvt);
    if (sep_pos)
      m_erase_redundant_separator(sep_pos);
    return *this;
  }

//--------------------------------------------------------------------------------------//
//                     class path member template specializations                       //
//--------------------------------------------------------------------------------------//

  template <> inline
  std::string path::string<std::string>() const
    { return string(); }

  template <> inline
  std::wstring path::string<std::wstring>() const
    { return wstring(); }

  template <> inline
  std::string path::string<std::string>(const codecvt_type& cvt) const
    { return string(cvt); }

  template <> inline
  std::wstring path::string<std::wstring>(const codecvt_type& cvt) const
    { return wstring(cvt); }

  template <> inline
  std::string path::generic_string<std::string>() const
    { return generic_string(); }

  template <> inline
  std::wstring path::generic_string<std::wstring>() const
    { return generic_wstring(); }

  template <> inline
  std::string path::generic_string<std::string>(const codecvt_type& cvt) const
    { return generic_string(cvt); }

  template <> inline
  std::wstring path::generic_string<std::wstring>(const codecvt_type& cvt) const
    { return generic_wstring(cvt); }

  //--------------------------------------------------------------------------------------//
  //                     path_traits convert function implementations                     //
  //                        requiring path::codecvt() be visable                          //
  //--------------------------------------------------------------------------------------//

namespace path_traits
{  //  without codecvt

  inline
    void convert(const char* from,
    const char* from_end,    // 0 for null terminated MBCS
    std::wstring & to)
  {
    convert(from, from_end, to, path::codecvt());
  }

  inline
    void convert(const wchar_t* from,
    const wchar_t* from_end,  // 0 for null terminated MBCS
    std::string & to)
  {
    convert(from, from_end, to, path::codecvt());
  }

  inline
    void convert(const char* from,
    std::wstring & to)
  {
    BOOST_ASSERT(!!from);
    convert(from, 0, to, path::codecvt());
  }

  inline
    void convert(const wchar_t* from,
    std::string & to)
  {
    BOOST_ASSERT(!!from);
    convert(from, 0, to, path::codecvt());
  }
}  // namespace path_traits
}  // namespace filesystem
}  // namespace boost

//----------------------------------------------------------------------------//

#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas

#endif  // BOOST_FILESYSTEM_PATH_HPP

/* path.hpp
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
*/