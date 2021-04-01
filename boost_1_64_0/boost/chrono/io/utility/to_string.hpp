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
TcdBahr1021t/v/ZZ61sNOLiL1m0SjVj1wCSs5EWED2r4vc9lFcLa4VMklbvtf6pnFSMJDlwJiijo3gXhfuRH2s7LBA/OvERtZ53yjeNXZWskOFfMpM1e9/H2GFmqLqIvmzgBe8D1OpR2y8+w3OnAOPsrxERPdJ6YbYen8sVYU+kj9o3VTgS6MVeXNtWRJxOjPqvjsnroYGp1yS2TymnI/bEekWHo20e9bl1/TNMGmqGxSdh2CkI2YWevW9ucbUGlGacXmgR6Zql9amSdGJzPmrcQmY8b8j0aR8t6DjQtImrw92/W0stMCwX8abxlhJjE0Cht9t09paUqin+3q0qYwUt473zCjKLMHMeaO6RE/XzmjiTF04uW446tAt3DzCPlPtqCa6XH+jzBKhYGEdtPPdOTbEY4ebGWmN4uMuD84j/YCOqeQLdDjRF8zhTaSD4N6HqVJRbuQ6OcNpANN8HXpGh4exopAGab101qwlg/YDdUHcKcui1DkrMjzse85Lura+w0s0nCdhTqH/FmFJ2KHb2/LfNe/sGLre2rXkq+FwENrv663KOeuHKSg==
*/