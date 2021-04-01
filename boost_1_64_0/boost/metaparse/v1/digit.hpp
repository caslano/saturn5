#ifndef BOOST_METAPARSE_V1_DIGIT_HPP
#define BOOST_METAPARSE_V1_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/digit_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/change_error_message.hpp>

#include <boost/metaparse/v1/util/is_digit.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        accept_when<
          change_error_message<one_char, error::digit_expected>,
          util::is_digit<>,
          error::digit_expected
        >
        digit;
    }
  }
}

#endif


/* digit.hpp
RZdgTtdvUnedD2W2V7kw321eJYzWilnF5dVK5BcEUt5SDOF1sj7DZ8QR1VeP9Stpl8dYCxLdYBJVKI5S2ybJ/dpg4cuC80JHJvVduEGFa+2pPFCD6DhdYZAYKipsnY0TWHVIzXymhTgeJO0+fBQyJ3ucR6SguNXRxzeGUlsMcyRVbEkkS71LewRPJ8tStSInKgsARavMZ/dXyrWDLeDUWubY8V3guE6OiFCb+g9XSoo752/kBL7HLNFfcLRYjsoqXylasVZI7dZ4/T/Q2SjM1Uka5Q6K6MX2rbG6SZ8Hs67qtIRYFzYrE0kT6gm3s9VwA7iHeAYnXKJehcOSRnK8kSU9AwClPufaAGY/eKfFsrIjdpmPZD1i5uB0VvDpTNwfjrAVrw1DVt/SNaAfmRa7BCeRILMhnwpuuRwyq3PaBXraDzizo5LmWqTs08PLdZWJ7qm1xf8mdTJ067jQ4a+97ROYVrVLV+CaFffIvDvnFoa8M9BSIz9WXAJAtUfdB/Eq6Lun2OiL/jGCsS/5ZYfw/+OPlBZ4eALVBPAiq65MBndw7RGjFEjsF5L3jg==
*/