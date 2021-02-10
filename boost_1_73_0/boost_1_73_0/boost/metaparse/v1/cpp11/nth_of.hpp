#ifndef BOOST_METAPARSE_V1_CPP11_NTH_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_NTH_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class K, class... Ps>
      struct nth_of : nth_of_c<K::type::value, Ps...> {};
    }
  }
}

#endif


/* nth_of.hpp
AbZIJGDtXU1z3DgOvfev6Kq57saiqA9qy5XL/oOpvXXl4Jp0Zl2TsVO2M1v590sKpAQCj5I63U7iiXNIYpL6IIH3AAKgfP10fHz67ebx+HZ3fXv34d7/88fxy//uH94/vt19vrt9Cv27x08fb77srq/mrusrGr37ZffL/t8fb493T/98vH1/3F3/Nv7gRzweH/46Przd3d3f+ear9OP1h+PN0+eHI7//9dXcuL++u/nTv874zH0Ysg9jHn3HFfVcX6Vn7K79LW8/fAlPe3p//9k3/Xp8/Pzx6V+7/finemMqYw/23S79VNlD/W7qHdqGOv1/m+Zg3u38f2xzqKjNDW1o2+/TeOfaQzNf7vo23Ts22G7uZ811d+jzZt9oukPHG6s3fd8fWnl57Or6w6C7fEfbH5x+ZG+cfCTrrNzBVPhB3eDwg7p20A+KXc2Aromddig8bBpRVQdTl0eEMe3gx9jSGN/vfL+Ra9w2Jl9j1mVN+Z3b2sB3rt40fV1ahaar9R19s1fAPilgk+ufHezB5jpgvUq2XKesV8xGjLGN1pPqTe3VValZ7VVWLYFv7tXYqcsrMdSA2qtxYe61gdekbuMVW0pHjPD6XdIB3+uVvKxDvt9r+9L9CftuQYNGCnAb1HDxHmmYx4OBQOaD
*/