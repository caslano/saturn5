//  boost/chrono/round.hpp  ------------------------------------------------------------//

//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_CEIL_HPP
#define BOOST_CHRONO_CEIL_HPP

#include <boost/chrono/duration.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * rounds up
     */
    template <class To, class Rep, class Period>
    To ceil(const duration<Rep, Period>& d)
    {
        To t = duration_cast<To>(d);
        if (t < d)
            ++t;
        return t;
    }

  } // namespace chrono
} // namespace boost

#endif

/* ceil.hpp
x0f/3rsGZ7+p77TKdPTHVT9c2dHXbXN0f4aj0zaK3rmSo39aRk96J1pvWEbvVkYfWUa/vYw+r4y+d3v0O6aPbo9+9+CQHY7eVd1vUb2H6jNU76n6ZtUvreroB1Xvre613412H6V6f9Xjdzp6dS2v6qr30/BL0SPzF3gvOj8V34t2b/RedP76lNEfU72Z6vtVX6zpf1nG/YFdugao5bewjN5md/S9/draPqwuc29iRmsj5tE4
*/