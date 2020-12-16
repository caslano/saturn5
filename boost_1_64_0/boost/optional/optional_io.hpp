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
JTuhYKisOdnJZtk5Qnn2w3j1szwx34R9Qr1W/cNjWnb8ieUg2XGOh5afD8XrZ9TeifJjf6dzLPf94UdjdzLlSX1UKF+ImsftvkfFa6pKyqGdVUb1oR85RYgU9vDAx+nbYOzz30bpj8KSyXWfnumdPgj6PGc5pT8o1rp9Y9egj/lA1+HMRV21M6e6Urup2D7FMT/YeBTT5/Lg4/w9D8O/8vsUNwVtPFD5WG6CjGxWPkkw2/Vmh6Lyip1zm7p373HiUaDv+TJ5uvqRyup8nXDa8RwcowmJS1x9EPXdHvdLPPDNM/12KW61WCbSKZ5k1K7bBMSOJN10wiPYq9zMPn5DpVlygOJ7Im7qZrZlviR2D49OqwfcrWk8hs8o8zy8mW3Gu2IOr+PL84Sg9lyCtJ0AbTPei8zU2T6d0w8BniR68Pf6TfN0wtOg+2fqo3z/0bWhrugcT7L7j/QY3kftcAVaIYPjLLNtmvTdfYPw2sf5fL5CcbCRivnumv1H8Vlx8nUl6jEu7r7Eo5uR+Cj3xezYnUg7tqA9AdxevrmC/fg47eQWfSfSbLttNL8pj7L/47TYnUg+xBUCmJ9nFvPTacWAO5lG34mU+E60WP+MnMI7sTkb8q6I075rue5jPO5O3S2Pq0xP8D1Bx/V9sFubn/f4Qlj3+5aI/ufokrD4kft5OvJowX2wjOvuk2KcoTnv66a0kwl3iev1w7eI72rUYbG9FhvyZRnHNoXsV/CMPptKYX3V1F2w+ebZUlwdHOdRnKZs81+gcsK2MSveTmrvE3ynmqX6bzDCcdI2/8t2//FxM1lJ1ZTWli5IfF/p77VbT0iaN0jz3w7YLSJu/Qbeqd1ZrfGyjX2b+pJoFNYmtj1kf8pzs1iK9r5PtHZ9dzGfpGenH6HNEm3d9Pn100S7E2X10Tq/DqDnrK9Q3r1FED3b1NnreMLrZ883pn2wuWdynPLKst/J5xBdHtm5atl6gXA89jqlK+E8a+yRUG+hiWJrnJmEM4t2B8byt13a2OXvRzfNJupa2bIlKH2CGMA02S40f1N1tvduhlP6A6IaGMtRFzqjIzq+HwRjIo1sBJ3nur0AF6RggxE/Tpx3fueZthcxmaH4j5Kcy55wnMvG71t0e0oVoMwP2eJwIzqp31cSxgkb1Zvjoyv370bCLfZF8GWKZz2Xis7eK0S1d4x4xnsvcJS83b1N4qTjVXCV+AQ2ujdZf7Xe8AbFIW+mbZcxlvj8WJwHqklipMsYo3I5bUrZ9/E5SnvL15m/fyTr8w2Ke070JBuinnZ/30HluRnX/M71OsYo5eO022AbZmrTf5J2HvBVFGkA330vvUCAJGBoIfQeepHeOwFBqdISegkQkCaGDgooigcKIpwgiKgIKEVQRKqCgL2Lih4qak5BUVHvPzPfvmzyFuHuwm/4v+ntm9mZ2ZnZ49r+ZEghPbaSuyK0WXNM4gPnNDvreJ73qxJvR1zB7diJy33WQJd1oP85rO3PhCRYLazVIZHW5pDYwD3OY7Zrv977RZ70/s5kFUnvJ5I2td6WjKqMqo26GdXGGmQ9bl3ypTjrRTqsiFB111VbVD/q51FWMl+zqoQErXG44k7M136Hjx0ywr1nu5N219S+RJ0naTOnzDqS34pWkZBwq2xIlOxP0/2YvgCTHwH5e0aHsT+kMO11ofWDPxtJXMU459kQ6V90OcndkXL29kXt552Q4lafvOchJL+lnzF3cyU6/eVTSl/K19bqzQrAbwE56qLdPcea5UqRdXqxp5XZr3Y3K816g7L8DHWB+elt9kx335L7/Sqd38RA3N9r/5WtJOnneum0fmVXxEVnZuXbrAq2s0egg05XOdLjlrd2uoU=
*/