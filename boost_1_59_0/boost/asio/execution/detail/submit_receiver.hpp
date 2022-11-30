//
// execution/detail/submit_receiver.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_DETAIL_SUBMIT_RECEIVER_HPP
#define BOOST_ASIO_EXECUTION_DETAIL_SUBMIT_RECEIVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>
#include <boost/asio/execution/connect.hpp>
#include <boost/asio/execution/receiver.hpp>
#include <boost/asio/execution/set_done.hpp>
#include <boost/asio/execution/set_error.hpp>
#include <boost/asio/execution/set_value.hpp>
#include <boost/asio/traits/set_done_member.hpp>
#include <boost/asio/traits/set_error_member.hpp>
#include <boost/asio/traits/set_value_member.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace execution {
namespace detail {

template <typename Sender, typename Receiver>
struct submit_receiver;

template <typename Sender, typename Receiver>
struct submit_receiver_wrapper
{
  submit_receiver<Sender, Receiver>* p_;

  explicit submit_receiver_wrapper(submit_receiver<Sender, Receiver>* p)
    : p_(p)
  {
  }

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename... Args>
  typename enable_if<is_receiver_of<Receiver, Args...>::value>::type
  set_value(BOOST_ASIO_MOVE_ARG(Args)... args) BOOST_ASIO_RVALUE_REF_QUAL
    BOOST_ASIO_NOEXCEPT_IF((is_nothrow_receiver_of<Receiver, Args...>::value))
  {
    execution::set_value(
        BOOST_ASIO_MOVE_OR_LVALUE(
          typename remove_cvref<Receiver>::type)(p_->r_),
        BOOST_ASIO_MOVE_CAST(Args)(args)...);
    delete p_;
  }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  void set_value() BOOST_ASIO_RVALUE_REF_QUAL
    BOOST_ASIO_NOEXCEPT_IF((is_nothrow_receiver_of<Receiver>::value))
  {
    execution::set_value(
        BOOST_ASIO_MOVE_OR_LVALUE(
          typename remove_cvref<Receiver>::type)(p_->r_));
    delete p_;
  }

#define BOOST_ASIO_PRIVATE_SUBMIT_RECEIVER_SET_VALUE_DEF(n) \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  typename enable_if<is_receiver_of<Receiver, \
    BOOST_ASIO_VARIADIC_TARGS(n)>::value>::type \
  set_value(BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) BOOST_ASIO_RVALUE_REF_QUAL \
    BOOST_ASIO_NOEXCEPT_IF((is_nothrow_receiver_of< \
      Receiver, BOOST_ASIO_VARIADIC_TARGS(n)>::value)) \
  { \
    execution::set_value( \
        BOOST_ASIO_MOVE_OR_LVALUE( \
          typename remove_cvref<Receiver>::type)(p_->r_), \
        BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
    delete p_; \
  } \
  /**/
BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_SUBMIT_RECEIVER_SET_VALUE_DEF)
#undef BOOST_ASIO_PRIVATE_SUBMIT_RECEIVER_SET_VALUE_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename E>
  void set_error(BOOST_ASIO_MOVE_ARG(E) e)
    BOOST_ASIO_RVALUE_REF_QUAL BOOST_ASIO_NOEXCEPT
  {
    execution::set_error(
        BOOST_ASIO_MOVE_OR_LVALUE(
          typename remove_cvref<Receiver>::type)(p_->r_),
        BOOST_ASIO_MOVE_CAST(E)(e));
    delete p_;
  }

  void set_done() BOOST_ASIO_RVALUE_REF_QUAL BOOST_ASIO_NOEXCEPT
  {
    execution::set_done(
        BOOST_ASIO_MOVE_OR_LVALUE(
          typename remove_cvref<Receiver>::type)(p_->r_));
    delete p_;
  }
};

template <typename Sender, typename Receiver>
struct submit_receiver
{
  typename remove_cvref<Receiver>::type r_;
#if defined(BOOST_ASIO_HAS_MOVE)
  typename connect_result<Sender,
      submit_receiver_wrapper<Sender, Receiver> >::type state_;
#else // defined(BOOST_ASIO_HAS_MOVE)
  typename connect_result<Sender,
      const submit_receiver_wrapper<Sender, Receiver>& >::type state_;
#endif // defined(BOOST_ASIO_HAS_MOVE)

#if defined(BOOST_ASIO_HAS_MOVE)
  template <typename S, typename R>
  explicit submit_receiver(BOOST_ASIO_MOVE_ARG(S) s, BOOST_ASIO_MOVE_ARG(R) r)
    : r_(BOOST_ASIO_MOVE_CAST(R)(r)),
      state_(execution::connect(BOOST_ASIO_MOVE_CAST(S)(s),
            submit_receiver_wrapper<Sender, Receiver>(this)))
  {
  }
#else // defined(BOOST_ASIO_HAS_MOVE)
  explicit submit_receiver(Sender s, Receiver r)
    : r_(r),
      state_(execution::connect(s,
            submit_receiver_wrapper<Sender, Receiver>(this)))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)
};

} // namespace detail
} // namespace execution
namespace traits {

#if !defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_MEMBER_TRAIT)

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename Sender, typename Receiver, typename... Args>
struct set_value_member<
    boost::asio::execution::detail::submit_receiver_wrapper<
      Sender, Receiver>,
    void(Args...)>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (boost::asio::execution::is_nothrow_receiver_of<Receiver, Args...>::value));
  typedef void result_type;
};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename Sender, typename Receiver>
struct set_value_member<
    boost::asio::execution::detail::submit_receiver_wrapper<
      Sender, Receiver>,
    void()>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    boost::asio::execution::is_nothrow_receiver_of<Receiver>::value);
  typedef void result_type;
};

#define BOOST_ASIO_PRIVATE_SUBMIT_RECEIVER_TRAIT_DEF(n) \
  template <typename Sender, typename Receiver, \
      BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct set_value_member< \
      boost::asio::execution::detail::submit_receiver_wrapper< \
        Sender, Receiver>, \
      void(BOOST_ASIO_VARIADIC_TARGS(n))> \
  { \
    BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true); \
    BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = \
      (boost::asio::execution::is_nothrow_receiver_of<Receiver, \
        BOOST_ASIO_VARIADIC_TARGS(n)>::value)); \
    typedef void result_type; \
  }; \
  /**/
BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_SUBMIT_RECEIVER_TRAIT_DEF)
#undef BOOST_ASIO_PRIVATE_SUBMIT_RECEIVER_TRAIT_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_SET_ERROR_MEMBER_TRAIT)

template <typename Sender, typename Receiver, typename E>
struct set_error_member<
    boost::asio::execution::detail::submit_receiver_wrapper<
      Sender, Receiver>, E>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_SET_ERROR_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_SET_DONE_MEMBER_TRAIT)

template <typename Sender, typename Receiver>
struct set_done_member<
    boost::asio::execution::detail::submit_receiver_wrapper<
      Sender, Receiver> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_SET_DONE_MEMBER_TRAIT)

} // namespace traits
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_DETAIL_SUBMIT_RECEIVER_HPP

/* submit_receiver.hpp
2zaEyUJfagReZP20Y2XRR7r+HP0d9eX1pxkR5xRzowLL8KF604H95z36BcOSz+9/R7ExSrphpm6Uh7oMreujfjk8MbN3PGXytDFl4dagaCROzCJOTCJOnHcYko9hr9JCXytWpoowDku7Rtl0GJKEUW8TY9dpVpbKO+5FPw7LsXb2AmdPzOgcn3sTh+cQvPFPAH5I4OZLzibud7yRsEmLQHQ1gv4IE9omiMu2F7chJIUxFX7aBs9xeM12CGKzA2GzE8oTQ4kTAHsaDhH7k09RJomkyBznnVIEQ0NEJqgSn4ygIi8knyaDoMLzSBq1dd262VcZQs4t3AbZjd6fobJHKJiDlopgAphaBXiyMUP+xQVMa6Mg9p6OSt36jYLewMcfomVKJ251p5K4asDI7zYOovUShuRi090WVOYsoTU0sAtjkt1IUgsqE5BlEoCzr+fzKcgPOU8GYY8c1AsZsArCEEfKqwzZypnoXzfKN2tE8JcRAQgTIhbmkUZFi5YfJ43AJpNAJo5AhnzNm2SbBuNdIEeNgB9HN+EvwBEpuoRZy61pxKpLhFouUQg4qIiDixUZAOYCdsPradusl0JZUVSwIHripUK36yPS7DyC0iD9EVKJ/W2p/l29iD1r1Y0taDZxFpItAurSfJsdjRnL+kBpSSvX2xwbS+q/Z+rpvIDK0C7BkhJO6LEQw3USnU2shtIw9NdKJaT0YWzbMTLZeVLZiDlUn1Kqw3wqq0KqqOWUqfEDsfaHwWlBdC0bhJWW57UU9PD2fXmvP2hjFiXduC05qy2Qtq0LXDO6n1rtQdfear2BCwQOL7hf+s0+olX8QbXhz4bJWSe/RWtajXgladj1UlfiRG/YtMhpg0AN0KQMwyr7qgK0jfA+gUYIkmpAxJFS/kkQA8Krqnmn9DPeDvmieH+1XwXjgO85Vtod9BGP+TjRuvmeIkjtzk01TMRCx9ESVmGomb/SGk/Pvq0u6bHiQOhHkHXabI2jzsj7d2MVNd3ihpnhZVGQrRVSvRNtxuKGkMRT6lhNWQZzbZppJ19FztRtveWQbgP9gPAZwk0rDFtHJQvUKzZR4g3PJL3f7ZBn1OoyoUSj+4uRLcbje1okJM/+T1qNDeNOsblEVI0Nw0+DvQS5Wv3Cssiy5WajNNHhphPqSWTJzjjCftWxVtsnHocUWRHZY43Ge8I4oHqvC3ztxPcV9EEWnWCa8aQjGq0VZPUY16dMqi2XYIlUdrUZuNTziT4fA1dg1be3oZthNIwJhBGrPNXYco7rCPiyywUPrZeiNEJgTGpRDoUO0cEmLcRXvu78sVHBbed4XgYs1T9O0Ur7Y+IHBA2FHkk6iH3zCNEjPX3DdHWGZWieLpcIjIR1mJ/FkvqOIt7jqLaf+WH9Bgzx+zaHRGfz4UiLzp9bAFylrr3A3n9zEt6PSwsMXK/rX3jzoWKtrG9Wpx4PeBuhLQeCRxqD6hPRL90zxPk3peNTp4bpnuGiJjuTMTUhTC3YQ6JhpQg7+j1XyQcnqj2DPMM3cu5B3VfHoj7YYlKh95+MNnN1fwJncsOM49M7qjEOkwapK4YWwkXmiju2VgiuDHd6JaFENQ2b4K2SFonkYTduwrWYyhOoBV1hHy7936ktn8g4nIymeiSCMjXAmxmtWsitYW+KvGPuGYVqRK2lH4Z+NA5zIBhIbFfVgpwPlgErKF3E10MaCG/PHXbtDub5q8pNxI/It5QDTuQSgX/MuMKBcz1ZbLg+Te7KFRMdQC9g0GSC0qLG9PynYJBlKibFEsQXP1eAqdBTUv7ipcegKM7Fiya6OBMLgdXLthOTaxbFkOLsmGOEgIDVXiKhnw0hjPC8Xjo1d/nLf0Le0eP5gLq3dlwJXobwigyMpmaRBp8PTqQqC70C4K9nemXQdUXbo+G9o7alR90vG24R1pQyQvTCtEz5t2CEjyBa6FXuqSnijIOXEie4Dz4VCWcZlb7KbNqVfsrsX8mgVgXNy2jXgSzIKGrjjbwxiuM9vp1zIkSMhIOcJo+Us0NsHEzioiwyVH1Mv4c0czsE+lZpD1h2BUtmWZ6AJ7SdTJs0sV1O2zyuKN3I89xHXax5SsqNz71nsw1PT8W3aXguI769XJx6MiDoWLM80Qqdu32ynweG0YmdP2FT2G+o7ZaD+APtUdlzMNU/WgISJtmg/OBxo/jBpByOWGkgQXo17r1QxB1R7muv4Ujs01m0ysvnISqA2gwuws66jrV2DEBxRGznWXfJEVCdgSuNLcQJPF3WsP8jpGFrDPGBKCANmGbZjkHFqQ1GH6nmJlHx8t9C4B/vzUWhi7uS2apl3eZZ/DHpSuzQ9emqbMr16dpo2LHpYp07DV4bDkYsXzMpQqxYWw5DbFxjQSWGaUSGRusKAWdHs6oAR4A230OLA+pbRvF8sR8OieOSqiJfoajpmgqzP4HYAjQ+aRsOszgh8Ro081K09mP0rGLc5vKcZ7FxnXoPSkb6onis+Hl6lQ+Z68y29BIWixWVkPi7Rb8LIJ28CSguHSurvEzPqOuWIjTe/Nx9uTwiCjTApC+sABkDQbFWbXtz9C+fWO8ruZMHdSzflSXjbgJMRTqIwrebBZlmTcjVT5XEPEw7aq6viAcHYahoCHu1eGU3ynT+woWI6erPejLuFwYnZm5MnOboMCDVH9lSmSp1GsaM0xuERLhMSUq2DC/WU24Abyg78L9jsWS5sGFsXrP7sucBkolS7xLxZJKpJM3+CtXKiKrrssuV+mKVNbrDLMh0qJRohMu2Ur6Ra0FUGTTae6VyKLLVshyCBc9LkxJdRBDuPPzQf1ozqsyHxxtyojwO54cWAOkMvJwGgZl0PQH8depJ8UR7nxOSaIrHgmrMv50r/ATZ0AZ/gDlby046nf//e+AXqJKWdgtLFBEgEgRCQGcnqKsr/DXC5hauAMT176KFvJZr6/TMBwXVunfJdeyYObvh/Iq927GnOyhnP3mYbGa1XHrutrwStojCq/9uqAx5gjbaDJuqb5y4VhpMbrCIHELEmXmQ/psxcOUK6T/w9qLWM6s85EWXocJ2B24qOgyxazpiJU1CjD8UxslJydLZ/0yFG6Dtb5keKkTfSmfhuj9cG1mNHIe4ml/Zy1L8HnHgD365gOpbnwpr9Fl8IrnhkkwzzIBbJnvP5LVeRxxcRXFJIesEYzxDnwdSzJZU/GO10aKSlWrF49d/zKSbe8/yvOTqynARCA2h62z753smaC/xC2dDR/UO3kHPoUh+jQR5K9z6q45GdNGZW/P+UN6ALADpSNsq70nZ+sop4BLnos3Z+2q+onnqQC2pHHeiNfeg5yPgSdFtWIwaqVzkIP/DbMVMhrddhOpz6w9utT1Olb3Wn7rsP3VbfxRcmU9b0cxTLZQHoiSUwZKpC6AAXxnJsjAGp50kxEXqR7QwirVF6p1f9xq5mxPCbG3KVBjvp56WJMa72+s1xu5YXzpVEr6nohcjlPctZ+AWI9Z2LckvqQ1MsdNpHNvRnLHS7R070I5621lVbI2Wn4fHdzaxLVkZH7wM/9nGQBOXrkHcxyMHmuWjDbgiSBBDHX9hsy/enuAGvfvH3o75y9i1oA2A4+tbNKDtY+L3f3ciklCTD7fiEIvtaq6Hy9D3QSB90zgUIkcxB3zigAY2V+79XExZW76e9LR7w/5Us7YW7+F/HD///Szt3WSH1U+fE+4M07XPyBfuDM/tZdpIdkXjhc/GGN+MTsPPoZ/ZjEmLnUk7zhmsKToc6xVmsoxzReK1Z7Hs2x1zfRsbsBm2VtoJzdZhq0+rR2foeTx2IRpOn6oi1wJ7dp+qSnSLyupQWzVnsmCOJRrWJ0NzP6lbUG60SA3Y03FB60buJGd5pvOhqbkWGpVGPCiu7c5ZbPnDYfgnCPVF1zZzUcSFuAOclw/mms7qQeuItyygPD5Emf78uXBYu7cO3w5zybRnaXel4MU8Yg6mMay8J7H3mDWifvMrH7fwIlT49kKmGoWZ0kq4Gci+HXA4Qw8Nklj1DeoAocFLJJdM9NNdevFFc1PVyRThBjoW7qBkxxbdCjAseE47ET+/rJMpc1P37a4yja+BBgPkjZeV0U7nkgZfRLLVIcnz4whxkMme7JKGXVSS8OTLT7IGP6AdHDpRw0QTU6vBiJEuiV7TJDDu+Y/EcKN1Sv9h+uxDSdTQBkNWg1okPVbSjrWBAO82pPy8UJbZtrTXAA9a9F7MjHyKecdAOL1z7EMkHZIRV7anfqrXt9o2Tvae20ff05GNJPz3Oi0wdy1TrJnB2o9r1wqlpk23EC3rFUch4EYhL08TfztjtZC2bfjW5cK40CxWcKo25s4ceN9r3kftPWQ1J0trs+plLY5WIzhMq4G5fZpkcC3nBOUKGett5tsO+m24z19x7MW6FcuwMh9EcQn3FLUU80KrmEz/Ga9jL7071Cnh5fVEQr5GYhIEfzx/M8GB1fj7gSTe77bEO8pO7i2hofEquZ4aNYQeEBeyv/7wAcgpbCu+zg1iFjsUPpR1wBl1ucuBOgCuPmktI/PPeZoSyHzOQoxf34/WiiNDGYkXlByn7jPkZLKO3YwmgwrcOraFpoi2V6S9CT2fDW6s6fz9xgcYxxQ9mfEDA85ycYg3fxkaUByrmeoH/h04uQLEOGoo7aip6appqInz8Lt5fXgGeK9eKzzLXDrc67gR1OVpmTRqlc16O0xptTcflWl62tHYmM2oW3JxtqZr4XFzmrdoXiZ4SHA4arg0ro/6bndd8CbulfNrDOi6EI4t5lWputDgjUo5NmpRMf+ZHv/MeTsVcZyTowdOTD8sYPZ2ot653E9nWiDLnR5k9V78o3u1v8YOnLrm3LZ+deh5620QYnqf1PrZYUgUb7sYued29ZfqrMe/FPwMfD66L1W6X5HfboaxiSefhD8k8M3EhgWJ5+Z8+ahWm7DxGhOyue8KjPhIOB5OYcC+MrSQLtbim3eFsJOWLumVGgvLyLlshRfyFdguHCvTYog8MdL8QZXnn5l7ET71wdo4NZNaU2s2pV08qqcQQ8aabBo5NatRnKPwjeuQ1oaMmB3kpf+LeKcPEnMOcn20QQdKgyFaG9gacwILmjxzQRbs33svt4Om6DqhaAxTKvdG4akoONAPWbvi+JrgGoN/jukPNBI69KCunwnJS03RfpDkhBOYte4/a03NuHj8h2A1snHFnkFKXQxZqa6A/nZQWlXc9eboqbnNNKGoQULX+Zx6Wq3bbxssZ4j0i6rAdqDaFOQNwFe3XcqeEm149Dg63ZDiUZ3YEP9iO7K2A/Nsuh4PvIluVtGWvh5P3rIbLFFZImaSbkJ667Tf1JADwKbFL66Dv6oJMNFy4cBuZpxtp50cIHJX99Cfu8jEo8hV3wZurFcyZ0waujBUN3Mau66pVDhxb2bWMcOjb1aua7rnp1+1r9VJX6bJWW7RV3AWYZdKK3XWH9aDN/LXcbe0VI69liacibdKmFhpVTJrJ5ga6fq8e1LAIbimSrdTwEUCvLZWlNNH0Z0mMpippZ84kV25qEyXZSXDdNYqZUNPAk2szhx13fWFaKVfKJ6HXnymPaJPYwVW7mLdp/3+8d7NICjN+LACPIhnLIjNEy51ZfZ6svqGZ27c7ilmZXN4yqesQy3aqCeo6Cx1UVngiRYuXM284PtF+bCyf2IoQyBg5MSkZZ0nIW0RDFxOE6rhXxKBFaxoCuQy7tBjgiIcjHZrlpe05c4NgXV1E2tV9k7HATFU9wuZhsWwAds7Ti7IHbe2H/KNiUs86ajTm1sGxAglEHFNNNvidp3ZP9cN0JYQx4IPfUMey+UxWFUooSK+0XYkNOFhGn6u1fxBMBXviqzyofBeAYW4QGQUqUeU5Zx8KO7UtOEt8UjbiadUNjEKS2XnJMT7RgowaVvEmMc1qSEwZyEbxQBFSSGklcXkieqWPBHbQ6z/w3PncifZUwks5NQrzZv0PMQqLgcX7Po4QqWW1s8d1ZVvB9NPZaBCEx/TyfAkNIvaSEXN2yA/dmJCFd9A5RK5htHRFv8ydCmli95O0ZVr0nnnHXQbvodOSu1gX7KSrBaGjiFgMTGLfJyWwDbZq28RyZz97CSincidXq/zbEr+gIVnxVcfT0qtklZglreMOk4rl1biWvIkfoAunru9wyyXMJsj0THnNdSIuJCjb5v3MnaO5EX4EKmM8ccE1ufvifr0ecLng4zX0+A9dkuL2IaBl2P4kdxKwTlmzOAj9ruoS67eBZG249ORmOr45eoYMUmsys0s3B5tMu0abTbtHm0x7RltNe0dLTO3hbeEt8g1YgxhTNtz9+PWI/dV6007khmkAXh7QBzfPQFYHE1YX0GEcr5ktyR/rFOgvJ+Yn4SflJ+N/qrFDOjpGWLZAH2OFIZkmhjGzN1KGgsnn5Ielxxm2J48nA2AqB9VH+Yu3K2rHR4bnBY4HHCq/wLHN08BrA9QgpKdPuCcq1tEShp+7nnPd57+lDDCnfJz8t2SDvl1yVXJpckj8X1hh5gdNhmOzc4B8Ll/FF8ZgTEC9ChkEEAC4JxBthUM99X6lfalDs7XCoQ/W1j4cjCgXy0aaJWFuZJDeMm8TDA/gHnkONg/Y6waetDIfTA4nMtRsYgp3VIpV7agtjW1Nba11bW2d7V3tvfyLfOt8q0zH0ofc59yO0P/j6EV5nJDkoyqvcXX396ZFPwEUF/IaHrEosEjP/45b64+1RV1H7UfZZGNk42UDcSxRGIhtT4nlA7yGD+AmBjfjfgYP4S4FN+O2BI/rL3FASld7vz05+iPs2YYMrpStMYVyFL8OOIE9zP3CncR91tvrAT7ZbNkx0idaadoXWnriC3S2aq27SOSou1S9XOrvElB/TAxw5DxPXJp6lQ01ioOr4msbNoGu+/e8FhUGsLIJN3LG60EPnFtDP1KgTIfA1URyli1f25oEZbWOmeoA/VZQl91cC5+MYdaB9PLntqjyiJpjCYTE10ln44yvzR/fZtTyeyfeZVNGl43j+PZw5CvKw99PX0/Qz9fUc/Q0hUZQa1b35iKAs0K1SrVr1Z55WWq5YX3C+jToBRAX9h/bWTHqeT0hb5mrgfPEC84P0THzKDegkPkEVyJzeXRRN9UHqLLtx91VYBTUhFd6Mh/wQ54YUfM9Fl/AqtnR7L6LQiq8QoDNit0K3O6A3xQEmbBjgFfqv5qVgJh1ZNVAD0ZVVWXVAC9GA0gS4Y5OcztJ6XntkcewKkCSOZF1dNWAj0YfdaLmO7AAOeHmC2GYQhK64rvNLXlGDM8JU0nZ5Onbe/mXXsgOkEdZXxA7OAJ1L6vrNIUUzlCO+I04jhONU452jS+jlyN6IzIjtiN9I/c047F1luvW76dVABZAEUAVQCNA51v6XYqdyR3oN5Iso6zSLCO5x5DmEKeNJg2njyaPp2wmLAeg5iAHnegp2tbhtIjmObHBpf0NvwhTAWL/LJma1oDsl9mLDHPDilHg4Lec2NhMGZpx2RBRGNINz8Dg8GWv1r1Qo7cCBGtLpmQW+maHsz68Q5Cjy+CQgdoTbYRTEYTNf7oGoVkdk3rQjM0fugaOsVhq0YoISQvZyvLBzPkkJX01Vhwf5/bb0dsBnRQj9Ph3QQSoUI3JKzaG1H+VObuJLnm7Vr1eUuUhuyktlE+TGoz
*/