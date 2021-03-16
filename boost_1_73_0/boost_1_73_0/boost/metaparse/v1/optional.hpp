#ifndef BOOST_METAPARSE_V1_OPTIONAL_HPP
#define BOOST_METAPARSE_V1_OPTIONAL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Default = void>
      struct optional
      {
        typedef optional type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            accept<Default, S, Pos>,
            // is_error evaluates it anyway
            typename P::template apply<S, Pos>::type
          >
        {};
      };
    }
  }
}

#endif


/* optional.hpp
8dUqXqnOf5OKr9XPT8ULlX+ZOn69im9Q8acqvlHFk9X5V6rjPXX+6vgqFf9HH1d8LxW/ofwbVLxRxf9V8dMq3qLirSreoeK9Kt6n4v0qflXFt6j4VhWvVnFjdf83qPg25b9dxRcqf28VD1ZxuW5PVDxTxXeo692p4tdUvFPFa1R8l74fdb1bVHy38t+j4ntVfLniy1Q8QcVzFJ+sjk9U8WXK/46Kr1L+W1V8jYrzVJyh4vNU/IC63m3q+Fp1PFE=
*/