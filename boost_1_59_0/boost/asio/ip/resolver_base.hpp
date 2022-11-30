//
// ip/resolver_base.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_RESOLVER_BASE_HPP
#define BOOST_ASIO_IP_RESOLVER_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// The resolver_base class is used as a base for the basic_resolver class
/// templates to provide a common place to define the flag constants.
class resolver_base
{
public:
#if defined(GENERATING_DOCUMENTATION)
  /// A bitmask type (C++ Std [lib.bitmask.types]).
  typedef unspecified flags;

  /// Determine the canonical name of the host specified in the query.
  static const flags canonical_name = implementation_defined;

  /// Indicate that returned endpoint is intended for use as a locally bound
  /// socket endpoint.
  static const flags passive = implementation_defined;

  /// Host name should be treated as a numeric string defining an IPv4 or IPv6
  /// address and no name resolution should be attempted.
  static const flags numeric_host = implementation_defined;

  /// Service name should be treated as a numeric string defining a port number
  /// and no name resolution should be attempted.
  static const flags numeric_service = implementation_defined;

  /// If the query protocol family is specified as IPv6, return IPv4-mapped
  /// IPv6 addresses on finding no IPv6 addresses.
  static const flags v4_mapped = implementation_defined;

  /// If used with v4_mapped, return all matching IPv6 and IPv4 addresses.
  static const flags all_matching = implementation_defined;

  /// Only return IPv4 addresses if a non-loopback IPv4 address is configured
  /// for the system. Only return IPv6 addresses if a non-loopback IPv6 address
  /// is configured for the system.
  static const flags address_configured = implementation_defined;
#else
  enum flags
  {
    canonical_name = BOOST_ASIO_OS_DEF(AI_CANONNAME),
    passive = BOOST_ASIO_OS_DEF(AI_PASSIVE),
    numeric_host = BOOST_ASIO_OS_DEF(AI_NUMERICHOST),
    numeric_service = BOOST_ASIO_OS_DEF(AI_NUMERICSERV),
    v4_mapped = BOOST_ASIO_OS_DEF(AI_V4MAPPED),
    all_matching = BOOST_ASIO_OS_DEF(AI_ALL),
    address_configured = BOOST_ASIO_OS_DEF(AI_ADDRCONFIG)
  };

  // Implement bitmask operations as shown in C++ Std [lib.bitmask.types].

  friend flags operator&(flags x, flags y)
  {
    return static_cast<flags>(
        static_cast<unsigned int>(x) & static_cast<unsigned int>(y));
  }

  friend flags operator|(flags x, flags y)
  {
    return static_cast<flags>(
        static_cast<unsigned int>(x) | static_cast<unsigned int>(y));
  }

  friend flags operator^(flags x, flags y)
  {
    return static_cast<flags>(
        static_cast<unsigned int>(x) ^ static_cast<unsigned int>(y));
  }

  friend flags operator~(flags x)
  {
    return static_cast<flags>(~static_cast<unsigned int>(x));
  }

  friend flags& operator&=(flags& x, flags y)
  {
    x = x & y;
    return x;
  }

  friend flags& operator|=(flags& x, flags y)
  {
    x = x | y;
    return x;
  }

  friend flags& operator^=(flags& x, flags y)
  {
    x = x ^ y;
    return x;
  }
#endif

protected:
  /// Protected destructor to prevent deletion through this type.
  ~resolver_base()
  {
  }
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_RESOLVER_BASE_HPP

/* resolver_base.hpp
CypaWGwU5ErKp8Ml7P6t/OCNn9hODCTspCo95icA9VVpyxYdeYSH2yzVKctlz5aSc45M6y2dhO5dISFybA7vrsbCxSrD050Xu7SNTtnL9YCbJnDgD4OUdmE/v7OLejXqx4jUKZEVlNzPEnTuwjub4hXdsjPmm99JB1Y/A5lo9jha67LT7Bfls3/nntC4H0pJwlS7uZQxq+QKmskc8UmeT//u8bM2A8E90sIRBiBl6mzVAuMPX6SLYq1z2rLEg00qCIRMjkB7Dx/uRBZUkULJoKKpMag8LzAXEsNZ2Pj7eqJHqj/glzSVM0PEY67AiLyq6qQJFBjjF5X2Euvx+97JBeXrdQvEH8sz5NZ3mpu5jIzrG3mcgRRObG6vQSED7LMRjaxt4B2um3D5kqCq/dkAFhocWv1E+dRoAzWR1OhcPm81LtJuCwyqWoskzAmaLFPEBEyFtJNTQSuZT4cKOO7reibSR5hifBxH02Xs+ifEbHzbu3qoH5dNnHKbFjaju3Dl9nszxAqtamzsRXYRr6kmvtrKN/JmDnNT9dAdGKvR7a6XlilgSlogACuoWEtoK/r9Gxi4qHoMtupIM9/3K8FIaWIpRyvMyb4aTq+yAMJ3JHJF/QdxzL7XT2tD0ctrXKmYso9BWQpZf2fmz1T4lrWVlUHwq+Z9WA8CUgcb2Qqm6MPdTckhWuDHAx0dkeyyu9zZBqtbJ0G1QMUT3u3toBMMpZcBRaRhIZ4gJDwWa5Fd6ySuCKlUOX8fJsGrFc4GxnaFb9R3ArZcCBVCP+JyBEvvr3xuiwRFBZcqYcJpOl8WkcPLdI2LZegr3OwxLfATO7iaoGbl4j0ca8SxcNpUikXVgqg8HlKRFYLsU8nWIFfGqV615xgiGItpJU7GkkQKIRw+WifJ4288QVllGvF8lrHfDIxxuzWCtxl5oSxXcP/JZLTp67p1iAz3VNGiQtizc6vUwdfhMyWDWHt//DvYtSHcls8Ienr+XOhDAZIAR8RHi8QeopfjppO+zKt7anqjQYY1aokyq/P4xCK8WSTjstkYBqzEYfP2pE8WlSO4XBceRSI+QeriKwtxMZCb9sKIe9RQJ7A4ECzweZz70e9oIHGcSvNPqB51yszyDWKD7YbVOUPVw2VHgnudQry+jMNqw1+fzpYCDHnlsEQeFL0cIyVklpmgp6ritBKPSV8tfwgjgjShcpAO14JyYKf2SKtpU3+147EEIYE38nMiL/07QKUyMhWyAUjnbDBHBLCfSS9woHkgWQhGOSD139cldYukzGAntPb59wIEtnvmJ+HCyImgbvQh7uB+umaT+BNNV+cTsm1/hyCEaK+Hk0nipIyFPkM8D/Q76oI0JHE99fTYgl+NdXjgL1rlWUfsvYIP0sdSCEDRvmpixJgcC8oXEEmByEGdhjVm8I1miJNCQwC1i/op/kDO82zJ8oAkoE5OUKnwPyCXG4y8AUjxI7PMfskAiB5aNkS8ipF9PufwhumUph3G16Q94Z5N9Zf3GcseWckzci57JQhKVgZqxQglJcD39qBuB123FYpjQ+lDdd4W75mPwc4CRXpioA3hTi4hpmLhcJCeG97l/XJEvTi3G1s/8+Q7VP44GgBrUbICAWYkCPJsdZ8NGAwgOjqK8vF6NPnkGMqW+lX/DiIFImPFQSa40Or953PvslLMIKRplDzUXiBEK/Q43AEcC0Ee/gVVbyr/AwKf2XFJIXEe/g5MHGnTxMzKPH+V2wM7p6VjX7u9ECEAbtjvG4pH9q1XvTvWagOVQatgiX22rJl0D5Df57XrOadFsQ1nMKcpFallbTtKdLqao2WIsGmFCJW+l4MZ2o/84NK7ZXL1VN5Mj6mlhpftC+sXryCgwVUWK1QaRkJke4AhXqnF7502gGKZ63cBDPtROjaJihD32WTzkmvo8KuzotjhYAEvYhq9qdsEZ7qq/DxmafGH70h+XcijHnxK9iF3ncSAtux1KDZBndVJPrm1crQ76h6sb90UZ1ZWvNdbn6mmq8t9uVp++p4HZrwGQp0YOAsvjz8mboWdjlB0TmncpinfzgpAGOGJv+gGUUIIzudc+7gLbZR9olhhI+2BUJeFKcqlITH5jAorO9E72acd9BS+Y9YQYiTHlNBCLZwnP4zekq1fxkFOWbfoYH1lep5wZV93DNc5XSgtABEs7tN9oF/CVOysa8Re73ClUuoCMcby0kLq9/0Cv7c2T7pPlFpvxTXYITcbDGnP0RtC66/wsncElAcw9WKX3rCLKwGtDkrTy1PTl9P1ertLh2ibdguuH9duZ1qcW6KbTrMcrGb32OuB4D17zoN6h1AjcjVnfU8JHFiHp3dDQssmB+e7ibK88Z3ShrmdqdyKm/R6Ij2oJAl3vb65O5PliYmhn4VOc3Lk1cD9MlOFZCJYeYIdc/XcwvF2Wd5uCXNCCgFpWYy34j3ByG6rHQhDJMMYq4JGGZBsPfH6UOczEcwhl+/BEHP26Tz+ojLyvoZ1QIkAxuGVnEgmSuAl4Tbz8hSsDLlVN45ETGhLDwDwM8vWjF+JQMkx9Q5dPuN9iwc9bfPjaABqh6DHVqU7hbwDrIcp/6X8nWi6pUSoSyUB7sc4X4KuutxsVBTMYbF0yY/TKyrKgzXnXMB0qFmcPedSckSg94WkPWGLBaT76MQwz1DusrwjJsbIJct3R7WUuLVeckoWprMQvrOvQKpVhy9AXf6rm2bAOxyjsV4uRuhMcYLn3Iz1qfPQO16YEz4IIyi29tymj/Ii36+yPWPlafE75omE/TgPTY/D/BiXTdZyf6QwpPokmHoLtX0EMcHU9uBfdOGAJkMvM+HM7si8hOBOuSA3sUW7n09I1lLr/d/5dtLAFIV39l9Ch83BrilBvjzZueATS6V8IRqatxNFwY7b7AfPKD0uGYcLwyg+MHyTVxVR64FKfvgyjSKQmWUDbITwRuTB+UZxyuuW6IZCm0r1IfLR5ISLrKuY26TqRdZxB3nE7dDCJbEpXt+0tJiqCD90Ad0Itbs4+5UP1wzY2EriL5hOhxwETI2Xs+Er/20ncrdJ2s6B/4CXg5H6JcftKzDwq8+Hg1Jzutx3Zsdiea+fhIxTXb2qlIicgjm+XXvkXAXNLXKYN6Ujh7biwfojnDYfkq8iOrivpTvuqqwCO0sNmAWsUuMdyaBFFPkh+Uov8utPVF2Ee+luSWl3yEfKrzcBlnF2ZNDfveZUhQSh82KTlIhgeOAODINy33nxJMNuMeaeQPyAOApAuODzNTCGpqcgxRfflAs6hjSU3br6OgG0BhuiOSRkxsoIQ7kiQzxTtq18HweRANEuEGWHKLnXINp5xmHB9rPqOhIZoJq4LaKcMZlILpYcItJsHtmXFyeHByWIQJCAC8NFt1m7MAT3K7NxKdyjfZQrNHir6fz1XV7gFCzPTPz5XZGOXKgM9IOjC/W27LVBwsSxCBwkyQb+rMIs6NMdBsDoFGB1TXyAUG+Rk56bPnmyFCjf6G7ejj3rs33Up2GehzxLQoMal65pRAbtEJcb7Dv1LMi4ccXMkny9zb3qAEV48nDXJJDh1vzF/WtLS0vuF1a47RIjOHxI41T3nCmyYIe6oRpke8GqJYj1R3DRMmysvniLPji6/PHwRfZO3vJV5BGhyMGcZpspqDBoCJooZXCTNZPXkf1qtgVgbcE2KLUpvAB+VYIwA1oEYUPkvL5yMcuJaEE2QAKyt0ORoIRd+O+pqeOu3vO+bwGIGAV1/ERRgHgiAvw88S/jF8GajiZxQtnWe7/ySj+9ENcjCCNL1UxaOV1rD+ONf6GDeYyf6xPwGvnt6Qaxt68ceFcLmwZ3HQvBknv++v5CLag2FLTV6wqEDuBzf912k2GG8iKY9SU1gGTBPaCH4IZeR8yDFzHzCghBbhEGtbofvLr7Xd8MBUb+tEqHOR2vNzMMmhrWF39a4tnIff3KvoR3+PLKfRKOa76dRGA8cQ1/73+z2TwVqLtbxHoNJGWWwUiE+1nK4SC8emvh8LpySfyB/5h7KBam+xuHgtmaZ8uz1l+st5WXFfp3k1VB16TnasjV96WWWaNhuSD7IK4woHi6sM4SgAuIDYSvgtPqe4DtBb8SvE9P+go4ZvHk/NbmiLi8YQTZA3voERSoMGVjs/bAjf/I7Lr6enr96hbzJJymxvjtEPdCCWwTRoLUTOrK9JL7q2di43XIFSw8PrPp/RCYqTh1ZTMNiz4GW0zy5q6feq6dAnp7il4npp5zS9ifY16d+fqYZUvZfzvdsbszn041UVUbDON4vqrVLWHNkof6v7rhsw3V82+yILPR3UItf3HkCd1EuYV6ejXnh3gMpGlDAE2qoqLJ+8dpxwW8g9ifEN+CZGo+h+xONrQdak2EI/VnKmosXspqSPwg96qQy36zeDtF+Ipmvr/8k/7kNrEb4hkSD7oKUjvuzM4XGb5T2JjlePVY38YWpGWDL/Id9b6WJzcL6YKkCF+snXR5p8SFvG4NBkDET4SqDVcV7E/syzOYKkCTu5+Eu9+fYjeCVneVPOvBf5vstxh+SEiGjDm3Is2Luj+d5ZaFMjtxshy307hLORKNk5tJ+vruavuShdj2dh3Sj5rXV+yKkj/mEaPtOz5FDCug5FC7gTC3AUjfhipgNsTa6QxQCjfKkNqBCP6ca1tAGPg7l9+XU/70Bz+xJNHQc7WPP6dOeZeIZkUxRX7O6Ql39TZ34hXJueUem0vj+tyKUXpajtYp7yVNvTB/yspqtM0Ov9XDO8XHkvgPHgKDY9zPWRlBbdfU1CjJEWYvkU7Qrk8uQbPzAZKg1sIh/sRa03VXpsnLyHVeYXZF4eioPauf7cyEiV34Fx0AikMxiCRnS73ZThEmuNcRbLlHKhHi8/4H1UdBD6SKcCtipt/DYLvSnu+r/lQNxkjcTY/CbfB3QIRitTwB8uoif4jy5V3V9VY7iyESB2N6kyjNX9qQhEk1HrcXk9JBDSMd2UA61UdLkFeQ6HTNSq9Vc5dnEqzLTxOZACoFijHCzzu2I2s6cwCq3oUTTKvYetIzmJYEpi8BOb/7i+d8vzIWOyqut2dyQEI8EG+ry3i6bBLWk1dCedWQVh2feDaZufpnverL7j2zSkVYJEvLitFC+HPKiFWRZ3th3jPr/VxsDunGh31ejcsaEiY9LX6fPoAfr4pvTdYWfQaDlNOOfII//ApxkRzXchewRU5dfLegemnTsPUl9acWRG+XPv6ovXGlDdw6ddZXt46PyN4qDT+/uBFWjmwQBbmMKEHcNtoFeZLSWuB/GaKzRrz4vcLywgaRkx4+jQxGSokJZfWg+GgBJWC3250OAeY6y4JP2+LDINkaDHmDIdI2Q8LJj6UeT2oBqZ+CnphesVcvlW72LaEAwJfQW+Spd8PEL8LWQ8IjbWpUIgGlr9MxKm/NCtnWIG/hF+tDc0KbD6GDtobAL3a95BDBt4Q+WNbaRhRWZg/+DJ6EEFWBidwQvbq8OmEQXMw2tV9SoV6wIBYXRupDf0/LB62VTJoUgSlqYQ8gWWgHxgJup81oN1FIpsSPVaeI/dDWjmWJbVEuJCNy+9ZaujIhgVDrYXuX/DviN+UtxO0Pn70fu59jJl1vQklHIAd/PhP07qL25UurxvnBXohDeOhfwwRhxzvGguq2wCodNX0eX572TjBXfPlZtOgr4Z33T+ZG3g/tdwf06yevNr4krR8v8z9yM8KhyU9CCQOwVK0fkVuQsS0UwZGStOMK754SZScDNv1sUD/MuhYl32d9SqWTzXKC6PFiWdbb/n0yJrLRstHijxLwARd++0SDz1fsdnOE1ry8e/PSqCH/k9qhvPU5sjli1UrKyqNVi6DWg8gDglfq2jDtjptLRnuQfXxgUIsjdaNJ92h8aWIZTyqSbK3DHowEBtU9TBiynKWNA+mWUOYFTLid/M9a3+AoyPSQuU4DXpoiWsBWdkQtAdQI4ddu4WkM429zltbM9yboVdWZJVPIYRiiVMWKvlK8vop3H+AXDyROgtt8aQ5LrLd9byjHmlLMk5/wO0OROn18JhGXH68rZbEtUC4ji4vkfU6ZAmFdckSuOVrudmcvIS42HBP3+V5MzayMEHchmRSXTM5bGUlTl60o2Z4zmoj3Hj7ikH82Qzm8g7Sfyj17JL+9xy9P+6V5oZQZn3MrlIOBMdK/TGVF7ER/gP7QOIrF9ul30DlV4x7iiBcrOmD2W5RWDml08s+i4tNc2ojdJcY6oPUl9X3Briz29DMZwXkk5Ek9B86QFyOgB+5CxFZgdXds0nOQCkDY+eEKCJkFqZzT7rQln5NdgHomv3C+zk+u8UIS1VfUBTckUJ+xQft5kVSoNjfCqpzpCV+o09PpWGnH6DIQV7xxqM6/5IjG9yn93rbXdc7m4sqjD6cLIecGcthGmA9jF5zU+HkrEGOnA23L5Djj9NhiZ/yK/tUtZ0/4vr7cOWVQOsdXdjcRzdN5au8J8TYnkTcqUfYT972TmSeOq132oDRvYFzECOEgaGtRyfDkGv73wdDqyyOLVe7bkbwi7hXsc2c66I1nGYF9FPg5I/I9vR+2eEdGRPiVWLSbIAda2ZWNFNyIPL3vqhrXCW/C/OuU6/OjViREET37mx5aWtgIO9UJshvC9vwjDXNx7+XrK3QQUhgUubbDifFKDuIreVCqSXAD6u8dDopErqK9nBQzXaYLR6Ne3yn3taz92JsXp8fLwDXm19bNR+HmDUQvKebo00ZfkMqaw+trN9dTFhSQYcJ29p0obJsQ7Gfh3rH3WmsQZsXN/prhqV+EknmBmBtWLyVwqb9W52E/7YLxdWCnFG3S8eBuV3I/xtFKJ8aqpswKF9vJKU62ZSed3/B2SmPl1GdHt9Qmcn1f/w40d7Vfg7qqEZy8KiodPiH37wbcz/vwefOPJ0KNcqM3U/w0lN0kVYTOvBAHSTpz3UNB9B77fUtF0yz26wH0eaGoekxC11LdeUMutpw61I1B9OAFdUxvtTwvH30keGBLDvxhYLM29hp0t6ykywuUR8y6ucEpJ1i83ivC3EK8+2lUd5fpBR++4gqL+sXJIreNF2ZqbLU+1CBILQ7GBbfv/CbK6dEv2r8Gtpc30exu7ooFbnkv1zNHqfa8g/eyGGw85BlHADxBXXedvBYhvNWhXmPeqStAKxRlHhRbqR/hBt8EhZI8QSrDn2ZLjK6Ai7hzkY9/c/du2cCCqaHVITfQP4sH0b7dvTGQBVAHCh+MGCkTBcnHBWDWBTV3BXUKf2CS/eK/pePkRFK8jZEq5l/uspZtpUqSqPrQ1FeZhC3mrxzzUy48WPpnJilj3zPidhtj+U0HoVbdGP/drEVTn0W/J0X+FBV8G3yv5MgEWcr6px4q6KLyog/XNlgiQtc3XPrCywHzxxAk1QA5mZ6nVlfIQ3+X/h1RVaYY8q4B0QtUj69EJ6TQ/U4AKtYwt8ShXoFbiHr3cuGgrpZMh1xqj0l0JyVH+aHuORIlqokm4LDxo9W1xtNUdXbj0F1pwEmMott+4Tx3SsudR+AoueukUulgxi6QztmFKGr3XS+awJ0gf7MwrBBNlCCtu2Jzphu2TSpo94RznjROc5YIdfcn1496Lfw1q1X7DTGj6ZfcJmJjp5XjVfPlzUpjs6zXrrWA22/z7Rw2Q5W1
*/