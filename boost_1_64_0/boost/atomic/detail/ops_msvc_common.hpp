/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2014, 2019 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_msvc_common.hpp
 *
 * This header contains common tools for MSVC implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_MSVC_COMMON_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_MSVC_COMMON_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

// Define compiler barriers
#if defined(__INTEL_COMPILER)
#define BOOST_ATOMIC_DETAIL_COMPILER_BARRIER() __memory_barrier()
#elif defined(__clang__)
#define BOOST_ATOMIC_DETAIL_COMPILER_BARRIER() __atomic_signal_fence(__ATOMIC_SEQ_CST)
#elif defined(_MSC_VER) && !defined(_WIN32_WCE)
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#define BOOST_ATOMIC_DETAIL_COMPILER_BARRIER() _ReadWriteBarrier()
#endif

#ifndef BOOST_ATOMIC_DETAIL_COMPILER_BARRIER
#define BOOST_ATOMIC_DETAIL_COMPILER_BARRIER()
#endif

#endif // BOOST_ATOMIC_DETAIL_OPS_MSVC_COMMON_HPP_INCLUDED_

/* ops_msvc_common.hpp
hb9/U7aov7WpnIcef6eovdES7cH1922d8A50Bvqa5+DLDiljWbdY6+px4lecksi69GGin7ddgJ36fVW7UgnjsNmVR2Bipa+C5oXWuqitK1lY59V5kzp762i3QjpRxhgvILsPlSL81emuxUhwkbvniKdI9M4toHVzFnh4XJX1wDyyj5Y1vfVEv6DkgIPPnoZces17cUAgmpZk9iS32K6jujiW5cbQX+A+h7/cxqKuTcW7AqprXQtr5k5DXd38Pg3vC+n96Imjpsx0TRudL+/L6X3+6HFjkLYscx9QfqD9HdNMp3RqpjOym+lJBroctJ5/lcF+i4E+YuA/vbPBfwNdL7Rv+6Gyj0LPpZy8v4CZmY56IVLKgBsJUUStFjwW7VLmjxWZmkF0NcuMb7sU4TD/NNF/Cuk/7/zDHLL/Gb41QomEZLaxLTY2YFtM9AZ9E6XHQE6Pa/oq9DzKc4xbYTLhySeRPndmWZ6TBj6fucU+URp9GY8J+c8tgt9nbrEX8S9TooVf5Fba/N2J51dEu8SPdBnfknYap2Us8S+Uehf8PnOMV5K9UzfWhdJtmGOEG93ctfWc3Zoo33NX4bflnF0W2dVZztk9cQLnjHNbmscyKM1FH+Cd3/hBIRBpp6+vEE9giLTPffpy69IVepJDUZ8yxuIjD0X53a1mdY4i8+bIGGJ8tEZ/FNLVZjPKi4zxZxLPH0M0N+PEj+tDJivDQ8xlJo/ikUru3g7xyN3F8RodwTLk8WeyUYZkXiiR3L8v7n9N7sNYpsS9UYZkHrA3uT8c4hkH7Eb02pBeGEXRyxn8ETlDgpN/H6Z72+mxLDt/6KrxRTkHKrPtb9qXy7nhp5O/e0O88lle6amf44AXx2j29Y5n0bK8SI21bbe/oMTyfNEO8vNM5yTladsX8FPzY52W25QHeVKerqYwpkt5HBzD/Uj+thdiqR1pW6P8WuYeiym9clm/ISXIj94h5+HehT7qcUezX/wNPL45QejuMje1idxVhXj7AdU15byO5hS4qUJYZxPP70Nq1GXKbfa+trec+5UHQpDXmr34ucSn3Z3CdXkE2R13ZipnOa7GV93i6K/8zTFAmetcpRxxhlIY0Vo+URjRIZkYE92PMa1kW7lyra3e7tHvO+Ka+yKJnnYE+XuTMw1rHWzqCnWu/X1lkqNAudPxKaVbtTbWTel2VF2izFW5Tc/5HIK5so9t3E/n739D7aL8TqXwQD1Fbocqsax3VhNPrj0Gb1Yoj9KcYLXE/SJv3pKc58nY/z0Ur8KQOSq0joeHy1Oeblz5OQov1fa2cqHIQW635vG+RJaDbeRXWUgk8iHB9qhis/dUpthjbQucX7Aseb7nPHbjoUc5uytfKi60ffdg3qfcdocSa09FHPKo7rqV/C3WyficSkU3rjGBZK2Dz70kl/b07Us2AMU92mc0989l5DOKRyf7S8r7SqztH1blQyc/C6TNqvV3NvWFLkv1jNesmB2eyoN9sLcaqxnVNfB431lk34f6Np4wNnEY6E2tOooAwjvjj7OXZRgvUZ4N8wujB8vfUErXl0OWIr/2OG5TPna+oBjkhsK/AvVVopZeCc111c91Zkg0GXpfrjMx4F0fRwb2/ljLbruDr4fmL9N7++rG/dmfv8b4GKofd6qB+2wNKs8FYH7S2V2LS2TS+ImDhpB84B3Kmc+c5SHVf3z/sOpfn36imtenx1X/+lSx6etTbp9JWwwyrJsnhLxym8047rqA2rODu/q2f+sNdEY3X/rcWF/6WwMdF+dL5wrtW+/vxF4tQm4fboEZiEjs7+F7n1OA+wLA69tG/I7oNVbrz8Dv20b8muiLeazFvI34L+L5pdTv8EPaiI4=
*/