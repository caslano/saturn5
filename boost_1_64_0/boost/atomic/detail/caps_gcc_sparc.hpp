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
JfAvcDD8Fg4PGr9n5kbG75ErckWuyBW5Ilfkilz/69e/Zvz/45z/z+BbdZnJjG/HR9G3J8QJtZMmV1XoeYE1DrkA70sffoyc3+8P/0bne2KFmRdwnt9nXN3gfIC47WTkW16j9XlWmPP74n6YkW38iNbPYqzQNaTc+DJzjyGiFz+kh/8ekytr5yojd+8ybb9K6yuN/2wVLAvZToS+0/R8htlr8JJ2e5pjXF1pxr5ttdtrHXYzzD1aaLuOomcmQesbyT0Dx8mdtV0cep8MgnMqnd9DrNH2g475bP7Bjj/8bL6sv4o7nX4B48C2J9vjwLqdd0XdmPX5B7HffXJV9t84HC3rr5KmcEyI9ddC2UvdCxbCgbAMDoKT4BA4HZbCpXAYtP0Oh9vhyfAuOBo+CcfAejgWvglPhe+Ku8/gaTJePB3GwZ/BtnA87A/Pgnaa9MyNMmO4ssgYLnJFrsgVuSJX5IpckStyRa7I9e8d/1dMmfzjnP9f7fj23y4Z5z+KSkI9gPrWHudPNeN87mtW/8Ot/Yv7DJUq8vLO1fopapxyNVzrl3PuF2o367V+hAmjlXM+Ya5vHbbM2C9Qcwgz9Fo44+sgd/FmHZl9xY415De0mzbGzINyy9yBb29+nXYzR4eRFfQttPu1nV/G/yVa34v0zTEy/87XZgUqBlPnGvGqY1wjzg+xRtzTuUYsZsX+cf5c3/pwaYj1XflOmqzvTg0Y04/RY/qPtnXZ+Nw36S8OumR5+7dbrDmox/QUNUlT+KhEMg41Vn43E1noLWEr2BoOgm3gOFnbrYXZcAE8Dt4Ic+EDsEPQGmpVZPwduSJX5IpckStyRa7IFbkiV+T6D73+ReP/KZN/JPl/Kxzjfz6Xq6/yKMZpwkP2+P9MM/7nvscw/tfuu8r3vPlOkNb/0TPT5Qke/xs5d9doNys8012JMgfgC6dT+DP/xk2e+U7yYq0/5Fqg/mZlyfdrrZ/ps+aeSaz0nm2NwOYS9ZprnFrpvjx4fsGcz/5ch7NP70kfbe7T2/ML1dh1gbuRai7yAR7WYf/afRzfM9zMmfRiq41L9ugHyAxQ+lnlu5k6rFc8E1zMkcj9Vmizqa4zuKfvzIR7vN7z4KpUewLOFRAX8x3vRUafGXWkMwH5Dn8Z+Fvs8NfC/QBSAK/37bPnqtUZKmfaQ+7vX639FlqpspciRsd1q7VA3SduOJM+DjNW671uKEHazZdWE3UV/rxxuECbfWelW9c79tzPnzWnwP/t1Gztpq/Lb0/88pX5VnCUzoPTrT58QSrbln8ocbxW+/uFtUW1xC1mJg4HrUZ87el3fHHJESYFMt/M6byp3WWZ/Si3nGXrLzHfZd6kn7+j635q/G7LI+6QeDlBf88/KNwCE847Otw+cjaFb0vpcGZ77lGJ6jd8o7O360HLW7ZDhUW65Cvzfd/WOqz2gelCujWXZ4jX6XKRewzzX38hN8+wsl2pEo/B+nnK1ImO71Au0+GtQ+/MrybovXl1vfbzIWlwZorHccZhlWMeK/+I3+ZPBJR1/Vx+/XzRp6qolHTv75yRo7oVKDGL95vl+8yUMSvs5TM7eJYx6+kz+8xv1sNn9oHfrLvP7DW/2Qk+s+f8ZkU+s9JxxqzQZ9bHb2bi3NVvZuKcbcwKTJyb+c1MnBP9ZibO3//MmJk4f+E3kzhzRiTEPOH0EGdJahqeJTHnQ8z8oZgtMv5px8T/4pBnRgJlNVQHfQemc5zSV5nsI8uFF5GKyZPM+2VqhQSm51l12zlV3is+d0XmPFiJ1rewGuw5k3dKP23/vdaPMP67oDdyWe08NHW6VNtnWvm0ss8QA8eZKVNHums3yZZ/v1ataTOmart40y4=
*/