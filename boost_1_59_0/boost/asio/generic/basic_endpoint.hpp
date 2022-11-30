//
// generic/basic_endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_GENERIC_BASIC_ENDPOINT_HPP
#define BOOST_ASIO_GENERIC_BASIC_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/generic/detail/endpoint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace generic {

/// Describes an endpoint for any socket type.
/**
 * The boost::asio::generic::basic_endpoint class template describes an endpoint
 * that may be associated with any socket type.
 *
 * @note The socket types sockaddr type must be able to fit into a
 * @c sockaddr_storage structure.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * Endpoint.
 */
template <typename Protocol>
class basic_endpoint
{
public:
  /// The protocol type associated with the endpoint.
  typedef Protocol protocol_type;

  /// The type of the endpoint structure. This type is dependent on the
  /// underlying implementation of the socket layer.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined data_type;
#else
  typedef boost::asio::detail::socket_addr_type data_type;
#endif

  /// Default constructor.
  basic_endpoint() BOOST_ASIO_NOEXCEPT
  {
  }

  /// Construct an endpoint from the specified socket address.
  basic_endpoint(const void* socket_address,
      std::size_t socket_address_size, int socket_protocol = 0)
    : impl_(socket_address, socket_address_size, socket_protocol)
  {
  }

  /// Construct an endpoint from the specific endpoint type.
  template <typename Endpoint>
  basic_endpoint(const Endpoint& endpoint)
    : impl_(endpoint.data(), endpoint.size(), endpoint.protocol().protocol())
  {
  }

  /// Copy constructor.
  basic_endpoint(const basic_endpoint& other)
    : impl_(other.impl_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move constructor.
  basic_endpoint(basic_endpoint&& other)
    : impl_(other.impl_)
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assign from another endpoint.
  basic_endpoint& operator=(const basic_endpoint& other)
  {
    impl_ = other.impl_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move-assign from another endpoint.
  basic_endpoint& operator=(basic_endpoint&& other)
  {
    impl_ = other.impl_;
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// The protocol associated with the endpoint.
  protocol_type protocol() const
  {
    return protocol_type(impl_.family(), impl_.protocol());
  }

  /// Get the underlying endpoint in the native type.
  data_type* data()
  {
    return impl_.data();
  }

  /// Get the underlying endpoint in the native type.
  const data_type* data() const
  {
    return impl_.data();
  }

  /// Get the underlying size of the endpoint in the native type.
  std::size_t size() const
  {
    return impl_.size();
  }

  /// Set the underlying size of the endpoint in the native type.
  void resize(std::size_t new_size)
  {
    impl_.resize(new_size);
  }

  /// Get the capacity of the endpoint in the native type.
  std::size_t capacity() const
  {
    return impl_.capacity();
  }

  /// Compare two endpoints for equality.
  friend bool operator==(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2)
  {
    return e1.impl_ == e2.impl_;
  }

  /// Compare two endpoints for inequality.
  friend bool operator!=(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2)
  {
    return !(e1.impl_ == e2.impl_);
  }

  /// Compare endpoints for ordering.
  friend bool operator<(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2)
  {
    return e1.impl_ < e2.impl_;
  }

  /// Compare endpoints for ordering.
  friend bool operator>(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2)
  {
    return e2.impl_ < e1.impl_;
  }

  /// Compare endpoints for ordering.
  friend bool operator<=(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2)
  {
    return !(e2 < e1);
  }

  /// Compare endpoints for ordering.
  friend bool operator>=(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2)
  {
    return !(e1 < e2);
  }

private:
  // The underlying generic endpoint.
  boost::asio::generic::detail::endpoint impl_;
};

} // namespace generic
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_GENERIC_BASIC_ENDPOINT_HPP

/* basic_endpoint.hpp
Co4cBtKq08N99iF8uOJQD19Isu1bsVFIlSydSqQy7n6Yi+qNl/GFf1DI2xYXw/aXyN8Iosg3lwNg/6+Ue5PME/iSETbGjLK0iTVFoXmFMPKexTAiJYnfNsvym58QqeyvpQ61DzXCOs2Ws4yRg0E2zAi7u4ChCfmZS7ss6HeHKxSl0cU0xVcstnitHeVG68iqKbIkVoQ0qtwTvtyTVgXNEo9NOcDETuM5xNvkuchcslKJ8f313QKkadarX8iQ8rsO5PIWkSyIZBrRvfmtbDC5ygVpW6MaZ0cRPpLLv9Oor8rSHnh8pFZSYq0sNIU6U8ilOwKi0D50/pNM6knZN1RGBlVkKqI2sO2YWBPU8S4bab7NV9RMFBD01KOkB8XU6ArvlF8ruJ8ZrVBD3cj9GHkNgv9AL66kaSrpoT+rMKRQptzFxMRQ9yWDPobgmPRx5cW8uIIX2ITtcXbUmrT3OczG4nV73MsPUJKZA7kikCI0C33a/lOcJJcQEELmEtVrJwfmfL020yBf/fbzCG9yTdMvke97KflcXex6TzxHhMOmsX9+rHjtRPAQMrtHZDMh+5/18G/F5rsPkZLnERVanUOoksAY+LuLZti8TKfPpbO7PV4juj/s46AaZbkqIlFlLQqfiAhVo/9JSK61PtCsAyJm4wIDFWtP360xzBJrVpFGRdV+7GtaRwD0v10Xn89fj8u1yXMQv/Zrg2R0DFjkSGRyz3pPrquzOsPeLo+1Wh3WWVcpFFgoD2WNwkfD5ddHPAWO0A7jcR7jZjii+iqBsxbjlZ7dizbP5RAVGewL2FzO8P92fQ+61MOmvT1jJq7PE3yXE9G6Xjmn3A9GPH79E5Kx5L+jwJUpW/pq+p98OsvEBO9ovivFGYsq45Of95gPV3VFTqPIQK/s+WwoE+gSLkJS/pWaIZIRDxIIaN8CG28ENtGTcK8X4T9/76zAIhqE9bz9yYVN7odMfZ1zjHNHIIGWRh7hnvV1+Hi5lrmypsjoiLT7I9Js/gmu5vHQzfJU3iNBALsR+29UbZZPwnCyQtTDdVavYIWNBINHmsHzR+r19j7t0LARS+t6LRyF3ovEUdXEnxY20fZi84pd/esFU+1yKmpwJ/x+XiwFwT0Na8qN1ej6JO0048wK7PeQDMHU2PSCqe5781tn3fQskdPX4GIpQU/Dx0L5EqbKdcVB0c7/xSS7CP6Juw36+SCyaDOhdQdflPSKFoQrgarVbbU9G4Qi4o+9RDOISqbGE5JP+ByImgX279JpHUxQh7qp8REFTK0U+LhqPxF+pdqt+cSbzkBb+lE0wWvE4motHVIth+KWrlNeKgbSIE3gnRo1xCA2hesS5dhm5tN7wpJ2pOvTgZ1w1PJUGMRPuxeMDBuDXmp2lw8DnJBJXslV185FnNGZ+CfUjzal0kvwa+ibwyoCjxO4PEWBywvF3VqydK7gKUclyeSRfr5OlpDEU24P5LTUK/E2tI/6zaARjDruWcR5YiQp/ZejWi6Tefq6FRYT8+K+OCIT3La0Fqy15iUz4RT6or3ejvpNbL0It1RigyJpvk54IqH5xVpGD4uH5RsMZjYDsy8TTxI8R79FyBHwRhLOFosb2hrsL4ZmETOJHYb97U6iGOEyhKZKpoBT9AorVBI6ltgWuU+l6uTC0nkj9CkZjUJjWLJ7gR/XmvmWVZPcKr5PFJlyFK/+wrQRhG2nKVRs8CpjT8ae9numqv4gchh4I6zLduCZTS1sO3FHmw4d3tvMTJL9n7Tc+mohvytyCYmJy9rAkCNTIqbkHnR1aD0vGw+XBNdu2uFiOhzKwEmPXK6QnQeGLjDqoblg0qk4zSKrRtUFZb/PGw6KelT7n9f06qzRPJ+QDPzvR+2006kxYJAplZOTqZM9sdj8vp7XedhlJAdFO0ujtmruzZvPg8HopZmdJE49e1t23I8UhE+S228W5IjJY5wXbzXCFwuw4GZL9JZQedIQHt3wluN4PrfxEKELJ5WmL4mdwK6TOXI6HJCjqSRIFGjxJJ2lfT8foNO4eo/PFy3G/J/QKCHf1H3cFDKUpmrg0tcN/eoiHCeeCFKVEgvzACa8ltYgLnTBD7hzdeSNxplwBOgpugAG5QX8oFUs5ynUOA9SIlwvvpw/UYT/zDP458S8+po37eBtoJ0mMJAysxmby0+1QaoiZsM9aZ0Y62bQico0/jVu5mOJEC4y9GAUNIOMjj+qd3PWjkmUXS2OABc907zlrxaaTcBj5kRfmX/ZJWEntq4fuogq7+lzWSxPNWR5u+4lLncTAMZ/wzF2ELv+i5UonoJBhoBiA4gk4iKRPD5NM/Xv1OJ0R8Sg1v6lGM9eCkPkdNjYNDntINyMOCaVge0dPyWcPYH8eMLvIWseyjpPccWWt0vedDRj9tZ+TgVDNzVpXA+fsio8g28vA7sv+/r0VswT5gda6ScS/q6Dg5JC2twa3TLboRI0O0IphbJYzFCAmKRr6FmSx4mkF7J3m7M5AY8G/t8cMxhL3+utVoeeEy228klu2y4ItY8Ru+/VXEsQ/C009p1ngO1tTPcfDEtPjhtmftMSOA6niSaWMPny9nl/7RFFIbuQwzod+3eTUi986MOacTNwa2wGW6/Xee9sGqxj67IrT1NTWahBElYxtIelWAnp+x0f4E1L0CRoyFQOXRxtad713RoqP759FHxD1DdRaCXVKpnwjgo4YDMk3rFiX46pl7w0Wo/6Xeqiehgz9y/bHHt3sL+mKqZOblv2L6o75LTTmWI+Tocm0QRpXSpNRTrqQM6Z1uYXxR74AV/TaWdvJfzkAgPv/FmzhgBfR7iEMy/NJUVOre16Q7+Lo7yDO8RQysaXrM+fL6m5xTDXyt8yycr9r0dxDMzLgHEx7s4aJpnTWtskgImtJVAaXNrRnHI6k2l/dJ4cOXsFXqsOAi4nTfBHIo16iKDywJGKPeT3cVNF4/U0F9jktfNuk0cu1h9OaP+ec86E8EMpHIa9I5r7Hihd+PVwdgEMiL8mP1eISm8UwNPSu9XfnXy3BIF23cws16a+QoLSG9yc0e48nQdzGbV6Jq7XW7EGC7i1fNUutVTURn81edwt0top6/U7XbGGiYeF1tssYFyregCioOTwJymvuPg372htn0vzgh+1/ZgqydYkwzOxOB8591r+8rQXWryLJri3ARNpHidi3+AeZ5gfhnxwqMb1RNmY0/pMiWeYknZZ4Xz34fptyNTHkbPOfY0w/BZv0MO5jDRGNqJqMSZfBt3hFuMoyRvcrK7I+M7TY4hHy1cDV2QxSry3j6NBCeBRU/mh4rMW079crkXevvr/9d4G7O59GKcMqZ+nPRmLw8JlSBCFPAScuzUZjFFdcmhoaIzeEHbaIS3lPFXNgyJ7Zbe174+ZtJuiSY169TVtxXs7RFTlCTFhG+zsQYPaYR/jiH0Z8MXORD6KmF3z58wmDR9kJ15dssFM89X6/gmeAlF4WHCz8p5p//gsvbVHe8CI/KzMXyp8btkZCxEqTJdTA8W5wEYkNX09gB5KCcvJ5U8TdEugye1RMjfRoaQhGhAWVrZsejkfoEk2AEBVaO3HyeOjJmMJsxOwHUuHxO+F9kGIeqIkb7ofxVAlWpqoL7wa08tiaGhkX6wHrPf4LL4Ba6HhUb5HZl/8CFnTKuQ5JVo5dGSWe2gIb9O888SSWfmny/q9pXXbQsTVmfDGerxBW6kxuTbMkx9ssykO75SS8JVB6EsAqdMnLEH0AGhUnhZoww8HUpN4MaFP8RDwhGmsK2/5cjjiwRBKEEipJE75utizWTY0wReZZAvgIS004tSpmpLAqnjQjP83EhIkj9G83ikCMgM6iKqh4VwN7g/e2YWSQZNphE6jschqFovZVBbdscoZrsTfO92bysd9qxyn/tX4gRaGSIMYbMaQ7Zczv9lXpL71EYC4Rv7G4ANOXTzKdyOJPf24kSSCb9TI4bQAhXU5Kztg6gbMF5t86noHOAVQKDhiIJEO/5dsnIMIAAd7QhaKZEE8/zgIFtt5+jeEk3E93krjVc+7OO9aF5vkecCjuzXTfygFhH5ALVd/gYYlEPBux1MqEbPcHzy/r6tsUfn2AROHcf4/yWiWwSc/d4ETVBTXQ3Aoig4A0Nq2bdu2bdu2bb/a5q1t27Zt279/JmebTZJJEgIoHw2CjbEGS7fi70BaB4rY8R82X7xmKvL42K3i9fyAzgVdewNEQogMCbTWgOoQr1Zt7llaArZyJZ/iAsu1kARcsn9i+yPDbeoohxprQLwaP5k23U7vvhTk14WM2nr+VB7RDdPYYkB5Kksti+OGC7h0cl3AURuPOvbXLlgwgWXjuHiMCi/C2x7D16Z7hLSpVKDxPTAcY84ZgXiBIfuxU0a29nGw2FQPLXmDSHrm2IAmCWbjuJVrGkGFWbacN2//72GRKQfX8XrB4t6dzLTPDem0jtGx9vi/l6/BDUwYImvo/MZk/OsRjVKDg/U6Px80OMNnvG5sFMiYRqw1+Y5QJmD0ceJrzKW5RZYS0AzDGHaXqVINPhoVMZuvKO/nfUN18BIUpeqen8OC3BvZyezuIQjMtjkzewjAl2ExMGV1lGtLGlcqAFi6bJjlhAsKsZL1Y53s7znLtGxw5hhGnUjBqZmFbsxgITzm13XO6TXfZ7+0HUwAcKycjmIlsKhhO5k7AFe4QHpAFSoWGMOaoIBKyhQ5cJK4/O4xh0lWfm1IyVym3si9Bi8+tJ2G8mV/tPkl+NwUf1l8s3tYU4nhQcU1jSKNb+cdehXBUv1Sc/chDAjOFlw+gp5QVb1/5GPgAzpO4XCfoseB4MAODlWUbeBXgkQzdogOv1Ql28B76GBREiY6QOgtaSQ+yJGmB/YQcpO0/hE9ZnPMN5QvOeKaqlzwYGYUefrxSW0qLFl6eqhdZVBAewRFjKM015TBO2UvlzsnCckjM1ZI4bLVo+glESBK7Pp9iJgtuelBauuhOwmpu/hHXTlifNm6+4d4GBuvthTAesABFlZPZM9oBS7ufIaDoyLa990iiWN5vXr3bhwp+2vX+mRCKNeX8DoM877Fc+hBj+H9j4LI+wXqULXMOzy0FJBdVrc1x/ac9cGTqb9BwKz8QLNfATXWb0nF/iUtDFowQe+34nNvWKc1YTO6fj/uMR9tHiFe0EA0PDpZGCw84GwHKYsIOa8n11UOeaNWdPYTxx40g6bDHCBgvjSQ6gNNWwNO8gV5wZS15iE85OieurXHbhFlM/3W7JLTYr194CtdFsDreFY9oUcRE0mUy8GzoPzlsUAv8KD97MJ4GA2MiDuSsjxs90yZLGwgMPEhGT2HxyjQVO614iqf+Eb7tDssk5iQVToYVQBGlewuPm4wRnbH10MsAznNlwaffRxJerEChLpWCJOUQGFWGQOvkOoejX6UCaYkP9yGDYGA3b17ax1bOIPwLJtqItOfUnJVq2PaR+yPFSqrI/8s2CdbijCEXiSqrIiG+0AXlXPyRTfdhNyuiN7moqFCjTIk4sHygr1RbT7ZOQV75PP7wMjNU6eN1oV90gebgv36NojG+9/HGgFU4mb89CFgLcFytKK1LCnJ4t40/Yq/Xq3/4RTBZcI4KtURRLShPOC3nJ7kbVr2xWC12uxAZpaJOMfZQTRvRkGros3MftIeH1yACi16ioU/HQf4n2huXtKpDL4ZFTPM4QlMNnTkAesTFQvEeljH3zBl/7MIGtS9ZIdLRReUYuHUt1b+zT/V3VUWFF5jP4+bBYqNCPGN8/OYU5Wq05neGd1n23sy9jExJPxGJ2Povij4gt/k+XXyuEmV31k1SvyFxAwB6PCQUk8pEFJOk0IucJvkA/D5/SaRjVSmzGre+rEgOXm9LTG34MKJU13AyByoqUgFI65sud0M66dRNXsCCJmRZKO4TRJBT4/P4g5oqWhx3RJuQULbuSsi1wPh9E8AwkAn5BeKLaiscxedjS4+Naz2qbxnmTyffzfI+Yllg+r5zRMO3Aw0G9pbyEzE/Yg79cz/XZDUE6HshoJym3wYc+sGFuCiE3jctcN7A/5aZm4666x5osHZkg4Vbx7tCEQf3c7GEp5ND9tgequa+VAnixuVJkcYvOXyN3/agyhArxnYA2TgxFkmAoLUUwsi0GSeyStyVliy+4asXbrjA3PT8tvgtTvO4rLDpj7hPY0Jqb1t/g/JDRcbQ5sKtGP7/Nou/I2LG/qJFyd5tEYpvqkGr0hFc/d5Y5e1Zk6Hff5TnQ4WCvDHBZL3SB/RJdjs77Xslk9WiNKvP3XfjHZIPWUr+7ZTv8kUiIkCeV2kfNI8PnSObFf+wNETnWbAwik0sVZCTN1kOrqNEQcYT0onqqESZvvvKID9JYI7GiElD8FUIk2hefEtDcDqXCovt9ynjXKmGtE4nqF89Z0wTcYC22WDdMv2VJ4ZFU58/d4BfSPw+c0sPH5OXQx1Ny8Wb+0B8Hi0Jz4rs9ELZseZr+B1uLibpgrFb8Gcb5+GKr9mXiKattDQyFDGbxufUSSXSTIBKZoywsVmvz8oadEfFE07Vt8rUhI+dpNkAhf/PKGpHrwXZe240z865CAaLkykAzZdNCiZotxF5TmfkfxW25yKnJ2pgstbezngUJyZLXg/QoCcGM4c3r5tWpdtflCoNr4YXAiw2cDqnSVF32dcNXQQFDVTCg9s2Vqh5Tom7DkDOb8Q1Y0njVtagNSswlGck+MH5ojLMfYfYCNPI270KjxifRC4ZR3Vk1c6dMtgbQM7yHKjeDvo3Lxt2kFPvyNpkqzbMQS7Qt9jrgekXAZKtpyfJ5Y7tz4kvvbnO83vf6dFLiMvFNnwOMm3XkGqOTVKrSKj8mXz8es/flpqTpuykdmQARmnvRs0k9TeAkPicGYvHQ2oAKh5esZa5IM/bmZzTdlZeyus61hq4efO0Bzl0EaO4x1xlJWoh9cGMJrRBBbhcILQYOIInFVvX3Uw5BL7eMO6l7yA+5+ib1j2GQvR/cQYG6kHiiuJ8gRzbXsseA0QSRX2kCwffRgZlcqrS6Pvvhln0PkSdURb+FWzd7On+1T4SKFB5KX4l8xeuuMgkt8e3ye80W48wzX6pbOK5w/+4e7aCAITjMvuEoln5jdClV3IdITB/4WjvjHWFj/kg+EeG93tvOWEX2QP6lyyQ6rJ1+BbvFPZw0zzGkJBmVmOe2/8A9+oBJeqUy89+tVHrTsRbbG1QPyn8P5pAbVOhCZP0l6hfVZCeU798aMLbwjkHhL4Jd82n1/LSVxkrzYWeuJIFZp9dKviMzBTe752zOVxenyh9ymUyQ/utxsXluP+NkmvvCjwdm8N4bEiqFgCwU4C+RPaRIxWiWaxr8LeRYPqPtBh86aD37r3TuJ8l9x+hum4fD2WugvDM1t2tmH9dgqte9JzHy2UxVYBwmQz+vlNlixm/xoSb/oyocoMbWpsgN6j1kkHJbnfw0EGTFAwi0w/+7n92jC1GhiCpNrc/NRBu0IF6U3mlNq0RX3H6kQF9s7lnuHHDC8RtsIZuvPhzRReChaxTabo5GscbFO4QhKy6N8AXR9aUasWuVIb18VEzIrVFvm430CHcZqJMd7eDZ8ciBXgQCEyXE6Fpn+4k/wf6iZnMcFkvU9tzzc2KrSRiRWLxlo29XUp/4rwZjNv+DQHiLtK
*/