
#ifndef BOOST_CONTRACT_DETAIL_CONFIG_HPP_
#define BOOST_CONTRACT_DETAIL_CONFIG_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/preprocessor/cat.hpp>

// Turn off BOOST_ASSERT(...) in lib's implementation (always on by default).
// BOOST_CONTRACT_DETAIL_NDEBUG

#ifndef BOOST_CONTRACT_DETAIL_NAME_INFIX
    // Do not use underscore "_" to avoid generating reserved names with "__".
    #define BOOST_CONTRACT_DETAIL_NAME_INFIX X
#endif

#ifndef BOOST_CONTRACT_DETAIL_NAME_PREFIX
    #define BOOST_CONTRACT_DETAIL_NAME_PREFIX \
        BOOST_PP_CAT(boost_contract_detail, BOOST_CONTRACT_DETAIL_NAME_INFIX)
#endif

#endif // #include guard


/* config.hpp
U6r1V1UtEM2a7EDUCpSAVlIbtL0Na5GzQq9IEW7W7YozWdqPsDBhlY9FA5Jy3odDV0alKYFC3LNla0uoET1TepGikjrbthTrJ4ZIax+oaJsK0yEtaJcLJN6Gtspp09l3ROyz9Cx3lH+nZY/YcxAVooKBG4MfD2BFJJM23PjJVTRP4MadzdwwWUB0CW646ONd++EFaoNh1gboXd1QiSgaYOuaM5o/Sf5DJ91ykiuYzGdBNE3SSRDFXhxNrr3kwk1cOIHB0a/wZ1uhvI9eD2DA2Ur3H06dk1PnEDf0W0qJ3KWSKt1pvFFUEuPGVxC6HzzrW8GXr6AWrELCUZxSmn5o1qXIPuGUZFxIChnhfEWyT128eBFG09iPrZ9YlfE2p3CuARhNlu+sLlcmcP9rXEP9BQ5KVAtH0XwDkw0bwXI46HGNzrqsF148mfnTxI9Ca4pIgcCy8HubZTFF0DgfW8Y5rChKSYk20/Ja7WDPVydSUyTOopniRiqLNLftmlZqP9tdzfv6+8pxCHR0VVqY9Rngl/NworENT0YIxukhX7rzILH0aOe0IC1XsCG8pQ9HAJ4HZE01+fgSzoPAOE5nURJNoiC2XCyH3mUUe6rl/7b77P3lfpgGnuVUhSUVUSxD5OpL2EPDYIaqrVRtm0aY
*/