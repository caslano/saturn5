//
// executor_work_guard.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTOR_WORK_GUARD_HPP
#define BOOST_ASIO_EXECUTOR_WORK_GUARD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/is_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// An object of type @c executor_work_guard controls ownership of executor work
/// within a scope.
template <typename Executor>
class executor_work_guard
{
public:
  /// The underlying executor type.
  typedef Executor executor_type;

  /// Constructs a @c executor_work_guard object for the specified executor.
  /**
   * Stores a copy of @c e and calls <tt>on_work_started()</tt> on it.
   */
  explicit executor_work_guard(const executor_type& e) BOOST_ASIO_NOEXCEPT
    : executor_(e),
      owns_(true)
  {
    executor_.on_work_started();
  }

  /// Copy constructor.
  executor_work_guard(const executor_work_guard& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_),
      owns_(other.owns_)
  {
    if (owns_)
      executor_.on_work_started();
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  executor_work_guard(executor_work_guard&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(Executor)(other.executor_)),
      owns_(other.owns_)
  {
    other.owns_ = false;
  }
#endif //  defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destructor.
  /**
   * Unless the object has already been reset, or is in a moved-from state,
   * calls <tt>on_work_finished()</tt> on the stored executor.
   */
  ~executor_work_guard()
  {
    if (owns_)
      executor_.on_work_finished();
  }

  /// Obtain the associated executor.
  executor_type get_executor() const BOOST_ASIO_NOEXCEPT
  {
    return executor_;
  }

  /// Whether the executor_work_guard object owns some outstanding work.
  bool owns_work() const BOOST_ASIO_NOEXCEPT
  {
    return owns_;
  }

  /// Indicate that the work is no longer outstanding.
  /**
   * Unless the object has already been reset, or is in a moved-from state,
   * calls <tt>on_work_finished()</tt> on the stored executor.
   */
  void reset() BOOST_ASIO_NOEXCEPT
  {
    if (owns_)
    {
      executor_.on_work_finished();
      owns_ = false;
    }
  }

private:
  // Disallow assignment.
  executor_work_guard& operator=(const executor_work_guard&);

  executor_type executor_;
  bool owns_;
};

/// Create an @ref executor_work_guard object.
template <typename Executor>
inline executor_work_guard<Executor> make_work_guard(const Executor& ex,
    typename enable_if<is_executor<Executor>::value>::type* = 0)
{
  return executor_work_guard<Executor>(ex);
}

/// Create an @ref executor_work_guard object.
template <typename ExecutionContext>
inline executor_work_guard<typename ExecutionContext::executor_type>
make_work_guard(ExecutionContext& ctx,
    typename enable_if<
      is_convertible<ExecutionContext&, execution_context&>::value>::type* = 0)
{
  return executor_work_guard<typename ExecutionContext::executor_type>(
      ctx.get_executor());
}

/// Create an @ref executor_work_guard object.
template <typename T>
inline executor_work_guard<typename associated_executor<T>::type>
make_work_guard(const T& t,
    typename enable_if<!is_executor<T>::value &&
      !is_convertible<T&, execution_context&>::value>::type* = 0)
{
  return executor_work_guard<typename associated_executor<T>::type>(
      associated_executor<T>::get(t));
}

/// Create an @ref executor_work_guard object.
template <typename T, typename Executor>
inline executor_work_guard<typename associated_executor<T, Executor>::type>
make_work_guard(const T& t, const Executor& ex,
    typename enable_if<is_executor<Executor>::value>::type* = 0)
{
  return executor_work_guard<typename associated_executor<T, Executor>::type>(
      associated_executor<T, Executor>::get(t, ex));
}

/// Create an @ref executor_work_guard object.
template <typename T, typename ExecutionContext>
inline executor_work_guard<typename associated_executor<T,
  typename ExecutionContext::executor_type>::type>
make_work_guard(const T& t, ExecutionContext& ctx,
    typename enable_if<!is_executor<T>::value &&
      !is_convertible<T&, execution_context&>::value &&
      is_convertible<ExecutionContext&, execution_context&>::value>::type* = 0)
{
  return executor_work_guard<typename associated_executor<T,
    typename ExecutionContext::executor_type>::type>(
      associated_executor<T, typename ExecutionContext::executor_type>::get(
        t, ctx.get_executor()));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTOR_WORK_GUARD_HPP

/* executor_work_guard.hpp
b9caFySM1rfPQYGv77/u/S+WIKrQVTQ9BAjOwNUX1KUs+Zjw+XsJc4Q+PgBz34uNt7Bp3wub4nZKnnb0e5kihaibRLWUifh/Fz9ymIxszAne/hgRlxu7TR0bHT9L6jWA5LaDxdkp17Ts7a2Ek0ylKI4mz0DfO3RFsqhF3f4tZz9uYb+P+nlqyPsg0ky9bfs5uxRBn2k4MbdOtZ3SANfrEYkK3XbhOzmumHiU2rTfkXR/yXKMtjJfkzlrRCJBU66Sk1KBkYa5jlTLsFfSKM64Tefdctqx8qjgnHL0xQT4w6NV3dwG4uujF5di5hnBQ+p0oN5slWJ2hdkxp4XqyNWj9nxdsObVnqbkYDahk4oumtwhtzm0Cbt6lQWN8w9L0DYBBz7NW+lT1iGq3ea646kw6B7dwVgm4F0Vmr0WjY4CKqP+R9KJHYFqihVF0F+5OCNlme4VAbV5yVOHuWc45AGE+J4U0sJeXvwTsKhAhEZiVzKjM4d3kqBhXjwk1TIjT0ouP2MZeYZibyXiiBAls1E6qxYAKr71kpJWBO5iLAfBUd3GYy+oN35B9sE8f1xRSqRnCR+Tc37qSMHZ7rWWBtv+MvaeQINBAUAUfG/7jvdwLOWPoH9mH5xJaaW5+ESiHLDni21NLGDFKjmkYIz+q10STJtOShPJjmzebpU9WSUJZBqNbpYP9zzav4A5PWhlPkpzoWegEXHhggBCi0Pmz2wxkeYKMm11oJ9RwktYAFUSKk1S1m5Iok7WG51Re4q0qsKxQV6itTTTchXVJg5JxgCoMPwlej1VfwUcC7eui7EyWuuFmD8ZE6bX4mtyIIx+pqrw5QgZgEU86tgOkQv+ofwQszwScp2zTpHoycHLzFfngAS7U+0s0oR7VfP+BiVAQ1Eh6D9C5WLMtZVVsgpZhdsSTUVU0nNBxDYnruJTnV6NgSQgG11+lRHqQClQ7ZXD500D/IrMqZXz5zSAAoc6OL97nkA8FZyVj6rAwahNFFriNLmFqjqTjdPpeZ9D+SajBjXsYmlz0jW0GbeKqAyL2StiGRdSNcEvIsG4sk67FQgH/A1TPGhR+J4QUAyniCoB9+xQFygKcBlnVrNezTybtGOkg7yDHIs/aKTCZUrPpKOybkmbMW3VRrWeDyXMSVDhx/PHuZeb4JXxkNE3upnOGNGhM7JWc54GVgEMM/CQXW0LOXhkX+SAwN5Qg9iEIWWLSW2tBnhS3xW/uUcSinhLOrD4CqsvygVdn/XWkAMUxQljv7g6QlD3+4yrZtySUyvYQX1/Gp5hb4tNbaOGuhMaD8LXz7BvYI/3ey8WcssDW+qkXKFcAVKBUkFcwXzXzY7p1XPAUaplvnGv8djRpnbdZO6NZo+/VXUlilsoNEuQuE0puacImOpCba7KcnwvY78QSw0pQ805FadyXEGJkfk72M8ja6PkqmGPab9hn+mg4YDpsuGQCVQ9eFLAhXAg3ni0Kaac1fUcPigdYVoouMSpbEw/PxWQe016qYUEp8J1dFF8GjWbU6LpokGyzbKbuht6U7ix0kzpZpatnJW+ZvmY7XB5j213+YCtYqlmqXap2phXtglDOfgFyACAFYDqgDOie/Rp30KbXVAwhm2Z7ZmtuZmkP95Os944GRYMi01XRddFl003RlPl5LAXp4K6yioyNEVeviNHBPMnnt5lSoD6RtvQCwU4UgA566bAEFU9IsMEDD5Lz+hizpR9VYh2vABMK4RLBjF9Xc1iW/THPTWyQnFp2IJaGW1qCqfrpQZtqahiYdGkXCpjIz0Qp+upBuYUbSkuLn52rDw7qhYVyo0e0bD8VAeFvdFtF6CwrmDVCx/jCs8xBryZTLDr20vaqdpzyhW2dbhNpcukx+WeDjIMsgxyFPIUEgKWAuqWJF3CysuZwhu6+E/YQ79HhJsKPB3AjBXePEHTtbgsqo1pDgIF0rh//jXUDWORwRtxXfrbANWitZDszy6m6wYbhYPJ1TK8siFXrMn0o0okxwT3JAA6kibvSpocTVHzalaGXvG+RM2uFkTkudg/DK443wYGNgncayuOymHOEJC4MZQn2rZsr7jDC9RuwlQPeuUxxR55aTdulx2ATUeCvurSo1chUQOzYtuntip7l7NbkJlQdZqIifX8McfyA6HN0pecWuqgiV6JkfFeidrqhprxrs2u+a7+rvNOL+dp12+Xa5ccuxi778ew3Yy+jipF6y4wJVgqEOUACf5/eUByoGUgSk4lwGwAF/7RNtTF48VUxVRFFb1HuxJ2oK1UrdytTK1910Js/v6d5/rX5Qz7kqT/2PSLvPVH0DkXJJLT6N/Zgil1LbhZ8vjSsokls5kks33XRaFQl7301cOJ8tixAhO46DKHdYQG0chwP7GvmXrMmlYzPZaDaE85U5toqrzsre8YYasgpasF2EYyGhbdSlQ8ZwYyt6S8LfvRH2Mka8RpDqMt9tGiYiZcsvmR5VgUrWPM1RUPyug5WXcR959MMk0Wk0NQzVfcBu77TN6xDihMyRZ2XOO4kCMsvMJsDnDIU9dRdAvbLdviOIWtJ5sKFOUfJnssqtDmi8oW0kxcJCy2zUPS0tIGWdjYADPWVB5lv7SYvbs/UKDUjVCLOO5a0tJMMJZlaC6976z61gidp1AbKjKI3wz01ucraEsUWA8WiTQMzdl6rXNVaputXIFu+04DbDjW7QbVaKFz0t7lnI9qXtrWoNgxslY72LRMtF20Q3QbuGmaZpp/zPEtda3x2ZrVHXUM+bEbOCGtpCcy09a3eqjck1hV6jCqH+4x7T/oVkWLm0TQMQDxgLydwrnsfUrWcaCbky0mNTM4Cbv23MLcM7y+b6YyXWUZ4RnV5tQY+QXzshFizY8m8WXjTmbgJQlyEag0UadiO+ZyNmGvcXW9Uwx38uDFLjqXiVARHZOJOay7WVzLHK2lTcuTYhnxTiNmPe2tI9twtR3gP08hY9q8D/CcK6mPm4cXPtjseu8bzq7PuGdhMVpMztFgGhGai1iBzUae9zjm33koABoqARDX7tQMHeqAXsF/XOzVLZpbhYoZsdWAPwt9W1ql6CpVDLSQJtLwqvYvunOlpQNJ0KWrTc3QsO8N83JxNzsPWvArYVW0T5mMunylOBZ99Nr4qCRtPqVfz5aDdn1ExmeN/uWLT+UnoE+0B9xYbRJGltNFnnoNF7VAmZuyipoWO5rSCpsGD+jD9AsLjHVpuJFdmO3nwfT5Unideoq5lTmPHqStMNy0XL+M2C7bTtou2bqNdW+0beRv4K6ufKxVjHmHe4gWMf5bN7Fy/ZHsbOVmfVh8RCHJu8tsbWxdJslWEYC8tf63asfXhmwq2350cs2L1jp+IDoW1eptIGQGkIRm4qRLFFj7Cq6YdleyGrnmy31ox8+V0VCWb4jXCvcJLNVQB0q1wmRFlsRfpsdR0DOpbN25/WikOb6IKsqPAswJTbDtl3PtBOmKzksYwXHP0cABVf1iMkfDaCzZSg7FLuSPydNDe3WOZSHTacsAnOgBxn45lNKm2RgwTFr9gFWa8ixrZ5vWfcl+OHIJ070vvQo+mxUb5r2QRdJAXSTkxtpjivGeUyE+Tj/zfHRJXWv1SB35V9A+Rasq72+gzfHyjSl0fAFnUMmxFkm8uE8/9p8WTSQmdY1BY/nPeXHu2gAa+2t/Wzgb6XbxmTvpQKHpH+5e/n13eNzA0/1a6ZvCaxg8xjF8i2sW/yDA9NN0amDPVUBqpja17AKVf3W9XPpJUzcpgvOf8kyN3fL2gTRvPEjze9o7EDbhdcJVNgKs3owB07PS/nP78wkhYT8kn3KQ9A9x3Ow7j0j2qyn9wjvMUioYuQtNgmmnHFSSlJewkTINoSxMwVnsUFcVaFqqGtnsZ2jo2I/PbbQ1nF0zphlR06SBeC74FkUX5jvD43yzt7a03tBD9fIYnVI4qwWJ0COle6CTuLfrMCOH3rd+HiTJ5ZJ+KnXqLA9OSlfka3/uSXA2wTriKVuTk4va3j1MRHbpU+MaLv2SBUOtfoIHSyjjN66p8Q6mE3c6ilivXMMtuLVj43GcswE7AiJTupFwU4vB+p27OqArbXazx2oadULDc0a2wbF6PC4Wpi2hzv06gtJoCMs/inFp0X05sL06zSX2j1xRZGcOzJSzLWeReb1mJnE3ndp9uAKED5rd/zCb5xsNvP8kdoZ9FqFLaPy1x62jsBFXYfJOfBVrGuLnV6yGadiwOvDuRemJcv8ylD6outxKyeHKXqaZqlWkZGeh6gkyEYEHCNTtkRcI527E2+qmwe9jnobgaFBeiH4ul7WAL5YxcS+VtRTcclpHUFi5IUgHH14Zn7NQMiE0qDvLvJKOVdYRc2iSftgflvFoRJ1UrEpJS0oaVivt5NdbRwCUQU8dDjSI4Evr1dBr2ZBlAKJQseFq8wM2j7XarW0xM5datzuOPGr3RjMGREQjMXfkDdxR38oMMxtux0RDzrnPscqLWJus4rvB6a2KhxtLvywqwtzfcu1ilWTa0tVOypFIB4wyF8nvNn/Qlrr99hOJTiesoVTX8hA9wYcYCTAhSjv6BoMcWiFQ+ovuPaGmtgOmQ6mqJ/w5bR/QU5Gy/ndNqAHToVzTtxEBXQiJg4p3fZ59x+6jz/5maFgff77mWfIQ2xcyzzmto9w43PAJiJJuFcVUuXn1MROm3TflZQoBLNabCnDWOY7D2kAz5mtN4jTHSZZTss0/CynHHMq7NIQB4qUapwFzgbVw6KnkuOAEL1m51DKI2DWcn1LHPkxpq9BKgTnpIOLvxUU6fgT4MOD+HwsNY4tlCGiaWWjQgMDBEDfItOtWcNn2jTnvB7Eh5tr2n69SVMO6F1W3HmD92p8ha3sJVzEWkVlRqAW9vnP5/LhNmwAdjBRaynvwmLvuXtfbqXFTD8jPEy2rfFzB0ASyxWcbzHKgSrly7Bhn8AyMpt2KDMXv76mx81wtPuHdiBt0W5EcxVwCE7sp+GIOV4oEfREH5fLb+mrHNtHMCIygMvyEw7mAqavS0Zgj44fsKLmIUh992xNJ6naQvfBWJsAWNS6vSuYkongyc1vOTWWs0gG04raXqwej00ZStjfaar7gfG9pXhWAx8wVamPPORzSaoEUueFyuUBnqinlDIQb0BOPJlKtFfGmVkp22crIt9Fielf/Rxw4mq/9PoxKb2yXPjwMTz4ttgZb/Xyxy+vLIckurqVo3sq6GK590wjp/t0ioWvtpSyDuwgWwAOpa/d/FQY5SDn8/h5jnfXTNmc6SaCUlC6cHV68wg0VVijnJ3yFBqJulQ35fwjUvL/9N0Dzz7NxosJItlkWnWFPdLjJ35gAZQmMtYmr/X8AHPkJMxOPZa345yDy6Z5Gu3rge/DPb4UDVkSpqnl0yvNj06mmKV7v2pwyqey/tGv00zXKsQAnK3HUm5Wksjj23bnEtHNMcYw+3fWL0K+ZXvR5PhldvO04goSysH+sEyKQwvr4SGR9IlLq/MXQEJ2CmLsKD4J7UEJ4VDG8+l5Xjq7Qsx/1sg5MD8XlOGHFE3CjNpPcA+ho8YQDLPbGX1zfALWN8TPkMGWBYwrDGitufScvTq+L9G84xMhFPhFr//JsmfNTjLhGSv0hr9NMN6QG748EodgzHcfRCqHlBqiAyOyJCwvwOBfJPylN1nqTWar5ns4Sr4EKqS7plnB+rMqEnzNFzq3jBcbUnzJDNioD7LTlAK+ht5Hm6zl8FuQNM3naWZrP5Gf4mlNJfvGh7K4mywt00IMlV/o7SLCNEG/g4hsl+JgpG2NXey/J3iomep8xnJSE3xbeYLYz2hAxX6vqjxYVzi/ph60UQSl4DstwZW7tfQZ93EgiMdhinS3y4NdqljIrFDOofFZTM1uXs2o/zJfb7yHoF5TER6+m1NysphnM1Gz3A/ZGxvK3HYnrUZ07UcEK9LNwBUrnQoWoW7L9qOOF75Aqhq5lQ+FODLMQaH0HzbInRMWAx01DUxdOj/0zhT+28L3i+z547pOP++BEVG4WeN+qW/xseWqnYOLCyobM+h9BWeXSUtOUedtsT7lSoNeOilsS/I7ATXa4QzNcU+Xqw8MMJ6fr0Oyh8E+8m3iujCzbxiEAr6c/lwYcfA/MpHRnw+ND5CCDtV8s0WELr1BztP0+Ui7aF5594r4z8aq0g09DhRZaZmAoRmfWIvC+bQRB0oDnCHSGwHTKtpxuEYupwiaUTOIT2TcOxSWGYiM+xanVm3nb8pyND2+mMk+sbGSurM254VrOukS51FNX8ANC1rsIQqqXT/tiY0drr2eP9xfXsYikveO/p1ekoLOGZAmpB7vmC+yxxXi3BXZ6m9L4xq0Wp0AQ9TTcKyY8SddLcmunotFgbAQATExigw50a3Pbhh0IZ6mCWy6vzOImwzXyTkbY3EymYoXkraUwo722bTtcSUnLmk61kMuY4q1E7OGjrMeq6UcLkzz3F1ZlLl+835XbIpRcnLTZq6EpcM4ILavrTZ0OhMi3eJqDbe0EI2VyK0N77OmIH/5B1DFWAqqtGHzAM945iS7J+p3Sv5lXDGzdu1MnTgU1maJ4h+QPy676LbKLtVGPedZFCVsmddEpTCJy0zFERQ3K9pOm4bBCe0SRmbmduxcziJRLIS8QVUePjmyHyWqyk9sdL2l+u0KWgGMWqKloa98Ekmi8/wjaDXNfek28XiPzQnmI3kju6dontECYmMnv75Nh5UmMlkNARjhyEEZVWquA1R9W+HZW0oDloawDotko6oP00me1G7UvMLJkK4G1/mM2Oovd5pCnl6Grh11cI5eDamjsuSZgOYpUVPDHZrOY+vlqql5vrCX83fEualtdTz8ucNz7ckD70Yg3iCizwhh+h/LFX7RKSp+t/iB8X3JxYoXO/ma3o2OMbyDjDzkOWcKpi0HvzjKqo2wPECS1Twoc2Vvml9cFd8pCci53x/PGieMBU7Wrmp3hXBbuUIfrlJwYf23nphGL9tDdBl7mHrobP0zQcVHU/IXfypDO9RBTJ41MEPPoq4VXagKOrO0LkCZ9tGl8HXQl09PDSIttd5ip1ylFheVPyTex/ttWY2U7iXrgv/Nz2bUfKSwaOQRuSv04Po5qKECOWFhaaY2T2m3X6xjEExDhy/vSkrZyR1Ma+tKpd+J0WxAg4Lge5DEc8NSFFT/OSj5wojWzSs6M4ls7FGJ0L4mREIu2iJGQJof2tf6fDatBGY1D3Ggnt8o5P8BwI/metrEjUxrhWeHInKVFZq2DWXn51/aqroNuQhKuri6jNlLtepcZQZQXuSqTb9OXkowpp2OWSV2BNYdQDWCbijyF67kqBd7aqRWfP1M4FiV93DRpHWCW7CjqVVpNthbmWWY/CPQt615s9NPvW9teevs3IBP0l10T4YxvMIh1vjJ/elIc6VSPc5OlCBc5r6sizAF2Rh+sOsZXAV0aRedTTVQtaWwufTRBAxlaHucX3VXql/BHG8LwUv5JHCLQHHpUfvYNCY/OGZ+4DgX1Bc1TY4svSeEqK1oFLpzZBJZ0QTLz6/RhtVGbnPl6XuLiARz2GyKMsLp/uw9AgubijhfB6yK1WABESwdggRlNoYKJTzKiDNJiGZbX+M0cKgAELPvTWfT640/nEDY8gkvu8SdUxIxAo4RCTZ/YPEy/J3LTTMUg2Z3RCNIEmIzkfb7dC73ill85QRxpq5xI3Op6NdtU4gK+EbEWZy6gCTUJrkdf/LvRSpbXFochYA8LwuZRFbQFTrUg1gE6JDd1tDut9mcoEgOinr2YY7Nf3f7EWClD917qvw0Fsh38+vn5AUICAAD+BfIL9BfYL/BfEL8gf0H9gv4F8wv2F9wv+F8IvxB/If1C/oXyC/UX2i/0Xxi/MH9h/cL+hfML9xfeL/xfBL8IfxH9Iv5F8ov0F9kv8l8Uvyh/Uf2i/kXzi/YX3S/6Xwy/GH8x/WL+xfKL9RfbL/ZfHL/+/OL8xfWL+xfPL95ffL/+/uL/JfBL8JfQL+FfIr9Ef4n9Ev8l8Uvyl9Qv6V8yv2R/yf2S/6XwS/GX0i/lXyq/VH+p/VL/pfFL85fWL+1fOr90f+n90v9l8Mvwl9Ev418mv0x/mf0y/2Xxy/KX1S/rXza/bH/Z/bL/5fDL8ZfTL+dfLr9cf7n9cv/l8cvzl9cv718+v/x+/d/7u+TRu6Cq6Yu6+Q7qEUgrqhGvkbLFAPi3ScL0tFyLBDRWGHXaTvoMce9O3HB59pnGdRTvLbSXQhwIGFIgOoVNpZHL+qqwBhtIrpcYEpprsjltyL/wqlAorqd9UkODIa6FaifayLAGO7QqWGx7pY3SarHJ1WBKKh/QGtpEBoyK463c8CNfpzl+ujIFKlULjtecOyG3Q3wi3Vux4Ip8eDPGE/r6OmaYPpFs5lORWdcbenry1pRoZwt08Qx7RjJ+bvXGUXSDM+022RUobnNKXpZOJcUCNzpg8VEWXRr9r3734WIZBllAmtgnAyElmw3D0onPdVborMsGBsHIrqDiCkQqoyXnpBpgPjzT/urhaEa4cZOYARxdasThYbUtvZOs+pWFmkneMW9YUkCV/Mjkgc35YrsnMZTp5/Y/VvGfQQJg8EkpBF8fu42FyQi1uU+vPgNwpjIgttDWkegP1OulsWMxHFe1fPWg3gc0+/pO8J4Q/k6PoKqHCN+lJN/nYkHHUbcfPqWPXe7fFU1p1jtMUKgWpguBDg0EgjjnmMvudW/y8BWk1SfltTNkzxJZF11qd+MjrJvd1LFx4tOTouPvPKLMx5c0Sn9+EGSU7DO8angPsB2Q1zHWWxhusjoua1HmT+iISmt5sRqYUc74ZivIRBMVorQ+4nypRGz98wQNrUB1+w9b2Kh2K3zsve76l9Ykr4dY4MvDgmoGycxvm58nmCSUv41wjRGoge3F6pTxz/NLFTjYIxgtXqTPaq4wyBb54XAibd7sPMKZUEOf8G7K75R5F6Nv9zf1ra4mVR9vFzbkEUq0z5igEiKpBlumsKGwgOTxcYXBXnEXyjuC7+JDMj4KSguMatqpQtH+dH57XOvqkGEEsEtnzyy0xM6HsMU4/331Z9K9DGijl77EE108bm0KI8s1wCbOqXE3MHGXqcKym6E3u1neOSMS//fBAPSJeJHoeLCyK90wT2E0RyZ/nlBoUAiyjQ7tduY+br106caXtIETs9LejkrLrE08yym11CklPVpPsxM=
*/