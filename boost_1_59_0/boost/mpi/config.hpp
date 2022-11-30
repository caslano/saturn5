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
/* We do not want to link in the OpenMPI CXX stuff */
#define OMPI_SKIP_MPICXX

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
// Configuration for Open MPI
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