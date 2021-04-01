/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2010 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_sparc.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_SPARC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_SPARC_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_SPARC_HPP_INCLUDED_

/* caps_gcc_sparc.hpp
aJvUdS8J6Ow+iDvvWs+M5BPzx2vCFSokmm6G//e/i8mfyrHvgOmUYhLLcfZOE0UliO1p0b8lqu9jhvUMQ7qFLKbvE1yB6Cl0sm31KTTopjc1xxfX+peNLpW87CcVkyTDQLeFEUfI2tmkOvMfux26zeg+/KWwKef+LrrHnVdfpAdyKcfz1G9cniflVbedyOv62sVqmILK8R7QEESDaJRnG0+OBia+a2CPnzdl9VOS5A476RK/uyGQJ9zJwter/9Mp052OTrt4qvvC8RsOloWLiFcRCB2H995WjSmdm+sg8f74ArIsQoXsoYBwiNgGjYXJU/ezKCSMH2mm3SVWsczph8YME7CEQzkxK8ue8b8eXPLElN8W+dvgjR4tLttuzPtxqA6kSh7t4cEclMNQ0YJYVudGnIMzAvKz0dgCk6X1FHZVp8/q4J93b4swjNt4aPKwf36X2O/oEvXgMLlnQnST722OwlbBmojJrFpu72fsNx0Pc/DQqZobOgg8H1jf5SZ+v1KXmW86NIIXdieWheaqNQDNqaD83l+tyvjXFEMZpgBvQNqoMyUjJFg59g==
*/