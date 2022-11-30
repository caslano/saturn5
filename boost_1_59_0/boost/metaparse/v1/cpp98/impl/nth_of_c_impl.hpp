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
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
*/