//
// traits/bulk_execute_free.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TRAITS_BULK_EXECUTE_FREE_HPP
#define BOOST_ASIO_TRAITS_BULK_EXECUTE_FREE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>

#if defined(BOOST_ASIO_HAS_DECLTYPE) \
  && defined(BOOST_ASIO_HAS_NOEXCEPT) \
  && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)
# define BOOST_ASIO_HAS_DEDUCED_BULK_EXECUTE_FREE_TRAIT 1
#endif // defined(BOOST_ASIO_HAS_DECLTYPE)
       //   && defined(BOOST_ASIO_HAS_NOEXCEPT)
       //   && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace traits {

template <typename T, typename F, typename N, typename = void>
struct bulk_execute_free_default;

template <typename T, typename F, typename N, typename = void>
struct bulk_execute_free;

} // namespace traits
namespace detail {

struct no_bulk_execute_free
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = false);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
};

#if defined(BOOST_ASIO_HAS_DEDUCED_BULK_EXECUTE_FREE_TRAIT)

template <typename T, typename F, typename N, typename = void>
struct bulk_execute_free_trait : no_bulk_execute_free
{
};

template <typename T, typename F, typename N>
struct bulk_execute_free_trait<T, F, N,
  typename void_type<
    decltype(bulk_execute(declval<T>(), declval<F>(), declval<N>()))
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);

  using result_type = decltype(
    bulk_execute(declval<T>(), declval<F>(), declval<N>()));

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = noexcept(
    bulk_execute(declval<T>(), declval<F>(), declval<N>())));
};

#else // defined(BOOST_ASIO_HAS_DEDUCED_BULK_EXECUTE_FREE_TRAIT)

template <typename T, typename F, typename N, typename = void>
struct bulk_execute_free_trait :
  conditional<
    is_same<T, typename remove_reference<T>::type>::value
      && is_same<F, typename decay<F>::type>::value
      && is_same<N, typename decay<N>::type>::value,
    typename conditional<
      is_same<T, typename add_const<T>::type>::value,
      no_bulk_execute_free,
      traits::bulk_execute_free<typename add_const<T>::type, F, N>
    >::type,
    traits::bulk_execute_free<
      typename remove_reference<T>::type,
      typename decay<F>::type,
      typename decay<N>::type>
  >::type
{
};

#endif // defined(BOOST_ASIO_HAS_DEDUCED_BULK_EXECUTE_FREE_TRAIT)

} // namespace detail
namespace traits {

template <typename T, typename F, typename N, typename>
struct bulk_execute_free_default :
  detail::bulk_execute_free_trait<T, F, N>
{
};

template <typename T, typename F, typename N, typename>
struct bulk_execute_free :
  bulk_execute_free_default<T, F, N>
{
};

} // namespace traits
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_TRAITS_BULK_EXECUTE_FREE_HPP

/* bulk_execute_free.hpp
s0Dkwsfvtwe3KyO/idQXvHdSYo5ewheGzSUdvI7SeNMbK8BAmTmcsNLLhjpozOfey4GyLwrNPFMKm/6c3uSTNEN0AvzGgsQsNGXJiSaF3YPa6cBH4lbc2JyiuUKBwj44Olxxnh0zStC3/AiyQ7lUQ7x/UMO+e3BZeWNluYWmfb+vjnG1PmRTQYo95mLGCVijW1l03PbJIuAOpPrR4CsGuT/D3hhlfEk4pPiEIcnogiJNk/HD41+IsFe1CGszJ6ymuk7gD3c1yKBDp0x7xeucEt72GJKYIq3lQAJ6nFfQEvCkJ7cUv2AThDMJWNsHjjckAMkr3O5uRK6mqm2T2NmdQYhcrhjHkxUjdy23UzNM0gxwRDA5Whb7SmNP2ReLYyh/HUhhUwPITMW/s7DpxQW5E+OrCUCYDCtolzJ8R9Q9tnXmM8NzLFwfyysEXRMaqghACEDX0CGDyp7U42w0I++BsJQYeeYyLQeCG7/dMYcUYb/Vm+37z+5mklla2w61utXgXJVqbURiHiH7se9UWwo/TPPyXhdmakFQGn+aykmQXUeOjpUmqMbS6HUqU61yWTFGWtjpxMHLKiV5iJTKUCQVmcNBU8rbMUGUKuIZAWN9yU3ZDsVoiBAP90aBDQm7owBoQ99i16CvZn0EceMAJY7Xx64oCZzb/ft3eX+JuxPiDsgYEPOemi6V3AlFQcMsdVF6w+FyVtFqVi0OkytIqMnxpLoBo/m06st5Wy41tD3MG72xNCAbYrK6XKBhH7mPHY0SL6eCjMnWIWBBWpaUN1rirhBksn+l6ufp3sarmj6I9ggAT9WukaZ9wZk7aOqVffHxTS6f+DF2nC5f39C9mRIlm/ypzKE6Hh2cIKPAUqIPVdoAdHwaJ+DqBDkT92997ouR/r2WHFaoVw2vTBp2kCFd9xvyHwLcopUDqDdm+HIICAuYABMgpuoEvCkSOXXHzPf7sAGWBeLu6c7mImnV7jb5k1kWNBEs2HBfHeqs44MT5Rg+t5Rev/np+gxR0MMzTkxJ2UPpuzEVgYfOI0BVWCZIWGxnlwNSwA43m9Bo+RXv6369b2HoS3CIUXbLUHylqlw6eyq+NJMzUQ0PWISY/Klir4L6USLZgXNDoFAmGOzRlkFJXEyRvVHSOscAHfrROasCycq5VJc9znTU3LDmRxYdmWD97M5GDGlsDrq+t8O3UIF4OhUBPzzwC9u1+IQTIAZg+MjiMbehMx+ELQPzizigIQutBobjD6bZGEGGUk8b5B5gm3ZWBPUUshpixelNacnfM/LoBPTUfP0+moe3D8g9J2R5yoVQDOwVLi5A0N+O9RCHMkTgYvA8P896lB0SqB8D9SrgdteW6fG8UQZPb/dcjIQ1HE1fSUAqb3jrmJXDCzJ2HsO3470uAtyTImEDi5C3CBG/WrKpdANnJU4Ubl7goCDfGEDPTtUTbmYgKw4LNiaA6tIpFPgPCJYZeWyQP0b39Qkkj8HyJlP6Ds3+1rJhL/L76ScWM+qkpaIWVg3MU/xh3H9S/yXPbZRkYtYIPRgdEKC1gtYULI1teqmN0gwTSTYg/vWVj86JnYFfCbn+m06/+qRtQaeIVOz/zQI0pI5MIRemXpS/QMTpJtNx/gw3MH780zQGWvJWIAMHjU9kY6Sl4c+gYORvYPhW923HH+Wx9kA4XUG/+0emH/pQFUrpJ4yY3tXA0GzxNNknVxAGOa7VW11VZbUWDEWREK8CN8WKPTgtChxq2VlSELtDQzrf32k98ba/WwnDIItbe675tQpIjKO1QSJBtJ2iYViLJLnjuN3l8jsoWeolRBu4WY8adBiinl3aTHc0rK1e7/k4VhY3Q/hLycbfP5Z3EXhPQX/tNZdnmC6hHLpAmMIgW1d7apXX8uvzzZrba44neDR0v8Qci39bzLA0usxmXbGgIBxUb54E4ZZWtqKvb9c7LJV/AHQIqD2EgRCvBhVOJpeMOOQx67PYDhT9sb656esozAt+E2Scaf/kGdTRD1dDDNY6R7eBp6tADDbc0BYqJFZ1lP6mH2hX5fyEhadXNVflrkHZuzDZZEszBIwsAqPFbzPXa7Cp8d4aq6FndXRQQDOPda3lMjTL7xmMw2qcTpmXqrzz3twDzYjxNIYxwo/DP6JvXHWlro8SH4L2ZVE1qBJW00SJbL+Aj0TeNLl37HLf7eqVCDXueaqnrT3FGK7ICxVsWzhtJjMaylfO2ixfDnBdXTOSVp2MB3x9uxHi5fRxVoPNE+cQ6NqgccAyzK1bZJlieY7H69SOw27OESlFeBBrEStK450Vpr1+j2PjPUXS8xImbFae52ete4BaNWoBBwFx3/dQaQyL0eZNlh/Hz4frLaAlh210RcQmc6QVukru8tOuxQefCBpS2GCPAuP6dCFmstpcGPwtpaf2qyYqkEuusm9n4v9bT4fmxmg7JqOGPnph1qkOWJ4/jLSLFj4ej16xGW5CTDd+ClgawEY7c6MU9gLvXNvD59563R8y0h2TI1RIy+8gR7ZvaGqkkf5RlyUPiB040Q29o2LV6dAiNKTDnvtiVULuZKwcMrBSv55+i9wC3qVWM/8+4jgJxP1LILxg4YG8QLRiDy1zMLIYz6FVZGrKA/ukm5X2V83HX5sXfgTPlPcBfOdiOHQN4fxFPfkdIo/udmLsMrG37xK7sPFT4TnntbtU/jECGQ5+rirm/x/0DvKvzJCe53L1rItX4fQ0EXWV/BDwkfANmuzQ+aQNmsEhStm/GrJanMWj0Qh7exgneZxV10uPYiun6LNDI/dHxs+lyHDiGOaGV8sKTJEK09f/TWVi5M5Qw4TaNK+TXl9ag87WPNrhcwK+jNxrbGFjkUobTwln+xSZNhO28jQYYqlPVc/pRVJwXAkiGjDgFb/u47E+m5jJy1bzJt+iIDyy0nrkKNzfsnb+MwIRQR70CUGEw+OxABEJIdGE1lFKpkUeNaDDXZQmibDfEfRlWEYyINiGg/ge+FE0LEt31yIRx/Mxq1ow2N4vi645Md5YZKRDRkTL+7shJs8UNHAjb/X3P7im6hKKqXGu+c6valhyCGIInHtwFpOND4o+7VfLrjXzeMtAPmGR0Vyy8FgcKChrL31OdStSHLKoa9+SYAMcCgy1DBqFX3RTm984MaU3E0MCVJwpoPvA7p7VJIUal2KvwwA0BKJfhOr8er2xOulA0EphUddgAXY5m6FsGhSUDK2pOI05BzaHu7YSAN26BXQ6yNFJCM9Zra64YtEa3gGU5mkpXHTYQcIwExbga+3fe015KiaANzfYLKAkJBGUPSyVPm2LNtKesu9OLIn1MTdsKLSUxIYCXw2dx72+tEhtSPl4LNGWY49opqELvv9OOkD7g+MEJhnSHV+Vf3/t+ZuNM0fW2P55e9bsDjSEMf+4t2MpsMnewMtmaCPiGij+vuicnJvc8nq7VQVk7K7jHIGASLhPt+D9YWVlzUa/VTKwBUM70DjE4e5CCUfSjLLAXhUC+6ea83G9p203aQgp9Z9BwIkyORZIOh73iVPBHKyIjw+PbEMiwF1TC7z5t8BvKtSx/TDjdqAEbi1sN4auunBy2K87RhKZdpoxDsskwyPX4CwHEvbxMWql2MMorm6ehHLqNgXfB1YwO8fkrHgz0AgTrdhtXECtu62A76bv/80QY3lwgawbxeVJg/Ml1HU0CprB0IqgLeNY5HKzOHVieGKV3AeNVQz78I++67rxHAbt4D/zCgwBI8DRqSczaGiCf2NW8WrP7PyDEo+jk2DMVx7RbJIM/HV/gDl4Y76lsEVzY6OxwCZj6BsPDHUMu0qc0fGI1tvbZbSCVxuf+SChjxFguZLYsIwXZUPL//EKqpQ+FiIJEcFMZjhllsnOxYuRSpxwQ1jxtGkq0aqSXtyfXtRUpNjIvHXyWpdnHpx5AgElrm9xRGDQo6f5bX9oOnUWpqnXlH1AGhURBI6h3ffa85t45i1MtLSpB92lTj5NK85VItotTfgfgrv8+GclNZq2nYrksv3vYQOICyK6zedyzVSF6RTUkVbmbMckx1T9FccF4hlVhn97zLR9WIZ+HxXuaRx8hLA6HxKCXCwSZCAmdP20bEaJUJD+IWGR5npIHImDiuiiIsn9/L6+Sptsj+tYJIIVyXZytb/olQVUdKTbpbeghrMP0yxT9R5c+KSHKlKM5/dsWIHWLIAejM/dxm/1udKVllEXBdaYKrDDMhXjqD60QFpvYJxiYZOzzccdlT0M8VjACGhazkxTjvVYI+xnc9A7vE2eGOLyXW+2TE2THew40dk+j0FCAMYfKFJG7bva7fX2bIBe9ixxKJotSfH8iFhDgyd+F4BZDszqyX2Q7cfqhRjzY5IBfGM2ahwWRIECThyzQUNIrLSaeRxnzIgFnfvrOqw0njtV0kGWRZfcklybd37FSp9kK4sFUDKyXRaHxDs7cq3fwht3uhPWF5zCXmabOtT8rQ73x5lmcqTFUGgpQZG2pA8AusNQRo3X+bozYtUyKmbLyjClmSvRusk/eLs/I8pbGV2V4bdANtY/t3WvhpiGHAg/mcxGL3L0ktxq7Tnr5pb6E1RjuyYcVttG+yNAwOoCaISBXN2PzMFdJ8Rps8iIVCOfwQ60Ij87yFKL0S6u3Gkd7wM6myr0iawJZ2h4iTDq8SjNF4g2Ph6zv9WNhYlpy6pPoSKlsuoOQRUoDijQCqVhPXvpc6n3fo2EKOlFyz7cvJzvKihsC3bryrB6hfF8G08hRiX0QrsVZMi8Bb4FGLrRleVwZ0aDHaWf857JJfftuoTYa2k9kOw+W3EaOV31kUfRf0h6ULXWWvuMnJ79lzRMsxj4Mb4iPBnV+ZLR4tf+UCWW+Qj3pAMUOC1UhEe2WX6XxLW69kMoJwkpp2JsYgIY+4D+PqDWrRszSzdpZqhOk8SksyKhaWd67Vm5il3lrTpUJWjAB0jz+livVmNE2/WppNHS8O/POav/jBu00ChpUH118wWWKV1nswmHbnLx3/YS+cSer0NH918hJYeIWGjNmIvEuWeAx8bLIVfwClVDpuiDg+6UwfDCWFJmhhVWKTaoBhhZp5IuWRzYNixaAvfvmc7HZF9OrNVfE6wvFUGtvQXnIq0f1wOth8/2AAQs+9PHdRJPBtuDk8MRc/IcATdNl2p+CGb+1u3KRll0OJRgPPuHzIACXmlet2y6Ozqz1whDJgdgwwAZYACtkanNTmeLZAAYswu18s9ZXkBvrSJesvV2ysrqrp1yb7dbFWPn3NQCFt4hCd7DvnXqjmcgZs01j8f1Rs57vbRLc5VoqBkPbdxhbmWVs6MuKkanyfSczyOKx/ma+mTJmfwwQQdoYODKT6wnA0s65mptgf1pFFCQpUYT0xwdUsaeFrPLtG3Sxt+IWzS0VbMoc3Ahoj3nrWW8ISpix0dn0Qk9f5+O3ChVx+ERVEiUXaWpLCnewejok1PkagTxMUxTKB41BZZQWj1GLRlbbxnnhoAitpJXviAed6WCmRwt5L6hh8iVpi5qcmVlpdhpyL1oZtoVGLwM5r6MDJgR0bpNOjFeWA05LsTcITcpxw5D0/46VAVOLv0XXHM+aFm8yeRuDqsSI8xPLB8WHUzjCwR5JewaTTtdouFs8Ikkefh7Drd+Ut6uZ2jyEXAfXYEMFUIFO21laUEVjBD/QRIfcSiq0c4By8dzzNgUsbxd/Bi6+kQl6xdB3+6ryy0+cxKURZU/8F+0YiwBcn2Lid/gu03byj+Ef/lymvYyJd77vE0n1cpk6UwMfjXEn0FqF8z1ts0kC9YaJF6aQRUCaOhzn5nR1lNYsJIoe9fbpHeKHNfBCGMladnsUAw8n5QIcy/BBJstRkHyuXz2+wLYvTG9N8D47/2FAkhPGOQEMLAA2rFnDhjV7HLZHA0qayjjACTe6RPT0eOg5jHJ+jtNikz96Zjlw59BsIvBQSqghPibMEEJFNVoX7WBIvUsD5BHS+EiY5wRMAx2amnLbCzjbb92Iduf+uQZ2kIQ4rRPRfyKGUgHQ/alDktUwkzRzoXaSsnE6gERdb53iov+c0k935+2mr+bcB62F2zeRljMjsvuYhwKcMNxjKGzJni+73rToZK5hPxmaiUP8JRnHjj6FOlsFAQwV7Ib6XS6R0V2F1NGlFXrbsXMBYm2aJ0+Zt5Tyg8PNu2IRGzo25yztaju0Jca845HFIMSwlcM3i10GvjWx5bsdrvWzeDfDktdUMQqAu+JAD22K8T3+q0OR6OllMqlyVT39VAK+c70XObN35+7M2Aft3LVMSbOE7k3rEwOnxLsWlq+uzj4Ou4kubUP+DbuIIOEpyp4YNc7H4+fnZ4dXwEvjjMlSzHxDDW7p4L8By+hCUglDl2OUHk7dUvyGNTm2Rxyv0fG5Bk8Va14IHy4p49duF0dfdPsyKPJovwKXDZIZQw2GyxzBroMOnsdvviFd8qflt4+S9pcIktVY+0m3xqALXM0YUx8e8yN6nYOm8NV6KOMiC1WIy9ldNY5mLG5gu+gsDTQNVBhcOi7nle0qPHgGU7pkhQEKCBqdP4NWS9mLi4viukL/6b+W4btalA7DEMXrczyeHRR+pshkKTPbwWScNe8FMZkcEnX2cEboQGRoSvGDgzrjefSSNvsrULXTS/i9Y22Rc4Td/jlg84GAdlem+sUBxIsSPGlddOGTy0wBfXJclqaWLUfshjGX7NsNxSgiEdUyNQ0vSqA826f12QmeoajI4JXyQ/JCedU2/XPMMrrzj7uk8fe8Dg9w2x0IWtgGM3zukLhkAwOrEz/qKunRjKouG/9/e0LC5OwGYjPjWLjDg9N0V3S61Ilsd1z3QblElzvn6zU9X1enBbGAeNOwgXy0VYBO4H8u9it1+cFxJQgTcyik8Z7/xIfwD5sIVDEb3IopmdpT12XBGIreFefoiGjCavHbn+bHh5q3nLnVtOZr64H988txdQA7+njt/xeSrvrvdMyPkdY8jI2HDHn1EqFJPZUxVTT6i/KpKtgMJ+vvkRsC52hsuhiTrFDO1breo+m8Sz7u9oYbiZq9sD4B89hcb0dnkFFnyKr8EUaPN4dbH6YRK11Gy3UwiWEoUJtys3nKMTVm3gI8SsV5lV/dft8fYA9sNicX6UeYFERfCSHIRHSIndkCQEUbHNIFZbCnECFI247nfyfG8Qd4HJBD6phSr3d1iS0qdXSJeNYaKpysEiy09EQIs6Q03y3Kjce61EboMMxNTm2UxLo9742qDRbF21FFQkVwYyxstJkd7b0TVXWSJ+eNEMEfkx+TdgUudBbP5EPrlIjHDqGAIJUj2zXnRVyf8NsWNLTsNkRu0UOfHWDV2K06dECa9hHXfIu1AkBwQH0i3g5WqQPBIKmBj5U73IQaqxqnFwmip6p5xZFNzrHp7zFd18bYVyQoMKBXvyrgffPPPJNtlptFij1V0hq80F+1rrtiKAEQYUi2pT6nKw+tYpLIJ9+CEKxpBX4NAs/51IbIvqwPGeKMj5nRg8Jb/0nRxENJ5K0/bqV9HyM9VWS6l9UThWIqLN7Oye7nTPC+Jbwmyt6l9ydvZjoZDH0Q4KQ6e1sKlLod1pl9PS1cU3ZBq9QYYGa29xJK8nxrbJoWne3m11/xqDCcjZvkh2Kohi91DMUvOLxVTlUvKw3Gksgn82E
*/