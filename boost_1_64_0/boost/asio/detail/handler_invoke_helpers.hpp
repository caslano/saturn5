//
// detail/handler_invoke_helpers.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HANDLER_INVOKE_HELPERS_HPP
#define BOOST_ASIO_DETAIL_HANDLER_INVOKE_HELPERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/handler_invoke_hook.hpp>

#include <boost/asio/detail/push_options.hpp>

// Calls to asio_handler_invoke must be made from a namespace that does not
// contain overloads of this function. The boost_asio_handler_invoke_helpers
// namespace is defined here for that purpose.
namespace boost_asio_handler_invoke_helpers {

template <typename Function, typename Context>
inline void invoke(Function& function, Context& context)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  Function tmp(function);
  tmp();
#else
  using boost::asio::asio_handler_invoke;
  asio_handler_invoke(function, boost::asio::detail::addressof(context));
#endif
}

template <typename Function, typename Context>
inline void invoke(const Function& function, Context& context)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  Function tmp(function);
  tmp();
#else
  using boost::asio::asio_handler_invoke;
  asio_handler_invoke(function, boost::asio::detail::addressof(context));
#endif
}

} // namespace boost_asio_handler_invoke_helpers

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_HANDLER_INVOKE_HELPERS_HPP

/* handler_invoke_helpers.hpp
f8MMXeVFGKsb/AnG6PSCP9PRL+bho9FHl/hSDNNVfhJDdYM/x4rYtxUbph2xwjx5PhoDdIkvxXrje/gBLNB1fgezdXrRdbE+9pwPxYJ4B/gcjIj18y0xRtf4RYx3bpP7vuS+nJvjkZitC3wKphpT5muwwPEqPxnH4975c6wwJvuy9WN2rJ+Pxnhd4ksxINbPD2BErJ/fwcr4LhrW39DGd/OhGBTr53PQusz6+RYsjHePX8ScWD/3fcUY43M8Egt1gU/BKF3ma2JM7D8/iQm6wZ9jZuz/q9aPOTrPR2NaPDu+FAsd7+EH4rg56/wOVsb+v2b9mBPr50MxIdbP52CQMRW+BaNi/bwefdxXeOFKf6bo8OMYrrOve59R0OGrMU6H/4aSDr+K6Tq3ynj06HAZc3X4N6jpZvQb3nNd5a+s9q+ndPggrNfh49Hv2YG9PhtDdf5Nf7dBSVe5jrxu8OeYrotvuV+UdYW3e9vf5XSBr0NR1/hFVHST+66xZp3jkZgV4/kUzNVlvgnVOJffwnyd3rGXqMV1eSUW6+y7G6b7sCLm5zHv+XNcl/gOZJY7zj9o+ruXLvECZHWdN3zfPuscn4SiLvOTH/gNj+MfOhdTdJFnIaer/CqG6LTWddEdY/iijzzTmJ83+Nie6GwYhRj/X3OgrMMPY7oOr8c8nV/nnfzE/ca1uI7FOn26YToRdV3hdWjEPJ/5swbL47r8Dpq6sN7eYrUu8zVYF3Pyk0jP2R/u+7n16xyPxBBd4FOQ1RW+BRld4xcxPM7lvl/Y2ziXRyIf5/IpyOkyX4NCnMsvYnScy32/tP9xLo9EUZf4QUzUDf6W/zbeFN3NB6IU8/OlWK97+BEs1HXeeIOWtDbG81yUdfjZDVvSLB1+B1VdbGlJD2NNXIu3bm9JS2Kd3N7Rklqftzb+LSboKo/KtKTxusRXoV8c5yVYqMMDOv1jHd4KK3WeX8ZYnd3IPBiji3wTpupwx1da0jQd/gZm6wJfiz66xhv3aUmTdTdfiEm6h9fhzpi/r33CCF3hGzAo1smLMEDXeRWG6Sa3b9yShsa5fBjW6RK3bmIPX3AtPggZHf4xsjr8VwzR4YXI6/AjGKtzX3W/SLrAyzFRp01bUgXTdY1f7Od+dWmzlrTb5i1pgS7z8G+YV4eb32pJK3RzCG9vnbq4Q0v6dKj7WmH8ji3pGkzUxZ1a0q+R1xVeiHG6e2f7huG6yoO7W9Jo3eRBu7Skoi7zvF2tT6fdeHd7qkt7eFbD/XNxfM+WdDqW6PCOe3nWOpzH+rgu/xPZF+05t+3dkvrrHJ+M7rgW34Ypjtf4ZeR0k7cYYX90N49HWZd45Eh7rsMj9/Uu6fDDmKB78taFim7wN/fz/uvw46jq8Eos0cX9W9L5WK0rfBsasR5+G02dDmhJ5yD7kvn54lH2P+6L9/6O+3K8yFPGtKQeXfleS3rj+9av8wXf2eH2Ns4d15LOO8r7GcfHt6R7j3a/uvwTz/AYz+Llgb3+Y9F4Hb4FU3X+WM8RfXR4g586R4dPxTBd434TrM2cJb79OPeps8fbM6yI6/IsLNBVvuYEe+XcBv9mYktaGsf5MyyMc080P5boGjcxy/h0kt8TZBqe0cned+R0kUun+B5jzKmeHRbr8MySb0CH30JTV09vSQf83L7pEt+IIeYJt0y2Vzr8NYzX4W0xVYf3wExd5RcxV4drZ7Sk+Tr8BRo6vMmZ1vyKa/EdyOk6v/xL19XdU3wXUz2L6HO8h+f6pnSRV2GKzp7nupiuy3wPKjp86a9b0hwdvh+LdfgprNHhFWh91bnnt6Rl6K+bvOsF1qALfCa6YwyPvNA3G2N4+kX2Wld5s+need0=
*/