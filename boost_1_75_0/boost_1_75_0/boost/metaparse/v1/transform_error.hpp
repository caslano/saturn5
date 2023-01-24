#ifndef BOOST_METAPARSE_V1_TRANSFORM_ERROR_HPP
#define BOOST_METAPARSE_V1_TRANSFORM_ERROR_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class F>
      struct transform_error
      {
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename F::template apply<
              typename P::template apply<S, Pos>::type
            >,
            typename P::template apply<S, Pos>
          >
        {};
        
        typedef transform_error type;
      };
    }
  }
}

#endif


/* transform_error.hpp
b5CRjgwrXLNfWNK8E0qfvvJufO7BxLm3wtxbsc8jj/c8S4ric0fd8jqae8iYO56L2goaRIfQP011wr8s+JcHlN8Dn5nwD06RqQX1szzRWcVydFZJdFYpIG/r66g8mAoLYb/1Axt+rYCbcHDMqpKjT5FMFH0KCWX9U/X8g2Xrp1gR8BTrRJ7ayFthGkEamEV7lYzfpuKhfjJ9XcKHuv3oEC73zSsQEpWZg7wCeuhy4bkzI1N3nfkoaprDubrrDPgmrTq4eJsFI8MbpIsP1rXPHwhH4JuszwHWOSsQHREb0jTVY1UOB6IXmmu46jFew9Bx1rDJXMPeAznOojgeqUJiXbyGr0GPDzTG6TFxUNOQPHD6yumPGQT5JmFKiBNk/R7D4+B/pMa3D/jfqPE9ww3bCPN2CNxMWQd+SukMKv3hZAhEPY6Ae0PYVRRNKYpOcsA/p7fJk2ltw1jA/PbCuY6wMxj1OAPuSc5wf7wdA67cEnCnhG3wTgAk/4Cyo+0tMtVeDd/7yupVjqDSNwDivrtFqnuXRBIvKg4ypdq3LSjEBaC5neEAPqLsBProhG+oGAin4l5EoQB5PhB83LIj3CsI12L98Sx1O8L2YNQRS4VLsH96B5VPg9G+MVtQ2eRt8mZaA3jeyg5P/W2Z4mtQ6Y2dA0kWYzD78Dp6djIQL8NvJ/12QsNReCrgbENjMk4gPBK7Qfh076rY0fYaKxFk
*/