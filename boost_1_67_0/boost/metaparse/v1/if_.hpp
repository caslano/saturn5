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
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
*/