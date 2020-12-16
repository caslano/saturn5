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
fUOSeI9L4GWjsZhZLlaJNycrhQxEOacjpDYaCiM7Qap52A/fSkfCX5jO/0Sv/q/3x8xB6KRBuNGpDLAOp2peLr6Vv3SyIbprIuuzpWpRr4yML9pUGL90C9FmuJPGDqW/w4/HyoHqSqIa+1ChunQk5905gEYnSGnDqD/Jp3I9/ZUzEMyaBPbAaDYQKpkyGgIxzPMJEuYOBVEfJHSAAkVCaZj+QgVeVivwnZ8qQGdk9Vm4SHKe0a4tAL0L2WQcBg15rIQ15GqVzp/8omLrTyApTG48QyMxObDSgkqfflLKynZFFzTdC/0F2dMHIi4ybh7MDNl3dCYWwAcL6ri3xIMOpR/7TKIbUZS4noBEKW8fwd1C+DEOUzSfJGGm2/tSmLlICjOlQRRm4Mi/8cBuR/38+W//WOXjAaeQfDx+HMnHHx1vIx93oyHV+I4cUhfLIfXNxLjy8YvzNPn4+MmqfDx73g+Vj6tmKvLxG/0SsxeMntnsfGhqG+wF35Vb5Otd8zh2gvY4NqkfKRe+l3fNlr6XDXxmGwgxcQrObGGIm5ykZB3D9deATFl/jmKaC8Ba/3dyoit0humZgFr2yNRb42GBEq5u0J0vwe8ShODy8nu05kXYWTWsbPFPBq7I4ScDs5i8ChXthOfZEzwmgZMvgE3Ng5VwmKcHy3OEVrqpjBWKm/yzU+lmZ5XE7Ya4YaD46NEKRQ+m9oF6d9brvetdpd7eodwJLS4X/jFO58L2cRq1e1Vqm46Kz4WgcWlHOy50UOs87XydC/TCYkcbLjx9vJULOedzLjxUrFCMLeBcyNbr3VGttwvqDbK0GB/3Hgm0lUd0jiQphTOgcaxGKPqOQqh+CNXKL2l5ZhGtcqRVDlzeSGvDZTqVP6tUFg2xZyMKaYyBU5iNM9QOY68FPPSaRTQDfg0cy38F53C2l+PlMdTC0E4KBc1WC0qDgqK3yh25JqAwbjasU5QBKQ38rvDXZzIHuNf+f3dD9ZUyNvdmiKUprVwuTavlhQhi7N/fIqbfxvTMwVzM2s3lz42YmnUmHyc4DlF2+pKEugD2JFzEiRKlYW8ipUajKZcPUTE05QbkaboZ6OIgLCNC9wAh4248RZtTKu4YKWpk6Tqmy+ykXWYZVIM9dFZu6wZGltmOSwdirSigMynfY8/wmC18eBBvYQcnIG8prtvNx9c/ofLkzAR6jcqgN6FZEj0k0P/qUBg0EexKuqfanzH5RZ5cQWtFIZ4Wb8CESkq4BPZp2Wb5kI9sOKZU8udILzuDS4enx294f2vDSyqUhm86kkuxh0W3Ql7BWCXvFsgjqbNLcZ2PTrnPeUMw5OVzUCogl1WaamtPpweu/summlV++LbM3j7mO6MN9rE6pPRQmTiUm0FncKgX0UfYzMZo9zBgdd0Rx3g2hhvPdkjj2ZgswnhNNZ5l0ujcuytNroJGSYCPzkUpivFs2D8UkF4CpCyFaOrGs0YmMBxrnlaR8ayIjGdFzHhWZBrPykcwFevd15QSpg3gJXwijWdFAHokgb6mgvYToFv+zd6RQEdVJGcmE5hcJNwJIAwQIFwSMOBwyQSCDkuUqAiRyyiwxkUxysSNmoRgYCU7RAMei3ghq66KKMquG/AKohIVXfDGa+LqLj+OuqiroiKzVV3d/fv//MlMAN3d9xzeJ/27q6qr+/dRXV1d3U5hxokL4MeYxqoblaC/WsjzJnGk6wBJ8vwQKL31AwvVHufyHtqzo8SGWeEZVCItf3BTmGxs6Ho4+OsvYygrypwOO1R4+kkNQyGZ9PzxCfPjaWEc6hLQY88fw2O5RUsWma2Ki8W9TCMPfAfUmh87hPP9ZjyIgW9ClCHfDrgSvpToFrMJ84c=
*/