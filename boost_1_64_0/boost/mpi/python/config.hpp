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
jitot74mBEQm1CQJZoAOP+WLN1Olf+G7ABqaPOnYxgQI8Yp1b9SjHiGIxiF3dnC9EecSpmC+5Gv7T/JFFf8fwKXnnGnc2Niq+NtiH0zP94UeZTAqY/bc7nE+3puX5XvWZdhyx8/L8QJw3mUekVHLlmgSL+SUbr7lXLRYQwZGMzT4DbtojFq0RftPd63qF6fOUgw1kjFosnJltOaubWb0Bai0q+6l922q+alKF/FBHUHCq4wpUNZ9yKRxoUfKN4patNW5FW1EJyVspi1PKv00hIqLyzdMIgGk8wzOJA8DwRGGQ1vUuXMYq2zIXz/E4Z4Nkpt07QgKU8F71WUTZGVniplSrfyMAYzdC0aXfY8A9XXcBbukveS93gOHZnl7VVIa9cWnkgPNhewkueWE0/Goxb+0ARCbGMB7yQpKfA83M+iOlq1cdZ3s3Z+x4JrKPa8CUcH4qTZ5dtX4MWg8J4GYex49a2o3Som+61bZzXl/lOG7oN/BaaG/kOtXhp190QHnz0uMX5yzs34BROMbeACBK3CYVQ5dCYuPA/7iZTWdZsuqO5cq5ATZmAzFOA==
*/