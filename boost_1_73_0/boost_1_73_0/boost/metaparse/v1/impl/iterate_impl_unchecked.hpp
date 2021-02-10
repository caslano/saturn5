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
2FwKjUJ731DsdO7D1IYEJrqQwoeklOoGFbUVGpZfmuf6UF4PFoWqpCq6S1lRoogPODPLcDydPkGSx7VCPcsaIdonkJVBzpSuY7EjfocNR+PJF3LB1GzcOHlAdtzBvCyMhipSZEFiNwTpyghZrnVFF87bwIiGF5PBk5CZEMQihX+k2wdvYTMmju5qkMjDwaBPWbpCerLRVaP79FaIpGxSdDthn/PecrWN3tZ+z0iuV5uIm5KNbil3nC4a8i60sKEc41SZACmepEiU8tG20yGrsC6ht93MF28bXhafpmtcSLK9UFo9VKWlsZTm5ewy0d2QEPfJKevhB9ZF1oIdqTjTWIPO0c4D5LGCT0QBrsqldllwtFiTUy21TGQZMuNkp3geQIctScyHv8p32A/qhfe8I3EaoKYuee/jZbN9W7077DlJsKLwPb83XaeMLxIssEaBnRz3D+/I7vOE2NAZPrqBX3z9jz+TrvzRufzxTflKp2TYqf4ONzY4fmknv/6afgNQSwMECgAAAAgALWdKUqVWFLoWAgAAdQQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzY3VVQFAAG2SCRg3VTbbptAEH1fiX8YEfklMlnjuKlCMFJkR7HVNrZsmncCg0HGu4hd
*/