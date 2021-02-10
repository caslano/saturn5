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
FdFIUbdqqrYBJaTaPVUuDAEVbGQ7afj7HXCT7KFSL8CM3zw/v2dCi8amwuCMhaXMFb3esf1QOjMztkiSuH9Ao9WhZcvoNV5Ff/4yqVwj5GdwyN08+wFr1HvUvikzZKHGpmppORNWOEo+GU3gajyG6JH9FhYDSHZ4CeNrWKo9LUzGMJkG0+uAIPfPCXN0AXRSfdMXPBfvyG6VtCit/4Rya4sApqdO0jbYDRwsL2xdMZYrRQqdhpB/aiKpt1XZ4Z3UtC8I4DaZscLahuDHMpSiJqM2MkMNqZJZaUslYWdKuYUO+9rbcgmK4Joo4egYvLXg+7JfBiEzEGmKxoAVeosWNqsnsIVWu20BR2fdXiSFDrR3Uhz9TfcZcD5cROvkIQ6GnadxtEpO+dzgQdRNhaNU1b18RxFSWdPmjowYjKrxo0CNo/8G+OTq569OrMsYBgOiOE2GOQq700iBH4WeO4T7dJCcfUFd5i10loPILTlmC+wzhEIYeEOUMDCFssS/77FEQJxWpaqasfu7BL6XebxOHlsoYwP4EuqxDSXoz7ckLYB0pys+fLlbrR+ipcfmFERD7Qt+4bG4O5JPl0hi2kUbwCNi48+rco8e8+iAZ4EhP6nm55/oH1BLAwQKAAAACAAtZ0pSLZ7YmMABAAA/
*/