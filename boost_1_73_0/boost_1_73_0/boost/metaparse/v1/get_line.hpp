#ifndef BOOST_METAPARSE_V1_GET_LINE_HPP
#define BOOST_METAPARSE_V1_GET_LINE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_line.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_line_impl;

      template <class T>
      struct get_line : get_line_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_line.hpp
cDqhlgxPAiXpk+raFleVwvQEBvGO2wddye+2nM26Q7HyzttrrFzaXu5gbIik3rVcyc55mD3c6opghZJQmUt5lCpVN3d7o50n2A13VwnHW5NpWC1i5CLX4Gzf8i6G5zgT46+d668R8Srym7Key0YkkRS7gfQpLkx9zF11f3o+6jmqQat/sfpaMDK7syPz/mMvRy6LXZlTqgrWGPfGnqbHbmuULcrjIi5reKxgWfGkNZ/1Zk6ugbjN0k548zaJcPM=
*/