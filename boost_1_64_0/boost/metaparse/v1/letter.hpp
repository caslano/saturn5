#ifndef BOOST_METAPARSE_V1_LETTER_HPP
#define BOOST_METAPARSE_V1_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/letter_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

#include <boost/metaparse/v1/util/is_letter.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        accept_when<one_char, util::is_letter<>, error::letter_expected>
        letter;
    }
  }
}

#endif


/* letter.hpp
M9I7E0h0dFloYSzbDs6OKKN9EJBop6wgIBD2Hiln0lCU4/YvH98h7QQJFeqW2Vcze+j/Iy4okAyLCSPWDDa0a6PL+74wYelYTXQjfqqJWaFZA9Bll9yWJx0O+ewk9anjMg2HwuNkvMWSFyJdVsmApmSfDyEccpkTnLe/XxRePTr7ltonGYlO5Hh62T0l9H+EEWH/mPNwXCC25i7o+2Io8i2A4pEj0fBacVxHKPnFRBSAVIk5ulshvmGMEiZkoAlMP6457wLnJhV9ktWSSj4DGf495kvkQF2XrizVRCaj7TOv8H71/ZxGsWaglceAypRKUFWMcq9oBcMAZmRQTMMtpK/ggnvfYqlOK5WoW0FOfhsrLtySIseMSzJldC1bvjIta6ia2R59Dyh7/To4sq1mFggx7cjG3ug0lxfycHqQbVfJ3FszfPtivZ2nW3uOnFiwWcwM16mGrdbnriA9N3BSIei6KmwbxXIGJmqaZYtB/TdLiOuZ6FrBaBjyGrGz/XZKm69ZFN9SOYuhMwYJJZSu5mLSTS6f+tNdNQcsM93lfWhZwPMsqkljTLJerw==
*/