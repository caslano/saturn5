//  filesystem path_traits.hpp  --------------------------------------------------------//

//  Copyright Beman Dawes 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

#ifndef BOOST_FILESYSTEM_PATH_TRAITS_HPP
#define BOOST_FILESYSTEM_PATH_TRAITS_HPP

#include <boost/filesystem/config.hpp>
#include <boost/system/error_category.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/core/enable_if.hpp>
#include <cstddef>
#include <cwchar> // for mbstate_t
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <locale>
#include <boost/assert.hpp>

#include <boost/filesystem/detail/header.hpp> // must be the last #include

namespace boost {
namespace filesystem {

BOOST_FILESYSTEM_DECL system::error_category const& codecvt_error_category() BOOST_NOEXCEPT;
//  uses std::codecvt_base::result used for error codes:
//
//    ok:       Conversion successful.
//    partial:  Not all source characters converted; one or more additional source
//              characters are needed to produce the final target character, or the
//              size of the target intermediate buffer was too small to hold the result.
//    error:    A character in the source could not be converted to the target encoding.
//    noconv:   The source and target characters have the same type and encoding, so no
//              conversion was necessary.

class directory_entry;

namespace path_traits {

typedef std::codecvt< wchar_t, char, std::mbstate_t > codecvt_type;

//  is_pathable type trait; allows disabling over-agressive class path member templates

template< class T >
struct is_pathable
{
    static const bool value = false;
};

template<>
struct is_pathable< char* >
{
    static const bool value = true;
};

template<>
struct is_pathable< const char* >
{
    static const bool value = true;
};

template<>
struct is_pathable< wchar_t* >
{
    static const bool value = true;
};

template<>
struct is_pathable< const wchar_t* >
{
    static const bool value = true;
};

template<>
struct is_pathable< std::string >
{
    static const bool value = true;
};

template<>
struct is_pathable< std::wstring >
{
    static const bool value = true;
};

template<>
struct is_pathable< std::vector< char > >
{
    static const bool value = true;
};

template<>
struct is_pathable< std::vector< wchar_t > >
{
    static const bool value = true;
};

template<>
struct is_pathable< std::list< char > >
{
    static const bool value = true;
};

template<>
struct is_pathable< std::list< wchar_t > >
{
    static const bool value = true;
};

template<>
struct is_pathable< directory_entry >
{
    static const bool value = true;
};

//  Pathable empty

template< class Container >
inline
    // disable_if aids broken compilers (IBM, old GCC, etc.) and is harmless for
    // conforming compilers. Replace by plain "bool" at some future date (2012?)
    typename boost::disable_if< boost::is_array< Container >, bool >::type
    empty(Container const& c)
{
    return c.begin() == c.end();
}

template< class T >
inline bool empty(T* const& c_str)
{
    BOOST_ASSERT(c_str);
    return !*c_str;
}

template< typename T, std::size_t N >
inline bool empty(T (&x)[N])
{
    return !x[0];
}

// value types differ  ---------------------------------------------------------------//
//
//   A from_end argument of 0 is less efficient than a known end, so use only if needed

//  with codecvt

BOOST_FILESYSTEM_DECL
void convert(const char* from,
             const char* from_end, // 0 for null terminated MBCS
             std::wstring& to, codecvt_type const& cvt);

BOOST_FILESYSTEM_DECL
void convert(const wchar_t* from,
             const wchar_t* from_end, // 0 for null terminated MBCS
             std::string& to, codecvt_type const& cvt);

inline void convert(const char* from, std::wstring& to, codecvt_type const& cvt)
{
    BOOST_ASSERT(from);
    convert(from, 0, to, cvt);
}

inline void convert(const wchar_t* from, std::string& to, codecvt_type const& cvt)
{
    BOOST_ASSERT(from);
    convert(from, 0, to, cvt);
}

//  without codecvt

inline void convert(const char* from,
                    const char* from_end, // 0 for null terminated MBCS
                    std::wstring& to);

inline void convert(const wchar_t* from,
                    const wchar_t* from_end, // 0 for null terminated MBCS
                    std::string& to);

inline void convert(const char* from, std::wstring& to);

inline void convert(const wchar_t* from, std::string& to);

// value types same  -----------------------------------------------------------------//

// char with codecvt

inline void convert(const char* from, const char* from_end, std::string& to, codecvt_type const&)
{
    BOOST_ASSERT(from);
    BOOST_ASSERT(from_end);
    to.append(from, from_end);
}

inline void convert(const char* from, std::string& to, codecvt_type const&)
{
    BOOST_ASSERT(from);
    to += from;
}

// wchar_t with codecvt

inline void convert(const wchar_t* from, const wchar_t* from_end, std::wstring& to, codecvt_type const&)
{
    BOOST_ASSERT(from);
    BOOST_ASSERT(from_end);
    to.append(from, from_end);
}

inline void convert(const wchar_t* from, std::wstring& to, codecvt_type const&)
{
    BOOST_ASSERT(from);
    to += from;
}

// char without codecvt

inline void convert(const char* from, const char* from_end, std::string& to)
{
    BOOST_ASSERT(from);
    BOOST_ASSERT(from_end);
    to.append(from, from_end);
}

inline void convert(const char* from, std::string& to)
{
    BOOST_ASSERT(from);
    to += from;
}

// wchar_t without codecvt

inline void convert(const wchar_t* from, const wchar_t* from_end, std::wstring& to)
{
    BOOST_ASSERT(from);
    BOOST_ASSERT(from_end);
    to.append(from, from_end);
}

inline void convert(const wchar_t* from, std::wstring& to)
{
    BOOST_ASSERT(from);
    to += from;
}

//  Source dispatch  -----------------------------------------------------------------//

//  contiguous containers with codecvt
template< class U >
inline void dispatch(std::string const& c, U& to, codecvt_type const& cvt)
{
    if (!c.empty())
        convert(&*c.begin(), &*c.begin() + c.size(), to, cvt);
}
template< class U >
inline void dispatch(std::wstring const& c, U& to, codecvt_type const& cvt)
{
    if (!c.empty())
        convert(&*c.begin(), &*c.begin() + c.size(), to, cvt);
}
template< class U >
inline void dispatch(std::vector< char > const& c, U& to, codecvt_type const& cvt)
{
    if (!c.empty())
        convert(&*c.begin(), &*c.begin() + c.size(), to, cvt);
}
template< class U >
inline void dispatch(std::vector< wchar_t > const& c, U& to, codecvt_type const& cvt)
{
    if (!c.empty())
        convert(&*c.begin(), &*c.begin() + c.size(), to, cvt);
}

//  contiguous containers without codecvt
template< class U >
inline void dispatch(std::string const& c, U& to)
{
    if (!c.empty())
        convert(&*c.begin(), &*c.begin() + c.size(), to);
}
template< class U >
inline void dispatch(std::wstring const& c, U& to)
{
    if (!c.empty())
        convert(&*c.begin(), &*c.begin() + c.size(), to);
}
template< class U >
inline void dispatch(std::vector< char > const& c, U& to)
{
    if (!c.empty())
        convert(&*c.begin(), &*c.begin() + c.size(), to);
}
template< class U >
inline void dispatch(std::vector< wchar_t > const& c, U& to)
{
    if (!c.empty())
        convert(&*c.begin(), &*c.begin() + c.size(), to);
}

//  non-contiguous containers with codecvt
template< class Container, class U >
inline
    // disable_if aids broken compilers (IBM, old GCC, etc.) and is harmless for
    // conforming compilers. Replace by plain "void" at some future date (2012?)
    typename boost::disable_if< boost::is_array< Container >, void >::type
    dispatch(Container const& c, U& to, codecvt_type const& cvt)
{
    if (!c.empty())
    {
        std::basic_string< typename Container::value_type > s(c.begin(), c.end());
        convert(s.c_str(), s.c_str() + s.size(), to, cvt);
    }
}

//  c_str
template< class T, class U >
inline void dispatch(T* const& c_str, U& to, codecvt_type const& cvt)
{
    //    std::cout << "dispatch() const T *\n";
    BOOST_ASSERT(c_str);
    convert(c_str, to, cvt);
}

//  Note: there is no dispatch on C-style arrays because the array may
//  contain a string smaller than the array size.

BOOST_FILESYSTEM_DECL
void dispatch(directory_entry const& de,
#ifdef BOOST_WINDOWS_API
              std::wstring& to,
#else
              std::string& to,
#endif
              codecvt_type const&);

//  non-contiguous containers without codecvt
template< class Container, class U >
inline
    // disable_if aids broken compilers (IBM, old GCC, etc.) and is harmless for
    // conforming compilers. Replace by plain "void" at some future date (2012?)
    typename boost::disable_if< boost::is_array< Container >, void >::type
    dispatch(Container const& c, U& to)
{
    if (!c.empty())
    {
        std::basic_string< typename Container::value_type > seq(c.begin(), c.end());
        convert(seq.c_str(), seq.c_str() + seq.size(), to);
    }
}

//  c_str
template< class T, class U >
inline void dispatch(T* const& c_str, U& to)
{
    //    std::cout << "dispatch() const T *\n";
    BOOST_ASSERT(c_str);
    convert(c_str, to);
}

//  Note: there is no dispatch on C-style arrays because the array may
//  contain a string smaller than the array size.

BOOST_FILESYSTEM_DECL
void dispatch(directory_entry const& de,
#ifdef BOOST_WINDOWS_API
              std::wstring& to
#else
              std::string& to
#endif
);

} // namespace path_traits
} // namespace filesystem
} // namespace boost

#include <boost/filesystem/detail/footer.hpp>

#endif // BOOST_FILESYSTEM_PATH_TRAITS_HPP

/* path_traits.hpp
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
*/