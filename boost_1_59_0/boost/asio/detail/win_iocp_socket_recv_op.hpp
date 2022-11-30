//
// detail/win_iocp_socket_recv_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECV_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECV_OP_HPP

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

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class win_iocp_socket_recv_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_recv_op);

  win_iocp_socket_recv_op(socket_ops::state_type state,
      socket_ops::weak_cancel_token_type cancel_token,
      const MutableBufferSequence& buffers, Handler& handler,
      const IoExecutor& io_ex)
    : operation(&win_iocp_socket_recv_op::do_complete),
      state_(state),
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
    win_iocp_socket_recv_op* o(static_cast<win_iocp_socket_recv_op*>(base));
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
      buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::validate(o->buffers_);
    }
#endif // defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

    socket_ops::complete_iocp_recv(o->state_, o->cancel_token_,
        buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::all_empty(o->buffers_),
        ec, bytes_transferred);

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
  socket_ops::state_type state_;
  socket_ops::weak_cancel_token_type cancel_token_;
  MutableBufferSequence buffers_;
  Handler handler_;
  handler_work<Handler, IoExecutor> work_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECV_OP_HPP

/* win_iocp_socket_recv_op.hpp
Q+SAqgWroBWtTKbZsLiUaggxjOneZsksaf2dd2Ya5QFdnZaEMXR76ANSbJzkJRmDUfUMzsEVECc7RL/T5svxP26fW/aGT4tOJiaKteihpF0nNRMZpPF2K/ilDjc/qwqIBKVuU6hJdI4uFdpmsIrRL27AR2Q1bVhpTmOe05zn5sZiAyHUqFFz3cwz/Eo1vbGDBti8bNmVK6YYWE1PE6sOwtzmyVu0mGXs19HnVgrUTTpuxo5rT3RYhkzKWBEezWM7Vg50rTEguWtoGei2q6vFZFsiFS6Gpnntjs63p7aplH/t+p1thCywqtZf3ImKUqjuV4Y8plcK0TXvBVcGLUmkBmgxZa2S6MGhEbPcN9uniuZNr+Bi2WRn3jUTQ+AsvXX9sJScCmRx6Nw2FEuVVaG6QLs620gYbgdWKml4axElua4QECn9bYDZqZ3zjRi2H81tPkfJOJ87y1mzseaFyV2efVr72gmbvZzWdUdsOfUO1iLfd8Q8YB7s0vF6GUW+jVzu3aij8elN/lLVm7fmMo7CIx3Gykj3+zSqnhMe65Sq9osx1u2V/HO+Y7uymKYYZUzopbjXg81vXWObNst1/4XwNGB6fq/NnMGDX5mWoCmMcxrQnQg0IABMpSXPcvveC1P71qUs3KGAjzqhTZjPyu6rfZ6b6+SPHsBjqOkyqSYEBy+zMSrMEZ/7ahqr+Eytl8u/QFKkoeGzkxNmdfYd24DDcd9mBoso46nDOQ1G+F0uHgFPaVkq67xmg6om7RWM9e1VylFmA6FTmCVMU3ELAjcmKBdh99IsOfGLWWge8HFRqqX794RmkRwNgHLk5FQt8IVwzqqKHaSlzaqayxsTx667aWu4n293PU4jXTS5dldZbLkoudhMsz7s/piLakC4hLrFkkW3nSn30SlNJszyFWa94k1KryRnaF1YZQQw8+daRycFFSe5O1EYEVa6Vfld1pvokTgGEc/MOrOpSum5CQzM9DYXCkh9dtsKvsnNpIZyfpKTd5M2wuU3ZzdxmxCs89OWBm73QwrOAjkOUqxbMb3PeRS3k/rneubPz4mNUrsYDAVvTpTogxDTO78KgriKlAfpLoJXEkur+0AEQPbPGZZkiAuGPcucBHEzq8pb8jaCwjxfx5BilJO++OfkmFUdDjodCpgK7t17fGavPsjlVAvzZCnnSbXtZs+zr0fi9dXuH6phEAGflEF1XEfpa3R+Es17y32XjkOp5W9tbbJzJ8ucD5/UHLYPTKnXQX5FGPq52k5raRSae/xzQ05Kgof61Zqvii/8J6NojnrHnJsQbeLOAwPTXRHbdNrK3sS5IO5TCiYaQAuvzGsQ8HEEeHelueeDji5titn5/bJvto4KroizA+6veShTQec3nqMhyNE5BVvGd+NXIslWmKH6TETRAm6hnoHwL5avSXCAn0JgQ8QTlX9CUK52bZ7Hx90kq1KzAv3iuMFqMqnsTBYwwrr5zDXshl+Zn0cP1wJgAaK8QPwbAkSzaYwcezHQumk0JrQdASh/9SGvGxtPaaCGVKg04IUfAop8vkQjrK1gX7a9QrHuVftS7z+JCXeJeLtaaLZYNnCdJVn6uXW4NnCV9Lgpug4DkiLoUDFCMM2BEoAbKMRG7zMfpiW53PE60fDqlQwQ/YDAE3OkrlgU/gk4AcnspML0cUE4V3hXgi1WTDgqiD1N/xfHtEX8G1MCZ9IBwTVquloymBYFgIgbZULEkSOjOVv+eSazQ9dFspKAnvoo8QWzsDwWa95j3LF3nen1nLggpHJxK+SflKOHJXkJPh9Ao5XkPam8NXwt741KtvdRR0nbGhj0Dn0g3l7NgMFyGopfbdO9z3ONnXa+C5wvW1VoBqIHwiTNzDJcYdwVH2QtfrpBNN4ZgIvqPFh2SCkzPIt8W17Q60W+blioOUF5Zkv/3l7LeocexDHAOQKN8KAGRzYwbvPCp6bah81wtbA8DzcxcOckPhLMo1jJeBpIUHlQfU+EKSvsPf7qdwTcdf5EgU5BrD7dAAgs99O7Zzp+PP4B/qE+LD4XPK2rEedgKZpmbJw+3CDfgCav06OTGe/Ag7jvArTMeOXRrGIBYJaaX7k4KyUSo6s0xBWt4oYzJFlTPcbGp0suKhvCueLOKo1A9q6YkySJg6TM1YNATsGrcsouxUe53O9XPTAxRDfc3pMLsNnR9OKmM4tQNmFFYQWDvNeCPGnooR1TV3pCeP+19Y/YVB+AAHaeYC0jG0oSrov33CfOqysw2P7vHQpGCj76A5ilJAvMXXg0KuuFcycoBl/Sthp+NkpAwoWtWVfsu76VrGbXKwELysQvyMpj3BuyznpeV/mc9GQILVufopyS+TZHJ+juTbdjL+9gdYtdkp+cexVQa2b1G8WdNXLNfvFwViFU0zdEhiG0Iln3U/zVeLdMnRCD7mQ3gKNWoiF9cOb53KpqsvAPfnZ4Z7i9I398yZAb2nUqGQrAgvPxzhggLwoXg4cSYklJT2BMJZbKksiy3AujA3kTTeToI1eMzqpp1deIJFf8hamcLKKb3d8TCAb4yFQYeZuazVBNZJS2AJ2G/zoUfMe8MDJzJXB5/jOI526BmDXGyVXZn9PbLzs0g3hQDV+twwbC3WnOQmG/ZkNYq36olkGJXU+T1VamuZfVrCpwkky9+WKL1A/WaBcNe/zdYe1mF8qGxnulucx7HLEfv5Izg4HEgy/m+vUi5UoolBeJ/ti0DRYk60ZCSk+jJEQeIru5TDfeR+CrGfR19lM/yX0H6Se1R4AHkLWbOxtGIk3hWzzT7As3Qudb+tAvBF8Hcfj3H4h599DNB1xCnd2mPgfyu1DuHF6QIRF7O+mc4QM3LLu/x0LsNSN+guLemBjZ7leeKY3tBsY7uzIGac6hucP9Fvpg4dz4dYLvtQCBIeKVwpE57yRHQ/LPv4J5C1hJ5XnG18tcwByjrowiMRUyiwIWwQK3a211dpawBgxyQRn7qPXPbjZnHEnzOkcn6iK0IP8TqmqHiCVBXvvNp6ek7P09RA+fLz6OD/6kzOM1oMxLO66essQ2wwvV/xo3wm7CDjywz4DhzkN210q/fKD3R1m9+LgKZ8FjR6968Ie0DtwCzj6d9vnb2/zASn53VqkOIopFnQW5ARD+5QFG6wVty7V64fuzz3FylQWa7kHxJiGTlsWUg/eOGjeYoESOurbmLsEZs3dpuu7xJuGznvJz+6P6rwzgK9MJ2B9z9AclKv3Eq46jt9Icn/mHra+G3tpJBEoAE53Z1DA48tg/Sktt8AXU8Tb0JGrac+aljZOxTCGZckWWaX57ZXfct9/4lzCnhmYUEnkfmYxgyMUlpqSLSbX53Yba5568O1ilZzM2wzt8kwSx7x5njM2nGiGFrg7UfopgTaHhsHkpsHjdMgYmf0bYESXnpjqdhaIpeiM/DexrWzK9d8bMdEK6hzibzHsiaKzrseynMrN+hHBPMWsfGpBXAEsediVKa1ZFWe8o15ieCrfEO2neeJL1KKYFNuXCB/43PygABzMJP6x7UD4KEyWSJoZKvL+jm5zy9j4XGTF3DNHjqxnyA0cQh1rwNKYNNjAZh5t+mkPfamC76bHXZDzcPsjZhoeCz5HQ8aLfWILAn11EqUQdZA6I+3KHj4MEMD+G3mmQaKTJJm7vMOMcd1OTG8/vNlz9nMv+ujreQQ6yiFgvKw0abLQJIC47m0m56g5Hy2ebd5PyG+eJF8S4ViSK/uyC7ooLs2Td+h6B95EB9V4faPCoRcMBSiz/4YFdtlVoPyeT3owWBUS8MaKQpdyQaS/CuPXtaHTBZ4Qx6SUVJxhEaNr+wjydoScUX/xWYspjYDWUlJcmlZyWVNghiWCTrATyQ/M6r9p7PTGU9GuX16KPHOJ7/r41k3k/h/6BNj8+zg+yAVQsWo4ZjFkR+q5GJ0vhNcy0E6YXrtGK8jC6nayFzWBv2WZIeab2bfPC/k7l/UX8hiLp4vxmKGspJw/3H5L9wR6YJkou4+iyFKPcSoS3nIegEc5XBZB+vS1yEHD858fENAFtBbD6L9hUddhrHAGAv2dG/hAYSI/rNN98H54/DhJxGamB3m34LyuG/JU5sQLqATVQ0LFqyPl7kA2+GvsFCWSobnPM3E5ZL+YZqtuaTY6OHVzfKBv/3YXiKcndLj6MGJ50MKvufMsEnlSea2fgKyl+7lasjgcjQlQ+jV3k7dBmntR56WJ+Fr5vXoQDSLIO1zoiGxiQdkypbuxtaOyhbr1g6dq+KgNVCAfeA4Pm4K2l9qaQjr61RZtJjq52Ch1biOfZmwcDLD0NTiwH9oMO5r9jKpgSoijEMnM5QaUrFSAM2VEVHQwXoTFuVK0DsbgvuCuHf5mz2LiWvwgg7W4Zg99NmQ1P0+y2QhuiNc4U5zJ7AWohbN99D+ncdT9WQ+YPXRCCqM0kT2DsZxWZV8CcyFdjBevp356tzte319tygGOMQnC16e2NjNOsNFutJJ7RtZWhtaFBe3wrDN+uWFia7nnrsAZtMwieIbIE+v7q17X3n3l9tcLZqqu1W+ztn43vY0vmYw8GvnsYdm3vSEhkrxnJr2QFRo98Tx2HODYJRVaPjo9TJ2NuxLMy+sXU/tdXxVNNKeVoOX23y9l+3mUyeoHI6dk/KBbkaWmsBsAXKBfnywg4B/fPN//wxdT/PQcKmHbZCPT9C+uGCJcWOylxHKsRM5zMTzFyY/C9OghJGL7y+I/pXbWYKyYzeJO8YBU2xVOyG7K0dZwWbi4uXU75roPcFKZnDByboKRqlHI0xIUHD5sTaN5u6VNjp+vKFVc8AoJoYy2l5RUAbVdV338CaKis4045/4coE9cFKUxRiUvUkCcjlln9gMb/+HojHOc4OPazVh7hXyGMbERD/LZV8nvyPmw9N7YxbSptot8KvSKiuD/+DmqHrny71yxeB1NDMORAQlhIDuF/onHzoXaAqjdRk/YUk6rllmXtzpxtmF15DT4pEAqreA24FFqT9tuoiuzZ6Wo5luz3Rve9uk2cnQcVPuiJHFPlpOUy3l3TCz0EaDoyd5Cgdc0R2dk5SxQUsso7Jr4fXUmiTCduXGPu6YP7sMons/RSlHxdjZnIeVVLhm9xUfD4vH0vHHMIU6h+xBamu9IwOtJb4+jz+pyHhOu9pRyTM4OUk4iYXRnMmrKxmOt+XaxAQW2IglEPLHTr6IkloT1A8RJf9A+H3FPfk7nhoHsno5hyi7xAuRkm0h8ywfRPaoMQKrmPX3o3L/CSCY+g5FkR3/gTqS5wqxpYVCFi2VLYUoZNvhcCCMVLXl3daUhQFbjwYzulqr5NYOJg8dKrTS9rR04exX2AWfnkwgnlic1ybtqZflLKO3hNOe+IVJlvHC2MaydCJ7OA7Z3fxI09+MvEQxOW1vBZ4HCwRCVuw9dfp/aS4RpxAZFtUDitQJTO1YCJ/hLDeXpaEf4f8zwTQFN5NF4SDDdFGTBDpU4ZO8ElYTRAY6fJteuIBEZCxLcMHw0ISxBW45qGs3q7py34uXDQvQJaasRMu6BWCnNIu9OVuhvLtmClrxd8T04YCFEcGTibC1XzRqGdonoEnpX+CHmw76gIoCD4LokPeDJWTnkzw8ui7fmHmSX1rR8YUzlVeCDs4JB7/G5PQmIopLjmovo81NA8jnwBWStpdGqd2WXCnQbxOwli94v2/k+uFKWvxrKWEfyylrVitqE81ylyfLR0F+T8YAIB4GR31TIJmwea9tOWgPGgnERmYw3oHyCFE0DK4Mv6K6gNnD8X7vRiYAg3SnsZ9h+eqVdHfc+FN+ncQTeUztRWcoh5P8BFhfdR9E7UQ4iIQsrGDzD9K00CcxbrRer0aQ0oBwApyRZ6VHsuHWE2wMFOEgF8hhFFwM7PajFDOPsCFBS1ts3tiwADUA//JtZiZmLDCP8jhXclh7gdrTltE2/FPALBAxlRAZhQIXoYDdSRmuAS443HI8DyHaMuN/AX6Ees9SvOmNA5Cbq5knHQRX3j9qQkaBi38hXq2i5uFl6qknDeDe4qchHQzVR1wCt/D9tRGcqgKlB0tX28HbDv6NPbqFsZy+N78T8mB95QZLDPbRNp6jqCdq4YqwzDQTEY0ryS7Yq9qqCWoZZxz3enWJjr6ilPbIfI1gFw6gZC7VPsILyu2gf+iKBdZCgQdLy4lgxZVLLgE0A9GalhxgtnpeqMSN/SSyXq9XAeurOkBkjjF+cV32E91NuLfrlkFAAocjdDyO25tZtEas5de4E8GL4HO48pe7aVQcVGEuJEqlO9ZxEMIsMj+MV6xoBxbYW3BSXfo4wavN/Jx3x6KQVpf1jXahnfWnceh6PxaRJdZDQwxtX48jw8hX+3oOEOUW1zZDjbiN6iLNPcN/0pmrCP8OuA0zs/QB8LcdKVURgeUA1KB0c2eFzaqLEMDd48bAlPdrPczD5j0UMGILtbJcmtTvZUqpSHMAk8WJcExztv9+a4QqCPvZWJKkAUcqsXzFDfRnNgJJ3t0wbNuQLHb/L2Ka+QjZY/3kZAYwGBaqgc7mt2UNAr2hizUJvfYOfeELLe9RTKvTvnxXfCFiPBb0732rkvhUKQgNodqf7PsyOQTTEi+f5ZE0yWxvsGXJvJ0x9ywQ9ruY3zGXtfrvfmmdZ37J6aEpv4/eqj+d7mkjLaJRDgisj39yd6hPiwy1UPt+FW+xHqGGrFkgOz9PZTOTOi7VbQPb4ZLoCA3Y6Ahou+d8TnMh7EeBfFvu644g5+mzsx7B3CCpMNnfnNlcLE89/ViTQLV3+knaP0zJZuW/3aO7815g66jEtmzqNxnzFlRus3JJHZ7adF3QT5FyJWRbkaMDuKGd6BNqvkY3vY0P59FsEm7968PQPcwc13gQ6PkxAuSf84chQ0Ug4zB7+EEu7RoyIeNNo3YsTZ0JjpHlKr2UpSAdrYqeNpZ0pxzuI06RjISX2rF5JAXW68PuoG9xKrb/RXDFJZ/qqqEriLwhDaYsmDHKXuSakb+KHdkfz+rBgjRAQlhHnPh71LNff1T9ypQKaMTToBVOx2qWCtzLZsJs9prWMOlaZbdta0oikhQwz17DYnJapN2Pp/WaMNWHRuff82cPDBUSAFGc/Slk40uSkM2/5Nd1thv3LZodTjRwWCAVpe9UQS5+TxhYdy7ydI53WYkcdn1XXlfFlOoGPj7vaUeqwe/IDW75Tyy54k12Qg6wCI2jwIZSMuuH1S3yo50LRjXmCzQQgevsGNDVUEiHWSs6eCHEoea49Hnr4hOoOYAthCQQAVrFwH1rfZoJyxQzhHyrqkwzYT2lwjqbguN9anon+M4wyok9g9rxQoHB72p5n4CX1KOX5QHrlr6xReGnGw3N7XV3LoLu+nYfGjzqifbWrdaxUUsl71koZsYCG7OArOSts28FmHkhEKAzWMWt8cWO8E3OP+Fx+4VRY6M/EyLdcTG54FdYJuu+O9pcJ3Ec1JepypRfJen+uNNuW7kLdltWBLIsyCZoCFKN+beAXk4MeX3BY6I6oLDy5pbpfIDD+ifuYIcZETDFTe5xVocbiBEZQWbBcyh+yr4AORJnMzgxokRupdwhrsdBf8BEPE+gX5vLZcB39HTCw0DHdfYrQ0TqlKoyb/Y4dSrLL9th2NhosFjAxJXyVpd/jZWV73fbIQ
*/