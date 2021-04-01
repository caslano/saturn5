//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_FILE_BODY_HPP
#define BOOST_BEAST_HTTP_FILE_BODY_HPP

#include <boost/beast/core/file.hpp>
#include <boost/beast/http/basic_file_body.hpp>
#include <boost/assert.hpp>
#include <boost/optional.hpp>
#include <algorithm>
#include <cstdio>
#include <cstdint>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/// A message body represented by a file on the filesystem.
using file_body = basic_file_body<file>;

} // http
} // beast
} // boost

#ifndef BOOST_BEAST_NO_FILE_BODY_WIN32
#include <boost/beast/http/impl/file_body_win32.hpp>
#endif

#endif

/* file_body.hpp
9oCCJU+PE6Vd289eZvv1KUhy9AB/4dDGMQ/XLXBm5jBGR1A2jmXvCZm+sGjkV1sOt0n7HCSW23i1salaF3thxyoRA7jiaR3Z36irMdSO378GBlqWUISgR1MYUlFM0tvCaUhJX8lJfH6AB3ix0zfk3P0oatJ4+zN1a/FwLBvZmp8lyPQqDh+oMQVLs4V/h16BPmuUva8SASItvm/s+91YvE7eAmh8fZyl9LHAQvq3DZ9H0ptH81vj04ed/0W+49O7G7tQYaA/lbKKOiKIx95ODXMDqMOaeJ4M6qTOIxgemdgnJRK3i8YblYMkTcPh+VXMOV5F9kbdxnV+AKQT+SgZhWaKCsFC5ToSqnJ+/MvaCkPNYCGIOTQNq4MGP4Em48FgYcYqqIOh5bFUiUWe3qOFuRSV6NdqroshQRidRshVMfLSN1lEymn3TiDwW03unana6+EPjgPcG7fUWOwLQuh/52Jz+UEvIkO8L7JwdflZDBNqJAt5Pvm1ZxK3GzJ73nUm5Q0+DByAW6PsOfYJB8C8raBIYjxneTUrRpUgh3epKSJn6JgpKciaS2PaqA==
*/