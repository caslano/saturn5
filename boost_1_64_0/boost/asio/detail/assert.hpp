//
// detail/assert.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ASSERT_HPP
#define BOOST_ASIO_DETAIL_ASSERT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# include <boost/assert.hpp>
#else // defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# include <cassert>
#endif // defined(BOOST_ASIO_HAS_BOOST_ASSERT)

#if defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# define BOOST_ASIO_ASSERT(expr) BOOST_ASSERT(expr)
#else // defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# define BOOST_ASIO_ASSERT(expr) assert(expr)
#endif // defined(BOOST_ASIO_HAS_BOOST_ASSERT)

#endif // BOOST_ASIO_DETAIL_ASSERT_HPP

/* assert.hpp
HmhR9j55x1H2gktaiyz9aP97kAdWUy+nCX05jkN2BzaxwNPtlebRfhxy/AKZXyKmNs7FtkOxYzHtkScZm++lbEAy+pBXQ9458Mmi7hRk/myUtKOS+rTjNbAqwofPI+9mG7GHXy6ol2xOdDN9gToW2tmI57vxQSGyDh0jvYj9yigTeRPRf1O2eMeAtDYR+8zBLwnSDeTncd6Rhm4W5OF8LnrUIc+POH8If55qhyd860ljq6VV8NyNnbZUSOsL8HEjfuA8hvMeHtIW2kC7cpa0ZgTygwM+aA6DHnVb4H3zbPLHYSN0nIRcJ3L8HY6r66QV2P1KzuPQ82E3vvVKJ0yCBz67BJ2mDZZm0qY6Ez7oI2Q6GTnOnUp8eKF3Av2CmJiMjSIt0MN2v8R3zdDe1yD9dQR1yEuj/e+gs5y6F1ulbBvxSewugOcXpk9C62PqX98G4HOXkzzi/xXi+COwGT0WlnOczBhATM2C3yh4nwv6YdO+dvpskfSbLGkXfL7CLv3R7aUEaQbtP6T9BA980bMhRYrA9j/HPmH4/yr0vSZeciRA30qclUruDOl06s0G65Frfg59BJ2/1596pp/S7mv0HE7dn8JrLDzKU/GvBT/0A2XoiZyL0snHvp9QfirpfNIN5PWmzkO0XZYDD3hvwc5Ta6UxXqkPcj+I3WzzsE0GciNDKfJeOYt8MBrssNB3wTJ48Akz3UNeaiJ8q/AP/naQVtqJuzypJJdxHXrF06Uqh7R2PCBOz0Ru87qGAYwpXnhGIcd9pJPJew5ZdrdK+dCZiIxPUHcwciwuQD7s4CJvejVjCPRvi4dXG2MAeIt6J9A2143v0fcA/milbhJ2u5m8qaSfMN70xT7vJFCGXguQ9y+c8wpq/aFOSuQ4sxxbo/vIVnztwI6MyRmMW49DKy4X2UgvGkhb7GZLkt6FZlu+dD7nK4iJs+dgV/yaQD9wEHPnYZtdTqkemQrIz4Hu1ej9Ar64hbxMM47D53XyFmbRDjwM3R0+qYj0aTCphf6AT7aYFJxB3XLs+qSH+tS7FLlKoevFRinEvAfc10CcIMNA0ltqmFusjDmkL5C+NwZ5wRXwvgz9IvHJmjrJkiotxba1lP2Z85fAHRZ0mAst8t8AufjgGfIiXNgN/T7nPCmF8ZE6bzmJfWzVO5PxD9q/49iTjR6kv6lnrGpBngr8T5tdoBadvg/N6+GT3kR/AQ+jwz7KRnK80yNtQNefcr5nKOMs9ntgpJQ9DVrkvQoaqXcf6afQObENOvj1hWRifjJ6gwvBS2ANeBAMpzzdhVwF8KfddU7GG/AlbbYh41OFjI11zKvwqqyDdwU8iPWVduJnJDw5vzsRPWejH765dj5yp9Pehc36IVuG1DMOOzokPt+t0QnE4hR8DO23qH/cRGwOj+OxmbUVmvCdmgIf6J2CDaPRp4Tzj5GtIRfaxFsF6XPgSTCctnFzyCfu8qez9kBGFzrdznldPfRp/3v8uQ1aj5i0mLq0sRMLu+F1QhGxg5yvNMGzhLin/0bS7kHo9CpGNuj0SqNv2eAfz1qN8whw1xjkb5DepK0PDIHnInD1SOJxOPGEL9kiodwkyu30Iez3R7BoIjaoYdwnHpalM2e5JSe+bESvUdCcgg4nQ/ezInQciLzIXI4sC/FnxSjpgzzs3EB+ufQYdRbDwwPOgefp0B/koL/ZiEkfdkbua1hjZY3DBuRv5LxwAHyQ6Ve1jCPQPxtcA929xNCJZfgY/pc1EV/k9YLnD7DbL+KZe6ZiG8quGkq9TGkB+vVgDFlbjg4FjEvZxEorPsuCP3J1TMEWxAJ/D5IP/qvqGT/GI2+FtJPyR0uJ/Tj0KUNf8p4jbzc6vAM=
*/