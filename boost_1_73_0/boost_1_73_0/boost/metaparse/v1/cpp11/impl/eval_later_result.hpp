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
FpX1X1BtbB7CV5dRmFqpVQhpoc21Jz6W6CD+WJ7bXXHJT6QptZHtFakKqfAbrGWBKtnh6JN7BoNgwFhwNxh+IZ1OldN7UkmCb2BcSIdlZIZMpE0QUdrm0kCFFBvQikKEDD/qDawxsXWFYDUkRaEPUBt3NmghkxUJ0NWxSdAB3T0C859B17asLbFk4oRAzjeIxOeaEa1HEcutLalyDoUTE10+IRykzQm2B//xoge1wj0q+F1r8p1Q2suETa37iI3fli+/4ukqnsyWo+7i54QXetMMa+si1btdojLQpcMbeUr7Lf8enaRKizpDr+UYct59mq/i2SLsOnaL+TLmznUn2p8T6gnM+X62tzH+HSu5PkKzacnaYtWY7BYF8sTAB5ICz+Taekzsm16CKCttdaqLiDkX2kHnveywJ21sCP/w6bA38tF/2NBw2q26Knj3fbpczeavHfaQplhS+pbfdliHSF5HCLdL0CyTRw7x80KR9PNGuQ7SI/iFIb/+h38BUEsDBAoAAAAIAC1nSlLUOUHbDAIAAE8FAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMxNFVUBQABtkgkYNVUTY/aMBC9W+I/TLfislIw2d0TspDQalVWRQUBu3evMyEWiR3Z5uvf
*/