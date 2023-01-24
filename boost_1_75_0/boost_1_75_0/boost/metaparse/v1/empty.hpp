#ifndef BOOST_METAPARSE_V1_EMPTY_HPP
#define BOOST_METAPARSE_V1_EMPTY_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/end_of_input_expected.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/define_error.hpp>

#include <boost/mpl/empty.hpp>
#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Result>
      struct empty
      {
        typedef empty type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            boost::mpl::empty<S>,
            accept<Result, S, Pos>,
            reject<error::end_of_input_expected, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* empty.hpp
24zf2KRSk4ddx/lD47tRcwYnM9HK5B+me8TJPr+1/sPONg6JT+O3jEttR3f8KltMLgOOX3UghiZqzDuhTvEp0djv1LnkZuUZkk9UYuecyHH/5tsI91fdreqhOoo196c6shlkd1CDKCE+xiUd97I/IaIDZcl6t1SMIccUVRt8KRWdbxCqCH/A99y+H7YH40aAbPy6K6PROacIdshiDOtlfA82F20fD1sQdLp8z6TbUk/4H7B9mKLtCYfVHbTX3eNLmHKBwQhAuIjeUzQUoaaLQSowplQlL+DlYrIwLmqmmQcsLE4tE6pWMk7VPj+ezYt9GpwPHrMGWjvnKu+zh/1ZwWNx+Gs7/OobPGbDX1/Br9TgsVb46zn4dXbwWLy9BPLx2JkXrUDCP8G3LEbwucOP4VHuLWGYiDgLNPejuzH0Er+D4pSdGBmZHdpEcc0SLYEIbfVAxR2plHZm4oabeMjBKBFnVMyfglCjZLpZxcccox3klv2AfTiL1jQLmibGqysO1w8WU6QVzUY3kI5SSD9Y9Fd4fOx+OOnTb3AxCpaQmZYdynSVNBZ2ADgIxHF+bzFFY34TCw1UjyMJ43W4PZKQLa3lq/kYjmTYH1vgrIjzum4SxYOkUdp4nUmXn8A3yZBptEkena7GR/SaptlteLzxHNoqXdqrbKIAvZE8niAfqGI+fNGU7/S8PZ/x9smyvSSCsNxNMc4NMwDo6Hyn
*/