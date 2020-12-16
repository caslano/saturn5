//
// detail/functional.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FUNCTIONAL_HPP
#define BOOST_ASIO_DETAIL_FUNCTIONAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <functional>

#if !defined(BOOST_ASIO_HAS_STD_FUNCTION)
# include <boost/function.hpp>
#endif // !defined(BOOST_ASIO_HAS_STD_FUNCTION)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_FUNCTION)
using std::function;
#else // defined(BOOST_ASIO_HAS_STD_FUNCTION)
using boost::function;
#endif // defined(BOOST_ASIO_HAS_STD_FUNCTION)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_FUNCTIONAL_HPP

/* functional.hpp
tvmhU+YS3W2u0HlzjS6a63TV3KAHzU16OHo8x9N+oc2X9i+jhfNhTtI95hTtm9N0yZyhq+Ys3Ygevz/HE+1/PMdzke2f7Z3mHB+fMZfYnpPx77u8fs0ttlfNDbphrtOFos2Prnezr/GaA3rEXKJT6+z80N3mmubHXKfL5gZdNzfpYXOLTp5h4+H4MjQWzlfeHLC9aE6yvWausH0oejznqxX1D40btc0nH99hTtNd5gydNWfpnDlHB2afrtJooOvmEt00V0LjhcL2r+vBXGN7xlzXeMwNzU/oR5ZHlge2VDc/xOslPfZZ4ftLe3yGbpizdNOco1vm0Z9vwvb2i9k+TU7J0+Wuix/aeOuX6nFvHMf3U8rJNzH7yrUT5XfKyg2z+u2Kt8f2f3B7f2/B56GDwtvKFu53oVyUp8kVebo8KPtyU55L44MGPUPulGfJGXm2nJXnyAW5L3T8fXCvjU/tM+WyvECuy4vkITlv47v8/s833l+F7Slrz9Bps09nIo/j+M0BnTeX6II5TRfNWbpsztG16PFjeTzmCj0UjZ/9h831sB0fbOz+TXfAer/G4zE3dTyw3q/RW6L3fzw+c5bObXloz5d/+tIc++hwvj9s46dL5gxdhXU+Qg/SWOghc479W+YG3V6N5jN0hzlLd5pzdMacoXvMo/99NWz31T5DLskz5Wr1nzT/2XEvCPd3lY2frph9uk6jgR4y1+gRWO9vQ3dstfmmu8x19s+as2zPmxtsL8L6PBO6Gj2eHoj604PmJt00t+gWrPMNY7na+tMdNBaOp9Oc4eMz5pbGD+v5wfGbU2wPzGm6HG2PrplzGr/Zp4fNAd1+zf2ff9wfOR8f0f1bbshz5ZY8T26/kp4vd8q+nJUXyL68SC7Kebkqz7HxyLPkIbnPxiPPtvHo+lkod8jT5S55htwjz5QLV/2Tnh//hCUeZ3j+9wvP/9fseqKHzBW6Bev6Cp281a4vutOcoTPmLJ0z52jf7NOBucT9lc01umpu0nVzS+Ol0aDxmhu0d1v0fOL4zT6dorFwPGlzku42j75/8vjUPlf25dlyUc6Hjn8/aIZcVrsv1+ReeVCeKQ/Jc+SWPE1u3xVd/zw+eb6ckRfIPbv+/dfvr594yIkNjgOvR+18f3klcng/RQ7vg8xZZvzggPfglszY/cPr7ft2fdJlWPf/0DVzk27QWOiWOUl7P7DrkU7KOBOhUzQa6LTZ5/67I/PxOXOJ7QVzmu1Fc4aumLP0gDmn8Zsr3N6wuUaPRP3p5F3R6y3Hbw7oLnOJ7qZHLbi+eTxq75X9+PkC7/X8gOPnx2zrr8f71l+eLlfkmXT8/AgdPz9myan4+ud86fHz5MG7/v3Ph/tbfP0eZnLCeI7v0cxp5lFL43Fc33zc+If2fBn9/HkGfz7Arhe6Buv9V+g6rPdnoRtmn/1b5gAOL0i73uikOc3tpcx1bi9trrF/d9RO95ib7J+PzPaiuaXjicz+1Wj7Oh4aC9uHzBm2D5uTbB8xl3Q8P7Z29u80p9g/Y07TWRoNdI5GAx/vR2Z7EJn7K5mb7F81+zoec6DzY86xvUmjge2tyDqen9jjdTzmko7HPPrnEXh8ap8n+/ICuSj3yVV5ujwgz5Ab8kJ5RJ4J8+cJovsNxyfPl3Ny3sYj+3JFnmX7l2fLTXmO7W93dL/j9bn7P/N+8mCXqo6j8bzxnJ/nM9desPf9p/VCOnNkvP7+Fr/rb7cnn7f3z+H2/+xJoW9ro9fI35DXy9+SN8p3yJvl78iXyV+Tt8q3y9vkb8rb5W/LO+Q75Z3yhRr0LvlLar9DvkTtd8lfUftueWeb95CWhZgyVgfz3yflpFySU/K00PHvu58=
*/