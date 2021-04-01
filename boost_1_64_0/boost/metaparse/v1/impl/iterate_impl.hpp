#ifndef BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_HPP
#define BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/iterate_impl_unchecked.hpp>
#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class P, class Accum>
        struct iterate_impl
        {
          typedef iterate_impl type;
          
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<typename P::template apply<S, Pos> >::type,
              typename P::template apply<S, Pos>,
              iterate_impl_unchecked<N, P, Accum, S, Pos>
            >
          {};
        };
        
        template <class P, class Accum>
        struct iterate_impl<0, P, Accum> : return_<Accum> {};
      }
    }
  }
}

#endif


/* iterate_impl.hpp
THsY7uGeYVdRLqSrYw0rAwViCDR1hUB48XxHs1r21HMEqXLIRlDwwwd1Tx0cVB/n6c44VcxZEFtrz6TXUUFkZms2JDj2AIfIblXTYPhyg4AI8WcPuDYS1u1upMKEHxFwQSjYaJihfwS+w8omyx2xopId+VXM+SiPmG5PVRo81kRkUbXkAGtlUeLf/PEsrSvIuRXm7+7IVWkMd1VJTVrD6xO6kewoiVVUCU42MQvcp4JKgspGNR0u9JW5w9hkY99j620wUEedQE1i6R0Ewu+i8ppBxK1g8tvolN94bq48qpVe9twwQDdw+5zFaFSrNYYn2AyXDnXQOGJokvtqr0uVzkyWa+O1YwJ3PLoLOkRNB7b+s8FeR3LkuYwNcea/Sm1EdhPbyX5MCy0Xroyaswq2RO5Az1y7mqW5U4qW7SOK8tp59y6sO1HLCyEj6NpRB6OUxP1qmKdX8BvyI+u3fmNUIvLZ2fEaQxdcaXEZay24lvDizqIx/f5wrZqYI2t467GdL6JNxLarF5qDStMYHdcrHY0ld+4UhaBKXiEFgykNxdiYciTWdGirybA1Rg==
*/