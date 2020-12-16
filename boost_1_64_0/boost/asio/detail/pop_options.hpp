//
// detail/pop_options.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// No header guard

#if defined(__COMO__)

// Comeau C++

#elif defined(__DMC__)

// Digital Mars C++

#elif defined(__INTEL_COMPILER) || defined(__ICL) \
  || defined(__ICC) || defined(__ECC)

// Intel C++

# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  if !defined(BOOST_ASIO_DISABLE_VISIBILITY)
#   pragma GCC visibility pop
#  endif // !defined(BOOST_ASIO_DISABLE_VISIBILITY)
# endif // (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)

#elif defined(__clang__)

// Clang

# if defined(__OBJC__)
#  if !defined(__APPLE_CC__) || (__APPLE_CC__ <= 1)
#   if defined(BOOST_ASIO_OBJC_WORKAROUND)
#    undef Protocol
#    undef id
#    undef BOOST_ASIO_OBJC_WORKAROUND
#   endif
#  endif
# endif

# if !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32)
#  if !defined(BOOST_ASIO_DISABLE_VISIBILITY)
#   pragma GCC visibility pop
#  endif // !defined(BOOST_ASIO_DISABLE_VISIBILITY)
# endif // !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32)

# pragma GCC diagnostic pop

#elif defined(__GNUC__)

// GNU C++

# if defined(__MINGW32__) || defined(__CYGWIN__)
#  pragma pack (pop)
# endif

# if defined(__OBJC__)
#  if !defined(__APPLE_CC__) || (__APPLE_CC__ <= 1)
#   if defined(BOOST_ASIO_OBJC_WORKAROUND)
#    undef Protocol
#    undef id
#    undef BOOST_ASIO_OBJC_WORKAROUND
#   endif
#  endif
# endif

# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  if !defined(BOOST_ASIO_DISABLE_VISIBILITY)
#   pragma GCC visibility pop
#  endif // !defined(BOOST_ASIO_DISABLE_VISIBILITY)
# endif // (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)

# pragma GCC diagnostic pop

#elif defined(__KCC)

// Kai C++

#elif defined(__sgi)

// SGI MIPSpro C++

#elif defined(__DECCXX)

// Compaq Tru64 Unix cxx

#elif defined(__ghs)

// Greenhills C++

#elif defined(__BORLANDC__)

// Borland C++

# pragma option pop
# pragma nopushoptwarn
# pragma nopackwarning

#elif defined(__MWERKS__)

// Metrowerks CodeWarrior

#elif defined(__SUNPRO_CC)

// Sun Workshop Compiler C++

#elif defined(__HP_aCC)

// HP aCC

#elif defined(__MRC__) || defined(__SC__)

// MPW MrCpp or SCpp

#elif defined(__IBMCPP__)

// IBM Visual Age

#elif defined(_MSC_VER)

// Microsoft Visual C++
//
// Must remain the last #elif since some other vendors (Metrowerks, for example)
// also #define _MSC_VER

# pragma warning (pop)
# pragma pack (pop)

# if defined(__cplusplus_cli) || defined(__cplusplus_winrt)
#  if defined(BOOST_ASIO_CLR_WORKAROUND)
#   undef generic
#   undef BOOST_ASIO_CLR_WORKAROUND
#  endif
# endif

#endif

/* pop_options.hpp
Zd67TiOSe2aG/d0rnw6VTZfKpc3fJZ/+Lanvfn5wWgqMk2+yrVk7B8kkmPQyE+iky/4NtPZqMVuVCgY3lryx0Mz276dL/MQWP0PdxM/dOX+Skvn0jQ3wgUTI+Sffztm3qE+w0Vt1H+MTKnVLKDzV3VNs8lOdS8veWMvMRtWsU95rqjpmVryxAh/qm/o01v6+OjqNleHOXEuPuLf9CbvOW3qnQe3cO7xHzrP0xExOZu4RY4s31jSz+6dBzD7255mA8S6YCH5aqMJw51QsqpX2FDbw4uGjZ+DkmO6eY5JbYtN9bM138PEWPZpDjRKdCZrcO9XWU9bnc8zdQ2++D6oKasqE9Tk17TgenFNTNyk/VROkf6/fOTPY8dFB3xT3zhqGOlt72NmHZwnnVO76hODgkPh7vN8+F6l4q3r+DfjHse89HJ5Yoia0XQsyZj7UK5yM6Z3rU469w5PFB3fGiRXrlOMYXWvhx/armQ34xOk0lZA7eNZVH/XF6vhgt7Z7q0NSIRCjE34RfZyy5q0CNQ+eJNVz7k4qlIfS28TalWufSimPiiEfdY+thk7I9XVqr7g7B7sf2/W9OTh0z7TJmeyWcLEtPE2uq8k0rR2axQ9vXcGRLAx07nSOekzcNQac91hhjtWVXBHWw04pXNeavgKLPrafzWzpybPDXTHuW8i3NeTZ+t/1oB5zKFrbHVcTpMePnnHrg/3dD110+dvOyjZ+bEPluRMUi5UxsxXudq/d9LVNkrvvaXC7kXPt8PnGH9sX+Oi7S2gy2b5V1zq40z7vUtnBLs0s+di6+ED34qcX7ih3+BtN/A3kEvyNmG6S6Zd7dMwk0Gijk/Tka+nH9r50uJqK+J/tJ/brO/tzV/TL7Tunr9Jc3wJ4cDbRs359SvK/dbbv7zjZN66/z7BRSm9TEbXfM9o7BiWqhjxzT+cKPJ1rt3qjMwVmn9q3qO0avXt7djTWvsyI3pW9UisYPSx7Jka9dLbuTsX29Rq9ep1eVqXNgzr9WVU4ugZ8F6D9Wk1w5dSR3gDUJ5GDT61QRm1TZ+tzyGPtdLBquz+9y/547V7aY8edn+3sq6KaHHcqfP5kj1Qd0tZO6H5OTrTboAoe1qv1qeX36uXVemGNnq7QcdV4tBaH3/B61rN/TN+YeTSvX9RDD5TsyRrB92mCrniaXm/VIr39yLQ3rW/WhVU/2d/USa+hgn9uJ/3d82q/17uRz7yvf9ErVu24mj01u7aoy2tU5ZiavKQilQIO8ZQXeMZP+4FH1O64eRU9d14dX61je2x3VJe97VuuqJDqs9D7vrv9gsr8fpccWZG7PfJH/dtBvZ5bLbP4U7t+UK/ja/L8irymwr2GvmWoTo76FKjQCvVp/CH1el61vLuOr1by3N56jhZGzIXolsTfV5XUNU+F1bckWheJv6nyb+Xd/U4R6lbW3xJuXAYv0r7nVOxA/57da79X0cP3A7fvBh7U7Ih6qbfST+2XR+p1+y29wVminJXp2zYFanWYubb69k3gb8IjT135d8tn9Nwf8RrH9OFTdcWOzpNvg6rvno3rMw06A7g/LaM30cP6LbROZu3PNddvDrt1/Zr1GQa9K6zPy+u9s05i3d3vfuL7Z9mntvqdfZAYFU7y4YP9EFY79B3YWLX2Kqu+VaJmdfVtNX1PrXUe/snVfVxnj6/u87v2uBl5rKL+Abdiln9qAT4aXkf8x+Izew8fhura6Tpdp+t0na7TdbpO1+k6XafrdJ2u03W6TtfpOl2n63SdrtN1uk7X6Tpdp+t0na7TdcT1G1BLAwQUAAAACADAsbxKp8YON4c2HwAAMIQAFQAAAGJpbjY0L2xpYmNyeXB0b01ELnBkYuw=
*/