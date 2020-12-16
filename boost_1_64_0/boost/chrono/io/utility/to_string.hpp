//  boost/chrono/utility/to_string.hpp
//
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_UTILITY_TO_STRING_HPP
#define BOOST_CHRONO_UTILITY_TO_STRING_HPP

#include <boost/chrono/config.hpp>
#include <string>
#include <sstream>

namespace boost
{
  namespace chrono
  {
    template <typename CharT, typename T>
    std::basic_string<CharT> to_basic_string(T const&v) {
      std::basic_stringstream<CharT> sstr;
      sstr << v;
      return sstr.str();
    }

    template <typename T>
    std::string to_string(T const&v) {
      return to_basic_string<char>(v);
    }
#ifndef BOOST_NO_STD_WSTRING
    template <typename T>
    std::wstring to_wstring(T const&v) {
      return to_basic_string<wchar_t>(v);
    }
#endif
#if BOOST_CHRONO_HAS_UNICODE_SUPPORT
    template <typename T>
    std::basic_string<char16_t> to_u16string(T const&v) {
      return to_basic_string<char16_t>(v);
    }
    template <typename T>
    std::basic_string<char32_t> to_u32string(T const&v) {
      return to_basic_string<char32_t>(v);
    }
#endif
  } // chrono

} // boost

#endif  // header

/* to_string.hpp
vUXsKa5xRkh1dYPhcvS7/b1iH+eaaLj0/YfjfItT4u+vcHlxJPyhjHuoBpa6w/hYd6IMi+6S73n6PdnPb5z2y3Ra+reWi78xBt7wjUTO8zlfzr8mNEJNUvNRekVISbuQTCNajiPFcrwAR5tZ3p/t52xtO6e8Dum28akUavN4vkvHmvYb+S6J8fAxpv0ajPdP1fGn+MXf2RZ/Sekl+dl6X5b3xF+k6zOku8Ixz+mNY7xfHElws6zHh44FT1HEMp27xO+5IfXUS843ndl8D1SquaRvuypG/2NX8Yvds8Tv7JC+iHkCTBryphxcpqY4v3QOV31D2qhYvkfeK+Gz0bPUFmnC3km4LfuZ75ISxwBsS9AEocMlba0SpH8Ia24uzC4utfUP6X6sjHzP9Scy3eFSPsfgNwqtRxd1Nspwm+or6Z+P9F832jw+zahvjGY98Na5afDZT/URf163ZqE9sE6iwm6ZSc6G6gJnfXUTcvRN51CVhG+ZnJClSoVGoj0aJW1KIwnzbihGC3F9PaC6rW9J62J3Rpb9OTlV8iJcfw9MEfsah1OF83uA6WCfR1uJB70ybs9+NrGsMx1GydqPIXeoMHzL7Hc25HdJoVxrmCUN2e78jMxsZUnDQk99UdHUH94nYV6CriFEt8WLx3H+iOlHp6m7bpt/L8eTUAaRphZS2tGlEq/b5Ut3TnFGpiRc16X+cq5B6HfsgNrA7wy5lokh6+C6TTVVTiMf2oTtjjEhhrXPUF9HPNNdLucrdU01eqhezjy10bnDUSW9OjyLwpIPYyXvHdxDD/odsY9T9eGjHdz1vAxxLwoUN+trjq6v7PNie8fnHFu8aL6jFHjaGzVH9aCbN87L4dLAstdqdrlb+fYA/ZVc7zzXGFxvB8cQ9aJzjcOvzkhZmLqCleI33eVLY7Ytjcts91SOL295z6yQ8JmukTiXyznNeaEL36u2+6QHw/MakVS26ZL2W6Scy3AXRtHNG249vkAHOUy97JYmHk34N+bYgnPZ8fAJ5lxDPGMs+2GlIV5rmQ303KP6Pm4g9rNQWqODv+OBg0dyzVXTrsNloayHQccUJeMIsUxTBdL0NdLkvOIpJKieyz/ewM+uWM9YBOPIb4ExHsThCo0IvXJIeNfwzojK6ary3hov8UDLJPeAOyTBMVplO5TjYtT9PnLs1NqlaNYda5uh9+aTc7Sp1X1nvZa4lp4yMkvnyvjwjp5SUtWW0/kSd0zQMnkezBI/IWq4adfX2RbXebG6Be6vOKJQCFHVXm+LUHtaK1t68j0i4ooTLqczSvLdETjfn4M9VdJwS8g45Ptq5Pt65vtzZyjfTbcxco40Wzq7J3rr/RXvmPnZiNlaXZ52lXiSAucprydR/PSRc43CO3Mj6f84dfOxadgvsrWGubcbOPfW/MY+JM+FKPO7O2kg35mPBHn3PhHk3VsZgd+96xuBv72jDO83mfXdsjHeA7UuPq+Qbq3FjXHQrbN2k/c2cUvSbnzX4js+2lK48f3EN/+U7jk292XaPZvu9m/d8g5KfuY+R13I3vBfMd77bYC6VP23Afxy7Jdzzz8Q+y2OVQ5Hdd8GDJelvylCJpj2JY5cR4Pqvg0Y7iL9TfGj2K9w5DvCq/s2YLhz9TfFV2Jf6bjUEco+P31vWr4BGI7vrwdsc6/mZpRY5miMkPSP1GGT/MJ+ooJ/PyT7+T2iqnw/6Htwp/gbqsOm+IU9oap8B+j3rL+Jvzsc441zDf2O7hdeBXtH53P5ffF7qyPN6I69nI6qtnwmp0yUOSQYuRmgytHubkYq3lUNsB4q3if4rvqphL1B1uQeLO8ErJa+sdaA767R/G4x5BzlxgLDqZ8pr0q+97U=
*/