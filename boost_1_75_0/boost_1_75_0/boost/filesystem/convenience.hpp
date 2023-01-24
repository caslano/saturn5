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
+PjSZBP6YYcVcD/sZPLD5mPwdk4xNeONzfqVoB+MD4bHwwmlvkyqg8Z6ZhFLCIfyVmFoLCEZUbpOno0GJ/5nwNo1EJaxT/nyuihTRpXlzipLBy9YRLFLGV0qAax93iXs0l28KqXLPHoF2uV5WEDq7l1BlzVYvAr/34L/L8f/l7H/vTXBIp/3WaRXVdOYnQafZM1M7MqXQFf7BncYk1dobyz0ZgW+8cvQJ72XfcEiNBbC9usfSo8yqbTk1pT/kpYMC6Ulk9XsKgQQw5O0TSfORFTdAA2YBiv3yIv8VIzG5/I5VGD/jBQmhNa1IA8qw1BEkp0ulGTnMSWqH/h2eh52+t9eZuasGkAeZ+vAGYmSKrzGqhdlsfPV3YdzFJXL1JfYtn8+Of4cUmK3JJjQa8KidCyE9t1u9hYmUzkLr0B34PB1RVMIGMA7i8TJnK5CYGOiotdYnjcXB7IlR808wOM/foj4ayhdbmcXJdJ4XhCNpFeksun9M0Gd3hyn/D06cDk53bGGYbY10MH4RfoZTocZ/tFSPhCsmf3rj6BPikXy7g7iRM9BaNqqn+epyis5OM9T8v1vV2H5iFRMZeXwjywGq0HdTJ/lM53pvhmK4VttqiGAp8M/vyAIjRxSXt/E5hPbsCj/Got+uuXgy+KUJ6TaHN6tpQ45jiu99T3y9IbYuaxnKVJwK3tYwh6ecsc6MKGbks8aDVgYKinolIIu
*/