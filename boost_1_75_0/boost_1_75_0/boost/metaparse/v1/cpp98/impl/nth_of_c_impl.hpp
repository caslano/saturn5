#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_NTH_OF_C_IMPL_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_NTH_OF_C_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/skip_seq.hpp>

#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/fold.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class Seq>
        struct nth_of_c_impl
        {
        private:
          template <class NextResult>
          struct apply_unchecked :
            nth_of_c_impl<
              N - 1,
              typename boost::mpl::pop_front<Seq>::type
            >::template apply<
              typename get_remaining<NextResult>::type,
              typename get_position<NextResult>::type
            >
          {};
        public:
          typedef nth_of_c_impl type;
          
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<
                typename boost::mpl::front<Seq>::type::template apply<S, Pos>
              >::type,
              typename boost::mpl::front<Seq>::type::template apply<S, Pos>,
              apply_unchecked<
                typename boost::mpl::front<Seq>::type::template apply<S, Pos>
              >
            >
          {};
        };
        
        template <class Seq>
        struct nth_of_c_impl<0, Seq>
        {
          typedef nth_of_c_impl type;
          
          template <class S, class Pos>
          struct apply :
            boost::mpl::fold<
              typename boost::mpl::pop_front<Seq>::type,
              typename boost::mpl::front<Seq>::type::template apply<
                S,
                Pos
              >::type,
              skip_seq
            >
          {};
        };
      }
    }
  }
}

#endif


/* nth_of_c_impl.hpp
JLqxNIldw8yNwqMULTi9RvQn2BPYOk6C8OilmJLoMmCbeh2J1ul1xeN991kSfLOjfbNNor8wAb/vmF4v+pPzxNzdwqMn4DGQ5mXtSwTHsg72OVQbAolwyr60g3v5H1mEEQVZ3qO3euKEirlRVqFiY0YbVvvyu2T5bRflU+SRXolXfoxqd0oNSh/jIDiRmohez+Vjpy5uCxRh3OyfSB677N0c5ZvWQrspfq7GGcGNq/4NaGZP7aDWZ05SFAcmTZEKZNZHvCvtOcPGe9qxGx3euijvwT/p8RQAhrr1b/TRHnDaein6jsmB/8l6Ha+NUzheUdfU0l3oxNgEjGn15ycoZuNGcvu5jbQ8Io/9pFM5W+7jQ5h2GeeUrfT2DT0Vc/0GLbqiD69NZ1PMOzAp0KDcQI4/X4+A/APP2dJhrhPw9efpqxKJ2lsVcyk1Ec/zRD+Hj/qyuvWYyG9/DMBxf/Kyw0xZNU45rOmFuHuLtg99q451DKCjcIaoVgymGn3tHD2rJEojHG/4D+FOXFYeAylCekNSLe0PQxOHHsrGt9WyIDBimv7CRkwT06QQktu722/HQhY4oO8F1KF6LVHxOIs2Q0JSbMxL6zVaXsgIIpQ+p8MYlmU1RE8qHalJMUwj8458uUxS7PaHSIq945+qp8tvknDL0zslVz0nNXwhB74A5DEU1Iu+gu0gxL4Sc5vmwHjJV/BCHZXieUf+pJUt
*/