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
4R+lwqQ+ft+BTiY3FHU4jU5Oo7e4QG9rwe3j2gpH8cVfTCWL0pafYDr8ZcTaIm/eQHfZu1zNMYx5jiHzQTKoYiNSjQg6w5VNhfECltfT2Xw5XrI/SRVnZSLgA2kMqbf9yLzwWOP6U0O6tANHW9SQYW60jOgDRqjE3uSZLKacg6M4T2zvB6/1YrQ8X4znq/FsyuYc4edQaKkcJQbWAhalusPgej7MD3IGA7R86lRBrPik/LHC3KNPhZHaC8ECNViVv5XCuijk0E5mGYKAiahEDQZXWDU+E/aCQ5bZUiSsK+5Fgxtl6eeLmhBwkSzrhao+NLlqDKiKYwlk2SPc80wmrPbnu2fofFcBhs3DaKwtZMFCyEIn2mGqYrE8OCKS6tZGcGUFu0nHjYA1Lwqhku5J7yadexD9e80B3dq9Xg0YcYWSjjPBDaM1oZw0YQt4iuHAkktsMKCtLjVCrHmWBYURYxfS+vblmx65wClNgd9y9GDziPFxDi1BRKZXk0kwwlP6xsjY5y0ibQvB74iKHFA+7iGu2LmMSOWDt7wOgDcLybhFS6W9g+4Recdyfkc+hEKKNfqkSvSNQinTloQUm66llo0GJiLlZeb2jJQtzGKmU0dOpUFIiLw02J7YymecD6YPLbRSMxGEvaXm1KQm
*/