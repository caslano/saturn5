#ifndef BOOST_METAPARSE_V1_IMPL_NEXT_DIGIT_HPP
#define BOOST_METAPARSE_V1_IMPL_NEXT_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct next_digit
        {
          typedef next_digit type;

          template <class PartialResult, class NextDigit>
          struct apply :
            boost::mpl::int_<
              PartialResult::type::value * 10 + NextDigit::type::value
            >
          {};
        };
      }
    }
  }
}

#endif


/* next_digit.hpp
O+XvO7v4prZf0JeFnT17zsyZgVCj0mmiMGJhKXJJjy22n7LJVMRmcby0C7y+xCzkl5OQd2B2w8IG66qlUJboBIRMC0y3Y7dF5XYM3L/zYTgYwOKbw6aJxgDiPfZh8Ahv8kAn/gD8UTB6DAjz+iN22BqbAzYBmNw8ZTc8T7bosIkUGoX2vqPY6CKABxsSmOpSigDSSqorVNzWaFh+aV7oXXU5mJaqlqrsLuVlhSLZ4dgs/v3D1ydIi6RRqMf5Xoj2CWRtkGOlm0RsiN9h/vB+9IVcMDUbN44ekB03MKlKo6HKDFmY2g1BujIiVmhd04XTNjSi0dlk8CTkJgSJyOAf6fbBm4LSmdxrYukuh6nc7Qz+mKcrpEfn9V736a0UabXP0O2kA857s8U6ni+DnhFdLlYxN0Ub5UpuOF00hnShKXikcqQnIcpC2/5GrMamgt56NZnOV7wqP0yvuJBkdqm0uqsry2ZpzMvJW6K7IiHuoz/WuXdsyrwFO0hJrrEBXaCdAigSBR+IAlxVSO2y8GCxJqdGapnKKmLGv07xNHYOm5FYAH+V7LCf1AHveUPiNDb7puK995fVer54c9hzmmJN4Vt+a3pNGZ8lWGjNATsv7h9+kcWnubChE3x4Be9ad0T/r19HV//Q1M/PfeKX
*/