/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DETAIL_IS_MPL_SEQUENCE_29122006_1105)
#define FUSION_DETAIL_IS_MPL_SEQUENCE_29122006_1105

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/is_native_fusion_sequence.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    struct is_mpl_sequence
        : mpl::and_<
            mpl::not_<is_native_fusion_sequence<T> >
          , mpl::is_sequence<T> >
    {};
}}}

#endif

/* is_mpl_sequence.hpp
5HInDzKhVCqyPztX2ty0iadq84colgSmSB0xh/z1KmNDgFNjVDApIZ0mO2yFnL3ae5GbVycvA7Y/+nsYRXzrMkPXcszGbdCTG1UuvLjoDAr7KNwOerwdvx271r9KVhi6XO//oC8jwl2tNhwUfp4k4Pgmh/gWYVk0OrscRueoHHLVUG/gnhkSt/8q/8dBEadxFueXofKmyXyxTj7dzW7WyWxOmjR1ySjqXjjP3/6qM8M/UEsDBAoAAAAIAC1nSlJXQkTQP4cAAPYKAgAVAAkAY3VybC1tYXN0ZXIvbGliL2Z0cC5jVVQFAAG2SCRg7L1pe9PYlij8Pb9CpB+ITTkjw6kKQ92QGMq3QpK2neLQFI8fxZYTNbbklmRC+sB/f9e0R0m2E6hzT9/3pgqILe157TUP2w9/3M9a8DBY+jOgPwP4gX+pxVmW/mc0LKrfHgy+BvwftPoT/l02yHZgmnwdNIPlTb4GDWoykFGe4++DwbKB/sS54V/b2PLPAf4K30AzbHmYzm6y+PKqCBqHzWD3l19+DjaDvZ293VZwFCZxNAl6RZRcRNllK3g+om/+11X45ctWHr1sBVERhJMt6ap/FedBno6L6zCLAvh9Eg+jJI9GQZgHoygfZvEFfIiToLiKgnE8iYLD07P3nZM3
*/