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
wfU3x/IrbbHikfz1qLfOQOL777J70Q7hNvYb50DO9fZ4DlTg/G1A7Pj5TG2QFdv+PnPeckkwj6+DvmT0e5M7m7w6d1+05zqPUFgv91s7ZmAGP1bnso/m1blP/8GZ+fvfvThm2NvzvnjfRoNVOsgF9ZZTcSS2rzeNnFeGiwanXRY7jgr2S79wnqid4u/tb0NyIBXuk6N1zfmkcaqpwFa5TY9G29TGcB3sP2zQJWGZjL9My1U1
*/