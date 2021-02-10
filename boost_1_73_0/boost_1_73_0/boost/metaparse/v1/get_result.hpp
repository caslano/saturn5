#ifndef BOOST_METAPARSE_V1_GET_RESULT_HPP
#define BOOST_METAPARSE_V1_GET_RESULT_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_result.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_result_impl;

      template <class T>
      struct get_result :
        get_result_impl<typename T::type::tag>::template apply<typename T::type>
      {};
    }
  }
}

#endif


/* get_result.hpp
27qj61w66Sl5dB3BzXgMyS/2UzqMId3iFYzvYK53dBGNIZrEk7uYIM+/U+bpYuithnYoeCG/kD1q5VC58BXVxpUxTE4naddi37B3vHRNzVihNTn0HgQ/eCKrj3XV473VbCgI4EWmrHSuJfixFEo2FNRa5Wgg0yqvXKUVbG2lNtBjP4ZYrkAT3BAlHBODzw7CUA3XIFUOMsvQWnDSbNDBevkKeWUwc3UfqpchF/QvO+/CM9/325jz0SxZpS+LeNTHuUiW6Wk097iXTVvjdaabwbmnEFQ2pOvJvmPg0c3tbe/RjxYOAOI4tdL2EBAF94amKjroEwVZOArElTiMCEpp4RNRwYUttbtgYjdgiYConc50PWXPTyl4yeOLCNhMWxfDf84CtqYBhA8bko4h25qaj96elquXZB6wB8qxpeNLfhmwgCyeJQQ/6fLzK/8HUEsDBAoAAAAIAC1nSlL/ipZs6wEAAFUDAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTI1NlVUBQABtkgkYIVTTWvjMBC9C/wfhi65lDpKSnehRg2EbmlK2zgkTtk9FdUex6a2ZCQljf/9jq187GFhL7Zn9ObNmzeycGhdKi1OmChVrun1ie2XNpmdsFmSLPoHNEbvWzaP
*/