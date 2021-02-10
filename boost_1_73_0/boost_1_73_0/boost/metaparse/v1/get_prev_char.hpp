#ifndef BOOST_METAPARSE_V1_GET_PREV_CHAR_HPP
#define BOOST_METAPARSE_V1_GET_PREV_CHAR_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_prev_char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_prev_char_impl;

      template <class T>
      struct get_prev_char : get_prev_char_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_prev_char.hpp
e1uoHfh+58kNaNIa6geDXfDeUFV1ZZAqBZkkaC04aXboYLt+AZcbvd/lMNjaX0QcNM1hfjb+Ox5lVZc4TnTVcfVlQWFFjXvggHOrK/zM0eD4rwN8evvt64AJJ+VoGW7ipygYtYuJwnXckvbbhVONLjr3FxlKtzdI+x5QLxnSnQwkY9/QFFkDreMgM0eGuRy7FUIuLbwjKriyuXZXTBw6LTWgnk4nupyzx4cY/j/M8DV5bKmtC+CfUo9taYH+YkdoASR7U/LR28N68xSuPLagVdSUvubXHovakXz6hhQm7WYDeEas/UVZHNBjHg14ART8TM0v/9AfUEsDBAoAAAAIAC1nSlLxxLJ65AEAAEoDAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTI1NFVUBQABtkgkYIVTwW6bQBC9r8Q/jFz5EgWvHbmHIGrJSqM4SmqQjaP2VG1gMCiwi3bXjvn7Dqyxe6jUC2hm3r598x6EFo1NhcEFC0uZK3p9YPupdGYWbJUkcf+ARqtTy9bR73gT/fzFpHKNkF/BIXfn2RfYoj6i9k2ZIQs1NlVL40xY4Sj5bDKDu+kUohf2XVgMIDngLUzvYa2ONJhNYTYP5vcBQZ5+JMzRBdBJ9U1f8Fx8IHtQ0qK0
*/