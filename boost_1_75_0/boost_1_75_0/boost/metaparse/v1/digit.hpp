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
zuUYb0E9Mon9n8L+T2dacBY7JrP/mUY9MnP+lKzQlBx3aMqE0JQ8Jnpmgj89NJIpfrbtl4K0OzKfXWRK9JRCd2g5NYBeDkrj/OXU5m459Zdbjv3llm9CDd1203NWNLGEbSuexfHAsOHCP+eRYcN2M5TvBHd7JCljr4Se2lmg3YEHuUTx53JT6ZhkxbH4EDh1A70Ux+PsL/u6hrk7TOyLGeKObihpfKCTW4rfSBI6tEb3hM6PdN4yMsssHfGEhqg6e7cjJNX6SaoV2jmY+6AkN3dh3DOd4tBy9HFogKHl0X01xmkdIGEh3V3VmEJINobmw5BXXi1q3H9OgYK+avmuWyhvp6OIMqx1S0XVuijDwGGLLspQH+23Zk90lOEZa5jHjDLcj1bnvf6rKBYP4vqgbtYXwjKJCRaQU7bZ26vMvi5phH1dO5Oz1+eB1u5gmcVV8mngx5Kd/u7cOTTpMCcHmgPdI+2uh4ZCnCIMOmwx5oPq+2Vp1rc15sg5sc5jPGE1N1RiNrQ+dPDD27Uly9I3tMZyOjvk3X4iIocfUPtsNbOGxee2dA1fv+kMa/hOQ3NruK/2/+IaPtVwpjW8v+F/uIa/559+DTveR2vYu9AY10vB48ZV/LCLcRWbWcIDebSEZzW3hL/80twStqv57yxhPV9Cr34J5S0W4sm7/vQifvFLzEVsrS3iu7/8Dxfx8lub0E5deSK2it57ePz/
*/