#ifndef BOOST_METAPARSE_V1_IMPL_FRONT_INSERTER_HPP
#define BOOST_METAPARSE_V1_IMPL_FRONT_INSERTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/push_front.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct front_inserter
        {
          typedef front_inserter type;

          template <class T0, class T1>
          struct apply : boost::mpl::push_front<T0, T1> {};
        };
      }
    }
  }
}

#endif


/* front_inserter.hpp
Jza5b6EJ/ZXrjEcbQaJ/mqWMQ1pO8cWIRBllhFi1aByEHqg/dslb7bQQd1cnyFDEANjt1MjP6671ePUcwrSHNvDrhMFkLAghh1CqGJV5YLXIXlrfFnV9W6xVwAwi9UGQB77zyF91VG9HvSnSjKva6xhpaLjvSm24VTpx+MsV2++W6pw1YEZw+UYZhgLRKaUyT1JmZ/I8Hvdj4I7LIewM354MabsYmrGk4faHgs0+f8TcGa5uDTu62sG++iy0d2s=
*/