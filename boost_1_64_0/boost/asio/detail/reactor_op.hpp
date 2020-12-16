//
// detail/reactor_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTOR_OP_HPP
#define BOOST_ASIO_DETAIL_REACTOR_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class reactor_op
  : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

  // The number of bytes transferred, to be passed to the completion handler.
  std::size_t bytes_transferred_;

  // Status returned by perform function. May be used to decide whether it is
  // worth performing more operations on the descriptor immediately.
  enum status { not_done, done, done_and_exhausted };

  // Perform the operation. Returns true if it is finished.
  status perform()
  {
    return perform_func_(this);
  }

protected:
  typedef status (*perform_func_type)(reactor_op*);

  reactor_op(perform_func_type perform_func, func_type complete_func)
    : operation(complete_func),
      bytes_transferred_(0),
      perform_func_(perform_func)
  {
  }

private:
  perform_func_type perform_func_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_REACTOR_OP_HPP

/* reactor_op.hpp
uyE6YNApX03qcaBHSpdfr/iT47zSypX/rm2nh8rGjXtseosRk1b3ye7pOO1auvL09G3F773wj26Fe0/qVXh1r92Oc4bjylf3HdbvnsO33vntuns3P3f2Z6QJjGN5/r3b89748bacj3958aWtbx18leMcF3Lln8zK79WQdu6W33Sbem6rfT/8jercKFf+wkkvPvXjl+d9se7nfQ+/e8tSyovNLO/x2/VbvhtY+vBZa+fdeeaDd+xxnD+wvKLv2K0fP3F9zgm3vnLnYesqSH5Kkiu/btETzdud+Y/bB9zzyoC0q+dNd5wfmX/sgyfd2PGVrjfPO/X9Y6oOlF7jOANHu/J7z1t94cgt91W+efj3O75M60+RX8byrm3DOc8t3F89fPAlZ69f98svHef3nK4TUy959NHVPUqev+64X+8btnS842xj/t0zcr/4bvL4Fy/64M0nK0IVzzrO9yz/7vVHW152yqbz57z6VXl06eB9jrOnmSuf0S/y1cnLVo5IWrOyzfoPIi86ziUs/+MFbz81KxK9ZtPnJ664a8AtLRxn/hGufP+WfleMerzmu02f3Xj/qTf2vY3C5/yse776zC8/GfrUi7/I7DXy7YlUvhcxv/crFW2qjp1/2l9anVk3aFjB9Y7zGcW/zns38F62pD/a0DWMCtzbcTamurocXXs5XJYb+9N1El2H0HUyXUfStR9dx9CVZBun0HUoXWfQdRhdy8GvAH8vPWP58GbORnLbyT1Obj+5XiOaOQUjSE7uHnL7yHUb2cwZR66UXJzcFnLbye0mt5fcF+Q6jmrm9CM3jtxcclXkNpLbSm4nuV3knif3Bbnmo5s5aeRmkismt5bcZnLbyd1Hbje5feQOkOt8BHHJTSRXTC5MLk7ufHI7ye0mt5fcd+R6pTdzRpKbSm4ZuSpyG8ndSG4XuZfI7Sf3Hbm2YyhccsXkwuTWk9tCbge5x8cQl9w75L4g13wsxYPcIHJTyZWSi5M7ndy15HaSe5zcS+TeIeccSXxyg44kPrnl5NaT20JuB7ld5J4nt4/cF+RajqM8JjeVXC65KnLryZ1P7iFye8m9T+4AuY5HUT6TSyc3k9xycnXkNpI7n9y15Jp+Tb+mX9Ov6df0a/o1/Zp+//lfc3Ir/gvf/9WxZQ10JE7N8fzp/+99+6c6bVMemUZ6/pv0HetUx1byN0TLlFL6Xi4opilAGbm5szIy57szFXIKediZ7QUZ9KE8HvaCbkkivTeGyC9df0bXxynM9FPYXkDTG/KKinLLSjjOhLenb/tHCQ85Yqtw2AfAH8H3i+h+Kd+vDbn8ONsL+Dxj2Ao8fn++zyX+Qr4/IdRa2A7ot4qxuYQ9wlghpVc8K2WDe3+5M9CpAyfkPMCyHiI+8p7j+0BPN7zKhpoKh/EFFMYaDvNoft4Gzok6P/w4+53hpDuHWcOLc47xVlyMu95P4vA6sn3kiWkuXl7n5Vkq0jGOw5jmtKGQW5N9I0RYZrqwbaQ3YttIha3Czff8EOc7y+aSjOJCMpG3Pag+PEWcUq4PeD52dO9K2NOEFXjYqvKaMJffpJQnOO6UrwMcvh+9Qdx3xn0t7ildbBsZi7qzy31JYGNys3gJud3EmbmR605ZrOYE3terkuRuvqxmm1DZrIbKSt6PDHUH/GF+2UT5fjzbkQY6ip9MsVtMe9ipKpk3le/n++EM4Wdd3JH9za6try4nL349O5Y5s2B38vz0YbuTGJNfkNIrieSUtvE9KK+GJbds23KYX17jeoi0tOvoprysMBJrqIor9eAXHF4K5VNeiluuE63F2s+3WS2n62q2Qcl86UFyd98fN+2QI+3sh+NJ6XMxpE+U0xZ+NrUpA7g=
*/