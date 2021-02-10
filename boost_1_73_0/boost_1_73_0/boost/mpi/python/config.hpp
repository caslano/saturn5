// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file config.hpp
 *
 *  This header provides auto-linking and configuration support for the 
 *  Boost.MPI python bindings.
 */
#ifndef BOOST_MPI_PYTHON_CONFIG_HPP
#define BOOST_MPI_PYTHON_CONFIG_HPP

#include <boost/mpi/config.hpp>

/*****************************************************************************
 *                                                                           *
 *  DLL import/export options                                                *  
 *                                                                           *
 *****************************************************************************/

#if (defined(BOOST_MPI_PYTHON_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(BOOST_MPI_PYTHON_STATIC_LINK)
#  if defined(BOOST_MPI_PYTHON_SOURCE)
#     define BOOST_MPI_PYTHON_DECL BOOST_SYMBOL_EXPORT
#     define BOOST_MPI_PYTHON_BUILD_DLL
#  else
#     define BOOST_MPI_PYTHON_DECL BOOST_SYMBOL_IMPORT
#  endif
#endif

#ifndef BOOST_MPI_PYTHON_DECL
#  define BOOST_MPI_PYTHON_DECL
#endif

#if !defined(BOOST_MPI_PYTHON_NO_LIB) && !defined(BOOST_MPI_PYTHON_SOURCE) && !defined(BOOST_ALL_NO_LIB)
#  define BOOST_LIB_NAME boost_mpi_python
#  if defined(BOOST_MPI_PYTHON_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#     define BOOST_DYN_LINK
#  endif
#  ifdef BOOST_MPI_PYTHON_DIAG
#     define BOOST_LIB_DIAGNOSTIC
#  endif
#  include <boost/config/auto_link.hpp>
#endif

#endif // BOOST_MPI_PYTHON_CONFIG_HPP

/* config.hpp
LFDSVl3+fgck6oXyOm/ee9NWOrIuUZZ8kEWdaV5+qb1qk1ofvuIQtkG8hepcugLWqygGKR51KW4tMMaIzIXMiy1SAmmoKVsup8qpjjWstuckVerDMljPj9gJ4tsA4mMYMJDiiSbFIMUOi7Kg2g0OSQ/umj5krrm38rbTuvShLE6z9+mMCzeMslYV9XPhtXA59nNhUTsymUoIVZ2iLfX1lsyQbXRtCblR3DpRJrqqmNY7fggx+d5E8Sr8mLBmuNnGojMU7Hjn8e8Qdox7MkXWYnceqDJ2RZcTdleAubJ4IqpxZHPtRiAvPZf7yRhtEp2y/ZTVnqBsjHY66UbbRcGW4+u6rfTZehDOowg54if9qaop6ZXz8O5h6cHisMQupQdBGO096A9+7vXX68HPbsVfKR7SDO5ZxOO5/ANQSwMECgAAAAgALWdKUtEoDjvdAQAACAMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTAyVVQFAAG2SCRgbZLfb5swEMffLfE/nFLtpSo10LRbLCtS1WVtt3SJEtrXyYEjoBKb4SMd//0M5Ic07QV857vPfe/OktBSoixOmSx0ZtzvHdsPU6d2yp7ieNl/4HEWs11TUsEeXlfzxTL+tZqtF/O3GZP8HC/5
*/