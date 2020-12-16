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
BTxk3LN/BxIzMKb6Xn5i2kHA5FV/jUuHZ5h+O8Ba2l5QHbICOnhBdfCCUgqudNQwsd9bsd84TAsLEntDId2lMOR1uFx7YW2Sajfxwtqk3DkHrxY94WWIBqy1XWpt51rblRvlIJX6ktfovp+BIj8FmoOs9q5fL1Wu512/Xu16P+2oNM8lnaZJnWOgEb7cghY/uXLjdAQTS2QX3LaGtQKVkdKS21ax6F8eLuVbtWgXxH11R8C//rpzkg2ygPQhqjdw0fXvULU9RHooRoPXnBvOSbKXtfiOknmEkxkGhtaQ4Wxm7gFO3SBHGbIiyUpJpu8ByLIrHfli/h2ZkVdH7Mx79u9QYgqHyf0fl+H/l35O/OF1AdQPl9pm+lmd9PXaZwXMB8wRlO1HpeTQUvuUJ4WZVJJJrFzEJAVjfE87U9/lVSm/v6qP1ZqkQcJLZIIltz7mJcq9Y+KS7upCM7cug+sysC7ZKX7UGx1A9ZIEwa3l5GBdNSzhllDTXCs7mvLSHWU2gU8czccdWhGDixhYRDajn+xPuDiMgvrOGmLmiPgpiE/WHZzX5nUSr3hUiy+wam3AVgzVZRQ+T+VaoGOqlf4DHKQBHpfTYvJC4WDOGXTmcgfyt6NkIPsPnwlQ6gP5Q8nbGw13Af0L1s9mSNzTo3pWNsfKdJLM5hovg54Qgm5OB/EA+YYybKnWvjokj9q/8jzLHhE4sC/DOqlsJOvqAY84R67hEsgwYwS6UjK3LYNGSIDTV19Ib5ZvE9mLhyA5XEsBvzO6qLs8dxDLqAQ0wLVXW3Uhm+fuTR6c21AZ3Sei+mA9xVltVplAPZQ6xUMknQrxUynQXPuzVRJiAE/TPwOE8CrPrbY6gCOtt3odJr1hL9LBt8aMFds6gbeitzhocZO/JhCOgc4MOlT6SFJ3rHf2sPubSo6GvgGvwd1DbTgf9OXuKZQn41oXrVVcgR916im6b+9I1xCr3Hq5Yi6Hsms7Bio8PLedMjXS+ph/Rm8NS+gjqIOZu1kLpZd9MCIKF+iZcnfcr0fa7fRBGerV0c5aLxtkrTMmquCSIJmXdwC3n5ySZ7mLcltMAd/6mNIKke61mvwn0zF2Lww1+fEw2bJfI3QPpKwVYu2s6/uzthEAii87XZOsBkXHtm62+2Z7cDqTscr5vutwEFaVcqJCZhlrdHO14U3RsF0j38WJfB5b2ME7Qd23y1C7eNxIew7UfR8CaheLG17vQI3c0JBZhebF8HcN/P1G+/sd/J10aqF5+qmfxNX4f/gBv5V7K0eu5emT6QwjrRDx2iHAuMjzb/Pk6kAM07n+UEQB2uO//SkVhzQSAaT4Gl3iM0Himys2dLZYRyjpW1wYkkje4MK+ZKMIA66G5TOVvWTgsifIHROuvkrwIMKdB3JZR7pztB6Jv4GYt5sFCRl/6yWwZwFwhd9VqLKUmQf3teqHrrMZhuz4kuUvsVUBUDukCoPxn9xPqdU6oZcsTLBm/TsTCxcL+WPjXXsigf5Qmpvx7M/U4SniW7+lNgAa/btiobQn67PcBkWdU1zm4HxiKVwfNmRwPtGwh8IeFGvWQHlLFSepPVntxbmMfCkAODDQX6ecu8GR60P+nPOyFrAXIre20oaJsSpWH5aSqi5Dqi+D9D8hEo/TsCMgD/fB1rYuHFPr0W03raf5tDbRhI7Yk5VyKESbTlfbLuecPEsv4lIFWd6tJjgGqlEKsxDvPlPffcy5rHqWKpOsA1f2DiSK/sBVF6MVquoCqYoyDlzTQ0rb4Vd9649QRnFdShEBlY1wqzbOVkHIQozVeMNKuDKq6RfP6B30CVhZUllkNawTIqwTSjy1fcfH53YTXG8HkP3j3whfdfbS+gk=
*/