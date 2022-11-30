//
// experimental/parallel_group.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_PARALLEL_GROUP_HPP
#define BOOST_ASIO_EXPERIMENTAL_PARALLEL_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <utility>
#include <boost/asio/detail/array.hpp>
#include <boost/asio/experimental/cancellation_condition.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

// Helper trait for getting the completion signature from an async operation.

struct parallel_op_signature_probe {};

template <typename T>
struct parallel_op_signature_probe_result
{
  typedef T type;
};

template <typename Op>
struct parallel_op_signature
{
  typedef typename decltype(declval<Op>()(
    declval<parallel_op_signature_probe>()))::type type;
};

// Helper trait for getting a tuple from a completion signature.

template <typename Signature>
struct parallel_op_signature_as_tuple;

template <typename R, typename... Args>
struct parallel_op_signature_as_tuple<R(Args...)>
{
  typedef std::tuple<typename decay<Args>::type...> type;
};

// Helper trait for concatenating completion signatures.

template <std::size_t N, typename Offsets, typename... Signatures>
struct parallel_group_signature;

template <std::size_t N, typename R0, typename... Args0>
struct parallel_group_signature<N, R0(Args0...)>
{
  typedef boost::asio::detail::array<std::size_t, N> order_type;
  typedef R0 raw_type(Args0...);
  typedef R0 type(order_type, Args0...);
};

template <std::size_t N,
    typename R0, typename... Args0,
    typename R1, typename... Args1>
struct parallel_group_signature<N, R0(Args0...), R1(Args1...)>
{
  typedef boost::asio::detail::array<std::size_t, N> order_type;
  typedef R0 raw_type(Args0..., Args1...);
  typedef R0 type(order_type, Args0..., Args1...);
};

template <std::size_t N, typename Sig0,
    typename Sig1, typename... SigN>
struct parallel_group_signature<N, Sig0, Sig1, SigN...>
{
  typedef boost::asio::detail::array<std::size_t, N> order_type;
  typedef typename parallel_group_signature<N,
    typename parallel_group_signature<N, Sig0, Sig1>::raw_type,
      SigN...>::raw_type raw_type;
  typedef typename parallel_group_signature<N,
    typename parallel_group_signature<N, Sig0, Sig1>::raw_type,
      SigN...>::type type;
};

template <typename Condition, typename Handler,
    typename... Ops, std::size_t... I>
void parallel_group_launch(Condition cancellation_condition, Handler handler,
    std::tuple<Ops...>& ops, std::index_sequence<I...>);

} // namespace detail

/// A group of asynchronous operations that may be launched in parallel.
/**
 * See the documentation for boost::asio::experimental::make_parallel_group for
 * a usage example.
 */
template <typename... Ops>
class parallel_group
{
public:
  /// Constructor.
  explicit parallel_group(Ops... ops)
    : ops_(std::move(ops)...)
  {
  }

  /// The completion signature for the group of operations.
  typedef typename detail::parallel_group_signature<sizeof...(Ops),
      typename detail::parallel_op_signature<Ops>::type...>::type signature;

  /// Initiate an asynchronous wait for the group of operations.
  /**
   * Launches the group and asynchronously waits for completion.
   *
   * @param cancellation_condition A function object, called on completion of
   * an operation within the group, that is used to determine whether to cancel
   * the remaining operations. The function object is passed the arguments of
   * the completed operation's handler. To trigger cancellation of the remaining
   * operations, it must return a boost::asio::cancellation_type value other
   * than <tt>boost::asio::cancellation_type::none</tt>.
   *
   * @param token A @ref completion_token whose signature is comprised of
   * a @c std::array<std::size_t, N> indicating the completion order of the
   * operations, followed by all operations' completion handler arguments.
   *
   * The library provides the following @c cancellation_condition types:
   *
   * @li boost::asio::experimental::wait_for_all
   * @li boost::asio::experimental::wait_for_one
   * @li boost::asio::experimental::wait_for_one_error
   * @li boost::asio::experimental::wait_for_one_success
   */
  template <typename CancellationCondition,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(signature) CompletionToken>
  auto async_wait(CancellationCondition cancellation_condition,
      CompletionToken&& token)
  {
    return boost::asio::async_initiate<CompletionToken, signature>(
        initiate_async_wait(), token,
        std::move(cancellation_condition), std::move(ops_));
  }

private:
  struct initiate_async_wait
  {
    template <typename Handler, typename Condition>
    void operator()(Handler&& h, Condition&& c, std::tuple<Ops...>&& ops) const
    {
      detail::parallel_group_launch(std::move(c), std::move(h),
          ops, std::make_index_sequence<sizeof...(Ops)>());
    }
  };

  std::tuple<Ops...> ops_;
};

/// Create a group of operations that may be launched in parallel.
/**
 * For example:
 * @code boost::asio::experimental::make_parallel_group(
 *    [&](auto token)
 *    {
 *      return in.async_read_some(boost::asio::buffer(data), token);
 *    },
 *    [&](auto token)
 *    {
 *      return timer.async_wait(token);
 *    }
 *  ).async_wait(
 *    boost::asio::experimental::wait_for_all(),
 *    [](
 *        std::array<std::size_t, 2> completion_order,
 *        boost::system::error_code ec1, std::size_t n1,
 *        boost::system::error_code ec2
 *    )
 *    {
 *      switch (completion_order[0])
 *      {
 *      case 0:
 *        {
 *          std::cout << "descriptor finished: " << ec1 << ", " << n1 << "\n";
 *        }
 *        break;
 *      case 1:
 *        {
 *          std::cout << "timer finished: " << ec2 << "\n";
 *        }
 *        break;
 *      }
 *    }
 *  );
 * @endcode
 */
template <typename... Ops>
BOOST_ASIO_NODISCARD inline parallel_group<Ops...>
make_parallel_group(Ops... ops)
{
  return parallel_group<Ops...>(std::move(ops)...);
}

} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/experimental/impl/parallel_group.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_PARALLEL_GROUP_HPP

/* parallel_group.hpp
JgoY1qMvcnm87rbteCPgc7aj5w8vbDybQk7hEM36lEDBkEjrQEj9RkzaCLzf9sPcTTQMq0uJ/gPP6EvtRqT/tkpSCiMhOUHdUB+2x81uw9xJ4DMVzWlClBQu1fzPGx4ClFgLOm0ECsPBkrOkzq64oAm3OZNEUiIr4vtBpxQnjAIF89oDtdfUScYfmRSTE1jD2EsbwkHVeOIiArNXCOCvt0KVhoBMavxLVNdLeUpPEQiGCwp1wM1UknV3r5BB5KFjTC/i37aX7zeeSDbtZnXnHo1v2/4QNowGitgdeaYNulhtDUhMMvD7fvYUpcKfrHGuG2kXT5hAijE/cRVgq9P1KaiQfejuVVT+4jDZbHX7QFVhcc5c0oBnVw5nFb4z6YaGn9ABBtn39RLAzolyop4gMfdwLYkASoeK1rfLyWg2HSBTHLFC+wj8uwyGpS58t2Gvb3AWAo5nBLRoMoEGityJx6tyBqFf3oUTAIBMDqhLvBkSq74IJ5k6mvUFErOEeK0mOLREIyxO3242AY04MP5ZOk4z8JWb1e0OQwVFNCsrkqTTn/N3HTMwOnVEzWC31aY74HUVM3NFHS/1J0GnZ0ZxSDX/ZKiTOKQWU0S9uvTrXJT9mfuUHVb00d/w48KVgbBOQXpbVGwzDt4b9eqGF4kOXYTiGKFuh14BweWsVQcOo+ju8qsIHtfEVaHN7R5MpysCaooq9X5ARxRcG4rSfWs7K0UBugItmBpw0M0HgI4cfuVXc5gqxdZTir9qyqVwPZX1sh4vs9GSLlE66DoYmif5PM1L6JRXaXp/8bOa4AeAgYjSmMCwowi8FwjUfv8ozAydVqEbMTV/FifJY/c7eYOErdhupPWaaxP8pp17/HCpQMQLypMHir236NhxoPDf0aOMosoE44ACLxzDwTOHGG2fH7EsZeN7jIhXtop6pwjiZtG8MIc3iwJBHVEa+vMAgOEs/N4JHR8cR6F3Z5Kz/B39RW05StVZevxyKnjODKmIN+OeaDw6AZ5XDaNuJjkZfWeOs2ZpeiuXBUM2Xf97atIgDApJB0d9z4drYvD0tKjQSuBz1+9qMhJdcVLeD41CKZtnixqhqpbFxfHVz+t8Iry4vRHYvFP4F2HG6rrtED9b+vBhisUQZDDWsNVjaUQyva1bdOW22HFgPa08Pe3fk04baP4Qaq8L7PFFNCR0qGK8JLp+cTxBTp+tHpc4cF3rzd0KLqikBe8fcT2fCCz3e2/nFYV+oUpAf8AGffbTXosdbIcn2+HHn69LywJYTUr3Zktyn4MgBhPMTxTq9I7XHe8sIPCeEnn/ghQV7P8H9cluDXp/AIBDS619Y5BkTbRttc1p27ZtTdt2T0/btm3btm3btm27+853I17E+/3iVUT9rJOnMneuvVbG2jtVZZ8Kfx/H6m3qt+c2zoEGq0BGCpn3fTRy3YbjP0MEleXKU3WuujbrVbZbAaCIlQVyvbdJ2gv/fNCAyEUT6VPrja/FsW/1ddfNTUbQJXUcXmpZH4w3QgtEQHHsu3rN7B3n3uhM4GhEVSg5LtwzTy8KancqzY5d0Hc9zjdpYB4izdH7nkL22xd7vu/0wPbSDCnsU9zUUqcnmYPUzw2LlqSd6X3JLWSFeghXQsJoeabe3G+i6R2d6dg1EstTcPuKlQZrjVMEJ/SPCsXCv0O1kiT7kW6wY+7SoBxJkM6kHpd3ih6/3pVx7L5QPNgNEnDw6O/mQyK4VLczVEnuaTGHfO3VFFe2Y2nwDM2IqfQk8r0dJtC6KnHHNPB/9iF41+Zm+JcqIiyUUKoi0LEBIp4t/HYz8Hw+75bHEsjVYvD5dVVV2/EMiBtkmkYN78mrmXSwlzOufj64IYuhgYeagucP00A6T5APkJuxkAC1IrUFRMPQvFuYurXO4JQar3fnw1El8WcFoCLOsT2Ofuz1HrIS6V9xRuNDc8RhKpwulZDw2w+31y76JrC7EovLqW7sX1OL0qmpDfaLpFjAAdaKPFfrUL6Nax5O/KNjBDOjfDEEhzVJi/W1+j5CJZoum3biv3bcypNWGiVZ5WLxHrfw04dburYc9Wt4p3Vg6bZtnfYapawJ3F5j+WKnCUDiUL150tyySPaAbBl0abwlFyq+xwSMf/vt73RAMsYyqVLh8W+DQKzgOh/q9+xzDc0FvBTaXizjPH/0pAYTRxsOV4o5hSrTsoUhR6DTW9crVdwYar20VcJCh2LMIgUeyX5cjnR3vnvwY4WdiE53X1R3pNO17vrPwa6IHWEJkuCifTf43MM8fD5bucYsGxU3l0ODgPOVBWXBa9Pz7BWw2/bF6u69UZ0Bnf36XO02IHfLOh5mpkTeLU/qV67+8wAALP/TTuaHQk+nGk1kc+2eG0OgWpPDGxKCBWWip88Z7Rq90flCUhCs/Vp7DcrRbsjIfILewzogx0daI0nJkLjt9bLV0WoRBPN4hf99G+KTjZ7Ag/zfNRVkxZo/fmZLfa4c3mTOzZoxfO+nedCIVUp0uSIAaN3f2T4jb8W/NnpYXykQ6LlBoV1yFAVEOT/rw4LN1Mgk5IUoOJj6AlwQzVQkG+WhSi9BSRLZ30lRSDrRKDk6G1SA4UlS1vwiCUAlJm2PGd79YTyqwoD7i1Lnb4Yfy7EvolEXu3TTUGJz9ZQqLY/0y5cir5ps9OlS++EG0aw7zrQV/PJZsGPC84Sn9nzahpSlsy3b/7QHVcC7tAJgZds4tvxTVkjbmOp8TOcj7MApKBKZQvdAsQCK9V6JfriCBL9tBlXf4t2JWx5B7AbqQLIKvo5kMha+VnGj0n7nfHem2a4lHSYvlE5TcJQquZJar/yS4+lzEofmeiHdfKg1SbCvH+eupwAYnK0uuUOGJlfpVYszfO4dhZ9xEi+YBpzBMye9Tj/tsX9tJfo5O4kb4yIftIOqojtvEoHKApAdQZNy3m8WaKxJ9lEq/nxQgOiqu8cxt4s+qx6+Qr6LLcfNuzg/9gr1wITgjei4t6U9D9UQOFkXtO+fx+q4XALLK7ae3Hldat5tNYOYh4MjLtsPn/DfGfseWvP1THPmb3AMX7BEsGRUpbFt4bideBUD1zSP5OuB4kJQ8cSeSgBLFp3kwD4dwgvnvi76h/BOUAKVQJFuiGPaku6NM9OaAAv3CiL9wsg9O0tcsdlqbXc68GffM8phYK75FlzuVsvSRy+vbuUSydoXQ3S0vBPnu4/LYdoSyMivFNyUNJR9Ra0U/3sgirDAuGWu22q7B8kWP0Dc4rNm+64CsNZ1UpNLt4xuf/B+6O+gZ8ii57Ept9vU7SX4RaNddothw4nwSPIGrfwIKRDvgJ362xGvKijRdBt594sYU/DQUMSAqOJKmGstJfPdHprGAl57FpmJd/gUPyrDlMa8+OekZWoQwatxhakMm6WcubCxFbN1QsPFM09NzEta3tFXn7feYcCJ/wcx0BkhJn9xaSlpJoffh2KndjRYMRUavsjAihKfb3Py4yPr+Oila6OR77mUJ6F/qB3HeQAeXRZiL6v0VRThTp1t5lMEIIRU893K0mcjkCSdQ0KAjg65oJNppCNhe9ubJ10BgETAyYRfMHzsdScO9+Z/Je9hMaLrHL15sXSS/5KXj73vD2cVh8n+e4TNp2UH9I3R7AjhuLW3XHIKMDBQj6nUfgnI6UYHvB4Qx/DM+4sl4bqf5j3hCCpD/ntHa9Il3L6waeEfxwS3pwR8VpmWny3lA5Y6l6p9EzRIZNkGhvReGcH7B5ttaQDzbwgcRTEzUIU6NFnjDPQ1Bv9RCXjGkj4/hYHtjv3SvihU2bACdRuSuqvRrbG9ksx1clt5tWy34zRVHBHLo3wcrfYUHbsh1AqHM+m9qInJOjVAP1GJz/VBzO7iDflcKv5DJaxYfH2ZUsny2ZJf1GIw1VRl+ZOKcnqAz7NFg/WhxMP7jTVDEkc0QdbAJyqGKCgFh8RYNQgF4Jcv4mzdRp90hG++dN16erv0h/WNhktZle/8shaIe2DbHVh7EeN9wjTGbTHxqVAh9ozCMvgHknenU6kehfernAaM0TOmGNzn6KgfTDYEvC/wBWyW7h51Gpnijv7x911N8Xep0ac3Ghohv/vcoajsU0DiDA7v624AT/+06JtxCu3PF9NDHkKQLUZrbhc4oipmxPPGsvbDwUFtgdPYVcvOtuNeEHryHQc0mCzQrK1y3hgU8qDcx/GSa6l5ssZLE/1eMYfukWIUdvhpIsoy8SmWI0Ge3xwou/Stnx4CSX9aAZR7E6RSpQiLHzUpem103ZW9EI8JuDwTD2+8O1C2ZPiG3V+S4ub24RfNkAs1dooRIMb/WHP+17icGzOWNVkeKQfGEDkzGE6mJudCBQVeUfUwtZDJwaDz1CNm13PFuZ/U/96M9DDNfZPIfQQYUatWf96AaDQfKhTdGoKueJ2k97yfMN2NQrS/x/95HaH7QPqVhszYBR1sfQZ5BnAWkuNGw5fhvFzekPmzaruwNYZLRwM8x9mo4Ct60l1oLw22arQyDsKVagj3ykaPuYCIYj40U6vfCrrqiJUTsf74p7AzaJ2HAHNvv8VOmvytUs9tleXMQ5ytlz7cmBEWnAcSdBxhAqpjepcuaTxzRGwR7u0g1oy9l3F/82FqL+KGeWmhOOQ5b6NGV/BML40MBOfT9RddaUcp82pd+104ufeX+FWH4/l+6zOXwGpkQPdrGX1+Xsvd9ihty2Y9rt5HWAWDti9DFXUvg8vX3L8Hutaobn2CFcMgaIra7dIGd4me0fgGCuRlPOh3aQw9SSo0u46pJSKhopMW+IcNwNhmYt1UZbjC3Wy5A+S3k90jO+3V0SZykdi/2HxFLoisyaNk6AWgihfc74CDHDPZSAHQ40p0AkRGkZndmYQOnsX+zuNq3Qbw/Qu+SLIBwnS21hgVucFcue+9CW0t2+4X8HhGI0FPx9T4P0PoW90Obo9DVcZ/Cz5ACSonK39azxNMbw07vcndFmTYrQ5U/IXybP0JDN61o2oweNcn3y52JgMr+EzyX6MN2G9SbFHi4kgMgITD4wZlwRT/rUVjUl6Y5Kow0hwg8I0gV4tm4KFFW8ntbb6zkCYFArPes25XpsDbTqun0AggTUDr12t6kwrpC3R0XEpYHxBwARNX4wuCTgAEIQDs5nJApBKd0Opw0z4T2bUvzPkR5RkwDAbRXb3p9TDFbjPSFU3ieISvxvOeMAP2QZPqk/v1AUtgCYl2nrMrg+cfSAylJzNjIq0dK3EiUJZkHxU/Ff3zqvJ3egc9A9oRkZsqWNjWXglJK6Kzf2xAHfJgj4NP7Uo3DHxQhja/DjoDKtSxtXBM/o/KKU8pg9zDvWCAbTL5HI1e5L1SzdMCtdmpyxYyhecfKyD0QStxWFmNhQWKcQbwtvHTSJG56tKw/bvTOFfgW4bIU1aImel1uXWf9RJoFHQcnnb4rNW83db7vZ9vV1P8tWLUiF1nQayhVR2q1szVNxPUzJEp2/EM8jQ9+vdLJ9e7gSAMQaKTTAdZYpcW15xAfxIVQaYcLb2UmAtZQ9A1+yvWvxs23n4hXxUyYPDcyXuE5/aR8kedZZCaKip/xaJomNW7e2+Orzs6jOWSzK4G/wJpuLYn/x2ucKRLoObaEt3DyeRLBJWoKa/2picmSkyRv6iz7tYQyczd3sf2joSuFwYrj7B5DpNuwoDAHhgqtZ9UZ75Kv5AeCCMPWmFELEcXLOpksAf3u9IaqJnZp3P71aB/2Ho2Tsr/qk3QcVPVaRZ1cx0B8unwF5tgaVRDbFqCrrm688cjR0zUBpRAUTvyzomWqrbWDF0wfsJ+mvtOSo+5weanpCyTaUnk7iyQwzn1sLag697JsMVsorlVo4vNuPmqdwmJOJzu8126bUh6Stl4pSwKBj7K5YBkO6YWFseHoUqs7M+WazDhNq5GId+kcEjiEecZWTMkTDRKuw51iCBSb1mirFKSvXIyJWqJyipGWHNz2lyKrgF814uBkk9/hv1zxDOmRf4wLiskvGdPQVTMbwY8rrsS6usPumKVtQ+xN5SIawff0wAptc2HK/rd4ZkVQOjiPy66EoktdD+eTCCgPFrIpWxSwNqAwBqy6R2DGdMy/hC+sgWfq2935sLA1dbAbd18w3S89HSUawyAZgXTavKqsydtkUzNCz3lUzFcUqWy1Kv6q5w9HqKZbxA/TD2wUWTYVYkPj4DyebTenyGmILYdxesLsI81Q8k2jT+jpCP4HoZAiDbkUmF+gXQYtXLJgNL7pGpqW/m2/YAfyi/fdk9AF9bE0xrxit5aBDrtP8n7tTkws4X+R1mkYaZEHUYurgX0TebzinPnlb0z8tqdwuswlDi69MQi8I/ESS18hT4k9IZJ7FDcateGZdc11oLjQc6hxkl4OxZnjShg/t5JtxAV1fjvayyoJSyCBdi12Z+9qj7aOvAFLOx9t7LI8kIgk2dbeotlvbQf08oDu0ymkPFb4q7I1skQSF8//s2452IFWyUIpN6zePasfU6qmRsF2TaGoX5OKlk9aizxNCi973ZM5+e2P8kpCgytxMHAAb4AhvTb31HwgXdgC2q63ifs9+k3atvNrDX3DaTAiA2iv1/5IEbHyBGuFPp2sl70yIFJfEAJbENdzKfSTLI5kQdsNBApoJGZcrnxF5rck9aeC/DTlz1u2JBw3Ct7mWd5VkedoFYogTE6dPu6xJk72f4GL4vJGLvd6JuFIbBaQZXwAiNXJXX5V7jklrJsmHU4ue/f+vbm//Ei9JN3jszHM+VxQVYzAw4gDoVA9gex9g/c21zs5Y2SUInCjHgBZ+m+QFYCXzsygoTEAgMvAw5Qonp0AL6Iyspgt4km6kSF9riD+L5LQr/fm2JRabGZYTczbe9DiGVfo7bOfe/x2XAxEXTtAab4y8bCkmh0x2c+GIqk4mqEdzzcGp/3AIkBFjYPyKjcrlbTZdvw9qwy84HcIQOSGDcAwwHA6NWdddT5l3hIOPXDVpyxwS1tuZqlawd73G7j4v/V/DXwx/f2sR8EjAxZV1PqD9YisYsfkLLzW0uovvOcx4ycgATiPCWHiJjqWdkrLDoiBYYjqAHW4YGsHvIFLLDRYhI+G/HOB5CSKvq2nqL6boi+bRVwQOJuL7Ztu52LJ3rOhcCqlPxyTPePjZ42un7CgpYbRDfuAkJASKX98fYL8SjUGvVriMunLYo1mTe+LweuJBbnVeNC8Ew6a4WuYD4xNHc2roxkAYvJhBWJX/2FSw8jrcsmGXvjOOeTEIQ7wZ1vP1IweQDmcAr7itqIjI4xik1xTPr6/eNaRfGr7QKwrzxlKBRQ8MkhklGihIUPbwn4b9cafku8yhXJ4uB4KYwyOGOeJL39W5gj9DeCbZDApCTgoLtztFlbKtQEpAClsjjXeZtXMPS0++Bg3YoSqMKv21h3dKysYfdeAo5apIXnWWGEptydV8GpDjvfp4eUzccztKM4+qrOhJxfNx2YjwDOs9bLmoaVvz/PVivaAVa7Lg0Fd8fD6wlyfG1IaplMwKKCRGpCMMgqaEXj5OhRNh5bl+9fcMVHNj8hbs7k1YkYCrW3JBSHVJBU1jAoTg4RrhKovcC5Ikoqxbycg8CBuUQiPIGjof3UVNSEeDVssEhLqr2g1GZP2yFBMSBEfuMxsMn9J34B3txCkByV
*/