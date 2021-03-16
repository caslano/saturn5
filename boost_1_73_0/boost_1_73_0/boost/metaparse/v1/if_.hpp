#ifndef BOOST_METAPARSE_V1_IF__HPP
#define BOOST_METAPARSE_V1_IF__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class T, class F>
      struct if_
      {
        typedef if_ type;
        
        template <class S, class Pos>
        struct apply :
          accept<
            typename boost::mpl::if_<
              is_error<typename P::template apply<S, Pos> >,
              F,
              T
            >::type,
            S,
            Pos
          >
        {};
      };
    }
  }
}

#endif


/* if_.hpp
2N7CjBmNJQ+2cRUjDrYSehzqbOk62HrNB98/hMWDrWMdSnUoVIoQdyjkRJKST0p4WGILPKjhSDnYKmpZOKQdzxnXIZOoBEoATrTEWg92eJlwi+xnwpH2g62Il21Fqrjfy0XUezW8Suyn1ZQcKLdeP17TF/972lP2TwO1P8tPK9W13fZPA9VrybQ2YsSoF7a8/8Sm/67afO3cw49aetYrycMO5TtEdaiQdaM0FW3WvvhbOJXS8eBOjyX0tnAimmk=
*/