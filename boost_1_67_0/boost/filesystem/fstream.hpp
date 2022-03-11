//  boost/filesystem/fstream.hpp  ------------------------------------------------------//

//  Copyright Beman Dawes 2002

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

//--------------------------------------------------------------------------------------//

#ifndef BOOST_FILESYSTEM3_FSTREAM_HPP
#define BOOST_FILESYSTEM3_FSTREAM_HPP

#include <boost/config.hpp>

# if defined( BOOST_NO_STD_WSTRING )
#   error Configuration not supported: Boost.Filesystem V3 and later requires std::wstring support
# endif

#include <boost/filesystem/path.hpp>
#include <iosfwd>
#include <fstream>

#include <boost/config/abi_prefix.hpp> // must be the last #include

//  on Windows, except for standard libaries known to have wchar_t overloads for
//  file stream I/O, use path::string() to get a narrow character c_str()
#if defined(BOOST_WINDOWS_API) \
  && (!defined(_CPPLIB_VER) || _CPPLIB_VER < 405 || defined(_STLPORT_VERSION))
  // !Dinkumware || early Dinkumware || STLPort masquerading as Dinkumware
# define BOOST_FILESYSTEM_C_STR string().c_str()  // use narrow, since wide not available
#else  // use the native c_str, which will be narrow on POSIX, wide on Windows
# define BOOST_FILESYSTEM_C_STR c_str()
#endif

#if defined(BOOST_MSVC)
#pragma warning(push)
// 'boost::filesystem::basic_fstream<charT>' : inherits 'std::basic_istream<_Elem,_Traits>::std::basic_istream<_Elem,_Traits>::_Add_vtordisp1' via dominance
#pragma warning(disable: 4250)
#endif

namespace boost
{
namespace filesystem
{

//--------------------------------------------------------------------------------------//
//                                  basic_filebuf                                       //
//--------------------------------------------------------------------------------------//

  template < class charT, class traits = std::char_traits<charT> >
  class basic_filebuf : public std::basic_filebuf<charT,traits>
  {
  private: // disallow copying
    basic_filebuf(const basic_filebuf&);
    const basic_filebuf& operator=(const basic_filebuf&);

  public:
    basic_filebuf() {}
    virtual ~basic_filebuf() {}

    basic_filebuf<charT,traits>*
      open(const path& p, std::ios_base::openmode mode)
    {
      return std::basic_filebuf<charT,traits>::open(p.BOOST_FILESYSTEM_C_STR, mode)
        ? this : 0;
    }
  };

//--------------------------------------------------------------------------------------//
//                                 basic_ifstream                                       //
//--------------------------------------------------------------------------------------//

  template < class charT, class traits = std::char_traits<charT> >
  class basic_ifstream : public std::basic_ifstream<charT,traits>
  {
  private: // disallow copying
    basic_ifstream(const basic_ifstream&);
    const basic_ifstream& operator=(const basic_ifstream&);

  public:
    basic_ifstream() {}

    // use two signatures, rather than one signature with default second
    // argument, to workaround VC++ 7.1 bug (ID VSWhidbey 38416)

    explicit basic_ifstream(const path& p)
      : std::basic_ifstream<charT,traits>(p.BOOST_FILESYSTEM_C_STR, std::ios_base::in) {}

    basic_ifstream(const path& p, std::ios_base::openmode mode)
      : std::basic_ifstream<charT,traits>(p.BOOST_FILESYSTEM_C_STR, mode) {}

    void open(const path& p)
      { std::basic_ifstream<charT,traits>::open(p.BOOST_FILESYSTEM_C_STR, std::ios_base::in); }

    void open(const path& p, std::ios_base::openmode mode)
      { std::basic_ifstream<charT,traits>::open(p.BOOST_FILESYSTEM_C_STR, mode); }

    virtual ~basic_ifstream() {}
  };

//--------------------------------------------------------------------------------------//
//                                 basic_ofstream                                       //
//--------------------------------------------------------------------------------------//

  template < class charT, class traits = std::char_traits<charT> >
  class basic_ofstream : public std::basic_ofstream<charT,traits>
  {
  private: // disallow copying
    basic_ofstream(const basic_ofstream&);
    const basic_ofstream& operator=(const basic_ofstream&);

  public:
    basic_ofstream() {}

    // use two signatures, rather than one signature with default second
    // argument, to workaround VC++ 7.1 bug (ID VSWhidbey 38416)

    explicit basic_ofstream(const path& p)
      : std::basic_ofstream<charT,traits>(p.BOOST_FILESYSTEM_C_STR, std::ios_base::out) {}

    basic_ofstream(const path& p, std::ios_base::openmode mode)
      : std::basic_ofstream<charT,traits>(p.BOOST_FILESYSTEM_C_STR, mode) {}

    void open(const path& p)
      { std::basic_ofstream<charT,traits>::open(p.BOOST_FILESYSTEM_C_STR, std::ios_base::out); }

    void open(const path& p, std::ios_base::openmode mode)
      { std::basic_ofstream<charT,traits>::open(p.BOOST_FILESYSTEM_C_STR, mode); }

    virtual ~basic_ofstream() {}
  };

//--------------------------------------------------------------------------------------//
//                                  basic_fstream                                       //
//--------------------------------------------------------------------------------------//

  template < class charT, class traits = std::char_traits<charT> >
  class basic_fstream : public std::basic_fstream<charT,traits>
  {
  private: // disallow copying
    basic_fstream(const basic_fstream&);
    const basic_fstream & operator=(const basic_fstream&);

  public:
    basic_fstream() {}

    // use two signatures, rather than one signature with default second
    // argument, to workaround VC++ 7.1 bug (ID VSWhidbey 38416)

    explicit basic_fstream(const path& p)
      : std::basic_fstream<charT,traits>(p.BOOST_FILESYSTEM_C_STR,
          std::ios_base::in | std::ios_base::out) {}

    basic_fstream(const path& p, std::ios_base::openmode mode)
      : std::basic_fstream<charT,traits>(p.BOOST_FILESYSTEM_C_STR, mode) {}

    void open(const path& p)
      { std::basic_fstream<charT,traits>::open(p.BOOST_FILESYSTEM_C_STR,
          std::ios_base::in | std::ios_base::out); }

    void open(const path& p, std::ios_base::openmode mode)
      { std::basic_fstream<charT,traits>::open(p.BOOST_FILESYSTEM_C_STR, mode); }

    virtual ~basic_fstream() {}

  };

//--------------------------------------------------------------------------------------//
//                                    typedefs                                          //
//--------------------------------------------------------------------------------------//

  typedef basic_filebuf<char> filebuf;
  typedef basic_ifstream<char> ifstream;
  typedef basic_ofstream<char> ofstream;
  typedef basic_fstream<char> fstream;

  typedef basic_filebuf<wchar_t> wfilebuf;
  typedef basic_ifstream<wchar_t> wifstream;
  typedef basic_ofstream<wchar_t> wofstream;
  typedef basic_fstream<wchar_t> wfstream;

} // namespace filesystem
} // namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#endif  // BOOST_FILESYSTEM3_FSTREAM_HPP

/* fstream.hpp
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
*/