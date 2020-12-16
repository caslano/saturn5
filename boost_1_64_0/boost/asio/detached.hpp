//
// detached.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETACHED_HPP
#define BOOST_ASIO_DETACHED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <memory>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Class used to specify that an asynchronous operation is detached.
/**

 * The detached_t class is used to indicate that an asynchronous operation is
 * detached. That is, there is no completion handler waiting for the
 * operation's result. A detached_t object may be passed as a handler to an
 * asynchronous operation, typically using the special value
 * @c boost::asio::detached. For example:

 * @code my_socket.async_send(my_buffer, boost::asio::detached);
 * @endcode
 */
class detached_t
{
public:
  /// Constructor. 
  BOOST_ASIO_CONSTEXPR detached_t()
  {
  }
};

/// A special value, similar to std::nothrow.
/**
 * See the documentation for boost::asio::detached_t for a usage example.
 */
#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr detached_t detached;
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) detached_t detached;
#endif

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/detached.hpp>

#endif // BOOST_ASIO_DETACHED_HPP

/* detached.hpp
iDV++Pnd3Y3XynKUx/nh+8R7Gq+dvAu67xGJCfexr6MnvD8cuu8hcdzXePnk4+Ailref8QrJi+CJfvh+9zy73chL4a95vfONtwN5BTwJ7xC7fclrYC3e4carI2+AJ+MtNF4TeQtcjHes8Z4gXw5PwTvBeK+QK0/FO8l4neTd8DS27ynG877jfByeTr+qM9448kJ4hh++P32+8dYl3wjW4V1hvEVzXf+M+Js0B7UyllMFz6QfXG+3B7nyLNZLk/EayJvg2bzeJcZrI1eewzh5j/E6yLvhuXgP2/3je3c/4nl4TxpvIrmyntf7nO335GXwfLx225/Ja+EFeC/b9ULeBC/Ee/VvbLeL0my3dpbTCS+m/71ultdNrrzEZ37X9tM/cx9eiveBHTfIlQ14K41XQq68TK8DjFdGrrxcrwOMV0GuvAIvyDbbg1x5Jd4A49WQK3+LN8x4deTKq/DGGq+BXHk13gTjNZErG1l/U43XSt4Or9HjoPG6yHvgtXoctK93Bu8X/BD+/nd6HDRePnkRvE6Pg8YrIS+D1+PtbrwK8ip4A94+9vXy/GrwbsSrstuDvAE24R1h1zN5C7wJ73jjtZF3wJvxTjFeYibvN+Pdgne28XrIEz+GXIJ3sV3P5EXwVryr7HomL4e3MW7caLxq8jp4O/3qZrteyNtgM94dxusmz/sp5B14LcabRq68k/OSR423LrnyLl5Hq3295Mq7edzHjbcRufIe9rdnjVdGrryX9fyS8SrJlffhvWm8WnJlC94KOx6QK+/H+8xuD3LlAxzPv7X7B7nyQTwvx5yXkCsfwssxXje58mG84cbzfuY+fARvvPHyyJWP4hUZbxy5shVvpvGKyJWP4W1kvFJy5VK8rY1XQa58HK/ceFXkyifw9jReLbnySbx5xmsgVz6Fd5jxWsiVT+PVGK+dXNmGt9j2A3LlM3hnG6+H/Af4LN4lxkt4/HsZcBleo/EmkhfD5Xg3G++609x4GvE5vLvt9mU5yufxHrHbl1z5Al6b3b7kyna8l4xXTa58Ee8t4y0iV76E96Hx6siVL+N12/5CrnwF73vjNZMrf48XH2DGDXLlq3iDjNdBrnwNL9943eTd6uOtYbyE7/KIr+NNM14hufINvNnGKyZXvolXarxScuVbeNsZr4Jc+TbeXONVkyvfwfuV8WrJlX/AqzJeI7myE+9I4zWTK9/FW2S3L7nyPbzTjddOrnwfr954neTKFXiXG6+HXPkB3nXGy4u5POKHeLcZr4hc+RFei/FKyJVdeEvt9iVXfoy33Hg15MpP8F41Xj258lO8TrvdyJUr8T6x241c+Rne13Z7kCs/x/vJ7pfkyj/iJXJX9bzA5RG78YYaL59c+QXeOOOVkCu/xFvTeBXkyq/wio1XTa78Gm8D49WSK7/B29J4deTKb/F2Ml4jufJPnJ9WGK+VvB32cN29l/E6yZXf+eH//1FpvB5y5fd4BxovL+7yiH/mvHiB8YrJlT/gLTReObnyR17v8carIlf+hHdi7j/3PslRLKcWejH5z903y2sib4F+LHzcxcZrI++AMbzTjNdNrgzw6uzryHB5xDjeWXZ7kBfCDLxzjVdKrszEO99uD3JlViycX7vIeJXkygReg/FqyJXZeFfa/YNcmYPXaLwGcuUAvOvsdiNX5uI1Ga+FXDkQb4nxOsiVg/Ca7fYlVw7Gu9tut0zJ+xKvxe5H5MoheA/Z7UauHIrXavcjcuUwvCfsuEauHI7XZrx6cuUIvOV2e5ArR+K123GNXDkK7xW7PciV+XgddnuQK0fjvWW8RJbLI47B6zReIblyLN4KezwiV47D67LHI3JlAd5KezwiV47H67bbg1w=
*/