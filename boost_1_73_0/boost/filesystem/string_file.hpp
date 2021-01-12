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
sw+JWZrEy27e8ekaveMrY1E3M+TZXePHgPZMhG/Fj5DIXOY59E8SeF8SIli9wxW6NIorAyJzidqdE7V79sA928UMa1Y2Uz9X3EhZiviPDft5ZTJH/0Yymei3nptS9CFB5AGwD7zW7cdsj5PJ2ELo/61nEy2HH4q7GwK38IwhTgHrecOcExoyQwPJfnULz/Evj3kqn3tT7ndwXiUGgs4BfnIb60d8vm6u+ZpFt9ytF1yMLK0N
*/