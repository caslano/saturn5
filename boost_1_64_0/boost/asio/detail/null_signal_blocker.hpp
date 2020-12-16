//
// detail/null_signal_blocker.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_SIGNAL_BLOCKER_HPP
#define BOOST_ASIO_DETAIL_NULL_SIGNAL_BLOCKER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS) \
  || defined(BOOST_ASIO_WINDOWS) \
  || defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  || defined(__CYGWIN__) \
  || defined(__SYMBIAN32__)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_signal_blocker
  : private noncopyable
{
public:
  // Constructor blocks all signals for the calling thread.
  null_signal_blocker()
  {
  }

  // Destructor restores the previous signal mask.
  ~null_signal_blocker()
  {
  }

  // Block all signals for the calling thread.
  void block()
  {
  }

  // Restore the previous signal mask.
  void unblock()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)
       // || defined(BOOST_ASIO_WINDOWS)
       // || defined(BOOST_ASIO_WINDOWS_RUNTIME)
       // || defined(__CYGWIN__)
       // || defined(__SYMBIAN32__)

#endif // BOOST_ASIO_DETAIL_NULL_SIGNAL_BLOCKER_HPP

/* null_signal_blocker.hpp
0+3xFdCp2+Pbwafb436IeThfPOVSrjvtwtfBAbYP4C5oZvswfgH2sF5cPL9Qz3oXvg5sXrbHXRDR7fELIKyX2WwPYd0e10Im+wni3TCsc4VTLuMcWe/EJZDK9gHcBXWsD+MXIJP1MscuGTBMu/Fa6GM/Ju6HVLaP4SlZnAvrXbhWm+2DeDc063Hx2LlcS7a34QvBo+PERRBkvYHvAbfOG34KwqyP4FcgoOPJtstHIKTjxwvBYL0HN4FwTUP4EEQ9bH+5Xa6GQd0/fho62T6Kx+awjY4HXwimjgcXQUS3x/dAUMeDn4JE5jmCX4E9Op55jAeGdTx4IfTpeHAT5LA+hA9Bom5/BfMJPta78VpI1/3jpyCg54tfAZdu/xm2h0TdHq+FPTr/uB/Sdf7xlFzOUecf12rr/OPd0Knzj2+cz3gYfwhHwEFH8TFw0o4r7TIL0mk3LodMOoA3gIsO4d2QSsfwOVfxc6SEc8dfgwFanerm2afV54N9+WRRz4F0OoifARcdxWd8lncXrX4O/LT6qgX8rKfVHuik1SULeYfTtjx+1oCNY7nwUkikDfwQ7NEx47M/xz1Du/AzkMM2MWzL517Vc8ezwMl6N64HD61+DOpo9TMQpGP47EU8R7Qbl0M6HcI/hYjOD05azM8v1juwC6I6t7gcYnQAb4BBOoRrPs9nl9P4M9cwTjqMn4dMPS6esIT5pR14FgzrPnE5uFgfwBvAQYfwPhA6ijcv5T2ojYdgOy3X8k6AXbQDZ8AO2oXzoY324FrooQO4CTwc18S94KPDuB+CdBQPgUlLAfuHAO3AGWDQLpwP9bQH10InHcBN0EybuBfq6CgWD/eYXnc8DY7SLrwUDtMGXgcjtIl3QpKPZwofgQRaCvlZCXbaia+HNaWTRX03NNLq9dBDh/GKZbyL6BB+CiK0+qNF3D+0Oh1itBvfBEevY3ucVcx1Yb36617eb7R6Fxi0uwRDGeMJ4A2wig7hfeCnY9i2nGeEduBZsJ524+9CAvsRH+cFjXpe+I5S7is6hlOv41rT6tmwg1Yvgv20gX8NzYxZ3XE9zwut/jrsoW1lzDm0sb0LL4U1tIHXQQ9t4p3QQEfw1eW8H/hsADfBCG3inZBwPdvgQzBJx4nHV/Czm7bhKZDOeTlxNqTSblwCmbSB14KTDuJ2cNAhvBuydAz4EMykY3h8Jb830jY8BfJoJ86GXNqNS2AJbeC1MIMO4pdgEuNXn25wXFrt/QLPKa1+EIpp9Saoo51V/O1WzfnSNj/XDurLJ4u6GoK0+jbooUN4H9iZnyieUMM9QDvw3VBG22q5FpBEu3AVTKXVgzCTVn96BedIB/DrUMz+XXV26QZ/2WRR/xLqafVrYNLq01fys4x24W5I4rPqX4KDVr8GmbT69Bu4t2kXfhXWcFznF5kTOEirn4MYrX4BEtm/+jVw0M5VdpkPk9jGg++AGaxXfx+yaPWY1Vwj2omvgb20+mE4SKufhaO0fIn3E6xin0H8BKyn1a9DD62efiPPJO3BqyGNDuJ7AswV5xXDU26yc29yjngpHGC9gddBhDZxGPbQEXwEhmnbzVwviNEuvBSE/Rh4HUT1s3gnJLI+go/AIOvlFt6fEKadeNYazpFtAngDpNMhvA8cdBTLl3leaBueBjm0gdeBjzbxTthLR/ExcNG2tWwPHtqFl4KbNrDzVuaK9uDV4KSDeAsspsP4FTBo9UfreefT6o3QTEfxMcikbbdxbWEX7cIHYYC23c48w37aiefDpErGgNeBnTbxRXfwLNAenNTA/UAH8NJ17Jd23MmxIId23WWXW2ANbeJfwCraFuQ/K4MGOoA3QBodwvtgKh3FQzDCeOQ=
*/