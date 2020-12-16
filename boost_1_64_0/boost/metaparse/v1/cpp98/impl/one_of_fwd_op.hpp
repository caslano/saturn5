#ifndef BOOST_METAPARSE_V1_IMPL_ONE_OF_FWD_OP_HPP
#define BOOST_METAPARSE_V1_IMPL_ONE_OF_FWD_OP_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/cpp98/impl/later_result.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, class Pos>
        struct one_of_fwd_op
        {
          typedef one_of_fwd_op type;

          template <class State, class P>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<State>::type,
              boost::mpl::eval_if<
                typename is_error<typename P::template apply<S, Pos> >::type,
                later_result<State, typename P::template apply<S, Pos> >,
                typename P::template apply<S, Pos>
              >,
              State
            >
          {};
        };
      }
    }
  }
}

#endif


/* one_of_fwd_op.hpp
Rgd6d8eBX4iey7P7vTV58mcVH4tTk17zk6vXzlwPevn5oORXohBUccRlDN3e/NkDt/3soyVwqKFGOE+WwEGS1fsJxpR8d5jxDaeHNTx3Vfq5ta1rTcYdhmf0cZQ/j3zEFCP/7jbOxJ+L9hPmamINSg9eVXBGDoBRfcSGqcVHdH/bjwNJFc57HhxRXtNt2z/sPQoszc6/5sDVavQawvtj7HszQXSBeBr3xl8Yocaz7wg+r8Hs9zwkRmuwvPONZbWfUTqey7PnNbhdp3tdfy4D+H93JpUrX+7o1steXwZ/3GcaLHvzkKSJXUu+S9LbpYWL49aRFc0PjGLB7qhSNc4j//Y9guFW7qfTusz61mB3+95RrvhqhA/te01bLK9D27f/B7/W1ePGHe967eDGY4O4W0YHROVc+ESTQlptOTbipfVtMiXD/cDRERgDTQq5p+zONu5YwolGfrC/C0dolG3ZrcxcK6Ypkv+ysSrmDW3WOKt+pMtTeE7j6x8kbWreTaz9IbJR/XXwWKd2gUTp21e0nlFmjOPUvIeMNfIB7/uIhpk4zr3iESbceY50U3MveEwuIRJsayuO+DFGG6u2vn52S4P5npXryTN0oBpC4WzvjOHKzwBzTTJlCUw6eOuQH/PbIluX2JvNz6/GGOs27tDv4azXvIN/+HZGX4eHE5w1qmAsOjdx5jDfRXGtRdd8Z0+hnY++6fNs09/+hqS44mPOM91ZizlPpbMO97301c4YZo5wxQDfOkyc20qeP6tz38dL4Wg1y53Xi1uMVHt3z4lgy41PBw3yxae/G6q/d0xc3yM2W9d3QlRqpn1Lz8ETcv5fxNUUDp11Dx/03/uM9mSHM97I/2W8ctcHjR7k80FHj7V0KtVl6NRupo2F9uEBnRpjlaUzbYUcdpMxSszRmch3UjbJ9Z7u+A2HTjt65eV7zKmKqZhYDXb82Kh+iM8w9eUEA6YO/XRbeNJY/bvGNZTLkSWNHqdocHUuruCnGvAZKUomDKBs5GnGGuR3Ri1/GsZevGtNHj2bd3mPG6vXhAXFiQVKwuKZLvLpUs8+ToyeM1R7+Clj0Bph8IwSMqF4fn4An9lYD8OFtnHigjfA+2/4Oxv5xSJJDtw7Fl5Z/vlY6x4+HlP3v5eNtfMJ8/qicWfLxRVG07m/eGUJPHie0Ol1jbW2wBMrfl0LXAEhmEbL34w17z6S/zjviupbZuA4z9b+1hhfLFGLJcZ6cgbrntiNPhz8gy5XS93nHKgzKT9zybroT+6n8+qqdeGSwOu8es6X88gUWcf79VhvPuncNb3AM7fwEzrOq945BVN7Id+FUu8umGnaNPsetXC11jM4N43Q6+8CISw6crbvwyFCAxoh6bXk29k/6iBA5ZA6ivOvD/tTl03ki6O4MJI1SrwCFsU6t44x1taaF4kat7v19d8haa7uh6tv5A63vzeqPjKqzsigFM8gB63BwV5eH3+aVleRSGSWHF1p9L3dWGdPql2rkd/lrA/Z1t7ld4veVxWRjDU8pb4BrBCsfazWeaQmi+h8a7gO3h8hu0Z8uw+Y+P5mXnhx7V0qq2U7JiPKmR+UbfhqI8e5R44fEpKHMo1zhodlP3LHpH6n6pGxGn3Fg7DF9LIXNeZCqXc3HO619Y+OVXWEaK2azVxr1Bn89+Je1HDc8zo11jveehUmQcvVX9BwbN5F92P99if0Ke5dJsZSkmJ+o3D2aHP/vfn+NrQu8VzpEYN8NaUfanfqSn2f/BQNp9T+T3RwlBrotv8no93nHCfKKKeup7tVnCuOXyeuuEvH1+sYuAqXoY+90sZ316GecdXW22sa46aEFrpxeN4rz3/X/Gv46RhdL5+34cLVaP4=
*/