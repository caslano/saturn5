//  filesystem/string_file.hpp  --------------------------------------------------------//

//  Copyright Beman Dawes 2015

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

#ifndef BOOST_FILESYSTEM_STRING_FILE_HPP
#define BOOST_FILESYSTEM_STRING_FILE_HPP

#include <string>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>

namespace boost
{
namespace filesystem
{
inline
void save_string_file(const path& p, const std::string& str)
{
  filesystem::ofstream file;
  file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
  file.open(p, std::ios_base::binary);
  file.write(str.c_str(), str.size());
}

inline
void load_string_file(const path& p, std::string& str)
{
  filesystem::ifstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  file.open(p, std::ios_base::binary);
  std::size_t sz = static_cast<std::size_t>(filesystem::file_size(p));
  str.resize(sz, '\0');
  file.read(&str[0], sz);
}
}  // namespace filesystem
}  // namespace boost

#endif  // include guard

/* string_file.hpp
/nTOPnPD9EqRpJyNfL4a35E7iPjo6JAHl0oiaLZqOSBxsaOksxzY0ActB/Y45QHFYve5knNJMPydiewGJM9kHnBXtY0P/bCk+7DhK9yoIOQD0PpT2IKu2XiyMbhJw/+ParIDXgRJULfxECASVHOxfyqTtuES2oaFmoEWLuzq+WJh/zOfdmH+QsL/C5uxQbnreIsw/dgjzdubsj05QJ4LxBL54g14pDVQWXNTc0anZ/1N6Yz0NijLj3Vr0QZl58MhNigIh78BIy+vx+D42X8h+H1oQmOUSg2e3LNatkLJElYo+qUm9PuiSZig3JzrW19pBJVG9idGUCktCjU+MT3cGuOTJ29s0fiEJvSdp8lOj878/s83h9dGBFqEgaklTeE1wMenGD4GadcCwGHKnPkdNJ4qq6Q1wPDxDc2hqOOygOQf5Obl4ISiXjhqQFFCl6iaFn70kF6XmCP/Zc+cxeDiLsJP7gyHPF+Q3j0dcrWj1x7L6njGN0bE2HvVCs15ledoxT4EHjAEyfe/TZaYOxX5ZS18PBr37VSSXwI1GcdTCxFP7QLYmtwIT4GH6YabCU/lM9hwaLCFaKoKYYtRhp47UOYBrSeI1kOQ0WRERsZWoA0vjk2ER170oNVEMHeDioyeftAg9fQ8KKJ9NMJFOlQUzNAI0iYklbiKPZ8iLFT9DIJg1TPN+nXsVVqEwZNTWsRDgwAWXfLcJSoyWjul
*/