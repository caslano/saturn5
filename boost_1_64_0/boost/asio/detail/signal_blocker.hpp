//
// detail/signal_blocker.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SIGNAL_BLOCKER_HPP
#define BOOST_ASIO_DETAIL_SIGNAL_BLOCKER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS) || defined(BOOST_ASIO_WINDOWS) \
  || defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  || defined(__CYGWIN__) || defined(__SYMBIAN32__)
# include <boost/asio/detail/null_signal_blocker.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_signal_blocker.hpp>
#else
# error Only Windows and POSIX are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS) || defined(BOOST_ASIO_WINDOWS) \
  || defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  || defined(__CYGWIN__) || defined(__SYMBIAN32__)
typedef null_signal_blocker signal_blocker;
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_signal_blocker signal_blocker;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_SIGNAL_BLOCKER_HPP

/* signal_blocker.hpp
6kbS5morG6erf7m2K6jbSmNvu9xitJXhdh9Desd9NbeKPcc3U0rRF7O9PCp0p9u6OrGfJf1KaCzkNXxHncLUPDBRZKBEmP59FN1ScUN9idu14pYtMhnilv3hxyS+t+HWBenIF/qZ9Pu+0KeJWzLPG2aL22gjRb7lk3jbiNsr6m4gcZ/n0+4J4v4HxLxL4oDsJvG+Iu4hoZ1JNwetuCfLTNeOu53xENuoo+19xb1lbIdSP1zftNuhQ1+H8oUbyzeiPaXO1B+5HKYrz1/3Bn1Ops0Xy0obHPyAXSQ2P5CurzVvKhP7+Z58MJP0zv2nS8W+gG1P01PvJjxQzPjYfzF8D8f6RGV9hUOfXyj+eQ69Q7HVp24Qv3iHvN1g9c9Xi18b2pFLsfutOnosueVtVdeLlBPbanT/mGO1X8mvrhPKBPtnGTpn3HNTDHO0E4yuEyWsFWBFPNb9EKRLtXSVcX312DHN1T4Rg10vDDM++s4Nls8QiSPOKp8FYo93nfNOJu1Z4pdmtIW/HR/7KdZTptBkoSbDsoc0fSZqY5a5dtVena3BrjlAfCv1O3r9iv1qvMSTEXO9KiT+A0Rebmn9edxvQTeWGdY8+ku8av+oe8/m3jk6wlqfrjvFs1PU2SOhb6wdWta8PJes65Fh5mN2nGLKdJF3OVnz221Ce6ZvMCjLYN5Fili3jCfV2j/8fD+WmT3vrK0svdDaP9wZ/qCS1aprjfhInrDqeazQdQRVW4svHhS3No45Je9bYDovE/+syLS45E+epxe57xZJ+yLfILTDNryf4hPe1VSAci2EeRa/n4T5jGbx15A3Pe5rstyQPrip9PEMBPvQ6rnR97v8CGN7bn9d58sLxk+cqPboTpq8YOL86bl50+fOKdDdluT7lsGRe+YY1nE/y31N3vee4dr7hfi498udzlm50em8FbTVTaVTiiBmOhk2xdl/lzQ45FL62+dTvmI+3DKP+gbvYWHeHvfI29pumPdbeZs4d86UgkXjZy2cXFBZugrlX17uGIM/aUG6ZN7L7y2eF/29QeDFXZ7fs+t6QCePc2pfo64RH8vIXR5j5ken73PQvuiVvuqqah6l432DkWlkON41kyj+KoB6CMFx51NEPhadQj7wTebDvvsqUdzs79jlD78F0fmbjfo+6pm/+tplsfPGMCmOO4aqOcZwbIzIV/5XzBd5mHcJyTdceXrLI0/ZnZDXAR55Yrv05imGid0u4f/V2+WATs23SzNPG/M82iXWurOsPE2dPAeKoVlyZ6a0FEnzM9H1hDBfvZ0gPs92UrIwOn1x6p49r/TZLYW66cg0MhzbyVVe7URovno7CXi0k6tc7SSiH1gUnb/LUP7V3vkjV8WqA4Zrqr//Gnz1TErzfGXmq8M50fk6Hx/ZYuVrbu7kOQsWzCpYkDd/+pypBUvLKkuMmGeFGS6F+ujoPoD+9v7vU8gXvheVL3yDfYA7X3s88pU+FmNErHxhLDO4/tZHy/W4uhY35DrHl4i0L2xB2s25Yx+RgxhnhDyxIz86rYWI9MUYaXWOM971wLBsP+mJMcaZr9F+WBeu9oPvxGw/a8715rOjsfLIscY7fwwXi8/E/6uPNS3hM7PuCs+LztcT/2bvTOCjKu44vpuLQAKEO5xGDrkhXIqAGpBLQAinUZEQkiDRkKQkKCpooFSxpZUqVdpSRUVFpRUVFTypotKKLSoqKrbUYkXrQRWV1qP9zrzfvn27+5YEPHoRPsN3581/7nnz5p7+fBd6huJlt2mPyJtC7GgHRufd7szouMmu8u7Wxr55h8yR5x1+xuQd/sTkXd9QG+Fsx5WuDuwc7XHkdbbiaHc0mC6dxso7Rq4TklwTj9k=
*/