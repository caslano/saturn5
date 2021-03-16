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
pn2orp/zzYSTgl8vX7lh5gVH7z3i+ss07bg+uP7M4GFbQ+XlO6b1PfXsxWP8x4qNquv3L1g2f2+/G+669N5h775495qnNe0qdb2s7K7gR6/tP7rhrYtHN9w5+jkcBY/ri48/Wf/9yJv/67uuTde+vOqLBk077DBcr9t0b+07Pz4Q+Ot9t64beP/4O0ST6vrmVze+sf/YmRc/Mz398rPlO27QtGvU9avu+fddH+4sK1uxs3FpbPXdezVti7q+bOg=
*/