//
// detail/winrt_resolve_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_RESOLVE_OP_HPP
#define BOOST_ASIO_DETAIL_WINRT_RESOLVE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/winrt_async_op.hpp>
#include <boost/asio/ip/basic_resolver_results.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Protocol, typename Handler, typename IoExecutor>
class winrt_resolve_op :
  public winrt_async_op<
    Windows::Foundation::Collections::IVectorView<
      Windows::Networking::EndpointPair^>^>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(winrt_resolve_op);

  typedef typename Protocol::endpoint endpoint_type;
  typedef boost::asio::ip::basic_resolver_query<Protocol> query_type;
  typedef boost::asio::ip::basic_resolver_results<Protocol> results_type;

  winrt_resolve_op(const query_type& query,
      Handler& handler, const IoExecutor& io_ex)
    : winrt_async_op<
        Windows::Foundation::Collections::IVectorView<
          Windows::Networking::EndpointPair^>^>(
            &winrt_resolve_op::do_complete),
      query_(query),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code&, std::size_t)
  {
    // Take ownership of the operation object.
    winrt_resolve_op* o(static_cast<winrt_resolve_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    results_type results = results_type();
    if (!o->ec_)
    {
      try
      {
        results = results_type::create(o->result_, o->query_.hints(),
            o->query_.host_name(), o->query_.service_name());
      }
      catch (Platform::Exception^ e)
      {
        o->ec_ = boost::system::error_code(e->HResult,
            boost::system::system_category());
      }
    }

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, results_type>
      handler(o->handler_, o->ec_, results);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, "..."));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  query_type query_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_RESOLVE_OP_HPP

/* winrt_resolve_op.hpp
HEjfS2mX7n7g8NFybsFD5O/m+ovTpYS75HoIPuv6LYfdD+Gkvch+rALWgdZUMK2rLuL6+3BeJ52/o3ZrL/zXOoYrTsc4RyvSmvZgezJtv8QZI8f35+euyF+bW7Z8VXluaYmIN9luBZ+geMa5RPyiw71zDxSdVuS0MO88nW58fz1F9jEuDzTphzgTlDxnkvKkM04JcUEPkL8JX0FhblWj1TypMXkBbQuRWuyjKY4dOIzmD3J2Ux5zIG6kR/eiOBdyTzdPQaSD0i/msS+nMFnOfo48pd4xhLdrx0pBzPo5HnFMwTl98kHG83yyG+6MV1Wc0xuP7pT/sxSfcxaXyDUDiinMEOcRNUpp69igfIDzsjY9X7uePudDWLm29BIKO8I5FPH9BOFou4xvN2cXZSjFl+5xrvtiuO7LI5vRTqcjUAl1bFKO8nknyPP21YXLV2L4es2jcJOd43DOvzjQZ4lwhmtA4e6gcCulfn9QuFfnMVnZL6/hQNoWbkyfvAeepv2t9fGQ5Wgv7YuRx3qF/EGkxT8a9+ApVDILxPfx1uMVoxZ/BNt0D4K2ibBxzXcHdFak3W1sF8d284L4WK5L3AFt3a51U90BETbf8BM5THWQ9xums6o1pCLjAt3OkJCeId0D2yDDoR/p4nOhXfAN95wWzvOiX+G0tBxDuPNEHAM9v3cHtTbOi5F2Ua3ZLsSz3e1sb7LT8m9oay3/1p2W+WewyYPNImETtu5uzaZdjK/NetjMoXEK626R7YkhTru0OLl+EeQOaGUb9+dae/MmsK271S/ivPvmwFbUXXss2tgv4R6DOw73BG97Hi6XfoNpIgyvkcD7TsBp6xzm4biNrYlC9wmKUQHXgRGskYk6HW0g1+m+Y+GQ7+Z2KW4Irl9Hm/aCB2UGy7ZCttMI06x22mesG44l2+mx2rgsbnWvdqCcgJeDoi2Lj7CLW3E5N2doghttz/gYcbIeGU7+CxzrlTj1H+o8ZYHDIeuRuVHUhsl1Q6zauigwk+00beX55M+wbOva0L4AqYProfNfq/aFOp62hnUNbftMbaydi2BN2RFke75jgsOpzIEztHfyGXM02RU6xjvwdAtnbHvactszNNKbljBuc8aQf5S6Wxlpbm/4meA5OvYmNVMdzM8JKqdhv5qkZKo3qfHGdke2VS+Q3Ua1mzqR13DR8j3VWB/L+X9PU5jNahafb44832tqDyWLzqdra+TYqyfJ5gY1Tp1rvMb6ul1q+j5M9repo/g8k+V53sS1GUXnsWszEqLs24ywKF6vhduMdPL3xfNoN2o3QnFv9m+r1XvZpnYjhm0KNBvXdHdAnLtt1WSbtoDtb22r1elH/KrTtXAHZLh7/AoXweFOteX61O25xh3Uzlyfsl33drIt8LidkSY7LU/Gt9PypOptU1vKNmXasVxVH1nW4Wy3sV1DHV51yrtvAGzdStN1N1xDPc119Pgm6uj5UeY6uqyJOro61Pp9xdPath6sUJrx3hLvth+frrQ3tw9dxJz8aLtz4/WlBePT5brZFuf7RAx2MZ+vXD8/ICTapy2CfbPaIp93RhzL9M7oDrO+BtXma1DenLkB1RZ5L/UQwsx5ES/GdVvkRUvnBWTwuYLCzefqhnPVa+cyvKPfYXhHr29efvu0/TiWzO8MLe3h1vm9T3tHb8H7ebb5/Vye75BF+hOQ/tAYPt8ZvZt7z7EzwrtjOgJHgSPAHjhHdoxc65U76XLzCwpygdKVuSvFeZFXsoyL/fI5hsPOl/oWR8nfSje+e01R8ZIifu7Q7BexX7Nvr9PDQOul07NfRPt7q2kKj32W54zTh8FTgCLb8nNpf6rai9+Hp8swsfDLdrB0pW69NSU=
*/