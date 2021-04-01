
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBER_DETAIL_DECAY_COPY_H
#define BOOST_FIBER_DETAIL_DECAY_COPY_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename T >
typename std::decay< T >::type
decay_copy( T && t) {
    return std::forward< T >( t);
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBER_DETAIL_DECAY_COPY_H

/* decay_copy.hpp
IijQNxPiNmO9C8h/iP/J3UnIwG66J1EJF5saLGnDDvgtZuXUP6BHLHD/S4IE07ryVt1EDWGZdGv0yFKbgYlddC1zySJlsrY+3DJceaAdg0tmE3t4hSk6dqlKSswLQSfQJ2o4YVoPnVfjzCa69rSwqqM3i62nWFAN1vANRspi60XgKetY2DlHjj4Is7+XMOElaN0IPci1itODN/4j8hkPgTbvObW6mrpCDlJPNsC/CRB9TpuIeMOgFCkrt9X1F9Ax+378v7I5ReJ5y4g4WCHCbAlynaVOi87cneJ9MOUnBz8723HqGnOdWmtzPW5Ncxd6euc5eUxVRHMvuJRgSw9zk4yQPmudngm7KxldQjSzqWRHkl9mWSZR9HV0WIFZzwjGIoNdQRvKYj/TjQtqbDHqNSYRXlmbJ8uGKwNJ6VlkB806kLPEuJBFSxI7cMv9vdUmRhdlNXDU8v5P+GWQ5LYFuLYPLyMG/CVz0TVkJlZw0gaExRveUZtsAE0LJZYnwMVSjoaYqFroCCMa9m75r4Kxa7KTjoEGgTeHZR44Sj2uLuIqWHMPODQASWZa4Q==
*/