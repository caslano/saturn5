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
r7uEBgbxYF1wOHk84lWw0PXgrUjraob32/IWE8CF7Yr1zJpxiMbAALtdPWxtWIa5hnRaHGqnErrmtLum306xa9UpM+IcECjlSDqkhTVq24YwdqAs3jvEVKPHj4aWg7fSjVSwibpZD1v3z8692Nlg4/S3q3gBqm4iIrPXWSFNp+zBx2OJh3cDoeNEvY72Tm5Bo648ovrQaULN34eUZq9wPKDXqr+eBKK2pIYDH38SIMPcOz6s/RSwHLRmD4qKJ2MLjbQm+zPsQRon2UqT5+Ovqm0IrrrGblizKGr2SfABXwbuwgX8MxbU7r+r2o4KJT/wy2VuEjGwS5RrvRWef9lPhUI6Bq1k1mg+M2AzcG7XTHVAo1cw/oxeszobIOB7vlHOb9yulqeZZCFHriPQ9PGPCHp8H5ANLFou0Ldbw/3nxPMSyBH5bhL4y9xUnVRgCFBPkTXoaEX5DiBdwtTXMtvO1CJTHU24IQhlp4lqcwNpkZ/eV659APWqUbL9xgKn1x/XypAxKmGRTp9zk4FGGfBJcQUoyHwtHyNuz8YKA7/yhKRtRdPSMryqwoytpg==
*/