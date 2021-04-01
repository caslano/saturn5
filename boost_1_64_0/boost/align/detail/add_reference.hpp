/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ADD_REFERENCE_HPP
#define BOOST_ALIGN_DETAIL_ADD_REFERENCE_HPP

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#endif

namespace boost {
namespace alignment {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::add_lvalue_reference;
#else
template<class T>
struct add_lvalue_reference {
    typedef T& type;
};

template<>
struct add_lvalue_reference<void> {
    typedef void type;
};

template<>
struct add_lvalue_reference<const void> {
    typedef const void type;
};
#endif

} /* detail */
} /* alignment */
} /* boost */

#endif

/* add_reference.hpp
O9yvbrYflRyh829+OiQIaTx2BqSrLO6bqhJAQBrCMX9rSa/ovFz2vKiI2/9eZLu6+hmuVcY2bvXEu600PmARkVKJso8FPL15WVFDUX5J9BGrayeVsEqDsQaYmZJN48Y5ZkN4QEtUMR5BZe9eLHtHN72SBGMme+78JiRDlnSe3sC7n/k0mocuhKKmEJkqz9dLSZmxJSig78t0RUyKwBD8WDfo3wafhai8lnJjJIGOW37YayHchAPafrw5Sf6Ny6GeIqLPKovKoSwu+6b1zIkFrdhmRBOB2/i2ma8S4vVZ71pDYDKUpVHCNNTLaaJZ2W/TkKNmMavrrdvKEhVdLLRxfqnEzUap80K4+4oBChrkIe25xgTWK4176xHzkfSX/7OTRZ1jf/WtwuZadDVx6Qg+7tSmMsOVVJOWviQNqZxAJ8XUSINCQnaNNDOrtmBkCkE1/Tjyf3Hq7PumoFxfl19hVaA20oroednHbx8lVp3bvbGj2wgHUhFCQfYORiuOwo+UaTZdJKG6Uj1Cl6R+eqkWjgS3yvB3chC80oqE4r5AVVHLjbCAByh5Pc+x5g==
*/