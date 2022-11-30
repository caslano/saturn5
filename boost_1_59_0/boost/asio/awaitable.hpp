//
// awaitable.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_AWAITABLE_HPP
#define BOOST_ASIO_AWAITABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CO_AWAIT) || defined(GENERATING_DOCUMENTATION)

#if defined(BOOST_ASIO_HAS_STD_COROUTINE)
# include <coroutine>
#else // defined(BOOST_ASIO_HAS_STD_COROUTINE)
# include <experimental/coroutine>
#endif // defined(BOOST_ASIO_HAS_STD_COROUTINE)

#include <utility>
#include <boost/asio/any_io_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_COROUTINE)
using std::coroutine_handle;
using std::suspend_always;
#else // defined(BOOST_ASIO_HAS_STD_COROUTINE)
using std::experimental::coroutine_handle;
using std::experimental::suspend_always;
#endif // defined(BOOST_ASIO_HAS_STD_COROUTINE)

template <typename> class awaitable_thread;
template <typename, typename> class awaitable_frame;

} // namespace detail

/// The return type of a coroutine or asynchronous operation.
template <typename T, typename Executor = any_io_executor>
class BOOST_ASIO_NODISCARD awaitable
{
public:
  /// The type of the awaited value.
  typedef T value_type;

  /// The executor type that will be used for the coroutine.
  typedef Executor executor_type;

  /// Default constructor.
  constexpr awaitable() noexcept
    : frame_(nullptr)
  {
  }

  /// Move constructor.
  awaitable(awaitable&& other) noexcept
    : frame_(std::exchange(other.frame_, nullptr))
  {
  }

  /// Destructor
  ~awaitable()
  {
    if (frame_)
      frame_->destroy();
  }

  /// Move assignment.
  awaitable& operator=(awaitable&& other) noexcept
  {
    if (this != &other)
      frame_ = std::exchange(other.frame_, nullptr);
    return *this;
  }

  /// Checks if the awaitable refers to a future result.
  bool valid() const noexcept
  {
    return !!frame_;
  }

#if !defined(GENERATING_DOCUMENTATION)

  // Support for co_await keyword.
  bool await_ready() const noexcept
  {
    return false;
  }

  // Support for co_await keyword.
  template <class U>
  void await_suspend(
      detail::coroutine_handle<detail::awaitable_frame<U, Executor>> h)
  {
    frame_->push_frame(&h.promise());
  }

  // Support for co_await keyword.
  T await_resume()
  {
    return awaitable(static_cast<awaitable&&>(*this)).frame_->get();
  }

#endif // !defined(GENERATING_DOCUMENTATION)

private:
  template <typename> friend class detail::awaitable_thread;
  template <typename, typename> friend class detail::awaitable_frame;

  // Not copy constructible or copy assignable.
  awaitable(const awaitable&) = delete;
  awaitable& operator=(const awaitable&) = delete;

  // Construct the awaitable from a coroutine's frame object.
  explicit awaitable(detail::awaitable_frame<T, Executor>* a)
    : frame_(a)
  {
  }

  detail::awaitable_frame<T, Executor>* frame_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/awaitable.hpp>

#endif // defined(BOOST_ASIO_HAS_CO_AWAIT) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_AWAITABLE_HPP

/* awaitable.hpp
G83y8Ds7w/HObDGHewiO90HswQq9v74JeCWKnQf3PilgHw0VZSpU+aNOl/aORPJeIlQdNPnPUxwJxY2BfUTEJpXSY1hUuinP4zw03PyEVf06xwPsW+fyxcJno4Ak5+ZGRtmp1TnQGr0W2Hremj+A/5qCUeJUpF7qRBGwKsGZxXftPcqDBC9OvyqEcOl2q4DOsX4KqLNUhVSEXtfE7xE6WGPtbLwNVAnciqJJCZyKe4eGZOreBYXis1NVkd1NwsTNRo55hrsf+cOToc1roO81gCvcSWqovi77+zHRoxgx9gFcYv64Wp57hAO0a72iesmEaw2SfF6QiabzhcM2RMCgsfbMFe8w/1pFNKMf2YyuA0i4kZTH5tox4Ug3VWUWeIOeHaxKnr7pDQqjtbyd9hvovkfCTyz5ElUYjmtVg2/BoZxc/EgkXg88JDNRiWPYvaSp3XK4kLkMHI7fR5/oOpnVN5rYLZEos5dWlw+gwKmaeAercYyV/f5+vvNQzH4rkF/KB1AH9EAjxHjoTMlhbopcnWAU8wwA1PdYrIGwG70Jo28CptoQurtGrTvZK7ZlsmD2UhgqW6P+JaRSxlB+2rDS4rdD1Uulbw2kMo8jmwXjyyHsTqpotyCBI1MIaa0dfv36apJQz6B9IPpnCYKNm98/N+Y0XfVUnQDsXrg24A+0ok6WyYM8p6sY4nj7IUok70qmkj7IXBBDrsGf3+9PkAIoJCQng2O16LvqdbbPSCE01jNvMumXg554eaZtN9W5PJzXttcMsIgrEUzbhBXaZAEzOfq9IHY6tL9IA4bwU29zFo7lwHjPrRLFAyU0M0VPXy1YuovssmnEchuRTA8gcYfn3JFO2pp2kUw/m2CWxzQiuI8KMh1Tfw1D2v9x/2Ic5avtM9jiciyVeA2pHJHAssgpKaMyQo+ELEWwAJ3a6nAbgef/sL8GoQyLQ/A6Kb3cThApSZt2OZfBhEoHK3vJeCyez5JSBC4/XHaNwrOpqWRlrumSNU/EbKco4UVHjUJ3Pv5FnMqhSReN7VzhmzbGVJZyo7/FVH7GQcCIgkUfbYc81+BESB0VtSfsenruKTu6LzZ2wlbTuke/lxJSLLa+rZ/ZLMeVGSKizyXhh58/YjhnuIUE1uIeHlgGQnJI/hsjmyB8oJL/UnpN3zArryBLKaXsyJllUqfDlVJA+IlVZhglErZvkEGvqKusLPy9n5K0OKzB4SNkAYyG0yE+L1WJBq0RHBwj0d2cItlwCExgwus4S3dP/TeNijFV7QotDFEiThVqFJOGqRojrT8/RkajyhzepNaAI1tw7IsBboBmuDgOx2ar/ag5MH88b0h4wFBJoQ/DklzYrE2Tpjf7gjpWo+Krhchg18emsy4JthxOCl841xWfBQJZYxfHIc32VJzn2D5OM9CocDzvn9L6smLqAaoV80QU0TiQfRY9n9ejLzg0p1EMwRPBXwT9if3wRHtr6mtuKj+Jos4afl8SPcc44/Z3XE41yDadUL5gBXToFxV5FPEpsGoSs898+gwvV203ptcXNpPAHpRh86S6GNXwCvof85LlWuvTe0iljJSaeStG3i2YDbtkwiw4VC32kVDUx6zuC4vPvaourqookcOX27gYiSEbXgmpAVATmJYHUjpggzpdoskbA0zveUOH+TgCi1aLwRh8KVkaWz5ZLLTwEUkIBDoSSTlu4nrcLVf59O0ONzvwSIimTWZP33eAIEGSgMEo76fpbG7u87MzJoB+jvwFmk08Bde/SAvhhfveqEnBZALl09yBEmDCCqWe9lYSG+NqUxczPktmIBPSW7mOB7sn0Xsl1RblBM+pfDv26CA407fx4pjLW46Hkg3ssOcWLrlUQpLKZayj6JIoyX+aQHZJkVE5hsQKOGIIaOdrJS5lPJAA/v0swA1AS/RiZJDfrBRcwjT/9RHwwF9UGq1cb+tuhs65ONxMcLhxLZzuphL6aQ/PIba17t/cemv5k/zSCyq//7WRoYgRzZD4XRutVrMznsuiwvy9BUZfX/64jTepps+0x10+JlrKtcDD7igkPhaaTHqpwtPGg25U/0M5rtwFtdXtVl/hB1MtTbnTmJ9Lb3POSQq3HTtvK+AmGz2WvBafAGX/RiQq2omCMQQdN5tLaufanwvaA6oLAx6YwzPuz9YMVJkmK5rLpdOnAeupxgDbTwodH216f3cNA/RcCn8zLtFlb5ZrijzzbvEFKaTwz5c8cgeBBdoKLdGxgb9j5vb3Y5wmxIBulvPCSp6dz6yMaDMqh5ysJqn1lRkA/npYnmXYuU8wfgyM2P5kSDWiAUsv+8fxHMQzoSGkJOL7i/nEEBApuQ4pFvt1iTF0lULy9oOXng7JZRmeuwC30z8xu3pHX1TXjWFZZEA/Ot5t9JfBVqm6z1l1U01GtN47Uu9Fl9f0cxdzUvT1O+gAK8EiPreHOcvVxAADrF3n4HEu2cSI8VrZbXuJdZkTV19TDoVpnIVCrK7B/W9rY/5o2FH7wl/dmb9Zk4AECojl+22GVMI+3XUNx30Ax7X8zHmKJlbnwRJw+Pfl9GauFox/fUT+8gQkwkVaipzZt9ckxXJoZ/is5jj2ju1OZTpIfS3/oOKg2HD/pgyPdavu3o+gPiSlZFcAE8DYRfL/DfrAI9vwz85//WUQoSSooqw6AWALlRENDFPt77bargAM/pS49N2G5XTqk4w0xJZ8cHf4dzTPuk1Va/pw37470+LTjg08LIUoA5v2w3a/LxTakvKRaEfdOoMJBbH4JHb2WZVFRdkmw/v1fYCqcWlXw+9S9861vLNTo1HGO2A8cwZomS9R2OgQuAXQvym8xIkef7WWeEuFLYSAFrz0pwv2Ryalk35sNtIkqQDBgSSUFMWZtuHi2755hQGTLgODaQ4XHgAL8eDqr9qbilIjMVJ38l4FBnWoGdG7F96oTexmHOL753OrNdpttasUq5knRm1Ry6yAE2D1ioL4FxG8xWay2Zyl8Xq50kJSAa31lrNGZySj61hmXLVtKBcAbc5Juu7em1QsZ9S/ipkndcrA5Wt7Dd7mv/3i7nIUq9MAACz/0waNwWTOTum6vA2V4cRQg9WJ4Xrf8KRo+Rk+AMryDuQyimEAngrO0TDprxcc7fWk/ZhVH24MieTXgfp6hzJz+bT2XfJUCfnVt1J5OTkA0mrkK/VPiGr8u3BlHwSa7q1hUa47xW5KeELxX3EThIsgHKDafzIVTkW1JaYJBCNJRYXOYCNX02WRIvsKPArBuYmEsxkHkqb5U5TfKe5iNY/U/Ot9Pt9cz3sa5YjcHwAhiJkZVwgJhl1GTS8Q5UYMm8G/RGCUAJ1AF0l1Hc4sih3GURJX23WWCSuFR+6OAeM8bBs7Lza79ovsbSpW3heokeQFZ0IxJqbmasHxCaJ7HgLKBk4UoKZqVhypAFSfE5wq93P3mucCLDyVJkSDGTB59A/k40deATIsGnOWoNHS75f3sjJt7EOijYsevf/+OZDua6ZF4ICghJq8i1wMpLcPS+bH47NOY+XpJi4YLPIHGA3gkfXDt5u/EGBX/kxp0Wj/zdn/Meo7Ts/KTTXubGRkBLRQMXXtPsKd8iQTzAZ9D4OgJcuOdn7JxcJIbPkWaulN0fiWMHETA0GnKGCiHl8drSU9M62jqBbPr8onJtN9s/wEIrDR7FOY/pAy8dt/DkyeuZLvYcFxXtavFnj12W07K6ykujRUGwZ8wQpmJu7uNvSrIH2dakeOGtDXyoTYKVKLhadIkNcwg8tMyV9w4TLN2cuTJFNTNyW7BKCjD3lciJ4ap+Mmhv8Q12d0p7QVYq8BfpqqFewgiVlX27j8a0+xJ7upS0fpSFUwID0+Cs/+eW0bVEIhH8AAAlJLYFPivd3lnCuJQWaKBopiyc6nom/ZTw1QnIN64QtErnY14tjAEWR/bItjm52SoopB5T4mod+Kc8k5HdHETBu1fVkMP0Fh4N0RpS9GwNICQ/2E0Pac3vbcrpCxEx6DBXeBS3OCRAJRbKstTVpIJF+pT+ldnDm5x7J+E8VwTZ6AP6gnZ29tKBHQ3tPVNQLveu8pcO209lM8kjisBc9ITNthmbO41ECaQk5Ho+jCUqzH9VITdNRmkk5aBEhYEMAwy7Sr02wmB8S1EUlSe6AQqwXj2kx5T1AXHIp+UtCES1czGL6jpY0pMTE7ikxgXW/DetioIinCp5oyBsdHOS3h5cX8OKKkk17MH1q3o5ZxEwxQ0KEhuJR3AJ9wl7wwEKyirGm+UTADryjLd6u9fNaC17x8R5xxi6kuQdHnxm+FYsxSSH1tQs4gaIJ4PT1G82A+iKynay4wuxqcp3rkbPu+W96+1BuJJEljyXsHklykfe97k3vndTo0XS8NClQcYg6VIEu3wVQGGxAJJDxSfkX3O/Y6eegPTGAlzPaWudfLmG4+cnHesoY0E8hz7Sj7DDebDRsyQ1Q50vBAfvEbuEwV/EHdLQetxVBTAWh4K3tXv3SiwypAwebdbCAssSagwQETH6vvJks3/0Aey6TT5Qr9BF6RTm0USEcKc2PBIWjyzSjTuKeH90NAsBme0+84dx3DvyeC9ii4bp1lvQ3wak/aHQEBxePXFTXd66LpIXBbXfVFEHqB5gTBISAOctfX6YRhd1k84VBIW79KEdpNOaF0Ou3j/YKsIIh6PttS7ceytDVL1oxZOVmlfpUib/GSBZfEsrpfB8EKkP6ykWHfsXZFzfsb+hWDmwKkFKXS5t22TnwC2bAqkdYLARi80q6rzda606uIMZJrYEsAuUDdc6rC0C12RPChogoxUykE8zHrfFmZ8xJesiLYF5hdtbPXvx0+lfn2rI07pjRO8VrCJIXMFFdAwxxVP1VZoHwC0T8quYikAdsfexOcMJXJ7nYCUVAMnZT3e1LlOlXS3mE4NevPs89JuG4IhRGR9DRrG8f1attClNcBv/GikH/CXvpQ/q64IXjFpcHmZsy603GEy1BsKlJIAJHR2+DyvHuUZeHz25q94pw9Y5XQqVdbp4+vDl9pNo1iSLnOAElYdhI4jGxFZxmqrHJeYdRUhoklYzL8ePa5qv3JSZ3DwTDcKBD3G/j2Y7VblRmaAhUSgXQeQV3hKO7kQ7Ka7t4sCXGkFsQ6Jn9pxa1xw81JIa04A1ZewOVMDQtv6+85owjUPOmyBAaPFtzNuIHwDdcMSHfP6jz5xKMLuTrpqBoAC1/A68HdhumvK1TIPAyoqKiC2b5hQ0aV8I23hViDgqUZT3Mu2JWHGqFEoKsq8lHquzEmf1eqvXgjdP4ZWgtE/3N0PIMEVloe7gUJ5qdAfEbGSccAR7GWcfKjZFfQ8Qn6nk1JdtFYLdJrGn4NwP3kOewcgITMfL3htmQOtAvH/EAiReg8UKgMZL5Xzqz6wU385IK/GQVH/mK8fPn9/TUIiTB7HcedqizZdExNHLJygmr2rU+lXAkK5RAIMfq0sfxEStSgENBxLo03GHNa8g4HoX+Cu9UrtT6zxX1w3rpkk1mAX6w1SCeR+G8GLIhzc/0ZAoTNCHnaB5rEYEbWz284CCnsqrUEBTWKcEt+tdt7tmDvqn81t3TROj5LalFSC1BoZwBCOC66A6SX6LnvBaM9ukEjhxi+qdDrGkrG8Pc5/xLQ4KwWW1er7gscxLWnHHnLwJHsqPMaQvzj4+9m1UF9o/AK+qmhgSto3mzg1RLkYjQQ1jykr7E4JaxIcn7ccUoP2OVQpYT0wpI+Pa+vSdGiLdiC7UqxzrstXjWHGY/5JCbdPkZ/bt+PkZqdan3e3zcXeDfQNPIS692PIhyFd5hPnZmkFnA4hK5nnQ8z8EUg/lhRDySsxEwMBHIc5gPG3GUwECKre1eRPm+Mw7oVUPZ73kXvqVijNOsJJNptU2xsyZpJ2vMZQN7hwtuFlS0dksNIKHnmJB9kjAaXl2u5crjjDvtQWx7R8pqfMxWsnnJwWtWw0EOUgoIky0HZKkb64PV1RvzEh5e6ik/mJuDXTkdwhb9uWq1EJ8bMRhNSun/k7onAjAbLtbhSKGvZuNqssoYyJimHu9WYVU3XMijmNsgn9LiIb7meXxwEcz6YwBNhodbJ88f9zATFPlrUl0K75ZxE8du+lDR33Izknbei97vtwhsHniHUgrzyiHHsXhdOMHNn64huiVplXMCfnnELDQw9F+ZiNR58koWK0ksdpJT6VaD4+GUqNActftqgx3tAQF9frr2SpdEaJaXX4bNE8pexZjqDNHAEuklK+NU7sXKOZTylr52Vhhg8a69kmeSd4xyvatQnlt5bANmrMylFGvE/Z+gE0mOTaZAKEHEffumV2m312bkSefhNaAHFaDTmsl8XxzI4XuVbOLh5kEm/Y3nCbXbQ/ibkf56iisadtbk7xiBKJkP50JEtIOBoe9mjxD+CnykF5Q+QY1pztGvg0SYYS7c8Fmr1r/aqDlSgI7BVI8W1/hr8Hiu6APfC6alvNL6JgcnPfT4IDMJjE3+Bwpyj1QEKtFqBazSCXcZdIs9GojSjiqy2vlseXKpQa2GGYfowOqKVipN5lNRpVocgNiCIHVw5sF/JJXQ+RaVWfbFCBJVAQKnu8F62Zt7LgJcgNamDa+e9tV1wfgamksTzHcWAcGLv7QN9e2GeuVLiqtKnK5ataX9mTQeBI08BwMERSVPFillcY3BeMISdkW15THSHgkjbf0p4KHaZ73BOoisM3D4XSRQpGIUOBcfr4aF/e8+ObAKGdrcdllVewVWPNXyK7yXPLvH5mojflfdQiitt8351rOal6Onxet/Y2T7ugqc0GpXLXegkdPjDeGo3J5b3gf6gVauz7NoPSb64m+2S9Tph42ZxN8IHKrBpwMVuN/zRI873svp0xqX0ekelxPgtPpbToaYdVTdCUVrOtiTmJZZGecITLMWMP8SCI4iF3wpfIpE9EE5SAHu8USXyYRGKtOs+0HWMJlf31O6VXU0QJw0j1uUxmWnHUJw3Rk3FOuQQ9il+HMhVNnbm0BVaLbhK3AX9KqkbJyEAsaGjDmv8x4jH6W80QRKwpe2d9NegS7HzuHICtMr6batA33ohdonAOiCcbI0tlAzGXjqyAAstYH88EKZN0Bcw1ockQcPrptMM7gCQRaAZ8m5/ORXzfYhdZpOaroHk7ZZ+N37gWMya0wqw6XgjZXFt8/DENJTCZZaRcd320txeD3f10diQcbo6XoZNLK9xbJORECDtHjsetniSDc+OhRhk+xYHpu35zcBps+Rovqu7oV4Y2PWgF2MjdS7Ler51fXUStqzKy3LxiFiGufsTMp04wmgTmF6AJBCJd2BS7y7FfDhc9cko8dQg/O/Glq1fGCNsLn2C74lyfGvSvpPePqHggR1CCSKeRzAIqGRAQejwu+XD34Meb9BqVZomMbxPq+V1RiMpTOjDhWRGBSD5cDVHbNq3rguOE1PFSAvNGGg4jN6uHs96V2zI25+qDBAXINFEytX6ZzRXfKMQcdGmyrBNm5S60zcXUAOxm07Pkh+/85dDGpTVfUgpHKyF+fmAgS0qU1+sNMODEaFfk4l8cMx6WmklUIewIXmEfZKecfo8wsFXfuOJQ8BN8I9CbmDBIOY4uUVaKdnOP+iD7Gmi4l/2OjU2pn9nX6f/GpVKMvRZpBNwb8GWKxAy
*/