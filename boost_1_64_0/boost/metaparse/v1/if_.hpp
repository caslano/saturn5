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
TRwF4iiz0zHTGaKhCqhco+rKRPZPE6m02z1hXaUmp4Q3UfMuzQPGrQnF0CSl1+GEhSqokb7kCIoIy/J5cevMQvU2zQMccmgdFJygzzwxufYD4NE08lUG0DCn1VhJhVq1nSM7mzVQeBLd2HkRokMHAMLG2hqG5Tnw77YVfMU1vi/Hz175sXwBuEoE1oIafWd4cpwei1jGifZ0GppMFBcRj+rXTqN1yo8RbkwPoPzgpkTCN+gm9Ow0A5bYDz6bYeE/lvzBvWrROvlYOqVUtOcoA2J/t4FvfwwMIPyaZmNcb+mYSye/L//OuhcDL3oEAvfnxvBqxj4HFiJD2x296ezGWMwXc3ItWnul/dyN/tNsqiRxwUiADOVouQ9gptUrFLun0KrgrGFEdjOaBEYXJWvc7DyE+V4F+en8OvcEgCPdwf5diUwAy1I6yDGcLP6n2ul2j6UdZePTZERcHfc9NQznPAUH09ImihUx2uK6YXktQcHDWM4OyXCAQWBmn5i/f3t4XhBiOmQiauDg+SpD9nvXIMez9HPnUNt6BIzzM7odB9NOqdbQ8oM2KxaZJw==
*/