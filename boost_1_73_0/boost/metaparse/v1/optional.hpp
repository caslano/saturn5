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
7+VuLmaR4P7fYnyDxfklS3I3D6B/FynNsjyQh/IgVmZZHseDWZOHsAHLsxEPYwtW4Ek8nG1YkW1ZmWfyCJ7NKuzGquzOY5jKahzAY3kJq3MoazCbJ/AK1uQo1uZY1uUE1uNENuB0NuQcNuYCNuGLbMY32JLreRK38Q8sbrm35sE8jcexLVuwHU/i6WzDM9mdZzGDnfgnnsN57MxV7Ma/84/8gt35FXsw90CoJw9gKg9jH1Zl
*/