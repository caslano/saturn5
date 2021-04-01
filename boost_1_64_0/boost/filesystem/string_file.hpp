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
UYk3tOokyPVsve5oEpu5eY2Ox7uTyPbBE5o1RzKpMxlio5YGAP3WekB+p3UyVjsTxPpxPuxrfUE/CwOQoJGmj+ywdSDs/Rh4NhRVkJSVwWuGg4Asz80HWpiamWNXZNmXAwVbOqbdGfpMSKsnNnMmDq2FzO1qvNRbGCYi2NXo1kQrOcxMAmamPEKConhoFlfi034iVacWwPENFFXh2QoM9SObq0YNvJkHxJdhiKCQar9UnFqEiWgsEK9REgnbeyq0/6cwAFj9B4jXwOZnXS0r0uOz2AZh5CFXHUtKbv1wbNL1CgEt1i4GTZWfz86zx89nbyGcEKTIdFLf+DfurnbXlH+9zJGrkj5RgozNHOYFaV10rqP2yXjFEziJssbXiqEuTFEaSYsNvDnN0UjPb4GK/UpKV85DChhrnNfqPH0N4c9EK8fXmTOME+mSVQ6Qe18Bc9CdmeZfR+p5Jjrm7qr7wsS0ZVcLfmmV8ZCjFcj6uo7ltHa2YQ7Jg4Qpq3P8njIZ0MLJzFPs6p3PfMbt1GVqOUl1V9Xdjjagi4MHyJqTdw8tO+YLP10pRvK/ow==
*/