//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_ALLOCATOR_SCOPED_ALLOCATOR_FWD_HPP
#define BOOST_CONTAINER_ALLOCATOR_SCOPED_ALLOCATOR_FWD_HPP

//! \file
//! This header file forward declares boost::container::scoped_allocator_adaptor

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/std_fwd.hpp>
#include <boost/container/uses_allocator_fwd.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif

namespace boost { namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #if !defined(BOOST_CONTAINER_UNIMPLEMENTED_PACK_EXPANSION_TO_FIXED_LIST)

      template <typename OuterAlloc, typename ...InnerAllocs>
      class scoped_allocator_adaptor;

   #else // #if !defined(BOOST_CONTAINER_UNIMPLEMENTED_PACK_EXPANSION_TO_FIXED_LIST)

      template <typename ...InnerAllocs>
      class scoped_allocator_adaptor;

      template <typename OuterAlloc, typename ...InnerAllocs>
      class scoped_allocator_adaptor<OuterAlloc, InnerAllocs...>;

   #endif   // #if !defined(BOOST_CONTAINER_UNIMPLEMENTED_PACK_EXPANSION_TO_FIXED_LIST)

#else    // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template <typename OuterAlloc, BOOST_MOVE_CLASSDFLT9>
   class scoped_allocator_adaptor;

#endif


#else    //BOOST_CONTAINER_DOXYGEN_INVOKED

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}} // namespace boost { namespace container {

#include <boost/container/detail/config_end.hpp>

#endif //  BOOST_CONTAINER_ALLOCATOR_SCOPED_ALLOCATOR_FWD_HPP

/* scoped_allocator_fwd.hpp
wKmTLUXcB3xewGxcjUZfkqn/o4HfwGf366/6WRho4Rqzp41X7STTB2lhHqvlj6OPPycz59KCDoSxtcX+JGaXmFNibolBSGDTS8woMbPErGhlmf01Z/Z40QPaTWZHT5cuJ3oI1cLQIJ+d7Xzm+CfrB84wrTjmjaqBvmMezSUxN9ooZvu+2zOTzJoncJxNYna04rl8tuW7M7VFLfm1UCzIZ6omvzrIjGotxIEw3zmNZlGYOG/R7Gi12Xj9Fr/ZS+bRBs6p12lhmspnY1q1+InMFBN4PGtM4JwOSZxbEqcuHDjOiNYyyGeepvfPiP6KaGEVi6v9Ni6RzBmrhXrMqswZ8J3oPU4LZZgFj8zfnMyMFijOibaO2ejV15aT2YtqQc9MXHujudB+VPls1etDF8gMJbSwnPU34nzQNNF7KS1MZ2s7KLxwZdF7Gb85Y/s19lc2sJkkZpWYA20Bs+Vjbr4ksyT4x4n3BzS7xFwSg8TAZkDbHeSzL119X5GZy/v2HjS292B/ErNLzCkxt8Tgi8Cml5hRYmaJWQNaOtjRaM+qoxrs/3uh0FKZTbXuXUSmNmjx/d1nBU0ddwmr6FsjNN85jWZUmDin0SwKE8cZml1hYt3RXGg6Zrw/T0CzgLqSFg57e6irGgT7n9xPIzNV1sIA8Fn1yDezyNxoOmY8J1QJZL1Az6yeqryfGSVmlphVYna0TswmVrhQWNRSVQufM2s+/NAEMhPaQmadP398mEydrIU+zAqMtqSR2dD4eFCh8XQRV81/vOPTL/8qekdzM0udqzoneq+O+zyzzJgua8hcaGuZ9flx8jbR+5daGMks9PqSUWK8Glq4x+xZ9/vvxXg18fqM2dEdtY6R6WtpoQOzGSUfnRS9o6Uxy7dwvp0Mamshgfc3vmCOqAVNzazOoCJaUQtaLLOvPV1OifEkcQ7FeA0S654l8yhyiutkNL1RC1OZZe2J6U7mQmsS5LN/f6/rIbPUxblW+Szls97tRZ0NtNCF5fyQ+MdRMnXDwMeuQWImiVkkZkNbzqzI/IVhZOZGWnjObM6AX5qKuBQtbGC9b19ZoCGZozHOmdfq47PmdfZb/5DZm2rhuspnkQ+mlSczmnz7Lhrbd7E/iZklZpGYVWI2idnR4piJvRzNpTCxl6NBy8BxBrRAcWZJnE0S55TEeSRx+laB40xogeKsaCeZTa3crYCw1niOMePnmAON5xTvcWhuianbBDajxCwSsytMvKeiuSQGbQObQWJmidnQRgf7rEXq3fNkng5aOMLi9thLNxLWUQsfVT5L2LUjjszRRQtfBfls7KHfU8isZi00U7HxKjn7izp7+PYQNP/3W4nZJeaUmFti0DOw6SVmlJhZYlaJ2SXmlJhbYtBL0l9As4AR7S/v2jbA+/4Ro/9zk8zRRwuPwWcvhvWuQebOwL2Omd/3WyUGffF+mtn11n/VIzOhBYozS8yCVpT1EDmqxitRZz88V1Q+q31gxioy2wA0lpN/L9apMP69C48kTj8wcJwJLVCcVRLnQPuTWbfdK/4kcw0KnBMsgXMa0IoF+ax0w8sm33eJ/eP493ddEoPBgc0gMTPaAWZz/rgdQ2Ya4h/HvxNslZhDYm6JqYdqYQ2zFaVXPBFxCus7dNNzMd43WjjH7GGntXnJnMO08CTIZzmP/lOAzDBCC5WZVTlt7i7iRvrOWzT/77FIDEYFNr3EjBIzS8wqMbvEnBJzSwxGS/qTmFFiZolZlcbv+9GGeq0h2tw28d5nnBXBOMa3ZzXinxWgmdBKB/lswJXu3cicY/H6msWNyi41lsz2LR67ZPTZBMUpTJzvaB6FifMPTW9lRp8/UJ1oOmaidzSLxGwSc0g=
*/