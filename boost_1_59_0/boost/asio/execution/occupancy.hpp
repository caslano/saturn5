//
// execution/occupancy.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_OCCUPANCY_HPP
#define BOOST_ASIO_EXECUTION_OCCUPANCY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/scheduler.hpp>
#include <boost/asio/execution/sender.hpp>
#include <boost/asio/is_applicable_property.hpp>
#include <boost/asio/traits/query_static_constexpr_member.hpp>
#include <boost/asio/traits/static_query.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if defined(GENERATING_DOCUMENTATION)

namespace execution {

/// A property that gives an estimate of the number of execution agents that
/// should occupy the associated execution context.
struct occupancy_t
{
  /// The occupancy_t property applies to executors, senders, and schedulers.
  template <typename T>
  static constexpr bool is_applicable_property_v =
    is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

  /// The occupancy_t property cannot be required.
  static constexpr bool is_requirable = false;

  /// The occupancy_t property cannot be preferred.
  static constexpr bool is_preferable = false;

  /// The type returned by queries against an @c any_executor.
  typedef std::size_t polymorphic_query_result_type;
};

/// A special value used for accessing the occupancy_t property.
constexpr occupancy_t occupancy;

} // namespace execution

#else // defined(GENERATING_DOCUMENTATION)

namespace execution {
namespace detail {

template <int I = 0>
struct occupancy_t
{
#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)
  template <typename T>
  BOOST_ASIO_STATIC_CONSTEXPR(bool,
    is_applicable_property_v = (
      is_executor<T>::value
        || conditional<
            is_executor<T>::value,
            false_type,
            is_sender<T>
          >::type::value
        || conditional<
            is_executor<T>::value,
            false_type,
            is_scheduler<T>
          >::type::value));
#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_requirable = false);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_preferable = false);
  typedef std::size_t polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR occupancy_t()
  {
  }

  template <typename T>
  struct static_proxy
  {
#if defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)
    struct type
    {
      template <typename P>
      static constexpr auto query(BOOST_ASIO_MOVE_ARG(P) p)
        noexcept(
          noexcept(
            conditional<true, T, P>::type::query(BOOST_ASIO_MOVE_CAST(P)(p))
          )
        )
        -> decltype(
          conditional<true, T, P>::type::query(BOOST_ASIO_MOVE_CAST(P)(p))
        )
      {
        return T::query(BOOST_ASIO_MOVE_CAST(P)(p));
      }
    };
#else // defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)
    typedef T type;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)
  };

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename static_proxy<T>::type, occupancy_t> {};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename query_static_constexpr_member<T>::result_type
  static_query()
    BOOST_ASIO_NOEXCEPT_IF((
      query_static_constexpr_member<T>::is_noexcept))
  {
    return query_static_constexpr_member<T>::value();
  }

  template <typename E, typename T = decltype(occupancy_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = occupancy_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
  static const occupancy_t instance;
#endif // !defined(BOOST_ASIO_HAS_CONSTEXPR)
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T occupancy_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
template <int I>
const occupancy_t<I> occupancy_t<I>::instance;
#endif

} // namespace detail

typedef detail::occupancy_t<> occupancy_t;

#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr occupancy_t occupancy;
#else // defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
namespace { static const occupancy_t& occupancy = occupancy_t::instance; }
#endif

} // namespace execution

#if !defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T>
struct is_applicable_property<T, execution::occupancy_t>
  : integral_constant<bool,
      execution::is_executor<T>::value
        || conditional<
            execution::is_executor<T>::value,
            false_type,
            execution::is_sender<T>
          >::type::value
        || conditional<
            execution::is_executor<T>::value,
            false_type,
            execution::is_scheduler<T>
          >::type::value>
{
};

#endif // !defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

namespace traits {

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <typename T>
struct static_query<T, execution::occupancy_t,
  typename enable_if<
    execution::detail::occupancy_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::occupancy_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::occupancy_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

} // namespace traits

#endif // defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_OCCUPANCY_HPP

/* occupancy.hpp
TDo7FLcw1h3QOjznY6QZZR7CbLSpiJQBtjf4bbeBkB3i67pHHW/ibnT+sK1+/Z3YcRPNxX2atyIMQvZd3D02xyAcZBR/LslsyikkfOwM2REV2blxtox02onm4qkzk3tGcLPlM3t4pojxnwffnBo5JzNN5FjlmczTGyak3JeshoqRhooVh9IZh9IdhtIloxeQo7vicaWLOJKlXGiSDjSoNupUgo3jZIaITDnRygKM47C40CjX6iSicCLml+skZD/YfJ3ExAdbr5Og/WCzdRJVH2y1TsIWR3t+sU70/INt1olyRmddc7qSLdUx4+Jwz83UMWd9sJU6Zt0PtlDHvPHBNuqYeT/YXB1z1wdbqwPxwYGZXqoD8YiGvOJG63WkEeitAxEcAtvjRiM40/APNQbNj4Y8OtTwf4uGxNjW8N/FgWGYrgMJxIFR+EilGoN+wYVR2NPwbzUGDceFif1G02swBAbrQNOr8MGcaHq/DYFFfgglPpgjTa/FBwuoyxEe5DL2yGQOH+IucP/O7EjORewWz+wY4yZ2YWLeKOcgdqpi3pi9HbloOWnBO4NZRc5Z4NLOrGXOUdDUj1nFnFXHOYaZUTS5TOM0eGBjbjPpMHigY26TzG3slM3Mdsht3PALMwMms07zOHKCytyGznnwYGRyufI+cqKb5wp/6ID6xeWNzQ9h8ODDbv4O/3v57Fo/ZmIiP8Rdh4c0G4U+bOlxzb8lAuGbjS9tNwp/uP5Azk6ujCmh9cXyeFAd5xZmRtvkciac8c3vgmjZMdi01/EAs7w0hpC0guioCWPjm/eIIbKiSIzabr6wymBNZ2KP751HlXY9BPwcDsjmGzKevVxfFu1f1Kf3nR4vv/HGvEMv7Xvz69AnpaCQRSfIB5wSAFVaB/fmfms5J2L5Olk99pX9pi8JBpeDQ+dipXGw4pgo+w1b8knjfcR8lRTnhCZF60TJvGOek86lWjrrUOmQO7Ehn82v2fImxRleI4P3R2jgDqKhAbpB1udmQTKmZaisUoZq8zVuYZNUFMEToe9ytCuDFQzpvyXfZNPBumrVn2sET8w1unz2Eq17p77XITwopfrtViKeo0I6LH76mr1uWwOdxftlQfPaF7pi5vkM47N2lhZn/LmYcMHPLVe6M7YVL2VcCfpYO9BBGD2Hxfqa9tO3Kf/2mTw+tzL62cTOZbpX/KXBTPqSFHB81M4LEMJG2S+BTWkTWBXfMev7z/hn8WaJgSScRcMrMYH8KGJowFzV7j3Q6/u8OpZc2MJTQ8bsRrffhXQMk9DXbR2abI0uaickXlSF/lYsgRIr4AHGiMhfhl9l0k342II2prgBM53hS9fMhlnejBoTti/slNJYtLoE6f5dj2IvYAXtmMu3OBh55COSpoIdHucHLV7FG2Pn8edTVn7Gz/hr72lzNCW6cg6Tw5m7TsV7mbFORpOYnNhO2RMe3Obik92Z+o7wQKwnrsf2x6dHgLegPv8WyJaA/rpbfM2oW/Kl1ZZwG1GLpF3EOnybruPzXvRoVqyX0oVH29Le5lyASyw3y9l0q3ADfBX3nvPRZp55CCGuFFeiiwluA/eBK1mWpnmDk+thcZa2q91am/KhXlZgFpRz9VFn441HVopbd+uNapb9ubf+4V1Wi7Nv5U1Dlv75i+chApffjKlAyne6IF0z57QFU9cUoG65p+qt1nrJwEbV5eTG1H3IPcIy/zc/Gz/v9/ZX/Ut5vFSPb9M/c+DxOOavpwP2QM175sTVAnf26svOQDfDYn43vahg+KAHBm/Cd19dKoFbRjbq6BBuIvL7z2ITNN3XitHHmlMYryLFaol2mH+YHPKr9LY97a/ynCQlptH05hKTGImrt5lFnBmO2VMe7IcFmTmOvjdI+saxWgix6fsR7UoZUEod6y2rcVpOiavD69dt5P7zdG5Fi58LF8uFvRJXI+GLoue93wmaGKvn6S4722+w1K3oA+c3ocrunIrUFk3xJGzFarRitSI6fJ6P31yfiQmavr+KPqM8b236bfdKQkFxKd3gallJ0wIpLY74/Ft66XCgpjcWx4T371U9wUvx+oFO21HgNZ8xWKE2iS5yLoV/nCXc/6TY8EIj1Pf3vbRtbhnZFPPCvphYtb5gvT/xauoa1cMsJutOOSfdWvYRuc9E+AbX6+H19vKYzRvRkwV127cl9rvdaArzx1l2i9dINq2X/nPjUrb0g17Lc/YGtVvVustadcTnFZeU15cLtA65TVZcJY+OL66Qri6racuanU69k0eT05O9k51ZG26uyytm5nNZzkMP3PcXj1ZDh9x8dTmr1y/RVdzZy9cMClPnrU5Dgdzhbl8vQs+PGgv6otdxz/k7fKd2vdjOPZ1dI1aiBlAYIOyV7FTsFKrlu0pemngYTvsq2SfsIX43nF1L0WIMbgX+KA7o3wGRNrSVN4DrwZTKACEEspk6nVg28QpkW5UVnVjZohN6OnGr20fGErwDxBFOdrfbEQ3iyN3ynFwcbzPerldgbKZTjE94APrvMyXH5G238+/5LyAp6bawDAdvVSDkLQk3w8AXknrkg3WY4aI9IkfmtpR1UDUfyNBbHUfU8X7+eOnhJhPOIgbmS+IKg+K3tBcRX8KWuGeDbt/sdXmzeM09RyUpPTLTPUgA8oqYHmFN/NJwigmbR0Kn3CYBQiznnpcjpAfUwUPLiA6AdUWajuRGgjNNHi32ixI0ngAqZxoNRE1u8HycVn0oDZl+nPJwmQk0Z1SmoBw5QoL2iOaeTH1ipmw3aM0bUnu8njTmvkr+9zNyqCOXW09P8K44HJKQUhnU8niSrrBNGfUZ7SMrT+qFUjk4q9m1o/M9dgB3V+Cm5GW+25zXUZcznO7fHeEFNmZXF5wefwJArcipT0cciT0hbojgF2dYotkK4OdpWwiny2LPDJogAFPZ8mSPC24ZVyPZStDnho5RnKl94vlEc4ppLaQBBGUlVRbWT7A+yc15tpbcq9l84jnkfvE9w+R7yunCPiwprrn00+jH0remT198krrFWmaiG1HOZTqml46xb2Wf0HwyuoWbp6sbsc/lvGKnhg+dOzqFuiW6NbpFulW6Zbp1uoW6lbqlurW6xfQo9an1yblGlsbYYzv2sPcz9jL2VQG0ACugGpAN6AqEB8oB6YB2ltks+t3i3ep6xDV/d3iCn3i67wLw9AjsVCyPRRtGGMnYC9mfABAD0ICKQEagAxDao+Kl8CXxpfEl8qXyJfOl8+X7S/5L/Ev9S/hL+Ut6p6yvrq8wFwFuIrykpCAEqsw3QmhCk7zPqhZC6MEvxS/JL82dun+8oPjqvwm8KWwSXibyx7uNdOzzAoYA5IASgDngEIAOSAGoMyz2xD2Mbo1ujWzNuR173fo8gb7GXjBgUa9IERfVzYpYlrMop1PTJiZLURdFzapZljSqO37Nia9wZvhrs/Xtn2ds9xj42DkYOVg5mDnY+hj6WPppPek9aT0Zfql+6X5pzxPgB4I3sWnjRJosEZS4SXJS5kURs6rHxc7qnhS8ouYFbTNCmuWZVZkFmRWZJZk1Ork0ysnU6FTUiRGJEUnSidJJY4ljSdSJ1EkViRVJ1sMdJi318Z01OhU6JToIi6ditUbs1BWJ2okLo1WjtqPno7h74ADCFUHXuIdh8dGsUd3RjVHe0a4/PkcajN/8G6x75DRr/vgcQcCkjVITsy6Imlm0MG9kd4TNibN2ZuDCyoqc/NsG8XyC+WhSJeWiVjq0aignBmVquPnwqiFlfQtIJxIuiVxauAXRqkNluwvQJyIu8Z6dXJpZ+XKq8golZeTl5GVzC5izrGJuBSEzc0emt2xPGD5RPH92Qjeuua66zvrNTkOcq5evV65XrFetl6dXplekV6VXUK1So1qjXKNur2CvYq9kP7KjqZRMcH7M9wT+GndRyD+Tc0x/y/7E/Rr4Jvmez3vs6+mPVxhiQX9V9blge8iBjPGnSTFDkqVMSVcaaEQKzaI/q8lKJZL1eHptcSOC9WD6XDdLTJMBrSb1YnqToa0m92L2vn+MK+MjNm5pjlYlMVytXCXz6a/2ertK7tOfnliCxFvLhmcsfEzd7PeY/Bj85fS1epXsp31P9TwH5mgwtQRj5oRoavoq+kYl9XPLx2ewfzwr0pp+9MDLbWc8rt1PTB3+tMr6ivqq+sotZTUV9qX25fZl9hWXpWsLbgsP8w8LCPMIC7gncnfELint2hsFvpW++b7lvsW+1b55vmW+Rb4FF6o9qj3KPeoPZfyl/OX8ZfwVPaU95T1lPRV+pX7lfnX7Z0JxtFhlzwvg+XUW+XgqCGHF+WkWdFqlklEWKsb5RRZFDrKzP8isw4ut0outg83CF/OjLKhXw+6JxMdmsSzgmmx+o7TlBx6Vss5iWcs2FmsxV7UtClmXNc1qWds2NmtxV3UlFwAbdaoCFxmlF7msdRurtdirOhaFT8vukLNEzKtaFsVPK/YtfSdmwbQUxpaEtDQiLBSrco6I2q1em0BXHVYFbGPVcgf+eAGJsB7Q+vU48qiJXQk3olQ/T0MrPcVUL/O/cAfyxxnIbtOIpqYmXD2Wmam1cmPZKvQqy7nIOYltO5sw9YyZVUOjUpVMRtXEzIHV/iD9Ko9tt1oe7TRVE5Vtnmu9WtWCRZNWVnOo7i8605S6sRXUMynXpK65QTWsnnrrFZczT1fwjriNfjuzimXaVaNd9l23XYRd+fsqhxSHEocWhxiHmrpBDet1crBB/TOv5pician9wxvTFyENUd3BGkfXYbtg1t4s8Q1Cr7CeQV8Oo5gz6zfcrSE/E/76nOWpM/R76ueo18k3RCQk1NfI5yioSKio10HQ3VyHYYn0H68jb0bPK6CusbhGknIc+5FOdHX2bd9cV54iQI1yKfxLYLKymglD3FbdoxuW2LTHUZLytWh2dAfK3pvXBr3MzlpsR9ftd7sG1na65qOxHyLoB/Tq5F9ofN+fs7G3qFvi13B9lqIOx5JxEolrhbA+b/rm4RyW69CQ/z84yPrjHmt3fwTw1YNqnfOnhrmNxFjI6fq2mRTfJJ5eGY86HTve6PJPa3vXb25XgA+T3cH1aucA0akfidvdacLDLKiOusJUjfoJaUPUbY731vgpLHk+TM6l2El3NojuNLz6JL36NNjuRPOjZ8zLrmKfxT6VvS2+VX5Ku8247bgNuS25TWncWjbrtOs07LTsNO207TS2Yd9k3WTeZOcz0K+rWWG3qbnG0RRfbEAFOLFI4BFlDDPfOv3x5juFNZXgNKxsgokPeTrpUBuMJU2fl4JFfxXmjcyfLX+wC4R4jc1m+QxM8rVUCJyp/QkXxkuZJYnHbNDO+pV4zcLEjlmffYthywQdEz/+dMRtz9KRvC0enihlBkNXpCZXfbbiyKg+LdvOwrFKh5zebAo7BkM7UjxqKHIoijyyajBhUPlfnZiy3XN5BXaNbBrZN+jasK/18Znl1MqvmJ853UM+IzfecEwPXht9Tx12ao05BMDnJjSIlFGA8+LSDobW5RbNDcAqgqVz60QiEgsuZaNOhR0Kbumh1oTZ5naw5qvNB6CphwXtmGwmue1ueCBMH8z1H+/ATu/BCOakBPDpQzz5oF2OeAWo6f/0uuHrpJ/a9bW7BkH4nvxG5IvaEzDoS92NshWYbRZYzNbs8T27OeUwoHoyhfpR7w2utyU3hXF6nGj6lnfH+Brawt5t+nd1bh+vqNBkwmvuXJZgjlcg2kMK1PBQ2EU+99Qh4Rvz+wDfNyklQshnBSjjfk7U01dw9jYSE9EF575xq2mGDsVdMtkMVvuZetVTNtu1pqnrfdej5TKnlOqN9oejlQq3nG4PX2rEcYQg4hnfVygc9m8KgpW1FHqZGDwmR7W/icWisXjNzlqvUcjkuHwBiWXkMtzXhcfMUsPjmkWmDYfjtDnsPUaCpgu/EiqsrU7RaPlMR8pKsnwH08xpAAIs/dN5nzOdprjfv5uO0es4zAyk6Hiu7KvreCwsLFV23ref2hOwb3SeJC+0bLo+47ptujzwPlRrjl12vAdAnS5VbdVe58ki2PuajBXE8L71L5LnEE3xPK/f0Hc+zo7VdD6tNi9tEdh3391zr235xHhf/Y7Owj9f9aEJdvz/hwA5xhRGMJaQ01rrslqSuhLSQvH6YN6mu8L7IzVnz2xmW/7k3ZgBsV7Dr4043idVe5ZP4HWvQ+ICUHoktBKZ6xB6VwsmmHEjKsNtsZGBPWCAmuKqeGxJ/asYzl5rhXv3q4SW2INGU4D1VdrUoX2f8mECzWxA/zDGVSN9HnG8iwnWCm2W9C8TiMctmOPZvb29ohHqBDd/NZ5f+jJ4JJ8s4bJfaQBaAK9rX0fyYzh5HfD0hgy9Ml6RL/5jShQezI9n7FcopOmZCS8wWrEw2c/WIkTEI9a3kosoVvTE+rPJt856EE3r2ZXyfDBFq/EohrjfwB8bgc4MY6hz8cQJNXEHvX1v9xee9XhivWSxI7t7wlbh+PFuJH4EVRL0TF83zYlXxHL2QuCzfSwQJWT8E9sTKNbLiOR7n3bhrrJyjFR/fUVbHlBOuIwt7pcnE7K+DCbvye3pk4F34vTTkyKBkQSPHUNtbhxx2h5r+ZRjxJIFkS2Eqj1QEfYF5/Wq5asaFXr8ae697naTDVjMnotvR6PaKn0LdyP5CohnIUwb0qKc/M8veaTut6y3OFcq/KaiNlzj9DlXFUVeRS2JyIedy2Aa8lVBC+LGWHnGx9DOdLxZdIEzbryPr/bTNRqRsgY3hsVpY/IHMdJBV26dKsRZMFi+cS8LeSMh2by3B3lbCWoAMCa02982Fq+stVRrnz0BXI/x+LEbeyhUBllzIG+r1hFhtyyPXmTLkWuZSZNi24BPrz984d6Wa5x7fFi+vFSxNU9B+HHXWzVjHAxnGOisET9r35Pb/+TuTR09BH/8qgdZpTVIH9KDcB1TtDh7ur2vfeVW1Ap5ENm0Y3kdaEN1WCric9d7DuWFs+4SiqPla7GfdxfCRsZPNpGLoB341XEYxMIH+iUL6rULmeVCEMBWOa4lhHCbC378OXbcmSsmW0YeVDIbqqKdO6uZH+S0cskAshZhNRMSL2fjgG+7ArV+5uqBRG1QLtjjTao5rmvsbefLODScB/NmIMIBOYBJbyzlKqkzu+eL0zX5C7svyBsZqe5oHJeEbmH2rIFluwp5VXx3YvfXud4nb7pTABgQTOP9pfRHYsAfH3+ORO6PGYlu85jNQZ+4X6+QBGd4t/G/3oQMF9EQNIGttcLdenBR7hNjWlB1hNCZm09HVSZwiF5MPc0p7kGVwQw/ebjCuIO+AiW4MqPJb1LxjXFki1j9P0lMxV4WDm1vNAtOlAyT8SacJ8jWZyOjQWZPXfOUkfsFeQ+7KYu2J53FOmt4+A5dHBgLwOClfAofIUnZEsHbJp9jHhauTEX06fFkPLqmaP909gvCaobfPf4b25dGinH+IJd373u+cYSIEUdHWtqkg1hpSf9s+FNgh4GKM3qSAWjGTIpGW+N31jxs6ISLoJaIX+FJEcV7PJ5EPYKbQ3z+Li+n8XKu18+5dzUNUI8Sx1CM0ZNBSN8+tflnZvJk0CAlFLUc4aQ2k8dNzuLV2pU4SY9CeqNpJFkazLH9PNoEcyUYFBeSk57ORMpFR/kp
*/