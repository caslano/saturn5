//
// detail/io_uring_wait_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_WAIT_OP_HPP
#define BOOST_ASIO_DETAIL_IO_URING_WAIT_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/io_uring_operation.hpp>
#include <boost/asio/detail/memory.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class io_uring_wait_op : public io_uring_operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(io_uring_wait_op);

  io_uring_wait_op(const boost::system::error_code& success_ec, int descriptor,
      int poll_flags, Handler& handler, const IoExecutor& io_ex)
    : io_uring_operation(success_ec, &io_uring_wait_op::do_prepare,
        &io_uring_wait_op::do_perform, &io_uring_wait_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex),
      descriptor_(descriptor),
      poll_flags_(poll_flags)
  {
  }

  static void do_prepare(io_uring_operation* base, ::io_uring_sqe* sqe)
  {
    io_uring_wait_op* o(static_cast<io_uring_wait_op*>(base));

    ::io_uring_prep_poll_add(sqe, o->descriptor_, o->poll_flags_);
  }

  static bool do_perform(io_uring_operation*, bool after_completion)
  {
    return after_completion;
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    io_uring_wait_op* o(static_cast<io_uring_wait_op*>(base));
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
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  Handler handler_;
  handler_work<Handler, IoExecutor> work_;
  int descriptor_;
  int poll_flags_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IO_URING_WAIT_OP_HPP

/* io_uring_wait_op.hpp
6vzV9av7V8+v3l99v/p/Dfwa/DX0a/jXyK/RX2O/xn9N/Jr8NfVr+tfMr9lfc7/mfy38Wvy19Gv518qv1V9rv9Z/bfza/LX1a/vXzq/dX3u/9n8d/Dr8dfTr+NfJr9NfZ7/Of138uvx19ev6182v2193v+5/Pfx6/PX06/nXy6/XX2+/3n99/Pr89fXr+9fPL0CU3zsKdIj0i5uNx0qwDWKAp0LF9VFYyAGC5DV/xxLoay7mI0WutHin+teXXMwXerVaJrGQSTEtZj+zhS0yp22vsemp1gAOLPHTJ2fvUdND5cDkntn94308cmp3GUmwzesvr77dSWT+gAZpHY9lekwn73qvme3bNkkwrFQAfFb8lYChMecFT74aeu3A3HLtcq56x9rSPWHwe8Rj/cnK2Xf4LbR5vjE+oVjeZCWGpHDXNuYznPlNvpb6BU6ODhQaPlH+TFrbNjm5EqdQBDSl12GzOOOY2RjTFSc49A2V7etm8qaXS8Uk9rbUscIY4q7oKIukGXRu/lhtI1OaUx51vThhuSQYDMP9Xm09B8yq0tva5u7O9YxJmeFAnJxcqV3DiPoi5cieJI5mJwuMOGW9OmItUC2F8ieFSRTxLrYVFLG18+5ZAa9h6VXQqe6DCzbYj8dn4sVKAmUXYJtEMVEUOlu0YEgjeG1O9fvJmPWT0mY9lOByY0TKVrV3PCOPkPOu6TMXWlYjO7G436yu5sWhPrIfTwKq18hNL3Nyn6D2VJONCHWS1xEWtguJHdMqYiiAcciE7ld/qLYAjgoXpHvcIFsTRbrOnHuIYEgzc7QAl++upINw/BEcPSVKsUiQudP3YzmDaT+8FcNYWBOpZ03UOft1/Tq3q5gtT3otfe7QP+y36nuSOQRXWmzJwQ4+Y6Wss0HKYh8Dgt1febBlkTrCYvL9+bj0jKKOgHAnUrIok3i/JacxoALLajODzQPhnKTBZq0fOn3YYFYsk6RIz10Y6+Eh1iREEFuaWoqZZtfnAMnKLPZ35RtfJFxPRJgcbINIUya8hfjASWKPaFIeVPi5wlGBAecBKGhcQC6RUMzWtR4AFA5IKPrnstcgDcVgaSwClLK+2+SaWKD2YCuyKrlZYopRfeBlpStkl3WjDc1mL+apiVvNih8xVk73b9Z1w761N9j2fItU0zPThySzF4sbR6we6Jp9pGO8JsE06EIlqIkuFwW0JA937XWO3y0Hrg+7jON5OnqmaZZpzqmkltDX4xn0HvLegr5CfIs70qrIQWQjWIv0tpzJWpMFlV3wspQVlyvrmF1uTdyL4Yex2KxltJ4q2BhRyscNOeSQtDXkbV4VFcxJoqwVtydYOUhNz5HUTOX+wXZ6lWP62cwhz5to59jPqpj+ErODbkXeXm6JzkBT2W4vmUP/1detmtCPb4XNU59w8ex6myClLFwR7giL1eij9XnidrjGncgTAVWIJXfLOakwWx5GvVmehwoNGgqaBxrWiHeUAO6LsroQ/Jfr1kkS5xA8EgITLfI3HsdYN7um0//f9011gShqTjSzhgODw+NDXF9fw/ZtbW3RtHrYtsBvbm2RtHYgddqBz5qyPa9+ZHocZjv8eGyj/2AdMHSznHweV5Yr1Zd3LJ9XB8tCcTKadbbiTgfI4ztiqA4CK8NBbgVedXfKBjeHWy8uGa1+kqPTh0gsOqpQTaPb8BvVP1Noa1QO6OPsqOtFzRWXvKr5ZVQOUifPCdhDUrldkS5Ecg1QeKwnPNTiM42M3bwn+Il1sop7vnsrdtiDZtqPCE7I+jc73K+P1lSwjvuCgJ7kF70ESRwRbo9ZzI0K1UHx1ghKTS5BQZdkDa2sYy5H9kFl2Bq1TAudSxgDxzvvs6zfrcvh8MaM0FnHFApK8c/ox5TGaGR8b3TJ29pyj6+8rh8zPuKbTxD5+SZrg3K3pkUV2cV9cbHQmVLaQHSiccd0aauT3431Jt+ODIzEDMYEdUvOv6zJE6W2aWxjnDg/0TRk5G3DuJxtM2jpenWku0fN1odCMd3ISbP1A3//E9UqrOlpAAHp6CpxwYElyKHTSFSvUMl0C+WCnXm6oBlmSwGZzoBF6kj2cfHYSblQarVqzIkH77BShXh2hFYma5sIKrNWBjsDOTdqk2vV09xdqm9uYK1frudU3TTZ62CpqW6XtdbkGXG+c67R8tNHmRbffHWXlDag2HrlpWZ/+NZuW4/eGoLbYzk+4uArJ3FKcc2s1u7xHk2+wB9dp3dmanN/2SOzhrS+Nxsvuwdp4uMZB049U7zGVDn1m+5QwGB4PM8mnwkvja5IEXLAUWrYIXCM3o8wbFk3L05pxhH3DGt2Uut4bVd9Pa4pE9KUr4/LLlnTpVehGuCS6i3djrNG3X6I7ZnJgrue+obLXiwx+sGiqkX+82MFl6RrE8dB6+iYwWd1U4rzdyXsL30+Y+jH9ghEN81nyqnNfrIuyx9RxG96LdflCnbfOqT4ZO6nwcGD0KcYRh/IPuCAFpa43ph07PGPQmaFyObTw0FFCsuZXum5Y+CoOEgArlhuKeuEStIwB+B1ZIzEKqoeDHD3ZgOxp7gOCUHsI4VkPlF/Cmh5GH8F5ISSv59iGuKX6q9Z0cTmin98lXMkRTTj2fnMQejtBQ6l3TuepEzR9za1kZGXU5vyKEcTlaN8QP86eq2klFLsRcKBekpSIClLUB9mTrDXP+svIdmNDqhRI8U/5F+FuyG+UJmlnfCMt+vd7l9CVtC253hwu3f7ASMpJWXiujWB8UKwzBTsxDaSgXdugQThZJRE7E2LYutVDmXMRLAx1oSDI0+olfuWeRZwQJLGFPVpdvM/C0E6kIg8RNE7ywMbtkSdOttzuC04YEc9OiNePISIrACA4JOeZsQ0Opht9mHfw0CnDrLlayzj1xhbv4Ua0PTR8E1AIk0eYG3SNCXd0N/w+tcl7yvX6gUBDYIarZeYR+pGz1+LXE0AGD6PAB58NAKsf0H+HerGjMVZTcw5TDga2Cmep1msWqQpkukRUknYjd2N3Y89jHVH8InzjHPFd+raqbuBMQVyBvTym/lrqluroFLSyVvwj7uE+R0bOXSV6aysWWFCxjFBMFY4ViCWP3aVgISMg4zhxENaQFpcWl66nL+Tv54/v88lADgAOaAweS7dDkystX+XQ9/8/HYT3xWUcd/G0dQN3F7E605jTCNMY0djmG6YVphuGEIEfMQVUO0vBH6AiUTJYMRxxGnEecRlxHXEbcQ9VD98KlIp3DzgnX9nH3S33Rakf1ugw+s+6SGncpDl+ZmiPcXx/LQQgcO4slCUuAXzyZjLfF0HpTTF6H4piFED3qu3JTTCZdpl3nXZZd01xw3B9djlnLaFpoN2h06BJpUmE+eL6/O9GmItsVmcUBoTGsqkGI5KO3nTgiXxT7IwBSVHvdHBYjGmjLWotaidtLN0m3S3NL/kNh4Uxr9VMgYq+3KHcFtKB3EHcwdIO0p7cTv9F0keBRWZVpk6sWYxjqundV9ZvgJ6C3vzUjQbJAsFiwSLifs3wr/DXP0AxABizWGNZY1jjWeNYqZKn5w8HwStXs3KBfWCERnYTKSEtAqxjB3GZvOj3cFeuAErNoC9fTHRKCXUpqk43PXOZrKhdF4WzgmGkkO5TfS8W/ptowLbEAkWVDH03mqV9YJBYwJbECkWZDGyymWd9pmgRr+v9BrEJ8RG1SlNmgVXjOjHetwXTAKatMpjMbsev5R/UExWzBiGB5sH24VC6VpHUKlQGkja0F3QndA6yPpQeFC4UBPSc0Ix0krCBlJhQmqCGA1vWt1M0CcW4nebv4MaW6Lu8kksmt0P4g9Gn0GA8DgMSGLabkbMCf3WqbCpjKaCITIf6Wy4mn40FocaTA0imJ35vzPG1SiDRtmU+JtIUpasFXm4c3rKMSvQJix2yjOr4BXMW1qTpQB34z99RgHcDvAlf7hhoJMaS/5dwQAnkeSs+jK8/rv3KPTYJuVQ6VMB0S1d4K8B9RMftkPie+AEH3THgzYo0KjTuD8+rGRwS4gHXU5i1rDcLq0coygYeL8IWlSaxVikea9ap+mwAG3FwYakBfUBYwsw2HjyZPFE8YTJ7uGmsj78UkZRdKa7UD3kw+DN46bgqGPn4O7jFuOZY9/jnutZajvqenKeAgQLgOoV2wW1RW4FygS8Bgjxk+hN5VSANq14g7gC/RRkl0MmE2i5S2Y+QwB7IziD2tu/RF6PO2efMLRPfhpKPhpSvjpOHkp+tNibelNLjpSOclTykwg/QAeCaOTeq1svVHKSyGc9unw4Y32M2mkyq0hPHrSiTD9esWxdQBlGc6O+w5KswEwelJ7QOtmwesVqaMIwKdJM7rT0xOpoaoBLPjt10Ev3PIX6l97PgNqHAP2GIgHa2vZKIgpVq0y/Xt8IFRdVdZ50OMcxxyHFt7J/NmpEenJucyo6giZQ9YHlsry9gWIveqA8NAmrdsOiXdXVMHESu780MyoppkZcTi9vcww/QT4znpSRohObQ9WsZ/VpqTJJ8K+Dfbm1PdhEpcr6J5GPw0c3oBtUqUiTIURPyqyhFKdAu84UpYnR9Xktqp1I3aZ8XdYgamWa9Si8mUjRpnPdsA3QheQ4Mp/DqyA+eyBmKeYh6GzIEWoEZwRnAmcD5wV3gnSY61iu8YVg3OX9unzP7yNsBq7+pKBdnjKWFaqHdwD+7KI2/iP021oKR+8S8syg/ef2C2XPfBPjCOfCYPQhNUdMJiC3tLQ0dTd7B/cwO1YsxoAuhQRXgjAozsdrJjxHA6DbLNWYsJz7Rbt4Mg32X7H2Q4QdACpK/3NdrVDY1qg0qsjzttoC8XCTqRyFcGKI8NZU8kb7iOOjQ4PmeoGWSUSItMl5+kH2jtIc5JWW4PRu0E/yQ/ZLd7uCSJ/QR9LM+YbXN5eT2GnOReSYRzuF3MfOKzOEqKx8v/DHCx8gCU/CWyOE6IF8sMjL855ffnYYb5an+hoxJEFnomrJnKhybo1aa4+hSIjKh5kC7MhziGCtG880WZwP0YWJQUOcNMHFTz9T9BFjsEPpcXa1oT2TRXotKtLkDXu9DdxDAkqm1GEaTYZ9WbJZDsNChtJChstWatxBit3okaZpK8oL41n4quRzAqrkvcS9hFeYj5i3WOeAVox29F7kcaRZmHWYXQwv3jn6Pa47tj9XQZeBDzSPyQwpD86dOepzRBAOCoPQE/RTwkloDKDplRunnavw+bP4p6XLcMUkVnoEJymewCPBGEYolySQGzg4BKo8IcQHCsYuNXr9mjcKg3Jscyje9+0Arplt4B8yKy99t3gHfwclS3Lo3j+DL5I/JIpZWNzyg6TRHFzekd5EW98Dza3AXFopzm7M5k/uoY7gBjJmMW4zdnDbhfvlt5BTXLUWgjupdfwGRfuRXRzFFuYLs3ndRkZbqA5e99Ws1kn3kkewHwwLLyYvHQ68h8Ij03iCyH87dzyssmZFADhJ0uvoIBHlJocdk0doJwnHAMFGUwv/xDNJoQZMd2Qz0WAGsA63ijwzFJ1WtwWYD7tpml1/YOFeZ8xG4SuNONJ6ssbeThLsp2ALl5r4FXr8XUmBHB6glemfWvwn0ocaA8BOgPEjwxOnoSPpPttCSBuIjBmoaLvyFoi8PFLTY4odXfBB391vfTEZaaCW7lMPjKS5xNNpYbnH817O0JAgJeDJfs7mwJ3EtUWC/MQOC7OK5JQzxdn5/Zr+bC45KqSNineogTnZmYHh9oGYmvfRxrvTvjWauXU/IlxmIH9n6B5xZN5mIfzwtr4XgFQzsSaQMVn/FfwytaYf0o+qA/f+EVDbDTyRjXaqqlktT+gkxSz8BgdMTUuVkiNKog+uuuXN01sgvw/lHk2Ti2riNrmlm5CBqzi9VMOJ55kzTV86UdWyjaFlaGMf1T9axsZDSzV2jyWOlbPvNumYfewFsz5Sad20iSe59KS+tTL7pKlZWWrdYcGHE7VXef6cWWiz5ugx6LLj2HXS0rbas+N6BdPNo2Wv6pZKAXuAXLmTg0N6y8YrJS9aO/r8BdO/+MKxvTL70qTB56VRa+nGY5yl4ygBzu2Jkx3uwIXWC7/37fNnlplJXUuUKJHkyya+XCBYwH5fTnj0+r2CG//vwTRaS18emhPV+8QoaK8MltquMs7oM3brfb1IOtRUaig/qc1P9J3fMASjnqJTIQ0vZysYpGqCTlIolZEtxsiWRYHriV3aIqLPrCloY5tkxrbDqQqHZG4GFDZ6X7ulITWplCPLkFrRDOIZk9dLbZCrJhwAwKiIGZKG/9LbO7QhxKhuVWx9zpnv+t8bKj6ycQNiEK3Cx2DoL25vuUBfO1RKmcWQhiMLxfvHyUIywSvXwUsRLDnEebkMrDISRQth+YC2GzbL95t0b68aRfi/1OoSgiz9P+M/s+D2epgiOTLEUuVi7KdXPm0fUwoy+NsSCHztYPB10cSSlnmPZOXxhob8G434WigzgIEEJh3q3omJMKLWMvnvSsL5s1Db/9onxxmUL/4NqGJQYzqlKK4VCU5Z2P+kGdI3GAkiLCdTjIpmo8uDc9TfFDaA7nZvrkAo60qnhMiPRlRyqiIHhT15zPLnSvFjW8l7GrYuHoMnAtw/jjZZVDI037LKVwu4ohA289OOUX0KjhK9tOr11HUpojAjNRyl6U62VZI/0lqKfXuutgEVldX6qSKwDZJyc4e4F340N/rB79hvdd8gnDMYH4NnQkswmcBLIhn+vdlol4+242/2hP9jHigH7741ZRj4RmEaox1jPh3Icrht/piyEY8blW098eplJyFPDmObFOJdW5ZXkqqw1tbLatjkonTSB4M90sUP0sCX+jjJszMlr9VcWQWey5sVk1iD+YPv9HpsiuZyXJu+AOEAqCeQEFBfte+37Qp0FPJ1iHUts/KohRdtR1Vaoq8bP7aPZsUavCtap9Dw6A86Tteyvpfjrkfk9qF3/rr+nUz6N6ENblfdWWy/Fg5QoqxLI5tJA0XnGXwU+32EcsymO/d2cEQgcjxZEy9qO3foz7r5BNd7FW6eRUln7CIBrgNZU3ON8pX3PxcLpAPCNyr0jKy0b/ZKhkGtK3aDyuupzLCTzQMf+kcivU2Lez82dG4QJXq995e3mz4rLvIZlL0kELrQLFkiL7pku6wG3mSOZD3h8kzeShPdyBzYjqzohORB2ihlzPw8aMiLuPvEUcb5usosEYLPwGbAL8LBS7zqDbAiSQ2shm+SEmIxNXyG2tbug9WxKBODQDIBkFt5ilC6Y7QdXNk0gz6MSI4EJJVVn8s+RDB93HSlJeFG6NY3gPiX91qzkI5dJDOukXbCWnFncavCRpj+DOl7IPPIwDfbcpTzSHyJoCLs9hwG8F5Way71o+9YJ6AhAPwv1deGV1DCPZMbKtOgfWLjDGgGCuQCbW9SLwvZcRQm97xqT27LVrb7hcSvbEMDtWHUYipop4Fiji4QndgduXdYO5J2D91K8C5E73/3IVDiJbjp7kW0WG972JSnqOS2YGptJrHn8nhNICpHOUM7VAQ06Nen/fA49HyQ7hkN6sUIfKftg7AeWG9Emt07IK33w6fkTJYN39QpQdOmwWg9I6VBxqivl4U4jvAwc08HPMPVKwFsXlk/j6yYysmZcTHC+VlmgDq5OEEN5Mz+
*/