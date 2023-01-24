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
vUZW2dHCO9vCIzZbrqZOLozcZhK25/imrqOi8kDoqMD8VJ1dRsWsH+Bj9aDD9Lmbjwp3+KjQMwlY5E8ek7tjXt+MHey9ESC4abPN9CY2Kr4u2+kWMPLq1Oe4m7+1nj6JAAIs/dPbec2WL8gmw50WpR8xX1BRbs28bNBPQ5vcf7Brk54PeBt/fK624Z7NtkVKU6gvtIGGPcQGWkgPFbLSMNS+g3jAHSs1tN6E2/Ogtdz6OdFKdeAiGo64drGbPfo0Y5dv8BmlQZtwgTTye/sihuLYTKaCrdarAeuhvg9aKwyRW+FK2AX7Q5UwNhQx5q4bJUz+8nty1907U9PA1gVH2+vfY5zydkpDn5q193w0sL/sC4qc8Z/BFDD63BpY3D6mgdGWbBpCJMsV857PQtQv+Lxc/n0ImxOQsuf7CPUr4SomwLINYWoYCTBVB1MTM1cydm79QdPCVtM24s/SUpkWZpP+nYayC30Sb6VlUpT+s+TlBmIGud3iAL1s/ndIKRAyfmNqsZ50HHSBaaqHKnNCNA96c6fc4/sgwcyfAsGGiGyZdiupYqCnUbJMabeNJejM+YQcDvChihnaTAifkmd9x10OKwgRJMefVxAZKvVhSSdv6aLDhw/w3ftCB7gV94kdF7uZ+rx72SAfcuUMPsgBXutXbJQ7cutZyV8b6h7+5MU4AVpzm+b1s2Y0sffzWjCFJxYsCpkDMXij5ydU
*/