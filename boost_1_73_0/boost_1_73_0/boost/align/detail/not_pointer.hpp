/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_NOT_POINTER_HPP
#define BOOST_ALIGN_DETAIL_NOT_POINTER_HPP

namespace boost {
namespace alignment {
namespace detail {

template<class T, class U>
struct not_pointer {
    typedef U type;
};

template<class T, class U>
struct not_pointer<T*, U> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* not_pointer.hpp
WNicdyDiYAEtqntpJ6HCOI/ZxlD5lkgYnfKxtgr677hJBoe0UvdXoFdQvPgyUPnw7MQSObl2GBdCmFRq14fTz/ySmrGZ7s2S53R5PXKrOkbdeZ+etKdmcig8z8RzIONZdvlWlhRlc2HTumXnXiSAqdGBK5Qd6h9MmfKv+u9NOVfbnE4mELOS5SZdrpNqIu4WC+L4x9LOMiycRo7Uv6XOguIuqBc84lWHay3geI6e31OkxieZLPeC8/TaMORgpu1EUOv35HL8nQiMTflJLQJzHUgFa/tDE5OZhSCDMTaPnDHW+EWoRZsme3mlZ4+0srIapgUoi7NGsxMhPsiiEw2lWcd0Z4L6tgjFCEg2XBGTG7t7Zn2T1IYTxuZxLihVVTfK9+U8Xvy9FkXnvChka3uWwePCwjy/XRchbyoWx9X8ay0wmgY0c5NMEwaPFJnIjI1leq8ay7PK0YENiKKjlcJUhem0oQGFwqj4+2rGWZCmI8MVsWJ37H4aOjTUsqvG+vHESCo9KuDYbyzYS9NXIa4LqrLscRI5YT0RlqwSVBkrTULgmHtsZak1R1Uz+k1Y0vmouk/m5bVJRbXVqkhEJV7X50ir8ryPb85OXWceJH3D+rshq/Jg489i4cVYsGpt7WNFr5rQ7q84TZ33B7A6
*/