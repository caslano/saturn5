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
A2qAL9SEWlAb/KAO1IV69rE3GXvwgTJQFl6D16Gh/Tkmz4FKUNnkOSbPgWomzzF5jslzwBdqQi2oDX5QB+pCPfCH+vCmvQ/QwH5/CIBGEAiNoQk0hWYQBM2hBbSEYGgFraENvAVvQ1toB+2hA3SEdyAEOkFnU3QoFLrCuxAG4RAB3SASoiAaukMPiIGe0MsUXe0D70FfwDY47PUAwNw7bMEg+AAGw4cwBD6CoTAMhsMIGAmjYDSMgbHwMYyD8TDBFBswCSbDFJgK0+ATmA4zYCbMgtkwB2JhLsyD+VAKHsMTeArP4Ed4DgZza4INLHCBNPASpIXvaHMLbsMd+B5+gLtwD+7DA3gIj0yuM7gO0kMGyAiu4Abu+slAJsgMWSArZIPs4Ak5ICd4QS7IDXkgL+RT3+YNBeAVKAiFoDAUUZ9YDIpDCSgJpeBVKA0+UAbKwmvwOpSD8lABKkIlqOxwV8g4VIPq8AbUAF+oCbWgNvhBHagL9cAf6sOb0AAaQgA0gkAD+YYm0BSaQRA0hxbQEoKhFbSGNo7//xryDW3VxreHDtBRbX0IdILO6kNCoSu8C2EQDhHQDSIhCqKhO/SAGI0jekFv6APvQV8D+Yb+BvIN78NAGAQfwGD4EIbAR/Kf3sDnIt8wwpAYZRSMhjEw1hD/Nw7GwwSYCJNgMkxRXzcNPoHpMANmwiyYDXMgFubCPJgPC2AhLILFEAdLYKkh/nkZLIcVsBJWwWpYA2thHXwG69XPboCNsAk2wxb4HLaqf90OX8CXsAN2wi7Yrb57L+yD/XAAEuAgHILDcASOwjFDYpbjcAJOwilIhNNwBs5CEpyD83ABLsIl+BouQzJ8A1fgKlyD6/At3ICb8B3cgttwB76HH+Au3IP78AAewiN4DE/gKTyDH+E5GCb/gA0scIE0dr2HtPAypIP0kMGUeNMV3MAdPCATZIYskBWyQXbwhByQE7wgF+SGPJAX8kF+8IYC8AoUhEJQGIpAUSgGxaEElAQfGzoPZeE1eBP8oT7w54HOzbk5N+f2v9oCnHbLuTk35+bcnJtzc27Ozbk5N+fm3Jybc3Nuzs25OTfn5tycm3Nzbs7NuTk35+bcnJtz+99vPwFQSwECPwAUAAAAAAAQtJBRAAAAAAAAAAAAAAAABAAkAAAAAAAAABAAAAAAAAAAYmluLwoAIAAAAAAAAQAYAA9Y6lf709YBD1jqV/vT1gGO0uBX+9PWAVBLAQI/ABQAAAAAABC0kFEAAAAAAAAAAAAAAAAGACQAAAAAAAAAEAAAACIAAABiaW42NC8KACAAAAAAAAEAGACO0uBX+9PWAY7S4Ff709YBrevUV/vT1gFQSwECPwAUAAAACADAsbxKDsTXy/wMDQAAvCQAFQAkAAAAAAAAACAAAABGAAAAYmluNjQvbGliY3J5cHRvTUQuZGxsCgAgAAAAAAABABgAAMT4tP/X0gENTddX+9PWAa3r1Ff709YBUEsBAj8AFAAAAAgAwLG8SqfGDjeHNh8AADCEABUAJAAAAAAAAAAgAAAAdQ0NAGJpbjY0L2xpYmNyeXB0b01ELnBkYgoAIAAAAAAAAQAYAADE+LT/19IBba7ZV/vT1gENTddX+9PWAVBLAQI/ABQAAAAIAEKxvEpcAv0mgsUMAAACMQAWACQAAAAAAAAAIAAAAC9ELABiaW42NC9saWJjcnlwdG9NRGQuZGxsCgAgAAAAAAABABgAAAZOKP/X0gFtrtlX+9PWAW2u2Vf709YBUEsBAj8AFAAAAAgAQrG8SsgMc4VUWxgAANBwABYAJAAAAAAAAAAgAAAA5Qk5AGJpbjY0L2xpYmNyeXB0b01EZC5wZGIKACA=
*/