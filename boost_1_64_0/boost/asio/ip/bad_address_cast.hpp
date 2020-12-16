//
// ip/bad_address_cast.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_BAD_ADDRESS_CAST_HPP
#define BOOST_ASIO_IP_BAD_ADDRESS_CAST_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <typeinfo>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Thrown to indicate a failed address conversion.
class bad_address_cast :
#if defined(BOOST_ASIO_MSVC) && defined(_HAS_EXCEPTIONS) && !_HAS_EXCEPTIONS
  public std::exception
#else
  public std::bad_cast
#endif
{
public:
  /// Default constructor.
  bad_address_cast() {}

  /// Destructor.
  virtual ~bad_address_cast() BOOST_ASIO_NOEXCEPT_OR_NOTHROW {}

  /// Get the message associated with the exception.
  virtual const char* what() const BOOST_ASIO_NOEXCEPT_OR_NOTHROW
  {
    return "bad address cast";
  }
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_ADDRESS_HPP

/* bad_address_cast.hpp
Wpz5i/latcWSvxqdv0g9ecZ0DvJH+vhZ07fn78hsZ/6eUPNOZ/5ivt5tteSvTvJn15P55znIH+njZ0vf1uf2Xxwxjsh5wih1y1/15prqTbVlnnkTPVJJM8dU0QmPq8Sxjycfbed4kmkbN+U4EefBhkvc85fjmr+6ms21dV55QyfyfCHxJV85Efn6eDvzZT8f6GPY72EWesxbnHmK6T4HejJOhuYtohNui8Rpf1vMtM1ZzLTtz6nnOPN0UM1XnHmK6R5JkSVPJZIn0THzVHQO8lQieZK0bW2veY77/ZUSR542VwXvsLjeYyG+/R5LVTvvsYTs2jFXIopdF4ldOyPtktfPCPZ6Nis6Ofbn8PJc9KC9P/C8sG27Y3k+GLxf1D3YbuY5v71Qp8bnUvn2gvmmuH7ILO98RH5zQeKTSvieT+zfVCA923chJottu1xs+1wO16mrHbZxM4sPV1RWhu8nxfBNB+uxquc7j3Ufx8p3Hqt6U3XUshCdTN13knS4ir5uc9UaGQ8scczn1THY6yyv8BiepP3M49jquGCBM2+fJW9FLnnbXFvuma8isZlwWc9ULXtzyXgQkafl7cyTjN+yHodjRNRVi0t+tqn71Nb82LdOkbUNjjyh0/52e7PH90yKFjrtu1OND672mU233W231eV416tn0+7HM7/vUj/BUR7otP/7LqTn2o8PLXLa10Dco2726SboWV+ikylrUZxt8OhZtEGO52iDHMO1De4ucuZpixo33fIk36vxKHN0on6vhvD2f6+mfkLb36sJ5alysTNP36FMUtZY82RuyVJRJfcctzrqSXQkT+tdxgoJD7/3fgZ52upST+s9xorAEmeedqn7ce55YqzwzBM67R8rSM+1bxxwse9T2FfkZp88s0lT9ukyXcOWjewKaR2jI2xcGkO5ZoZs1GUoaUbYWXyp084qNea622mOMU87yxGd9o8xT3uMueOKnfbdpMZcV/s4hUeta9GTc/hd7udw4rT/HM4xHefwu5zncLP8k5a6980m9/wxhnrnrSl63yS8/WPomfTNYy55OoT+Ubc8yRjq0abQiTqGEt7+MfTpGL75FZprzbrMmae7cxjDbXlq/3w1dJw+y5zHuUfNjddaj2Ofqw5yzOkkvrTzb7u3c+K0v50PcpmrftvZzs1v6x13ydduNQ+PyBcN3DNPxDXbwuvOOQLh7W/fg1zmqRxD2re9jo4sD6awRPKxAGlAvyiYl3oyIgsqV63ZWB28dr0xcm8wsTUcJtffZlgP1/cFUmG5Dp9s3/flDPaZulH2NVHuiaZbrtFD7X2l3B/CnoHQgBXqnrMjj3pfLV5udt07SOLnmWuOT2j3W17vPEn8MV7vOkr41eLmPcEy5c4O3ldL1G2iSvYyMtdF/0br/EG7F5tpDDffT0yS9xPVt0MLfbjR9et0BxidcMl7i67v+mXCsTruR7UN3fX7jrp4avkR1PUFdVuzlA83GwlS/gW2NOtUouZa/bk6zUodXpGmwynu8D5dV+nwfO4wxImfz/islEXAiNd7VR2lnT65QvYiSlgR6EQ6kfsR9ZN4rcQrDn7PdFsgIRDwF0XZk0h0Sq6QPYkaHkoeIpsSjWZTom5xse9JdLu2OZ10u4mfPR967Ygcb9sV8s5kl4ZGx/sGtP36uOjfJy2Jk++T0u53xtn32Nod53wPrTHOub/tPvxoZ/hJO/N4x5C4ut67az9pD5bnV636WLotmN+WPH4Ovy15KEH5f/uF5b97sLL38b/f0Tjr1UGP/8n7m5N/1fGbfnn5gLtLHupyS/IRX+Y7e7/6//ctSq9vTtZNU/6b7/hIwYF3u99oPPH+Fz6/bhkfw7t1kPJfsf4=
*/