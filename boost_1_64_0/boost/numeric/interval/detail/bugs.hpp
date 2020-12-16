/* Boost interval/detail/bugs.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_BUGS
#define BOOST_NUMERIC_INTERVAL_DETAIL_BUGS

#include <boost/config.hpp>

#if defined(__GLIBC__) && (defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)) && !defined(__ICC)
#  define BOOST_HAS_INV_HYPERBOLIC
#endif

#ifdef BOOST_NO_STDC_NAMESPACE
#  define BOOST_NUMERIC_INTERVAL_using_math(a) using ::a
#  ifdef BOOST_HAS_INV_HYPERBOLIC
#    define BOOST_NUMERIC_INTERVAL_using_ahyp(a) using ::a
#  endif
#else
#  define BOOST_NUMERIC_INTERVAL_using_math(a) using std::a
#  if defined(BOOST_HAS_INV_HYPERBOLIC)
#    if defined(__GLIBCPP__) || defined(__GLIBCXX__)
#    define BOOST_NUMERIC_INTERVAL_using_ahyp(a) using ::a
#    else
#    define BOOST_NUMERIC_INTERVAL_using_ahyp(a) using std::a
#  endif
#  endif
#endif

#if defined(__COMO__) || defined(BOOST_INTEL)
#  define BOOST_NUMERIC_INTERVAL_using_max(a) using std::a
#elif defined(BOOST_NO_STDC_NAMESPACE)
#  define BOOST_NUMERIC_INTERVAL_using_max(a) using ::a
#else
#  define BOOST_NUMERIC_INTERVAL_using_max(a) using std::a
#endif

#ifndef BOOST_NUMERIC_INTERVAL_using_ahyp
#  define BOOST_NUMERIC_INTERVAL_using_ahyp(a)
#endif

#endif // BOOST_NUMERIC_INTERVAL_DETAIL_BUGS

/* bugs.hpp
6syWxE+i/TYJFsHseflvN2g+Yc683eMTf9J6gDnwtfJg3AOaM5gTswH/vuBGaxrGc7fJpC2htG7Tq+bZ/JrtqL4EwGozyzv6O8UvGebL4/BMPY3OwjA+1903ra1HOQFzZJa59+RsGh+Mj73FD8759J0BFsos+FVJFMUPxsf3ZUpBdVorE6vec0KTlvNorcBcmMV8UWp4dxIs5FKCE60VGI/tsQNtF1NewzTMTvwU50z7kWDNjv5lyGsYz/mF5Q2daOwwb2YlUW/oefdhPOc9dmyjvV8zqWotDxkz6x3tVbAoZp1yG3em2MJ8mLn8NnUYxRYWwmxBr8um9G4P431psPc7isM1mJliHxuMCnpN7W7BYpjNbZ5Vm/o5GWuF2dF87QR6t4AFMxu8sZj2ldkwLbPGTSc+o/cxWCCzzGQ7Q72G+TCbET7Jgd6rYGrld6bj8IOPf9E7bIa5akaldYgfIlgezExplylYPiz2o+Ff8wQrgaUq+99E/KB1qC1989cuxD2NtNMtMld9oTxPtNkwnWAUv2xDP1MFO7DYuBV+bdyKlhi3EznIF2V8M/AD037+n1FeM8vED/qd0xTR3ri0qr3Y7rCP1rtgWxMqXtGaXmauunyuWuWcVaOe4LnKNfK//SzsZFLV4vBvM8Vawm41bxurGH6GuqFYM1icV1qy3jLx71yLjxZf2BTWfK7j73obrjbcs67wvNHMYgRLg+kUC4A1bzh4oN7mw+IVqyG0K2FWXbAAK6wzxbwEawNLUcwJ1mPDgd/0VghTK6YR2hXDRpvAMHYTXG97/7Febwc0hvGpYA1/7P6Y7gnTKu0eIEhJC++/pjjYw5R2t2F/XWnXX28d7A1jOAcbvL90pN7SP5o5DPfcD1vx7/2n9JaP6uymtNsJ42M4AEtU7AfYgwHhffWmc8EzFdsmtEuHBVeD4Xnf49plzgBTvd1yrcyLSiuADXmRRePLdMOcKe2+xfXd55P/oLF7GOYsBzZw8IG9lIMwrdLuS1wvNvI4oLfZnoZ202HnWg0toXyBBSiWCZvxxeUdetsL81HuOQHX8OE1+9PYqxvWylhY/4EZcykOsAKl3TBcl3Ya1IByqQbeP5V2g4U5y6xh6OcgwWbD0pU56w3LCOjrpjc3H8yZssaSYfXbb1qntwtBhnv2EO5Zwuxzwa7BNIq1F+wRa9dGsDJmrQV7zqyVYOXMWgpWwaypYNj8qJ9NYHd8frqhNy2sg7KO4mFj3/R7SWOvZVi3DYV73odlK+0iYK4xzZdTX8INta46bMSiv+woPyMM5gybqFk7mmIL05rBcE872Ix/FlD8UqIxDKXdM6EmZ8NiFbuL65ZjayMotjCtYtdwXbw4dRuNAWam2FWVED9mJ3CtU3ajPsWP2XFci1/9mU0xgnVTcvAYrtYtHfboLTUGpuT8zx/DEmsxUW/qelgrynx+XLDrzoXO1FsBBpeptFujwny+smxFNeQTQ/w+BqBm9vJPab1/aqhZS4XxJcOoTgiWAvNRbAmuNo/6f0NrjLVbhCuvL9mwE6Yw9OXjIb/PVwcc9ObV1BCjSeLzmKXjets29QGNHZakzOdAoZ22Gd5RFBuAa4tp2tp0T1iZMi+98M+WnQ+Mp7g3N8xLd+Ge6haG+HXB1TvBspjmGlauWGdcry/4V4LeNiRijMo9Owr3PJFoyN02gpUzay1YcEvUV2UMGI5q8628L+lc0MaQ141w7fp51p+0jmAnlH7G4brt5z1mdGZoaxh7pLiOYPeVdtVx/XHRp7X+a47agnZs7+ftYMWwLKWdO65d5zo2pOe1xxgUc8L1z05/v6A9oANqhWI2uE6at+kLGkNHw/jUuK5/lHhSb7k=
*/