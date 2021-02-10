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
N1zDv02CylIHfcG1h8sRD0pT1xWmHBkzKaeL5Sa/W2XTQLVarnM5m4VV4y/5tGW5rymE6dWn9Jvjbd+UXzs8ZiaOTn/h/YRJkqSTvwPv8KTPf740YWjPI9qmOkBoHRQVowWuEcIBgrpw8IRo4MLVxBdC7Qasp+gtMWlq58KfIThJeNsMHIcaiQU5zuCVk0g8+AHE189elp/q1rZy+ni73twtf0biWmvsffpSXkYiel0w+PvYEkqe/Sl5Mi3Pt+oPUEsDBAoAAAAIAC1nSlKyaZgj/gEAALQEAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTIzMlVUBQABtkgkYMVUXW+bQBB8P4n/sIrll6hw4Eptg65UVhTVUaLaskneL7AYWmARd9jxv88dBNuVorZqHyoh0H7c3OzsCKFR6UQqjJgo6owiNoE4LxTYPJivhISaA1A2ZILZ++AdVJQWWYEpaIJOoWlaxPEKmpaeDx4TP/CwpzZVEbPp/gVfb2J2amIpafNAixXtZMkEP50RfCDCJobLBtsdtq4qUmSixaY8mIZUajlg88ALYOb7sLxj11RrrLV7j/VW5yF8sJkaE11QHUJSkkLG3IzINVcMEANU8Husj29iJUTlCBZY4q8Ee+bXZWER
*/