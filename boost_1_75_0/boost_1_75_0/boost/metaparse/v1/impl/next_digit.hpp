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
W2LHbHyxTAVUEiaj5bzmx/WXtj8Xw+LbpUez+srgX1ByyJMyHG3kzu3bq7AQr6D7/lwuBcLFBN1yGfeU5R1Ku87pkf3YTOXzA77ATThF6AxDmoqr7DG9lJfMG7DkTPBTbf/8JvSY5Buw2RLcWhNciYsW3ovtO0b+5cfuRXTzOIjdXmnA2oIeHCY7bge9KLOKeo+7XyaIDWFlDL6PE9Mz9KHq0b7VYEN2es77hxh8CxtCBiQBQcIwc56ZemT8ZGURgfTtpMGQfq+adEybH4RxeO2HbMDKjT+nKVy1wxd2R6g6P/2t+lTLlgqRhfLqQaNlCIfWL7jPkzQ3FbTKK1Lkq0OPhA0Fudhl2sT7Yy4beYj1+NNdxe3gu2K7U1kGJ9nFfhccHsCeFQlRMAkhFbo5Cf6Nf/B63IrdIB5lZKWY6Qj8/HhxQ/q0/PHiwmRwFNU4zt8bQnU6txh8d+tZ5Unyi7Hwlia0yt3zRjxXmFeN+0SHx/jslSZVqHe1J03zA2xiocd4Wh5b5j7rBWM9h+SU7C7z42Likce48yoXkVWyRZ+T4Xp+3GPcraN4W4mije2CnMjqaYPWXL7T1gGkwP/CcS+HgHSDaOTuXbzyyA6PuxUsPSO7W9gxty1HgVjGcdd3Ny7Pe4z7P4awBNBk3iaYy1Mc3Q6s86ZZDCCLnbPYyV3wC8r7snNPCtbx/MoWeqdze5Gv8/ggfmA7bti8
*/