#ifndef BOOST_METAPARSE_V1_CPP11_NTH_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_NTH_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class K, class... Ps>
      struct nth_of : nth_of_c<K::type::value, Ps...> {};
    }
  }
}

#endif


/* nth_of.hpp
wsXGg4umTGFxVeDfIwVYTnCNbTZXHs3K9BLGe/LqE7CFM9NPtSMr1HO+BOqUCN/UXPmeaP5m5JWJ7/ViRjhmXMgxAr4vvU7JR6lPtua5YtTKjH1UARJwz/OBP9CQL7A32PKyHFsxbt+rNuUVbbyx5WuiJil94XcgRVXTjPtKXMirjBvE1ib4iRERmTP5ZXfcnSt1niR5iTWGQla7a7fvon53i4h5kjwSEYJTMowDIYcMM8MqkqLVS516VAGNLIGZ04pvHQhcqAoXbqOFG3xCLBRvXtzKm944RJH1LpkkRf1b9tjBBQh7QUxd7jMeZawFbj98QAA8TVFOsGjr+b1e5gCscsJhIcCb6lLHyP4juqTR5m8spSkWg2XzeWJdahZHb9kNir5lwnjBOnKp/yUGy6bwGSdnakoly6iXN/eQhaGIyO+P/82RT1hjBirdFOxyFinCaiP/nQvUdcb17UjMZz7t8tElVSPQj8evfl33Qb7+UdpDP5lv2PKv6oQz4hsutEXX/PJEkzqh0gtcUZaeqB+ErvMKx+xk/sps7WFXFdb28PAEQXPjryalbg==
*/