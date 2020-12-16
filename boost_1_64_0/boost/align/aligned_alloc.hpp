/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGNED_ALLOC_HPP
#define BOOST_ALIGN_ALIGNED_ALLOC_HPP

#include <boost/config.hpp>

#if defined(BOOST_HAS_UNISTD_H)
#include <unistd.h>
#endif

#if defined(__APPLE__) || defined(__APPLE_CC__) || defined(macintosh)
#include <AvailabilityMacros.h>
#endif

#if defined(BOOST_ALIGN_USE_ALLOCATE)
#include <boost/align/detail/aligned_alloc.hpp>
#elif defined(_MSC_VER) && !defined(UNDER_CE)
#include <boost/align/detail/aligned_alloc_msvc.hpp>
#elif defined(__MINGW32__) && (__MSVCRT_VERSION__ >= 0x0700)
#include <boost/align/detail/aligned_alloc_msvc.hpp>
#elif defined(__MINGW32__)
#include <boost/align/detail/aligned_alloc_mingw.hpp>
#elif MAC_OS_X_VERSION_MIN_REQUIRED >= 1090
#include <boost/align/detail/aligned_alloc_posix.hpp>
#elif MAC_OS_X_VERSION_MIN_REQUIRED >= 1060
#include <boost/align/detail/aligned_alloc_macos.hpp>
#elif defined(__ANDROID__)
#include <boost/align/detail/aligned_alloc_android.hpp>
#elif defined(__SunOS_5_11) || defined(__SunOS_5_12)
#include <boost/align/detail/aligned_alloc_posix.hpp>
#elif defined(sun) || defined(__sun)
#include <boost/align/detail/aligned_alloc_sunos.hpp>
#elif (_POSIX_C_SOURCE >= 200112L) || (_XOPEN_SOURCE >= 600)
#include <boost/align/detail/aligned_alloc_posix.hpp>
#else
#include <boost/align/detail/aligned_alloc.hpp>
#endif

#endif

/* aligned_alloc.hpp
p1IPfqd70md40hM96Ume9Dt02nbpIY9XSs7JJQlGAt7gPhLEvzZGageRFzFfIoMK7rRXjOzKfpQ2+IgFauuCiZJbOTNq7CeTjqlXNJ2opeWWslNH9LHPNpwUeWdBy2H9Wh/LIsEOj6s425M+x5M2PenJnvS5Oi0mIXTipXe5FSJBW6vIbai94qE5I39Km4PYYawEOWxcBqp1Mg3GflRFiSaD/NN5UfM1Nuzg60RfcGVUtDFKCwt9hMT50GGP2ygHaez3gx3aMUzxOIkLPOmpnvQ0T3q6697TVIUwm+FSRfQJVXpL2DtBED9zRdHyjzxNe48iaW0kn7+GyIuqZ9AmZm6OBZ9GORNpvCIUR0gbNzBh4u0v1MhUeBCzPOkZnnSlTuueLwTt10yIBNcSX6irU7x9JxyDwI/Ue5Wney8xDk1epGFGlvEIbWEiGslSEoA4IWo0R9jLnxqD+Mxu0BMxdRYO73Nssz0a3G6reSWLIwZo3hpTTVFjayTRdjr2TswqePTdM23yl3kbcWunk5F0cnY6WZVORtPJGCXRb+HO3rsOZkEBSxGMDDgMi5oJ5CA1BCliSLCPfG9wJSFrJhAdGpGGJ65fEqYNUSQmVkF4wKaY0RpR66PqVkLdIWLRRIrHQNhzLgJtoEm69EQUmxyQOcdGk7xVRB/dzgVCXCHYi9yoepYyL46Zf2SLDb6ATMp5F93q9CWe9DxPer5Ow0Y0XVGK2+R2iCYz2Akc8e5EJiG4gMhpuOcXf7qI9lqBIlu1CW3YS9wVM3ZpmiR7jKQiMBfzuQjt0zGeo+deirCXHo2tzh7CLhPCoFjrGKcNlHl5xPyDZD6jkX63h4ArPOkrPemFOs3W4RJmy61IrTMSXOMh7CoQxs9peP5XyfW0TyuiVgtlUK6WiHqKKIsZG9BGSlziVtvmRiLONjbSs9+jcbjag897Pen3edKLPOn3e9If0GnCuiimtPIPg42AR8QvIiG4nvpB9QZKYFoHOKsfJILdHsI+6BJ2ff0nXqF9XhJCiTpCfj0xVxOlZIwmkcDsI8Ji5E/3pcR0TYTVEYjQ3eJIsNeD+LWe9Ic86Q970td50h9JCWqABs6NuBqIVJqeSMPPv3DiVNoZBqJY+fqixsqI0Uj4E7Efhb/G9dKbbbWHaERMgqaiP69GEs/7KSZRO5lIIRdOzNzNqolAx9idIvJ629xBRAa30d0S6DYBAc2EK+8nm3ODh4wbPembPOlqT7rGNbY2D6mXya0m1Q62uaSeO6x1PG01A6nwMa7EWuCJRRWfRVUuEWJAGWn0VlHFrfTIj0Xzuum6lEhHmi50f0tMPcm3QuzHod0oYvKQi108yPxEVL1OmegjkRkN7qXMWzlHgC6TtFiD0EMnFOJW0yPGIfRkRRoeOO3atbRTjUQXH/HN9twM0ENNlsaMZnJxGJ9eLa4H/faGlEqKc9SkYj+Klpaxu2BcRUZMgWurUGF4VL0JcqZj1MWchF/E+CKxdRAGAMgAMD9V7F4FQEigJCeqyLHFwDN1D7t2OF4aPBvMFwpXxehgIUwbsAODkMn2FuxCplgJg1wDYqTLmrErkpJQMz3AWBmlj1FFDLLNmOrjXizYC08fI6LAMnowmMJzZkQE0QPouBMK1rsUdAoFSBAFzBT4a2rPoww7s7AEDwNHg/uJiJi5L4oKZdANoaQPkMiDBJ+SLBGTWAEFf0IEMA/3Rw0f/HujBH4QyC5vFJig5y4hwwN7eUDCk6PdbejiZTIwB74JN4A2XULt4WjPKWcQhyW0/EMW3Iu+nxTPgLH1QMZkFGVodrobQ7Tp8MGNrQEX4cPgCEjQw13jqQgNi+dnSGD0Eqqmh1JR5SuJqS0=
*/