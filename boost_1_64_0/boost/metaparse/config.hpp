#ifndef BOOST_METAPARSE_CONFIG_HPP
#define BOOST_METAPARSE_CONFIG_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

/*
 * Compiler workarounds
 */

// BOOST_NO_CXX11_CONSTEXPR is not defined in gcc 4.6
#if \
  defined BOOST_NO_CXX11_CONSTEXPR || defined BOOST_NO_CONSTEXPR || ( \
    !defined __clang__ && defined __GNUC__ \
    && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7)) \
  )

#  define BOOST_NO_CONSTEXPR_C_STR

#endif

/*
 * C++ standard to use
 */

// Allow overriding this
#ifndef BOOST_METAPARSE_STD

// special-case MSCV >= 1900 as its constexpr support is good enough for
// Metaparse
#  if \
    !defined BOOST_NO_CXX11_VARIADIC_TEMPLATES \
    && !defined BOOST_NO_VARIADIC_TEMPLATES \
    && ( \
      (!defined BOOST_NO_CONSTEXPR && !defined BOOST_NO_CXX11_CONSTEXPR) \
      || (defined _MSC_VER && _MSC_VER >= 1900) \
    ) \
    && (!defined BOOST_GCC || BOOST_GCC >= 40700)

#    if !defined BOOST_NO_CXX14_CONSTEXPR

#      define BOOST_METAPARSE_STD 2014

#    else

#      define BOOST_METAPARSE_STD 2011

#    endif

#  else

#    define BOOST_METAPARSE_STD 1998

#  endif

#endif

/*
 * Metaparse config
 */

#if BOOST_METAPARSE_STD >= 2011
#  define BOOST_METAPARSE_VARIADIC_STRING
#endif

#endif


/* config.hpp
nbkqthPstk6a8YEPYxD1g7fFCvaK2JHnv43HnDVI3pY3e85kxZyB0bZ82zh0KMYH1pjkrMqi2HDMSyOjKCakZQ0zk+eP5LVvuPIsvrUxXFdpdVrAblVPnwXb2cwo0ghpr7PFJmEfgUUSixxReDW2Bew9sWOf08r7AJvDsZHYoDptLTiHgBk1M4Ntfd6mLua6hVGkIvafEH9njAEsJTE6L9nAwmm5DJa+GB+tU7l/16nYuuXxlTB2xRr2/infO6lYuTR6zLUbjMa3ttcE+R13ppyXmvLuWh+YgdjnNzP9mGul3KrWh+T5p2Jn8lT9iHMBmJnYjW91xmAfgaUmlvmfhNvYDy2Tl6vZvuQ97AfFrhbNE4lzuWL3IvqWxT4Ca0Ys/+tv+TB2MIxBeZ+An5r63nqwrsR+K1mjC/Z7K1JOeZ4kjprynIaLmDqW3GDBxqcHrA+xaVW7dMectYbjJu2/rbEYuxushl5apzNFn2A72yXvo2jfkL+xHBjdH8pOv7MDxxmYmY7rhBzNMNdgwWL3U1NzrdSZ+fQjPY4zasp7iRMVq+B04fN4oj3ZnnJfkJWacl+QjZr6nA1YFWK2yssGYx+BZSI2dvjacMwLrVO5f8lPTB1L8dTUbydQU+6lSqSm3Esl4oLHZyWm9pGNmJozOzX1veDE1H5wgsUQi7FkLY1jECwNMXpPlJeack+Un5r6HXBqyr1bogMx9Tvg1JR7qRzU1Pu6qCn3WbmpKc9peKmp93WBBZvP4sFiiXUrbD+AfduROf6B3dXOX0xgpZ+324zt7GwULYW0rLHl5LN6YBuIpR8eegrb0sUooogViqiYAnPd1SjWEDt/4kwPLAdWilhM7qcLsZ3d4JyP2IG/MtzDsQSWidicJ23xnMgFloFYpnbf5De0GfOBZSE2/d1SOWeBhaIp95AzlsiY6B7crIzZwApr/WcE23vtYlUcSz20/wo0e//boqKYl//A+RmxqRXebsVyYHmIvdyxryTGzpjoGdzsYOmJLZoZI7D/GHOBZSbW/1Pa+9h/jPnArMSqN72XD2PoKfs9lfoeCbAoNOU9Er3kOEulvJvCARaGpqwl9JLbS6lszwUWRYxuz4vbA1O258ftgalruGB5NQsDGzAgQT5n2tsoyhDL/WlMEZyzwEoQG1yk6g7MJ9h2nbT7Q8t3xO31lW0JU9fy+srYQ5XYhUvGHqrEbgfLRIzG7gQLQ1PWZoilUNaoXYy5GfNQU/97ccn4QpT4/BgfmBJfIsYHpsRn7QfbQ1PWKvvJ7emV7TnAoojR7bnAMhGj2/OA1dZJW9ZlQD7shwHBt+dkzAUWrC1esGBt8TN1BhgTA4Nvzz4w+PacYGFoylhizMWYmzEPY16wf7V+0IHN8K34gf0+RF7365Q1CCdYDCm3w+c8g/kcSsop6wWJYBVJuecHRjTFGIbLXAsl116wKGI01/FgmYjRXCeChRGjsYsRcs3qXwHxvYmYgvEx5lWstj36E26PMcdIWNcndkt34hD2EdjvxDJsHl4Ky40yihzEzpVevgPHhGIdD9Qrju0EK0xsatWO8lswjNlGJ6/zRvuF7zEvYDrN/hHJn2GMAysUIq3MgA0OtHFwLaNZEljkhaX3sN8nGkUBIW1StV3yfaNgnXTSBjapNADL/W4UEXppEVtby+dlphpFQ63Ov8EyVKkiv0cL5tTsF9h47zkfjolpcl3qJ9jL+1v/xH4AK0+sWRldIawTLJpY69hNBzAGsDrEzkVH/obtnG4UdmIVGza3Yc7ArhM7WnP8Cez3GUYxnNjJLNdxfFpnGkVxur2HPzdgnWCpiNHrI5dSru3n+XKfBitArEeTq9kxZx6jKEIs+40=
*/