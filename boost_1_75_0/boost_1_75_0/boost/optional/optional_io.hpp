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
XXu9VyU3VtWsycHDz1ueqv+e/uZL00///UU/1Jaap8rP5lzftab/aKetl0jt+Vj3VZ/7m4Ant21Pnm1WF1e/8W1V732svPr2rd+tkwUmQSj/RMmdp7XkpiADUykpf1v7j3hCwgcLyak/zewfwuZHS94fXnGx2La7U21DR6ZPXUfH73dQX6fR4b5vfDunqx/S3W5aiVZSIHWq9b76M6ol58daKfXVHZGT3Tk3PG/Cn6JZzcQI3Bv1R6PiufWYP4eEDDoJ5QaqrrwIvwgcnLn/5ZxG5S/RI78zW+jzrAk/sdYY+m7/gGm3v0mK6t+8+8b8k4ctLf2X/j/jSrd0dSKe/+Qdu/6JJ3Vr4+XjXXspW23m1FpR3X8C1Yy2khfWX1aeZa3p5J8l3d5aa7jxpU5XPK3S44VKJemXaR5MyaiKjfX28d+zuNHBlfhJs/N5yaT5ujKqiDoJviMFPHb053pOIr2xfGaf1arA5sZ2rUPVJShWI6EZP4IG1hyt2wE2PlMn/vWA7AetzY9fv2/xnPNA67u74Ptf62e0NHGjQ5eAn0+m/1WRxsjk+w81IW+UdJ/E+f+PjesMa6rJwrufbS2ISCcCCggqTUBDDXEFAlKkSW9C6BCQDgmBVZQeEJFepUsvkQ5RqtQQOqFJJ0AINQFCwmZ3/+6vO888U945M+e8594554Zm6f4rB1wEe/8kCUJbVPC4yD86c710nvTr
*/