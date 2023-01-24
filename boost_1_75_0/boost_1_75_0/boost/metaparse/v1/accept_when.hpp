#ifndef BOOST_METAPARSE_V1_ACCEPT_WHEN_HPP
#define BOOST_METAPARSE_V1_ACCEPT_WHEN_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Pred, class Msg>
      struct accept_when
      {
      private:
        struct unchecked
        {
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename Pred::template apply<
                typename get_result<typename P::template apply<S, Pos> >::type
              >::type,
              typename P::template apply<S, Pos>,
              reject<Msg, Pos>
            >
          {};
        };
      public:
        typedef accept_when type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            unchecked
          >::type::template apply<
            S,
            Pos
          >
        {};
      };
    }
  }
}

#endif


/* accept_when.hpp
gj1swxVGFLFS8zSRU/+6Re3SzSZSY+QMpy5E1ksD68ybiuP7VCt9rDBvsnPVdE4x6efLEOOHkwQ1tQyUDb8SmfDNOuDGCeDaOZO1a+x3ELHfeH4lXmO/XSxRwEVNl9ivXQA4XgB4OcC2UyJ8bKaBTSRQayuy5wJsl6u8N1ChsV6QrKD4gQ622LRSg+0+DbZ3mclSMUGt64R95HQAfjY1mvXGc2AGe1jFB/OmRorjbjpnN6mTNlYd8EiKlyB+AkGpE5qiGWQjfDlfV3b/KRfkwRorGOR+VN/mD+SRwqYU6KzjkW4jjzREywKLbg3s2bGpO/JIrEdf+jTxyAnEI00xeeR9LxEn++h1Yo1PvIyssUp+9GW68MrrxPqee51+P8mPC/jxEX59Nv89gx/vel3Q8r/GG0+aBG+U5SH+PzR2mBj4A9khY3kejeU1AFu7N+3MbI2xtJh8ibiaT2OUOGLlxf/piDH5pDHy73QscdcL3M4TFe7NxEvbR1fpQu9/d4dyeQ4JALIMs+noLSHaMjzrHY2wx1Hzd/xQb6XcjtI1VIWkzuTmOQ6gYkm5lfz+z3GDo3pFZRQ/6GY1fYhlFF+hF9VyqzEof7+wYYnfFN6PmQvsrFoBne7UJ1IbE9ODRZUmBiAmNiuOn7vps0R0FUwokwGDwV9bpsbW6+Lqhb7ZVvdCtp5rXyDsrF5Jx8qVIqY+BnyneP5j+Cbw3Jn0
*/