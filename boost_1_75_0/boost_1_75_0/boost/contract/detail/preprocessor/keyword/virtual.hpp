
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_CAT_TO_COMMAvirtual ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_CAT_TO_EMPTYvirtual

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VIRTUAL(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `virtual` (this can be
//               checked with `..._IS_VIRTUAL` macro above).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_VIRTUAL(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_CAT_TO_EMPTY, tokens)

#endif // #include guard


/* virtual.hpp
SzuudP9Sev6u/ff4R+3/cqP3D4TgH8iq/hpu7vS/FW7uNV/015ATnv4FITRas6ovu+6yOe/fijnGn3tV38vpHOUviPnJb/rbbv2CPPqH+uf+of62b/ra20x/Eha8fN/ynX74j6rbNjMz22w7fx6VCZu3fb0pfPtv+nRfxdSQIsE0RWHnlUtb7Oy2UF3ZeXHHtoRCU9xHv+lLCH/R9glP4GBi1yfbt2+fzJOrNDRYMjKsSZ6BXoIh+lD4J31SikiXmH37kOLhw1lZWSYC64PWr1+fdZWzhDT8Z30fimIXmn00WYcO03yRw1kC69fHxDDEPJb3Ffb5nb4PhSXxvkMCWTjtq9gnT55g8XcErY9h4OSkka+m/VHfh0IBSyMgkIWUyPZtOJJx5IhccPAGTU8aAfwNV9UpftTfv4mGJgg9/Ni+I0eCjoaVqIds3HhDXGcLmSYN7oas3TyJtd/p+wi7PQkSOEyzL2M9+9pqCiQ8jjy4IlLwsMz6GM6sS44/6AtvohEwyaLZkBXlk+lY7ePz1cA+4Zn8SU+sY55E/chnv7dMEFLP882s9qH7QXwoOBgOZQXxk/6gL6xIlnXYVp5i/29Prt5PgZ93n8yKfftIKH60p0/1U0+y9T54dUSCIjOT4g59CRMpXv8EWxSFz+/my3ETWQZVpg+dtCMFxf4D6oJUxDLZ2WYUSL9a5AwTUv9OX1vY11fFUZWG2JHO
*/