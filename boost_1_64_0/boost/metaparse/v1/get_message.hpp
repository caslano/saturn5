#ifndef BOOST_METAPARSE_V1_GET_MESSAGE_HPP
#define BOOST_METAPARSE_V1_GET_MESSAGE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_message.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_message_impl;

      template <class T>
      struct get_message : get_message_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_message.hpp
V6Abiq6n/F4hX1k2+LYnSs4d0y6Kh1G8pCE2EyWwHY/zRRbzQci3UEK3qEhASsdYZEgEdTdMyLZSGndx7urq3hehsSuwrHx9E9OLzg76o+oxBzSJl1Op3kX/xulnBQeUNgmqKYItlc/M6uE+7Xf+ZyzB3AL3+o/Amj6sn2UYpcXl2w/19aV4lY1wZbCWFgpwz9e7YqADY9691phNwLlRXAp16eq/OVj9UKDlt+mAGWSvVLg2glytdsbCeetZHfD81T5/B2kBPOmx8Y+Xj6/6SePFzCE153xeQlnXRBPiCs5b0sQjkS1vI98YDjdMSm5ebvkrMc+FPsu6EHoLKvvfhV06chgr0PrDlinOvyiU+q34qxPtBEliUQ1+UEPG3t7t7BzurPEfeOW7evcE8+MPkm37E1ALsBQ6DWIpbSBcvN0PYRqi6tQu+XENfLjJqOvXh83F8loWiWF4aWdzhI+gujKRplnQLZ9aytuPy5PJy/mNneaDvuQOHM03I1eTvrK01Bc6XEV5o+mUJwo13KVNgSXQU+U6E+3+7DKa8m2i5hTbribY6FIwe5kIJg==
*/