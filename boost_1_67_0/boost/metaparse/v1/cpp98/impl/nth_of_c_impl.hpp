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