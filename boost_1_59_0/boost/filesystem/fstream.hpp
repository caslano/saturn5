//  boost/filesystem/fstream.hpp  ------------------------------------------------------//

//  Copyright Beman Dawes 2002
//  Copyright Andrey Semashev 2021

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

//--------------------------------------------------------------------------------------//

#ifndef BOOST_FILESYSTEM_FSTREAM_HPP
#define BOOST_FILESYSTEM_FSTREAM_HPP

#include <boost/filesystem/config.hpp>
#include <boost/filesystem/path.hpp>
#include <iosfwd>
#include <fstream>

#include <boost/filesystem/detail/header.hpp> // must be the last #include

#if defined(BOOST_WINDOWS_API)
// On Windows, except for standard libaries known to have wchar_t overloads for
// file stream I/O, use path::string() to get a narrow character c_str()
#if (defined(_CPPLIB_VER) && _CPPLIB_VER >= 405 && !defined(_STLPORT_VERSION)) || \
    (defined(_LIBCPP_VERSION) && _LIBCPP_VERSION >= 7000 && defined(_LIBCPP_HAS_OPEN_WITH_WCHAR))
// Use wide characters directly
// Note: We don't use C++17 std::filesystem::path as a means to pass wide paths
// to file streams because of various problems:
// - std::filesystem is available in gcc 8 but it is broken there (fails to compile path definition
//   on Windows). Compilation errors seem to be fixed since gcc 9.
// - In gcc 10.2 and clang 8.0.1 on Cygwin64, the path attempts to convert the wide string to narrow
//   and fails in runtime. This may be system locale dependent, and performing character code conversion
//   is against the purpose of using std::filesystem::path anyway.
// - Other std::filesystem implementations were not tested, so it is not known if they actually work
//   with wide paths.
#define BOOST_FILESYSTEM_C_STR(p) p.c_str()
#else
// Use narrow characters, since wide not available
#define BOOST_FILESYSTEM_C_STR(p) p.string().c_str()
#endif
#endif // defined(BOOST_WINDOWS_API)

#if !defined(BOOST_FILESYSTEM_C_STR)
#define BOOST_FILESYSTEM_C_STR(p) p.c_str()
#endif

#if defined(BOOST_MSVC)
#pragma warning(push)
// 'boost::filesystem::basic_fstream<charT>' : inherits 'std::basic_istream<_Elem,_Traits>::std::basic_istream<_Elem,_Traits>::_Add_vtordisp1' via dominance
#pragma warning(disable : 4250)
#endif

namespace boost {
namespace filesystem {

//--------------------------------------------------------------------------------------//
//                                  basic_filebuf                                       //
//--------------------------------------------------------------------------------------//

template< class charT, class traits = std::char_traits< charT > >
class basic_filebuf :
    public std::basic_filebuf< charT, traits >
{
public:
    BOOST_DEFAULTED_FUNCTION(basic_filebuf(), {})
    BOOST_DELETED_FUNCTION(basic_filebuf(basic_filebuf const&))
    BOOST_DELETED_FUNCTION(basic_filebuf const& operator=(basic_filebuf const&))

public:
    basic_filebuf< charT, traits >* open(path const& p, std::ios_base::openmode mode)
    {
        return std::basic_filebuf< charT, traits >::open(BOOST_FILESYSTEM_C_STR(p), mode) ? this : 0;
    }
};

//--------------------------------------------------------------------------------------//
//                                 basic_ifstream                                       //
//--------------------------------------------------------------------------------------//

template< class charT, class traits = std::char_traits< charT > >
class basic_ifstream :
    public std::basic_ifstream< charT, traits >
{
public:
    BOOST_DEFAULTED_FUNCTION(basic_ifstream(), {})

    // use two signatures, rather than one signature with default second
    // argument, to workaround VC++ 7.1 bug (ID VSWhidbey 38416)

    explicit basic_ifstream(path const& p) :
        std::basic_ifstream< charT, traits >(BOOST_FILESYSTEM_C_STR(p), std::ios_base::in) {}

    basic_ifstream(path const& p, std::ios_base::openmode mode) :
        std::basic_ifstream< charT, traits >(BOOST_FILESYSTEM_C_STR(p), mode) {}

    BOOST_DELETED_FUNCTION(basic_ifstream(basic_ifstream const&))
    BOOST_DELETED_FUNCTION(basic_ifstream const& operator=(basic_ifstream const&))

public:
    void open(path const& p)
    {
        std::basic_ifstream< charT, traits >::open(BOOST_FILESYSTEM_C_STR(p), std::ios_base::in);
    }

    void open(path const& p, std::ios_base::openmode mode)
    {
        std::basic_ifstream< charT, traits >::open(BOOST_FILESYSTEM_C_STR(p), mode);
    }
};

//--------------------------------------------------------------------------------------//
//                                 basic_ofstream                                       //
//--------------------------------------------------------------------------------------//

template< class charT, class traits = std::char_traits< charT > >
class basic_ofstream :
    public std::basic_ofstream< charT, traits >
{
public:
    BOOST_DEFAULTED_FUNCTION(basic_ofstream(), {})

    // use two signatures, rather than one signature with default second
    // argument, to workaround VC++ 7.1 bug (ID VSWhidbey 38416)

    explicit basic_ofstream(path const& p) :
        std::basic_ofstream< charT, traits >(BOOST_FILESYSTEM_C_STR(p), std::ios_base::out) {}

    basic_ofstream(path const& p, std::ios_base::openmode mode) :
        std::basic_ofstream< charT, traits >(BOOST_FILESYSTEM_C_STR(p), mode) {}

    BOOST_DELETED_FUNCTION(basic_ofstream(basic_ofstream const&))
    BOOST_DELETED_FUNCTION(basic_ofstream const& operator=(basic_ofstream const&))

public:
    void open(path const& p)
    {
        std::basic_ofstream< charT, traits >::open(BOOST_FILESYSTEM_C_STR(p), std::ios_base::out);
    }

    void open(path const& p, std::ios_base::openmode mode)
    {
        std::basic_ofstream< charT, traits >::open(BOOST_FILESYSTEM_C_STR(p), mode);
    }
};

//--------------------------------------------------------------------------------------//
//                                  basic_fstream                                       //
//--------------------------------------------------------------------------------------//

template< class charT, class traits = std::char_traits< charT > >
class basic_fstream :
    public std::basic_fstream< charT, traits >
{
public:
    BOOST_DEFAULTED_FUNCTION(basic_fstream(), {})

    // use two signatures, rather than one signature with default second
    // argument, to workaround VC++ 7.1 bug (ID VSWhidbey 38416)

    explicit basic_fstream(path const& p) :
        std::basic_fstream< charT, traits >(BOOST_FILESYSTEM_C_STR(p), std::ios_base::in | std::ios_base::out) {}

    basic_fstream(path const& p, std::ios_base::openmode mode) :
        std::basic_fstream< charT, traits >(BOOST_FILESYSTEM_C_STR(p), mode) {}

    BOOST_DELETED_FUNCTION(basic_fstream(basic_fstream const&))
    BOOST_DELETED_FUNCTION(basic_fstream const& operator=(basic_fstream const&))

public:
    void open(path const& p)
    {
        std::basic_fstream< charT, traits >::open(BOOST_FILESYSTEM_C_STR(p), std::ios_base::in | std::ios_base::out);
    }

    void open(path const& p, std::ios_base::openmode mode)
    {
        std::basic_fstream< charT, traits >::open(BOOST_FILESYSTEM_C_STR(p), mode);
    }
};

//--------------------------------------------------------------------------------------//
//                                    typedefs                                          //
//--------------------------------------------------------------------------------------//

typedef basic_filebuf< char > filebuf;
typedef basic_ifstream< char > ifstream;
typedef basic_ofstream< char > ofstream;
typedef basic_fstream< char > fstream;

typedef basic_filebuf< wchar_t > wfilebuf;
typedef basic_ifstream< wchar_t > wifstream;
typedef basic_ofstream< wchar_t > wofstream;
typedef basic_fstream< wchar_t > wfstream;

} // namespace filesystem
} // namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#include <boost/filesystem/detail/footer.hpp>

#endif // BOOST_FILESYSTEM_FSTREAM_HPP

/* fstream.hpp
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
*/