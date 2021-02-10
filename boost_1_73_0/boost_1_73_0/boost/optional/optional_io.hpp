// Copyright (C) 2005, Fernando Luis Cacciola Carballal.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//
#ifndef BOOST_OPTIONAL_OPTIONAL_IO_FLC_19NOV2002_HPP
#define BOOST_OPTIONAL_OPTIONAL_IO_FLC_19NOV2002_HPP

#include <istream>
#include <ostream>

#include "boost/none.hpp"
#include "boost/optional/optional.hpp"


namespace boost
{

template<class CharType, class CharTrait>
inline
std::basic_ostream<CharType, CharTrait>&
operator<<(std::basic_ostream<CharType, CharTrait>& out, none_t)
{
  if (out.good())
  {
    out << "--";
  }
   
  return out;
}

template<class CharType, class CharTrait, class T>
inline
std::basic_ostream<CharType, CharTrait>&
operator<<(std::basic_ostream<CharType, CharTrait>& out, optional<T> const& v)
{
  if (out.good())
  {
    if (!v)
         out << "--" ;
    else out << ' ' << *v ;
  }

  return out;
}

template<class CharType, class CharTrait, class T>
inline
std::basic_istream<CharType, CharTrait>&
operator>>(std::basic_istream<CharType, CharTrait>& in, optional<T>& v)
{
  if (in.good())
  {
    int d = in.get();
    if (d == ' ')
    {
      T x;
      in >> x;
#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
      v = boost::move(x);
#else
      v = x;
#endif
    }
    else
    {
      if (d == '-')
      {
        d = in.get();

        if (d == '-')
        {
          v = none;
          return in;
        }
      }

      in.setstate( std::ios::failbit );
    }
  }

  return in;
}

} // namespace boost

#endif


/* optional_io.hpp
qX0v9tl1b0W8yJD4Ot6A5xcewq+8FVY+6dYaIY1s+LSVGiWJm5pgv6xZxdCFMP3nnJYAdRcao4B/rtEji87S9m5/nVCIpS1IG02zf9hl253/7bQp6y3fKHuL8wQdBQ0bYoVWiw0F1noHFDl2dI8ns+Td6O8u/U7NkvYpglW30RxugDwp+3YFoqXAamEHbkbfp1YHvahV/Nkpdnsb9W/+L5e40V8edPPdd8H7o19o9z98rh2E+8Ulhq+nbBR6DOvHuNKiPsr8xg2GIRzfO6tbNqynqLdC1yAI9yRMX2y3DzJmWR972NwYJhUv9Io/ME98RKnkTNXlfjPv8L+KTuuCK/cJa85QiM81VynHd9Jel5zORw2HboTd6K6Hb3PoZ2B71jhujpox3x6GgoUvm0ts2PnW+RdQSwMECgAAAAgALWdKUucbBGI/AwAAeAgAACIACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjU5OC5jVVQFAAG2SCRgvVTRbts4EHzXV2zdFztQrSZPbd0cTnHU1I3PCmTnigABCFpaWSwkUiCpxEHTf7+lLCcxcqmLQ3EybFL0zsxydsng4Pc9HhzA3oe1X0YPjS3iQqtvmNp/j2bsHjYfQl3TuE8kgEfIPRvAfsg99FsI
*/