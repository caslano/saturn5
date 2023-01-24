#ifndef BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_UNCHECKED_HPP
#define BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_UNCHECKED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/fwd/iterate_impl.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class P, class Accum, class S, class Pos>
        struct iterate_impl_unchecked :
          iterate_impl<
            N - 1,
            P,
            typename boost::mpl::push_back<
              Accum,
              typename get_result<typename P::template apply<S, Pos> >::type
            >::type
          >::template apply<
            typename get_remaining<typename P::template apply<S, Pos> >::type,
            typename get_position<typename P::template apply<S, Pos> >::type
          >
        {};
      }
    }
  }
}

#endif


/* iterate_impl_unchecked.hpp
pr23bZKbjKoyPlqRM9o/l6aB9pSqrmzjbbRbmEeTLUbf9rWqbq076BUO+L5sPn7Ym+2odHBLQs74oaLqBHXCjLb1R/MpGc5dJnRQrmLg/pzMyom0HtLk39CrHNXhjedZ1oHkqkjZhxhs0d31EkKY10LTtCX1GYcXYaMxvQhcRuCnm4MBvb1dmHFphckL4T8ffnTyqdRvxstg839GYgIXUKloxx8E/r0PVpAyG8zQFIf2iSE6qJ6Vus5l5cFL+XFfAtiogcge7a8cH/SQQYkMU11JAxAoWlt3fzyW6cu2cvLUtF0izkimhQaOf+A1JxTubmYWCc/oLeyuaKFt4t9sTDFVpu1SiJrhmL1Qk7ygkHo/aHx5EEt9kjHHYk5uGDCURIgK8yQjSOY4P1V1Gatxfrqim5BVsDadzV2zcVpYhc3fVM1sr8J2j+QH4zs9nZnxnZNNy0+6bsNC4abFRDXItaKdEqi+dUVfSg/SqGhnBTFhk4IBW4+7sdLmNILYfKpFDMFT3pGCGcb/tfkt3rA3K/5dQJwpgVIX7iYx4MBwED9c2oSyrIn768yzUEHM2PC/m+TQnLCQK2sfhzj2fzI9+Xnctx/fdfWeg7S5DgaCNAbNP2/JvyFNiAc6ypeXFDnqgjWIBWfb4a3LhPsXG9B4Bx/bqH2QT12BzJD5LEyGczlTDVzpGbh4G7n8oZ3klxcOfKH2Rv6/x23Ece55
*/