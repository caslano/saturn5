//
// detail/reactive_socket_accept_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_ACCEPT_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_ACCEPT_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_holder.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Socket, typename Protocol>
class reactive_socket_accept_op_base : public reactor_op
{
public:
  reactive_socket_accept_op_base(socket_type socket,
      socket_ops::state_type state, Socket& peer, const Protocol& protocol,
      typename Protocol::endpoint* peer_endpoint, func_type complete_func)
    : reactor_op(&reactive_socket_accept_op_base::do_perform, complete_func),
      socket_(socket),
      state_(state),
      peer_(peer),
      protocol_(protocol),
      peer_endpoint_(peer_endpoint),
      addrlen_(peer_endpoint ? peer_endpoint->capacity() : 0)
  {
  }

  static status do_perform(reactor_op* base)
  {
    reactive_socket_accept_op_base* o(
        static_cast<reactive_socket_accept_op_base*>(base));

    socket_type new_socket = invalid_socket;
    status result = socket_ops::non_blocking_accept(o->socket_,
        o->state_, o->peer_endpoint_ ? o->peer_endpoint_->data() : 0,
        o->peer_endpoint_ ? &o->addrlen_ : 0, o->ec_, new_socket)
    ? done : not_done;
    o->new_socket_.reset(new_socket);

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_accept", o->ec_));

    return result;
  }

  void do_assign()
  {
    if (new_socket_.get() != invalid_socket)
    {
      if (peer_endpoint_)
        peer_endpoint_->resize(addrlen_);
      peer_.assign(protocol_, new_socket_.get(), ec_);
      if (!ec_)
        new_socket_.release();
    }
  }

private:
  socket_type socket_;
  socket_ops::state_type state_;
  socket_holder new_socket_;
  Socket& peer_;
  Protocol protocol_;
  typename Protocol::endpoint* peer_endpoint_;
  std::size_t addrlen_;
};

template <typename Socket, typename Protocol,
    typename Handler, typename IoExecutor>
class reactive_socket_accept_op :
  public reactive_socket_accept_op_base<Socket, Protocol>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_accept_op);

  reactive_socket_accept_op(socket_type socket,
      socket_ops::state_type state, Socket& peer, const Protocol& protocol,
      typename Protocol::endpoint* peer_endpoint, Handler& handler,
      const IoExecutor& io_ex)
    : reactive_socket_accept_op_base<Socket, Protocol>(socket, state, peer,
        protocol, peer_endpoint, &reactive_socket_accept_op::do_complete),
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
    reactive_socket_accept_op* o(static_cast<reactive_socket_accept_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    // On success, assign new connection to peer socket object.
    if (owner)
      o->do_assign();

    BOOST_ASIO_HANDLER_COMPLETION((*o));

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
  IoExecutor io_executor_;
};

#if defined(BOOST_ASIO_HAS_MOVE)

template <typename Protocol, typename PeerIoExecutor,
    typename Handler, typename IoExecutor>
class reactive_socket_move_accept_op :
  private Protocol::socket::template rebind_executor<PeerIoExecutor>::other,
  public reactive_socket_accept_op_base<
    typename Protocol::socket::template rebind_executor<PeerIoExecutor>::other,
    Protocol>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_move_accept_op);

  reactive_socket_move_accept_op(const PeerIoExecutor& peer_io_ex,
      socket_type socket, socket_ops::state_type state,
      const Protocol& protocol, typename Protocol::endpoint* peer_endpoint,
      Handler& handler, const IoExecutor& io_ex)
    : peer_socket_type(peer_io_ex),
      reactive_socket_accept_op_base<peer_socket_type, Protocol>(
        socket, state, *this, protocol, peer_endpoint,
        &reactive_socket_move_accept_op::do_complete),
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
    reactive_socket_move_accept_op* o(
        static_cast<reactive_socket_move_accept_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    // On success, assign new connection to peer socket object.
    if (owner)
      o->do_assign();

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::move_binder2<Handler,
      boost::system::error_code, peer_socket_type>
        handler(0, BOOST_ASIO_MOVE_CAST(Handler)(o->handler_), o->ec_,
          BOOST_ASIO_MOVE_CAST(peer_socket_type)(*o));
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
  typedef typename Protocol::socket::template
    rebind_executor<PeerIoExecutor>::other peer_socket_type;

  Handler handler_;
  IoExecutor io_executor_;
};

#endif // defined(BOOST_ASIO_HAS_MOVE)

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_ACCEPT_OP_HPP

/* reactive_socket_accept_op.hpp
AU2opRq2iBvEuYQjeazKWwESHnh9tsR+RTYm8Mm8I5OiH6Ldk3I7KiU6RHORGuh6Ku/UJIZleol5Wyou2P14clMUCkC19sbmx0x+t+pv7Tbai/PwtTOEtY2bGtY6RnU86cxNgGW37azADmCau35E0JDx48DUbsRYkupge6BWsjP66Vw91DtYsE+QnooKL18VDlJ2gdKzChawWT0WKoxrVBpfbpNpA/MyHIL4atkz+dw8TtX04kWRQDbl2VpDtaVtYFQpO82SDeHNqfA97XouBi3x0XGxMSmQGH92HYBD+6nIOBaf7PJ9eJ1DnynuqFYjKTAldox0qv/pMp9oChF4WKgrUfCZ41AG46MhqnYzgu70saPFXsMBw6jQBsKzyfYQinA2rfLZHczBXsgij7sRMq54Qf3F4gTO1UgIUhFV9n3ELsqpRmIXR1QlV+WWl7oOz/72/VzGmR7G+OWw2PLt66tKvGvVtZ3+4pt7fUTK/jc39clqGQN2AubU094/tpexV2OL2VLwEvDy9SLw4vXSh1my4dlcxePaH57zHQl0DYT2vdFjXHrbqx7Mq3mginCJeO6xN93l4Zpsn8x85v3pd89n3TsLIMtbpNv8uzDvBEMSw8hcOZW9cAdvNiP/hosa0qabzmZMn7RokhdVx3pcztSPxcXsXQ9REOrNIB3HMnXYOOftiIspL1JxWSwYSwph/pnK/KvBP/5BHJra/JuxZccufYBmV+T5hr++VH4wD5y52BgqkJUofrVRPVsu1Yk4nPJ1hCVgBJHhQDkOt/g1BpHBQ5m1WV+Odisf3h91XqoiZP8j+KvoTu2gVR/jrgoollbIiVmACv9e9km4yWYKi5SXSd50g6pvhkkj8fYuQmffvBvqe6QUMMYgX7fROUopr9AzSSq/0QBVRYOxhVJDk32MGpRSNVtEODoIcO5/WF9ed3gvdMgUcg99GJV0/1UPTVgAJQ75itSgk7nfTE+b2oeJWRTmMykdAetmKesRO08XU5C5/kI6XvgrAGv5rKQSKqu3cxhaed65z1XJkf/JZVpup8/6/J9iQ9e90D+kaU8JbbzdBFJz4JEhwFEIO4UBwsVMqKgBikNzVlyYu+pt9UJ6o9USsniyRWOnz/egcxHnmhSR8K50XM3Fjv+Q2L1zdtwFDvu4uj4h+hQyGnYLeW577qZCTU4TbDtaNJYgQIHA2TQXUXGQULqjWwzDIy1BF90Se3e+S7LtFjexqekDLDRT6nYS4FecehLCspoWElrZz2GJb/vMfSUQ+86jiMd15TsOyWSbxt7mUDesv0hJM6y9nDbUt6wDBSPyw+HJhqm9j6iFd5yKCIbJoqV8ReS7qzIHJgYHCJPw64GYFCMtxA1VImlBZSqKBYCDDYk6n6PJCFSaeEcxnS+7PW4TzxLxnfO88qiGpcALx4sVziZmo6gjFnzn4DAB8ru9LHuPv4y4xNv41nHbcNsyIhKIxEV+dxJeguDA9vBAqHEZuOoJHBXQMnzGcPQkzp/Ely5OdmWvHq54m8ylzX9T5lVNqM6uz1xkzq0t7LuqIPckvSDgADDZmPQZprA/gIImPSntPETuzxPDQY6MjwHcTayReCjztdJ2yKIGmDr8eqSe1s0+2neIK5wFprNVd974X8Ce0s8b4c7XQr1zF2+5sT2SRaBeK6nKJp741D6TXTD4nYhIj1jY5IFOM04z0Elawog2N/+RfLF3EyiSXQmWfDHVpy40DOz1vOqEMNPPnkZa5QM2QGKgblQZN1UvbdhQVFNt3PD7aIkrCqfJtVzIIHe7nDtq25pDXp8Rn7Ydhao8GfMbVV9t1OKpsz+T8prj6DkWHVruw4sZDI01fDsIXHN9EWSVvC2sq5GV2RaKebKGyBO7hPdUFeqNj3e9ggS1XC2MOM3xouvFFhB1iDw4o/H1fH6lcGpxNUOVRkUofs8zjDqQCRbERNziQm2okmTE+zkO8gBtCa1+vKFx53Vy3GZ/2Fazf55wzyObav/q1ZfI29Y+KY3XDRYMTqlIBbeGjNAsaX3J3G8biIzhgBtC8YRVaVIpECnQKXApMCj8hyiESAQR77dVFxvg4Z7GGwf3z24yZoj8mbYurRmLWKRO9ePnu1w05Lcb+X22P12bAKO8+nGbke8ki1qhL/0/0WnYr/uF881CEJZVU4Vc9qB1PNJZy0knNxVB0l1BUso8Qrx8wt08QlZUbsS4bDpaoD2DFp9uoZTQ6UCEIncspmybeN4hSvsKvHJLcOkpp3r/XgGe57sW/0atwW1QG3eYMhitF8wclrs+y7e1Pow4xEybyNyomv3mt3FLeyb0irT9pjTKcCoh1lsuINoYgxOgYJX42NRuZNLU+NjkWvpwL6lgqqF2qpOa/8pZsqwKOuOUCKQR5w3FGmblHAgSLk6wJSEgxUdaxRDAirsVafNLOsT4zeLP8DWL2m4tkL5RxYdPrJCu28Tynb23yfJTAIh1O2PMUuQuBROGBczxXgjHmWrvkcRfvjFXC/qYQ+KMjFfzfhDIJ2/SI565UfdfxLU7naMonCS1FzhFyGvtWk2uvhTQ92pYNt9RMAuttHl0XYpQVpSOsjgCOV0oncSy4yEtMa0xv0hxT5K7z5bWRrN32xRpeceyb3sVbY9zOBAduFT3Ejke/puSbLC5U25sqDp18b5kc+25a3YXEXkZuKW48PGhxpUISmhLFEmJPbWxe16exXNxPD19Raumr5WuwamBqbVGyOeOBPJb1YlHjB8gQlgASiBzNQnO+0kdbfih7RbRBNUtJpvs8MmFGlVik5YYNavkSKbjMfm4nzOv6OEZmox0cqYDmzU6ykhHkUl1TzujNoOeXM/Z0R+eI8NkXzm5xOidO+eW7enYRqXxHFZujFH9XkRtROsFyWrbXv1Fs3nR5F/9eLESBgit5o84d83l+yhjxyiYvLrMyeBFvv4FBDqfRDOC7DIdb1Gyd9I9hIayJxl8ZR0+REGVFPWm/GpnSX7A6lPkHVHLE1ojazc1/MoOTNh7hbs0u4yyoXpg2NmIWe6ZZNlU0x4jfWYMRstEsDaNkz4Q80CBjpx4qwKtyCCxLs5u1Py4mzJ8fMHjtPK97fq0dZaRmnws/3BhfOfc/w9LNrpOKdrDDqxoNjCPQGSbFahVyt5Gl/61vxV5wYc5S53eNDsveJMIZ8jPNaOVW3SzBjfVbVU5xt6aRAKIOO5DNXA6dmWYRcvDacwSLdr2pui5O6jH4usVECXv1SFkFNBvEuZXTu+ijXVN00uyL8/wyx+O5+OprckHEtjPlp2LwgLyCwltpgUXTauNSqay7r8XUBLHWSVpEl3umgvrWcIGzas0MQtBcjmf3RsPyzanazwPgm0o/TEYSd96ysHvTONbWDA1nYAO9MIdHt2eaxSKTKYcwFDXJCkXdBwKCtqDhqi5whp/7eLQ8mBV3u7GFOHN4sGsWLiTacwoeYpYGvDN8UdDmu3g7H/6cYZzXl6h+qXao+sRExEhsrMHaQaxB2yn4gglH3ngq+xO+gkP9gm9W3NkpX5qeQS6J6RB5GNPr7jZKXCQDnWBkpgtkrfSXvRtcVmtUDDw23EBWGrHXnXTM7MTs3P9vWQSs+MZyRXBG3AuS0FOB+QCZPe6d+trA1+oP92yOAahO2cucbJDE70x/YMF+3QQeJkoGfDgJx5fWNLDMfkRjUoohQSEMJa9a6Q6TM0+3U2JvWmk3yTxunNXJTclN/waNS0080mxgNCQpYndSfc+ADTaNx1IwzKmHgiEIV/4N7suplYvhuzeWNesxRANn7cFao82HMPbmoM19jWAEuCQHcuxlT7EBGv3eNE2fdSl9tUi95AYhYOQzWwF6VQbnL6mQVglUtFxyrCNHD88cA43M71ePlZcuzgJcwS1mtRVnAJzPbrsAurmr7Mz43kaIngXXB4afVUn8YS2F+LWF+yRblVwyzP3jfdq4RKaeov3Y/0qhdYtTq43xdRadyyiJVLcfbW92R7CbwKK61scWzpdnatFEqYULf/M5ap7N9qL9MnA3bQJ8BtVLxK4QShj3m1TGdJcOmdTpdS7FMe3tm+ytZ5KdloopicSv2lZJ3+e155ycUSKioWfyuvwB0aA6ZsOPbOXR8fahWlzx2cKZvBeEJrF7hrWdFYkY5vr3D29HppiHtXAMdIa8ry9qZxti++d6IWkUeC65QldFPSCNmDMZ9dzbtnYGWA3zZ13LG12Nc+f0r4NVhs2U1JM0Iy4W06324LrM48a316Y2UghuTTT5MLkitZlNko2ia/Caac520+QHUAIUp8CBjqzXxQsgAY7fxhslR38W04xfwraFcZjwsgj/CV2J/45dTn9czJpv/pHv4k19M6qL+wY+skcWKvhkGo9mP7zmR1VOoq3v6uUY+RirBhaAc+xNQiSphTCblF6gB020WGD3XEA7ezEOMpq8vIomTF2a+RhOo4fQYVCdsvzZqWh+MwVdq/IuFD7vjut6SanpNhEJQhDzS5ZiXf5T02+9NuvVM09+Z/Eszuym/MQ0DRUkDmmbkAIQC3lyew4gYuqbe/LYdIsOTrTye+Hg1L7moqgghwNN3TzowMmdiHnCNiNpwiy2bdZpbm5w+d9vgTQaOW0QRN9yLJsFcqdbSSK8zlV0qeSAkBku2mFDS34RNmI2h67AOTgs47xWL7x/RL+PO+7CmPIfARcZyfMb7/F/IvPUTsH3Nw+zPzJOe6nES5ZE6Mu3TLW22Z5VOlM7AwPspnRoB+6Iy/IuxExjC2P6pphUhLeJIbzaDvsDT9Zt2TJ+ibcTMWDRXPYuq4mmwd0bRfqnf86J78WA38Zte3x+lWbdHDPFFrjGoo3nv/Nk/IWrD++Uhuj/bBd7RLSqrgchHJ0mMr88RB5E4r7o0jxNTAA52LXvp/uPZs/wEmhPf7AY4uWepAyEufSGRv1crYLYEnBtKLO9QnGBDpCYcEqg04Pvbie7hscBHBfE5pC3LEh0qUNE9S5fy6kfSgwRdedukFbCKSBz0TfbvRzFi9B/iVGUZOLgYshJZ8VsP7pDLdCT1u/OB2XafjY7UJS9pONwpY8XGB0/grQRqbUptSG06ZOk3lzeiu3ZaP1ohmj9aJtYwvoBsRaOIjJstESONj55PnEH2/hI0IjEiKSCtI8JE4kLaRgJBdvCVhtQGrAcukU6z2WQxaxMo2ycNGTqB3UAB+BTqVfkNqGvIY2Bl7kkWxiy7iKVAu9KssqWyDa0FRCrf2aMOc3jgCUmYgx/9P/+uzoDFB5Isty4obnf8N9rB+E5O7Ie809Aq61q0/TNVRONFAVNVzyTfJB81mgErINsgey88B3wOOzm/i8cbtd3h6AWWcgRqMYB7lH3g/N7EHZ6FuqlbfpguAM4HpCLUnJciu1REQvQK2j9IY1HVOtut81GKznltXUeTNXBoifteP/Szu48wJyY+r2FgyIw6Fo+WWwo4yK8zCSouPBJIzC8QfPK9wgEnuwWLBosEiwcHBdOIZ76CXuIduee73Px4MaCmiApd+vfpd06fQiTW/6lsieptx4ERjuMwg38DeoN9g3gCcDizIQDtc3rw9PE6oCHAHgjMIYidAfqtOl152/nqHGwePggwcMQw8yMYnsmJGH/UbJjE3ul9yrvJf7gg1BnGWtxU3zCVjod9yHund5M+5i2PmY4rGKE8NlwVJf0+8duEwcZ6xvaxdkgy0+p9Kc36x02G5QXVn/bOoxdy0qgl7/xF4ySCJ5GMtfeFL0TSGvS4oxZoy0HRs6Lkyi9jRPaG8xU18pzEejAVF4aSeenQoWAhtmaBAKnapn1Xr44nnvL7pyeLeqlB0ZZCkX4M+mpuTw1FVnxdesxNIX5RH1BBzeyYxXE6VCWkGmDH4e3Bm5MMTT49Zq+Er4rviG/Ob4Nvie+MI8HLQpuqCQEvmr2SApzwU85TICLF7g/KdMqRhFpU1Y8fnzW3durHM+z9MNu4E9AnCLzzndHdYplTgvaZEgQ9xIpIcGysM37BbaqdvAd9h1OVcWEpYufhrkM8jd7uPGxFyJl4iZmGNuE+aq8RmkOY42IDO4Q5rj08i43UotHpPe3L0O2VjakFohwsiJBuLGbj/V/nMiyRRxaY0TlOTKGxw+qKY8VPCXAVNU2AwOFLZeXKmXwzVpamwMF3U7dmkQOZyPFt0/bo931jCoj7mcEpwUnPA4yzjGOnsokSiNKHUR4RHueWEGKhYl23GtkhQ9uLl+tUOnB5r3t3fgXqg87YBeJu4mTia8ujJU+Crw+0MUB6QHaAemBjD1SWri2HVVhddotbPWfmOPEw0bYXNG5hyYS6bT6p7JEBpeDNMSfrDAPACK6mlA1FS36mpjan7nl5ynS63C/9KRkU57z/h4xzWYLJZ9kMGNnnJ9jvd3v2z6kSP4NGhU+EqBuAcyDNFybvuAqLGoLR4n/uV+Ug4+TPx6a+dsPAMwpWqmYjM2+4Lf35nLaANIpol6lXPlxrSEKMqW2qtBupXxBFj58oAuKkGrKMhUei45qrG5E9n5wZQcimEUiQSjaVmeT+A5xWy1pWZTMJXisOj2hivSHQsUqcGqsEl/2oD2hsu76YCf1jBzwKowKDEotWx0fZ5ImkUF5D84GncPZMgn7pdvSd+bbFogrdb+KFbjgisUBNjrVxsTXyeJNrZoC8svT6Wy4mZDESfEVEWDOoZZl/O9v6BzvmaXeEQ+bljH8IW/IHfS36Y6wLw74vpHW9PWQNde1TDVMhD01KjUpNQQqFSqTlqUvpa8ptHO4m/qjy0d+NfzXoKpEQxHlroINkvzk92ip+PSZBv31G3dzI+RxpRv5hDVLPeTmS6HHLTXW68Y1kceTcovZN/GaGweVzZXEFegeDb6wWQQTs9B7FgfGq4M04d0rF1zgvp4F9SA/NgShuSGHCu58sp30g48eD/Iq7EjP5fKtYB3rHINNOTQXat9X3vDO8Kaz2ciBWU8Qnge7GZ7DTRMNFjUPU63viHfw3QRSSGSxsskHXf04Q7YIs9YsvHXmRZ03WLviO+et325uX4HvgP91+V6EOMZ/MQIO37EZP3N8FYLwfJKYU4IG6efEecD+kX7j9t+9bs/oYujaEvUlW1n0UVbU/c4bbNHGfPLOMLUrMZ1krKP1e7XxYGJkMHM93oUp9RHZFjv9wj+uqpmfzx9PEmsOk938m/qjo3PDTLi4ZZ1aTVO8cnBtzYmsaYnt35V43AWmXyMjPwUW+S13LDYMzYpgpcPIxM/IoxA9N9spM6MBGYP2JKHyj8mC6tz3PHBdfGxl2mkdqFyvN+dcaq/Q6VANsfUEIpeGGLbG6aF6nJjn/85bUKn7WpaLpOxzfz9rljAQwpn23M3YPO1973wGFGvi+ggwH4TIUQEXGdyTQ753Oxm6jnOYHk7KXzFqqwP93LJNDqDm8F738RMzfDRMiWXyOjs2rN3jiIHI7AHkmzDgWzyJPm0ZOg7kIQF89LLvHhwFyI8JzzHIo8BvvXALMZLXg1vcAVmDjjtsZnEpqSCxb88PnloJY4xRgP7h5Xcmh1jq20k8iVnH7zkv4SiSJ7/yi/iGnSv06n2DrsBE+XWbY2SzpAqBHmoJ9WCUHnpmZqwcgsUZdlxOH35fQlUZVH5MgW/kpK2nR5EKCrBuntkSyLRzu+bKghAOSVtegK2AAZ4iK7RfJClhjI2/QiOP3cr01yb9zwDn5OMrcKL275igMkcSDZS5imfNJ6aIkRIwMqfodLR7uyXPrdEBgPutmjMYxfwin9ZcCEV4Z6M8+0eK58snOxlGqqlH86zl7nBuO1Kx+f3z2+O4vQE6xgXR46utH07Ez3L5ZmxIicfwKRms5JueVLFlmvOZdmQ7B1XRTn+FCeLlPuAfvHeaa3Box6CY7OY3UxpbY3c9nT1Bw6rqVnhpEKnE9F+xuGHqkIo6Lpl5h1h9rIY99lfl/aJowgPpHAEp+eSaDsV4pv99FP1TZ0fAIHQwuSL3k7adoGZkbvVXuxqWa0mukv2yGnKZIdzfz3dnN3+8g4fvaCL7C5rW1nB3nLTV8k9Ngwl0Qvh4ZSccgjuNAHofljDz3Lzh9pqGXyymin7N9FcHVJ7C0IDMl2bp/xiSh2mowB4bGXNifNrGbiMZc8nuogi8YPRKkLgMYkmBZYfpxRpsBnnFEqThTr7gnJfk5N/7AbqpnF3tx1ZGS2DVmdO/1dX0nmuyBd4phjV5T92/SDEkJ2FyK7m3GdYPfyl7TrLR/qAhjOls5CRmrnxoh8fY8mMS9A8vNlBwWGUrLmh00tS+C0omVGL+8z7akUx+jieIuEAAyz80+3AE6rznFGhb6LWWFv0KOqbMesP6Gm/oZhgR1F7VPIi0MsGBsBsD5JOnpKziZJ2ztYuk7bkmTdOSGC8EGOjI/CVixo6NbwwofCQIuu+5MBYLHnNs27/RGhh7tw95tj7AOOBa0IeRY5NK2cnn1hLV/n6MbYSACCM2PbeXmCEEr3VRlrWmtKysyiIVc2sNOge5mPTxbuzK5+Tkhr5rcycwt1Eql6PYWfIhtvTEDQWecfZJuDpEjzuor2SGWUFVf9f14pw3hGAPa220t9nbTeIjb2psMPuaOgnZAiILnAb/oj/4JREcMjTGLy6tyjWr7vntgD+4RRZ1pH0aW1gL2UCYug6w0fYUp+doARxZ7T531uCCNxLlL5l7ziwCO63HpPsUsNV88af38ETHzSGlNGtoCBU9SP6qWWHHCnnE9dfY4PUBEPTQhqn1bs6PR4ZZYdgUbsCpzKULjTVL1d7hQzq6x8E8m75Emn4VvjFGTGakHpnGj88JT4HYUGyC2+w77JuYIQRtcPUvcXJba8Pjueq7Qvus7EQoJldrHg8+cLHh7HavC04h8zERSO51SjYIyoPIWlckqVX4K+nEdBKgOc04PNqHZ5HOp+3bjNCxXxNvIoJHzX4Ug/CR0ftciwpS+LXV4waTPJojSPL6xrWx3qqWlOHqvfswiGIPTw5xWCS6Of1V1mZyA6OR3xySVKFzGq9yL6JPR++OC69aLcW9EE47EJ5Wcomyhhmy9cYaOBzcstl0N0Us97ean52SKfiDk9ClkMqpwKgGt6y5I1vEayFBzOlZrcWuy7fNyjzojEBALMR35hszAIELxWYjhx5CDfpbiK3xlcYaSo3wio5+wVbPyzRw/nmfJuL0poXOAQIa4cIyrtCL7nX5n8=
*/