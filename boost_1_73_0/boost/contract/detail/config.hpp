
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
zeFp4mc+sYT9zwC0dNdi7skwe+ol/BXYLhb3PchHa7Pf5xqRzcQe24NUXjl1qtH9J79XxU+Jlc2/2L6AZ9MxmBd0PadwJ2tfqsdGv1WhZaPyJCPX/Kr+lYZ0MZZRHUvvq/0QtX9s3L1rQz99DeL3spZUebMjb1nS74CJvVeVJZxeeNxJ9w4Y/v+7liRrC7E2rfffpkZrCx11TaE7zIC94VDYHx4DB8A5cDA8De4Nz4D7wOiv
*/