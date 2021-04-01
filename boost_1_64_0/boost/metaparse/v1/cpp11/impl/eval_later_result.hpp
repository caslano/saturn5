#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_EVAL_LATER_RESULT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_EVAL_LATER_RESULT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/less.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class R1, class R2>
        struct eval_later_result :
          boost::mpl::eval_if<
            typename boost::mpl::less<
              typename get_position<R2>::type,
              typename get_position<R1>::type
            >::type,
            R1,
            R2
          >
        {};
      }
    }
  }
}

#endif


/* eval_later_result.hpp
KUxS+kCkNTPDdqxk73q4Lk8kYIHB/+rrowRFWxdfGMpAwUpHElYI8mVN6+8FRzR86Q/j4ip9wgstPtB8dQUXt/vsUABwSG/qSwhqr/Wt8OeWknjXBYhrEE/VDr665MoTC7rmFarL0dEFFkrKtUwx7bhMSjdyLdMB1zbf0H61CXhzB9i5iFLh1c5gsTcGOQOEMn3bf2/a6fkNAveFzvuHHQOoFbm4cYHEzxmpuq9dW1O22m1AtLLXnvN3i1OnOpXvq8FLI2b/ef87GUBMay4Wrbq8GV4SCznO5eKzoOBvNFleqm9tXlcKpqqqPG+HVTsJ7iWKTSsijoWgz9p25GRsWhlSd5s2AOmp7zubhU/Y4FohX8JL5zQ82BucP4LltRf+DNlZPVpzM65eJX5MOmBqiswGeIiVcY48eRx0dSna67yUF6GmotMECWjSAIoxvycbON0Ai1ly4v9PxzI9ZgrY7nZHU+s2wckJ788fimfFERB0RNXBXkdtKgJFg/JA00pxhEoNKVr1bRIspTnx0ZauWUz7FUtUv097lpyzqa/kuhJtxR0F+BaTD26yvQ==
*/