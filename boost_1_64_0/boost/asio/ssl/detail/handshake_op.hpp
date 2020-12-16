//
// ssl/detail/handshake_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_HANDSHAKE_OP_HPP
#define BOOST_ASIO_SSL_DETAIL_HANDSHAKE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/ssl/detail/engine.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

class handshake_op
{
public:
  handshake_op(stream_base::handshake_type type)
    : type_(type)
  {
  }

  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    bytes_transferred = 0;
    return eng.handshake(type_, ec);
  }

  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t&) const
  {
    handler(ec);
  }

private:
  stream_base::handshake_type type_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_HANDSHAKE_OP_HPP

/* handshake_op.hpp
9R2libv8ikKecNd+qAkS7i673x9Gvv3atRnLm0TLU9/r9B7piBkTx7T0vn//nGfs95NZta+8oG3ce7fmwd33+qTjF9Ad9KTDbevCmx54jiA9EbmUtvKmZyd01tjY9Ig+fr+xFdrGpaPYp04f9EnHI9BluNNh1Mhjt8NXJhmNTItf+1p1TJiwvbavDNxW6HI9aVlUViXW+X3fOZQ+w9T/bRnx138/GRVpjgT0u+156Apd6ar2vAt5xmxNV7TfjdJr21eapEbLMQd/hmmvJl5XG6jlV1DzsAT3AvzFnnwEtgHz7VklPPPIDVYecJpHjSsLOv0u87EdM9rQ5dNLCZ1+g7pozbfod4V2pOtbtI3abciJQ8+0fosaWXXAP8p8r7me6Wqja7O88voVcVjj3PLSNuorp6xxvnLSOLLw654+t90NDc9XGxsR+QiNkctJ47xy+WEGconThkWsXLQv17178iz3t1prrzxehHeDRx6mr/CVyaP+MtF4siTP7f3tsShNvtSvlkYuhs7I5iUf2fxNZfPeYcgmR2XT3m3bwyWfFdne/us38BeOd8vH9F8B4wv0pp/Ikn4iSq/9hNK0N33ck43o45x5OtXYINFnxNiLmNPGu+f5x/AXj/e32Re773mfj71ieM2+53v97clBc/j7nvf52GK+121PLrEv9SuwL7X9cPt+06YnDNp0b9O31474w6SOLW/8KLEv9Uj2pepLhcwZ1YbCushV/5jOt/MOKHvd3PrHhkAuHQlo3x8KRvg2KF+qD99o5RsDpoBjlc++uVX5limf0Zuj+iSzwAKwreqTPFb13HUDB6r+x1NAnOiXvED1S05Xulng6eAl4GDdo3oGeFlUXx58OucLdpB0uPWwjlB9myP19WkU2Eb80fxXKn+eT/63Kv8jYBfwUac+4Xqe+4DybdHnPqjPxW/0vtUpf4Hwu/W+Xa9yXw22Vn+O7kXtoXtRTwRvNPnQuTqwmU8+ajW+5WAaeJUjH7ljgvNxr+bjB5qPzZoP/Ia/sB7+7wk/95X/VuXHb/iL6+G/TflvV/47lB+/4a+th/8u5d+o/HcLP35nOdbD/x3l/67y36T8+A1/XT3825T/ceV/Qvnxm3LbPya4/V2j5Xattr+VTn2D9fD1Vb4TlO/EKB+NOJhvofItUr7LnPWrHr5i5StRvlnO+qV87X3k01bl0w7MsGnAbPWb+qX8GT78S/S5V4DNwaWqH3eZo58qVv5an37qWO2nuoDtwFzdE9wbPE735J+ke/JPBbknegzzwBlKNxvsAVboXv1K3Zu/RMONnrFxweko03TM0XSUazqqNB2XaDrmajoqNB3zNB1Vmo4Fmo5KTcelmo4qRzo21JOOIk3HJE3HZE3HjIj+Xk3HVE3HeZqOaZoOnKTjAk3HNzQd0zUdM5zlOj64XmRpvWit9SIbxOGP7kkvVv4cXG3Iqw+0V2pij3Zij3bDe7S/qP3Zh7M3+6uqS+3z3J99NPdmfxX2ZR9YRb25LsUqwE3HrcBtwj2LO4BLux6dZbgxuErcbbg63AFcymp0quHG4CpxN+G24/bjrDXs78aNWpPY2524ElfiSlyJK3ElrsSVuBLX4Vxf2P7/o6j/b1lvy6yZt9P97c3VfsOnuFJ7DfQc5xqoUR8UqFfsfKF/x3LoFdM42nvWTEdLmFuv2FTxf2Bl85tl1orNurTQjYJus9B1hi7JV/9YtYRnIaMLMlviv1L1DS1UrFW8zE+H2FHQAaZrtYn1yq/AeuV4Wa8cV3tbQe7AK+5+s3vJha90qZmYWK883PXKsF0Ybdvap6yLsQvTWnWCtAU767x/LniS6nTpoPPNHcHhqjtngs7XF+t8/Rw=
*/