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
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
*/