#ifndef BOOST_METAPARSE_V1_CPP98_FIRST_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_FIRST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/nth_of_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct first_of :
        nth_of_c<
          0,
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, P)
        >
      {};
    }
  }
}

#endif


/* first_of.hpp
c84ONzhnz8zcih4Nl4iXORjDMAtsdKftWD1hKQ3igFAT2yWUVwS2/1cfHnYJnSm5rGh4rsfWtokUc+Th6FJJpqnU7ShoeUFCVgRS5xu+wTpZ6qbNCIkg/Ir2zJMw8OGBz3ugOyfd8qmnQf+NctNZqLq8ty82oCyhOLfp38R7LLSXZsaR32DySPBu43GZQm/NuUY6pwufWq3XGmstHX5B0trqFYQznhWAD6eJYCfXecG8znXLvZ6GoNRtGX9fdV59Y5AUB/CYkcPnu2RbeB6a/5pTV8YCnzbMZTGImNd7YKULV9hYG36OZsIkBHigBIkO4YKzfk9oV+Jl46HZ42pKOcChOKTbZroBrVe73/G4ei5nDVq9ht5CQ1GESyyp15qoQNBvBn3SYFZdEmpzjM1T7n9NS4fyh5HyZQ18enN/lDHbnMMv483pmMeD8F5fZCeUxwZSUpCHIrhdIeQvlDzQTu2SiegmctFIrSmZ8/bVWRIm2DCid1JaEXB6dUhIY0U4vJeOPhOVwHyUAzJf5vo9cArgTSlXkM5Lt5RRl6z2bKcOzycqXxn5EXEaiA==
*/