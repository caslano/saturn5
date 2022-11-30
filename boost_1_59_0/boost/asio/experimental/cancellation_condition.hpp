//
// experimental/cancellation_condition.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_CANCELLATION_CONDITION_HPP
#define BOOST_ASIO_EXPERIMENTAL_CANCELLATION_CONDITION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <exception>
#include <boost/asio/cancellation_type.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {

/// Wait for all operations to complete.
class wait_for_all
{
public:
  template <typename... Args>
  BOOST_ASIO_CONSTEXPR cancellation_type_t operator()(
      Args&&...) const BOOST_ASIO_NOEXCEPT
  {
    return cancellation_type::none;
  }
};

/// Wait until an operation completes, then cancel the others.
class wait_for_one
{
public:
  BOOST_ASIO_CONSTEXPR explicit wait_for_one(
      cancellation_type_t cancel_type = cancellation_type::all)
    : cancel_type_(cancel_type)
  {
  }

  template <typename... Args>
  BOOST_ASIO_CONSTEXPR cancellation_type_t operator()(
      Args&&...) const BOOST_ASIO_NOEXCEPT
  {
    return cancel_type_;
  }

private:
  cancellation_type_t cancel_type_;
};

/// Wait until an operation completes without an error, then cancel the others.
/**
 * If no operation completes without an error, waits for completion of all
 * operations.
 */
class wait_for_one_success
{
public:
  BOOST_ASIO_CONSTEXPR explicit wait_for_one_success(
      cancellation_type_t cancel_type = cancellation_type::all)
    : cancel_type_(cancel_type)
  {
  }

  BOOST_ASIO_CONSTEXPR cancellation_type_t
  operator()() const BOOST_ASIO_NOEXCEPT
  {
    return cancel_type_;
  }

  template <typename E, typename... Args>
  BOOST_ASIO_CONSTEXPR typename constraint<
    !is_same<typename decay<E>::type, boost::system::error_code>::value
      && !is_same<typename decay<E>::type, std::exception_ptr>::value,
    cancellation_type_t
  >::type operator()(const E&, Args&&...) const BOOST_ASIO_NOEXCEPT
  {
    return cancel_type_;
  }

  template <typename E, typename... Args>
  BOOST_ASIO_CONSTEXPR typename constraint<
      is_same<typename decay<E>::type, boost::system::error_code>::value
        || is_same<typename decay<E>::type, std::exception_ptr>::value,
      cancellation_type_t
  >::type operator()(const E& e, Args&&...) const BOOST_ASIO_NOEXCEPT
  {
    return !!e ? cancellation_type::none : cancel_type_;
  }

private:
  cancellation_type_t cancel_type_;
};

/// Wait until an operation completes with an error, then cancel the others.
/**
 * If no operation completes with an error, waits for completion of all
 * operations.
 */
class wait_for_one_error
{
public:
  BOOST_ASIO_CONSTEXPR explicit wait_for_one_error(
      cancellation_type_t cancel_type = cancellation_type::all)
    : cancel_type_(cancel_type)
  {
  }

  BOOST_ASIO_CONSTEXPR cancellation_type_t
  operator()() const BOOST_ASIO_NOEXCEPT
  {
    return cancellation_type::none;
  }

  template <typename E, typename... Args>
  BOOST_ASIO_CONSTEXPR typename constraint<
    !is_same<typename decay<E>::type, boost::system::error_code>::value
      && !is_same<typename decay<E>::type, std::exception_ptr>::value,
    cancellation_type_t
  >::type operator()(const E&, Args&&...) const BOOST_ASIO_NOEXCEPT
  {
    return cancellation_type::none;
  }

  template <typename E, typename... Args>
  BOOST_ASIO_CONSTEXPR typename constraint<
      is_same<typename decay<E>::type, boost::system::error_code>::value
        || is_same<typename decay<E>::type, std::exception_ptr>::value,
      cancellation_type_t
  >::type operator()(const E& e, Args&&...) const BOOST_ASIO_NOEXCEPT
  {
    return !!e ? cancel_type_ : cancellation_type::none;
  }

private:
  cancellation_type_t cancel_type_;
};

} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_CANCELLATION_CONDITION_HPP

/* cancellation_condition.hpp
X9NJxDKX7AgLLV1XVmv/mYv0B1Ve/K1JP5/RcGT/Qje+YRrEonH41/gn3u81xuumT0tsYA/+L1J9N+GDN/2eUDaE/aOxxnJ+cyzzwQK4zVMEnxaFP7sxUX75bSPQWcBu2rv6rk9p+Y1u30mA/UBAYLYQ1pfwc4f7R4/iqHZuV7QG6ihwHrFosM8Q79fjQsN/aRR7V7vjAMxv2zgOEUtawg+knlHUoKHvViqKieHOpP1a4m7enxIy3859IoaZ5LOFumz7pDeUgfd9x8GSLqutv6nMTD4LGdvK6ya3oX1+H+l/qzV8e37z7SwP60tRmNCABMIyAgK1Np7AvyuD+SC27Sfo0qxVMjuf1//KEWa6qlPnQPvawlIw6D3Xpxj/fPT84OwrQm2fru/B/t2Yjmj1XjiI/nJrprqn4GGItH9rhbELH5dQn+Eh81OPHo0+WUVwycbFK6GkfW7BsZBPVQyf8X5u+NLNtftolWYSaN2ISjidX/M5O/LQxO0J72AWmIzUDWzpZO6UG/+wcmqh0LUbQouxUNHnHfFLfiIO9DkkIRjz/md/QUYU1Zg77rawQdxRlp7vK/7NPebc35nU3lsXuhjj4katBrsagzNvcIHOAS7az36JdAxWkxvGYm+cKGIf+TDPFF1bdlwPZJWTOYyW6x6MmSCkNm4TWszwZMlY96F9fQ/GKTrP4lYWt8JP+DFJRTMwf6EI0QXohIM1TSFJPSzILDzkyyVeC9Uhqx11hzO3fjZP+FLOpKrf5SG+AYEGmOggApk24yUqPoEnzHdvN5m/HM5nqG62HXygCG3+uC6pqAXFiaR9GvEyUuyfvKFE+yBxrv7xXunYVimFKAxpmTCNNXNsEOcdte+a/LlNX+k8ht1vstAEDk3rwNjzB6e6favfWIgQ31tWVseMUFB/IRYVMgjJamDV+75PuUgiyWJ3qKdrXiV+VL4WzGyhuruXZvHprwN3w4/J1msDjc06Ep/sfCbrDOe3w0XwyhuxrRGc6bP9ltJ7VzzLYYrDGO71DR8Z/+fwLTCUFcf4J4GQVp/KusdsNjDFyXbP7ys939pwbfQnOXZsWO6J/UjH/VzeSF+9EHzy/MGGe658/ruAUDDMlD5rpYeXBvPsni/3x7IUUW77Ws88WYIPtgeKzStoMFgAqAVvr9e6eYlxhlWzBi/CSZLiRUaZe5sYm5q7YkGm1H/TgMUhyAv1H21V+IH9QMC0vyl/WqkbXgh+XkdE39VyJNo7/wInFdcqp7+iB7Owo7U3/LcYAavE20uG6u6NM7yAstBFE2bIXOZuhkX0O3EiKj6l+mRFG9itfmjGCs2B8p4C/ioDeIAXMkXfbBux4fwkuKWqLy+gVsppPsB4C21+agHSZqVxM4CThNlYFKYA6man8PSkzLfCcWuGBBm5ZXEJRjazXqi++iupxjPIDM4Gka8amJJJXKjwtCTUhsWHA9qmLNtKBjy0J82zgBx6mrNbELQIb9ModR5fevS/5PhiS+xso+zWOkkcR3mGG5X5MZb/RvH5G15szGOexqWA3pD+Voi9N/6fB3655UKPatVQZ6MQr384lhXMDy6oTin39viz5bLj1YDgdSps4EQDBxZ6aIrfylRs/mnyHdhhMN/YdXKMnItHa9QikRleS+xzGO1n+GUf3tcHPO12koVhfRr5Vmx9X+d005cdYr2tTWSrnYfhIpXhT+WTvQEujs8is85fBe1zc15Ro1sq1Ul+al0ZNtggHw5qqnsZX4/RHzuBRkHrTAIZae5a+oXIMFP4fVlUo0xyoXfwkP/ymS5OqOo9wf5M4pbNb3cLgXoaKIikxB7B0LrrbzkAx0FLF/TmUQi8ZPIQ/1+Cd8zS8/l4R47itRwEPCQhfeGaeb/3VZpptlu2s6be00LOt+N3hd7X+VPgYR0qvp+6QBljFv57mJwn8efJbhCGrvqL7EPeCTODmORB4htIgUpnl4XYKV6LWIUEYc1XrE8av0FdlGCfEOxM40VL91OV7ZujhsTmsrwWHTKv25woxlQNXJXsSr31AL9o0h0NDA6iwD1mjut+GGyTyZlHHIjTsUW3dYdWiGu1cjaiER9kmDHvd1ty1CCxME8kWCLGjFuxwesDeoHCf0v4UJuI7OmgWTh5Cus/4eAl++z5S2jLMVs6zoYw9D4ZK1TdiX5EtCD0qvsLJDOjQQKl2Rbdc9wjp9i00yuSqoL+9f+BMjVyBrEgslgFwto/hodTHb+I9c2pEZCRDZXbS3OUw5fA+EwylXAu6l7MC6WebM69T/Cx18zG6cqEhdl6Zyp0PQE+IQn6s2gh/lMarDbRuGUL066W3L1U26xWN848L3+BRFfz1TLsX9Ho1+przBGDRqe+QMynVCI7Nc3/8xmpRYNomC2P1BlibVdweCf7JVTAdHmxtmxM2LZRaD+04w0ObvXHFhC5uj/jIlTjdfV3qj42nQE1QtacRv+saUV3otMoyfH6a/1BXXk0N8q3GhBob6ZywfGPJb0b8+Vf2xTRoKs1Vk5yAdK8fj52EH7c8AJIvT5aiXaNt5l2ePjnGRVu/gm7ZeXJjren1vvz18h2kIGzhWB39yM3QY5vbQ6m7MF3ffkYD+EfMLGevwaqVvX3sGAwm5Pk/gXk0XLpO9cL2DPt1LD8dhzS1oCZh84W41giYNa1HyPbS7ShPlSftVtXh5+meU4IFG6RO3iyvGA2w6XlJ9OYWLOy0AcAt2R4wGffmS7dR7JMlyL07bNHbh3qd9fB5ylpIrorcjnP4ey8DjOwN9qF4LdDI46XMu1BLH5tFUXgJ1u0PoXSnBJh2NFqb7oFR4kI9Ov9JVKHWV8EpogMrrN9eAXn79pzHfmlG8PHK1dKCjNGL9fciHcGB79OBgZh9Zs7y/28DGsniYNlGsIiq68K7iwkzUW8JdWlswQrx3mgAx5xSgx/fvX2KRLpV3g/OTHaUOs9JJrSMmdm95I8XaX9IdSWP4f4JANj9Rcnf8iTe8yyB0KPb2ze0Zmzgzos7PTSEAMzugonWx+RSglNvjXFiaj3afQxLswjGw2HJz0qp+xivLXYCd6h6UKSCi0Lx5Lnn22MntehArJQh5rO+3Gw8sXUqpZtd2bgonl0xDs7DCy6PeOdt2mXfi/xbQo7z4fbewYeWvlNcDLrSIoTOV6n65bTHymuFOETTg1nOgfp9dH6El43QQOgID/gITmG8f+WyZi/PmTld1ZhzK5+n8n5aJYGhMK47UkSRK8cfj83Xygkuh3yUwKI+HXunY4wum+DWsqZc046lwslEobNgiziaWyIUFoq+7FtTP7LbWvQaDAxNs1yUsXTZoVPtn1gVAdA8IzRsEvPcptbt98Ne7s5xvtwd47/geqpv81n/MQLnrQDAd5kotzXzeKGcG0zH+vJbi7la0ThMee4gEi0iabv+bSPrmWh4tf1sF4xD1QcLCb51iEwHCpaLPwSK191K78sz/k8pHhYONKDCWa1DiR+r4vxov14HeHHfxY0Q3U5cDyza7nmSAcC5T850C1EcSzajr119jZeNMaCpDsgCPkVs8rgnBKEgj4StWWnsyWs/lwMDrPzbKsA0fKF0VTyVcXQiAQOLf9oIy/1jyrlBGXZn81CFEqlcFlznOUCB4Z3PlXZ8GqgfVaD1t+P8H/fDTTxM5Uh+NFi7muaiSr/3V5D8L4NiPwZZhff5JT/aAMyt304H76nN55mWaRqdrPTfIp4G2Km2T94rQoeOYvNAjK+VR8ezUhJpPpW/+a4/df1ouym05ntl1vgVDIT4Iy1n24JuqUINN+SUYjdNHhcHFEbVSeCEJBoc/fbHipzBHUc+V7REKzWPv394jjcaIbvnQ/T3CE+i17bD9lqN9tbGaE+XX2bWx0GSnxZrtE4Y+FJyxTRCxIuS5+4NZQ3nfea7OAQvGFAiD2xn4rEkc88R4lK/XdIx9HHCiIH9/LgFyAUDmw7nvJuzJXtgK2wA/S7inOCh3EHBCgBylEJiqxHVZVXYp2ehnuPf2HWVycZoqQCSLKKa5bTMhRO+I3XjYewO/aoDTNHriAKyBDcNpVkV/i43Ko+VgqQ5h9cCobNs1g3apw/EbBxNAyEm3cRobcyfz3UtCMVlq0Di4I74eCzRrSKE7oQzGqMihyPRoBHOuZft7zxmX3lmWQWd/KzSX0DswMrztLUR6JOfjPL4NB6mxyEFe3+Op8+CGYV34zlYQjnG7RYDlUZqGBNvliGWpf0FrXTiebkqWa4d4rZS5GmFfsTxn9Pjv/zXCiaalsisMnuZt1ChSqsAQsfXS1Fgc/K+Sjk5aA93Gf/0mb7R3xIk+3jpsenQuJ96CcyMtCzNXChBKfDtL49qHaLE50U6uD+2Uj5IVZ+oM6txh6ofbV+PqhI8LVhDu7xCmgPhCnxInrDZsZYkG+LXeVQCCt8f49A688My5X+X8TBRavCG59+vwHe59UCRRU4aaVDBM5Gz4y7m4Z1shwEkifcHRROaA/4Xi5Eku+isRAwAco8erAD6Dy1Wcp3l02sdlGbepxhm5xWIKm/KjCLJsgRwGn0dNU9aWaAALAWuokZE05xAADm/L9cgGEcy1rBL5Z96s8DzsSrae6bSg84cMrzNDL48flJ9eTBBhwLDa27LXAmyksx3PMxRZqV+9oZhSFMVPkXzEYoq7yfG1dpqbYYZPIjXrldVx+smSVwQkjBnThcmthPPahuuYTrMk30zOPgMJxpaH1NcgHsh8uGGfiW+zsXGMhtABObeG7lyoXUqGUUuU0yq9z4PYKOGiui8JqiUlG0efrrL5kb01K6+iErLByA/MSO9f4ueTdfBXyOuE3DFLtdcpD1CoKFfutKLl0rmhgF3asHK/nhzVzs26eQSZPvEjThogahW52AfTF2vhxGsIxqCi+JNSNHPg6G5pAZGylsx2olcRTOKCETGClsT+NGTlXVGL9vmeGuWwsfhrVJJenUvgpUjabL/lr/ivWfMJw3zTsjjRLriWyMUQj+177L3QCEasVJxBD3jeJ6CMRztuMLBjb0CrxW/XdQv4J515y9RwFYGktjk1XYun0h7++HHJ9qAftqbLPMYxKUJ4bihsJWo31wh4P5XsyFVLlsrRZP05zvx5KB4SSc8UVCpice43YBZikMqEqVjiumGIY3HEIqyPmTzkeQp4gLGxdpuxHmhnpho7bia87tRvOF/tikC1dNLFkFjj++mXnJDAwkTQ8J6TY8hT296vQ/QYqrahYotzUqR3WawKB7p+rjJsjbGha1bUrF0lgVYx/r7hkxJRMj7Qbmr6uqaJXbqmnL4PX/rbR5Gi4AMudR4iBFrd2Vi2GWgaBoAl6JRTOejTt610IWFfeL4+NgNDvw4zFCmSCawaPhFqiFlYGD5x8A4SCoYZrhPE416of7tMs2tp7oZU2m2J2F45xo5P5m3HGivCT3O5Dhin98Yc42V9/O6Si2G8/OAPJSfyasjqX3VdcympSDRPyQ+PXhyDbruFXPsUZoF9BOlIep9EBVAAj6Fe5sEcAMAMZOHB6MatpITEK4B5D6GtPNQaXn1ocfPYIHJA0Y1/psO2D/xl0ZWjz7xF1YjPK8FR7LAw8C2jVV+jSakA9n+GoN02OgMt1KbMeXn5i1B8VU38r4WP0vfgEbj+Ff7FQXXne5kL/wL55MgKxgE6CF6TqbmWW2Vd+bn4r6e/2PF7IUVRoBoKNwOBjDEWnC3VgLtNPh5DnJKvm1y2jcN3utD1dn4OB9ACLbqpHqCrYlM3ZpuOgfe846ihzhlvwra4mMm3X1B9FHiXzcfMo+pkjPLKlG8iXlw062OnQUrvpxSeO1ihzV/JVoPUWDSjOfOl8yrhs7Do8Axb94MtsIKOKyyb4rxqNFRbtpXAFsTFcylbiq6GY0wUx0H4KeCDX8ENCSMsLzq8XWrh9zr88RB7vNZLgHph0BplM71gutl2Xc1Xraph15xsmPdtrWC/yPs8IsX1GizUuqWm2QSWUXxpJeRvoA+C+YXuQx5+5uRp0yxm/zZ2WZYR/VXwmZoftJB1pbEUOpzCyVIermfWwMGnKEb6kCdfxwlQ7qSo9Je6xsknqwiepMlerFVDP1pl5gWMG62BSmLuZQK1EIbJzjpQOZ0aaROVfRVNerrZtMQ3haNFze1R1bxea4nwqaT8NYPuFjU8lTwwd2bZfF9JgTgVyGW0axIfeaY/xxZ92booMJO0PYxdmVb8PCxwv0V0CkYvbY9l0yvq4h2F1yetjRCzuUk7PRrtY2yDSwlfKRzpHOLgPjK0UpuuOvbdWHqs88jJy0xYdXph1G4dzs9DbSdhwNTIT7rZ1MbyGrIPCchL75SW2i2vTnvn7YqODBfX39waolyWbVd6HX6t6Ke3KjNwnrnx+Kk38JrZ+bwQ3nh5ITV0LPBff7/1K9apzLbOcRrfBR+gaDJTjveL1gWQQyctjF+OczPpNHJ4Hz8bT8bVXW0msy9hXVa63DRlHXuJO5a8TB5t/AW0AkOhkxDkpue+i/O+j54gQGZqyltO0gr4bw3cXybn7EVB/7kbiumKcKHmri7FGtsStPtrX5y3HT6cjreyhBdq9kc4/ONoxT+KnUJM1p0rLlnFEexjOijB2s4zsIYAqKQqM3XKtP6DGffXnuq6f+jWDUXSfUtzpjfN0KOA7I2Sp+fmBJtDF65Yf7R0UveOnbzZ6TIx9o7JWsU3jBwa0Be7rCjmg0yu/WnnnJZ21HP0RP2HqqNXdNxNsgdzdAhf6PrBxrAl1jP2jy/ZsiJ+XLszgOXAmubysxUrMVAHgt1PFky0oztHpL7KBfE//ILPb3NTbgbtK6mw+nqqSpf4lXEtduTf71l8PxH1zEP3q/GQJvYRlXJy8S7d5g4Sl9e9tHfJkTgUlftj1ukJ8qY85JWilCaXoiUJ8NnrDpvhosaY5OfpAhDFtpOyYjV4lUdYsa5518AXfYQPouqBYHURzZpURBjiaaXgFIsbMZrWJ2NvN0uYdJKPyAAyjyiXHsipeIcGJmnvq94QdZ4F5PpXTgAPtdCExYeIABjQCtESeZL22N36kL8PBKo9DS04yhB0BCq6bfwWrVKTXRh37u6ST/73Xjguw6YvY6AiVgUJ9JXFoiwsOJkYrSIlwXGhbIo+3bWt+vGwMBIh80OwM0HaapZi5pT1mX+xZCCoTpu2GVGL+gHCKMpsxgBfufDdEc8asTrsYywgkuL656hgeToZxKbGa4noLJA0TWKzBJi+34SNayIKBBArL7u4JClK6ZOInzpYYwyjFYGa/lMyN27qJdPD1rj+ZARgFk9LnSSPLqV1wi4T30l46Bhp3OESVmsPxU2QUAxEqPJObaXtNCoGHf3MtWIxhM1+gQhVY46M1zKvwV3WGjd1RnMJ7EY2vfvL3FEbYZSO9XhOIzoELheXR5E2jYGhTAMyqgOaQqWNvon8FtjP23HYFUOCP7tQosaq8hDOF9ZQTnJkAJHDJggDeoTNBg3FzrCojuX0iA06T/6PoqRT/0FdCfZuqp0Yu5+jswaIUc71TUa+rZ7/cVYoX0Nte1d2XiN6Kfvtp+Hu2kUmNKfTI77srjLEzsKjapvK9+OjC4N5O8IYfBFjMV5ugIYSiVwO6ary9w8KI97eFxho23dglUcmrKvm6VK/887sHGVrlYhacH
*/