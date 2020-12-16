#ifndef BOOST_METAPARSE_V1_FAIL_AT_FIRST_CHAR_EXPECTED_HPP
#define BOOST_METAPARSE_V1_FAIL_AT_FIRST_CHAR_EXPECTED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/void_.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/metaparse/v1/error/expected_to_fail.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct fail_at_first_char_expected
      {
      private:
        template <class S, class Pos>
        struct apply_err :
          boost::mpl::eval_if<
            typename boost::mpl::equal_to<
              Pos,
              typename get_position<typename P::template apply<S, Pos> >::type
            >::type,
            accept<impl::void_, S, Pos>,
            typename P::template apply<S, Pos>
          >
        {};
      public:
        typedef fail_at_first_char_expected type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            apply_err<S, Pos>,
            reject<error::expected_to_fail, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* fail_at_first_char_expected.hpp
Jo8XPB5srT2FPyi+jzX4X1T/+DbJ4Dix/854RtQP6/Fy7dcWUfsEP9JxOz9wHj5OtH+K+JOO2/HBTfj9pf8f+Rld4vHBH/Gc8RwejQ9uxu81HnSNxyf+jS9x3a5/sm0yGC/iA1bjxzhuz/9D/CiRvz+zHSPRLSrHl0/AV5RZfzGKn6nDlztu8ytMxB9x3OZXmIQ/JNZfLLRJBieJ+Rkf4+Mdt+f/CX6MWp++Osn6FuyrwvogYdtkcLIav8HfFvnzrsZfE+t334C/6LiNb7sRf17MH2lMJIMvxPOxEF/ruI0fuRX/zHHbv/khfqfjNj9CPpkMflGmfzqM5jfh7cusvxPFjxTwauM/7B4f//wwSf/hlj5tobM+OD7e+HN48/oA7ZJBV5Vf2eMFvHtV5fi/tfgHgT2/+Pquw98znsOj8zu8PfeXcQoU98/iU8X6QpkOSZPfwnz/8evF87MKv1I8P2/i88Xz09CR97/jdv7+1fg9ZfYfvT+vw+8S+89unwxuFvnJfoNfK+aHz8SvDsT8+x3075/F5frRuFw/2uONnv3nPNs3eTyPy/Ezz/ZFjwc7JoOFYv5uCu9tnPjGOL4fr1X9g520Z/BBqn2HN4jv53z8MvH9vAL/o/h+LsLPNv6vXZznt3MyOF3E143FTxXr7xyNT1PrY+MnB5Xjs4Kdkv+df3Oh4ysbnfxC+MHq/sJfdt2un42/6LpdPxt/TsRvPI0/67pdPxtvEvEb+S5mezt+hD8jxgfex5eJ8YF816TMj1rAZX5SfJzIH/MtPkbUf1t1Swb7qfWX8E6q/Yj3EJ7D5fgG3lONz+Gq/znonpT93yGujl+Lq/PLeDzr8QZc9i/jqv+4gMvf3+NBD+2hx1N4UngaV+3/LH6UuD9/gx8u7s+L8GHq/eTZ/8ee/W/07D+T0vs/Clf7n4ar/TfhcnwLl99P/Djx/dmAHyu+P1/hR6vnv4b3k1pfEm8l5n9Owls6bvN3n4xvFuP3uZ7J4NYqkZ8Fb3Tcvn+fwK/AK71/q3rx/Rfjs024qj/lI6/0+3m8iF8tvt8b8CvF93sj/ifx++V2SQbHi/kxS/HjRP68ZfiRIj7gSXyk47Z+8gx+gPEbejvz23ongxec8tv8cPvhT5RZf6tFtP4R/phYf2sY/qhYf6u2D+cnnu898V+I57sRr1b9v7iKv1mKq/ibcFfqZ+L5bodPEc93e3ySuD8a8Okqfzx+msqvtpv+ftR6PI2PU+u74xkxfpzDN4j251J8vev2/sY/Eu3DQl+eDxX/jB+r1tfZPRl0Vt9H/CCx/xl4V7H/PK7if4seD/vxfVPj6/gRKj873lXlZ8dlfnK8lzj+QrynOn/82cCeHxrVH/FnHLfr27yGP+W4ze/3Ot7kuI3/fgN/QsQH5vvTfnTd1m/xWhW/M0D/frX4CVWV3w8D8Ql4pffDIHy867b/eo9ksEfJwzLx361rk0FrvJfj8/vSx1fafyd8U7ClT7o53v9w/Ezjf8Gb59cOpPzi+s3Ax6v4G3ykin/ED1bP76BkcHfAfyqs3zsd/7WZn7lgdLx97WD6J8r8Pl1L/8bBeCvczg+K6k+j8Z+CLX2HW+Lv2xh8s/GT8eb+2yFJ4ocrz49eiN8TVJ4ffSu+2HHbf3wbfpea/7cn48sqfgBX/UeNuOy/wmX/lcfzHi94ylf0bB/spbcPcbV9ClfnX+vZf9qzfcZz/DqPZz1e7zl+g2f7Rs/2Oc/2TR7P4+r+LOB7q/gdXM3fqt2b8XV1/fGVVY7b/Pf4MnzbZsf6OPnv8fuMkz8vzn+P3+O4zZ/3Gr634zZ/XsM+yWDfFpXnN96I746HkZv86Dfhuzlux+9uxvs=
*/