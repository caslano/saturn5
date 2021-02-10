//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <complex> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/complex is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_COMPLEX
#  define BOOST_CONFIG_COMPLEX

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_COMPLEX_RECURSION
#  endif

#  include <complex>

#  ifdef BOOST_CONFIG_NO_COMPLEX_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_COMPLEX_RECURSION
#  endif

#endif

/* complex.hpp
QEU2FBqaU7bpYGrSaJAlIiB+wZRGzFYzKXykp6Bps1Y9jCmCcCWBbAjjZIl0REOlda3eDId523DcybCQuRrmOyn8Sq//s6s5VrMmdyBrDVpCq6gHJt6DtSxYae4oES7W7ZIzVXn7spBQFEPZgKKc93CYyqjqtkAh6dXyTCTUWD3T5qakUIZtW8n1g0CUtQcq20YgHcqCcYVE4T1oRUEbG2+F2LH0KlvJv9Gyfe0FSIFVgRskECYuLIliyoObML2MZyncBNNpEKVziD9CEM17vKswukBvMGRtgN7WDVVYRQNsXXNGiwfk33XSHT+9hPPZdBxGH+MsCq5H4zi+mk2yNLwewUtwX7yGoF0Zf//sgsvZ0hgAfvFfvfKf44L5l1Gi7rIV1UyU0vQbbaUQObkEA+g8Cr94BphlpRZkTYFL+Wdbg2ZrarOTeRRPkjBxfmAi521B4czwdR6s3jsWOZe4flDGwLyC4wrtwdElj5WAppOtcfixIa2P3lrei1FyPg0naRhHzoRgJwjUkgltPIJjscvB537EOutITbgt3oyqorkUhYKy6Z2oNI6g0wrN+H7H2GfJN0ysYItDmktsN9Wm385NRdFGGFCwxpyo6LFSci63tPA6OkNk0SnJKwz8q6XKxpGisO5GKdBOiJXQ
*/