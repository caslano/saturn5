//
// detail/chrono.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CHRONO_HPP
#define BOOST_ASIO_DETAIL_CHRONO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_CHRONO)
# include <chrono>
#elif defined(BOOST_ASIO_HAS_BOOST_CHRONO)
# include <boost/chrono/system_clocks.hpp>
#endif // defined(BOOST_ASIO_HAS_BOOST_CHRONO)

namespace boost {
namespace asio {
namespace chrono {

#if defined(BOOST_ASIO_HAS_STD_CHRONO)
using std::chrono::duration;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::minutes;
using std::chrono::hours;
using std::chrono::time_point_cast;
#if defined(BOOST_ASIO_HAS_STD_CHRONO_MONOTONIC_CLOCK)
typedef std::chrono::monotonic_clock steady_clock;
#else // defined(BOOST_ASIO_HAS_STD_CHRONO_MONOTONIC_CLOCK)
using std::chrono::steady_clock;
#endif // defined(BOOST_ASIO_HAS_STD_CHRONO_MONOTONIC_CLOCK)
using std::chrono::system_clock;
using std::chrono::high_resolution_clock;
#elif defined(BOOST_ASIO_HAS_BOOST_CHRONO)
using boost::chrono::duration;
using boost::chrono::time_point;
using boost::chrono::duration_cast;
using boost::chrono::nanoseconds;
using boost::chrono::microseconds;
using boost::chrono::milliseconds;
using boost::chrono::seconds;
using boost::chrono::minutes;
using boost::chrono::hours;
using boost::chrono::time_point_cast;
using boost::chrono::system_clock;
using boost::chrono::steady_clock;
using boost::chrono::high_resolution_clock;
#endif // defined(BOOST_ASIO_HAS_BOOST_CHRONO)

} // namespace chrono
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_CHRONO_HPP

/* chrono.hpp
mINl2IQDiMJVxOEjfsNOoC/ib2RFSdRCS3REDwRgNKZjEdZiO04iBg/xGr+QaiJ7jILwQX20QheMxgJsxWFcwB18hpzEOpAe2VAQVdAMPRCM5diLK3gNz2TqEOXRBD0xA9twFnEwU7KKf1EFnTAR63EOr5FsKnFEHfTCHGzBBbyAmMaakBeV0QqDMBcRuIh30NPJSXijMfpjNKZhNQ7jBp7gI5LMoLeiKKqgDXpgAMZgBpZjIw7jFt5BzmRuIgvyoBKaoStGYgaWYieOIwaP8BUpZvE75EZp1EcPTMAq7MM1vICZzbUojapojB6YhDCcwD38QOo57BfqoCsCMB5zsQ77cAq38RrfkWgu/QhZUQDeaAp/DMIELMMunMMT/ETaeVwPb1RDI3TEcMzDekQiBk8Qj+TzqVsUQVX4oQeCMAtrcAS38AUpFmQVuVABzdAH47EM23EO9/AJiRdyNkAR1EMnjMYchGEvLuE5fiPVIuYifNAcvTEZK7Af0biNt9AhnKmQDzXQBkMxAyuxA2dwD++gFpNTKIZKaIh26I0gLEYkruIz3BLigmKohXYIxESEYAsO4xri8Bvpl5J3KA8/BGAuwrAf0YjFTyRZRk2gEMqhPrpjIpZhC/biLG7jPb4j1XJyFNXQGROwCvtwHfHIsoIYwhfdMArzsBkHcRmx+IFkocQFeVEWddEBPTEEkxGCrTiJ2/iA30i6kt6If1EMldAInRGIIMxGKMKxHxfxBN+QbBUzG4VQFjXQAH7ohqGYhIXYgl04ibv4Arua+kImFEA51EMnBCAI0xCCcBzFTbyHXkP+oCBqoxW6YiRmIgyHEINY/MTfa9lfFEZ5NEArdMVITEMI1mEXDuIcruEx3uIXUoYx5+GNOmiNnhiOWViNPYjCNcThO9w6ahxZkR+lURmN0Ba9MBhBmI0NOIGreIS3sOt5b2RHEVRAM3THGMzHekQiGrFIQNIN7DO8URWt0AcTsBhbcBhX8By/kWojuYqyqIrGaIMeGIHJWIAtOIhzuI1YfMQPJNnEepEVBVEeDdEZAZiIWViO9YjAMVzFPTzDO/xGys3kOvKgDGrBD10wEOMwD2sQjoOIxi08xTck2kLdogAqoBG6YjTmYD0OIQZxSECircQbpVANjdEefTAeyxCBE7iDT0gczrcNSsEXnTEKixGBE4iF20afQmk0Rw8MxhxsxFE8hIwgjiiIamiDQEzDapzCTbxC4u3EG6Xhi+4YjhBswxk8RAIS7aAukAdlURON0Q4DMB7LsBNnEItvSLqTdaMgyqEmOmAAxmIONmA3TuE6nuIHUu2iX6ECGqETAjEBy7ADd/ESejfXIxtKogoaoi16YihWIQqv8Bsp9vBdCB/4ohP6YSRmYRV24TTuwOzl/VEPg7Ace3ABd/AGf/DXPmYnvFETjdEDgzELS7EZxxGDe3iF70gUSZyRC6XRCP4YhrnYgCO4jrew+8kfFENdtEMApmM5wnEQ1/EUngPcG96ogQ4Yi1DsxyW8hjrI2QQlUR/+6I/pWIsDuIlY/EKqQ+Q+vFEX7TEYMxGGw7iBT0h1mL4GX/TFRIRiL27iE+QR6hiZkR9lUQdtMQDTsAK7cB6P8R2pj3I9aqAHJmEVDiEGcfiDVMe4N7zhhyFYiQicx2MkIMVx3gul4YsuCMJiHMAtPMN3pDjBPVEIleGHLhiK2diMSFzEE/xE6pOchVAGDeCP4ZiLddiPS3iCBKQ+Rc7CB77wx3DMwnocxjW8xG+kiaKGUBEN0R6BmI6ViMRNPEcCkp8mn1AINeCHfhiHWViNHTiBq3gJeSaryID8qIzm6IIgLEEEzuMhPiPFWeoU5dEGfTEJq3AAF/E=
*/