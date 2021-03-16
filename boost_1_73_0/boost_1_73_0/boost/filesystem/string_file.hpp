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
pKrgqQaF7NbDC88qB6SjhYQ1QmrYJSw+ONFG5f7PQqk4xbiDFvkzsZbh20VnHDsbjXxDJulAf0c18m9Chqu+2HHFu73ELDZwyjK484XWtokKfV2l6AwOZqPpY0Le29XchnxwJcTpQ97Ih02B0JKxI8jR/JFOfmaJmZISKD73XfQRqId5wvAm995chTRKrYVh4ASWjOL6YL7i2ZCk5xVF3ArpCA2vP+2NKdzmwTgu4PSFXplPCsBLd4DTYWPMQis=
*/