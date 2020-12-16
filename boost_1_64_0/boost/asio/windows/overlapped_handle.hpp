//
// windows/overlapped_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_OVERLAPPED_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_OVERLAPPED_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE) \
  || defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/windows/basic_overlapped_handle.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Typedef for the typical usage of an overlapped handle.
typedef basic_overlapped_handle<> overlapped_handle;

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
       //   || defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_OVERLAPPED_HANDLE_HPP

/* overlapped_handle.hpp
LMp52puc+8m5X34nGAQ7WzMeoZ5mPEIPsA2YAsbz+IREHp8wALwdHMTjFMbwOIWpPE5hBo9TeIPHKRzlcQoTFe34BO5j5j7rVW7jCzrw+ISOPD6hK6/J1E3I+Nz3y2tF/YLxCWK+c3zCzv/T8QllBu73437MVeAQ2NWsT1gm7ONUfsd7+z/Me4rv4fEy+3n8y7vgPvB9EM+E1siqBX4AZoCHwFzwCPgceAz8AvwIvASeAONxzpNgL/BjcDp4ClwCnuW1z74E14D/ANeCX4FHwW/BOBPeH/gseAk8B/4IGs32NQAzwavgW+BP4GHwZ/ACqL5niw/qFTACNIKnQRPYxGJf628c6AM+DlrAI6AVrGG154c00A9cAgaAO8FA8EcwCGzja88XfcBgcC0YAn4AhoJBfkLcBt4FhoOrwVrg92AEWN9fiDpgYADGkIEJYF2wCxgNdgu056+RYEMwD2wEzgYbg0OC0J4Cx4Ax4KAa9vxzLxgLrgNbgb6od1uDIWAbcA4YD54HE0ARgroGRPVO+agc7AD6h6K8gslgIlgAdgIfBzuDR8Au4BWwK9gnzF7fZIM9wRVgb/ApcBD4KjgYxFgqlzEcV4+YfvE4jqrGcAQcRTsDNhl2LOzso/p4Dd38e0w16f+zphTYbor+/6EY1CWsLzXxt+NBbrOV8HzgA3OkvtTTfmE47jqfVFB7ZaynucAcNkHqVI1zq9xPjMP3oLR+HyNc5gKHQ3doAgfXx7cPdiCsQ0e/6hrjqUs1c3sr3Ob2bneb27vTy9xeXI+c23suAt9szdzei9Tm8NaWvfG2qec2qPe25gvUNv39qb88OmFD0UeLM98MPL6naJ+3NrS3tri3tvUva8tmCH6f4IOcv6ywA/jlBPO6nuHcVqkF9gUjwJFgbXACGAlOB+uAahpRYG41fWvK9G+LbnSjG93oRje60Y1udKMbjfxfcAvlf5sth/5lTZkwjjoAfuUagGofwIMxSIP7AAq5D6Ajj/2Oh22krtHGfQC9e/dST902PjHLVkAXJXiMsOuaJ/0UR5x4jWw/ZXoxH+/verzyumhuxyNobZZJRYKPD/GYft4M23ghaC9F+56mHEZxrHdCYYt95BhaGTbOLSzkSjk2vV+wvU8h9Rrj/tNAk9sc7AzZd4B7Z7+x2rHJ7JcL4h7hh3tkv0IZ13FfIXRduP5K+rSd4ubNgT5LfQcZJ8ofatb9q7BJm+e3PVrz9bdvvf7tvNC8B86DLvOHuY+A5ySQfivMTfbfdvTG5P4DR03XLfuf0WV/3ehGN7rRjW50oxvd6EY3/w753zb+psn/D8QIOff7G17fpjHL/3Vg60EuTdPI/zi1FP69yP4cvrFX2Z+Pe5Tt09yOIx5+44x8PE97nOcP34d7uPc65pDz/PxKcnqiBzk92YNMngriOPxwPbdI/o5KJf+/rpwT/3hLS4ud3VsePPphNYx/PU/yNj9bsDG7fWCT+CEGsfxdAwxl+Tuc5fI67K4PhoI5v0Iuv16Z3HpMl8l1oxvd6EY3utGNbnSjG938e0y1yf/jb57+/36N/r/CwMIyy/9dYaMgA38z2yn/j79O/b89TlevfQB83Kv+n4971f/z8ar0/whz/fp/Div1/259DzJsolvYUs1YgbD/4LECql9pNfRfpFH/xbgnehT/LqfivG3O6KQ2fTpvrZ7+C/keOQ+7jx8I4f6LULArWLMaxw/E6H0VutGNbnSjG93oRje60c3/lKk++X/c+Jsl/69g/b92/H83lv/bw0ZC1izTyP849TX1//bw3bzK/nzcq+zPx73K/ny8Ctmfw7CMPrYKeT7OLSzkQR5XAOLearBMn3gNmT7Zg0yf6kE=
*/