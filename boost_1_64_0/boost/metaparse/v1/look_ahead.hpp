#ifndef BOOST_METAPARSE_V1_LOOK_AHEAD_HPP
#define BOOST_METAPARSE_V1_LOOK_AHEAD_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)   2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct look_ahead
      {
      private:
        template <class S, class Pos>
        struct no_error :
          accept<
            typename get_result<typename P::template apply<S, Pos> >::type,
            S,
            Pos
          >
        {};
      public:
        typedef look_ahead type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename P::template apply<S, Pos>,
            no_error<S, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* look_ahead.hpp
rRugjQjY2G8UtfCu/Y1un4rGOkT3hqlAHQ8eURJbmNzE+Ee3XJNNQNs1U3eEKb4xnjHd5ufW5gaxojrvsEL3IpspajehsYV+rXhtyYyh3/5E5/MokGH3nCiDzkItcJkLseU1iuTeyHgrtvdv6FLmgf+PeyCA3aGulreobqIvzCFOFlNNUgcbWuyH27gsFIfUjRRIl/mRW86zrCqbseD7eYxEnSRDL/jEOs2iWodU1+wSPni82SehTnDTNj4qi5irUHUfwMC7HNphN8CaTi5g/vVcrHf6xIW6yu6dz1K+yHyrtTTJYG33jI3YRazfGY8hromHxBMX/FYei9rJtYozTqkYJo7rmEyL7aK0hYhpHxAw2c/Y3gCZxqUc/x2S3+1v7eIHs5bookvsDBVh+uq2gTws200af6si3GEJEwBNnTW25GuCY/iC312c8lAqfxCLVUgaP8yhRjgslQyYNKJN8ntVqbdd4FzhmlAebKbSTsFqBOHfW1jhhhRriUAxZdXgNEfeB9AD0dC95VWd/hAOwOdVWTl8PamKr1xMilOZBnLpYRoPu5Hm8is/Fg==
*/