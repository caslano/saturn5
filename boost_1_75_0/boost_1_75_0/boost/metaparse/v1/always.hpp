#ifndef BOOST_METAPARSE_V1_ALWAYS_HPP
#define BOOST_METAPARSE_V1_ALWAYS_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Result>
      struct always
      {
      private:
        template <class Res>
        struct apply_unchecked :
          accept<
            Result,
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef always type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename P::template apply<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* always.hpp
SRvu8mPErANFgS2O0dREIAVvy/FdKe7p9BugH1Au73QAO3iPU2tm55XWppLL/TBvlIuhColfL7YxWbFe9KjzSLXeEMUa2osf1eIMUrRSeGc3Ms0lzm/nRfCg5t6kJ9U6eN7oOnhTk62qVwWWnqFHewzPMeMHFqaoPe3Ope/Ig4YDk5BATV1OAvIkOJJQd2oZ0szcsUYjx3H33J+ozZzt+yxBt476pEMeiHD7Hf0ZoLIW3Z0tTX0oW3oLNm9GWci10B2yVLgWmsmdz3SuBOKWy7li9A5pfQdNlKXLZNyD2ZLrfqa18rTTZQgD1NyJPf7bwcuL1D9Fz+7j7HEfo0QHTKIrsH3+NHwSWOQ+ziLbirsZpNHEgD/DC6jutWsftIm4euMJCJeCIACmoTUWl/kvIW0OI5nJNZYmRjZLuQe0etddDB4zybU8Zq1rRovQV8YWUvoErePkKuv3GwxKrrIak3gBd5U9TFrscojQ6FfhWplA8FxFbjjXBxg4tYDKbfpWAoYkqhgy/OymjYmELaQNU+UO6vn+UcCUQ2EsYwkLritjiT6xvs8Sd/8bP3Z/FsyMPIRaD19pq/ztUrrn1DOEZo1wlOus5DejXkEYDfup6grW+YEfc6htGz0Vm8H3aET86dp1HMGTINy0iiOHrpH7EzaGO/hiPpWyp5Nssu3ZuQI6R4RJKtRdKTRcmaO7MsdwBRzv7H3t8X3kfv8k
*/