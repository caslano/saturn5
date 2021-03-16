#ifndef BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_HPP
#define BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/iterate_impl_unchecked.hpp>
#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class P, class Accum>
        struct iterate_impl
        {
          typedef iterate_impl type;
          
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<typename P::template apply<S, Pos> >::type,
              typename P::template apply<S, Pos>,
              iterate_impl_unchecked<N, P, Accum, S, Pos>
            >
          {};
        };
        
        template <class P, class Accum>
        struct iterate_impl<0, P, Accum> : return_<Accum> {};
      }
    }
  }
}

#endif


/* iterate_impl.hpp
Jp66Ls/5JnEeobIHcU8YLwilWgLnUVdcmK8Sq1RUaJ7lZaQR94hl4rHaXWCulNXCA31dtcXkqabpbtKgjy8nUA1qqM4HoxxwoXym9R2aYGfxCDQtjQ6zDKEgWfPXFCupDeXYeOjJ6x2JUSRik8jmgn55UVFw7X6l5Ec8ZUKhYjRSSxkrkolRkz4XpftWorqAwxa+SSl4KJkN8ZDCGqcTc3Zi+A3xpkZYKJq34l2EhKkmh+1fKsmDv8OnFFyRgJE=
*/