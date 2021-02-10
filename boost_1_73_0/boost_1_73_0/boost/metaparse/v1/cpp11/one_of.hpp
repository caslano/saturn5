#ifndef BOOST_METAPARSE_V1_CPP11_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/cpp11/impl/eval_later_result.hpp>
#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct one_of;

      template <class P, class... Ps>
      struct one_of<P, Ps...>
      {
        typedef one_of type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos>>::type,
            boost::mpl::eval_if<
              typename is_error<
                typename one_of<Ps...>::template apply<S, Pos>
              >::type,
              impl::eval_later_result<
                typename P::template apply<S, Pos>,
                typename one_of<Ps...>::template apply<S, Pos>
              >,
              typename one_of<Ps...>::template apply<S, Pos>
            >,
            typename P::template apply<S, Pos>
          >
        {};
      };

      template <>
      struct one_of<> : fail<error::none_of_the_expected_cases_found> {};
    }
  }
}

#endif


/* one_of.hpp
TY6oXeDbiNwMi8zyEoJrhWBgXDMMC0dXIRiEj7Y5ujBRk/B6RgCJ4AnrrzYna1J5xAilyHrVQUd6alaA5OXzja3UUjVQbFqMmaq6oKTt2SXbivxJi8clC2oo7UfSv9lscPcuNqFYs6gAAE5e0sjlklbWsdnJK27DLm1VFuKdkz05aS+WJxpHLc70pjpoj6s2fA8Fj758J/ZXG6wz45kwT1Dwxk7N2meVcYQFBv8pDvFsaFgveInNm3yr5wnyT4Vro/rOVDFMyYphXppx/aSqsqKTDjkqMJfd8Fy2FTbtHPIV5SJJEfkRrMrNgSN8qoo0aj56VVUTb7qKG2sWy2I2PfUGTQLAAFld6ggapeSlappjs1UlOQWWTRq2/bTSN/LgRSXHqIAyByfsn1Xmrzrocz81K7jwb1QueoQJ1UYmVOUe6dIcSiqraHp9N7tW7URqzNXbK3KivDMVmdQYKeZg5RLYBgR+Mjfhko4rqegYPQ5KFz3GMVAzMY4oGuMF2BsNNMvk98hAf0fWm86ekH7MNDaTejezeqYXykzGpjxHRxqiFaIDSbikKYX9XNAWECdXtaNThxW1ps/pXArTuqXoG9V3Rw0745xUzZLY/vVfHKFlNrh8lPkZ9FIcNGbNFzfCisP4yT3Dqt2DUqWC
*/