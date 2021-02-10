#ifndef BOOST_METAPARSE_V1_GET_REMAINING_HPP
#define BOOST_METAPARSE_V1_GET_REMAINING_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_remaining.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_remaining_impl;

      template <class T>
      struct get_remaining : get_remaining_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_remaining.hpp
/ivKvS0CmF86Sdtgd+BkeWHrirFcKVLoNIT8rImkPlRlh3dS074ggLtkwQprG4IPZShFTUbtZIYaUiWz0pZKwsGUcg++33tyC4qwmvhgsAveW5rKfgxCZiDSFI0BK/QeLew2r2ALrQ77AgZb3UWkg7Y5Li7Gf8OTqJsKJ6mqe11uHFJZE7ETHHBuVI2fBWqc/HWAz+6+zgeZcEaOV9E2eY6DcRdMHG2STqlLF0YjuuNCHeYo7EEjRT2ovHYId/aOPH1DXeYtdGaDyC15ZQvs04NCGHhHlDAyhbLEf+yxRECcVqWqWrCnxwT+v8fwIXlspYwN4J9Qj+0oO3+5J2kBpAdd8fHb42b7HK09tqQUGmrf8BuPxd1KPn0+EtMu1ABeEBt/WZVH9JhHC14Fhvyiml9/nz9QSwMECgAAAAgALWdKUqAoW+e/AQAA8QIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjU1VVQFAAG2SCRgbVJNT+MwEL1byn8YseoFEdygciAylRCLKFq2qdoUsSdkkkkTkdiR7Xabf7+TuB+H5RJ77DfvvbyxcGhdJi1OmahUoWn5wu6vNrmdslmaLoYPtEbvOzZPPhbL5P0PU9ofCH4GC+772Q9YodmhCW2VIxMG
*/