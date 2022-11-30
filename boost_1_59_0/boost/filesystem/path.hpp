//  filesystem path.hpp  ---------------------------------------------------------------//

//  Copyright Vladimir Prus 2002
//  Copyright Beman Dawes 2002-2005, 2009
//  Copyright Andrey Semashev 2021

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

//  path::stem(), extension(), and replace_extension() are based on
//  basename(), extension(), and change_extension() from the original
//  filesystem/convenience.hpp header by Vladimir Prus.

#ifndef BOOST_FILESYSTEM_PATH_HPP
#define BOOST_FILESYSTEM_PATH_HPP

#include <boost/assert.hpp>
#include <boost/filesystem/config.hpp>
#include <boost/filesystem/path_traits.hpp> // includes <cwchar>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/io/quoted.hpp>
#include <boost/functional/hash_fwd.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/decay.hpp>
#include <cstddef>
#include <cwchar> // for mbstate_t
#include <string>
#include <iosfwd>
#include <iterator>
#include <locale>
#include <utility>

#include <boost/filesystem/detail/header.hpp> // must be the last #include

namespace boost {
namespace filesystem {

class path;

namespace path_detail { // intentionally don't use filesystem::detail to not bring internal Boost.Filesystem functions into ADL via path_constants

template< typename Char, Char Separator, Char PreferredSeparator, Char Dot >
struct path_constants
{
    typedef path_constants< Char, Separator, PreferredSeparator, Dot > path_constants_base;
    typedef Char value_type;
    static BOOST_CONSTEXPR_OR_CONST value_type separator = Separator;
    static BOOST_CONSTEXPR_OR_CONST value_type preferred_separator = PreferredSeparator;
    static BOOST_CONSTEXPR_OR_CONST value_type dot = Dot;
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

// A struct that denotes a contiguous range of characters in a string. A lightweight alternative to string_view.
struct substring
{
    std::size_t pos;
    std::size_t size;
};

template< typename T >
struct is_native_char_ptr_impl : public boost::false_type {};

#if defined(BOOST_WINDOWS_API)
template< >
struct is_native_char_ptr_impl< wchar_t* > : public boost::true_type {};
template< >
struct is_native_char_ptr_impl< const wchar_t* > : public boost::true_type {};
#else // defined(BOOST_WINDOWS_API)
template< >
struct is_native_char_ptr_impl< char* > : public boost::true_type {};
template< >
struct is_native_char_ptr_impl< const char* > : public boost::true_type {};
#endif // defined(BOOST_WINDOWS_API)

template< typename T >
struct is_native_char_ptr : public is_native_char_ptr_impl< typename boost::remove_cv< typename boost::remove_reference< T >::type >::type > {};

template< typename T >
struct is_native_pathable_impl : public boost::false_type {};

template< typename T >
struct is_native_pathable_impl< T* > : public is_native_char_ptr_impl< T* > {};

#if defined(BOOST_WINDOWS_API)
template< >
struct is_native_pathable_impl< const wchar_t[] > : public boost::true_type {};
template< std::size_t N >
struct is_native_pathable_impl< const wchar_t[N] > : public boost::true_type {};
template< >
struct is_native_pathable_impl< std::basic_string< wchar_t > > : public boost::true_type {};
#else // defined(BOOST_WINDOWS_API)
template< >
struct is_native_pathable_impl< const char[] > : public boost::true_type {};
template< std::size_t N >
struct is_native_pathable_impl< const char[N] > : public boost::true_type {};
template< >
struct is_native_pathable_impl< std::basic_string< char > > : public boost::true_type {};
#endif // defined(BOOST_WINDOWS_API)
template< >
struct is_native_pathable_impl< filesystem::path > : public boost::true_type {};

template< typename T >
struct is_native_pathable : public is_native_pathable_impl< typename boost::remove_cv< typename boost::remove_reference< T >::type >::type > {};

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
    typedef std::basic_string< value_type > string_type;
    typedef std::codecvt< wchar_t, char, std::mbstate_t > codecvt_type;

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
    path(path const& p) : m_pathname(p.m_pathname) {}

    template< class Source >
    path(Source const& source, typename boost::enable_if_c<
        path_traits::is_pathable< typename boost::decay< Source >::type >::value && !path_detail::is_native_pathable< Source >::value
    >::type* = 0)
    {
        path_traits::dispatch(source, m_pathname);
    }

    path(const value_type* s) : m_pathname(s) {}
    path(string_type const& s) : m_pathname(s) {}

    //  As of October 2015 the interaction between noexcept and =default is so troublesome
    //  for VC++, GCC, and probably other compilers, that =default is not used with noexcept
    //  functions. GCC is not even consistent for the same release on different platforms.

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    path(path&& p) BOOST_NOEXCEPT : m_pathname(std::move(p.m_pathname))
    {
    }
    path(path&& p, codecvt_type const&) BOOST_NOEXCEPT : m_pathname(std::move(p.m_pathname))
    {
    }
    path& operator=(path&& p) BOOST_NOEXCEPT
    {
        m_pathname = std::move(p.m_pathname);
        return *this;
    }
    path& assign(path&& p) BOOST_NOEXCEPT
    {
        m_pathname = std::move(p.m_pathname);
        return *this;
    }
    path& assign(path&& p, codecvt_type const&) BOOST_NOEXCEPT
    {
        m_pathname = std::move(p.m_pathname);
        return *this;
    }

    path(string_type&& s) BOOST_NOEXCEPT : m_pathname(std::move(s))
    {
    }
    path(string_type&& s, codecvt_type const&) BOOST_NOEXCEPT : m_pathname(std::move(s))
    {
    }
    path& operator=(string_type&& p) BOOST_NOEXCEPT
    {
        m_pathname = std::move(p);
        return *this;
    }
    path& assign(string_type&& p) BOOST_NOEXCEPT
    {
        m_pathname = std::move(p);
        return *this;
    }
    path& assign(string_type&& p, codecvt_type const&) BOOST_NOEXCEPT
    {
        m_pathname = std::move(p);
        return *this;
    }
#endif

    path(path const& p, codecvt_type const&) : m_pathname(p.m_pathname) {}
    path(const value_type* s, codecvt_type const&) : m_pathname(s) {}
    path(string_type const& s, codecvt_type const&) : m_pathname(s) {}

    template< class Source >
    path(Source const& source, codecvt_type const& cvt, typename boost::enable_if_c<
        path_traits::is_pathable< typename boost::decay< Source >::type >::value && !path_detail::is_native_pathable< Source >::value
    >::type* = 0)
    {
        path_traits::dispatch(source, m_pathname, cvt);
    }

    path(const value_type* begin, const value_type* end) : m_pathname(begin, end) {}

    template< class InputIterator >
    path(InputIterator begin, InputIterator end, typename boost::disable_if< path_detail::is_native_char_ptr< InputIterator > >::type* = 0)
    {
        if (begin != end)
        {
            // convert requires contiguous string, so copy
            std::basic_string< typename std::iterator_traits< InputIterator >::value_type > seq(begin, end);
            path_traits::convert(seq.c_str(), seq.c_str() + seq.size(), m_pathname);
        }
    }

    path(const value_type* begin, const value_type* end, codecvt_type const&) : m_pathname(begin, end) {}

    template< class InputIterator >
    path(InputIterator begin, InputIterator end, codecvt_type const& cvt, typename boost::disable_if< path_detail::is_native_char_ptr< InputIterator > >::type* = 0)
    {
        if (begin != end)
        {
            // convert requires contiguous string, so copy
            std::basic_string< typename std::iterator_traits< InputIterator >::value_type > seq(begin, end);
            path_traits::convert(seq.c_str(), seq.c_str() + seq.size(), m_pathname, cvt);
        }
    }

    //  -----  assignments  -----

    // We need to explicitly define copy assignment as otherwise it will be implicitly defined as deleted because there is move assignment
    path& operator=(path const& p)
    {
        return assign(p);
    }

    path& operator=(string_type const& s)
    {
        return assign(s);
    }

    path& operator=(const value_type* ptr)
    {
        return assign(ptr);
    }

    template< class Source >
    typename boost::enable_if_c<
        path_traits::is_pathable< typename boost::decay< Source >::type >::value && !path_detail::is_native_pathable< Source >::value,
        path&
    >::type operator=(Source const& source)
    {
        return assign(source);
    }

    path& assign(path const& p)
    {
        m_pathname = p.m_pathname;
        return *this;
    }

    path& assign(string_type const& s)
    {
        m_pathname = s;
        return *this;
    }

    path& assign(const value_type* ptr)
    {
        m_pathname = ptr;
        return *this;
    }

    template< class Source >
    typename boost::enable_if_c<
        path_traits::is_pathable< typename boost::decay< Source >::type >::value && !path_detail::is_native_pathable< Source >::value,
        path&
    >::type assign(Source const& source)
    {
        m_pathname.clear();
        path_traits::dispatch(source, m_pathname);
        return *this;
    }

    path& assign(path const& p, codecvt_type const&)
    {
        m_pathname = p.m_pathname;
        return *this;
    }

    path& assign(string_type const& s, codecvt_type const&)
    {
        m_pathname = s;
        return *this;
    }

    path& assign(const value_type* ptr, codecvt_type const&)
    {
        m_pathname = ptr;
        return *this;
    }

    template< class Source >
    typename boost::enable_if_c<
        path_traits::is_pathable< typename boost::decay< Source >::type >::value && !path_detail::is_native_pathable< Source >::value,
        path&
    >::type assign(Source const& source, codecvt_type const& cvt)
    {
        m_pathname.clear();
        path_traits::dispatch(source, m_pathname, cvt);
        return *this;
    }

    path& assign(const value_type* begin, const value_type* end)
    {
        m_pathname.assign(begin, end);
        return *this;
    }

    template< class InputIterator >
    typename boost::disable_if< path_detail::is_native_char_ptr< InputIterator >, path& >::type
    assign(InputIterator begin, InputIterator end)
    {
        m_pathname.clear();
        if (begin != end)
        {
            std::basic_string< typename std::iterator_traits< InputIterator >::value_type > seq(begin, end);
            path_traits::convert(seq.c_str(), seq.c_str() + seq.size(), m_pathname);
        }
        return *this;
    }

    path& assign(const value_type* begin, const value_type* end, codecvt_type const&)
    {
        m_pathname.assign(begin, end);
        return *this;
    }

    template< class InputIterator >
    typename boost::disable_if< path_detail::is_native_char_ptr< InputIterator >, path& >::type
    assign(InputIterator begin, InputIterator end, codecvt_type const& cvt)
    {
        m_pathname.clear();
        if (begin != end)
        {
            std::basic_string< typename std::iterator_traits< InputIterator >::value_type > seq(begin, end);
            path_traits::convert(seq.c_str(), seq.c_str() + seq.size(), m_pathname, cvt);
        }
        return *this;
    }

    //  -----  concatenation  -----

    path& operator+=(path const& p)
    {
        return concat(p);
    }

    path& operator+=(const value_type* ptr)
    {
        return concat(ptr);
    }

    path& operator+=(string_type const& s)
    {
        return concat(s);
    }

    template< class Source >
    typename boost::enable_if_c<
        path_traits::is_pathable< typename boost::decay< Source >::type >::value && !path_detail::is_native_pathable< Source >::value,
        path&
    >::type operator+=(Source const& source)
    {
        return concat(source);
    }

    path& operator+=(value_type c)
    {
        m_pathname.push_back(c);
        return *this;
    }

    template< class CharT >
    typename boost::enable_if< boost::is_integral< CharT >, path& >::type
    operator+=(CharT c)
    {
        CharT tmp[2];
        tmp[0] = c;
        tmp[1] = static_cast< CharT >(0);
        return concat(tmp);
    }

    path& concat(path const& p)
    {
        m_pathname += p.m_pathname;
        return *this;
    }

    path& concat(const value_type* ptr)
    {
        m_pathname += ptr;
        return *this;
    }

    path& concat(string_type const& s)
    {
        m_pathname += s;
        return *this;
    }

    template< class Source >
    typename boost::enable_if_c<
        path_traits::is_pathable< typename boost::decay< Source >::type >::value && !path_detail::is_native_pathable< Source >::value,
        path&
    >::type concat(Source const& source)
    {
        path_traits::dispatch(source, m_pathname);
        return *this;
    }

    path& concat(path const& p, codecvt_type const&)
    {
        m_pathname += p.m_pathname;
        return *this;
    }

    path& concat(const value_type* ptr, codecvt_type const&)
    {
        m_pathname += ptr;
        return *this;
    }

    path& concat(string_type const& s, codecvt_type const&)
    {
        m_pathname += s;
        return *this;
    }

    template< class Source >
    typename boost::enable_if_c<
        path_traits::is_pathable< typename boost::decay< Source >::type >::value && !path_detail::is_native_pathable< Source >::value,
        path&
    >::type concat(Source const& source, codecvt_type const& cvt)
    {
        path_traits::dispatch(source, m_pathname, cvt);
        return *this;
    }

    path& concat(const value_type* begin, const value_type* end)
    {
        m_pathname.append(begin, end);
        return *this;
    }

    template< class InputIterator >
    typename boost::disable_if< path_detail::is_native_char_ptr< InputIterator >, path& >::type
    concat(InputIterator begin, InputIterator end)
    {
        if (begin != end)
        {
            std::basic_string< typename std::iterator_traits< InputIterator >::value_type > seq(begin, end);
            path_traits::convert(seq.c_str(), seq.c_str() + seq.size(), m_pathname);
        }
        return *this;
    }

    path& concat(const value_type* begin, const value_type* end, codecvt_type const&)
    {
        m_pathname.append(begin, end);
        return *this;
    }

    template< class InputIterator >
    typename boost::disable_if< path_detail::is_native_char_ptr< InputIterator >, path& >::type
    concat(InputIterator begin, InputIterator end, codecvt_type const& cvt)
    {
        if (begin != end)
        {
            std::basic_string< typename std::iterator_traits< InputIterator >::value_type > seq(begin, end);
            path_traits::convert(seq.c_str(), seq.c_str() + seq.size(), m_pathname, cvt);
        }
        return *this;
    }

    //  -----  appends  -----

    //  if a separator is added, it is the preferred separator for the platform;
    //  slash for POSIX, backslash for Windows

    path& operator/=(path const& p)
    {
        return append(p);
    }

    path& operator/=(const value_type* ptr)
    {
        return append(ptr);
    }

    path& operator/=(string_type const& s)
    {
        return append(s);
    }

    template< class Source >
    BOOST_FORCEINLINE typename boost::enable_if_c<
        path_traits::is_pathable< typename boost::decay< Source >::type >::value && !path_detail::is_native_pathable< Source >::value,
        path&
    >::type operator/=(Source const& source)
    {
        return append(source);
    }

    BOOST_FORCEINLINE path& append(path const& p)
    {
        BOOST_FILESYSTEM_VERSIONED_SYM(append)(p);
        return *this;
    }

    BOOST_FORCEINLINE path& append(string_type const& p)
    {
        BOOST_FILESYSTEM_VERSIONED_SYM(append)(p.c_str(), p.c_str() + p.size());
        return *this;
    }

    BOOST_FORCEINLINE path& append(const value_type* ptr)
    {
        BOOST_FILESYSTEM_VERSIONED_SYM(append)(ptr, ptr + string_type::traits_type::length(ptr));
        return *this;
    }

    template< class Source >
    typename boost::enable_if_c<
        path_traits::is_pathable< typename boost::decay< Source >::type >::value && !path_detail::is_native_pathable< Source >::value,
        path&
    >::type append(Source const& source)
    {
        path p;
        path_traits::dispatch(source, p.m_pathname);
        return append(p);
    }

    BOOST_FORCEINLINE path& append(path const& p, codecvt_type const&)
    {
        BOOST_FILESYSTEM_VERSIONED_SYM(append)(p);
        return *this;
    }

    BOOST_FORCEINLINE path& append(string_type const& p, codecvt_type const&)
    {
        BOOST_FILESYSTEM_VERSIONED_SYM(append)(p.c_str(), p.c_str() + p.size());
        return *this;
    }

    BOOST_FORCEINLINE path& append(const value_type* ptr, codecvt_type const&)
    {
        BOOST_FILESYSTEM_VERSIONED_SYM(append)(ptr, ptr + string_type::traits_type::length(ptr));
        return *this;
    }

    template< class Source >
    typename boost::enable_if_c<
        path_traits::is_pathable< typename boost::decay< Source >::type >::value && !path_detail::is_native_pathable< Source >::value,
        path&
    >::type append(Source const& source, codecvt_type const& cvt)
    {
        path p;
        path_traits::dispatch(source, p.m_pathname, cvt);
        return append(p);
    }

    BOOST_FORCEINLINE path& append(const value_type* begin, const value_type* end)
    {
        BOOST_FILESYSTEM_VERSIONED_SYM(append)(begin, end);
        return *this;
    }

    template< class InputIterator >
    typename boost::disable_if< path_detail::is_native_char_ptr< InputIterator >, path& >::type
    append(InputIterator begin, InputIterator end)
    {
        path p;
        if (begin != end)
        {
            std::basic_string< typename std::iterator_traits< InputIterator >::value_type > seq(begin, end);
            path_traits::convert(seq.c_str(), seq.c_str() + seq.size(), p.m_pathname);
        }
        return append(p);
    }

    BOOST_FORCEINLINE path& append(const value_type* begin, const value_type* end, codecvt_type const&)
    {
        BOOST_FILESYSTEM_VERSIONED_SYM(append)(begin, end);
        return *this;
    }

    template< class InputIterator >
    typename boost::disable_if< path_detail::is_native_char_ptr< InputIterator >, path& >::type
    append(InputIterator begin, InputIterator end, const codecvt_type& cvt)
    {
        path p;
        if (begin != end)
        {
            std::basic_string< typename std::iterator_traits< InputIterator >::value_type > seq(begin, end);
            path_traits::convert(seq.c_str(), seq.c_str() + seq.size(), p.m_pathname, cvt);
        }
        return append(p);
    }

    //  -----  modifiers  -----

    void clear() BOOST_NOEXCEPT { m_pathname.clear(); }
#ifdef BOOST_POSIX_API
    path& make_preferred()
    {
        // No effect on POSIX
        return *this;
    }
#else // BOOST_WINDOWS_API
    BOOST_FILESYSTEM_DECL path& make_preferred(); // change slashes to backslashes
#endif
    BOOST_FILESYSTEM_DECL path& remove_filename();
    BOOST_FILESYSTEM_DECL path& remove_trailing_separator();
    BOOST_FORCEINLINE path& replace_extension(path const& new_extension = path())
    {
        BOOST_FILESYSTEM_VERSIONED_SYM(replace_extension)(new_extension);
        return *this;
    }
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

    string_type const& native() const BOOST_NOEXCEPT { return m_pathname; }
    const value_type* c_str() const BOOST_NOEXCEPT { return m_pathname.c_str(); }
    string_type::size_type size() const BOOST_NOEXCEPT { return m_pathname.size(); }

    template< class String >
    String string() const;

    template< class String >
    String string(codecvt_type const& cvt) const;

#ifdef BOOST_WINDOWS_API
    std::string string() const
    {
        std::string tmp;
        if (!m_pathname.empty())
            path_traits::convert(m_pathname.c_str(), m_pathname.c_str() + m_pathname.size(), tmp);
        return tmp;
    }
    std::string string(codecvt_type const& cvt) const
    {
        std::string tmp;
        if (!m_pathname.empty())
            path_traits::convert(m_pathname.c_str(), m_pathname.c_str() + m_pathname.size(), tmp, cvt);
        return tmp;
    }

    //  string_type is std::wstring, so there is no conversion
    std::wstring const& wstring() const { return m_pathname; }
    std::wstring const& wstring(codecvt_type const&) const { return m_pathname; }
#else // BOOST_POSIX_API
    //  string_type is std::string, so there is no conversion
    std::string const& string() const { return m_pathname; }
    std::string const& string(codecvt_type const&) const { return m_pathname; }

    std::wstring wstring() const
    {
        std::wstring tmp;
        if (!m_pathname.empty())
            path_traits::convert(m_pathname.c_str(), m_pathname.c_str() + m_pathname.size(), tmp);
        return tmp;
    }
    std::wstring wstring(codecvt_type const& cvt) const
    {
        std::wstring tmp;
        if (!m_pathname.empty())
            path_traits::convert(m_pathname.c_str(), m_pathname.c_str() + m_pathname.size(), tmp, cvt);
        return tmp;
    }
#endif

    //  -----  generic format observers  -----

    //  Experimental generic function returning generic formatted path (i.e. separators
    //  are forward slashes). Motivation: simpler than a family of generic_*string
    //  functions.
#ifdef BOOST_WINDOWS_API
    BOOST_FILESYSTEM_DECL path generic_path() const;
#else
    path generic_path() const { return path(*this); }
#endif

    template< class String >
    String generic_string() const;

    template< class String >
    String generic_string(codecvt_type const& cvt) const;

#ifdef BOOST_WINDOWS_API
    std::string generic_string() const { return generic_path().string(); }
    std::string generic_string(codecvt_type const& cvt) const { return generic_path().string(cvt); }
    std::wstring generic_wstring() const { return generic_path().wstring(); }
    std::wstring generic_wstring(codecvt_type const&) const { return generic_wstring(); }
#else // BOOST_POSIX_API
    //  On POSIX-like systems, the generic format is the same as the native format
    std::string const& generic_string() const { return m_pathname; }
    std::string const& generic_string(codecvt_type const&) const { return m_pathname; }
    std::wstring generic_wstring() const { return this->wstring(); }
    std::wstring generic_wstring(codecvt_type const& cvt) const { return this->wstring(cvt); }
#endif

    //  -----  compare  -----

    BOOST_FORCEINLINE int compare(path const& p) const BOOST_NOEXCEPT // generic, lexicographical
    {
        return BOOST_FILESYSTEM_VERSIONED_SYM(compare)(p);
    }
    int compare(std::string const& s) const { return compare(path(s)); }
    int compare(const value_type* s) const { return compare(path(s)); }

    //  -----  decomposition  -----

    path root_path() const { return path(m_pathname.c_str(), m_pathname.c_str() + find_root_path_size()); }
    // returns 0 or 1 element path even on POSIX, root_name() is non-empty() for network paths
    path root_name() const { return path(m_pathname.c_str(), m_pathname.c_str() + find_root_name_size()); }

    // returns 0 or 1 element path
    path root_directory() const
    {
        path_detail::substring root_dir = find_root_directory();
        const value_type* p = m_pathname.c_str() + root_dir.pos;
        return path(p, p + root_dir.size);
    }

    path relative_path() const
    {
        path_detail::substring root_dir = find_relative_path();
        const value_type* p = m_pathname.c_str() + root_dir.pos;
        return path(p, p + root_dir.size);
    }

    path parent_path() const { return path(m_pathname.c_str(), m_pathname.c_str() + find_parent_path_size()); }

    BOOST_FORCEINLINE path filename() const { return BOOST_FILESYSTEM_VERSIONED_SYM(filename)(); }   // returns 0 or 1 element path
    BOOST_FORCEINLINE path stem() const { return BOOST_FILESYSTEM_VERSIONED_SYM(stem)(); }           // returns 0 or 1 element path
    BOOST_FORCEINLINE path extension() const { return BOOST_FILESYSTEM_VERSIONED_SYM(extension)(); } // returns 0 or 1 element path

    //  -----  query  -----

    bool empty() const BOOST_NOEXCEPT { return m_pathname.empty(); }
    bool filename_is_dot() const;
    bool filename_is_dot_dot() const;
    bool has_root_path() const { return find_root_path_size() > 0; }
    bool has_root_name() const { return find_root_name_size() > 0; }
    bool has_root_directory() const { return find_root_directory().size > 0; }
    bool has_relative_path() const { return find_relative_path().size > 0; }
    bool has_parent_path() const { return find_parent_path_size() > 0; }
    BOOST_FORCEINLINE bool has_filename() const { return BOOST_FILESYSTEM_VERSIONED_SYM(has_filename)(); }
    bool has_stem() const { return !stem().empty(); }
    bool has_extension() const { return !extension().empty(); }
    bool is_relative() const { return !is_absolute(); }
    bool is_absolute() const
    {
        // Windows CE has no root name (aka drive letters)
#if defined(BOOST_WINDOWS_API) && !defined(UNDER_CE)
        return has_root_name() && has_root_directory();
#else
        return has_root_directory();
#endif
    }

    //  -----  lexical operations  -----

    BOOST_FORCEINLINE path lexically_normal() const { return BOOST_FILESYSTEM_VERSIONED_SYM(lexically_normal)(); }
    BOOST_FILESYSTEM_DECL path lexically_relative(path const& base) const;
    path lexically_proximate(path const& base) const
    {
        path tmp(lexically_relative(base));
        return tmp.empty() ? *this : tmp;
    }

    //  -----  iterators  -----

    class iterator;
    friend class iterator;
    typedef iterator const_iterator;
    class reverse_iterator;
    typedef reverse_iterator const_reverse_iterator;

    BOOST_FILESYSTEM_DECL iterator begin() const;
    BOOST_FILESYSTEM_DECL iterator end() const;
    reverse_iterator rbegin() const;
    reverse_iterator rend() const;

    //  -----  static member functions  -----

    static BOOST_FILESYSTEM_DECL std::locale imbue(std::locale const& loc);
    static BOOST_FILESYSTEM_DECL codecvt_type const& codecvt();

    //  -----  deprecated functions  -----

#if !defined(BOOST_FILESYSTEM_NO_DEPRECATED)
    //  recently deprecated functions supplied by default
    path& normalize()
    {
        path tmp(lexically_normal());
        m_pathname.swap(tmp.m_pathname);
        return *this;
    }
    path& remove_leaf() { return remove_filename(); }
    path leaf() const { return filename(); }
    path branch_path() const { return parent_path(); }
    path generic() const { return generic_path(); }
    bool has_leaf() const { return !m_pathname.empty(); }
    bool has_branch_path() const { return !parent_path().empty(); }
    bool is_complete() const { return is_absolute(); }
#endif

#if defined(BOOST_FILESYSTEM_DEPRECATED)
    //  deprecated functions with enough signature or semantic changes that they are
    //  not supplied by default
    std::string file_string() const { return string(); }
    std::string directory_string() const { return string(); }
    std::string native_file_string() const { return string(); }
    std::string native_directory_string() const { return string(); }
    string_type external_file_string() const { return native(); }
    string_type external_directory_string() const { return native(); }
#endif

    //--------------------------------------------------------------------------------------//
    //                            class path private members                                //
    //--------------------------------------------------------------------------------------//
private:
    bool has_filename_v3() const { return !m_pathname.empty(); }
    bool has_filename_v4() const { return find_filename_v4_size() > 0; }
    BOOST_FILESYSTEM_DECL path filename_v3() const;
    path filename_v4() const
    {
        string_type::size_type filename_size = find_filename_v4_size();
        string_type::size_type pos = m_pathname.size() - filename_size;
        const value_type* p = m_pathname.c_str() + pos;
        return path(p, p + filename_size);
    }
    BOOST_FILESYSTEM_DECL path stem_v3() const;
    BOOST_FILESYSTEM_DECL path stem_v4() const;
    BOOST_FILESYSTEM_DECL path extension_v3() const;
    path extension_v4() const
    {
        string_type::size_type extension_size = find_extension_v4_size();
        string_type::size_type pos = m_pathname.size() - extension_size;
        const value_type* p = m_pathname.c_str() + pos;
        return path(p, p + extension_size);
    }

    BOOST_FILESYSTEM_DECL void replace_extension_v3(path const& new_extension);
    BOOST_FILESYSTEM_DECL void replace_extension_v4(path const& new_extension);

    BOOST_FILESYSTEM_DECL path lexically_normal_v3() const;
    BOOST_FILESYSTEM_DECL path lexically_normal_v4() const;

    BOOST_FILESYSTEM_DECL int compare_v3(path const& p) const BOOST_NOEXCEPT;
    BOOST_FILESYSTEM_DECL int compare_v4(path const& p) const BOOST_NOEXCEPT;

    BOOST_FILESYSTEM_DECL void append_v3(const value_type* b, const value_type* e);
    BOOST_FILESYSTEM_DECL void append_v4(const value_type* b, const value_type* e);
    BOOST_FILESYSTEM_DECL void append_v3(path const& p);
    BOOST_FILESYSTEM_DECL void append_v4(path const& p);

    //  Returns: If separator is to be appended, m_pathname.size() before append. Otherwise 0.
    //  Note: An append is never performed if size()==0, so a returned 0 is unambiguous.
    BOOST_FILESYSTEM_DECL string_type::size_type append_separator_if_needed();
    BOOST_FILESYSTEM_DECL void erase_redundant_separator(string_type::size_type sep_pos);

    BOOST_FILESYSTEM_DECL string_type::size_type find_root_name_size() const;
    BOOST_FILESYSTEM_DECL string_type::size_type find_root_path_size() const;
    BOOST_FILESYSTEM_DECL path_detail::substring find_root_directory() const;
    BOOST_FILESYSTEM_DECL path_detail::substring find_relative_path() const;
    BOOST_FILESYSTEM_DECL string_type::size_type find_parent_path_size() const;
    BOOST_FILESYSTEM_DECL string_type::size_type find_filename_v4_size() const;
    BOOST_FILESYSTEM_DECL string_type::size_type find_extension_v4_size() const;

private:
    /*
     * m_pathname has the type, encoding, and format required by the native
     * operating system. Thus for POSIX and Windows there is no conversion for
     * passing m_pathname.c_str() to the O/S API or when obtaining a path from the
     * O/S API. POSIX encoding is unspecified other than for dot and slash
     * characters; POSIX just treats paths as a sequence of bytes. Windows
     * encoding is UCS-2 or UTF-16 depending on the version.
     */
    string_type m_pathname;     // Windows: as input; backslashes NOT converted to slashes,
                                // slashes NOT converted to backslashes
};

namespace detail {
BOOST_FILESYSTEM_DECL int lex_compare_v3(path::iterator first1, path::iterator last1, path::iterator first2, path::iterator last2);
BOOST_FILESYSTEM_DECL int lex_compare_v4(path::iterator first1, path::iterator last1, path::iterator first2, path::iterator last2);
BOOST_FILESYSTEM_DECL path const& dot_path();
BOOST_FILESYSTEM_DECL path const& dot_dot_path();
} // namespace detail

#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
typedef path wpath;
#endif

//------------------------------------------------------------------------------------//
//                             class path::iterator                                   //
//------------------------------------------------------------------------------------//

class path::iterator :
    public boost::iterator_facade<
        path::iterator,
        const path,
        boost::bidirectional_traversal_tag
    >
{
private:
    friend class boost::iterator_core_access;
    friend class boost::filesystem::path;
    friend class boost::filesystem::path::reverse_iterator;
    friend BOOST_FILESYSTEM_DECL int detail::lex_compare_v3(path::iterator first1, path::iterator last1, path::iterator first2, path::iterator last2);

    path const& dereference() const { return m_element; }

    bool equal(iterator const& rhs) const
    {
        return m_path_ptr == rhs.m_path_ptr && m_pos == rhs.m_pos;
    }

    BOOST_FORCEINLINE void increment() { BOOST_FILESYSTEM_VERSIONED_SYM(increment)(); }
    BOOST_FORCEINLINE void decrement() { BOOST_FILESYSTEM_VERSIONED_SYM(decrement)(); }

private:
    BOOST_FILESYSTEM_DECL void increment_v3();
    BOOST_FILESYSTEM_DECL void increment_v4();
    BOOST_FILESYSTEM_DECL void decrement_v3();
    BOOST_FILESYSTEM_DECL void decrement_v4();

private:
    // current element
    path m_element;
    // path being iterated over
    const path* m_path_ptr;
    // position of m_element in m_path_ptr->m_pathname.
    // if m_element is implicit dot, m_pos is the
    // position of the last separator in the path.
    // end() iterator is indicated by
    // m_pos == m_path_ptr->m_pathname.size()
    string_type::size_type m_pos;
};

//------------------------------------------------------------------------------------//
//                         class path::reverse_iterator                               //
//------------------------------------------------------------------------------------//

class path::reverse_iterator :
    public boost::iterator_facade<
        path::reverse_iterator,
        const path,
        boost::bidirectional_traversal_tag
    >
{
public:
    explicit reverse_iterator(iterator itr) :
        m_itr(itr)
    {
        if (itr != itr.m_path_ptr->begin())
            m_element = *--itr;
    }

private:
    friend class boost::iterator_core_access;
    friend class boost::filesystem::path;

    path const& dereference() const { return m_element; }
    bool equal(reverse_iterator const& rhs) const { return m_itr == rhs.m_itr; }

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

private:
    iterator m_itr;
    path m_element;
};

//------------------------------------------------------------------------------------//
//                                                                                    //
//                              non-member functions                                  //
//                                                                                    //
//------------------------------------------------------------------------------------//

//  std::lexicographical_compare would infinitely recurse because path iterators
//  yield paths, so provide a path aware version
inline bool lexicographical_compare(path::iterator first1, path::iterator last1, path::iterator first2, path::iterator last2)
{
    return BOOST_FILESYSTEM_VERSIONED_SYM(detail::lex_compare)(first1, last1, first2, last2) < 0;
}

inline bool operator==(path const& lhs, path const& rhs)
{
    return lhs.compare(rhs) == 0;
}

inline bool operator==(path const& lhs, path::string_type const& rhs)
{
    return lhs.compare(rhs) == 0;
}

inline bool operator==(path::string_type const& lhs, path const& rhs)
{
    return rhs.compare(lhs) == 0;
}

inline bool operator==(path const& lhs, const path::value_type* rhs)
{
    return lhs.compare(rhs) == 0;
}

inline bool operator==(const path::value_type* lhs, path const& rhs)
{
    return rhs.compare(lhs) == 0;
}

inline bool operator!=(path const& lhs, path const& rhs)
{
    return lhs.compare(rhs) != 0;
}

inline bool operator!=(path const& lhs, path::string_type const& rhs)
{
    return lhs.compare(rhs) != 0;
}

inline bool operator!=(path::string_type const& lhs, path const& rhs)
{
    return rhs.compare(lhs) != 0;
}

inline bool operator!=(path const& lhs, const path::value_type* rhs)
{
    return lhs.compare(rhs) != 0;
}

inline bool operator!=(const path::value_type* lhs, path const& rhs)
{
    return rhs.compare(lhs) != 0;
}

// TODO: why do == and != have additional overloads, but the others don't?

inline bool operator<(path const& lhs, path const& rhs)
{
    return lhs.compare(rhs) < 0;
}
inline bool operator<=(path const& lhs, path const& rhs)
{
    return !(rhs < lhs);
}
inline bool operator>(path const& lhs, path const& rhs)
{
    return rhs < lhs;
}
inline bool operator>=(path const& lhs, path const& rhs)
{
    return !(lhs < rhs);
}

// Note: Declared as a template to delay binding to Boost.ContainerHash functions and make the dependency optional
template< typename T >
inline typename boost::enable_if< boost::is_same< T, path >, std::size_t >::type hash_value(T const& p) BOOST_NOEXCEPT
{
#ifdef BOOST_WINDOWS_API
    std::size_t seed = 0;
    for (typename T::value_type const* it = p.c_str(); *it; ++it)
        hash_combine(seed, *it == L'/' ? L'\\' : *it);
    return seed;
#else // BOOST_POSIX_API
    return hash_range(p.native().begin(), p.native().end());
#endif
}

inline void swap(path& lhs, path& rhs) BOOST_NOEXCEPT
{
    lhs.swap(rhs);
}

inline path operator/(path const& lhs, path const& rhs)
{
    path p = lhs;
    p /= rhs;
    return p;
}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
inline path operator/(path&& lhs, path const& rhs)
{
    lhs /= rhs;
    return std::move(lhs);
}
#endif

//  inserters and extractors
//    use boost::io::quoted() to handle spaces in paths
//    use '&' as escape character to ease use for Windows paths

template< class Char, class Traits >
inline std::basic_ostream< Char, Traits >&
operator<<(std::basic_ostream< Char, Traits >& os, path const& p)
{
    return os << boost::io::quoted(p.template string< std::basic_string< Char > >(), static_cast< Char >('&'));
}

template< class Char, class Traits >
inline std::basic_istream< Char, Traits >&
operator>>(std::basic_istream< Char, Traits >& is, path& p)
{
    std::basic_string< Char > str;
    is >> boost::io::quoted(str, static_cast< Char >('&'));
    p = str;
    return is;
}

//  name_checks

//  These functions are holdovers from version 1. It isn't clear they have much
//  usefulness, or how to generalize them for later versions.

BOOST_FILESYSTEM_DECL bool portable_posix_name(std::string const& name);
BOOST_FILESYSTEM_DECL bool windows_name(std::string const& name);
BOOST_FILESYSTEM_DECL bool portable_name(std::string const& name);
BOOST_FILESYSTEM_DECL bool portable_directory_name(std::string const& name);
BOOST_FILESYSTEM_DECL bool portable_file_name(std::string const& name);
BOOST_FILESYSTEM_DECL bool native(std::string const& name);

namespace detail {

//  For POSIX, is_directory_separator() and is_element_separator() are identical since
//  a forward slash is the only valid directory separator and also the only valid
//  element separator. For Windows, forward slash and back slash are the possible
//  directory separators, but colon (example: "c:foo") is also an element separator.
inline bool is_directory_separator(path::value_type c) BOOST_NOEXCEPT
{
    return c == path::separator
#ifdef BOOST_WINDOWS_API
        || c == path::preferred_separator
#endif
        ;
}

inline bool is_element_separator(path::value_type c) BOOST_NOEXCEPT
{
    return c == path::separator
#ifdef BOOST_WINDOWS_API
        || c == path::preferred_separator || c == L':'
#endif
        ;
}

} // namespace detail

//------------------------------------------------------------------------------------//
//                  class path miscellaneous function implementations                 //
//------------------------------------------------------------------------------------//

inline path::reverse_iterator path::rbegin() const
{
    return reverse_iterator(end());
}
inline path::reverse_iterator path::rend() const
{
    return reverse_iterator(begin());
}

inline bool path::filename_is_dot() const
{
    // implicit dot is tricky, so actually call filename(); see path::filename() example
    // in reference.html
    path p(filename());
    return p.size() == 1 && *p.c_str() == dot;
}

inline bool path::filename_is_dot_dot() const
{
    return size() >= 2 && m_pathname[size() - 1] == dot && m_pathname[size() - 2] == dot && (m_pathname.size() == 2 || detail::is_element_separator(m_pathname[size() - 3]));
    // use detail::is_element_separator() rather than detail::is_directory_separator
    // to deal with "c:.." edge case on Windows when ':' acts as a separator
}

//--------------------------------------------------------------------------------------//
//                     class path member template specializations                       //
//--------------------------------------------------------------------------------------//

template<>
inline std::string path::string< std::string >() const
{
    return string();
}

template<>
inline std::wstring path::string< std::wstring >() const
{
    return wstring();
}

template<>
inline std::string path::string< std::string >(const codecvt_type& cvt) const
{
    return string(cvt);
}

template<>
inline std::wstring path::string< std::wstring >(const codecvt_type& cvt) const
{
    return wstring(cvt);
}

template<>
inline std::string path::generic_string< std::string >() const
{
    return generic_string();
}

template<>
inline std::wstring path::generic_string< std::wstring >() const
{
    return generic_wstring();
}

template<>
inline std::string path::generic_string< std::string >(codecvt_type const& cvt) const
{
    return generic_string(cvt);
}

template<>
inline std::wstring path::generic_string< std::wstring >(codecvt_type const& cvt) const
{
    return generic_wstring(cvt);
}

//--------------------------------------------------------------------------------------//
//                     path_traits convert function implementations                     //
//                        requiring path::codecvt() be visable                          //
//--------------------------------------------------------------------------------------//

namespace path_traits { //  without codecvt

inline void convert(const char* from,
                    const char* from_end, // 0 for null terminated MBCS
                    std::wstring& to)
{
    convert(from, from_end, to, path::codecvt());
}

inline void convert(const wchar_t* from,
                    const wchar_t* from_end, // 0 for null terminated MBCS
                    std::string& to)
{
    convert(from, from_end, to, path::codecvt());
}

inline void convert(const char* from, std::wstring& to)
{
    BOOST_ASSERT(!!from);
    convert(from, 0, to, path::codecvt());
}

inline void convert(const wchar_t* from, std::string& to)
{
    BOOST_ASSERT(!!from);
    convert(from, 0, to, path::codecvt());
}

} // namespace path_traits
} // namespace filesystem
} // namespace boost

//----------------------------------------------------------------------------//

#include <boost/filesystem/detail/footer.hpp>

#endif // BOOST_FILESYSTEM_PATH_HPP

/* path.hpp
+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
*/