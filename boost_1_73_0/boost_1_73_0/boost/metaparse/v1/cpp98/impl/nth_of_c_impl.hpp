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
ZXN0MTM0VVQFAAG2SCRgnVRtT9swEP5uqf/hVIS0SQtpUgo0C9HQ6DSmAR0tsH00ybWJcOLIcRr673d2msIQY2hRlNruc889vrdQY6VjXmHEwqxYSPq5x3UjVVJF7Mt8yibT2Q37fjabswK1ilnoPv4fuq3JDtuBGaoVKqfKEmShwlKs6RxuUywgkVmxBMPxARqEJWrQKUKCC14LDSKrNMhal7WGlKvEiWWCCWSFRRl9RERSoLIuWJhwzeMU43vICXnc1/ig+xHTUnMB/oAlqnlQjnkB4AjGR9A+24V5Rp4Pl7EG3wdvGAwOYO9/7Z4Z+q8YnvO1AYA3HpPhBf6cM0c5m5cwHgw6uAdPn+EIvtUCvION7dXk5PR8woRxbN/XjOEQTjEmOdZ4DHcUWieCulIuLUm981T9yyTdtc0pkRxS9lbtvTv3/7q3Pyb5wWCfyqEphOTJXqpz8XbvF3IFw4H1PgLU8V+9v6ibLL39YDiEsr770+forTemeFHFb4vPlP+mzm0DfBYZFnrTALHdEKSt2YgtdEn4bgdhwXO0DQbvZKkzWVDp7tkO+wilkkvF85zrLCavqNySV1WTvIckU227TE+oKyF0WxoIY0nwIomY41gSZ0vaHSwygSDk0rVbb7gPTg1K5rWoq0Cl
*/