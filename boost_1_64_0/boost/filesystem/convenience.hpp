//  boost/filesystem/convenience.hpp  ----------------------------------------//

//  Copyright Beman Dawes, 2002-2005
//  Copyright Vladimir Prus, 2002
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/filesystem

//----------------------------------------------------------------------------//

#ifndef BOOST_FILESYSTEM3_CONVENIENCE_HPP
#define BOOST_FILESYSTEM3_CONVENIENCE_HPP

#include <boost/config.hpp>

# if defined( BOOST_NO_STD_WSTRING )
#   error Configuration not supported: Boost.Filesystem V3 and later requires std::wstring support
# endif

#include <boost/filesystem/operations.hpp>
#include <boost/system/error_code.hpp>

#include <boost/config/abi_prefix.hpp> // must be the last #include

namespace boost
{
  namespace filesystem
  {

# ifndef BOOST_FILESYSTEM_NO_DEPRECATED

    inline std::string extension(const path & p)
    {
      return p.extension().string();
    }

    inline std::string basename(const path & p)
    {
      return p.stem().string();
    }

    inline path change_extension( const path & p, const path & new_extension )
    {
      path new_p( p );
      new_p.replace_extension( new_extension );
      return new_p;
    }

# endif


  } // namespace filesystem
} // namespace boost

#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#endif // BOOST_FILESYSTEM3_CONVENIENCE_HPP

/* convenience.hpp
R1v6iAm2J2MXbkGIcu7Nwr4nMjb6KLlFP22OqOL4ONgsdI+hfVSgAxi4uiCS/nBCGNrK1YI63kR3wacnvyxIT3pi/KBTqtntGT02EsPZeRajWiLh5G4mrNWi/vPKo85YVuJgMz6YOCat2qqRAKklelQ5uR/egTk+BtfLYtxnMCCNq8sc4+ZJ8RXBNYle0dcax8vfBqLjNTrBND69myMNcaTCtQvved0miCAcf8B9GrXSDOPypAFbTBvy9O4IWhz7fZIc6H62QmIJHGG2A1ImJ1/f/5YVyJ/bdVuo0RXA+fElbOdPZtWlUUnwcZmgPnZgHbURwLD7Y0zjJK6S80PD4ZTLU3mI5/DXxUexa7X7YEcGDyS7e0wfFaa13GDRgkA93+1zkroHpDPEHiWIxQQumoLF2ktRL7k2IjDjrvdocV2nsh4wtPsaGTsoe+bC6nnaAEPsDEz0LgCdqFd/xFRtcixE1eCfTnAAWHFRdqEj1KSOGXPLAcsjrJ/X3g6fVAkC50k2/h0Ri3dHfRlLZeEeOpdQkullPVbfI37pGvEHbtTkatxREjAbbEftqQ==
*/