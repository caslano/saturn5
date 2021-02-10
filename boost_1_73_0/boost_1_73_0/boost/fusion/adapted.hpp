/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ADAPTED_30122005_1420)
#define BOOST_FUSION_ADAPTED_30122005_1420

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/adt.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/adapted/struct.hpp>

// The std_tuple_iterator adaptor only supports implementations
// using variadic templates
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/fusion/adapted/std_tuple.hpp>
#endif

#endif

/* adapted.hpp
VMjZK8ZbF8tTUFQ0cqTRTZBaciAPhNVki+WIgkqpTv48m+W9qHEns4LncpYfpHAr1bzY1Rq7acgeeKdAcegldUDnO9DwgpV6RYkw2PXbmsnKeW4LC7bFjAuQtK5HOoQyKoctUEhGtRydCR12z5ReJG+lrrareHOUiLKORGUvWiyHsmBewVF4B/q2oMLkGyEOVUaVjeSvHNlz7wXwFrsC20sgSGzYEsmkA9+C9DZcpfDNi2Nvma4hvAFvuR75vgTLa/QGw6oC6GMnqMQuBLCmqxktjop/10m33PQW5qt4EUZplqTXfhzDOdhnF/Bb36Krz360wa7ZVh87XLjnF+4pBvS/jBK5zyRV+oDxi16SSJfcwtL76lsvODfv0I4FE/rlIBWqLbT8pOVmx6gdJY0BJ+tlGCVBYv3A2rzuCwqXutrgu+qTZYhzjvGXTUz0Ezip0BE1GuO4AQdugoUPJ0Ol6UdT69pP5nEQpUG4tCKCipMxa5wY0lD0A04I2hAOIgxeHgZpUwYD4aaMcD6logSPv7TGHe4q2uqJ3LH23hiqE/zeHK0hNt5F43Q12esMZDs0fefHV2HiT86nyGwVRBF37PjGWy3SsYAJRXGYhvNwkVieHhaM+L97X6OFb7ltaQ2amMZ/+ZdirGVqgioM
*/