#ifndef BOOST_METAPARSE_V1_SPACE_HPP
#define BOOST_METAPARSE_V1_SPACE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/whitespace_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

#include <boost/metaparse/v1/util/is_whitespace.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        accept_when<one_char, util::is_whitespace<>, error::whitespace_expected>
        space;
    }
  }
}

#endif



/* space.hpp
qk1pjNtgo5LdxbB1+e8B7Ep/ZSYkMRrRsn0mKvvksu4Ue5I1G4+33WzO1rrd+qG69nvz1QxvyYmQmNTOFWPKe+yQY+MblsqbNCHNifCutrsBbsm05JgtUBOxE6jDlmBUSc85IVvAv2zxMiSFre0lN12eXK97pBYXF3jtMVTPn45czJWeW4dfpg4g2n5UqCf8f1hXT4GQD/1Y3PwVSOY8ec6Ap/98l65RKIb/kG0Hevrh4Npk0QUkRuIZEgD+RJoYx2KNmBzg2E1/3AvBCThDfDpHk3wSUh0vfdIe1x7GFnRdDsiMJaD1ZBkejTxTgRevye6j5MVEsaZsRaNoM8uCmRNscqlNErZ2aCLamWTEWMRSA9zPA3wpL0WElWPF9mtrfq+1cZQ0d57T9C0jsrYxDdilZ+o68JuCwCwkwQwJtX+AtkPqLplam6mkIn7qyuRJ9wt4m53ReMDTC2Eyxg2swxWZgte34sxZ8X/RjtH/9g1xDRIrZnsB57a84bsjeGFvEx3WjO3o8kLfd7ZVAQS4MHqOln//A83R67PLbOwPBLgFughgbN79P91N5Q==
*/