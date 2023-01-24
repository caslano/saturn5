
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/variadic/size.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_1 0
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_2 1

/* PUBLIC */

// Precondition: A macro named `cat_to_comma_prefix ## token-to-check` must be
//               #defined to expand to `,`.
// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
        cat_to_comma_prefix, tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_, \
            BOOST_PP_VARIADIC_SIZE(BOOST_PP_CAT(cat_to_comma_prefix, tokens)))

#endif // #include guard


/* is.hpp
Zwf1UQaa7FUJ1sM/n6kIp/6DPoe9PYewHrs3HQeRZZQWXvn6ruyjmTg9lepq/Ii+19eTRMJBF6knqafiyKeotapfR/G9ob7X59+BkwP8B5DwE1HwXUH62ba+pH+mH1mEl8gd/EQcHESbDvhtRfon+Hz+TH+T4iacKLquLbl3NEbOQI+OODub6Qc6P+gr0gsJCRXQi1eJ4oZKE6l4wCB7X3G4tM+f6NOvVUVi6bpWcB/bhuwTkZb0IjKska6RHD60d7460/f6qt5ncbJWtejU4esZDkJr125S2up6ltFb1TXSHk1+9R1aH+Ha3/TPlsatCmOBVHaMkHdc3NpQprNxcaWlG/M3MorRb4qU5PheP+54/hfZSH/mqOVGVG7cGPKl6TgTU3w8E5Oy1W/6+epMX4WRnXoj088Sr/69frwD11dRr1NX5/oDcfDZ85u+ukHdVyFxcCCp+1lIDL7XJ1GT+hvZq9b4nf5e6p1/I1HXir/Xvxb1t/JNX/ZgIO0vSOBX/TUWF7R/QS44r/m6Xnv9knxdr//hfuD/hsQ5fL2qwO3i/v97q/+l91Z/cU6lJJT083aOQOdFQ3RGNUTnqXZ09glC+3N1dE4dR2cEG3UGwhh0BnNG51NtdN5UQufaXnQeUkJnwDm0ty9DZxP3JD/nGHTmsETnA/nR3vZ6mR2EGTE2ukrqrFtH0RnP0s9Q3hSdgf4Pe+8CF1W1BYxv
*/