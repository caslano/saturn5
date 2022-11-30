//
// experimental/detail/partial_promise.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2021-2022 Klemens D. Morgenstern
//                         (klemens dot morgenstern at gmx dot net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_DETAIL_PARTIAL_PROMISE_HPP
#define BOOST_ASIO_EXPERIMENTAL_DETAIL_PARTIAL_PROMISE_HPP

#include <boost/asio/detail/config.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/experimental/coro_traits.hpp>

#if defined(BOOST_ASIO_HAS_STD_COROUTINE)
# include <coroutine>
#else // defined(BOOST_ASIO_HAS_STD_COROUTINE)
# include <experimental/coroutine>
#endif // defined(BOOST_ASIO_HAS_STD_COROUTINE)

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_COROUTINE)

using std::coroutine_handle;
using std::coroutine_traits;
using std::suspend_never;
using std::suspend_always;
using std::noop_coroutine;

#else // defined(BOOST_ASIO_HAS_STD_COROUTINE)

using std::experimental::coroutine_handle;
using std::experimental::coroutine_traits;
using std::experimental::suspend_never;
using std::experimental::suspend_always;
using std::experimental::noop_coroutine;

#endif // defined(BOOST_ASIO_HAS_STD_COROUTINE)

struct partial_promise
{
  auto initial_suspend() noexcept
  {
    return boost::asio::detail::suspend_always{};
  }

  auto final_suspend() noexcept
  {
    struct awaitable_t
    {
      partial_promise *p;

      constexpr bool await_ready() noexcept { return true; }

      auto await_suspend(boost::asio::detail::coroutine_handle<>) noexcept
      {
        p->get_return_object().destroy();
      }

      constexpr void await_resume() noexcept {}
    };

    return awaitable_t{this};
  }

  void return_void() {}

  coroutine_handle<partial_promise> get_return_object()
  {
    return coroutine_handle<partial_promise>::from_promise(*this);
  }

  void unhandled_exception()
  {
    assert(false);
  }
};

} // namespace detail
} // namespace experimental
} // namespace asio
} // namespace boost

#if defined(BOOST_ASIO_HAS_STD_COROUTINE)

namespace std {

template <typename ... Args>
struct coroutine_traits<
    coroutine_handle<boost::asio::experimental::detail::partial_promise>,
    Args...>
{
  using promise_type = boost::asio::experimental::detail::partial_promise;
};

} // namespace std

#else // defined(BOOST_ASIO_HAS_STD_COROUTINE)

namespace std { namespace experimental {

template <typename... Args>
struct coroutine_traits<
    coroutine_handle<boost::asio::experimental::detail::partial_promise>,
    Args...>
{
  using promise_type = boost::asio::experimental::detail::partial_promise;
};

}} // namespace std::experimental

#endif // defined(BOOST_ASIO_HAS_STD_COROUTINE)

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

template <typename CompletionToken>
auto post_coroutine(CompletionToken token) noexcept
  -> coroutine_handle<partial_promise>
{
  post(std::move(token));
  co_return;
}

template <execution::executor Executor, typename CompletionToken>
auto post_coroutine(Executor exec, CompletionToken token) noexcept
  -> coroutine_handle<partial_promise>
{
  post(exec, std::move(token));
  co_return;
}

template <detail::execution_context Context, typename CompletionToken>
auto post_coroutine(Context &ctx, CompletionToken token) noexcept
  -> coroutine_handle<partial_promise>
{
  post(ctx, std::move(token));
  co_return;
}

template <typename CompletionToken>
auto dispatch_coroutine(CompletionToken token) noexcept
  -> coroutine_handle<partial_promise>
{
  dispatch(std::move(token));
  co_return;
}

template <execution::executor Executor, typename CompletionToken>
auto dispatch_coroutine(Executor exec, CompletionToken token) noexcept
  -> coroutine_handle<partial_promise>
{
  dispatch(exec, std::move(token));
  co_return;
}

template <detail::execution_context Context, typename CompletionToken>
auto dispatch_coroutine(Context &ctx, CompletionToken token) noexcept
  -> coroutine_handle<partial_promise>
{
  dispatch(ctx, std::move(token));
  co_return;
}

} // namespace detail
} // namespace experimental
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_EXPERIMENTAL_DETAIL_PARTIAL_PROMISE_HPP

/* partial_promise.hpp
0az/j/NDmcA31dznba+AZfNhZkq04qkog5fiwwFGL+c8VqXJJN1g/67Z+nIyCC6nxZVxPuJK6ahSoEmcHeSsxOjkMsRqZDZ1/pbqYB0cRvWF5xDwr723Ju5gW+0VLGMXDl3lWaYRb3FqcHDDbCDDDZu/Z++CTpN0raCMWx6HseN8r29ssWZcbjW4JBMr2vY5Np3XLeOTei8NgFw1axDcNkzSEON8xsI73ONACHwPHbEpEPGAgY2jGLXL+MlXALK1yH5lbY8Xn+uQ+ZF72q0xUI2tdqkU10NwKIoOANDatnlr27Zt27Zt27Ztt6+2bdvW71+crLLJZCZoLHjHP+YFTmmtC5NIvmRn/L2V8jEpSZ4h7jK4yt+LR6GUmGiIrGG7OavG7JizikIl0cQkXTtfHQF7QlyHMW30PzQC85MzNNKSomCxn4gY3ngnlmijtRz0KRC6T6M5XVfAoO+MZkGIMJxQt4YQVw78L0RFyK3Kb3zV09HOP4oS75Xo6IA43CF0WTzF88oIv+hV5mk/r8geGDHzIBL2wlSAHMDfEvnc3sSKMDC9D84jq/DU4PZF20T8lKYN8RAvTijvUt2o/LcmlM+hvgYdghDmWATzsD97HaDWgIhb4DkFG98mMA4mP0urt2Tf1zNqyfyU2g+GNooG6JtATqVbqnaUN9WGhCcPqqYVDC8JFg3RCzu1IUZ49ZHdRHvnlvA87cu2GXoEiPhrOnj0GbJ8KRWoDSN1c207lNZZjtZncDdZE1+prCnQ3pWX/XQmMA0AAQR0jvzRdOiT1duVbhM8vr+ImCXtBDReb8IvV+rlaFRDsn49Wkz/nf9xbTWlAm0Z6HY28mDcrc9uK6n4fFOCQQVlkpqOo+6uQT6BioIPeQJKfC1hVRhcTeNnrqUa0Qvu4OqfM27+cuojt5zmub5SrkK3dbaXhMvHmNR8XXxFXBOOlg7zrcd67K9p+JAGYQJ9iqdr8cOAamkriyqVkkInBP2oZ++7jl3w5qPHIuRgOu3yLKMWHVuZyP3KbUiuOKGOx6xODPIdvShSnOeiotzBCzOd7P2u/L2zoWuNpkOxiPSCNFln7mburHOZ10nEQJSsh9TKy6CHLUsNgPhWN8r+gHHF9MqEp0XjoXqRJYHwCDILQ7v/57EmH2tGI/jNnGz6V0dgAoKIkaItg3PnV7ECkJ8utn7SyX9KHwrcbrhlRcL39aYqLVu1rYPvertVLZ0sRSGrXgYmnKf7KbmyYkNpcQByEoW5k6iD0iVrKCQeMLI9SLOTDzBoTh3DU0Q3SKYzIL72kEKZhYS/dUKBDs+5YcnEzzvwKso2OMqCCKKoXpuAY7lBCQKqJu8CZtFuOyYBeW1Dxcs32KtX9FyQON4KRdDFc3fme5Bb12XOZNt8vrsgjdd2AArbqiT5el5YG4rcnYpale7RuhKNV5n7F5zqzuDiBGBejGmqkernlrynCx+Kvr/iOetwKSd0pjQ7WrMal2ye0wt538b3Z0z8jhq16C0PqDifWISr3wiSibeTnKDQ+MCNQ7pB+vuuVuWfrZeWCpEP/p4it3ougnInb81CLld+rsMB/7GkPRjzlykDD4Hi/YbBlp9AnWtG5o5zhxVgeJ7zvs5/qGjnienVP7dn+VSxu3aaloKyCs8wGhT0VkQhvPUdfudGjojZ43VcZJ8NFIzRixAH1rxd5Jm62/r46pCmaF9BKU/dLJB4p4jU37WrOG0Mh6/MJVvmc7yJS5mkNv/aK76fhcIVLkKvpCBmgEGd25D9iN7xIGP22W7nMMSgGjxgSbnttQNRIhkBF4w+TY8xR5X8512BPzw74YrhHxh1bajoL0Ld1pT+3RRVl47c030RR4gYRhgQJ1UuaMoM8mBFlxNJHXfQXpl4eUKT6jMk2JYBX78xKk7xmO59lTC5AYHAPu1q6kqnMzmuzwhmFm+XFi6XAwzwAlwhXsyGE9Uem5SS0MWhdETaeRwoVN3FuwGJNFNvGi5kp/DvoFRghLif+CO9+HUDpZjxh7q1kDvDeNIruKAZ9AmcXpau69/u96SZd27TDhc5G14kbTws+VBCVQTuPwrXFxOWWtrix5AtncHwKkEg9xkl6dBeybZKKpv2dx/BVwZF8GlO7oZ7NItWUIH7+OKXcCQ+cYt/WqmA9ZfkLMgy6DuSRpTODijo+aoAEBVoFpmYZxWFGNIQQHlc/sBGZ4MYlF/PTnn7LF1fTG1z/WL11lcb3MB1MpCDmWtXJhnQdHbChwTtky/lkaxyKFCV4/+11U6Hl8EsW6KI4dGxUfArGKt0mJfa5ynepb7XFr8mu4grL82heKnG6e3I5d56QI7hsqiabtksognF+QlqpBeMItbaej70lzV2gnbdgPpDB5wW7j09+maO1IpdxJfF1HxachTj9+JhOXNkiLVBtlAdpVK1kRfraWOWdzOb+SGqreKaoTadN5JD/6uB8gvyk6v4B7+EugVfrX7ZZWgYyXwY85+Xsc6KuZInOht7j7JjIV4MipoWZEmUlXxqPOtZQ9j4I7M+Q72Cdwq3BbbevWhXpse/uQDhvnxHi9195JsdzZ0I1gtFplKotH9M14fLyWOAsGBx8NlSKneNhYa93NMNl4sM8sX8kXaxMn73x4+vTmq5v7yKeGhJMcg57mZ5S2jwuLHSWjMqFAYNEeHZVEGQidiivjF5g1o6Vwksq9tv/TjHU6UOmTqeob+PF2c+K7uzjduK+iPQDLN1mft2Cmdl8x6xPMp11AYjpSYAF/oZUY/BFZEOdAZ2lzBOV18YilFJNVHABTORtyGOuck4v5+Ic7kDJVqpNlEk8GQ0YEz01J7spPUeBGRzqsru7Pi370lgQjKnpMuFpTtLgIaYeO27fM7QBZrb3x77CHo0FoBdKA+IRhvZVSDP67MtZXd2BXKGbAPWgh8muhRl2iDwwZegpwsOojajXjpk3vMwoI78InycfNpZ6zXVX6NQMFgAk1rCN9Z9lnE+llK8IY7L7EMyQZZYZHkhFRipKv/tRY4Zr0keojm1fDYsfHCN+oRRxeKpdrU0B0XUPnqIfNqxwDX2GnaJ6s6EASrQux1JqGbWAOXXG2ZcHFi3GMp7d9cqa86vqdub56mRPzzh4hQcjcsaZjA9MCc7a6VlbUsCAuVW9SQNQ/tH64qPvxui++A9f/asIgJZkKQ+fZe0oNuFYkctMayK2XLZ6Of0KptJHVvK3Jtbr2jCH5/OznmTV+X4G7DZTmIH/X4e7YFKf0/v/mTNbOZ5GNjXi5duUmYRBeR9uj8LyY2VOBpxhxDPsbuIa0Ppv1mmp7zDJtJR4mpO+dRpw/j19OFX7V94hsGuV48S6A/k5ruHnZjstbjbBHPf6NbzQyC6xVrFpqJPUX0yqFMDP951UDs52mniMFFzJuM83WXLUhbYgr9bdNpmhtzoAtPkZFn2tT7jveQCbRlJtkRnyTE/eq0Ec3E699jfGIbGFk3wyMXOUoAKHO6Jf2rGidJwXe+Vou62TSGHahxfsjstPyO6117gSItfI0xasxipz9UbTzWsZJ46mTO1Z09jxKjGrwnEEYVEQ0RVcJ8K5gVcSV136ZrprqleQpZuaUaeXTvnyqMNDz/Z123S/SiDLXeTfBFFWO1tCbz5WFjT5oz4E+2PmnAjKZEaghDZJ5bqWsOIg+BxdHm4hBgqo50S8r3GONlvAqFlPrFXpDEcG/PY6MNy/evFcoYbLeL5zj+09wk+fZqNOdoubOqpSgMEJ3ZWNwKFzzMO3kwj/SaTcmbpTH5kpWlo3OZAlSzqDP40B24kONy68dcHxvqFrEkGq1+xSRkRFqsx1xQBCrur0SsbehJHQm6ToxQL7Oiukk6T/Ie3z8ttLariAOnGhwfHM4GPizhVHedQHfwsadRkK9yUDW7z39cqo4gjA0UkPRFZNwY7QregaSvh584B8j9EQTCoQI69oZmbobwMjveb7bTOyWpw9sdO7iytO0+zhBdakhsbnjiOtuIPPngLdr9wtcDpsRqaCjEz1SM8a7dVuhECaKq5n9oOkAFN5hp+7dwhqmN/DKz0B9vUUOQ3D3tSyc97EFV0765iDaexVqBv48Msm2QUHxR7cIgH4DlN6H+Ki5gI7dyfourncslKy6jvwkhDdwwkuwsCfUVRZ56/FdzJqRDUrUPo0fKdunHoowzLmiCAnTxZfKhUvRnwXBOUV47UHt3YdOJ9yVRZ4x9EhNB4xzWYy2WUHpiOHngow/eK1O6WYhdT1P6kHQ/XOFlIx1MSsA2fLn7oPJvUbG/Xy2NWj72JTFd7uB2wCf+FF/2X9GEPhsZweAnk7EOwdvAaQgMKIQibHbbvc/uU/7BUkwqlv7L6oy9Vq5zDA+4GwePZYXFpDYSIDBkPMdb5KupqHqbfvAhSMYR6ze1163vDXo58vE/zgziJezFHUbWGIx4qseYV2vpULssE3igtfjacBgACBAq0fe8k6A+w7x0BKFXtMQIB6XbzJQTfMmtDx5ngdGhJAPWMmeVVLPZeOrEtYy5cqCZfvtKoSH/ojOOaSCwRmX1UV8YYYElNO7V00rCRldbWLtNp3BYiLP1DVK5NKR+87+wb1EFpIRoGOBO2wG9gF7HKRDj1xZlMqBHf5QtlP77S5C1SywHjEMJyhjiq3pdThxxrH6lVGOobaBHTFmUR9Qn7vl7MvskJ35SGlu9nGkqstdlM7SalJSFjnPPx37oP8mM8f1ru3SGSHhw8bSdYGFYGJT477D37CIKHSwCDKRoOlzF376l3fzBI8AXj7tL2c1Ew8tR/+/w2vONjnKzHzYZnfrbVg04f5iknOPbmLczlESObdYMuvXcfBglqd4P77D/3HqpIL8v97NZIUnQzEZ1G1ZNLBK4YwYcE07W46mnmQAJitxcFt2zYVv+aQ0XgMOYiHUMa+YAE0YAj1y+g5TM7wIZB0Y+mndM51GqeFUWa2Ik6XeyhASQA8g8dsbVLNRI9NGg0Xl71dw2VrXVwqOnKD5WdE0GbI4JpUQtyCfCyDRrSG1wh8ZKdhNBhZKmGlhgDsR7hZGeDPp3nb5PWMk89Mz2OwGYP5Q0dPQdLWlXyYIF+KHbR4EySIfG6WvcQpJ7WS2vUQrQ7PcE/E5zSBqT3cCe8ZpGyRjmY4lgzhlMWE5hy0ZILqixGSkbEWbNxaEabefCZ3dpH48GWI2xeWW9i/N8VBn02XGJ3Xs+7LL734oXlEdx6sg6023wR3uEcljK3XzFf67X8GTn9GAK9BnUEI6vWU8SiJrvJR+oNx/mFVr5SVApPwN3CJAVao6nFG5DQd8oIl3risAulHH586UZHAUThD2A9e+Rav4cAdXAEsgmpX/bPcBFufZmF4E8/P6rzsHLNV3Uq7O7NacnE8/L3rdrJ4XnajUFOwv3lFGGwQb1ff7ienemBfjOFjjMRNtbFj8g7VHVsPMlGlcfZUT3n9ulkeAMzzDD1CEqzGEyF2OLa4Mf8aAPiPOjYKPeXhMHhns3RyzzCooPpp8/+uRNcHJq4cOOfOFZ8APZxfXO73rXqDQ3YPjwLHrmYx60Ot8zmah6MymYHaRFreU+oJqtkanVnzIa2pjFISh3t+tOyTr7KioCE1COMeiAomMH+88c2OUOfRJn0nKC1lvCPVEOn72zN7R8bk/qmy6jzBADTTU/EN8w0Nt4F9U3JhLsOY4u034sUu7jN9A1SMvQaCTrIiWiI9DFPmSlcILmoMWbCjMMZ1U2+6YOyAdSI2efLlhSe8oOBCTv3mCWhH0Xl/oH27jE9/paoTBE+Mb0AJbgpVw8s7LmFYOAgD6GXymZ3cZdVHb+abXzI+w5GjCWo/SJH/C5d06oUW8pNF/VWNQ2l5r1FT4j96QpjEKFbX11orR01EBOLm6sfcjYecq7oKWzggzBo1G/fM0gV18hyzVkmm8cQM/+bL3BOlnIYXa/89CtjhpBT+NQQDHtfdEL35UUmYOruuU8CPE72aU98e/d0FbUM/8E+Km+d5g3LzZ5RpPAjeX/ZL5YyXD26D+Hh2NLLeJ6rOVo7+8nH8PwEYIC1xuTBBK2JiiWACN93Y1+pNn9CaVSjf7CRRs/mdtxKlrCZ3RN1Zk8TccHzPWH0AKZ2uIanROTais1x/4xMurZEn1aYxWyeKQpI4pilw7LN0IfM4vswFjjXbTkBaDvRA4ZIAcqozjOT8lOj43gK+6l6gPijrjuUZ+xcsMWlYufdvREOjiL3qDuWr9V3c+dhgJh9ZlSid6Plb+R9+CucU7ue744UACUkVrnJXbzHKfPf22dHEwkAp6/uDeg6t+9dgMlV0jjGhR3s8aNhOXe/jTw2wgHQ3PhhkYbi5smL9rHErM4iuN9+XPA2yJIVsIk9VLBZZY0GWrCtOXscVSPXUMB7sMQR19Ds+WvswFNMwtZgf8DGaIy9kfrURUPqXykxU0gpaGTq0ptMjYvi9/VkI0j6CKMw9B++wPddb84OYqb1CtngbCqzBOTD+LOj7slk1OCUjs7wrlTCJwVbNuY2WInM9Lu08CvdSbaqpeqA8+IIPVu9e4n1Fi4mNYSYL87+F9+XbgTpw1eoayA0zPY6ETV6siPKsgdNaZ0JXcudk7J12SiTt5/gdPDMZL8d4y52BaqQ18R7fx+vaZtlCgAR+FyWk886nwNxq2BPT/ffyaVzDDJd2m0UAbrf906QRlHr4NvcJro4gRLRChvscv3bz9XydEThdp/U4NjdaSAf5VIKl1hPA0kG5M44xs8hlX3zXgyfKakrSf1qKa3XpXx5l+LOrVJKDy95XSnzFBnFLCJx1dpImW5mkafuKckhP0J7OEoVYWpKnMS7WzLrRVNDh6RdowK+R0a/OgYJfwhsE3nUBbUuGr3rEkUUP1RePZ+w4j0++XjaIwGo+tU+sLSuf/BKrRFnKySO+TT9cXaZF1TA6z0X4Qz8pyP3ya8n4pVf5tFIRuzvwWtv5GjRIRMYUXVOnBbHL/2bCyxiJbUTIIznIIec4pyIyo+vPyYMEgnSmcdj+usqWeo5IHRTWYCRjaj8VPTqigbZPVX6TLcLxdZtZecULSDt0EAYwyVmon70jgVM7uPUOhiwGcn54Xc/hw+RmFJJiG68opjDAE3xe6KLe6E8u7bjQgQ2iIkZgyx3b/8sKs8QIo7nsqwmrJhNMLLxHXa3hnCejgUKnDSK98kAYuYYXkvvRcSAq5xVc70y6Fy8s3GYmPkTwLfutnV+SeW1b7ouJzOR5gEm+IHGbHXGVvlUMeMiAQz68giZYOlOJ3VOm++IuBfkNs/XdMlBMewNl/RHy0fPoU+WEPB1RhLZ4fBY2WgAHgBA4J+gP8F/Qv6E/gn7E/4n4k/kn6g/0X9i/sT+ifsT/yfhT+KfpD/Jf1L+pP5J+5P+J+NP5p+sP9l/cv7k/sn7k/+n4E/hn6I/xX9K/pT+KftT/qfiT+Wfqj/Vf2r+1P6p+1P/p+FP45+mP81/Wv60/mn70/6n40/nn64/3X96/vT+6fvT/2fgz+CfoT///Rn+M/Jn9M/Yn/E/E38m/0z9mf4z82f2z9yf+T8Lfxb/LP1Z/rPyZ/XP2p/1Pxt/Nv9s/dn+s/Nn98/en/0/B38O/xz9Of5z8uf0z9mf8z8Xfy7/XP25/nPz5/bP3Z/7Pw9/Hv88/Xn+8/Ln
*/