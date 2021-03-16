#ifndef BOOST_METAPARSE_V1_SWAP_HPP
#define BOOST_METAPARSE_V1_SWAP_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class F>
      struct swap
      {
        typedef swap type;

        template <class A, class B>
        struct apply : F::template apply<B, A> {};
      };
    }
  }
}

#endif



/* swap.hpp
+Qrm/lhMVLMI8kgqHqkGni80rmQwK8MI8kgqwfD72vX1Lf9jNSqCPJJKRKq257umIPchou6JII+k6ht+rflXdikialsEeSSVhFQzz9cjuPMGor6JII+kGiAV7/neeb8Tq72tIskjqYZI1fV8kT981pqo0ZHkkVQjpBI838lnlq8mKhRJHkklI1Xf8z11T/wlRN0bSR5JNRbU81/feTlR+yLJI6kmSLXyfCuaNfiGqD8iySOppobf14qZw9m7nBo=
*/