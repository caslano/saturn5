/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ENABLE_COMPARISON_09232005_1958)
#define FUSION_ENABLE_COMPARISON_09232005_1958

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion { namespace traits
{
    template <typename Seq1, typename Seq2, typename Enable = void>
    struct enable_equality
        : mpl::and_<traits::is_sequence<Seq1>, traits::is_sequence<Seq2> >
    {};

    template <typename Seq1, typename Seq2, typename Enable = void>
    struct enable_comparison
        : mpl::and_<
            traits::is_sequence<Seq1>, traits::is_sequence<Seq2>
          , mpl::equal_to<result_of::size<Seq1>, result_of::size<Seq2> >
        >
    {};
}}}

#endif

/* enable_comparison.hpp
oY7eSZlvZvGsAhgP/bY0SdNRZTrDGPTOxwp6cdP845ppHnphk/bpUP5pmpdtcbJVEhKoaT8bSZH0Cqkir0kUNh5LDLpWuJu+ZiMzg66VbGRW0PUCGzkw6HqJjcwJulazkYODrtfZyNygay0bOTToeldYP7KgNOhaB5VrqiwPpeMCLW1kMfytgb8l+KbAQ9s3QVe91KNSyignMUY7zk1f8Y2ZHnu4T3vGqnToSVZegPFFm/4F2C0FEJ2Y8wEQnm+lc48wW9z4OB8DwyZfZSGiw/K8QfEtp/0FYoTgZ9SB9/JHxDLBz4iZbuaPiL+CnxHn5fNHxIzBz/CPkrVcG1A0BmBAZYyggYRjpK2+eU7/rqTmpJitHDfZsD20q9p+K+cmRs5dKwZ25Nx1BUOlYSv37gKVAecox0HUGIZ5aYOmKmZyirIm39bZq3zAotPTo7NhegIR9hHf66zG6rCibNxhjWe/4E7PVmCnmchOW7Wdnn3KQ1SF/zOK/O7BgId7KfzS6sejCi53/PphWTvHr33LtGnM2OrZLZo68vyC+UvtW1ZmNu3QY+EbuuOmE0lt1PgOp3DcBjke5PPWkBHZ/OD3hSiQbFm0j8bMgj6y0xTuIY0KVfkZM5KjW1o4OZuXtdUiTxUYSrAecb9DPfiXX5MuYN/qqqCmB88ZcOF68OfBKBqLZrbet/rUn9xaD74p2BaDvIJz6sEx9LimNQ5u
*/