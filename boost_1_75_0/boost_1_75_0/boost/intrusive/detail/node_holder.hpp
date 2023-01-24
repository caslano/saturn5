/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_NODE_HOLDER_HPP
#define BOOST_INTRUSIVE_DETAIL_NODE_HOLDER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

template<class Node, class Tag, unsigned int>
struct node_holder
   :  public Node
{};

}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_NODE_HOLDER_HPP

/* node_holder.hpp
oZT2dyNLerNO4m1OoUzDpaJU5VPpP11f6IhHxe17pJ6Jd7VHNZuatMqPzZNmMp6YULUgx3OQr4W5puyb6zIQ7elAg3Lw+rOhSwardoNDSE1lj7UxgvjPqzPEhSKdkgU9mRqAKbMc5kNtagPaIzaieHDABSfQiDgzlfC4W+rPWDqKz70WtVg+lVFFWIvCjlnEkKFSDRUzFZy83ALhOY9F29SduRlar6w92Z/6k08FidWJqapBqZaqxc0eXGrXSVR0ra/p3v4l9iK1NXTADGzI9ICuzbFHpmamffwenAiZDMjp2BlugKbtHznpx7RoN8Qh5OnOHtyfvFkmigaS1SnMm6/HeGNXI3+Y2EeInmqr/QgfYH0KmELlOAGYu8dfLD7RcBvnG6c8bTk/gaKuH1yJ0GnUU9VUdfpyGEFV3xJ+K2nRVRDwRax9gy46tp07f0tgLNVY5whTNS6dnAmP2wzyQEI5rp4JxmzvxHFpRHejHCAGzvgvbEWu2sZfAKn5rT5XcX0GzlOQXVDcJrmmb0YwFmP6eZcjQZ+PTIUjMnYO0Y/2sm7Znj2e+Q8OX/Kv6M1nLsbrkII3e6rc1RyFBc2z0VUEyoLkIUr075VQysBl5OpfV91axGSO77V8Mk/AZTzzqx4H1pBvjsJxaV+ADIFp12+CLVtkF8Int60ifsuy/vxIz5rWcvr2N3Q4xKNtr0QffPYd/b0W3Z+QgBbB
*/