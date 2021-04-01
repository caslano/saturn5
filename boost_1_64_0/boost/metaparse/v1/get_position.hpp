#ifndef BOOST_METAPARSE_V1_GET_POSITION_HPP
#define BOOST_METAPARSE_V1_GET_POSITION_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_position.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_position_impl;

      template <class T>
      struct get_position : get_position_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_position.hpp
Y412qS4wTNg7axHODo10/KkPBKff2CrWb7Toa3zQ6hXRxU7SnFO+PzbJRjmD54rj7uywPQAmC6qL9U2bn+TUjRYPafEi6C5gC826rSlTTi3nm1wvvaAdNOjpZnvzROcLEXjjD8ZJkk4pBVXQ8N3HiIfmXa7uSVfX/XDjWMQWI33SJ/OgBmHUsqHbDQENKUo+Yn4jq0N+CCQ2QGMdUk9Hhlkdc5FUbZk8U6wMderXm/cgHgfvH2X3pXvLHdmzendwYaizyx1as+171zTM9H5xk28cHQBziBv/kPbcwRud1aGQ7F00JysMIvT6195+A3nMRnP5i/TRrsg2NGD2MdYJxNOrpKq9162/PXVQkiHx2UaODqJc7Af+7w4J9yTFwTzPKM3ECvhech+w5gfi/YwXRWEw+VIVnDSEUnZPLNERAy/oQR6zww/AOr8e8YMcpydThO0tXF3HVmQjRxps8GVJTmxTB2mRd2jdb24QX2tKJGSvb8qakLb0m20Qvm8mTcWewd9c3JeJ4LtxmKXiP8HitEXqUZ8wIWtHbCI0wk1wgwqEMNfOLLCK72zsqA==
*/