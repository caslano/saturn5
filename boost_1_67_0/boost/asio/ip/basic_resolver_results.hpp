//
// ip/basic_resolver_results.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_BASIC_RESOLVER_RESULTS_HPP
#define BOOST_ASIO_IP_BASIC_RESOLVER_RESULTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <cstring>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
# include <boost/asio/detail/winrt_utils.hpp>
#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// A range of entries produced by a resolver.
/**
 * The boost::asio::ip::basic_resolver_results class template is used to define
 * a range over the results returned by a resolver.
 *
 * The iterator's value_type, obtained when a results iterator is dereferenced,
 * is: @code const basic_resolver_entry<InternetProtocol> @endcode
 *
 * @note For backward compatibility, basic_resolver_results is derived from
 * basic_resolver_iterator. This derivation is deprecated.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename InternetProtocol>
class basic_resolver_results
#if !defined(BOOST_ASIO_NO_DEPRECATED)
  : public basic_resolver_iterator<InternetProtocol>
#else // !defined(BOOST_ASIO_NO_DEPRECATED)
  : private basic_resolver_iterator<InternetProtocol>
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)
{
public:
  /// The protocol type associated with the results.
  typedef InternetProtocol protocol_type;

  /// The endpoint type associated with the results.
  typedef typename protocol_type::endpoint endpoint_type;

  /// The type of a value in the results range.
  typedef basic_resolver_entry<protocol_type> value_type;

  /// The type of a const reference to a value in the range.
  typedef const value_type& const_reference;

  /// The type of a non-const reference to a value in the range.
  typedef value_type& reference;

  /// The type of an iterator into the range.
  typedef basic_resolver_iterator<protocol_type> const_iterator;

  /// The type of an iterator into the range.
  typedef const_iterator iterator;

  /// Type used to represent the distance between two iterators in the range.
  typedef std::ptrdiff_t difference_type;

  /// Type used to represent a count of the elements in the range.
  typedef std::size_t size_type;

  /// Default constructor creates an empty range.
  basic_resolver_results()
  {
  }

  /// Copy constructor.
  basic_resolver_results(const basic_resolver_results& other)
    : basic_resolver_iterator<InternetProtocol>(other)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  basic_resolver_results(basic_resolver_results&& other)
    : basic_resolver_iterator<InternetProtocol>(
        BOOST_ASIO_MOVE_CAST(basic_resolver_results)(other))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Assignment operator.
  basic_resolver_results& operator=(const basic_resolver_results& other)
  {
    basic_resolver_iterator<InternetProtocol>::operator=(other);
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-assignment operator.
  basic_resolver_results& operator=(basic_resolver_results&& other)
  {
    basic_resolver_iterator<InternetProtocol>::operator=(
        BOOST_ASIO_MOVE_CAST(basic_resolver_results)(other));
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

#if !defined(GENERATING_DOCUMENTATION)
  // Create results from an addrinfo list returned by getaddrinfo.
  static basic_resolver_results create(
      boost::asio::detail::addrinfo_type* address_info,
      const std::string& host_name, const std::string& service_name)
  {
    basic_resolver_results results;
    if (!address_info)
      return results;

    std::string actual_host_name = host_name;
    if (address_info->ai_canonname)
      actual_host_name = address_info->ai_canonname;

    results.values_.reset(new values_type);

    while (address_info)
    {
      if (address_info->ai_family == BOOST_ASIO_OS_DEF(AF_INET)
          || address_info->ai_family == BOOST_ASIO_OS_DEF(AF_INET6))
      {
        using namespace std; // For memcpy.
        typename InternetProtocol::endpoint endpoint;
        endpoint.resize(static_cast<std::size_t>(address_info->ai_addrlen));
        memcpy(endpoint.data(), address_info->ai_addr,
            address_info->ai_addrlen);
        results.values_->push_back(
            basic_resolver_entry<InternetProtocol>(endpoint,
              actual_host_name, service_name));
      }
      address_info = address_info->ai_next;
    }

    return results;
  }

  // Create results from an endpoint, host name and service name.
  static basic_resolver_results create(const endpoint_type& endpoint,
      const std::string& host_name, const std::string& service_name)
  {
    basic_resolver_results results;
    results.values_.reset(new values_type);
    results.values_->push_back(
        basic_resolver_entry<InternetProtocol>(
          endpoint, host_name, service_name));
    return results;
  }

  // Create results from a sequence of endpoints, host and service name.
  template <typename EndpointIterator>
  static basic_resolver_results create(
      EndpointIterator begin, EndpointIterator end,
      const std::string& host_name, const std::string& service_name)
  {
    basic_resolver_results results;
    if (begin != end)
    {
      results.values_.reset(new values_type);
      for (EndpointIterator ep_iter = begin; ep_iter != end; ++ep_iter)
      {
        results.values_->push_back(
            basic_resolver_entry<InternetProtocol>(
              *ep_iter, host_name, service_name));
      }
    }
    return results;
  }

# if defined(BOOST_ASIO_WINDOWS_RUNTIME)
  // Create results from a Windows Runtime list of EndpointPair objects.
  static basic_resolver_results create(
      Windows::Foundation::Collections::IVectorView<
        Windows::Networking::EndpointPair^>^ endpoints,
      const boost::asio::detail::addrinfo_type& hints,
      const std::string& host_name, const std::string& service_name)
  {
    basic_resolver_results results;
    if (endpoints->Size)
    {
      results.values_.reset(new values_type);
      for (unsigned int i = 0; i < endpoints->Size; ++i)
      {
        auto pair = endpoints->GetAt(i);

        if (hints.ai_family == BOOST_ASIO_OS_DEF(AF_INET)
            && pair->RemoteHostName->Type
              != Windows::Networking::HostNameType::Ipv4)
          continue;

        if (hints.ai_family == BOOST_ASIO_OS_DEF(AF_INET6)
            && pair->RemoteHostName->Type
              != Windows::Networking::HostNameType::Ipv6)
          continue;

        results.values_->push_back(
            basic_resolver_entry<InternetProtocol>(
              typename InternetProtocol::endpoint(
                ip::make_address(
                  boost::asio::detail::winrt_utils::string(
                    pair->RemoteHostName->CanonicalName)),
                boost::asio::detail::winrt_utils::integer(
                  pair->RemoteServiceName)),
              host_name, service_name));
      }
    }
    return results;
  }
# endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)
#endif // !defined(GENERATING_DOCUMENTATION)

  /// Get the number of entries in the results range.
  size_type size() const BOOST_ASIO_NOEXCEPT
  {
    return this->values_ ? this->values_->size() : 0;
  }

  /// Get the maximum number of entries permitted in a results range.
  size_type max_size() const BOOST_ASIO_NOEXCEPT
  {
    return this->values_ ? this->values_->max_size() : values_type().max_size();
  }

  /// Determine whether the results range is empty.
  bool empty() const BOOST_ASIO_NOEXCEPT
  {
    return this->values_ ? this->values_->empty() : true;
  }

  /// Obtain a begin iterator for the results range.
  const_iterator begin() const
  {
    basic_resolver_results tmp(*this);
    tmp.index_ = 0;
    return BOOST_ASIO_MOVE_CAST(basic_resolver_results)(tmp);
  }

  /// Obtain an end iterator for the results range.
  const_iterator end() const
  {
    return const_iterator();
  }

  /// Obtain a begin iterator for the results range.
  const_iterator cbegin() const
  {
    return begin();
  }

  /// Obtain an end iterator for the results range.
  const_iterator cend() const
  {
    return end();
  }

  /// Swap the results range with another.
  void swap(basic_resolver_results& that) BOOST_ASIO_NOEXCEPT
  {
    if (this != &that)
    {
      this->values_.swap(that.values_);
      std::size_t index = this->index_;
      this->index_ = that.index_;
      that.index_ = index;
    }
  }

  /// Test two iterators for equality.
  friend bool operator==(const basic_resolver_results& a,
      const basic_resolver_results& b)
  {
    return a.equal(b);
  }

  /// Test two iterators for inequality.
  friend bool operator!=(const basic_resolver_results& a,
      const basic_resolver_results& b)
  {
    return !a.equal(b);
  }

private:
  typedef std::vector<basic_resolver_entry<InternetProtocol> > values_type;
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_BASIC_RESOLVER_RESULTS_HPP

/* basic_resolver_results.hpp
ZiFFXPBmSeVc2qMMu2MyHMD08923+S/iaX0xrn3Li5mZRWKS5xlDoGuRvSu5xfhXZKZekP5dOS3XVtz2Bhidut6Gi/wmEHH7l8/Gq0nuAzcJ1QJjbvlXh0si3J+XnJqgoi2lCrJsHYtVtvwSFzxd4V4quP4RtbfyxjP7lVyG9ssnwBhrpikCpHYnWbuDq1Nqk2Ywsca/x80NnNqDBIwf428LyuwAB9KMegwbi+0oZHAmBhkajz0/I7MH76Pc99JlGjriZ1uz3lllHvcYYV+rv8Q8wpaGt8BHRgzL1klGzTA9i7A/25I/U7bp2YsqJ1RMShsjLhEh3GKXgD5U2bHuXkiHYvhkgUWcWR6HYHRkNdWI4xuIj2rvYBFnIuNnXezwHEZwe65kyl+XdeyaEPxW9rRQUHKx9gakdCxwV59G/KdjaRaFdboZAjS1I/7+G4aZh3W6BrPIuqdgbmiPDSPc++EIpFc7E+klzz5jEn6aSxpA9PBelGDe3ajY/wDPK9PzQKBUb4tcosvJT9uJOngLkQzVdkXg8Ns0DbZ2GEBMuEKserly6b0HC5ocuFu/jIEey0tUV2UpiGKnyE50+Q+Ci9cLBnJEeycQTUpqzNAdRrBTvIt8Xl8TrUs1XLcwVMMA8s9MLszZkpywCZ/V7MesnhcQm6HgeQUytNaMGe+ZoZ2fXVKTQzxR1hhggVSNqnVuQnYkrnVy2p3p9sBjw75adrfhH72TXmObqDmHgCkLlYxByZLaveZASuGhNQ+vU6Qb8GjN07wHZTYqpAeGAgZtHzgMo4E/iSkbhw8N+D4c5eS+c6u8JNLiZJQ7O00JimIa+A00nRnK5MPxpj0N5o9A4X1PzVj4Zmq2Ta+9POMZBdwUn+Od7l91njppmEMGO8Y7w1pcvqPpIIa8VcY6WFQop6ghkbgitM3ApNaa9YQ1/ssPBi0sZrt/jMx11vpoICHm9lJp3VpjHu6ZKOFSaWPx73OMGMd/1i13PsdVAG/gTuB+cCKUFOXFGMqvi5KMgtPv9P6wpJr0O94OyKBj0v6RbtDCW0L1Hu2K1occ5mE49yF6MSOeMAHN8Dukp2ES/0Eaa1MLvzdOuYg5d7QU79eFDvR1k+98MTvcsI2G2MUqGNbhZGPukjbN4Tdi6hXx56ilSqBKpfo57OVicMwDcAMJC0XiISs1Vqg5qR3mLND3HOq2hkeuPyZCcAl2ZtQsahukzqWdVe6/bC/qBWUQrLLt5Mycn1Xg5buu7dzY2RJ1EZx4HPHeID6k5maF74ZK/vqGQvChbNmJU4YL6KxINHu/XdFRbmYbing3QtcN6L1jHzW+mq2EGFUx2+qJva0/iA6AOb0w+9q+5iU5005BwkXO/PXHL+ZCT1DpR67RmOgVo+vO7iG7ZCCioTtlwJe5eJKNnDfn4Mq27+Yqit32e/304mqpFGy4hSbP6DafEdmPj15s1PDwJyEup8fJqm+cqmbw82u3kzeBaDXfHaEIbSOWJHyL0JUN1r1FysnmC9kmW8wzKHdaYy0GgjAFCkZt07+AZmxWtCCoB1/XUUe/9gX6T3tMpsqqKEvVrHJSslC4sowEUrqvaAi1KChyarNgTLyI35MHpGo/QOyj/FykDCXk46j2eJ1hL+0AQXHiKHb2H+SA+0OLYYTRxNVa1xhiblXRWGZSp+llHXE9xxkzn0WuIsZ/jk+VEQqwh2jc8nIXKqQn6g05CR560oKIipjIxsYqh0NGc9coquADLH2GtaJoQEzDxiTpq+EWeOCVbxf08Dr7zKutxrzEUbpBRmDyTnlfOnw85E4SEDNe+lmLsvCuEz7aoQoic7EZbQPNFi9g0seKE4tQfuOwaE/qwCVkHFJO0I7V81csjrgGnfQZS6/y8OrC1HR7YEsVjK/VAa5GdFWkHWblNGjditZ9+6WDcYRg1sRw6TgrBnV57dv8euUDl/VEsJh3/XTQvdXrpWOTX5IHokLWMVPsmMmiDpmvZvIZskV1GDtzkdT9zojwTTM4L+jCg5wPJinnGFp9tB0OqOaRWTgTst7spNStKeyxXzwLYpquoLjqky2+GW/Lx2sR73czcPAae3ayrz7J3azrLmOzaE36IbcKhW0XMIcB4HkzrwpeG6hyGXX3qKpmvHTRQJW2bPF9SnghkflQvsX/YtfeqYR3srZI7FXvIYqeYfxgT//1S/kJI9zg5W4pLnmzt3JVaXMa8Uf9ozfo4oBnpnnyhZ9b7uR5GYAp9PGSKNQUrfQBQE6MV+4PkkWpztY6X3yKkg7PSfdM76E0X+d/ppr3dOzJop5dpOm2yo5NKoocYOwTj16HECllQKdwSayuHjLPKIl3GHxpiph+zB0U9IzGMiUqIUhMeU7T/C7nPHegF+7K0MbSry7cUcErQbzCUnXP8Rmiobxja5u/xt18m01h7MmLrlhLyWUbfXtBg/5MiSzv/veOdvm4SoyQeNkfcZQpJnoAl5A7YfppPjF/EH2FRRFEMtjbnYKqdEerwv1cWLa7tDCpJlKWlf5Zz0k0uPwJgJgJJu6dtJGetMGMcHIvtIAOBj3E23ZIfaIvVHvwDcvruHZIeHLLYDPv3EvQY5z4PQ7ZEEbXuTAnUEr8sYtiyLaHP8QHbLTm6rXjk4Yl4gZz4fNRKJJ0zPSpEdqXFBR9PpN4bKYa3vOLfq1J4PqSwlBM9puUj9Ajmvg9DNlwhhcERDV826sT+ry/B5byVp+qltW89eSRaJ/Z7PXkBtOxa4VIFsIy8tbUvTNiCS9yEtX7M4Yvpxg+Dr8Jhm4wlHi+Vd6z1ScwLuG01uziPNS+GiyGVaYr66XvhWXY61iiBF7q86rtAmH1gCCoYtbIEasJ1rb3+alvap0HGQoGScpAqnDrFKiDVj7j9cqwqabSDDlQXBynYpQs2WEt6YJYbbnzd7+zMjNxAWe+Zel7dU1yMyA+6zTVBPa/IDrRXuGINMLvZ9O7/LBZEz90FeCgteGunLm8Ecj9L7XM8g6MYk15kdCicAK15sa5lTA3OGU89P4pkQd89Kil2SRxtMe6D76WzSjSa4OB712XnefWRIup2YtJTaCO4Zp3W14aY8iHha/UGtzj05WL0iFun0SL0QV0Yp6MzwS9JZJ8q6p+2V2z1SGoWDv6o7Q5PBc68UWYoBfpX7T6wXC7BsxtTsKhv2CRGJ7YcxTQ5cbzxjGU637I+5jFoiAkVQhdAbb9qeFj2UNFSDJ0hBdUGVUUklAqidIdWh0DiYZG0gZ5y725jfMU37MXR6ZZ9qjH/bEmA0nQdajK/r07+E+NZ1txxJdMJvbuSJE3J9WhYdnWEScBqOCgV1IJvC9HVi82LU3k9jnVAUkH3TQPpLskvuq+UiyZyKABd7MmRRPZyeBaMJaKEwsWhG5r3303d2YLgmWHAM5hlPfbQYzrbI02eMmyW2bu7K/aORWu338DbtqjbOC4iYirfB/7gzOy/xrrIkb+kzjeJS530yKmpUOakJhn3IYvl5snnH/J0EEHaYKArKK0m5nZETR20PZedMrQs5WLA/AGF3QzMOuhGQx+hMT6qqkE7NeCbAlIPmZTcPM2lIADv8uMh9nHI77iA6hXclC67jv0flwwq16IOiVfABn32dPD+760WB/sht1ViPAIovUwk4JYCVN/bPNCHwMgx5se31tU8p4Hd404hXxcM/VMiWrir4txSSZB2ZZyTw7irKRx3bkj2k1oUX7rzMXXsxj7JrJIrzo5fEWXy/RMfStztSkz2MsqBUlbZyfW7YrHDrxjMQgnW4ExU7jiyLzwSt2KU0uzTvZfYtygQCRtPrIZSiFnzA9JzVvb2AadOxwcDHwRopdhOmI9LK+YzNuK9M1vv9OEK/QRLY7i5ZGNPjfs0OrEpGwW/65ebbl6VFjfYj8n7K2qngKEaeXrq6Kbgc3DlAKSKI6zhW04AOowTc6XL9gS5koLT8c6JvQpjQrnWwSnPWSa9Dccd6PlMcjt8+y5crRLpyB6I+wtsX7KaZQvQH802wvnNf8cBhe97WoYKRBMfebCwtQpecRE+Gy8pUk8CwV3ibAA2pSbjxkHzkitbCcsuCLeGV3wRbXGDGdchSoEFZrtzj0cNrkFQxsO11PCeSY/Qb74SYSUOK5fy2nnRj0l8xECKujHORXzqDcQdu1vQ/DQEj2ygB39bomw3rImUBRoxZoKYmQT8tJMtBlxPG2qTbigt9m3euW+bU43ax70omyXfAP+7v1IcLObO7J/8iidylEo6F1M0me8A0ggh1JPHummqmk+fDolWf/JttfTkLxYuDVl/lXpFNuPu0HYuER9cit/AwfF9ch6Le/rxP8w1IQL96c2DfcTNR4Ix3+3vDkIcePLcZybQh+Zeo91gwmJ6x4KeVPdxj2Zf4xlQwmRC98IMZvk/+AJfpaHtftBTjGRflVK/mnhEkz9tHt4ofAuRmKITGaIjmnfrHrW6axtsjXfXZAZtLBd9OXKiONMiNOcELs90tjWrfzm2XhtA77sKxUgHf9kgWEMkKY5842QbK1Fko3qUT1XXg0fYrSN0r4KKXtALjNRPdsxDlEuQfOIRevQs7kQr1Cof0BNm0Zd6+2xbb1dAy74fxz8/8cBQGKMaaMc+4V3vefmzjrPNzy+yB/tWqvC/pq9Neaga3/7YQ+KCfggyvow5ihP9rVqUNw8UsQTYRH6et69eBZXEST/RqwMR6wUFeaccBxuf5WbCIrZcmwVmvJpxsqg+hr3mZDylPowPlt7qs9lfYssTsrgKbun8R7/7k35KAozle98bcSPvIbuqGao8ISntHcDp55iGNGuQKvVJbXSFknIQV29Hl1JqOmTTiPk+jfTFS4XO7ujC63hRWbUeiBoQZkp86gddGp+XkJl0341xsx5fPYPAbaltijDwOF+sfMH9r8uw8IiASQ3iQi2QdPKobFPu56XC1g5GHUoPbC+ocEQQnh+zqJAHY/CS6bznYN5SU6nMzJgU1lGuW97rkuFeDe0K/ViRFDS2/ehq4alVuQPBLV3bC4+b9VMD5vAH+Tvx4clVsRA70AJ9gsVnLmJAOOccVSa6JXvI8BAtXJvpeQHpAigqxWRwhY5wclO1MUpFNW7PX2XtNMYq+lS9wdJnu3FDvHWj0aferoXky8xqOxhIW60+0Mq6Me/J1kWYJAcmXNi6XQ6moaICji11t3Gvb712yRDaEARh6ewU/mr4AyY+i+0BlyPpDXuAjmQbo+WeQioLixZbHek2yLOED6YUIlmvyeXZoTwTKe6LZIY0LGwQoVrfefoLD/PW7jRf45qCgyeVABkx9E25VOdbXP2htLyrh11u5+SzEkGXTLYcPFKYiWJw75TH6DxDVH/dphgBEVJAI+f5dca7JlgH/Y2ezosUwfnJ+9poN9lCXdBJH1Sb2yGOAuMPwe7rRGdUXGRxLup9uRcWvIok3GMZWvfu2WfhlORbuwKvEJ7TxdwnMRY7PEyMSFPWTOg9rvQfF4WWVNJjnKYFnUhioc+Pj5HeS5ck2kjRUZFCkUWaJtqoXYcf5DDwhMz5CJVd+kDI0cO1M906yPyd+148pbU2BmBuJ5SMl4L17nd3PNuVBS3PY067YP/rVgtD9kIce/6ekK0zRzwPX92GN87nDeRUNjWZNC6I313pC1odMloIXSfKu52+y0hkLtNO4nu7T4gnGSB7XMQtd9PCuNQ2CEQVoHJG1+v2JapgNaB3EfWclD3y9iHydm+Q8u4tbf9slKys8ZfEh8PNoxjQRl9B7Zg+Rxw4/m54vwYWwwkf91iSNUN2+GAYkFu+0FvO795lntxxtMvoU/jfcjxn71iqG9bG/Qf2g1c/3iLPT71gdRaeeWI7fjhfrRY7PWHg65txZ6p+KZILcqNj2vyIKZ5PoFC4Cz/KJI+4Sz7/INvfw/llI3gLF9DOQ5WMizyHpum3Tp28RVTsau8wV6Z4GctNFezbWich6F8t8MlFdWUm4dBjXgfuYsVXV7m8rNeSPLSQVkwFrj54LZs6/gVknE663SvEwT/p24dHPaflGeIeObo8zmb8dSEv8uFsIBtbMYnP2ojgq0Gk/l/Mgv3qOM/97JFcrl+1r0VJ+PYGoiNslUQnAm9PR+lDuNAUz46q9usppdOj2h3lCjHgAkaDujr56HIxwRGe5gKOdvYJyQJiF7rlzT1zoZbTWyYCmRTfQi2OkzncNLL96cTP/YL09oLcSeEdXzrhFH7fCeyGCwYMe/Ypj11VPFaDTUMrfAHD1J0I3R95IgOUf+ea1ZOnEDneRjC6YQ8mmwFVIYzQV7uncRFm1Vg7A7Nc8Aa3/KGql9dPBy3phNkrv3UKsjMmuO/ruhxZW12gkct3OmcsBvk67YmZzCX17gIvayp3jyZ2Xg3OetGlv4VqeCN6UIZxw7/fBMYhbz2gFJ8i2APyN9CjEK+eMVcdaEXtA8nSytQeztadHW4YeG/R/kAFmwfRaOs3f7w2xKgd/La7nDZdkgw51BZoPtMqESXXvW/kh0X7feA8n6L8AXMzyiMQn54wTzzEYxdjHtnJIYGpGnPVXTBWvtGNasg0XriSebCRIT1ekR0ED1GPKTCNHa+6TX90D5eDOsJ/2YvBZTP4PgtdAFiUKB/lj4kWn2e0MqZFV6ISgy1+EXPEyCIFV4YSgi5Oq85F9LKURRaXO8R1qnXo16QCGCgJDsN/J4nIgig14oO6+Q2Ci8dJ4Z2nvsF+g9n/+O/WSExZEiIBu//7y7xH2hHKtp5DKu3F4Coueso5jGmiPN5zIsE8Xl27RFTgIb++BHrRQab9B3fb+y2gduUGCyehH0M8SVCcmHmKCOTMQQnSWLnB8s9FUsXC7iywPYC/pgAY/ah19CSmuqr8b5Bxc8qmmJiDyVDJQt1E3NqlKbXvmKfyK5+Bkg98A0+FOJnQDlU9lfSJYCXv6JyirrpzLQAV4EwD7Wi8oK6aaE4cXB5mEAkJfzUdfSFHAKSMYM4cXp5mGKkJGBUd/7eIdI5qsJYA/EqIqkSsNC8XLgB+HhM7ZAYZJRJJkUg1gZUYSwoRTVJ9nX2SMRKGISLxgYvM2o70alAH1iFH/S0H1y+UGcsRsEc03OpWeP7F3ZX/tBzPLSGJx/kntvn1AZrg/jweofEN3WePl7zzzeSPgR6NgoiliCdGF1bF1SkFGSEDWrJyGtIwnek/Ncgfh8+whSVaTW/oIfKZzmzgua7Q8XUjbq+cip5TTHd9W0t1OckoKoemYP8VkrxfStVujJZlHgzSdvHLW89L/iwAAgs99N0XXKEZ3pY6kHDTIPu8C2ye5IjGR02Y+rNQVbkeKAM7J4o1MlN4rXh5SPMDbQJxAxMC/jIj8r5kCGXPC3s+L+AJz6XUFoB98bRZxFnDqZjazrSeF839c+5CNMpaMd/wwS6pvHfZLGiGPTX/K2VKUaRjV/MYnPB1kzb36dqhm+vMk9GDvb8pCpVmLtYr194EiV8QWkYvVzZeefIjZrJv5ipUKwBe6T7+6iuMbd4/Ddw+P/i/L3i72EOUkEv/QDKfwCUf4HaQztLpqGZAVcZrCkKf+8ATuubsnX362AP8liCOUxYjo3eD1K4/MAaXAT5SqGK2mDsBSfeQVw2jl8xbKXxJ2nvL/OQgry2wmXJM/rEabKCcw9GCdNdPUw0g7yuImTJ0/fEabCCQb2JJFsmX1f/tZdBxAnA/8NIeC0me0Ur41o9NiujUo15DY4mWfLWoCLEp1aF2bYE5HX+7+5xssX1bVUpR76+m0GPNfy9/N8Pp1hMA4yP2seggvH0d8/TxmMnIqAJRLlavRzAZ3RtVXGoo0NUa/GpZG5bhXuvXw7lPS2bPSO8V1/ycw7tl/gJiSZAlvtNMdHsY6Jj7OKhmRThCGm8wS5tx7e5QI8L1APorjkTzq3Y4aHbKa9Btd3OtSV7rcuGg7p69u15LTQs20CJdVH73gRRpEmPPm/RsH/tNypmuKaf4CY9uo65RqzumKMZQGhaVINQiQTyzDOZLpmg4nKmNT/HsbHW9lQcKw8WKfXNpYPfA47uG7mLOi1fRjeM2HJ8Z3l8AmYu1WShcpr1uaI5u4NB93+Jn1/HUlHdCgcv9AYeanHlI27NO0X39dpujB8ssVCUe9+HXLm3Cj/125bGBdkKQpnNFx/0BiZqccP/IsFbmVDMveiG8JC471jzS4TbPY2pe5FucF9gpnaEWsEzxK4CLde3eTKjr0k7umHUluNZbTwZpNWnVor0H3ZabNdwID8Ea+twFn8y70fWYGF1ymTowiCw2j2XaXqdrnF9IqqBM3K+1sJzfgzAnmxuw81S8qVscJTN2FHjOghzUzqzN8c7Me+FpzOyegr7dSqXgka8bcsS8W33CtR+BtGS8Hf5B9aQZtBWEykEGpTFd3nqRmUeyT2+VOW2R6C4ikZt+r8LFHG7dD+t6/qDvZuCtjzt1n0NXPNbrtJGse2UXLTlqZa5cM3kvo9rX69XfJ+h97dagqaDnC68OGTMWBzYzajWlsy3tbW4evObIGUad3YLuluQzndyM7RbbIxg1BFloPeWjr6qbTbYCvzM/MJZTqIRIIQ6uL4i13R5qlwHsG/zkU58lzFrQl4PanyHeLJAAqP3cbBuU70IrivfYifsECtMtDc1WrvuxW8Im+eVD+aMg8+G3FBNgi+S+Ny2RMSzmiIRGqu/FCkQa1GAC+Uv56cR3txBVBYyOCaVUFDb0btYV7r+qxv2qaWc+mwuJvB45n5zTbd4uFFWNKGJIRpR64R7BKTp2PNxXcDl0Nsf3/ThbtjXEyCwGt5aSCyPf5iw1w+Z9WHi3Ns3wtm+SsgCCHL8MUNbKQ2CC3Ykh5hl6wJtoKulGZ0syton+IEWmnx5oiqGXBq1U3s6jd6rObV57Ojos/TsEYpNacNQOeclFZC+RRiPVjpuWLmpzizAth4eycJO7lQG8ypzvijPMylA0jWwUJd0fgmPG57yXx7yHxjCzwQJh15qfwmDr86wcX00GZ3OGZ3+6CmMhvWEgfFkeXlObkXTsPloklgoit/uGsvBvPQ5OYu7sOCzZvWy7n2F83Bq9+Fw797mUjLeT5r6AEwENSHXd9011sjzvBS7tOz3Bx75/Jj4/pH/LpMxjnypI1OKOoVN0L9q2/o5ZITqsAp2RVNPeu8IpL7xA4Q4B7hT5LsTIUyuRQjVOdLiG9RnO/TDW5R2NgyYRRTBBkgColE=
*/