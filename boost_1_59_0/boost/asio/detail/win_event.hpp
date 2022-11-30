//
// detail/win_event.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_EVENT_HPP
#define BOOST_ASIO_DETAIL_WIN_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS)

#include <cstddef>
#include <boost/asio/detail/assert.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_event
  : private noncopyable
{
public:
  // Constructor.
  BOOST_ASIO_DECL win_event();

  // Destructor.
  BOOST_ASIO_DECL ~win_event();

  // Signal the event. (Retained for backward compatibility.)
  template <typename Lock>
  void signal(Lock& lock)
  {
    this->signal_all(lock);
  }

  // Signal all waiters.
  template <typename Lock>
  void signal_all(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    (void)lock;
    state_ |= 1;
    ::SetEvent(events_[0]);
  }

  // Unlock the mutex and signal one waiter.
  template <typename Lock>
  void unlock_and_signal_one(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    state_ |= 1;
    bool have_waiters = (state_ > 1);
    lock.unlock();
    if (have_waiters)
      ::SetEvent(events_[1]);
  }

  // Unlock the mutex and signal one waiter who may destroy us.
  template <typename Lock>
  void unlock_and_signal_one_for_destruction(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    state_ |= 1;
    bool have_waiters = (state_ > 1);
    if (have_waiters)
      ::SetEvent(events_[1]);
    lock.unlock();
  }

  // If there's a waiter, unlock the mutex and signal it.
  template <typename Lock>
  bool maybe_unlock_and_signal_one(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    state_ |= 1;
    if (state_ > 1)
    {
      lock.unlock();
      ::SetEvent(events_[1]);
      return true;
    }
    return false;
  }

  // Reset the event.
  template <typename Lock>
  void clear(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    (void)lock;
    ::ResetEvent(events_[0]);
    state_ &= ~std::size_t(1);
  }

  // Wait for the event to become signalled.
  template <typename Lock>
  void wait(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    while ((state_ & 1) == 0)
    {
      state_ += 2;
      lock.unlock();
#if defined(BOOST_ASIO_WINDOWS_APP)
      ::WaitForMultipleObjectsEx(2, events_, false, INFINITE, false);
#else // defined(BOOST_ASIO_WINDOWS_APP)
      ::WaitForMultipleObjects(2, events_, false, INFINITE);
#endif // defined(BOOST_ASIO_WINDOWS_APP)
      lock.lock();
      state_ -= 2;
    }
  }

  // Timed wait for the event to become signalled.
  template <typename Lock>
  bool wait_for_usec(Lock& lock, long usec)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    if ((state_ & 1) == 0)
    {
      state_ += 2;
      lock.unlock();
      DWORD msec = usec > 0 ? (usec < 1000 ? 1 : usec / 1000) : 0;
#if defined(BOOST_ASIO_WINDOWS_APP)
      ::WaitForMultipleObjectsEx(2, events_, false, msec, false);
#else // defined(BOOST_ASIO_WINDOWS_APP)
      ::WaitForMultipleObjects(2, events_, false, msec);
#endif // defined(BOOST_ASIO_WINDOWS_APP)
      lock.lock();
      state_ -= 2;
    }
    return (state_ & 1) != 0;
  }

private:
  HANDLE events_[2];
  std::size_t state_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_event.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS)

#endif // BOOST_ASIO_DETAIL_WIN_EVENT_HPP

/* win_event.hpp
hZMz+QOkEseJoeXSzcizqfmMqMb3F9AZrXJtJRv6wHBlkJujKvJyy7g/3xx/5puZLPqaltWeyIRkxgD0zw+MLymWzkTABNiVJDc8P4+FJE551gbU0UwtRInijHPQHPFV418m9Bmpu3M86paR/BhwmNUGjt0WGgbEytHiK/2oc9KzUikqj3t+UYYkq/1GNPzdoT+rozH1Rkp1pq00qRXliKDLZk4fv8go3XMp50s8Yvr424VF2wF5TFpI7YugoOSDwN69+KOLCEEhG6OIWmsYR5T3TQkixbD2txvE+yf3akKjX6G6ClEpnxG7p5aaBvw4sw9SZvzOETQX7rf27SMi7IeXIurN0ZgoDQ3uBKsfIttO2d0Nn7SsxKO7fFXMPudTJysi+KE8RH9VXSzIfX+z+Z+OFXR34DupJMd/RhdWuM8VfUh/PjmrELAIaTlfCHADA1G9PWBLZWEha1rRzHkULPYs7oYzah1DvukqsGc/JwbezJPP9FUmyrCAFs/Axu/H/hoyV32IZEPMMclMDzz2FJSfdZaFIVxKYUgRV7ILzwlgi/GAmT2dyknbs5rovDpJU5euqLrcA3ITLWkcz7JKpIvJKYCQutB/2kmBezJA8TYmqZ+1Uf1Esytn9bmjPR2kzoys+NFTNULwoax2Z1sogTmu0dfWoSFYsDO0eRPotQD9QYzF0bNX0KJdwyTXXuttGSKYU6iaUfccDiqsYGXk11e2uqDBmVqspAqR2SSamV5R6RAWNxFi7zvfpKK93Ndcl3wI0ui0lTnYYT4W7Hx/rQJ1if1bEqntKu4n2j2mHWRDgzZjbqsRzwBrsZtD78/EufckblkX6dNQNmbYXScY1TQuJRbBt1LtorkOteU/gG2EvpKNbcbhX3JIDicxTX4wYEay1GKw7BCVXGSZIoJxHU0migwS3zrXpbxtp6BesGghsI7/EgjcGu4izXhSUoPLEuL4NqoT+2TlEc7L05LRlqLgILptMp0sVh0n55EaMmk3XhyZXq5sROC+TxwQV5lExhFp3KtdnAGpyzWmM86Br/8huRwCRHKG7MwvTd11ydRQPBnSn43qa9G53C2B9aWhkcQLZvmt645glHWbaGOPiuw3AZzozzWzUBxMtHTjw/NACd25J9x4nT69hZon28Qx9ICqQKqQ5hAW5J2D54AQQIGga/BrbsY29t0Qgfj4SuxxKexGggY3rby2FMhyTnp0fm6+wXJJCXmeWqIHJ5em9366ncf06q8g0/CMsH79Wtjh037Gg/fzq1J+IUX9ssZC5JcJcC1zW+Ll7H6MPPDIs/5blTNzfyiLSvFOK2zcRzo61i8XJ4ViSPPJfLSMwxoI5NNpWSStkAhH5qiWDSs6DitWCokJjmsPVXPuLJMUECmzgDbm3WTMU0oKY/KUmNeyL1l17dD81TuJBU8Fxs4iLoMQYjBPRwVSHEHxIUxXYU2T44NGc2QbFVC5clj1xqHHH/UgV8oW5zVcsK5Zj1qtf5Dy5F6+HW4aG7VX0xwz5hQ1Jy5iNk+s2ucYZTrsVOYnvYhinjE3yo+alqQaJs/WH+hUe6oJmHpQljsv4L7PRniVLNUqWofPkvh8X5ob3psn8G2ZOdLu8ynKgNkaskAKDpUsQmPtOkm+vdjAmOqWsslI68xxus/Njl77pfUZnppNFbeHX7R7TOtPYmTBOSorBdL14/yq7IM0tqHFDnc487XVy1ajoOlLFkcFOUGeBcxGnOmWIJa9iUQkLPJNDdpdCcfD9F/Aswrz3EEb1dpY94Glz58OhnFJjj4ysQtyasErXse7KUO1crewHCHo5YoG57fsPYjuiDtXBkRzJK3lYhjQhOnb4oHtQrBkujPrFp9ER6kUYq4ez5BwnA16rSM5JbF/SEhZ3fcvsVZNlT5MgXrbyi2FTy95ImHh7B2+Ik7b4cI/tBvQctQPWxNfezCOhJimCCgtUaE62sBLv4coPr62nJ/a9VKuOXSc7HmqaM6dl3W/kxDOp3slc9SIcXLW60GZF21pXV/eGnZfUjVrAWJkVx5Zyuc378s1RReu4OQwImdsxYzouFAWYKrMXe7mo7EWq6sdkGc487qL36z46h/L+LQD25nsmPN17Kx3QiqfCbRctuw9kav5zslIZ9MjUMNbJtIVtavmio9l00McJPrHU6DhZqirk5GQ7jvTw/DmR8+a8P0SHNdXbwcjf4GOPoUVKN+IXFcfddTsThsEeSvzuiQdaltzIblfh+jWPTXP4jkLny7tQFtIX79wHjmw7kPIe7e44idoJ7/cKdHwXPGoH6n6ryf33kk26ppNq6Gc7Uchp+lF+x8efHQsu9LwJIvyB4Ppw/HuqiTnST9pVsbaRg0gm3/8VW8Lb4+zsndgQne3sjV86vhpS5JmcRhjdv7sg3R0ghoC7W0hKfZVM8GP5SKU6/H7oB7XEMSu3F+TLFgkkXDERWP7LelXVHMxYQXICp10ZyL+6bho14t4N9ov9nngdCuFQivbQOn0SHGFs7BzQ2dBFBjLnS84JJfdsyCOZthwyqoosp6RcKBexzIyHwjuwaCUxXD2p+G6HFThjJJpSGE8+qQ5nvGs9+y+BldW4BpSPuJVkvX71njKesRPZ+P3tXac2a3uLHmheY3mecCvDmeksYXfNLkdnw1nY0zs83FQVhmAnx8bFbbO3rHr1cDp7vKyZnON4yjXwhf5TW9miut0lH5YY8i9BTuXdYH5pfUKgKqwtsxYKD+Drem5Kp4IU33+Or9POILTVzwBUdL5RVz1846FYO1TA6b91T7VhofuHfilyqT9AG26XA+6wl6TyKKeSAYRYwXsaqmKTWuLHvPWctFZCFMHYzRaDvw2LXzOiBnuuls90v7RU6ZHQFNRI2IQo0K9ETN4GFzCyuk8TuYh83LWm+NNS0XHXHVLq1YuiJnlUuFSS05I+amb152CFKaNm0uAuN0LbjWHjoQv0f4q5lieQ6M0T5xNurpLA0i8CuuIXUIuXDA03/rPM4eJHgZ4qi1xVDEG6Sit0qdU4Y4ty36dtnvMHes7xq+rv6RDeFjwRD6xCHGue6XZ0FlcK4d5CPZx0M87ncFKeLx8uRBH1ihBSPos81pUgXQWAvgh4nT7GvB9+dSuXnDnbZ33Fbp8aOvsv23rsP21xSHi6iim5GjgaPJuiykxvEsbW3xHeycT3vfX7x0zIyUTRy06eWFROmUTV0c6CWsDMxPBP5XQn0pCh05dztDCxMjxvbSENT0++58bYtYM+H/bGrNmxGeg/5vJhM/wx+bZ7/r/3h/2v/rz5+bXn9XRKTkZOv7mfzRDJ2ju6CBvYi9kY21r8/X3lg47nZCNlY29kq2BkQmdsImzuZGJopjg33dqhIWU/9yn+fs2Dj4+EyMDnZq58bvNxkInbmJu9sXx3fprH+dt4W0D8FlSVEIUAALye3vtXbwtA4QAUBAQkBAfoCAhIT9+hPoEgwwLAw0Ng4GIBI+Mg4mHi4OJjY1PTEuGT0hNhI1NzkZBTc/AzMyMR8bBw87ITcvEzPi7EpCPHz/CQMOgw8KiMxJgEzD+X369dQEQoABSACkwEEIAKAIIGALIWy8A5Y+u/tML8t2N/PlfvYDfXpB/60X4794lAAwYyHsrYAgAPkCnL+A/eMG/Lf63M43j/x/Z/5ORhfo/HdnMrv8kspD/JrIM9P9PhZbp/x/a/xtC++EVFIB2DwXQ28AH8fH1/fAK9u+CzPD/VJCZ2f9/Ocj/L3cSzA4lcwCAQ0vNvQVYZDGyL44zwAADDO7u7u5ug7sN7u5uw2CDuw/u7tK4u7sACCz307s7NPpndvfuvXv32vt/73vvnU4ndZIc6aRSVb/USZ//sJPRPjr53/XRp//tonmjFwTsHeQLCNyLAAj9FQgIoBcE0PW3mvS3/zn9L8yB/x/1OtN/5aVj/LOxfXw4mTj+R1461v/cS/exMTEycDCzMPyrw+9/3UvHyPzvvHSMLP/spWP6u5eOTYSNmZ1BmFmQnYHjY8QzcYqKiQkzsIiJMLMIMjJzMvAR8IgxMnGysLJysDEziYlwiDELizCwCX7crAg7BwerEDPzf+mlY2X7H3jpQDZAQJG6QUCRFUFAv9KAgKJBgYCin4CAYm6BgGLF/FeeODYOBsb/hxxxLIwEzJz/5IgTd7B1tvtjDv7FlqSX/muiRK/sYGDjaPfHI2fo/teL/KXmh6n5D667v530f4PrjoXtv/HcWcd3ha0yfP6R1Xmxadg4qSGZSANsOUXz0P50W9MYr5iYknj2jE9Fbm81k4KJcUN6/X7SGBt1iYRB/MiecGbbHjxgy/5zwvcFWTv65+TLdH78789fbeVk4ZFvBCrl4OAM8S764GYR84eTkcNkR79Csg6wRnwd+hTsPRETQJGreMqlpw9o6zIx9zvZ9O2co/qkNcxkq5AAYT99XNZc0uqyzNUkV3e3HOxB9sCk01N5+er4qJM7gPV6gsZnfAHT8J3NZLVnIQiWaZqqIl8ACqcoLS6+1kIHNSjezgQi/vXSUjgjdtfK2LZIiYVxRfOEC++TZQAHl4VVxiq75gOJXxlmgcduRFWtUmHtvhn3eBzbw0JKprdLRubAu/uvrpn2zdfeGDfEzGhJs7yO637ENJCfEczY5VlONevFLRRWKoVyhIrUxg0+Vc54wYE2ufpEQeYl7FTxc2QZ/pG5dtPmX7l4n0+5eKMMviI0rI/dePRnap7KS082vcBH6VV3kGxfz1C/LhUrUZDiyVOdrg84M/H7Sqo+FBr1dqpnSKHNR/Q1Xu/cuK5cE3t53KSyf/H4OeLpplECvo77eMH6At4//Drz/x/YiH2w60eWGONfwcr/b6jD+Xeo83eAw/Q3gPNXrPM3sWPNQvAXKfWfwR4hA0fjP/dEry6tqqCgSS3oYG5gJav8oTsdDT9qG9g4/Sl11GL82/gUtfngY3MbU3pJo48RYu7kTitBL2dgbfzxi/6um/8MEAZ6ZVsVG/M/TE/AyPav4+bP2f71Rv5PWemsf7fSWRj/xZRj5qRXkjVwtPwQ2n9tn39j152DIPxFB4AY/VXz/W+x6v6iq8lBKMFBkD5E8Ice/aNn0f/o6n9UtRBQf5Q18RcQMDBQcHDIfy0AA4UAh0RChmJk+kooaO//F338R8qDgXzo44sDX24gQk7pzAyHaETc2IsCepz81n+zvzlT7+GRx18wxLR4YCr2iwZgx3Kmm1mMeFQj08C5NJUbTr8Kz61WWCL8ZBVH+8vFyWx75AGyr++PCh+6Dmt3tCQdUI6on6faHdpBuYGSj1c5SdOg48ozrqhWI5PHyEpm8vpdqb08ZD9HTOsc1szk1vvSOWVzMDTncsKtPF4dhlmmL9v+cJWCRbsK5KpYM7VImWcUZo2Aaex4YyYWbc0iV1kpO1Pi6qcwqfZne9joN5rH6lH/uDbM2VSpJw5pGUyCYR2LjbxNpNbiFq2+TCluTq6Dp5PF+gCMJZix+hk8dlg81ZSkVP3VtsYFDLYN1bdSUVKqhYFQ0zYS66ZiofKv8aV6eKSZlzENe5CQ/97awf+/CT1YWDn/A379v8SiWH8wA/i/ZVIIEFAwSPA/wIHkg0s/aAjwfy0EBQOHQEL+ymRAyCiogEJk/49sCnz58/n5sQUp1sdvZeqg+38tN+YwTRLdlKWWHEdwOGxzML9ilg9N9ZK55olCJiIibJjPKFTwEbGuLzSf1YvBtzRdzlcBItUs9o8Y4tJGfELJ/IxBRHTOtzxDh1LU8qgbsqJp3O2Mrgc3NVVfOxIsFX625YHBYB5qbUJan5w4DwEz8SnOFqLaANl6M5E2ULIhVr3BibZchYecr/bu8FBLs8RNztv0ZGq6vk55On2e+bId9ivNzwhpS0bast6GKgI59/LcIDxzGiNLsy3oVOlTS5OjGfe8jh7WL7smv3EiZ4Vj/ynEaSYhDV+eWypuc+rijllo9xBL4wju698waKT8X4U+bGz/7zAZ5l/k4D9IQvAPefdHEuL+kYTg/1AG+gFCCBmRBQ3+kbkep65qd6GMSfFS4mc9TJQiPIhZ6T6NSQcwRzyO5dvE1JVPsyW0iCrm/wm/20q4nI7AoNOTmLmf6qRTMl41iUfPRo5nvljvWcrrCMG3lZufFBla73/siJcwXgPklQ33fDIHxYdfWcwmQfzBx+3z6Uo5tvPnTHGUW8oKeCyojsMM+39XFBXQWFBN/w6G9QOB+ITnaBd5drlK7OnF/ml9A/Yr1R8s1s+XgjEwQ4zxZNykFdz0n85zMP0fU45M/y8Jmz+i5t/29Yc4AQGFhP5XYQP5b0o/hA0SBDIhIzMRk6CCvSLKvxM2ce5Ktl03kjzV1o98buvKK5fSNI7hV5ex6gfQO1skV0t4DQtGTBgLLGfWUEr9zRVpZkyZnLPytBWNYm7FT3/7bhhxMU+g0hvm8Fwp3nOhTEDSmwp9gm1zeITUpfQCq8TpwDNy6mWnpxaboOP6jp2UkGsa22Kv6DB9kl8dn7dmLp5/1CI4Hee826KblscUsdIrRU894/RDwipEoiAEmarniqiMHxaLxQzVbe8Stk3x46ycXoTD+blqBH+J7CNuY2WMDDEq4qMH+xl1KAmjgwywRUkcxEkcRFk4YlTxQ1ENHr9N5QoWVcpJekD9buckPcQKu91N+v1V4CfaDloPWo9q5yAmKFEJZYnUnhOKcsLwIVkxdQQGQz/jnBz8yVfjP5HtAdT5dqDyFlCwxK7RAl4puFVhQA4/3n4mZA/sqPu1CA2m5wfjf8SjzP+HeJSJkfn/HR79D+ZXoP6z+ZV/4MfJ1B5VEBD0EmeJTyTdH5aMbvEcAUEcjD4IqEehsl+ADKkfCORxhuJfjuT/j5qb5X/U3LIGTk7GBFof0ODP5MD/pPHFHQzc/wO4+vf2Z2Rn/y+b323ZUB+jwE9Yc2JUWSs20o9JjK9n8LTtpe0TLt0LbDNtTY1X+ZmhJTNrylWxoeIYTe2WqUkCoiTzVmdh9Ew+oyaERO1P6vBNVgWOgrGEQA31ldFRAajKUOTis4bRMout5gT4ru8iKRjMlPKJGOxMGOx7w9sPzmLF5QxwaUYCnjUkb3Ys0hMIDc5h5VTVe334zG1PSJ3JlBHMqEZkXxcUuQoKuBRxPufqf40A4wIDQQcnuP/npmX97zGRsKSIkrujk7H1n4mdj3ryDkbGDh9YiICHhZONhY2VTZSdhY2TnYWdk4GBj17R2NT84xruH6WMH6VibExsrH/ylZzt7KyMrf/0BMMH/Ps4qbKtuKSIrIHd3zHVX1DSHwTmYG73Z3KL8a8TD//Syx+H/KnwhwOY/iNUxfjP0xFMTP/dg8Q60YIWPQxfROUZXJONWz45yBBgE3+ihKRf/sHF60cTqSNIG1rddnnGrRCAjju5ffLO7iWps7zA9hhxPDzlEm9/2cU4Zm8gvThzCI5j4bS+X6gY4HSSbm7R8yXHXMA7lNFU197VpboQ/VvW6U9vDPsH7yMRV2kpAIvCoLr//KZZtOgFmXdy6DdUqw2uK2/dh+7NxKby0Cq6p8si/dxcTkxpq26JSWUmrDR2TPivq/zvkneBr4w0W0+fYytKdmDq8vAfgtNkusvjdZLz5d3dKR0qN8Gts+K+C+WcQ7+BdHy2XPznDv83kF3wD9Z1
*/