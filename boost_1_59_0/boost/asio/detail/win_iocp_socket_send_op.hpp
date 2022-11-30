//
// detail/win_iocp_socket_send_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SEND_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SEND_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/operation.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
class win_iocp_socket_send_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_send_op);

  win_iocp_socket_send_op(socket_ops::weak_cancel_token_type cancel_token,
      const ConstBufferSequence& buffers, Handler& handler,
      const IoExecutor& io_ex)
    : operation(&win_iocp_socket_send_op::do_complete),
      cancel_token_(cancel_token),
      buffers_(buffers),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t bytes_transferred)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_socket_send_op* o(static_cast<win_iocp_socket_send_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Take ownership of the operation's outstanding work.
    handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(handler_work<Handler, IoExecutor>)(
          o->work_));

#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
    // Check whether buffers are still valid.
    if (owner)
    {
      buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::validate(o->buffers_);
    }
#endif // defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

    socket_ops::complete_iocp_send(o->cancel_token_, ec);

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, ec, bytes_transferred);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  socket_ops::weak_cancel_token_type cancel_token_;
  ConstBufferSequence buffers_;
  Handler handler_;
  handler_work<Handler, IoExecutor> work_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SEND_OP_HPP

/* win_iocp_socket_send_op.hpp
7Cg7qHPyyBz8pPtWqDtjPPyINAeIxa86DpYQVa0PKGHn0OiA9q8xit/n36gML1APr69mENIy7r4EOEDnleA0F1Av9BsqJoIEl1CwTXxWHzi1eJ+wDcxuWi8nUSTsMw89C28OfPCd84E6kgr7eMnGmLZk5CMt4mTyamu2BFVbdG5NF2s8XF04b6rnCtEUO3oquWm/EwfvtHT8+uSMYswxRsbCBhjHAQw+SLo3x6NzC6zXbWnEZaVPknWsxxm7YAtn09WddEBTh1pYGsfQeaEwteuj0qGDpprqz2PlxcmayLfB4tirTPYOf89qZ8kp4qoDbGc6GzYiyCK+SGokYvzFyW5tZCwYemxFbTTJKg0LFm2pcmAmY623QPnhfyC1OeacJI1uPVO10yR21i+xg+C6zhmisYkq4znqnlVS0loYQ2OiEfRiSX0wnzZzgTlSygbw48xtaNKcw0LdgDjkUzcnsJ/EokiI3FtqxSeqhHOv7PloFNIoNtMkhWBAmQbRwKdvPJo64N6MmRK8WqpijFiqz6qS79sD35kQKFdS2kfZKr4YiYIeCRrBOG4DvvYRMz/64itqrNuRDPuKeUKi4bFLizZp4M39UDINYiO09kMl8ttNOtPX3hMVq/gfTRkPVj46V2/6yCsWJ0DloacrbC34rH7xlrl11syEl8I+6jbgnsPKLLynWtLfbVZ3KK31nEhTiGF7vCeTPvJGr0cIfC8j+cG1N3y8XXnbR2xWScABtZjUdDMbBYgBW224cVYc67u51ZCTISfHw83gXINvpVVVKcZYgu8R0NnVOqaQhvfgWqP9suRgjmVVQDlzuWvhLyvLcnK9nTJgZWT+dliTHMHXed5eAZu2yBauplhxw/tH2CHZX2G3w922jGTWHUCjmB0cpHvQJTQuEtG6s/jZXnSHPhX3BBNfJcTQlB9vvcT2uGHv1+pBnPS2aUh8+S8xBu1tn+0NTiO1WBjWDr3QHhCFv6DT7/aQFr5Mp8g6O5LZngIpAtwZiSEk+fj41L5ZbWgvci2SUrkcL5pKhW6PThlWxMZeqnaFTS7YptSGjlrMe8y1W7DSDIjZVk4vzuiK0gkWJJ8Yo4Iq/M6xnWgrMfdSGrxYScll3F7mM3SCtqNLBIWy9ABjS/0z+kYQ01S3sDK0rk6NzHC6ONF8+ggAtg8sCmPXD0JmnOelCOesat6WKUOtXyNUjyhLYb2gI/lZgxWzYy4QoAsQdm4vQuG2/r+5hIgKRi/t6zDzd/++w4IVZS/XYlu8Z8Cg0uC32GWryS4HQZOFvipt0UPJLm9hJZ7t3ra3J0buCbN8Z5mlUNDuAv8D3zSolamRWyE9rzkg6uKJ+biWfsznCpVwc49K8OKiO9FJfeY4E1DXJV+m8IwBhav+ysGtaT0UQ1anGLtvOIRWV3y4JH3t2fNPLzSalfQnUqmIK0YwXkgcQdlLlCjz0zyXQPzPbJmMSD1SSqiLt6TP7bA7gATyZT3DTfOqKZuOmbjiyu7GKwCsd7XBKCbgLJATKToftPzrvmrPMwQzpnJIJyhRrv1lXkgp+EES8OrOdKN79umK7YU09HjUvZ307tRf3NiyBQKfuq4zMZYczvHrdCSMNQrgOwQWT3RftXXlmMTap2Zhq+r1GGD9mEjOoMiMwpb9pOfr7q+dT9mUv3EXJboQQSQoHtE3PMbY/nDf01Bw9UCR226GLtNR8RamCOrelxfUvz+zUjhRpr86S51hSQeWqWtbFOAJetnBV8rJnQIcCzL8Wtm9lavcu88MURGERfnpWIXnTHab2DmEf1WwSndA2qiw2otb5P8ljMbFkkaiMyH7R0KtWb+oh/HNkmgmbNvEvdr21GnJNq/5W4Yf6isixv2mdVuX/iXSEG3G08qTQRaKD+058axIX2czUxNMHl+gGbBDzv3P4zqMjiE4N0AH+BsFGMoYx+MJZmRef3L+nua+7WS8aFD1oGnIXVF0D//Zquo+5Q6uvXD6V5Eza3bQju9B6xPrdzEqdtsgZ7bgo25HPtSVYnReksEZcn+gHrmW41OOabGLp3qmJ0870tToWKh9Vhwh5aJlLN/CtbO3pf6eLlabLySyMyV5xfzbT1lVf3jeb4VLebFG5aJRVxvp4MQ07jU5MBB3pOzbTNhD4sK6ScWjo4TAOiUmJsNDxs9b7kF/F6NoxCx4MKVVnK9Vz/V6DjDMVidScnK6P7W3KPBUPjZktjOsJCin5YXheadHgd8HmlM58VjD8sC9DJ1rYm/3aR5U7/i6SPXG4IboNIjUrKx1Qbu+APhSef9WxV7oVo6dxeT3ror/uIv/PUxnsqrUdop1+NC9Beyg8eLi4q8zAMf5hDzorChKbfVtw5VCfrbDVL4blGMrUH2bPn412Mwtr262zVPnrSksBBxFGnhc5pO8bWvASMpoGVNDFKKT7mz3BkGbCXnBCBbL7RyVWTXIr7WeQHiZbiMYvTBPK/d30HmYQzKLrqlK4t3J1LQ3d0U9uboN/DrrzsReLvHx018IKUmOYD4hZbr4pIvght8hURq4k9hXfin/enfZibhc0TPenGHCD/f0t9zoDHNrLS1ap483vwKvK67dXVLTVZP3+o6nKl5LK6u+ZeousDbuKyy3LMmpeLfsf1P0XuILGmBNKKb2wBx12iFgM6+BKLMgBM8dJYncXud0jkHDf1Jkyp7fyDa8i8EVhA3GVXjdZs2OdYTuElULYg2z56mrzebA7c3hOKaEO7mbdhopZDjj2/GqqGkV86VOEyqyRpuVOEyFraM8WToKrXxfHq0k33mvYA/5DFxvfqP8uU/OljMFE0mPTPSXqTKllzO6KTQ+sU2xzaH2Fxs99X/Ow0oUfrw9Ky9BnPKGDdGX5k3azSSln/HaL9KhEalLnJXa8kzMdvgIhxoec4GkDG8dngttAJhPxVLPTKdzrXBWPxFMmlo/snyY2am5rKsJfCyOnadrwEXz7vG6kU5kmhxODpZsQmMx/o1aF/TDdvgryzlCFPQDEznYghL0Ap/buwWlTCkGpawyECXZ/2xvI4fDSGz2rsIqibF0bVrKnBN2hG0C0boKfUfu30a1V8hPZnVI+NRZWXp0nVOki7yV3p2ZDO7ZIyaMjMUbB0P7Xn1tfnOJWsVdMG1AIVdCleRvSC0B8wGMqnWhkdPH/2pgiKt/GEDFSlnFgpVgOEaFcPMYs7ypRKhtEQwhIp8VgKDlVcYDenkqx85OeCjJuvbBYS7ma6UZeEjxJSGocfi4fCKpn9mzfsDDkPDTDn6MEoW48WAjHxdcoWtWXgQ9uaTCxx0aHJTQLfalmHzmFGMWqBNQPhWlrVw26U50HzDxhaAsmThCNJV7Sj6jLVwfuc/CABMJBBUhh6aID0KrOA2hDt/uxxvpPIBE/FAXPEoeTBhA1iPRi0IULy8QhBgeUWriL0lJErnwnWUcY2Qn33iMIXEne+54jD5xY3vfuIwe8Spj7pntD0jpwTXjTNZ5jrFACwXlfGvxTwsJ5X2r8Y4jhdTbu0E6BUJWBFLWw91i/w1u0IC8BLEVvqFv+KXkDZNPMY/ccSw/eSFb3HFsBGUz29xxbCTlIFvcUawSzTJbmWPpbDxN5ja72y0hGRKX+pZeZFxhE291DW037+E1zZRSiBNeDW3Io6SOLqQpymBMZUdeOX1MO9++3Ay2LBmhqlZx0dXqFX4OZ66cQ82S0vlP02Z+K2dV/JaS+jHgVXMbrMapqqF9SsKTrmGo2uoDj5qIRHNx5CJMKM4qD89cdjgzKFdvRk21dxyHImuR9kRXCShMdE325gEL0YzkjQ83jkBjBu0MQadilWQCUuFPBFuTj1srjYwCwq/lGdxgdj+vuBpFrZPFxsnc9cYn4ARvveRCUZOLxulcf3Yfb6mkVePasepkvl9nX+89p5kkTNzTR/NNzMcXM59WEdHt6hL+TPMA8Iqjid/QdtRk/mqzreZXpJle/Vhtl2CKZfa/gNMs1PrVgz7d2VU4gYayXrJdYBF7V6RpQRG/qeKqcpcIFjssjzWY77f/YqBy26tInLZRBDKoKkOTf+553rgjsbQzg+lgK521T1akYDHxtZODzzAtfbUTg98wMW/vyUWsFOubyO1H7B1G5Ntu+2NwQQbiq4md8Asvh5o/Wyt7FKjLHUbxNuWoxh1EhzU0qc4dRoc39KjEHUQp1C2pltkXTP9LYbmi6n5FQgLPqbOaEx7LWPusqeFuU729JpvSC2wiqtmO1Cat5fbb9ssfVTZfUUIeNSqpozoNI42Lf1Rcr6iycUGfjZfFYzfVW/D47dxsaCWs6h8rkj5GuApvI9X4VC3MnVI5dzacVCN9AMh/KbOwzAYLLS5B9JHNf9l73g++VZf8yMG61r8snEGh/g9Ikp10KocLTNDUxPU5VnKWNG5DEeq/sRikyu+hlDJn+MmV1lsVXwTN4dX/qA3ZGN5IIP470pD1blV34bzvCX6Qvrpiban5rmm82hPby1xc79Q/V1htoNoj28vcYW/SF3zAdkYvZl/v3W202YZ/vq/8ldWv7OooN85CDNasGpX67dn0SDWuRdw9eTvNAZCM7+gyTkHM1gwYzTrdQZ3s6zhFBPfXT+KQyLDqw9P9iKV2ycYt1GK2yVcPmOfarN/ZouFt5FvB9qLpBsO7hqFJ7VGOMw2dc48FOKt1RbYNcr+u8TX42fQeOEWMRdXGJjpVVOV9gAbxFAB9JODxTn5PCugA/Y/kPzdZBhx7QOEuxJV747FM6eOCPthUI4UTgnnYRCODs4KZ2DijiBOCBVhu266rAaAqcqzKBl6n8NcncgAK26ETBG02ywtXcdGovSOesU3ZNGPcc52tNtRThR03gFPIwczKF1dFUaxJW9C6LNwcMZEd2eTthkl1uhzcXDGHnb6lnZ9gzLVN2BUjI4veB5wXcS6A6s/KcdmU7adJerqVRC+AlHGh652D4MD0+FI517uTuwPhlW4fAFHXtZOySZnJ5D7vGURHgNjxufdbzrnD70fEIvqKQVgj3ohpHwS8C2OQtY2Q8xiWu+6WUInZifQtKBO9EjHdnZulYx60c/ELUG66ws/ScZvr4sXEUSgtPYfXvpOd9+HzxHkoez0dvVhwuT2dd1Brx75LibPxA9B9ZmI7OaPdowDQqseju4Au9pXuTnd3GBQffx9pr2vYrcseOsBOLvfuvl6SXpgtbX7e+Ign0kJSn8tSoxRJibokyaUkSRdccbkixbrSI4lK2nyVVbLZNMYmUkuJ+dRKmn0VVrLZdEaeADf5CGCSx8njJLrKyyTTYjq3os8xyGS0ys6k0dlzrPmtokCPvcvIQDpFPmKINPOji4y3ojFyu36OrI63I7UGq+OKJ/HNC2dyOBIXXfb/7vF1TcyuMdiL79ENEv8h00UQmpJdX7AXvzUznicnSCKHHLFFuErQRTCaoE0SM6aTIBxLrl1bsCkzqCsgx0UM/rSZKBcpIcFOCVWwmitMTXpO5W0md5IyUzxc3kveW95T3mPeS54xns4dyx3THcsd0R3NKZGaTd5SKqEQIhMmC6GKppIhUSZFIccm0yExJimhzM5OzdpNM027TW1N4c0OzezhKmwqd7K2iXaqdpi2t3aKtqW2l3a2MlG0jjedN5U3pb+FqRTRksEhjc7I4UZgJ2BnrDNr+ZonPcw/yT/RP8Hr5qMWIBYgGCAUwBnAFcAbnBNdF10XXRldEd0W3Ra5SLDI7Iqtia2LbYhtilmpsKXypnKq4sUTx6OSzaTHp+u3WJonuc95x3nNecl50XnB+cr5xvnO+cbp6N+Z3pX+HwAqgNV/8Wc5TQ5ICEgJSApIC0gMSP03vgoK8MWhM2R0dF/yQxCYKck+M2IWICod/PxQOoweK2mRyJT5pbQw42++OLZMK1+aC3NsWfi/xJHL3EvS/NJzRzOS4klkaIsmLiw7oPKJFi6sPaB5iBb8jZP27kv+MA4ZGjYaGhZ0vyibLCEFXDRZoWi/ZAEtuqsaI7r5N1zq8Gg082JcKuloNvMqXJrBaATzP04F0XTbumxaihizA67m4bzG2aTWUXqFkuPYbpLltBhuA4JsJinRsOYF3z5ES5Z8Q48eiCzUn/uir0aT9qVkm7JOMZtRGa0sarb/cPt9nWE23SS6TbRbf+u2YJ14FeZ+tNY2lGvBD1lDRma09Kix/t1tRNeSH/JV2DrRDv1N2/yunT/E1mgXvmT167s2/JBao3fGaIkW6M/ZZnZt0aU5Q7uLeux/3oZUY1mIRjYvWqIkxkSNjBiwvvzy56Es8ZFDAxjmlZ/UBalysae+2Ay4bXtfhnxS66A0xq79ojPgYJ71yaiDbAPTJbJlQMC8/ZNOB80GDskX1AGUOg0/Ss/IdfP4e10/cmGsvMipAZxthTfWoO9HcRvlMuC17Vun8kQagCkSmTfAsq1zmXVv9ET2Jgoin7eDeGlRIosVLek5MsaSGC31tC21FiyNuC01JpMIRmJ3HVsj1zSdqXnSDYaZdrUBDm/bNW1nmpZ0gWGiXcJlGq8kgTEjYA2Ah0/njPkuwXe0E7gBIGmtXVM5Y9kfCVhOggaoTqZLAHTjhtW8gwRViSlJKFDTIoZhAYrMKdHAH4aMNMACEKv3D0FxYrr4JJkxC2AdiNe7Q1Asl1YliWZMA2ixWw7i9G7zyxaUEDYWFsulm0pSAC6DCFs1mZP3R6+AYEBrh6gxrc5wNFC+Vd6YMY9WZ4wLUG1Iw5KYPkozMgZM3tUAauzOAmd3OYC7oAyQHmgZxAdqBXmDEL1L/Lo65LtEu1S7ZLt0uyS7NLsUuwy7xLvUu+SNmUyYTChMGExoTFg2STdpaxNdkhZHecZahltGW0ZaxryGvUa9RrzGjoG+QN/dR+DjLjzQx7uzQ2yD1iWJJIUkiSSNZyx+2AAoszsEHNqlAVaDkkEaoFkQB6gB5Aa6AiGBokEKoDEQA6gS5ADiBnuAkcFKYCawE5jIu/2p5in3qesp+KmgQ2KDLpDyPMlrzBcYv6sCVNmdAk7tsgBZdmuBtbsuwE5QC8gLdAcSBsODZcA0YBswDlgHzAP2AqOCVcAs3t1+osK0JEnJiGrffmLWyEapWkqpaUppuA+oKlIpvDEY7fpUanmNkowZQ7uCRk19uupUbnmDkpwZ48N8d00AZt6M3GGVu1ob/XqKYUn7jMRh+bW6D4N/Spe8SEl3Utk9lgICrRiVCQKdGVWhZCrkqKhVAiCGXRevEJOWrUSVTn1bvi5JNZy+L+X36DurYnZ5vOoYtUH6nZTLURirQna5jCpFtTitUvrZlMNR19H3u592YaxK2RXo1KwZ3FLUSxQzKsc19hh2R6GsCtQLGNXpU+mt6gCF6tVztE3yOfWSehXZxYwaytrKaspayhrKOpOqaQw29DZ0Ngz7tPv0+3QMKamj4FH6Xahd8V3yXfNd9F31XfZdwC7irvwuvVUToAkQC6gG5AA6AaGAf3QfLf0Hn1G1P0+YO9MhVj1KvRmFsyqql/NW9Zb11l2uEix0VCPWItYg1slVbaZXoVehU2GYop2in6KbYmChZaFnoWNhqKWtpa+lW01ZTOVJ4UltSWlJ9Uo5HW0f9R19HIUfjRhFsSoDJdYrLFefqAlrC6sJawlrCOu8YVLzDYfaXWq39Jv0m3SbDI8pb7BK
*/