//  boost/filesystem/detail/macro_value.hpp  -------------------------------------------//

//  (C) Copyright John Maddock 2001 - 2003
//  (C) Copyright Jens Maurer 2001
//  (C) Copyright Peter Dimov 2001
//  (C) Copyright Darin Adler 2001
//  (C) Copyright Beman Dawes 2002

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

//--------------------------------------------------------------------------------------//

#ifndef BOOST_FILESYSTEM_MACRO_VALUE_HPP
#define BOOST_FILESYSTEM_MACRO_VALUE_HPP

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <cstdlib>

namespace boost
{
  namespace detail
  {
    inline const char* macro_value(const char* name, const char* value)
    {
      static const char* no_value = "[no value]";
      static const char* not_defined = "[not defined]";

      BOOST_ASSERT_MSG(name, "name argument must not be a null pointer");
      BOOST_ASSERT_MSG(value, "value argument must not be a null pointer");

      return strcmp(name, value + 1)
        ? ((*value && *(value+1)) ? (value+1) : no_value)
        : not_defined; // name == value+1 so the macro is not defined
    }
  }  // detail
}  // boost

#define BOOST_MACRO_VALUE(X) boost::detail::macro_value(#X, BOOST_STRINGIZE(=X))

#endif  // BOOST_FILESYSTEM_MACRO_VALUE_HPP

/* macro_value.hpp
nxU9z/tH+wq7diXHQmgofA4tz9/CS/om+o9/zq4SdpWJ8sHArIdqOneD6BDejDM608qzPr4gHQscjEd5W/O+kiJBt8pK5YrMzaLjSUod1B4rjJLl+4TExvyle4xSy0fKu7LE6P0FOsnaKR5n7SYMqaWdHv7j1wLYtY3AW5UZlRY1URWDJLi5nl1HCuCdDuMpG1u4dAcUd4E0WUuPNmIuCC598ivg6si0RGoEu95I0l8S/bRFG6kv4HOFbVe7iJPF1dSDHugKXsqXFhovoAlKfBidxTv98k4d5i4KFC0sQnKInVxa9hblMvksseMX2sRjfs/i6rM8RYRQgMAzSlYUkrjuOcpBYDeQNcebFr/i5I0csDAXHg75xiu0lBP85GjKDhz7/cuLDdZUY7WLAeuVOhN+htYG0VPE9TTYJJTns1EK8JamuyQQixa1coH2J8Fk+o3vIxyEMvcbS8Y49bR6/KQCl6AGiZgspPPyO18ZX/8YAzlRrgZNftMbVsLm+WNJO26GsCYc35M9Px4tCZ8ZbTfeMDfvgVsZQq+FVKD/gRCDQOY//hCJq+OlDA==
*/