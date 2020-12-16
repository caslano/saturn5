//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ITERATOR_TRAITS_HPP
#define BOOST_COMPUTE_DETAIL_ITERATOR_TRAITS_HPP

#include <iterator>

#include <boost/compute/detail/is_contiguous_iterator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator>
struct iterator_traits : public std::iterator_traits<Iterator>
{
    static const bool is_contiguous = is_contiguous_iterator<Iterator>::value;
    static const bool is_on_device = is_device_iterator<Iterator>::value;
    static const bool is_on_host = !is_on_device;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_TRAITS_HPP

/* iterator_traits.hpp
9qgyYeUj2qXCiNRH9UeNOWtNa5gqEb+0j5ru+Zh7KDNm+ePaoESf2CesBfK0OXqNv8lackOWJnNWPqnfK/k+u7LGjJVPiY86M1Y+bb3QJGibK/ZpMGf5M9o/14lgR1llSOSz4iZDgylrn9MuTeasdcRCneDz1knJ3+vKHG0qLzcW7vIc1wvaUqaV/eeaT2VUGXu+8wXzpCwre8xZeoW1SOwFnq/KOqMDsSkjr9SH81V1Vhyfc6BvZZ6s44ZyQvJV5o7Ygeu3MmbHq8qSssOcZFF8ZKjQJ3i1ODlDmR4LUq9xL1lqhPLuM6YKQ9aMZ58Koed5zA5lhtQOXBfzMafFX2dE7IX6okCfyKHrHNAg8iKvHVQYEn2xttm/dijI+WOw+xDHHlcZEX2J6yw93rjoMEicDIZL5/XfZV1jhyOqXzgR9JTBE8wBm988EWSUTSJP9JgCU9aepB+ahPflgiIjVp9sTmgyI/0UdSnQJvJUY6TIkFkuFKQy5pg8LcJPM24ytAierg9y1BiTfIY69B7r+HFy8hjzyMZ1zxNkWdrVD1km3w8FS1c8T1B1fFYZd9/oEfLzSI/pPVzdbXsf0X2omEg8TJ9k6mH/Xd85OvYOWVOWtqw3ug9wnuRZ46t7L+xp5wnOOi5Qvc8J35cL2UPBvc85EWwy2DS2+8n3vbXFnPR9xEyWOpF7yT+71DhmY8O1M46pPuU8QeQe6n/W+0rmfXY36/Hu5oPta4SCjnL1rtbSi0PBnrJFxD1nOGLtTsZJiymh0+bn9uqe4zl9C3PEgrVbmg9azMjfSjudf723c55g4HjZ+ois6/fN3i/ilOMMbWKnzN81jIkaI2JLnp9kqDEmcU05JkebBcvXEgtH9Ilc22sdWeqMSS3LCQV6NK8m9nudCOZXls+ruMYBByl1WFxJPJcTK2V6LEhfXl7IMmEt6fnAER3iCX2zS4vDy+hn40Swf2l1zMP4ku6Ja5t9Np9wnqCi3P6y9wWJuD65iPoX0i9DoheWB7I0mFF/lu8ERs1FRH8X0M4Jedjy3p1ydC59nFsuzO26cpcjJkT/fv5geOi8crB6niCj7JL8h31L6DClYiO7eGBdsc3uX+21QWRxfn972f/nT35ucOoP9lhi7/fnD5qkfmcvlF/Zo4WVX9s3hyGrv7EHCh2iU/t3UWRA/LfnD85Q4Mz37JlCgzGJ758/uAsHNBgT/4FzHNBkQuLYOTLUGBP/oT1Z2KfKmPiPnGOfGiPiP3aODFWGxEb2eCFDlRGxnxgvezQJfmpc7FBiTOpnHpN6tu+SKoeEx+qRpU3wc/2RpzGwr4wy+IV7yNEi9EuPydBkytJE21SYsCzHmW/J29fPHxz35Pur8vpF+87Q+5I2v2xuvqB/j/uf0f/nzPONfVf1Rr6r2pb7lr2GPnn+oM4xkU85Zw2VL3++YM3x+m1C/h1cvxd7vO1xnnM+rk+aJFZ9L/oD8ve+89uf3fUn+N45AxYkn+j762xzSI2jd7r3deIj+npzxiFtgjcYE2cp0mHOUsm4OKTBjPQbxU6JPpE3iZccHYI3mxu2KTEgXra+OKTNnNW3mE8qDAi9VQxsUaDDjPTbxEWRHrGKXJClQ+jtXufZpUzwF7lRRt5hHsnSYEb+tXJ3YC6UK6+xtl5prb1Cvy/S5wvVeYF5fr7zzxPjM/STtV6fZg2QeLp7GT9VzE/R5pON/0nWw5dDQfgrfi5yik32KVCjx5T247TJyuPl5bHqPdL62LFeOcUm+xSoEbjevO7JIKmsvvS8/sYMB2OvWec84bzB2W1t3MrrB3PS6/JLlgYTkrfWJgW6hG4jT+xSz50ISso+0dsaF5l7+9yhssmMpXM=
*/