#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_CONCAT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_CONCAT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class A, class B>
        struct concat;

        template <char... As, char... Bs>
        struct concat<string<As...>, string<Bs...>> : string<As..., Bs...> {};
      }
    }
  }
}

#endif


/* concat.hpp
OnbVeRnrMp+teTmP5O/YnVfwWF7JTM7hVF7LSzmXl/E6Fi43/HYLv+mSl/tZqKuyno34OXtzAwfwC07lRt7CL/kEv+Jr3MRP+E1oU/lbFpUB39dyeVoJZcBPDWXUh3APDmUTprIDh/EwprEv05nJkQzz95tsy/MfFeZ/GvdgFptwNDtwDA9jDvtyLDOZW1Q2P/zOYu0Syop2CPPvyBQellimfyvfGxC+N5ApPIVRX+LLw/f8
*/