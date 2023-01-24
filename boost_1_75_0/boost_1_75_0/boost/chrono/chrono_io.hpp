
//  chrono_io
//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2010-2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o under lvm/libc++  to Boost

#ifndef BOOST_CHRONO_CHRONO_IO_HPP
#define BOOST_CHRONO_CHRONO_IO_HPP

#include <boost/chrono/config.hpp>

//#if BOOST_CHRONO_VERSION == 2
//#include <boost/chrono/io/time_point_io.hpp>
//#include <boost/chrono/io/duration_io.hpp>
//#elif BOOST_CHRONO_VERSION == 1
//#include <boost/chrono/io_v1/chrono_io.hpp>
//#endif

#if defined BOOST_CHRONO_DONT_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0
#include <boost/chrono/io/time_point_io.hpp>
#include <boost/chrono/io/duration_io.hpp>
#else
#include <boost/chrono/io_v1/chrono_io.hpp>
#endif

#include <boost/chrono/io/utility/to_string.hpp>

#endif  // BOOST_CHRONO_CHRONO_IO_HPP

/* chrono_io.hpp
9X8DOZVV0FYzAO8Gkv6Pb0n/x7fJjartOsykxMFz6diGYoVTjrI7w0a+uKlhIx/sbabng/X75NBwU5mL+T4qnm3iyAh2DT1+KB1G1DL5pk4QO22ZsLfIqxaMtiECz5BR+SKLyX8EIGFWNPsCU/M1u067pukzgnAUniwYrr4QpboIvGon/tb110SGmGU+qXSOxjH9Xb+bMIcXKOsQn37rD+oQrWYdIp17mHjht643A5chezBakHqgtrUgRcClXDUI3B0WijYlsXFTijLtWmGMkEKmTTfk8waC++snQiTHNxS5Tgu28brpBXxSyAfFZs818aZIhH0j4Xe2xWJo19fXnPwI7GTzsfIqJoylUfz4Tw9q87DzQZZLi8pJTL2RL9fzZWh5jCVaLhx+3cnkwgtqWtF14LsnmMF46TUtqj64g2s0yxPNMy/FYgzu5FT/x+w2RMekBw1ZNvq8akH+qc6r7ljzx86rNm451XmV89q2z6veOu+U51XlW/5vnlfdt/rPn1fd+beTnldVzGKcmiWui2fr638W4dUTs3Xf0AibYBFdev8w3SYYbZHykD4qpFUnDvlJ2KKfxCF8ukpwyJ2kwKdkmic3eTIfKHWUP4t+1zsccy7lZGmOOReQh8f83RZhYOVAyxbNTeEqD7opOOZQIKwADp1MvF4/y6LxRrEeMk/0yk9QDbr/yLVk+fkp2wJihLYF4lbzCj+PMh3Y
*/