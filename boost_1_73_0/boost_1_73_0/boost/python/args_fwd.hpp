// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef ARGS_FWD_DWA2002927_HPP
# define ARGS_FWD_DWA2002927_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/handle.hpp>
# include <boost/config.hpp>
# include <cstddef>
# include <utility>

namespace boost { namespace python { 

namespace detail
{
  struct keyword
  {
      keyword(char const* name_=0)
       : name(name_)
      {}
      
      char const* name;
      handle<> default_value;
  };
  
  template <std::size_t nkeywords = 0> struct keywords;
  
  typedef std::pair<keyword const*, keyword const*> keyword_range;
  
  template <>
  struct keywords<0>
  {
      BOOST_STATIC_CONSTANT(std::size_t, size = 0);
      static keyword_range range() { return keyword_range(); }
  };

  namespace error
  {
    template <int keywords, int function_args>
    struct more_keywords_than_function_arguments
    {
        typedef char too_many_keywords[keywords > function_args ? -1 : 1];
    };
  }
}

}} // namespace boost::python

#endif // ARGS_FWD_DWA2002927_HPP

/* args_fwd.hpp
AAAAAAEAAAAAAPD4RwBjdXJsLW1hc3Rlci90ZXN0cy91bml0L3VuaXQxMzk1LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSNwHFjJwEAADWDAAAIQAJAAAAAAABAAAAAABW/UcAY3VybC1tYXN0ZXIvdGVzdHMvdW5pdC91bml0MTM5Ni5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUqHSEQraAwAAJwwAACEACQAAAAAAAQAAAAAAOgJIAGN1cmwtbWFzdGVyL3Rlc3RzL3VuaXQvdW5pdDEzOTcuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJcLaUN0AMAAHAMAAAhAAkAAAAAAAEAAAAAAFwGSABjdXJsLW1hc3Rlci90ZXN0cy91bml0L3VuaXQxMzk4LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSh/aCJmsFAABjEAAAIQAJAAAAAAABAAAAAAB0CkgAY3VybC1tYXN0ZXIvdGVzdHMvdW5pdC91bml0MTM5OS5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUvNSZ4XeAwAA8AkAACEACQAAAAAAAQAAAAAAJxBIAGN1cmwtbWFzdGVyL3Rlc3RzL3VuaXQvdW5pdDE2MDAuY1VUBQAB
*/