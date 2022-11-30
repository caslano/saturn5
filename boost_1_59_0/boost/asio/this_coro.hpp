//
// this_coro.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_THIS_CORO_HPP
#define BOOST_ASIO_THIS_CORO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace this_coro {

/// Awaitable type that returns the executor of the current coroutine.
struct executor_t
{
  BOOST_ASIO_CONSTEXPR executor_t()
  {
  }
};

/// Awaitable object that returns the executor of the current coroutine.
#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr executor_t executor;
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) executor_t executor;
#endif

/// Awaitable type that returns the cancellation state of the current coroutine.
struct cancellation_state_t
{
  BOOST_ASIO_CONSTEXPR cancellation_state_t()
  {
  }
};

/// Awaitable object that returns the cancellation state of the current
/// coroutine.
/**
 * @par Example
 * @code boost::asio::awaitable<void> my_coroutine()
 * {
 *   boost::asio::cancellation_state cs
 *     = co_await boost::asio::this_coro::cancellation_state;
 *
 *   // ...
 *
 *   if (cs.cancelled() != boost::asio::cancellation_type::none)
 *     // ...
 * } @endcode
 */
#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr cancellation_state_t cancellation_state;
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) cancellation_state_t cancellation_state;
#endif

#if defined(GENERATING_DOCUMENTATION)

/// Returns an awaitable object that may be used to reset the cancellation state
/// of the current coroutine.
/**
 * Let <tt>P</tt> be the cancellation slot associated with the current
 * coroutine's @ref co_spawn completion handler. Assigns a new
 * boost::asio::cancellation_state object <tt>S</tt>, constructed as
 * <tt>S(P)</tt>, into the current coroutine's cancellation state object.
 *
 * @par Example
 * @code boost::asio::awaitable<void> my_coroutine()
 * {
 *   co_await boost::asio::this_coro::reset_cancellation_state();
 *
 *   // ...
 * } @endcode
 *
 * @note The cancellation state is shared by all coroutines in the same "thread
 * of execution" that was created using boost::asio::co_spawn.
 */
BOOST_ASIO_NODISCARD BOOST_ASIO_CONSTEXPR unspecified
reset_cancellation_state();

/// Returns an awaitable object that may be used to reset the cancellation state
/// of the current coroutine.
/**
 * Let <tt>P</tt> be the cancellation slot associated with the current
 * coroutine's @ref co_spawn completion handler. Assigns a new
 * boost::asio::cancellation_state object <tt>S</tt>, constructed as <tt>S(P,
 * std::forward<Filter>(filter))</tt>, into the current coroutine's
 * cancellation state object.
 *
 * @par Example
 * @code boost::asio::awaitable<void> my_coroutine()
 * {
 *   co_await boost::asio::this_coro::reset_cancellation_state(
 *       boost::asio::enable_partial_cancellation());
 *
 *   // ...
 * } @endcode
 *
 * @note The cancellation state is shared by all coroutines in the same "thread
 * of execution" that was created using boost::asio::co_spawn.
 */
template <typename Filter>
BOOST_ASIO_NODISCARD BOOST_ASIO_CONSTEXPR unspecified
reset_cancellation_state(BOOST_ASIO_MOVE_ARG(Filter) filter);

/// Returns an awaitable object that may be used to reset the cancellation state
/// of the current coroutine.
/**
 * Let <tt>P</tt> be the cancellation slot associated with the current
 * coroutine's @ref co_spawn completion handler. Assigns a new
 * boost::asio::cancellation_state object <tt>S</tt>, constructed as <tt>S(P,
 * std::forward<InFilter>(in_filter),
 * std::forward<OutFilter>(out_filter))</tt>, into the current coroutine's
 * cancellation state object.
 *
 * @par Example
 * @code boost::asio::awaitable<void> my_coroutine()
 * {
 *   co_await boost::asio::this_coro::reset_cancellation_state(
 *       boost::asio::enable_partial_cancellation(),
 *       boost::asio::disable_cancellation());
 *
 *   // ...
 * } @endcode
 *
 * @note The cancellation state is shared by all coroutines in the same "thread
 * of execution" that was created using boost::asio::co_spawn.
 */
template <typename InFilter, typename OutFilter>
BOOST_ASIO_NODISCARD BOOST_ASIO_CONSTEXPR unspecified
reset_cancellation_state(
    BOOST_ASIO_MOVE_ARG(InFilter) in_filter,
    BOOST_ASIO_MOVE_ARG(OutFilter) out_filter);

/// Returns an awaitable object that may be used to determine whether the
/// coroutine throws if trying to suspend when it has been cancelled.
/**
 * @par Example
 * @code boost::asio::awaitable<void> my_coroutine()
 * {
 *   if (co_await boost::asio::this_coro::throw_if_cancelled)
 *     // ...
 *
 *   // ...
 * } @endcode
 */
BOOST_ASIO_NODISCARD BOOST_ASIO_CONSTEXPR unspecified
throw_if_cancelled();

/// Returns an awaitable object that may be used to specify whether the
/// coroutine throws if trying to suspend when it has been cancelled.
/**
 * @par Example
 * @code boost::asio::awaitable<void> my_coroutine()
 * {
 *   co_await boost::asio::this_coro::throw_if_cancelled(false);
 *
 *   // ...
 * } @endcode
 */
BOOST_ASIO_NODISCARD BOOST_ASIO_CONSTEXPR unspecified
throw_if_cancelled(bool value);

#else // defined(GENERATING_DOCUMENTATION)

struct reset_cancellation_state_0_t
{
  BOOST_ASIO_CONSTEXPR reset_cancellation_state_0_t()
  {
  }
};

BOOST_ASIO_NODISCARD inline BOOST_ASIO_CONSTEXPR reset_cancellation_state_0_t
reset_cancellation_state()
{
  return reset_cancellation_state_0_t();
}

template <typename Filter>
struct reset_cancellation_state_1_t
{
  template <typename F>
  BOOST_ASIO_CONSTEXPR reset_cancellation_state_1_t(
      BOOST_ASIO_MOVE_ARG(F) filt)
    : filter(BOOST_ASIO_MOVE_CAST(F)(filt))
  {
  }

  Filter filter;
};

template <typename Filter>
BOOST_ASIO_NODISCARD inline BOOST_ASIO_CONSTEXPR reset_cancellation_state_1_t<
    typename decay<Filter>::type>
reset_cancellation_state(BOOST_ASIO_MOVE_ARG(Filter) filter)
{
  return reset_cancellation_state_1_t<typename decay<Filter>::type>(
      BOOST_ASIO_MOVE_CAST(Filter)(filter));
}

template <typename InFilter, typename OutFilter>
struct reset_cancellation_state_2_t
{
  template <typename F1, typename F2>
  BOOST_ASIO_CONSTEXPR reset_cancellation_state_2_t(
      BOOST_ASIO_MOVE_ARG(F1) in_filt, BOOST_ASIO_MOVE_ARG(F2) out_filt)
    : in_filter(BOOST_ASIO_MOVE_CAST(F1)(in_filt)),
      out_filter(BOOST_ASIO_MOVE_CAST(F2)(out_filt))
  {
  }

  InFilter in_filter;
  OutFilter out_filter;
};

template <typename InFilter, typename OutFilter>
BOOST_ASIO_NODISCARD inline BOOST_ASIO_CONSTEXPR reset_cancellation_state_2_t<
    typename decay<InFilter>::type,
    typename decay<OutFilter>::type>
reset_cancellation_state(
    BOOST_ASIO_MOVE_ARG(InFilter) in_filter,
    BOOST_ASIO_MOVE_ARG(OutFilter) out_filter)
{
  return reset_cancellation_state_2_t<
      typename decay<InFilter>::type,
      typename decay<OutFilter>::type>(
        BOOST_ASIO_MOVE_CAST(InFilter)(in_filter),
        BOOST_ASIO_MOVE_CAST(OutFilter)(out_filter));
}

struct throw_if_cancelled_0_t
{
  BOOST_ASIO_CONSTEXPR throw_if_cancelled_0_t()
  {
  }
};

BOOST_ASIO_NODISCARD inline BOOST_ASIO_CONSTEXPR throw_if_cancelled_0_t
throw_if_cancelled()
{
  return throw_if_cancelled_0_t();
}

struct throw_if_cancelled_1_t
{
  BOOST_ASIO_CONSTEXPR throw_if_cancelled_1_t(bool val)
    : value(val)
  {
  }

  bool value;
};

BOOST_ASIO_NODISCARD inline BOOST_ASIO_CONSTEXPR throw_if_cancelled_1_t
throw_if_cancelled(bool value)
{
  return throw_if_cancelled_1_t(value);
}

#endif // defined(GENERATING_DOCUMENTATION)

} // namespace this_coro
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_THIS_CORO_HPP

/* this_coro.hpp
tC+cT3qRm6c6IpLf6qj5Y1G04a1y12IPoCJqESdaRW7EK0jlrHUPVJ6/eyqoFEeCWj6fbt7g09989+NTvchWHyTNXfEx3gfUtcwvF/tI+cR2XpsCatoMljl7p5j2rH0govq0CVKkSO8wnO+zZWS6nMbynTZR7rZatL/ywFxY6Ns3D0w7bCaXZ2X2mzZPOkX3upwuTkyGPZbqdgnl3ZcspbrbR6p13dVD9Naq803uTUw8WNyTD/a6BdsEGye7G5xt4rJM3N3n5oGsS8d3XzoluhaOr75oVpa4d9Rann4pcZfEmjqVOFiu81ba/vKLuo7axMN1PqGh4NRG9MALOBZuEjdmL1ghFoAVvsp9MnKifhJbdpHYlYzuKY3osPP9Fsk3SVEzFWpxK6Vsy6HMhVv7ZOb8ycwRZV4jMj7oIF60OFtfHPU5R7FOdaWeB0F+UzOwaeMp5glvQGOgCEk1NhJJG5B0zkBCqX2dNqdzHAXAXjzK+vBbZkFv3yoi+0SGbWUl78P23ZlYACddvATkCo6yZlVPtbGIDVmHEwI5W3MW0fT9yD8jJIE4P7/LgIYHz6zYi/gEDxk5zYvv024V/Ok94jEsuvyDJBU+xKfBVXU0TOmJ4a9OBOZVTZlrEmYhKVYkXmAHRqf4CIjDiVRrVAfq6Q3MCvcqfY+ZFNxaCPrJeKpCXIaOlxueKU8SaKClRKEsZahMklAzWAYXqk/N1BhlsolXguzDHYAkhvKj9CuBBg9kJho1JTFYeoWZe6wYWzgIRW+izjQqpohSBevyeKbOsGVVg3HYlqq3xJsyRTf7cYmtLLjoiURn9LL6Yd4F9GbrzpXYL1BamTYfb3K6MaE67+O2+AnGvEbKhNqW9/XTJVnaIsqyCJG8uAn1RvaR/BFbl/oI39fG48mIT9dPAK+MJ9W2wQj2tjTHPM1JG1vKheRKlthGaoBmTtHYBG4j476CxOTmNvbjFEV6Feqr2lCWsjHOg3h1TeiX1iVvVlQzMbutn67WDpVM12yZEN3KQHBfi/hFOOQv2XoshJwz5SSMbbvbpblGupa5prm2uoa5FrkmuTa5xrpWuWY1vmszbQvySHJMdGS4UBZVa1FuUeUshBUmQfeh1NAsqAl0CSoF7fz17lO2a45rd6Oqt6y3lrey91sjbmHVj4VNUHG7zrfMoyk0CSLKcaqURQOF6tDfUCIoGKoL/WAXjWhExCAqEZmIDkQwIh8BQtQjohDliHREW+ObBZZOehp8vKiI70ysmcB+NB7gKDOPS1jFu99tiGJEMqK50cTbwFvT2+xa9lprgX4/URrkrtJeJAUdgLJCS6A20E0oKTQFasA3051wrrqiuqKyMumx7YPwu0a+iz8Yzxg2BAq2ti7KO7K3gIyHAfBmoERryKL2AZNHcoN1TSajx4TxFveZ/mrv3szFFu1uzlbOTs52zq7ZltmOGXk3RTd5N2UAWQBFAPlNLGq/3O/4BAQ+3hmfmMEBxybkCija2r748oCd9Eiys2lZ0ZQhhzGHM4c1h9eMzozNjIk3iTc5BZIymDL0eB02GDQYMoAYDM8Ozg7NJnhAHL3EvMy6TLvkuggqZ0fMfzgmGQy2QDjXYesScIn19kEM+Mv6kD2Gw4Q4ePu6D9xn/QZ+s/7mBPX8y9W38+o7Cq+qDg1TXpn8lmnY9v4ZrrdSJ3jZcGym0/vL8qux6fYdL++uR8l0zKLTjvoxmUjIXJ3IgWkd/7bmmX4428skiyFn61ABHfKiGP1+NsukT0Oe1sEC2mJyaYWv9YvZWDl0k8CJ4CS7Iddj8c6IZV3ecZ/tzjNpb7NOrQejB8WVioCKgJIbV90LzhT2FE4DNgMOA3YDzlm2WY5Z9uGk3STKRMqkjMSMJONEmGSwEsIZmnZQIDNOu61xTXSXdi8fUNA9KbOVg+A1kr2YREXQSSn4BDm9IkOT0TBn+P36vYBu6pDQQsZ2redxLUsl+/D7kbcuM8FNhX5vOWfSz4vCKnE+Di/UnVei7g6K141yUfo2qvWubMn7TVm1To211Usmj7XVHVRi7EKwEIE0Ux5bEmdxiMMzv2u867ih6ErS3ZHr2q7K+KtUyC1XTzDX974htaHhPSF3cYmQLMjoe5sG5j0qdx6JuKwxHi1TC9L66ESDpNnE2aSqIZF1nHX1de51wDq1dftJ9Un2SddJ0Ele/cv5Mt/CPR13Tp/EuCTNRM2kscSxJN5E3qSaRKfEzqGWIY+hiyHpdYx1pXXWdZt10nWDddF1j3W8dc113uZEk58NnoLW3cBA0U3uxJAh+mVQy68qL0rmMsKk8piW9X09OeI31arllRzl5fbl1RQdUoc9EicaHYJj+lL2RE1l6T86JSM81lrtBZtaF+QBZc06xhWAqWZ7iabOBbn9UncdiYr5coMR7fbSVhqVEd3TaUd7j6aIBV1uLZ/jaknN/apz7ZvysHJN4TfdFFoh9so4FQTC5ee/rzoyvDMXzKRMqXNx9aKnUo0qk0s/Nempb8lsy1SETPXSzBd46sVtTEiFiytQl+PqRlQwTiXssLk1iitSV3zRHaggmorcwdxhihuY/D45BS7S0C8pZS3XnQZPgaftdlybXmfljeoNT2O5JYsbZxXo73SXukx72SeJm1Xpf5xC22G3rzIqmanA2ZF3J2/PNOmttjKoq5gXntGgNK5+GKq2Ea2lnFff++CO3Z5UZd5SFo1YQaycySBk5luupa6Xrjuv/a7vrjnukO/kDmYf3q80+PWJ9Xn1ofW96vtRG9Um/7V/mb6deAbJg9YtYs96ze38G4GPlRn2CuZNKO183B7rueBN2N2Qv2V3g4xnqJKXzB39nYVfU5eZTC7tFN62SkitzLyZg4xED279Sy52/CCs1/hPEvw4nX1S9l8s5+CtvjpyreucFLk80siIBxw2jfxy8RKuWccOc7xtDIABiLAEzmEiVgctmJ1XsNvOqS8Zq7/NTjp9aR/SHu4vpEQtaqY0dlwRJqL0bGk6slE9WHZInjc/dN5pFeqw0+OA0NVeFuZB+ey+CslTsMeCFNUsC+ugL+w6hOTS2bLo1EEsarqro5HXFH4mRtLBLFvBCaC4zggDnpEEjjMlAfcjcUqTTOoOeUZzhT3qjq+Pu3P/77jLVJbV2kWHJ41njQW0EyauoksvZYpzSlVibfUs03MjKWaZ1Geeq08Lqc8+GykQnki3NzQSrGqdkf+oIlOUE9kd2R0d8DkgKiDy5qzqWuQO5079jvsOcEft135ffZ9933WPfBPlN9Jl4XO2CaGoT+YGZ5cgnzydl80uygG7WUl5aQQEZapls5BiMlosiZHMaFluWSOAd68sgvm0X8ilMsUQ9X+MaCzUGKxBqGXtxIS7yZHOkxxznYTiTlbx7Bp6C1pW1I14fvMEm+QHKDsyrSTYDC7B7cXj38lZutJ3Rpmq1+RFDyp6h1ernumENH7uzJUpdoLSzuaM50zlQEV3jREl89F7zOcCPmGdQ6aWNQ1VDpQ+IZ2Q5fdODSYOorBv0h9yajXnbfZcztFuCBtPPcf7P/lK5tBZYZvSK22hiIuBU06xxie1fYVoUY3EYzU3rXNbv106S6O47ovdSwYgI/aF78VXsNqMB3a9UG0/4Zj1aBK0YS6F0chrjm9MXpHfvh6HR8vl8KL4dT1B3DjkyW6hGfkljRtvMSKIsdByzLH86ZGMrrEfkh7QKW64H74E4Hmno6UvLP7C9F4wTMduE9csJzzHWkHyxfYmRx3hQlZf+SazkRN4fo5EfYAu/q6HSCcPjpo1iup3gGPkmzllJp59sSoVmotP6E/iX4ebCdJT7hWf6iWr0/zR9tCjLgcHVZamO3qmC43Yz3S8GtavgjUCZrteDmhkNXSKmQDbN9Y9dpcLbORqlv2uSa5fB9CRYSnl333ZDbgNDHpV9wvkafd+fJX+ZQQOLT9waovfciA2h+84VAVckvnirBBcos7LKPgh2eBnulQJ8KCj/GpaGFujrKrC6e3XrakfJVn+/Wk2WZ3wTJcxiYdgbF4j7+N6NZ7OvRPO6o6dnY/VnY5XZ6KLnkSt6zPELVUdd18kDttusn0O2wOmUftC8KQ62j6NLLjt0s4fbfUPiEjdfwdrApZPhLzOWzfNPI+LUsy8zppmWxx9QjquZmCHDgEXUie9ERLu/o0fL+rIhv6fUsCXvCP1QmpZH39eO9YNcHMoU/eTy6G+CA6wmeEF988uZE1fRhT6i4QIW+bLqQyIIALj/VVcXBBuh8JC/ItWtI7Vj5BXCgy6dJvvBUjugYPdyc1q1ax+vTIkSKYR9ayBOR2RjcUAsFnImG/QkYikG/JxPA+TomJIiR85dbYDnS7E8ViSkOVb74OpbAoTKzOvpmlWB3bjL/61IrhcPvh8dX6MqYa1e/OQ1QO0fPTdLVesfXt6h7Hw6VeuIFBL8Jg/2BmkDG4AB8hhA3tcArI+Wz3xynK0QNPyQbsCNRfZPGXWGs6C9MNdtMoZxTBnkEWDNCkLQ97i5qRTJfhmNaLTzLR4iIKa+FBEAl9nM9HqhDzEd3BeodopeSfQH0nvQvTbXr1wPcp8iSr3nqpwKkRhTQPHC2uG1inw8FaoYg1dtJcnO9k3opFJWgDZyIdX8grtjvoDMHU4jPS7Qn2qEHLrO2uVDEm8Ll+fI3bFichV9qlaYnlu7cACvPvkb6rr74GoU13YHck4qwkORAfPafEv1LJw91VEgmggrKLfFrbt3tI3osV1fcnGzt4pqQxVD7laJ1ozOvY/5m79Kc0rQjuji9ezUyAWO86PUBCPyJbjDZ7wYLy8cxqveRsTa3NqXpzGmMkgyU7ybeXT+yxPGttLZqhBBAu19+OKMsJfMx2CDSEbj3DJPZvtLXeQ2oKIHDHL0LVDWBO/iZdg3jbNkBBtbR9dcNWSe8xxZp31rONcY95R3NaZbfvv2j6/NKbmysG836g3an66MWhs/s6Y8cb4vGRccQvFkoMNQcqCLTxeHh3KuXbI2Dfw3ucTpecVy63JqFOI2G/k+2cPcgJwF+L8DvfV0RApvANxBVxuqcbb8YWXu2BasP54xL4c1nyhTGPXs/vRsHtTXIqW9A4czobmcVSpbSRxKibB2NGiknFdOdDmt/IDx/Z9vG/iu25vkfdCRHx6fjcsLGL4Nr0XwbrP/skxx843ZjYy0+Axbxb8zEVeNy9pXJeMKZNJ7+lZ33uL1nG2DnSXY9Y+pz7ky4znwvzGewwb0Wi/6D6lz9FV43c/74br9l778thBfbfl3z7cskXAkU9svWJ8CT0vKeEeidvJYegSd1sEchNSq7SJWHHxw2lmDhjNnzi3ToV0eGLMc8v2pNsSs1RmG6pv9bZfuFNRq/jjn8rN8NbCerBfaJDJRUx8suI5tYgpKPqKpRVwbHiSdfmkA6ZfeqUHybWp8wPJzej05feceuVpceGbMtNitZdxLWu4f6aolOy2vMAqkMPOfo5xpMKk9DVMkitTfowprlZHvvFuqCh3gHGboxb7d5nKAz5IwZxRLrqvr6T2IGdgOeLKgsBQtbpk/ZcDUOx4UtBcKgAvJoqmg4LLnPNaoOJ5Sh2Jq5TFr7sjd+23dVgdzGI52UyLTPuWtD3i/hmlCSZ9IePXgD0Li9BLVFq1zZ6nL8DvlDVUsl+SnKr8MnYVeQ0jUsn+ilEJIw9m30CSpqwc0qu1ozR3dUKRwCdSlNUwHs9cyyUl6pFffBLgRDdzSJ6JVdDAHHNoX59UmdLfEGsl4iTfu4PP0OVty5UG6ohYTM1ULwcbgJfN8XhUs5GFl5WkWQ3ib7bQIjRYsZVtyMTat5yzzWGeDPMZ3Ja0tZ8crhLusKGjIcJ3okcXFsrPVuPA1r98rKjIUzuEWqkb2yXezlFCngk81986hVz0WNTWhl3ixVp9BGFaIHccOgqweDkJZNhbadRHxTBoxrdbawzBUbZ+K16TdBxuFwbHqs9gE0dwyOEaBD6PkjXCMQ/g4eFI45PWF3LuOb6L2yWNDQ1B7t7m3IOVeNQEZ0u1eQyP7abDmAcyllp1B3D3YU2AybY3wyQjGdbCgF/8rupvrCKjUQoKDewc37e18Ad4F6TmSHg6O3FmGaOTW1fHbMeaDqpSGRZPSCzxbEjVWxEkZiZp17O9qR9kV2nouFN5WO7sKGpd7p/93boc6zqUqiJrRjKWtQe4HS1WmkMkiewji7Ni0BwlN2cRXYhAt5eh/d/7xIZVSwby2oTb9EHGOnlnB69mbMXjxbViAUDSyjwAulaGOUD1pspC4Vi2gAK22a9GCVvvryIRwvIqsl6PLRh4zRHrMQhJW2w3YOROS5MoSICTiIpw10bHE2aoF+hB2WAOHUkzsHi1jo/eAEP37X4uAUvvIO1sY1MRN50CLZH5XxOVSJf9lLDMc0PYN5XSDi9IYfSih8TTYVWYvncVvN6a1IvS4EsavCvD0oRVM1x81TA5JbWLC7mSF40el3ITzXEvGAKm2EbrgX7sjDzTL7uoGORuAhaPnYmUt/5odUkeycI1mfQ3ZCRvf2EDuDl/Fcd8EX9etGz9m3V9Qwh3L16ilWv5k7pavcPeL7f9qI79Lx2T7bPplR/Ye6vtoM8xv/1m4cj0EbEmbSm1sKSG6FS8an0pS0/RKdg5DlJpPdIg2NUhoB/+oJhLdpv2eq2sH7iVMKTYZHVdX+mv33Xmyzg2PHTGc5MUiA73v9hPELNOZVy3vlPlgkKJlKZX/dMdudhs9+YndQhan1w/X3jRo4Hhc2H0NWF9g2fwBAXlOGGCDlYPubsOvnQBVuJ2WVkSpCFH9jNbshRBTQUKvhnpTLWYAxkzHJfmQV2T9sFuNirXX04vEe/G4WfnX4wqFJlXrmaFKtyioWJ3FHa7D87tDG4Bc18XLSyLX58k82R8qacWuf+st+P/vTVCzzIapCKPEf58l27OQ469RDys6jtTgfbPkABQ1dQ6pTVaI3Q0b1nBcgbRW7Zrxc26GXA53g/Hm9EVEb8lE2moM+tN2P79RZl2QtIyDQknvAw4d8k+nGyntIj6Ro2fKvipUHZMTuJvbjsmInOrjd7uWAg3ATaLhy0XSkLSWzTZBx3DVMl8c4xC1m+0ahI+F6qBecbNXAm76lwZXZUOlkBIzDsn/YP6gTnBvTRrbNWSEmIbS+AkMzUFUYoGuuFI3p25Fp9OB0sKD3VD8WcealFrqKVhqGfKl5zGZG19gU7PemZlfQF/UPvFHj1/q6jFlLtTK3FZCibELnmSC49nBo+c+gjLGPe5oYVTzdcfC7Hcoa2ORJXsVqnMkplu6LqaDuAaRyu33Q4GYlGd61J4USVvZUKQf6gOr2QL/9WbhOykHyz4RXa6Xx1f3zcu8zn8Ap/RxKlTBVJBGHDlvrySjR0Kp4SRWN3pmz+IlQXM8CJhyEhsR1feG95BeoLu8M4viOWNQ8SqgOl1JBHikcO4bqvZETTXuzYfeb1sTzjrCl4gbQzz7ZpMqZ2VSsG8Fi721rbnBXcwm7A8tmZdlMfAkqxnmbtle2KdzmmbfTSiTV2td3fZ+kt5vbtuJunjI/ZeEtFtJUvlB5QLUst3re6wtu7pnYID1Q7h/Q7+KzVtwYr5kQxjA8e3s6v98Ox8TJKkJZZ2gFxNdlAp2b6wAtXix3yBVvNkHcPa
*/