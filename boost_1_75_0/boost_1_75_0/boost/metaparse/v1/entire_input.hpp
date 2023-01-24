#ifndef BOOST_METAPARSE_V1_ENTIRE_INPUT_HPP
#define BOOST_METAPARSE_V1_ENTIRE_INPUT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/first_of.hpp>
#include <boost/metaparse/v1/empty.hpp>
#include <boost/metaparse/v1/change_error_message.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Msg = error::end_of_input_expected>
      struct entire_input :
        first_of<P, change_error_message<empty<void>, Msg> >
      {};

      template <class P>
      struct entire_input<P, error::end_of_input_expected> :
        first_of<P, empty<void> >
      {};
    }
  }
}

#endif


/* entire_input.hpp
UIQFiP0i5CoN/spSg6/c4MPeYDJpSJ8CazoBXP85nBgzRvDEVthABvqKnk/M//uWB8tlGfLumyTiC2bNIJ31nYVHTmapC2BgwAWo/9xA4MVobIo20bnGv79F19dTXwMFZWUQlz5rpwbX+CD5CcqceaVAnjcUKPNKd+a7meAZdiYQQ/X0OOYOFVXq+Sk1TF0tPxegjFmZROn17gsmVXvD0xKg0g8KzVJgNZZe2MbNnEMZeALTueRsL+5KVs86k1ttFFa1DUKtso15kQ5+EwZbJfC8yPUiaPJ7xBGI56nW6jh8hWQ0QP0PYT7QNgwngpefNkGIieLvxLG+HKxo8ZE4T7AnhJ5AvH8FxBUXVXpCraB8EHurq9oTcpmaaTJmrFpDpRt2KI6CbywxYqYwVOjy62kRcUcFPynQ11WA3jawihA0taTOwoOmBt1CgXQZ/DjmNl1t2QR3KF+tL0txHsFNxBJ80iGnxBbjuL0EROlgHkwUQm4x+DZUwKA5oVa+uB0oIP42yOjrv2T/zD0JcUeBRCDvWNks1CryDefsg+RAhlsaM8EZntBK2iWvvw4+ZkweQ4wAFSzq0+CtE0zyq/A7eGue6QOKXDpfKq9/BIfsAEP2wtPTnIO+DrC1LocXdLfSC3ZPcw3aErgBTtnjGC2LBE+ODnjdc2cmnGCPBIYFZyadCiR56aELmJhQP5XtYnb2pHq2E3uufgydfVo9
*/