//
// detail/base_from_completion_cond.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_BASE_FROM_COMPLETION_COND_HPP
#define BOOST_ASIO_DETAIL_BASE_FROM_COMPLETION_COND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/completion_condition.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename CompletionCondition>
class base_from_completion_cond
{
protected:
  explicit base_from_completion_cond(CompletionCondition& completion_condition)
    : completion_condition_(
        BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition))
  {
  }

  std::size_t check_for_completion(
      const boost::system::error_code& ec,
      std::size_t total_transferred)
  {
    return detail::adapt_completion_condition_result(
        completion_condition_(ec, total_transferred));
  }

private:
  CompletionCondition completion_condition_;
};

template <>
class base_from_completion_cond<transfer_all_t>
{
protected:
  explicit base_from_completion_cond(transfer_all_t)
  {
  }

  static std::size_t check_for_completion(
      const boost::system::error_code& ec,
      std::size_t total_transferred)
  {
    return transfer_all_t()(ec, total_transferred);
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_BASE_FROM_COMPLETION_COND_HPP

/* base_from_completion_cond.hpp
qa42AN6kyFcBBhFKesh0FzYwNw9LFS9hM9uQGm4RgVoAqI+W15FRtDTCHWNZis5zQ4XOGFSXEH/Xe24YJZb3dx/Ey/doG8j7nZIHS3PCB4vZzjM/Xgn83gE/6r+cQyNnxusnCBmoC8Te//Jhecq7kZrARxb4L3Y1NtG4tL0Ufvi193IMN+1RXftsL+RJik54XxJU+ErTDkyjIKJ34W8Iyc4I9XwCOHu9zGP19tb5/c2sD/qmdORr7sg3xcwrkk0HhIgvXFHjKtMLp8tI8HQ3gIl1VxXXGGoitS0y8YBFBOOq/Lbis4u5VGDlqjh1BQbYq1gUi4pLjTvp9xA3Z/ckc2iH4oc3opOnUOQMSlZaXSu5c9JJd9p2GOCuw6Ra3SMAyl7g9H2dOm6IcPHFI8q/yFXNBFmS+4wo1rmlFDi1MkmTx5HM77yEVGz5tTKclCFopWad4pmwSMXDU7MMsuUgUkh5fqRxitEijnOnLq3gjOF6AuNeScNszjD+SkEtLq/nJCrfOv89mJQwBI+OSQL03/wJC09Cce1Uny8u9bkpKrGGgDVU+T2P+9Fxs6bpOZB0l0fyChMg/1vxhYa9/MfmkWaXZpYlWizWVnMrM6+NiYeFC+HLMz0kg5riOEIw4CQhCmX3s/RdIJXg7UGP
*/