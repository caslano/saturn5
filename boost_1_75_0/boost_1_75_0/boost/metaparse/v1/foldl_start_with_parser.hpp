#ifndef BOOST_METAPARSE_V1_FOLDL_START_WITH_PARSER_HPP
#define BOOST_METAPARSE_V1_FOLDL_START_WITH_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class StateP, class ForwardOp>
      class foldl_start_with_parser
      {
      private:
        template <class Res>
        struct apply_unchecked :
          foldl<P, typename get_result<Res>::type, ForwardOp>::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef foldl_start_with_parser type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename StateP::template apply<S, Pos> >::type,
            typename StateP::template apply<S, Pos>,
            apply_unchecked<typename StateP::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* foldl_start_with_parser.hpp
P4F/f6b2/Zedmd8t/FLH7w41x+8eWK0SjsvhisnK/at5qzVe1y+teV7HC/Pyav9a1mPKarQ5iTLYrgrOzKoYCM+7hKNaHWxxqTVjZhUARadytcrNjjLCsg4cHuvkAbdTQdz+bOiidVRdmAi6YEUv4msn9WdK/0dNigLxCShnEYdgGy7x6V60hhOIkyrqEvrOLfP2cPXxSluxye0OeclZUMO8ibWgv7AJ9tdsgnwn129Ri1DHpasrdrwP0XzXFWaTEW8P1LRsf1e9HRNvl13Uwv298m8c6KUt3d+b85vF3ZGwv01MvIe5RC52Swtj6v9vw8ZGtPY3ResBhNYZl6tA+qJ3dP2EaJ5YR7i9ZncLeOJzbwFqK4DaXfg1FbsfZtfqn7WiuWyeGzqgLsgCHskBAVUY2OkFUN5e/ron9NIGxINbAfnWUUEewLxFVo3JbQLm4pK2GflL57cwyhdu/l7jc6FJWxmrq2qOzX37JrI537mN3h4BqFLlkcZn0qrc+oOiMOGOMT2MvEP5ahW3v3aiL2K82LcOl9i30idBJAjcgRJYvUVjtVK5T9qmTfSuN8E/wh5dycUfGEeIZ6u4lOR5A6Qk8XK6T+3Exrh+6DxIcwfz28TUNBoCqlKsdIcd599jaDfgEG/qQrepVvuV6rOYNDcSZ7xVcfReTS1wyN6619CICD/IFw36Z95QQb8Yk43imiwAE3wrmkD/ljd0
*/