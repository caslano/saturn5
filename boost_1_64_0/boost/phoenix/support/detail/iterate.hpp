/*==============================================================================
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PP_IS_ITERATING

#include <boost/preprocessor/tuple/elem.hpp>

#ifndef BOOST_PHOENIX_ITERATION_PARAMS
#error "BOOST_PHOENIX_ITERATION_PARAMS not defined"
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS_SIZE                                     \
    BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PHOENIX_ITERATION_PARAMS)                   \
/**/

#define BOOST_PHOENIX_ITERATION_TUPLE                                           \
    BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PHOENIX_ITERATION_PARAMS)                   \
/**/

#define BOOST_PHOENIX_ITERATION_START                                           \
    BOOST_PP_TUPLE_ELEM(                                                        \
        BOOST_PHOENIX_ITERATION_PARAMS_SIZE, 0, BOOST_PHOENIX_ITERATION_TUPLE)  \
/**/

#define BOOST_PHOENIX_ITERATION_END                                             \
    BOOST_PP_TUPLE_ELEM(                                                        \
        BOOST_PHOENIX_ITERATION_PARAMS_SIZE, 1, BOOST_PHOENIX_ITERATION_TUPLE)  \
/**/


#define BOOST_PHOENIX_ITERATION_FILE()                                          \
    BOOST_PP_TUPLE_ELEM(                                                        \
        BOOST_PHOENIX_ITERATION_PARAMS_SIZE, 2, BOOST_PHOENIX_ITERATION_TUPLE)  \
/**/

#if BOOST_PHOENIX_ITERATION_PARAMS_SIZE == 3

#define BOOST_PP_ITERATION_PARAMS_1                                             \
    (3, (BOOST_PHOENIX_ITERATION_START, BOOST_PHOENIX_ITERATION_END,            \
    <boost/phoenix/support/detail/iterate.hpp>))                                \
/**/

#else

#define BOOST_PHOENIX_ITERATION_FLAG                                            \
    BOOST_PP_TUPLE_ELEM(                                                        \
        BOOST_PHOENIX_ITERATION_PARAMS_SIZE, 3, BOOST_PHOENIX_ITERATION_TUPLE)  \
/**/

#define BOOST_PP_ITERATION_PARAMS_1                                             \
    (4, (BOOST_PHOENIX_ITERATION_START, BOOST_PHOENIX_ITERATION_END,            \
    <boost/phoenix/support/detail/iterate.hpp>,                                 \
    BOOST_PHOENIX_ITERATION_FLAG))                                              \
/**/

#endif

#include BOOST_PP_ITERATE()

#undef BOOST_PHOENIX_ITERATION_PARAMS_SIZE
#undef BOOST_PHOENIX_ITERATION_TUPLE
#undef BOOST_PHOENIX_ITERATION_START
#undef BOOST_PHOENIX_ITERATION_END
#undef BOOST_PHOENIX_ITERATION_PARAMS

#else

#undef BOOST_PHOENIX_IS_ITERATING
#define BOOST_PHOENIX_IS_ITERATING 1

#include <boost/phoenix/support/detail/iterate_undef.hpp>
#include <boost/phoenix/support/detail/iterate_define.hpp>


#include BOOST_PHOENIX_ITERATION_FILE()

#undef BOOST_PHOENIX_ITERATION

#undef BOOST_PHOENIX_IS_ITERATING
#define BOOST_PHOENIX_IS_ITERATING 0

#include <boost/phoenix/support/detail/iterate_undef.hpp>
#include <boost/phoenix/support/detail/iterate_define.hpp>

#endif

/* iterate.hpp
BYEYikGo1aOUC7Up97iUK8FgfELKHWMolXJ7ZH9A+f8XpNxAuT59ELbEwdgVh2BPHIrXYDTG4DCchsNxNo7C1XgtbsHReBuOwwfwOnwKJ+NXOAOvIY9ZOAFn43xMwEWYiIU4F7djMu5GB6rnl8qcTA9G25xfKpft+U+xMX6GIfg5tscvsDd+iUPwK1SPb4Qv9Hy/zGty3uootsFjOBxfx4n4Bqbhm+jEt3A5nsAVWIba9R4S57jN9R7daCf1sDd2wj7YDQdIuxqIo3AoTsNoTMFhmIpjcAeOxQdwHD6EE/E5nISvYwxqx52zPd8nMFqO547B1jgW1fqqkHKbbOrrW9nP/B5HYQVehz/iZDyHifhvXInn8Sb8GQvxF1Tnd3GO5/n9jczvb7ExfocheFbm9/fYG/8l8/sHVPcPKmS8q232Dy74y/Xv2BZrBbA9AHVwBNbHsdgQ4/EKTMLGmIVNcBkGYAEG4jnswlCcS1ysL3HrYCuJ+4b0S2/rz/flej5+2kLmT0v0x1ao7RdWUa6NlAuXcm115SpyPbeHE7I/WYat8R1Ur7sNz6McrrW57nZ1PVm/YTNcgy1xHUZgIfbG9TgBN+Ak3IRJuBkX4xZcgUW4Crehur4uy/O8vv67XO9/Bpvjx9gW//Ff9u4GLooyD+A4piYqKiIioBYqpuZLqPiaGeYbKiqpp6QYrOwiq7xs7KKoZGhqdmliWalHSYlmakbm3VlRUVJZUVFZeZ1dVFZeR2WFRUV1v9n97zC7O4uL5b18PnL37+vOzszzzDPPvD2z8wwOxg9wOFah+jzGEu/72/CmUu4Ygl1QbU9e4r3c75Ty24Lt8C5tO8US78erpVIvcrEjLtO2KzYw3S0y3XqZ7o+a6YqWeH9OZUA7ed4W+2KU9jn2BpZvgqQ3EdthbH16LIT36RJluvky3fWoroel3tdDE1kPF2EINtWuh6Xe20U6yXoIxQAM066HBvLZXM6TL8Z22AKd+/V8me5Vnf36Q1L/92IXfBjj8ADOxxJMwUelfh/E1XgI78Y/4278C+7Bv+IhPIzl+KTs10u15xm53uvFB1LeVVIvPtTWiwame1Ome0umO4Zqu3Gu9/acF2T7exFb4lHshS9jX6zAYfgqXouv42ysRPX8eZn39dlN1md3DMAe6Lwui5fpSnSuy6bIcSMOg3Ea9sDp2A/jcQjOwDE4E+PwDzgPZ6MR5+AynItrcB7egYl4L87HhzAJ92Myqsu13Ht5t5Dy9pfybqltD1/ufbtoLdtFAIZgG1TvV8t0PfR+Fyfntz9iO/wJO2IddsOfUa0nDaTvJ9tJEwzBi1A931jufft6QNbjTmyHxejcvqqWe9++tsj2dRd2wa0Yh9twPv4JU7AQV+K9uBp3yPZVJNvX/bJ9PYCHcCeW4y7Zvnajs15VrSA/+KZOvZos13MzMARnYjTOwlE4B+MwAU04DxdjImbjfFyJSXgXJuM9aMB9mIIPoxFfQRO+hgtRfY4zT85ndY6H+6Q97wAOwkdwKB7EFHwM8/AQynMN8k5/tlmd5xoukXp6KbbECAzE7tgHe+BEjMQpeBlmYC+0Ym/cin1wL16OB7AvlmA/PIL98SgOQLW9faX3/jT6Sn3qh/7YX3PfpkimC9fZDjZJ/S3AdrgZQ/BODMUt2vq80vv17beSfg22xDOS/h6iUqb7XKYLwkLn8VfqzxUYglFSfwZK/YnGiTgEr8WhmIXD0IYj8Xa8CrfgaNyOV2MRxuCDOAYfw7H4Mo7DChyPn+JElPKiInn/nfyhJvJ8DLbDv2I3PIyD8XH8BmuJ+HzX+1PK9lrtPF+R845bMRhvw864AbvjRuyDBTgGN+MEvBM=
*/