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
89irGOZ1K0SpgfKuhQTDJu0kOrBNUuY88vh2pioSFwwbDEXiDICKxNlmrpsgodIm86PldBkf1hdLs1bg2QoCZaMC8TvnKQG7gnGfAz+p4tx2FVxxEK+G6/GMImUVF80Q66qtjBamVYyFN8EV23izGACMMHwAsMRtj8MqElZ3eB07/P28XlwsOj85hnlrvSw1wOcEleog5B/SzanCLgPJ4xzvlhwFD8c/lDrOkhxnSY6Kh+Nol4GMhnNYkuM8D8c=
*/