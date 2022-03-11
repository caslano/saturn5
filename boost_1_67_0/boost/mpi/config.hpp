// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file config.hpp
 *
 *  This header provides MPI configuration details that expose the
 *  capabilities of the underlying MPI implementation, and provides
 *  auto-linking support on Windows.
 */
#ifndef BOOST_MPI_CONFIG_HPP
#define BOOST_MPI_CONFIG_HPP

/* Force MPICH not to define SEEK_SET, SEEK_CUR, and SEEK_END, which
   conflict with the versions in <stdio.h> and <cstdio>. */
#define MPICH_IGNORE_CXX_SEEK 1

#include <mpi.h>
#include <boost/config.hpp>

/** @brief Comment this macro is you are running in an heterogeneous environment.
 *
 * When this flag is enabled, we assume some simple, POD-like, type can be 
 * transmitted without paying the cost of portable serialization. 
 *
 * Comment this if your platform is not homogeneous and that portable 
 * serialization/deserialization must be performed.
 *
 * It you do so, check that your MPI implementation supports thats kind of environment.
 */
#define BOOST_MPI_HOMOGENEOUS

#if defined MPI_VERSION
/** @brief Major version of the underlying MPI implementation supproted standard.
 * 
 * If, for some reason, MPI_VERSION is not supported, you should probably set that
 * according to your MPI documentation
 */
# define BOOST_MPI_VERSION MPI_VERSION
#else 
// assume a safe default
# define BOOST_MPI_VERSION 2
#endif

#if defined MPI_SUBVERSION
/** @brief Major version of the underlying MPI implementation supported standard.
 * 
 * If, for some reason, MPI_SUBVERSION is not supported, you should probably set that
 * according to your MPI documentation
 */
# define BOOST_MPI_SUBVERSION MPI_SUBVERSION
#else 
// assume a safe default
# define BOOST_MPI_SUBVERSION 2
#endif

// If this is an MPI-2 implementation, define configuration macros for
// the features we are interested in.
#if BOOST_MPI_VERSION >= 2
/** @brief Determine if the MPI implementation has support for memory
 *  allocation.
 *
 *  This macro will be defined when the underlying MPI implementation
 *  has support for the MPI-2 memory allocation routines @c
 *  MPI_Alloc_mem and @c MPI_Free_mem. When defined, the @c allocator
 *  class template will provide Standard Library-compliant access to
 *  these memory-allocation routines.
 */
#  define BOOST_MPI_HAS_MEMORY_ALLOCATION

/** @brief Determine if the MPI implementation has supports initialization 
 *  without command-line arguments.
 *
 *  This macro will be defined when the underlying implementation
 *  supports initialization of MPI without passing along command-line
 *  arguments, e.g., @c MPI_Init(NULL, NULL). When defined, the @c
 *  environment class will provide a default constructor. This macro is 
 *  always defined for MPI-2 implementations. */
#  define BOOST_MPI_HAS_NOARG_INITIALIZATION
#else
// If this is an MPI-1.x implementation, no arg initialization for
// mpi environment could still be available, but not mandatory.
// Undef this if no arg init is available:
//#  define BOOST_MPI_HAS_NOARG_INITIALIZATION
#endif

#if defined(MPIAPI)
#  define BOOST_MPI_CALLING_CONVENTION MPIAPI
#else
/** @brief Specifies the calling convention that will be used for callbacks
 *  from the underlying C MPI. 
 *
 *  This is a Windows-specific macro, which will be used internally to state
 *  the calling convention of any function that is to be used as a callback
 *  from MPI. For example, the internally-defined functions that are used in
 *  a call to @c MPI_Op_create. This macro is likely only to be useful to
 *  users that wish to bypass Boost.MPI, registering their own callbacks in
 *  certain cases, e.g., through @c MPI_Op_create.
 */
#  define BOOST_MPI_CALLING_CONVENTION
#endif

/** @brief Indicates that MPI_Bcast supports MPI_BOTTOM.
 *
 * Some implementations have a broken MPI_Bcast wrt to MPI_BOTTOM.
 * BullX MPI and LAM seems to be among them, at least for some versions.
 * The `broacast_test.cpp` test `test_skeleton_and_content` can be used to 
 * detect that.
 */
#define BOOST_MPI_BCAST_BOTTOM_WORKS_FINE

#if defined(LAM_MPI)
// Configuration for LAM/MPI
#  define BOOST_MPI_HAS_MEMORY_ALLOCATION
#  define BOOST_MPI_HAS_NOARG_INITIALIZATION
#  undef  BOOST_MPI_BCAST_BOTTOM_WORKS_FINE
#endif

#if defined(MPICH_NAME)
// Configuration for MPICH
#endif

#if defined(OPEN_MPI)
// We do not want to import C++ binding
#define OMPI_BUILD_CXX_BINDINGS 1
#endif

#if BOOST_MPI_VERSION >= 3 
// MPI_Probe an friends should work
#  if defined(I_MPI_NUMVERSION)
// Excepted for some Intel versions.
// Note that I_MPI_NUMVERSION is not always defined with Intel.
#    if I_MPI_NUMVERSION > 20190004000
#      define BOOST_MPI_USE_IMPROBE 1
#    endif
#  else
#    define BOOST_MPI_USE_IMPROBE 1
#  endif
#endif

/*****************************************************************************
 *                                                                           *
 *  DLL import/export options                                                *  
 *                                                                           *
 *****************************************************************************/

#if (defined(BOOST_MPI_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(BOOST_MPI_STATIC_LINK)
#  if defined(BOOST_MPI_SOURCE)
#     define BOOST_MPI_DECL BOOST_SYMBOL_EXPORT
#     define BOOST_MPI_BUILD_DLL
#  else
#     define BOOST_MPI_DECL BOOST_SYMBOL_IMPORT
#  endif
#endif

#ifndef BOOST_MPI_DECL
#  define BOOST_MPI_DECL
#endif

#if !defined(BOOST_MPI_NO_LIB) && !defined(BOOST_MPI_SOURCE) && !defined(BOOST_ALL_NO_LIB) && defined(__cplusplus)
#  define BOOST_LIB_NAME boost_mpi
#  if defined(BOOST_MPI_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#     define BOOST_DYN_LINK
#  endif
#  ifdef BOOST_MPI_DIAG
#     define BOOST_LIB_DIAGNOSTIC
#  endif
#  include <boost/config/auto_link.hpp>
#endif

#endif // BOOST_MPI_CONFIG_HPP

/* config.hpp
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
*/