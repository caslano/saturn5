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
xYW1p7lEnkMPCh731ZOcATGwcLjW540MNxPvuOl0phnJYgtd3tgVPm9sg9cLV1JCWgp4lsfcMsnhyy12RAe+xrtDrogn1lh+fuwVscVCZ/tiWICYGp4FAxOkNV7gtSJo7XFaE0RrJqM1v/6Las1hF1vjQ2t8sG0hjgHhcymf+G9Ko85LMgsfRUQ7qxrYKXOU3qgvkx4/8LFdRzXqcAO59JJtueZzStFMEDzzxy+rajeoat2o
*/