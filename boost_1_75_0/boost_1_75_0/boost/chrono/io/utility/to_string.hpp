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
G/+tFf7SCD3nzxLOyZL9Na5+hyvfmEGNHQlB6DnXFdHRkYsf/Ps3wD11eP57s87R9HO9OCaB89zLcfEDnec4vkPWYTOwWLPJoyoC7jpnH3A0IblGx4GfXEh0bTdzA8uf/BUYEevRowadkFYRRKSKp46B6UZWG7yaGpbxr1EHRpfhx+FrwpIiR9AGfY7psf1mXaqn/5Inzbpdpqnkhz6RJ73u//p+7Clp5C+On2zGwFMJcXPaOJPJ7hFJ41CR3aZDCj/+EnSppWgt/R/UPJtA3L3hULSKwGZVEUTcxd2qHRR3bCV1DyZ1J8TNa+PsksKPugTVzOb4cZFQTaZofZ5WM51kbEkycvnj6H8mLt7UmHywLBpBKtwYA6w/P8ZANmYM7EQ9cKfwyZfIYI+VmXV41hCT4k6ITHFnRae4yWummfyFE8EkK0JIeOkaGaeQwje1iUUprl1k/ezRBO3OEiyzPAcgWbmdNJF9wJJND5Q7/E4qBTavS1V7nANls43dzbnnRMLCubbjwp0g2bccwoUrPKReOMKN4sJ9dEi1cPGDR5KqHRPIiEdgGxcchBkdZRZbkakPL4jQUY77u7sAas/DWcr/OPfgTpCVD+OwhOz6kgy+KfkiWhccMejcg8+Vmuk1VzyDp9aEj2rvuwpLPrgm7t0bWxhvKia5La8UbldkBAziKcFzZIorEngUvsMxktHOV6eC8r8S7x4vBrmX
*/