//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_PTIME_WRK_HPP
#define BOOST_INTERPROCESS_PTIME_WRK_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//workaround to avoid winsock redefines when using date-time

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifndef WIN32_LEAN_AND_MEAN
#endif   //#ifdef _WIN32

#include <boost/date_time/posix_time/ptime.hpp>

#ifdef _WIN32
#ifdef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#undef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifdef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifdef _WIN32

#endif   //#ifndef BOOST_INTERPROCESS_PTIME_WRK_HPP


/* ptime_wrk.hpp
Rnj16d7Ox3oFCocxX0f5M52mw0Uq/kaJxyMCOz7haG/wMK+AMMTkppB9w6B9UCEXu+h75t5FOAEpswjTTVb0jfOM8AdxoRR87zYDinQLlY5jb6P1b9rA3zNgtDz4M5t4rCdwiDNI5mdxqYe/beAemEgxc/B75ttBBC5jFeAVEa1f71pg/c7Xi4HR8uDHsN6xnsAhziCZn8WlfnhE8n7uC1CsfnAsevn4WK9A4TDm6yjIGgAajwjs+IA1gHN4mFdAGGJyU8iOSvAaANnJxS46NgnWAJJhgnASzGIy2VFKPB4RKIIWHasKh4d5BYQhJjdF0VHLM8IfxEVRcOw6XEcdbTsceBR7E607G+9dWDi60LC5EOG5zpAtlq8vNMguBl0cnqR5joQXrRzla9q5f8CvTJRA015NpuOL6olZ8vIp8rJpIToJmhMKh7w7WDWQdgBNT1hlUj5FlTRqBf5Se2cr+CtfEpU7K6dgCnVFcJlSCpEmRzwesH2o1YGahKuMtAIz2/KCG1X31k/eqR6ttCiK7kmy9UKlPFgGEtTCc1Nq+aqlz5e7IoaYzqyr5+7IrCKe+FrB0QygqwylEO1n4JQ8RRUGLpOUQIPnhsSCdAuvHvKOIGqKq07LrbCyZj10BQ1fKSuNzJed03CFu4S5
*/