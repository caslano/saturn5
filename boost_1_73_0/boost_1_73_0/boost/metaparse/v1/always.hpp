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
5L6uFnkkOs88Rv+R6/MP+QFQSwMECgAAAAgALWdKUh8X15BXAQAAIAIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjI3VVQFAAG2SCRgRVJNT8MwDL1H6n+whnYcEbsgTVEBQRE7raxlCG6hddVqbT0lZqP/Hjf7yiGxY/u95ziG0XNhPcbKNH1FcmxxOJArfaxe81SlT9lGrZN8rYy+Row+Jt9Ahm6PbuabEpVxuGsHiZaWbazGXYEspnAAeETFtWUYkQVq6yXgCUpCDw0/CO6x1OgTlDA8tw32fGIogiMJPvDGquKdZJ89ML3tMCiHCrmowULVtAiVow64RnBEDGXjsGByAxwarqGn4lBKrT4Wgymo62xfBvSF1tO3VZYv08VUYNPVOtf6bj6/h9lMwrMOuabyhGH0pXS0T2KliQ26phpg7A5sxeiCmPHxobYefhB7mPiaeKLMPuRKjztHTAW1sfrIkjXYnvqho18fjVPJQNgf8c92uxZvhVZuP18ilaTZJlL5V5rAMlLZ8juBIDcKUzzb7x/LPBKJVwqjL7z6+in+AVBLAwQKAAAACAAtZ0pSo6j8sdcBAADTAwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEyMjhV
*/