//
// steady_timer.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_STEADY_TIMER_HPP
#define BOOST_ASIO_STEADY_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_waitable_timer.hpp>
#include <boost/asio/detail/chrono.hpp>

namespace boost {
namespace asio {

/// Typedef for a timer based on the steady clock.
/**
 * This typedef uses the C++11 @c &lt;chrono&gt; standard library facility, if
 * available. Otherwise, it may use the Boost.Chrono library. To explicitly
 * utilise Boost.Chrono, use the basic_waitable_timer template directly:
 * @code
 * typedef basic_waitable_timer<boost::chrono::steady_clock> timer;
 * @endcode
 */
typedef basic_waitable_timer<chrono::steady_clock> steady_timer;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_STEADY_TIMER_HPP

/* steady_timer.hpp
fOotD81iH8viuZXjq3zdHsCcVVI3OBWz2jF9Zw19A3Tbb7V+R9h0nDim2tO0LRXt6bwPy89xfOx9PNqDyyz8b/ucPIE1DXIPxuFSjMOlPfKcXN831mAsBq08LXxtlNZCxj0e8ZWtghhn4LP999bQY6Ddj1XagWHCHgX8PIN2xvlrSbcbLNyHe6tfhbzzuNa+DNf51MuAXQRaU4lPLK6XXQO/uxQT81Cdy9G3a+hE0I0qb4aJ+vmMq58X8L5l9fSn03GuEf7G9wx2gjx/fZxWtQFnvEPuvZ11rG4LZN0BvT9ckmf7UkZUOkLo539RQ4FfQmb7vWprhjE7Jej7IY/MHXK5p8t/5Ro7D38P6XflpOxa5y67bvK5hvvFZB5pyPtrTXlftME87FlwPycp9mZjT9RQAbTmD85zNBP7HWi9xEEuGEvvvT+S7eO+dvmQl7Q75YV9NfRP0P4/sLVzGk4cU3nysSr1W6ibtGfQ4/M7FRQM0vGgkSe0OkzDq/OI/L9q6CnQrko+xDHIoXE61WzL4Rjqh7ph3ol2Ff3s3u5V7wB5roWSzwiZReq9QkF6H2jLH1VdOcZtsvrCQdoAuk2lcWBVx6/f8T7bPES/Wncs9ypdQNU289gzcDwzPJc27W6mV+xqof7bWun5N2fohGva6Mitc2nV5nbswU7GHmwt9mAnwX7nWFK7MLEvr7y3I3jJqM1L1h/MOp5Yh7qkUJfFqMsi1GUh6tLO6iLvz/rQoVUJd19b5B28FParSexXsW8d4Hfw4lQ6L0gv3xKkR/6kxpHC/N5DcCm7DzYGuRo6PIuzIexJkxizyZL83jBs20G9IRJ2qEKWC+KMFnuKW4PU+IkgDZdVnRgm1o+Ebecq/TxIezNTJhwHD74gSI+Ddmn5cMywbDHtMwPHXfpYkGLDBBz2Cd/C/akHUL8/q3wYxvwpRXR/Sv7C22GbCz7TjvnUjr1xO9qmvdxWai0Kua8tQW3DsGNCu7VlQ9SG9hRS4Yx7F7neu4dzubS6DnVsd5AeA6X3VdqCYYJn+4zrdS+e8U7Xes1qP11FHufyEdcpVvayPwrS5aDOv2jf6ooTw+Q3Svtf28a7/8dB2gzaoqXjmNGIsY81rrEnomRyjBP6SZBWg26Vac17fqhLCONnF/A/gB7X68nSiPIcmC++YvHIOvBI6Oah71oI2W/hqOCRzJZSYSn7/G9UyprgrbgLZ3JES6MrbfIWgt/C1nDuOPyIwCdM38NBuu6RIG2dYvLjG+L0BvC212Ur51xFcXtX2IrijsqjQXoQtGtKfSvDPOaNtOM93NWONw9WYfP52iMPH56H84wOtEE7tR/RAi23ZXdSND2l6HccjeURWr6jvdhWaM23DDb3N3Vr9/3Ar0zZcNtfg/TDv6Hv/6rZoSCMWJite49Si/EclKY06nJ9UzaFq2jkPxhrFKJdZjqJ51Zb2OmghyQOcsFYenEGY6zBPTCnHn+bofukORJ2gkfR2NNBOuqfQer+m1720RZ2Pahf4iAXjKVnvFqOofsrI6i/DnVRvCpJxZoQ3RYM0b16+eMtFvbyUIgmVFluGEsv2/wMkqcY0g/GiH7+05ul7miIfgpa+XfdNvN0C4vHQvQiiYPcMJ7el05gyJyvmKM708XafGow2Z9Q95jAi9OTCXz7HOprCdEO0B6tPI5xuU7dpWihlTvZ/Qj3+GpPNmrvyfCf9i0pfAt+s/im3rg8Wyr4Cu8IUcdeqYnR272J+peH6AOgsac6HOPAxO4HjZu4lBHMc9FsrYV3rwjRIzIM5IbxPIDp5R2cb3um4abN94B197db96G0HX5BfgLa8w9tLWC4vofNTIase4f/Rtjx2PdP2eE=
*/