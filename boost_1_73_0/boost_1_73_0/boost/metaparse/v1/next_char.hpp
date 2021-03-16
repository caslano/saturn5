#ifndef BOOST_METAPARSE_V1_NEXT_CHAR_HPP
#define BOOST_METAPARSE_V1_NEXT_CHAR_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/next_char.hpp>

#include <boost/mpl/tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Ch>
      struct next_char :
        next_char_impl<
          typename boost::mpl::tag<typename P::type>::type
        >::template apply<typename P::type, typename Ch::type>
      {};
    }
  }
}

#endif


/* next_char.hpp
KpkHjwfqQn7pwqw5dhlNLIhRX8Whi8YPZTcLTWdJnr8Sc1abu8tQ9v/XOd1thewLnOutxbjsg7K74CegsYaxL50dP7g5dXHerPyKs1j9C3l+2d3iyoXtiEL5obz58I6El13syfCot04SXjKE6WPJnLLS3KIFhe4U/hK4gYIO+gXtzdLKCt2zABOt5VofawtnOgeMKIcPde+1Z/D6Lc9ArZMdnwb5SqBNww7SocnxX0hn8hY6oHkK2Zc+bIQCK2c=
*/