#ifndef BOOST_METAPARSE_V1_GET_LINE_HPP
#define BOOST_METAPARSE_V1_GET_LINE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_line.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_line_impl;

      template <class T>
      struct get_line : get_line_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_line.hpp
V+Gr8FX4KnwVvgpf/8rrP/r8P89s7/tveP5f2Jfb/KDvv9Y8LjD3OsgtLnQI+nLz5L++g/sWyb83K6XEHvt9v6Zc3k8CzfPuezqsyL5RP2qzTIfhcErScNlg+Nf6DCwu13dgdt49a/cYnusN89jgvng/e8H9jpmmYXjzt7t3f5h/D+Kg7NSLhvXtq9LRvZLJffIl2mNx0Fddg7z2YNAerWZF7dG394CMRHvs8/vaI2N2wfr3
*/