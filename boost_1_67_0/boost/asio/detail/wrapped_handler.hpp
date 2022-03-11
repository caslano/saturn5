//
// detail/wrapped_handler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WRAPPED_HANDLER_HPP
#define BOOST_ASIO_DETAIL_WRAPPED_HANDLER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct is_continuation_delegated
{
  template <typename Dispatcher, typename Handler>
  bool operator()(Dispatcher&, Handler& handler) const
  {
    return boost_asio_handler_cont_helpers::is_continuation(handler);
  }
};

struct is_continuation_if_running
{
  template <typename Dispatcher, typename Handler>
  bool operator()(Dispatcher& dispatcher, Handler&) const
  {
    return dispatcher.running_in_this_thread();
  }
};

template <typename Dispatcher, typename Handler,
    typename IsContinuation = is_continuation_delegated>
class wrapped_handler
{
public:
  typedef void result_type;

  wrapped_handler(Dispatcher dispatcher, Handler& handler)
    : dispatcher_(dispatcher),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  wrapped_handler(const wrapped_handler& other)
    : dispatcher_(other.dispatcher_),
      handler_(other.handler_)
  {
  }

  wrapped_handler(wrapped_handler&& other)
    : dispatcher_(other.dispatcher_),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    dispatcher_.dispatch(BOOST_ASIO_MOVE_CAST(Handler)(handler_));
  }

  void operator()() const
  {
    dispatcher_.dispatch(handler_);
  }

  template <typename Arg1>
  void operator()(const Arg1& arg1)
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1));
  }

  template <typename Arg1>
  void operator()(const Arg1& arg1) const
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1));
  }

  template <typename Arg1, typename Arg2>
  void operator()(const Arg1& arg1, const Arg2& arg2)
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2));
  }

  template <typename Arg1, typename Arg2>
  void operator()(const Arg1& arg1, const Arg2& arg2) const
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2));
  }

  template <typename Arg1, typename Arg2, typename Arg3>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3)
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2, arg3));
  }

  template <typename Arg1, typename Arg2, typename Arg3>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3) const
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2, arg3));
  }

  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3,
      const Arg4& arg4)
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4));
  }

  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3,
      const Arg4& arg4) const
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4));
  }

  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4,
      typename Arg5>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3,
      const Arg4& arg4, const Arg5& arg5)
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4, arg5));
  }

  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4,
      typename Arg5>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3,
      const Arg4& arg4, const Arg5& arg5) const
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4, arg5));
  }

//private:
  Dispatcher dispatcher_;
  Handler handler_;
};

template <typename Handler, typename Context>
class rewrapped_handler
{
public:
  explicit rewrapped_handler(Handler& handler, const Context& context)
    : context_(context),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }

  explicit rewrapped_handler(const Handler& handler, const Context& context)
    : context_(context),
      handler_(handler)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  rewrapped_handler(const rewrapped_handler& other)
    : context_(other.context_),
      handler_(other.handler_)
  {
  }

  rewrapped_handler(rewrapped_handler&& other)
    : context_(BOOST_ASIO_MOVE_CAST(Context)(other.context_)),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    handler_();
  }

  void operator()() const
  {
    handler_();
  }

//private:
  Context context_;
  Handler handler_;
};

template <typename Dispatcher, typename Handler, typename IsContinuation>
inline void* asio_handler_allocate(std::size_t size,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
}

template <typename Dispatcher, typename Handler, typename IsContinuation>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
}

template <typename Dispatcher, typename Handler, typename IsContinuation>
inline bool asio_handler_is_continuation(
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  return IsContinuation()(this_handler->dispatcher_, this_handler->handler_);
}

template <typename Function, typename Dispatcher,
    typename Handler, typename IsContinuation>
inline void asio_handler_invoke(Function& function,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  this_handler->dispatcher_.dispatch(
      rewrapped_handler<Function, Handler>(
        function, this_handler->handler_));
}

template <typename Function, typename Dispatcher,
    typename Handler, typename IsContinuation>
inline void asio_handler_invoke(const Function& function,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  this_handler->dispatcher_.dispatch(
      rewrapped_handler<Function, Handler>(
        function, this_handler->handler_));
}

template <typename Handler, typename Context>
inline void* asio_handler_allocate(std::size_t size,
    rewrapped_handler<Handler, Context>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->context_);
}

template <typename Handler, typename Context>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    rewrapped_handler<Handler, Context>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->context_);
}

template <typename Dispatcher, typename Context>
inline bool asio_handler_is_continuation(
    rewrapped_handler<Dispatcher, Context>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->context_);
}

template <typename Function, typename Handler, typename Context>
inline void asio_handler_invoke(Function& function,
    rewrapped_handler<Handler, Context>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->context_);
}

template <typename Function, typename Handler, typename Context>
inline void asio_handler_invoke(const Function& function,
    rewrapped_handler<Handler, Context>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->context_);
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WRAPPED_HANDLER_HPP

/* wrapped_handler.hpp
D9lI/7jjuhd8OXT2JvBVC+saFVhcXMQBgaGSmwXdrrymVYQZ3rO4q0vAda1ZzDc05HflrQNfLDxNxlXobsnk98/b1/NYBXkeYSp086+cecmmGeY14wey++ZQXbh9lqfc3ZvY2YWpFcXRpp5c9ocKygrREsVYGqTbyemHoqJNNyJzkHY+GKp/G+yOBAlzMQvmEICDiDkHSH0Clh+P8M1qhf4UnwJhSBSIZs5ZXK63Ng2cQ5kLhizjW62nMrTLf8ic9uond5gPL/ypKb9hSny8KzABSyTAhp1F6NU2kMLW8rGXTCrDzSKTIIbHh+bfBcl0OpLTtmwV4wmhMXZ9kUce6PfBqA0oyyR0ZyBtksnDgmO2Q835nuL4ULNkNTIlnzykiju6k2dm+5rZnbxCk8FkHk3TxtAwrPL8cvb3T/+QdViu1gZDmXz/Q4wsoAZDDnBAvPR4vjpstyshJQ/j1s8U6kD0GJlA1eagMqN+EnK3VM0SKd1QNh2Ba6/vZNtFvC1MH4rRd2SwvzKeT+wtihnlf1ulc7GLy9+HKMFA1ZwPYWFaO6B4yD99czs1PD6X1Tw7Kj4s3g1OfKmGt7bRWt6cVB0z7msjcpQpydJWZe7sCw1y0PUFZ6crDduHsxsIhKYl81ludFN7SedBgp0Lv2H936hNYmq1if8YjDYEabgIR4eOTFxQmpdR6iBEf09vHwpo9eUDOOwrAuf3pymDWpMOW9G4ZrjeRtOyg7xZMqsIcw+345XM3j/UOkQyavPAkImE9+Lv4LjgGJbRUMT5W0ekHnPIua3VF48M5+Zd+D/27MJLh6iZ5Nuo8GjCDShvHLf9tIeTI1Xy7Na/aqLWYrQb36n8LTQo/y3HXa1vgImxMdkxmNJ45O6XGDBQRwbmh9NOeHg4+Q9h53w21MHsEPkafDczzq3y/WMnRIlfLqvStTZDvE0/XG366yfEOk6HLBRupaNOj7CtE/4GZRQj2GiP/NChRcTNDv53tfW39ZaM/t+/sOmHzU5t9n06+0CTOysZRTaqlkvy3cgcdtpRYVMaoJMmF1WPnje5FilA+1Titjd6JY6gNZrAs2TB3223nzojxPit1nAYqSsd4h/mJY9ZDBgMml3hAHGqtmaLjXU9mtMHaSRd6SZgmBZrjAoGzgZlMzKhS+suauGPxTo42vFoLWCnOpaRSpVsy9cmc2G1c9Ggd8+c3dZ2w6w4NCXZHJq+bHNBO2NTp7qirs24dvyy+DRYPnNq9hJNm33yJl1l6y+H/NpNMTgFelwBHm8h9D8nA039lxktVg93SXRdJq8MF+tscoGR85kIGe+rGmhQcSxNZzKo4oc+a/fLajTz3e+MYAS0QswJXH9DijT3VONgjaxU6kKVcCVV1pOpAIgCNqkxkunoCqR+gThfFTzblSueOj8tstdQ8zGKw0jT9tPWZld7Kx806Tu2YnOSFjybMTkzUtAl1iXFQxJLwFzcy9ZKsZb+baGVvr2WS7FhYl3rdCLBQ16YB4DBYNcfkdusTD5WMlYBXmBk3fW7LKDTuxcS8ySlMBOhaRcIo51aSgr2fj6j/cQgHayJOmT7N9VpQV8481BHR28m70lpwaxwHft5QAfctzVwruiJV1q4HbHw/p73qRDhq7WY8UTqdjSCOvdxmOdVcBpkjZOESJ2OeLm8d8waMMf8yiivmdH56daqf1G/6uaxmdXOUQDWTCUvM/JKs4SDvty5b405j/SAJurDjrC/Mk2Obm5O/Tzber8aWS1gmSyJXDdxc3ZQIC7ysjyd4UnOEBhiTmHLTP/iplJD6jP9G83ekZihTpTywjiD3daGZ8cXXCo118hCBHcwYzMgHV2O37tQ4+Vv0PxNK3VFkyz9azIydX3DSXIWZg+ryJQbNtg6LLYBFNoKunKolUzyNkMLe3SWCU0HSzFjLxtA2DREh1Gk3bOfQeVi4S3tTbQlJEva0aFtt+ATZd55IUk/6Ka40Fsznjr7wvDQDNYhno3I9kYdANKPLGDg7M9gsHG9x6PufLUJOxKkO//jrrfFbePol87YpFZy/B3H9vMLI7dS91+3n7ed7kFM/zGlLwMDyf0bjpj/lj/r3i2H+xzSs8zbrQg9PKZjfUoYgbdEGw4nj/xltQUU/qqHfpbbu04SnK+d4QyKDo4/J07R+vSyZliOOcyAXwDs8dvDADmgQHIvoGDmx/18/4kTyXXh8DSRSlrg7F4JKorQfUF/Gd+1meo+ajLhNHtRXrd66Pn/7QWIhvBu75O0/nRj4+tgcdqv9/qQke+sg5Thi1yuuuFClLLw76eBsddxnzIviKOYj1FBgiEWppb6ceeorKxM3R3VfZgfQaeBjk8NACEcSFthZw8b1m8xmM8VonY6ku3MgmClWEhIZLPs5ygfW96XyxxzufGJ26rbdVj3RMs//LPx/Wp626j5fyDIavW5mhttnB4Fw/xyet6EIL03ifnz7fF5GyhBymirTjzVZWCfRqtzZ/NKTASeSexNAA+bVuz9ENLyAM036fHM9OeZUCBRbgIyPC+EGj+Qr/gCSmlC7mwvmB1yIXc+C2XuYCa8/4+j2Enb4ilFZPgeIlX7DQs3o/PdAi67zcIc+FPpoXYYJpngQAAsl2EThf73QLvTOU6JTFp+iHozOpGDwvuiuDx2wZWrXgGdpyr0k9gct/LgUpfFnF/BhyCa99Hk7VfUsF4tgyQmljMUwnWM4TuFZUr7fCZHM8zw1yScVP3pBfyuJHvZNbJPCwQC3NOuaX7WONVGCyeiglYzg0BcayU1Nr9aukRHWy7TblbnqAWXPraG04l1kOExsqoxWS8mi0QGPIcR0l0vNCGMAIEhgaBULuGhOAqDIOmQ/pLH/9rTB8NVKkjpvuLbtg/+roeJI8ZchNnpFlqoNm1tRIzRCEJ33xOJUPillVDe47nNIeq5ndc6v0hIQNyl8M6aFhOZ19+KOpxQ9SvYr+vKLK0uiJKfOTKOWYPr/wWHWN4GDHoF/yNbvnya47O5P6N8WHY7d4MOeVWrPNnJpJfVdrwKTL2k3AFt/7n3oshENw94v5OmazsQpUrYRkgEzZ2o5NeQzKZZLldX5XC72HAeU/QBZGKDkP7k8JiCkZ9z/4YNFZwQ5VJIu8x4KoVVFIeCjDlXGXaRyUUg0j5rC3TCHZKTOSOxsXG1P+0ebWf2ygOa70/XvJchR6b+IUw3CHkRyCprAztYyiEj9zKURpPmAtEIGqhRmoUeBRtjFU9yu3AO79eh3u1OnBq/8HmpU9aNDPeNX+yULVeqKyJnX/kjaXXFDwiRhZaVYpvsZm+9pwJRD2fVyct/U2LPo++tHlmhv8Wqq90d/gL/NbAYzMv9XL70s3NVQkdOCM0/EVTshzWLEgGREGjGPu1YsGmh8EnzRd6NlOhPCISWPfuU9X/hFl6Kc/AbMJ90RllL2NlynqWLc2ZB3Cu23vO/DOW6iQWX8QfHp6M4xsxhZ5xbmjsygLOFm54T8eIaHX8gsc3AC/ARBvYhpKYmjFis6O7Bk2k2W5kn6ienIqAV03++kCqBlS7nz+R6vx/x9haF7a5trPizwKAVWIHNDXoVb64DHpi/rCA3Ucnj0L/gOKwUfetrMirRkhYmYydn5oqq9nEEPNg7GwPwl1Zez5vjXiJyzJlXGY9DB2gunUtvDcMXJMVjEA7574p8hQuHi2UzcGbJL04w/ye8fE6WAmJGByHQgPT7BNbQJqwOx5LQZTVkXgWJIs0z/sPlPKRMrWKO3qWTEPSyQHRzm/hln4BwjMslBdOnnzJtA9vbzGlMETW4S5DB5hDcA7ldpuh2fgYlwgQoohWTH8mY/qGBDHmXdo6z0xClQ5TBKu5qQdE/PQein8ciigGAXhKsXfm7CsTE5y2PmujpnVNx2erdf4xAAzgzUliBO8CDB0fLnD9sR/eMIAoVZCzY6+S0lzvXr4MEYlyXkJRfPSGYzLFqdMDPwCgyVhkeNNVluNPUm7nYp/vczaKoGSHX3neaSyKWphzzGBu0VmKGzcva2V2sZUqQ8HVJbcAhylKkEFftJoO5VhjXfWEdrDTyHZXzVIa9ewvijprzbhBmcLUOZ5o4oQo6cjoNKVqRmH8iDnzvh7btv0/nqtZ1PRT/l8kCZMJocCNhkOhEa1zHpIc9X4SMvAFZ/uahtnArzGfm375Qyn3TuaJNwiXvaBGcRlJRYIofotcnSwvafQird1gjCcX1FBiA4iiRAE/ntC3kz7IWG62SO4N8BvtozcXMtttxlsYdw0XEJVPw6r4UipiRGASMDcM/fJPlYETcdNfRGiOpBP2BRnjyp3N+brSkAPTelh+iMjYaDQH31a3hCe73UYI+0/1DjIEmxI3tiGTOCTz9q/r7JlxYIDrIDxanjHzTywOTyCBAdBWI8+Eczf2wXNsH3XwNaHzWuD/sKgDqNLnPv6Hs7dWUruVcQSDYQvhsEXkhohNIhWHOgxIoj5sVdtSsMwhKJnbOC9QTPOpcFV40p4hUxLcupRkg8fAbaodqssTt5oMPH5jrdEgh2oAC3Xtgb72kKZm59Lv3x71UE+ZAKctT9TTrvSu0NbqsC3mY8dtqpjrb7bv1p2EIMjOWLDCsQ5hsC5fZetnL/UdfmGBt4b7pdLs7kZ7ofA2J5K7GpP/EW+diY4IiBydSYX/DxG70yWz5fH9CeZP72Sz8gUn/w/DvdbDCtI8erQs4HCd2vdIJn2OdAH8JNl76IhdGVHzLjkjsrP/CINRhzoTYwTgYYhPAxYcYqMOC2KWFmdI8NGlNX0xtTepdXPVi1He7GshM1Gogxt5QSU2CdIdAf8axf3B7NsPZL/Qq4zp7JLuV3ur+eAb15hfyTXxJ+xqUBgsMjEtjiB0eWN63WyZRuzt3/3xcJnH4AQwjRH+6H7AfPFPElJtPOiCVrjHcV9TVXDq/fgpM+t2kRq1TmUq5fGYLMb/izIE2PeC0LymccSPUKMicSSCkaCjFsbwob4oJAIOiKF6EqU467dWt0fiBtyBnuhadx+lI7npDnZOFD4e0yw4MSx1Ppt3fCPjwuP6fKHrpM98Gjqu1H/fpFig47OQoN0bgFf9huE5rKOtxr6+vT8YjaqP5fb79KRz7bBWzufyS29J+DpOwSySv4llpn8Mz7Bcujided9usBJawZ4IBcaCphA+HucDFaS7+BISEjI86dE4XOsrbPLq10E2aMPGx5LPw1AGOnBX4qvpz8H2I/Z2whgDUV1svwn9BqjLF276QUsMpEUWgvgMRyVaoxabA8GzWTxUL5RvQX7EtMgznIgkDQs0C5BUKiGXkfiORd2CNVHK+HiSE1Ar0mVUqpf4amf7D7v3J4LSo+rMcQeLH0PmAfgutZUuF/97oL1xbkrVw27DbYDFzvLfXNJ2+kKA4Dg2Lc/oWk180TCd3UmlkUYLMbJCBwPkXe5C33y8mKHt3H6QIYgFYMF9CGRWsgUFMlqaDmQrlRIJYHJ7uftF0c8Xg0gq6tKtdSB9zdT5cvEZ69frC4Cus142IqN7CJ8zOjZPpSfefRyQCfx0c3JT3be2zv0gqVKr+/E/+CI8L/blSABY46qo/4XKgT7LoZiqjEsPXhQRBft+yi2KYvtbonpHO5NEZAsjMkdgi9/ocJ2y1DGAbp7samkfsV8gk3DWyF0s+jmjUP0xcgJYVBppDp5/mEgmCaQY+QWEJAvQ8HVjIeBBeRE2FfW8qMcgP3bFsglW0tbHPiq8nVNVfwlVTUbcagH0dm66o+DwdiHP7xbWt+lew4CKoueiCYhCjcr4HOp2Ed6+Yup51OBVgJKQIk2p/Ar+2v/Z4mh6i4JrgdQOl9jHT1ubth22y1vz6IwsokExRqtY0olj+Ym9Ov4T59sMGeNbqRd1hltl+2qDhAIZVZ6R/ZyKXQ1AC7PMw1XsqsdPckCQohVbI6wAAXdO5SedGwT6tSWZFIgaOxvwDu0JoUhg+y4Lqrj2Qlpj21E6eFDgmagCAKOfObTZf1COrrJefiHdC1CKPSsSDFBLFROLQaCRvaRoYb+hytcEZQjlo2fbqbIsnHZ6YfFCa430t4XSYgonDKGWPqF1nnPLrF+1MuluTPvIAVIhlSSHDoT6H4SO/ZY6E5+Z63vL4CITEXzj9u3l7QEgjSgByuR2c74hVgTMe/fTIQdbIFEU+63zCk3csA1U06cYTkbxEA6wZVrAfR2a0zBjj9cnMzolSgwmCom6rBdte2+V4orUov0UcAQtje1kIhLmo6deQsqr2owO3Z/5TIYA4LBx9dHx837TiKiRbmIrJfm+A5+VUo7aWWNRqRgKHJYbLE30okXnh8rkzYkwwMT/kuue5jb16Lb94OguMfGpAAQnNUVZfNZG5WpbGSBTzq0cbdypGvh3ktRgkNriaNVHpqUbFmQlswLeeIQgAy6VK1pi/aaflxsPGirvqu5mDsmJrlq4Ma8uuZgJRHG5QDXsm9DC0ax/u3K/9+/iaTeUPbCi/8UdEirTi0vV+PcS5+3VE4DJUqiBTc6MlnC+pnxm56OK96f78zJ/j9ItP1wmMXHhxGM8hki+VEBkv/mO5OqNCx8Myxd3FGDJ0yvDGfAVTUhFXxVpZ8VjGF6K3OH8enQ5GCz11iGF6jqH4Nyl0FilBJgfDXFZYe0Y4rvPMzxwwcyywW8tuJT2fj7ciCK+PuYHAPGQ3CZd0AJSVu0H185DdmH9P7C6GmPqZ+DaXkGy2Wp9ZXvjp73WA22GSajmj+JXvg+vTGHVNpAclI83tCI6Imi/I5WcwIK9YiMh7aPQ9w7ZbfVraV12BqtZ67mp5dRX77CgjWpWMDPLNWhg1RMSitGyRWvPSOhdVd2qZE3uPS6VQNEPfwZB9ulq7r0OfNBrhG0qWyeYu3dHx1GqNtcxZUC+B/hgvEUfsr2Nzy9nTcef+R0OJoHzYHnZGiJVCKD60RYb9XAGQZxVqq3MU6bpFOq1/wgYYGMZI4u9/tv7Pwo3Q4IIAvfa87Th7PSL8PrldYhAreLcffbnJ5z3AULBWhua4DhoYp6dyVQmmcCYogDLLHsc22hZpO2ci3Na24tZ+RS7jkmrAEA1P2lhK3iitaos7bEUI9sfFLZYAT+VUESOWwMzBOdpabS6L0Tr1bZcdszUKW+++uQZIlRzIipx/fwUmv/VxKu/j7iWwEJjlDoESB5q49PFevsUHmMBGo7b8DdGeoSGnRpMm7NBrfBvCPNKfFjYnbuLeVwDHqmaps4dBJ0kuwKUk4FjJtcH6XCOfw2XpEAfHBNDJjkLrFC/Sfdhz0yFBtpaNFGn5g88VdEXhG1ToVJpbXyoMDr6eLenmBIrmrhBaG+j06Rp0P61ZsraWZQ2v6nYepVvGr6EvQD5+kvJC3w4+8xjMfVmCXvxUdb2anDda7TkLxKLGjAFpMbVCRjcMTpcYDYvJl4hn3SHb4IKzGb4lqyhglY4SNEheHbU5cWK5dnNVSesSNv3qUQbAgF51f7XDGUmkr0DFHnMhYcu5+Af2aCsdcFRns2JE4gQXheyAwxHZ0Fg8MAQpJM9b+cPDw3JuH59yHFYez5ZMSGa31ISjRjSQ63oTLKBsfwRKuEI3WBVkn2MjjdIRG49PfiFtXPo4gCavdDulSNWpJCETts9u+zHk+Tg7X+KvlqURH2uHP9WaSMHZYReQTWDzAxcCNpQE0VgGHMcenIrka0I6JGSUbFBwUxaHw5GCt2xvVntNyEUq+mDnqrWRer0Vf0fBPO1s+h/H78lsxgFSvDtqHqO17MuMIdtMF57/YFJ5auasRG1J+wcqL9UxAZCUsuT6Oy9CuKrktXtEUZ5X2VhV6NdPdPkNJhCG9+un4cKH8PDOX2hfiP0/tP6sEi/xfDCwdTI/qkJ6L4pzZdZue4leU3fTgeu5vG5crSzs6IjQYR0Gor52EoujvEi8lUwmuMl369xzi7Y2PCr0n9K4g0yfno8P8/KqfxfhhCuGa7qe1jQNBmWH6A8B+kdYFl7wIPWYlP2Munrl8xoZnlwj46LzbKOlyF0O1L3KCMtcveMM1KD4wPsfNjS78lAaE+vWpWajgj6/grETCTYTCaIPWBMTo0d5IGezc/XesfRSE9pMmLbKufmmGN1gfsfgyWWQjganC3YGEnmxBqt+aO38utMxO7BxfYATYFhYi2DcQaS0w2RDsWy9GGLMV4o+jISOz++zemzZzs4fiqIKIrUn/+vuFJHA6YDgV0GIZ1L3w1HYrPCEEJqSnHA0AlFCNo2Zg/N66yDTEU0DV0BkXu0+7+eFFebBvoQnb2L+gR5FyDKe2V/OZ3jVaeWULH5t8YjH/eYCbJW4Ejsym/u5ImnO6xOwaS9cD4LHujmJpRpVQJ+QnvI5ZCh318P4K8yAbglgoNqsEiwl5b+Q8/YJx+EqRHFAlUClFeXQGWRf0T/+BTNcrwWxE4xmlw/UY88stN2AISBRhyKTkCcLlZZOGXIkCVpFOQkFWXPgJXfRMi/nHpj9tgaIW1pi+jIqeh2utcWLlJrfR97EMV+XQii0212cYqo1zemaIskW4hJ0QaEkHw5lzHeDx568wgyH/mEso/Eg/hUHEDyC2HB5v7k0Lb81HGfY2BvYDDVh5DyYO3bhoNgAECzv08WBnQ9M5knthkcannLG1dq75EMUMD0NDIVYlrNQFNqP+QOOKX0+ynGEd7Hw0Al+Ocwpjttzu0qNpMLu+Rmaeml7DzPf7BbKMxgEullJ+J/y1XeBT7lyDVhg0GDqTQeKDy671cpM5O6STlkuQhvWkIkJ3zsGOyrh1zl2q8HfVGYKoAQofxXtt4tey6YVG6TsVlr6fAO2MH9GkRjbQe4VEiKLMq07DqwNF0WxqUoZQ6IQ9FAzMQcMKgHfYe1Zh656bvftq5sMeTHqVi4VjzA3WyF1ldswuwH5HPh04lUARBL4fRwv/8ffK9NZNJ7xAsrX11fsEHxnNUbYkfDwBT2tU1r/OSqqMZXnz1PHx9VvnVIdL6+Mscs9USQrFH0fKeTOAl+c38lYBkwwGnHfcoYW/v10HsyCbojtg8UAVZSiSwlVRAaxPCVnvp0x/SR1rwMpDAGwzXAHp6yV/rfFKPEKB7kc9IautMyMkDSHm7TLcE5xxC2TQ8ScphNf/hiyzcQp7tSWUp0U0ATMfdwiFonOEOtZio57WFJFiwd48A87GD3/icwLR6f1Grk/pllM6qziyb6z1Hk=
*/