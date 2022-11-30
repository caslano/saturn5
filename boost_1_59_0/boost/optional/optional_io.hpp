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

#ifndef BOOST_NO_IOSTREAM
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

#endif // BOOST_NO_IOSTREAM
#endif

/* optional_io.hpp
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
*/