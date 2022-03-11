//
// detail/reactive_socket_recvfrom_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVFROM_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVFROM_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence, typename Endpoint>
class reactive_socket_recvfrom_op_base : public reactor_op
{
public:
  reactive_socket_recvfrom_op_base(socket_type socket, int protocol_type,
      const MutableBufferSequence& buffers, Endpoint& endpoint,
      socket_base::message_flags flags, func_type complete_func)
    : reactor_op(&reactive_socket_recvfrom_op_base::do_perform, complete_func),
      socket_(socket),
      protocol_type_(protocol_type),
      buffers_(buffers),
      sender_endpoint_(endpoint),
      flags_(flags)
  {
  }

  static status do_perform(reactor_op* base)
  {
    reactive_socket_recvfrom_op_base* o(
        static_cast<reactive_socket_recvfrom_op_base*>(base));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(o->buffers_);

    std::size_t addr_len = o->sender_endpoint_.capacity();
    status result = socket_ops::non_blocking_recvfrom(o->socket_,
        bufs.buffers(), bufs.count(), o->flags_,
        o->sender_endpoint_.data(), &addr_len,
        o->ec_, o->bytes_transferred_) ? done : not_done;

    if (result && !o->ec_)
      o->sender_endpoint_.resize(addr_len);

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_recvfrom",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  socket_type socket_;
  int protocol_type_;
  MutableBufferSequence buffers_;
  Endpoint& sender_endpoint_;
  socket_base::message_flags flags_;
};

template <typename MutableBufferSequence, typename Endpoint,
    typename Handler, typename IoExecutor>
class reactive_socket_recvfrom_op :
  public reactive_socket_recvfrom_op_base<MutableBufferSequence, Endpoint>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_recvfrom_op);

  reactive_socket_recvfrom_op(socket_type socket, int protocol_type,
      const MutableBufferSequence& buffers, Endpoint& endpoint,
      socket_base::message_flags flags, Handler& handler,
      const IoExecutor& io_ex)
    : reactive_socket_recvfrom_op_base<MutableBufferSequence, Endpoint>(
        socket, protocol_type, buffers, endpoint, flags,
        &reactive_socket_recvfrom_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_recvfrom_op* o(
        static_cast<reactive_socket_recvfrom_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->bytes_transferred_);
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
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVFROM_OP_HPP

/* reactive_socket_recvfrom_op.hpp
1A9jgIZ+Vs140mN9qT+qRiC4OZMwj/p482TXWDOnQ/st/o9o2P+4Bi76gbyG3HaRzJH/QIa0cXHxmulgrGJE0zPCHik7lGvaA5Z7vXlJJzRAdCRI7zagqVXPo0BXkReIeTOyneFw28r+V0A1Bzci1u2yE/pMBWAvCcpwms0v2SH4J4bu0PBrX7jTmLc2Wre6mdwKQtGTfYBiwJib2hcHS8iu8gnVP/ri65n9l+LWOWvyebvNv5S19mwVQMVW4XEnE/ZWMSqBlAFnnnYxt9dXa1mJtTn+20e+2KEstj7igoTP1K1TycUkW0eHnQEkjdmZ7P4eYB0UmXdAR/dK273TobUBHnuHYEjDlMf7rkum/3dj3FnPiTSgMqDD5oWwS2Fn+EJrJNQlGXwCLY/oShyX8FygldVq49weyveiAv9tC04PpSxUTWg50PwXGBwOA0ed/4ltNCxUC2R6GaTwPG0VwuxEtCTxa6+rwHCSlvsuO4vmTce+0kafSdXP7RKRUjqZUWJOk+eh0+hMtP42Q6hpN5dGpXceVYc5v1wFmmorCkvWBdM1OwyqeLxLOeg5MFr6ksVRz0ciWHAilvld3u9WtMtTbmNP8f5tGZNPrcMcf8dF5xa84fR6rvknqXIMyT085uxW09+hPDRM+I3KIhAYw5ErJn3LUypBzBVEnf5aQdtj3rm6x2dJt4P1MiJ7MzfTbjbQ+HkIFvKxq9GLu3Uf4qgXlTC3V25tFBDWg6XednjqGhkAJrQWp5WNDd/ziv85jwGXYeEUog9czpOhoB3ypBmLh0N8Z13W8JYwXDHTF5JncfCdSxNbbcIq2yxR2vaFqNVHUV33wGrayKlIq9/tu8Bw8JLcKD9bo5GnGLJghC2s8Ps/VSnHT4fvqoZp1nHfoPsmOrT9SW0vFd93A1JRD/u1xZQeZ87DpUT6NZekp3ypwFlAJ05/Fy+fReEsvKUYRxcTf1TxrPEuVeg3Lrh8FK3yaLN3Qs7UjlNv8tB282AbD703/YdH7f1uNqtgqeIElFzOvOl6g0K5YYsjrQntR3/Oow8VzbXneBndrx6IDC3UUPhglUUHmXHHIoOh4kSoH7mTzPqTK71VMoEalIUEGLViZWgdhaD/YvA1s9+ZIpqNhlbxh5DADNFbw6f7OTAi1yieZ//tmDPl2NJYgTllrcb6re5T2ysHqKDfI2Y/+aEwy65Yxn42js/GdL7lsLwujRytZJhsC+FdbAwRSTAqMkP7bhFa1XIl6CzkQLeKHmc3b4PswDZvwVZD21ANwsUv4DrshEe5hozbYc9BcOvMXi/g6cD8x7y2gwDKy83BTIuTeHsiRfMIY6lfxm1XUXU0q4XKMmXcadHu3ofdMTtqQ1RNks6YJaTS9uld0XO/FWu9eEjTnbD3Qw+YqVN5yZ9ZZBjOVFNJYth4uBbDr8z4YHNzYF54dXEGrj1NGOb3fTGfunWL+VuYj6N15CoSw9pdmdb2qxlkqjtUq/plRZ/uDQCWhG6G+Lz1UHnwBVtthXxUKN8eKvEwR5kwfC71ehkUjDbklvgvYwm9QcvLUV3dQBFRwx9Z5/5O66ST9SSfap3uUMpxIYOoeF7g1XakfOlzNNO9yoz5FffdnwAUwHH8NVlKNp1h7IK4oNy+GlTvMO9+927KUG1OBpj5a3axAOlTcHXecX5E+UXQgoj4Ue0MYZHcjLcItcVXjKChmjkVUYEXzqQwu1MzvTo/uc1QVjF/Pqx+oYz5Q4MwwvopWeQNJbnLV1hjn8r7wfXuZH49Yd62LmLBUEd+UlYmFT7H3KFL/T8zXE7rjqFhQrOakRKXtHZevJzNVpmQbgdZQusiC5/MRkZdpLqmM3RCRV1GNYXW0oMBS/NttcwdltReOtaNClZ/1zEnhkuhHSajiRQb7n7ey6KNJ/AEFyseksG/nVtfulK+ve7BhnhXQ1SEI0v6HnbKY4c0vKoxtlVSQgNh4rXQDzq/EHjIQsomDnHNCLtc3oUDvkmOsHIJ0VLROeephzu7YK5XOhRi36vz+4DCVUgFQ+6EFbenwp8vgzBvQ77aa3sgHeohudzWztFCyZ1LOj/mv4BStyDLxyAloZ34M2gjyNmCM+3nCpgvA3Z5Zxc4H/XDRx3e3XNH/sE+UrsJUGn3RxZ2Kv+U0kPqd/k5khWogvlnqJ8iJuNJDevBb9v8eWHA+6KkJ7UwCfLzhBdj/shqmjsO6dHdmsWtlSZqkLQSrYyymJHuXE/zW65efsK8Zcn5ZWo7/pjTKvNMGrplHN1Vd1RgGOd2A4zaoj6HijOZ4TOhxlcrSvUa5BV0x73Uft3DI3engQcChPNbn6IuHbvGnEIg9SXOuERk6iPJlppabVzyH7136u7rURdvVSmukMBhhE0lGaH4Zo+ftvpI6Kpn+iplCX7cXSGMccTwB+uRJKrmAq2bgAFA5cXYc1tYE1Mmc4OEt31Rmgxb9tt2x1Hlk6VNyV7SCN/D7wGhitlKPWitiRcBK1kvxoVjgTmHrt+FbSG5lYa217z8dZabbIbs+MUH/kaeCYll1WS+bZYVwnFCadXAnidctwL/PgyfIR0d8pYjTlw54YP5fxQk7dcq6ZX+bcHeYjoc0qdyg+XYxVoghO9iMa236MyCgkCn/DxKHpjqCmoqZZrK8/nl4FYVY7WU5tUTtlEGq3I7A4rHTM33Mq7LiPOo7B+ILjOsLLxyykaxJ2HaTHr0+K7K01sJXXqVZAbRo44CnXBb3Xb4cqdUNZO0jPb3IlYRvnT4bXzHLdvQcgFidjomDc8tKq63L7UZvZoy2Z7pxo3MNdWjvCnk5JTkpW3hVKW0NK9QNLheaTlPdVrJ1M7K8QguLy0sqPMzT9QXF7KLizq1zLClNDv2SFjTcydUN2pqezSM+I2DCidNTfHyKqslvOImHxaFBlkHF8U0V1Pr2EyBgNmgTX02IThiToPrpROI7N6K1upOcw7DHV48c+hlVmAh3cXVJRDZCt0UUPUaw84LCCxw8XbFDPoSquWZUIclBeVbsLrY5f3XFbbUhzvqB/Z60fSY6Et9gGSU43I5CaJ3Oqn6vwm7Zggat+ZRZpvXuQS6uldOx53mgfy6vVsar8ZDghIRpOiUrK+Jj8rfE6qyCp0DDszdPxUdrTDhjEzGxsJJS18RciPBFf2jLq/u7+s8HwPUz9Og9EUkyFPPulQrBjs3gfXMT3u06Lq+33n/DWYqe+LrbaqoXjjXGiIokX8EO3vv3UxAza7uog5R77h8gt7+I1nAKWhd35U75TR8t9iEkTISlrzDTSwxL5ocBx33a/ivVrp+eSDldtUiDRDzM6APwZddioPtaSw2JVMOXPGB9EtRis54XyXpnftV4/GgxVJ7NCNwUVH3jgwPXt1+UdpGPzJFQoXjBg/8yCAHlmlPqccvZSq+wlhBNW82aGygGmk8DMhQWMGwxRF/ipjJoMRxf7r4xLDGsf9lqN1AZGffygSSVcQymtRqxC16sBGZ70a8r6lVB7T5RoNmbXhbAsCMqwBoA2n30vhqojt85wxJD5L/eujcvPc2JS8p7McGOJgYA7nRBJhnsyKPdR5Ju3x189GeHGai/nIqjLyg2g4p63zR1F79INyHrXU+iapuaCWfYxF03Ggxe4bkI6LLdj63mqmSq2A1zHfqX6MHkqH/90mmDKwt26GZmJRhxSc7azP2HTuj+Vj5539RYr3Clt2lhJIRKResO052fm+olcQKIipS/DxInnOuxUJjuJkrpvwokx3hN3zf14sFV/T5llaLqnajljAVbaE+ddL99vfnaZSEdez2XgZDbPU8DY4R7OZeCWR6/8UKaTvx7w6RrLBHexLFZsHie1stVNYKcZY6/C5RaaJZdkP4ypzkrFBpoZ1u3Lafe8M6oHmLjW3TmgTRkzpemx5QD4lmYDBuxNaTO8echNQjbjeUu8e4ptqLDeBJz9G2mnvAeqbekV0I3mBN65KNX+yFftKocb1YI9wVhmJMeHWNp4nDlDbnnbRJwFQ23w20ScLcxgO8tlnBPNr1yFTYLcJVvwdd09e+y9KAdJk4YP7LMZxkDhNVqAuWL0900GPGt50SDJgCqnHMeQHAbXM7iDMEXXOPwhTAYr436vTQAgR3z+500fqJb2fvNNHij3fH6rTRwjNyPHSZzUpbCIYckXdR5wpzFzSGSpuuWyCWGsVmApYmZcs+k3CkdelmEqLzUTMDN4waTV9MOdFa9sr7ROwRPQeupiZPVaVjqQ91Jt9Gj8dnyOh9HLSf/V6ovHdURx2JDZLEhztKMcLB/+gqqu/nbpIUh2tKWWqgZeSles2i5ebq0zBI2a2UKbrW9+xrIaKK3EBt+9nbWexpuudbSuEY78TwXAPqRB6q4lp7Nvu6awVi2LlneZc37PYkS0WM9vciSH8v5JV6xabdvuXvNtTYvTxJ/ZXbbuxyspGqG6//7u8pdTf3jq0j6kxwZXBpBHMn33q7Z0vVk9oM9xZP4+V9DN3KOS8+5B5SrIoV0/yZiE2RnPbsKo06xP7BA/Z0SC15rZOFmC3oAenhfXt1yn5zB4EfDVbP4/UxudjnE7/xPO3DTV3IT5pNi2FeSteIl0WasWCrguXE0bSUq4g57LNiZ9N11/7nMjeqzC6QeFITYze3fzc5H+izgpgViBAbEYXYSxmI6hxwTsRE8u8kSQqc2WiNgmjNoixw59MiThC2xcwt0CYDMDDBz8ZZojziVkWODYg/2VJlj+27INlQxY4tkDvZVCXP3NsoGctRxMqfYeQI5ST0VnunJDpNia5+GAbLKvkNLpNtxqL8yVZ1Jzlo/kI6GXgeM17VsuzppjLQ3CVfFch09+e5PmSdk1Jm+tbJY8nRP3SIJkoacAPIKUR8eakRIlQJVk+6vBiUESXFcSYUl0ZPml5Sm2LZ3HGNpk4aQpKbpaQGZctxI5SFJiwjcHSENRnOUS80YNF7MVlVRQ/K+w00bNmg0WgVGUrwLUR++ajRXqUuR79rEOOjUJmzES0AECzv0xR+dSgnn1qQ4+NYmbERTGUJinvSo0X5uREq1M35nDpwMoR0OayxXyUO6tsLVLqRxbl/R9DrI125sJEztG61CE5/Z7D6I8fxOXRrtQuqm8fD95fTm3u3okUdD42Xq1CvWQ1ZfSZ6tk4j0zaxx5ksdb30kMqlJPvkMajRFrpzkGZ0pTa145CKdMUWu12QZrStprSzcTvrkAbsJiv1Xuhaa43JMdfrlQtMG7Z3/cVlcfn8UWfrqV8XZf8c6QSDwJyEDSOYa7sNZQ+qvy0vjMMzsjdx9BHnIWAsMiCP9O3f+iUOf+saSCEaDL/tLcjTLa+B6LHkmBUtm2B74t3BxBePG+U0Wo4ToCNsDnuX40c1u4vT4QCOdGv3Go5Oq6xNZwu7w8mBtCX4t0s/eTkasa+ASexWzDn5I04iHIevhsnp7O9ZW5uj2fOqtaq3Mw9BLCjPnPV9B/cTZ0XpkutELGq1fkf2sSbjLhbc7ltcU3CKbaNuHU/Bp1yrtwYGu7ozt22HtseQrbQWBtd6W7tf1/daFJe1q91rCXNIb6Qe54XSicZh2n16oREvYZ4LxJvZD/Rp5thuZrugb4Q96d91hD7MnFsp7Cx0H335GmGtqfY0/jx6OpP/xNhlXWzN9k38VHnBcC/efA54nb/D+CDeaQ31FX1N+pF5nn/A8DGus7Y8vjqKucW4Ij4pnnTtvFZ6nXmZf8Z4IL4p/jz5dxUf10sJi/xuycmGk8Qb3MYLE8ybnM6LU9KbhkEPpaHsFx5n6LIHJ8y4gPnkTnbJh4Y/exXLi+zSn2t8oTKP/e8saMKH7DU/C2wDvN0E7BdA4T93vlbgB4hzE0J3hH+y+vwNw/l6YWFmO2Bv4O8XQFtCff9Agini56CDBOLpiID6bYmDgRo40WUShfLF/qFwTD0RoivRjRPSjeXJ/SPmmOGIehpET2IHThznUfTyIY3W/2e8hV+dSyZbCqyMM/b+EVeUJsUTJI8MgK9EKSsQSBFpgzCWXG0YEgSLgwsO/d+1nJaihqG6o0agZuKKbL1kU2VjZBNl42SdZfWcAuECARV/sWCxp2SoTKhUqEioQKh8iFKIxksLtDaIB6gFqAmoB2gKTgROCE4HGx11XHNgS2HTYMdhGVAtYbdgp2F5YKugobRptO20KYyRNJ0mf3QXcCAMJCkd239sclR8JYSlg0bR9tM+MB7SArxfTD9NJ0wHTUdPj+aP5b/nqYtrixWLdYsFi0uLI5DH6g0mBSYTJgsmGyaIlFHGTcZJxtA8RDxKaGQ3fWUA17BY32WLE4tziwOLSYu2pf6l7qUQpc2luRRKtso2xrbOJuN4EHjkuLvcC1yIvArf537goP+QjfLq4g44DZqSeBD4lRDC3RAQiBHSxRH2J+HTa7wCh9TNKTs4iP4iqMYcKGtiQV2d0gON6KbuqQYhsEObaZSGI7BB/Rg/KdIGC2h1Yk/9P5iFStnzE8a56qRe6OndYQDGsH4hFBa5SHD3Cw8dsCz7NVP7sMW8U3Sx3y/ejAEjojG7/ZorZ9BPUFh8rYmxVoP9EO3kS+yXaeyAXHKjXRH9uFCgTsjV/FX1mZ3c7kbbI/gSfnqYyhuHMuQPKc6ALqSUuhnD3QoRiVClrWjr3GuVYpHvR73RUVB76gxoA46jorqAuoC5ALtF+MW6/pqLmgubUZrRm8iayJtq5zRGuU+uVqtW9FaJVrlWgVbkVlsbfxt3GwibZpiE6YJpiumGaY7pgGnIaUSNpkkm47GWsRazFrIWdFIx0jJSW9k52TjTAZsBGwHbAQRB+EGeasf1ViZwGoW77sPCfcIWd0m/EVxcFEwUGjQCtJJ15TnlOesN443vSfIkmqibopoim2Wa5Zv0mvSbBecWxjfGdMYNxktGrs+SzYbNqM2VTbjWdZiByCSe25jdjhBPF2HnSedx51iXaJdF13nXVNdk102X5qrV2s6a3arHbP6c8Oz43PQc/azynPrc9hz8nPHs+c3Wdog7ub3eaE+sx+ZLHBwnqmAhKhhjqmR3KhyVqjQQeksB5ZrwAkP9vaICEHPrg64255zIAtP9UfHgb9eZcOWi43uiGXpYd+MIjPunGftoha52jAg8kuIX81qDG2Igw+M0sU25wkGHRjlDTuTd20Rd4m6E22SASSSlKiFpOjloYemEKSg9+UGSEFnwhLMpQVw01ljT+T6S96Q5wvp4MO6fHa6V8nRh7mQ1En4WDt0ArQQtAwI4SfpgkDSJjP+CWWyMcccLNJB7qe3jRY1/+MNdJLBZaGlkC+VeTufx4+0DuZUe5zCJaYxpMGisafRp8kDVOcw5rDnEOZw53Dm4rRMi2ELYnHGtdNxs3HKUapR29G70cJ1pnHXsbexzHtgu3a7bHt+W2b7eSu3T7SO5kR5lZfZlhmXMZaRl+mVAZMR/jyE2uQu4v7mNHtsma5kvcBdwNXAFcCMeh7qKupq6iLqWuo66nqiDqJGpbzXMNMI0yzTGNM6qkC6IrIatia2JrYplhtAetB5tHGwf4B0RHu9GjF/FphItmE7Fu8y7wrvLu8a7zrvCu8i7xbvNu8VjEDWQNA41EmuI34bfid+J34o3hjaJNok2iryGvYm9iXEf+kZAXgsODwWLo8exlwuFlwyjlw2Tlg+zTgvcceR6UHxIjGMlsYq2pby2S1dpIjbkVkepoQ+sRTjifCt/pC7bgz+pv/Bk52wu2NZ8IjWUiiNfawq81h4WPcDaUaIzxQ76fqujRf1kUXP/0bN4XVLaZC2ZBKKivJ+8OhK91nItvDnJzxsAsWcanqbdEHM1vD05zB8B2WdiaX6flt0I6/xwMXhBeiFiOBXOB2aSnzLtNk0USIPhsPayH92PGc9VvgzaaHghLeePFaVj2LmYqXt50/ShU50lbkxx0nKx8u5yjnLIspt2FLY3dgx2L3Yctj86/K5QLVHkCZZL5n/KpIqkqqVKpEqlyqSKpSqkKqW2cLVwlXDlc9VwjbNssOywqDjHec85KDoqOlrqO+pHeiZ6Vpo3mk86Nr50HW99fp1jX30VCso0VsF2WzN9AhjwHugp6W6UrK3cte+/j7BPuG+xf+AcZ7/jrGR/4Jxmf+IMZY/hnGff42xkP+BcZjd62jdGxdbBzYlOiC6KWqXXRHdEd0XvpM6lHhBtOPvl9Zo7nmP/ztzBHsO6jXqduoF5kjqLepu6hx7q/Kh9pP2sLVC9Ur1V3VHdV/1QPVR9UT1WfVN9QXulaJSQholgg+9MoQhQG4AXvZCWRBCXwH4KJH8Ec5hp4ycLkPiT0BprTXJ1iogHNjD5Sysw0nprmdJOiodHMnD3V3S6JQpw6lDWsrXoJXqQ/6gh0tfy0V8qzAducPYoM3jikG1rw+LKSn0w/9dzUD3Afaz4b8zv28/Pvslg/DPoaDeWohJYHpz0DG4NA4yO3OBYuOxJDp1kDa4N45ORvOjoIEWy8kgRAEnuYBpMAIwINCsqEPkxNEmKrJUIKJ1J0SEkqRxxC6zrgWi5MalMHSyoJepBCdL/E8I2yrBiiU14qXeObJJi8p+xsuiRaBIiuTS5dLkrmUuZC5lrGRjSHOh/oEStQS1hv9f7J20U0bYXF+yRuqiRqI9ok6iNaFBoj6iSaI4SSbHJsf6jFW8PbxJrEDNAuCN4lchbw9vLW7uzxw/I6uV7QPfKjEeMSRdkR2THZaLkIuUi5KLl5+Rn5Wfk5+WT5BPlE+ST5cxIVWB2oAugTGCooG1gWi1NrW6tXa19LUHRgZV+rgeO7qEUq8jAS+nI6UrpSelLtYkJF84ECrVybiRrJFlDuURucP/BCsGMwUTBzsElwa3BZkHDQxvBnsG+Wb2zjzme/DgMtMlBSYvj84trq4u7S4hnKpNb/HQ7x4vv3x21gFhZ73QVOZtnDwjMzx81gxhZz3QNyYeL18NWrs2nXhNck+OqbBd6oSnP1nYp5jWLP2aIsq9O1E2kowrzVKmfBQdUtfMr4j86iB6DP8jzjRXEJoJWCXMn2qpPIkbmZVO27Ryi4AMERoqTGL6QZ1m2Cd1HEPp3D5Ml5n/e1mxlVbYJLUQyNBj5O0g4RIAMTyVKzbxrKTRVLCU6frbNGGMGE/ZlGxx7z2lEK4BEETwcaEQ6RTu01O4nbn8mfdpmQ3FHcClwY3IHcD1gFbsXuzG7D7spux+7OTdPThw=
*/