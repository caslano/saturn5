//
// ssl/detail/write_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_WRITE_OP_HPP
#define BOOST_ASIO_SSL_DETAIL_WRITE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/ssl/detail/engine.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

template <typename ConstBufferSequence>
class write_op
{
public:
  write_op(const ConstBufferSequence& buffers)
    : buffers_(buffers)
  {
  }

  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    boost::asio::const_buffer buffer =
      boost::asio::detail::buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence>::first(buffers_);

    return eng.write(buffer, ec, bytes_transferred);
  }

  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t& bytes_transferred) const
  {
    handler(ec, bytes_transferred);
  }

private:
  ConstBufferSequence buffers_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_WRITE_OP_HPP

/* write_op.hpp
/RJlM1rhJozaH04f9rBGp8g7riiU/lYurXcgnbX1PcJ5/st+FJX/jj2ty6DqW+9/pKwXF2IfMKFNr8LzNe+PALcBdhAVYLfj4zcaUK0+vtbCbVdtlfRxi8L/tld7qsCh49838w+Hsolr08vB5f0/Zh64GhtiqAsWg37m0CkUNROokvDR67GIbzsDelu3YDr0Zxr2ibdbGPfeG2F/uz/CrR74t29noE/f4dda6+/3TLvOevWeaddYr+ykGOAW2TOpX5/+HwQKRZ36qDcaJSclOHo7idIcXBveM8kOGQRWYTUG9clfOEPg4FZs9fRB9TmS2lI/221E+ae3/N5plaZ2RKJ76tjK0wq8d1tWUnZ+JfV0fApb+r3XMXYsY0uAdZx2g3omNXYsSjnetKKZorJcwhq1QmK/+3TaO3z5aKdYOK3B/RxJ6dgMJUv5/R07G/xPz8T+b/hxelf3mPKv2606KvIP24u4UlQo/orN9qFSXai//aS6IECoKCqC6op/m1Bt8Vdzqg3VGq+b49+m+Nv62ev64I2jWssb/9b4/t3vd4Vd777r6uOfu87WJyKoZCrJrjfujaM5KpGb41UvagBlrUlY+xCKw/+y/buh1Q4qjCqN7Y2wTz8qkeqG/YfjarrhVU/72K1wpB447gBqEP7vhXME2nsnYW/r327v66LhYqgKONa7czfG/4Psz/bBvh/2+qdjbrCPGoheGYx9
*/