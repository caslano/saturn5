#ifndef BOOST_METAPARSE_V1_UTIL_UNLESS_ERROR_HPP
#define BOOST_METAPARSE_V1_UTIL_UNLESS_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class T, class NotErrorCase>
      struct unless_error :
        boost::mpl::eval_if<typename is_error<T>::type, T, NotErrorCase>
      {};
    }
  }
}

#endif


/* unless_error.hpp
b1hZ7W52v022dUVcOrIPemPDOicQhzYZ4lee5y04dNzasV7Ukt5nCmkFPgDF1PuXE7iUS0gLYusZYj4PGcwlFn/C+4zMp7BcFaWCDYiUEb5vAWILIqwU1R1TCjT3sRIvaDuvdI2riCJ2Wew9BcsVOuEPxqwcqqpJCR5+2Ozg786q3ZGXnk+RyLzbtsHi8fA4eec16rMokzYefDJPyTEFnSILu64z5JgtpVV58UfqqVZujwp8jkRBboqEXIlM4ORWnYbuZAOj1y3WZk3D9FRmNgA2Lhk46okOBfuHyPAjL4547CpSf93AeEWwPJiC0urYKaD2L5FMTVxpJ9jLM/2ji5MuW8ie6CTLCh1DN8kClM3sy6+hVajjgsbshxSu/Le29O0RivPn6fKakVny07XoKPdTQ3opIZpwXgGyRclFgLRIbnTTtnalPRn+Nsu0NOywi1PA43MxeWq1mWQLUEnDR9obRBKri83LodsflRT+q4Ffu2HhlpEmH4jyCmYJlJwjewdi4SZys6qrF1VXUtDZM9tOjl5nbl5/7EsOxRpGapwW9M0MDDskQBDFew==
*/