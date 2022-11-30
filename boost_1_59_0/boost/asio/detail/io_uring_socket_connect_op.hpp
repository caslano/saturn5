//
// detail/io_uring_socket_connect_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_SOCKET_CONNECT_OP_HPP
#define BOOST_ASIO_DETAIL_IO_URING_SOCKET_CONNECT_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IO_URING)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/io_uring_operation.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Protocol>
class io_uring_socket_connect_op_base : public io_uring_operation
{
public:
  io_uring_socket_connect_op_base(const boost::system::error_code& success_ec,
      socket_type socket, const typename Protocol::endpoint& endpoint,
      func_type complete_func)
    : io_uring_operation(success_ec,
        &io_uring_socket_connect_op_base::do_prepare,
        &io_uring_socket_connect_op_base::do_perform, complete_func),
      socket_(socket),
      endpoint_(endpoint)
  {
  }

  static void do_prepare(io_uring_operation* base, ::io_uring_sqe* sqe)
  {
    io_uring_socket_connect_op_base* o(
        static_cast<io_uring_socket_connect_op_base*>(base));

    ::io_uring_prep_connect(sqe, o->socket_,
        static_cast<sockaddr*>(o->endpoint_.data()),
        static_cast<socklen_t>(o->endpoint_.size()));
  }

  static bool do_perform(io_uring_operation*, bool after_completion)
  {
    return after_completion;
  }

private:
  socket_type socket_;
  typename Protocol::endpoint endpoint_;
};

template <typename Protocol, typename Handler, typename IoExecutor>
class io_uring_socket_connect_op :
  public io_uring_socket_connect_op_base<Protocol>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(io_uring_socket_connect_op);

  io_uring_socket_connect_op(const boost::system::error_code& success_ec,
      socket_type socket, const typename Protocol::endpoint& endpoint,
      Handler& handler, const IoExecutor& io_ex)
    : io_uring_socket_connect_op_base<Protocol>(success_ec, socket,
        endpoint, &io_uring_socket_connect_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    io_uring_socket_connect_op* o
      (static_cast<io_uring_socket_connect_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Take ownership of the operation's outstanding work.
    handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(handler_work<Handler, IoExecutor>)(
          o->work_));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder1<Handler, boost::system::error_code>
      handler(o->handler_, o->ec_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  Handler handler_;
  handler_work<Handler, IoExecutor> work_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IO_URING)

#endif // BOOST_ASIO_DETAIL_IO_URING_SOCKET_CONNECT_OP_HPP

/* io_uring_socket_connect_op.hpp
1dcc24uKgzWxaqaasj7OgCODwoDsw3g5KwImdgYyzuh2A/pDmd+IIunZHpeoMSycRzKbDu2VtNsjqSES8q/C9P33LeTejGVqVMXwPA/wLf3w+gCz00mSgC9YhfyOFiRREsJBv4O67SIFcK19awck+/Zd43TWBmG6FPaQZ5GXGJhMdcmMgcqbYbZgNpXmQexln7Fx9jQ2jqvp2biVcqx8TG6mvJm8RWyJ14rTiqLyefJZsJWCeWZHDooNqbc0XXvDpacAqiD9H/mwK7QrNKJ2sE2wyrAbkRsRBRKqOdU7YXXW6M3J/sKFm9p9CbBvfOU46STG9KghSboGYumUFtkbqonxhJxgHHrEyrwyYGekIzaFCqL9f5v6pygUB/UZaMa8CpRenoDCOUo4hiqGa0/1CpbACYQDQzR8VLE0wfB9D7zMm+oBXAzwh3hv+yiirFAT38x4pZ52YfiJZO1NIfHWQv/QwWYhuSR3p/ogsURin7yo9pr6QuKTJd/SwWrhiBTYXL/XQUrlIBOfRRT6VHtevXnmF56eq9r1tq6/ek7AFAtZJkmi7JqIowKR+4ilbNttuEEDshNHQcyX5MyXelbW5/Kd8BLtVoIlHqFDSLZiRbZiSYgAeY2qvQfUI0bVIYb8qceAzM2PVJbHnZ5IQkwIAQUZ8JseAHA23zRZHme4J7IAJ2wrwv21UKF5GG6CYxPq0TbfmFgewVQcE7gn8CfCx+bQ41PcAaBsuiMyReKHx42kAYFTLxub42nY+fZL6QFY5uBb+uFZ9BgDaAmJ91Ia9VklFJlIDrbKlYQzOrk9QqqzjRtBQzUfqSZFQmqf+QmhjoGOPkPx+iLA48EJ4VSTXpYVE5KOFcfks8QTs+s8v8PKosiFPHi8T1RE+w6BS5JBth0dE2UxIPZUx5R6ayAVC9gkJpK24khgUlSqyMoxkhVRWdccJLhMSIdrCwNPwwUiDGzBYnlOwhBt+gGFfriFftba0cFRJf5rXhZvPZNoRfuLUv8HHIDjf7YXSvrlSfrxYxx8wTiIxjgIwziIxBiRiLgjitCljYeSp/yGMSIAByz40xPxWZXcTIYcPUkWi2oWjWqWhMsaSn6XV8YCvsASPt8SSZW9Lsmyt16j49fkOw/s8TfU5Z/pRL+s5DEdiINFjV3Zvytyb8IrmBTFJNewb4od2rt3SESHdXrHt68GoJWZl64/yBo5BW2perWhxbfj3zV+/VCPFiEaHEWaCHj347AJqFg/vv7bbfXA7R4AahwDNa6BGodBV3VjB4mcNO4sqmEL5IAHnPLKiTPCCjxwt8yhSNO+RotUbhvT/brTDK5zZLeHwVXyWkHtL5zAnWbb3LUCknWcp/3mfZoWKdYbO5JVBMK0xSqu/CqKo/3xwa02KzgiljycPIxHGBeX0Nt+BMyhIO8yMmau+eKvbfMfwzHOT6PlFM6xBfhUnoGC1w2XAyzKBybZCT0rqz+DPtE4OrV9bbzvqAJEby0JynLHt5g+PkJTDBdNlMfe5Inxx6HmjznVDHGoLqGgXlcpCKWWLB+JGp2pGhjZZyp0/VZ34U86Sc44Zsq0zv3p+cX9zKllXoC56Vc+r2wttN3ohmfODwM3ugYD12qNXSGV9N1x5zmkG8Hfqm5w/pvVB7Cp99PFXq3zyqn3gGKvtnnn1NUdVaS7CaYINL9aNMR46HcBsF7I5/4rv/2Q/dHlf/3s1TBlIHv6ntiR0PWmjWFl2NkoN48Ry+tDB8yVFXYHgfzG2CkNv3+ckCx+vV9zimXDtSOs3Th3/cTWhfswhzOSvoRc6M6t1dqGsKA/wbpu/6JoNkGeoI3KD5penTcTFkshWW87In4B98nG+fMEbr6/OWbsiP8lu1qXuTJRJDRf9wWIl5EfLzZUOKShKgJLtAP+AoYbN2b6ePpjjz/8+g1P28E8AtXdkpuAs4NwsjvQsOOLB75ef79guPeOkC+J88V7kfDc4am9sTu3oA89WSb9tSCe8+RHryCentja32jn4Xf6z6zBSSJ9ubtTlzp32s/Um5MiWyQXsZC9R4JnppeYl95gjF+SLK5ZeJTmBbIDUuLvsPsHaNmUFTE0BuXMS9IodiPp1ShwIucG0s3LeWWyaJjfjw24uUa0KhqS1WAsfcPe9nMtbNWrwqocyN42du0pwyUYoDBv8FF0RJ/6jjtYaZ7po9FJsYErMOB8UX4nH8AQ9L7nm8hAUHxSWxXg67qqMyVPvAGgGnRzviHMp3NK6p3QAfgFJHZjaYvNokEABvCR36YijLC1yeZQT8WNAfEtsuv6lm3ZNbg9G0JXlh2dm7ndx2OscRsyV/qPre4nAjjsUVmRx83dy/hmCS2UWWky58Y/WJfrQat3h1eue/G5+aBeSehsJLPGuansh2908iwjiNxi9l36CsdDVh4dC87dIW2ScAe5KpxBZD1x+4/kQehsd8WP6ubiLobK9XcL02EoeTo1VCj5Ns6kK484Qch2Ay47LfFDj8xBuHYwQp4kdkhdTV85w4j9QzjDjf2/NYbkGCjoi58JKeqLoQnL60uwCIutiqoIK62KuwirrF6kQsaKhIKze5Td8mw2KYX3f51Q4vrdwc5C+0EoZtH97i1+WOdeTsnZPHO9ZHj89ocYz2L7PQvMRp/tPMh6P1O8xF9BMe1L+32iviLvGoBiC7nCgR0UnZXB+gYzq4P1XTwBYRWdJmg67k3dwHu2z29ENb7Gk9qO0Sag4XPEfBZ1oI5ntZ3UxIA+4YuQFAuzTggyb05Tuo/0/VHwgZReiopPWTPSnl2VESMSQOpawZuMFeKVLWeeZ6YgR2a7wlf0lvNEEAPBqSMEK2yIiQJxuh1kyWq7QWX51nbTypLWdgvbEs/2t5Ylr+02l+Ub2x0kdgxOsB87UiNYmh2f89KaHb7RneoDMn779yhYpq7EKASlrlRFKKeuXMU30dU0iaIOPHE7g9J18YrNTamK0E+/xJWhiIJSFGGFguKz3rY/0vMhXvkSpKPyP1Gnk23guCRiXOT4xI6/edoQsw6NOaMuztvLTWC/KL5LGMfxHzRmlznGfAAYXjTcpSdFbg6eWRLvvwSxm1BKJWj28m5ZQkfBfdH86cMqix0V8fV1lI2UBlriESjJckXF4hRJO1O1kDe5CbQRlYfVzYYyfoqfjchCKixG5kORVuRx44/KIAa+w+PrAqSz+t3HNZi+AcUX11MZAB35aBFG+FgzyIGGbbnrr/qMloSQcAmCaQsxJMUd/QIUxzObA7DjWXEApNzKDeVTxhbcuNqWdR2qqFLxjqKvgeo7Zjtmbh+ihKWZw9FpExlMsQ6B8ngRKAAtVnyCxEozSW6apd4yR6UarrXMkxGkhrCVUEMEikbkNmJpOx432Kh5YqA0XnUXQMk6J13GmTvMOm7dXHr8rR5ioTdUG7b0R2g9q6EJ3rYJQnNUspZMinF0ICrejAUgm7WCJq7D1FKF2rt/P0f6NBRdOGwdubAzad1Gu1fXBKXwyUC9393XO2c47NEmiK0nwWTYZbsFLHAnFCAU/FlkqIUX55LrGT44vGfK+1zoUeOZannMRcr7uWGf2Q8cOfiWTVrxfeIgJ5tE0ve2AnFGrKZtLNf2VqN1Ju1IhEH+6WIZKZWLIh/pTlJjdAOIQMgmNsn32IHhbfeL6DvjR8ogzOAICfZEK73UhrtU88/rUd5xawBsN1lFqENK3xJBmQBHR3YqDS4ljjVH+2bOtQzhhsSV4XdpZg09fABGdoTM/omZXV73BL4FwZEsu0luht9GlUSZ0oSZ0kQOQ4QOQ0QO1HzaCrw38l6Mydu69At1mhkW5R7D6h9ipNiJIpNAukXwMVL2+7pFjsPkXG6M6havwpVRXeNVuDOquw+TN31kVFd4Fa9lDq/C1VHNYBinyd1RzX8YB8TrNbS3nG44POnx8VhR5lW4HSvavArXY0WdV+F+rOg9PHn1WqbyKl7LXIZhrlwZRU2GYYB8OL1nulBjdVDQwzBviJDjznRDflhAk8fAfePHycu1gL4XwDENsYCOcWfsFR2GeefGKBpqAW0eA0frwSgabwG9/ZryYhT9WQcVRoTMOlAHJfEqxuug+l/FK0jxKkbroApfBfxQEOqHoyiQ6yQt8VnUNuIkIHs/al1uEiC08aEtMXuGf/BDtUb2jN8nDv1SvsJrSZvGHGDU4sGkbfbvqEUMm8ZJj6FdRhvHFH6LhvEPmQ3ZdXzDHzLds+v0TqMmfCeXs86iJpBsHJk/DlkXc3BXZtW1TX/IpBGwaFjl4H4A9wYTZtaCnR6dnomjJn5NLr8h+lm3stNDnJkpiXbx2UdfkMUYp/ayBdoFl2Rr+VE/gCYIq+e7yKBY+qj44npdOrKFezcH9+uX8REM7VLIEGWmfGB/SIedEOcwQ+WQISLIHB7afYkcpi6OwvvRLRxR9UnPA9Y3oRNY5dxDKsLrimHzS9Gvlx9p0eVRZxrkfnf2USj2BXHJKkDEkCUxFZ06JlEl9IgUotk6BJz7re+RhB/kbn/XX/6bpfQrrDIKLh8Xo6s970T573el8LovIzarVISHjKn6h+o2HfN8zJ41Ctl76nsCSQ0F3MHNdpepHqi6mUKfv4VtvzczxTXNftssRs2+jJBdxlpjsyYgYZmGKXYo/kmZaWXIgTXjt9yzUgZM1w+dh1qJQxvdrkBgkkPv1Kc6tFv1tOCdqvcn2HCui/BYOetOtYjZQkgLehdBiJUzDyd4bw2S9fkSTqQlCvs2vZiPuVf8NYhkWeKcoYeQjT0X62vbjp6nQtpH8oW9y1lmkzqXmZ9IloayWAp1oEiwO0+hyBqVkMKa0ifwKz99qB84FpklnqWAYPEVA1Ziw0QwpXEgeVrdQOiLm/w6zrx3RUembDmN3r+LmFknES/aOvS4Gz21Dyn96YtC7DnDZFdgQy3eYyABnhQzLIW5vwj1CoBnOr8vXXCYZQcg6k5UP/LQKeAzGZFmhHTdST/CFLZ/WL4ixMunGZGzEuvwPdlt8W/+xXCScDJlH6zxQLL2kj7HWGqk7DoJyNpxLwFmxbmbT37gI3DLGfMVsJGZ7M4ycUOF4N/z37Xf3d+BA8RMRDahNkVN1r0Take9U87wN/vbyFvknCPXUduM3B6AMaPZcf7qp75tS7sba6GecQKcx9OtEg2o1QJAj/2NfJtwMiJ5/iRPS6IGgV0v6mw9mwZ3r72SbAMv57U2jT3j7LBsBI+a/c7GS9/sVM/uosuFbJejgOA9z2we76DOS/dsk6PO6kuE7J599jwFsdSfzBzt44fsHWOPzFpd9H5Mp3PbOYu3wFObB4kHhGOSVpFmke7gk+faWxq0cUHe/S0VBDTCQ599UXBIw+YBRaWoq9uK5g3p2cDwuX4QfVS3gqjEGZTJnXd5KKe0PnUNlss3EtEDlDh9f91CXABHEtvJW9nqgl/uJ6hNNCepzSYLz6WECXPsw6kclDbv5J38JmezovlYgJ2Zl2qTKnw9kG+1bLLVCLITYCmj8gnYcqPfBiDZaj55J8vTu3VMUXudVnWHN+oOC/lC8k7S4eoy9t3Bcat4OvY6HsYLvk0MTTqi9mdh8/dt6gxH7GhF3IU6TLLVg0LdTx7BHU/ocfp9zwVPEU8uZyIft4rCYInKIahMTcUpj1icHiS9Bqa4MbD7zkegfLcH+i5oTbTtR77zoVAduKgMWBf026lbMvEbuQfTpFOhyDgW0Z5b7rU1S5fCLpRb6xOuW3z/665VY6vadxqYm2M3CS7HwuT+kwitOFudQsFBAWc5g5uTsPfxLoUfjbr33ol7Ta11WU7tdtUGrzpMWfnXbgaenWJ3aB+3By4Nfj5uXwsK8o40ojnLQC3vNILrgOngP1E8ZtzgM7XxsLG1MbXZmDwVEDh2bGg4UG7feSDy9w5o2rkkyl1WOfExG04hUjn1eVO2573etJNPNCiA5D3g5bE6YyZzGnOT++vHXoQQgbcQd8fg8dC2HN4nHgYeOh56nqINjWd94rRrs8XMXZ5P53o3PsU473bOxMTnRM1dQ4p/NNP8+Lr5plgpJC6go57uunGVmFSlaV7dM7k58n1XW3Ylj7RsXDCkEOHa9aPR2x+AxI7pNn6++4mXu2M47v0xVk9iSO3L/txVoqHfYbBaUIjCBDc8nvuLdkiiAMAXGBCEoQftfgoHZHdja/uyLnP6prKbUNKPuQ3feptkpBjIXx+lnpZ+G5/MqvGiGETeE7c28sRq0iNKTMoxwugGR0dVG8cOJvdNd6SqTVgCHAEV2DM75ZrjeQBhlqiQHEO5jVDIkxN7aoDSTUIkQFBdeTcRruiT5icEVSllauQ+hjIyz6IURvLIER0glhu9nrgyhU3c3AgFkNsNhy+Rkcom0aW3MjipJm9JTZovuYz0YQTaT6grdEPWhRxhhIxe40sFpZxLSct08pV2+/cNaa4KjbCMKy8/BEj0o/JZkfdMx4HQlbEfiZHS0vTDAeyV2P376lKHA/72nEex5jnQlXl7qLAiz6zMPnWGFMG0zIH1apz1nHQj24qEcImSrcY9XmAWd+HEAdUV4j3lL/HcApU5G1vk1QRByUM7htUMYYXcQidbg9WY5tKpOVxALpAFjAhJ2lUlmSgm2o+8orpnD/zSLW9SWDtX3UhxIikwx+xBEBjWLbdZ4DLnDbBeTfYq/GWHBv4AyXJOTR3DHUsFpI6mjqSO6QB0RnVGdMaWAEujDMAj4JEUDQQeIu3WEpAY0BAQ2anerWVMtUm9ybxJtkm3SbXJtEkxkbg7djt6O1IJ4gI/gWHBYWAJt65ObWOa2lQeWexZGIiZb+Hjt065IM0NRhFqEWYRMhE6l/jchNyU3Pjc5NzE3FSTOJMkkwSTFJN4k2STRJPUltE1IE8R7KzYQVwSlqRq3xvchPfiON9Vv1B7mAFcRl1GXMbWQN6gW+AtCA2IBiICK0MofFM7DTYoghmDyYPpg6mDmYPJgumC4SyeCHxrH6sfsx+FAlO7ZTZLSabRDlAL6xKqOdXxGZSSSuQ5ittmxe3KG9VXaZ2SveT9qWQu6NrkEQojZuZt4YnHnS1iL+ouIi7KL9Iv2i6+XBRfJEMqIZmQDkg4pBSS2rYpaErMiZY+wpgg1ZA2q3ZQ5KHdTmuU7CzvXRw+q+HBnUHAlFQ8ujLKN9o26jsKGYUb/TLKDiK3anOrc4twK3dLd2tz++JW7Jbs1uQW7cbkm3qsrR13m3yUdJRM0Ov36432MY5VsVtlvXybUptRm0RbYoCoMKUAgBlMDJFtU2gzaJNp02lT0auucvUaJ/HwOlmiP0q6HoUHmRUWz4zaOjWyreKfRN1Ix/zmcItGlZYpTJxZ2Tf34GpfoZGdFz/QbJKNrhy0FydiXKiQmM8/ZPVs5RcnKo9Rl6m0mK875PXs5BfLLlNWj9WhqdSYLz9EPOS8lrym9Gznl2hf3He+YvXD74rakCYprI23CXAKsDjm6ubq5nj8avVmXmFhbH5sgWGeYaFyvnLBYd5hAfvQ8/D6EOUw+lDpcOKwWk9QYRSjSOiXTHCeyGz2Fc09x9OXZ+ng0uBpkQOTRppfKmjTYVfvT+C6sc2wHnknKanTxrFK2KMPGnk4TC8SBvF/fGXM5DKP1sNcTLoxm9B1X03drcOponIY1G/grmJyGF5t
*/