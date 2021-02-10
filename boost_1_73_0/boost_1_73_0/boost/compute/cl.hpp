//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CL_HPP
#define BOOST_COMPUTE_CL_HPP

#include <boost/compute/detail/cl_versions.hpp>

#if defined(__APPLE__)
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

// select what OpenCL core API versions to use
#if defined(CL_VERSION_1_0)
#  define BOOST_COMPUTE_CL_VERSION_1_0
#endif
#if defined(CL_VERSION_1_1)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 101
#    define BOOST_COMPUTE_CL_VERSION_1_1
#  endif
#endif
#if defined(CL_VERSION_1_2)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 102
#    define BOOST_COMPUTE_CL_VERSION_1_2
#  endif
#endif
#if defined(CL_VERSION_2_0)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 200
#    define BOOST_COMPUTE_CL_VERSION_2_0
#  endif
#endif
#if defined(CL_VERSION_2_1)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 201
#    define BOOST_COMPUTE_CL_VERSION_2_1
#  endif
#endif
#if defined(CL_VERSION_2_2)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 202
#    define BOOST_COMPUTE_CL_VERSION_2_2
#  endif
#endif

#endif // BOOST_COMPUTE_CL_HPP

/* cl.hpp
QtpnVXJYH7JcVw1bKCaYrRK/OXFxgUEOchQIWttWBZguUXvIJFmiB0xetNer5X4n4Ro6aUBL3IVzbd+5ni88WuYCa+BOhe7xO8e/8ALHGiXlLoVhCw3zkINmTTJUNZG0DIM4bo42RSMZtdCuHXvk+Jarlm2s0gZaT3YT/vWQL8ES3FfQ+R1YScyggjXge1e+EwRWsNmj+SrNMlhd12Qg0ZLWwTuQsZiBezWxx9YoVzqyrFDzlskaFY5sSlRYHVBJx0B+cMejoe2Pbu1weG2FSueBZkyrZJdKg73E8Q8Dl9Q3WNbSis9gUQadhUO029otWM0WunVoj8cX9vCG7dYPvhs6l7PJkAybIdSMdCquL6iRkP0yqqIusyYdV0d8P7JD2xoBea35oCqocrVCRBYxjUDkyjNBEIaBD4OAlxt1i1HuJpkB9aTUpLyMQmsIBt31huGYF9p964FSiguaSN3R1KI0IZ8UHJkY5a4hGPjAcW54ucs4/twneJPSAHxSbOJhlFtDcOje8AZ+GiTPF5/R3egTvk1v5nC6CoqZuRYHIIaNN3UmWMLpqQusYgsYmawi7tL3MjlZHWizrGZqqlIbj2E4HMPi0FetRZqT/So5dRgw9P1cTtYLGcYnK3aEyPDU60ldLe8i8MZO6NSg
*/