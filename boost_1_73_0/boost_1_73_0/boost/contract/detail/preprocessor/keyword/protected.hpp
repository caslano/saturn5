
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_COMMAprotected ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_EMPTYprotected

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PROTECTED(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `protected` (this can be
//               checked with `..._IS_PROTECTED` macro above).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_PROTECTED(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_EMPTY, \
            tokens)

#endif // #include guard


/* protected.hpp
wQGZXRUeWNViEnkhpAvLwd4nFSUR/96exegkCKfjKzTsex1ejm1jsZC4eNMg82xRlnqtJfTZaq2Kt0/hnSLq0qa/0LOUFYJN39X9OkYW2gK1NPS2JZeoZbPBJrMk6BBqk01sqzkV+MERdq8L/QsLNwFpwh7a5Kh/Zsvp1CeFuZL/6OBpaLbhWb8roqjMmZBez2+Cotm3mnYNgCkjR8nrAq6Du3EaWuxTyqQy+2pQIHtNtGnVu5El1cHFkrY4Bs21YXYW8tw/Kry16h3aDo4Kuhj/56qrGMHCpeHIJxpNzh3HVm4ZZZFqxkkaTdLrKE4cDO3QX+/RNPQmioYRwxnEf/A8WD37xm39laZB+Pb27OLFd68Grr9dBi1ksVP22aA8ojLWVsaG1EOCcrNMJpdWgioksXGQB7VXqKpSW/01jnSwRF/i6PLy+9dnF4OnpCbRIrV2AQZ4PbtECXqDsY5K7jqaQNcgd5HHusuTcMCwPMd3FqD4doNUYFEqLWl7eqcN3ww7jp8Ey2niERrtwnwRJdEomsbeJJn7EN/Sf3gb4P88mr+0Z8b/DW7n07GdcwgSIzLYM8Fml9pZQv2W8nWGHJcalTKdCdFNOUdOnw4673ccT+4AelcjUQmcJv29as2PuN+JrHcGy/BTJ0ob
*/