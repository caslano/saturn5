#ifndef BOOST_METAPARSE_V1_IMPL_BACK_INSERTER_HPP
#define BOOST_METAPARSE_V1_IMPL_BACK_INSERTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct back_inserter
        {
          typedef back_inserter type;

          template <class T0, class T1>
          struct apply : boost::mpl::push_back<T0, T1> {};
        };
      }
    }
  }
}

#endif


/* back_inserter.hpp
sMIEiD6tLtJhouIVTRiJJ46ps0EdmAie1mvzIONMNpAbri3ISFhFI2i4LmavsKoRMy5fWyYqE+lSfgK5yPWlNR5XCXF8P0giOK+XwWjtam9fRGOU6QwlpxyVMUujIGpqoA+CR4pb7RZy1bsH80uKaVCYK3vF0Lrpfy6si+KCkRpLNt1SYdWYAGRLtghqyBMd1xvBChvMXZ8G9TZcOACui1W9vZwqSZ3aQI7jIB3QWK8RoL6gTuq+0OYK4v84fQI=
*/