//-----------------------------------------------------------------------------
// boost detail/templated_streams.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_TEMPLATED_STREAMS_HPP
#define BOOST_DETAIL_TEMPLATED_STREAMS_HPP

#include "boost/config.hpp"

///////////////////////////////////////////////////////////////////////////////
// (detail) BOOST_TEMPLATED_STREAM_* macros
//
// Provides workaround platforms without stream class templates.
//

#if !defined(BOOST_NO_STD_LOCALE)

#define BOOST_TEMPLATED_STREAM_TEMPLATE(E,T) \
    template < typename E , typename T >

#define BOOST_TEMPLATED_STREAM_TEMPLATE_ALLOC(E,T,A) \
    template < typename E , typename T , typename A >

#define BOOST_TEMPLATED_STREAM_ARGS(E,T) \
    typename E , typename T 

#define BOOST_TEMPLATED_STREAM_ARGS_ALLOC(E,T,A) \
    typename E , typename T , typename A 

#define BOOST_TEMPLATED_STREAM_COMMA        ,

#define BOOST_TEMPLATED_STREAM_ELEM(E)      E
#define BOOST_TEMPLATED_STREAM_TRAITS(T)    T
#define BOOST_TEMPLATED_STREAM_ALLOC(A)     A

#define BOOST_TEMPLATED_STREAM(X,E,T) \
    BOOST_JOIN(std::basic_,X)< E , T >

#define BOOST_TEMPLATED_STREAM_WITH_ALLOC(X,E,T,A) \
    BOOST_JOIN(std::basic_,X)< E , T , A >

#else // defined(BOOST_NO_STD_LOCALE)

#define BOOST_TEMPLATED_STREAM_TEMPLATE(E,T) /**/

#define BOOST_TEMPLATED_STREAM_TEMPLATE_ALLOC(E,T,A) /**/

#define BOOST_TEMPLATED_STREAM_ARGS(E,T) /**/

#define BOOST_TEMPLATED_STREAM_ARGS_ALLOC(E,T,A) /**/

#define BOOST_TEMPLATED_STREAM_COMMA        /**/

#define BOOST_TEMPLATED_STREAM_ELEM(E)      char
#define BOOST_TEMPLATED_STREAM_TRAITS(T)    std::char_traits<char>
#define BOOST_TEMPLATED_STREAM_ALLOC(A)     std::allocator<char>

#define BOOST_TEMPLATED_STREAM(X,E,T) \
    std::X

#define BOOST_TEMPLATED_STREAM_WITH_ALLOC(X,E,T,A) \
    std::X

#endif // BOOST_NO_STD_LOCALE

#endif // BOOST_DETAIL_TEMPLATED_STREAMS_HPP

/* templated_streams.hpp
aGLMioDseD2IBLqdaoqKlHtP7Hhfgnh/vPjsuJEJCseNM0F87MLjtYqkg1DbNo9UNtDLXm7jUmS7WQmmCm8dcOWWekwEZmgKK+JgyvEQe4wbSZnWTVX7u+Kkat4FcoTmEdFJEzZNmjBMmv6dk+bQTJq8/M5JcygnDUyS4aZJos+FFDfOIfPsGA6zAy94zsSJNDy30f7Aps+e7TB7tqFWPiSD5JSU6duQPhhC+uhwyQA2JlWUcI7a7mCuV3uOOMuPzt838Suwo3+aiP7JlUqzK74jlGYXEVUDw8JgiqgAXvejwtGmrrmv0X2jnx3AlVoES9WI4ILU5sjRLpdpknjccpJYV9DhcVbQ4bTyxYbxOYDxJ4TBc6FdhFViFQsJBzB+eximHX1uoh0f9fA2OAJa2nvLPeILEhZkccICfQ4PhzlsmuWZGIBLvsvNS/5BseR/ojgSY8DiDfPEDtmlrVqL6MvqFAohbYUNV7sRiGQNM/5MDIcnhiqGA+dFx3J+lUGK35+dCEjti06APc6BnUMyojkhB4gSheAE2OMcWIeM3V8mmQMmyRVJTOx/rLSIyJZ5vannRV8YY8tdugT7mplLC/9Efb1L7+s3uQ4yG33flAUtdccE9DkF9DgDdASV4xTBHKcI5jhFMMcCFbs/cB0NlKcLbtVwTEt6NwtSOC5IcTkiLpviJqfoa27tohQkTCQ5MzwerTNcViB2vC9ufAJCLTNuZILCMxMUnhmj8P9zEhUZnvdU/alr8magFrM2C49jxcpGTDoUKSaGMxGo0SSNB5MhDIcQ547K9o3kM4LJ3db0HhsGutoU4V30G95H8lhLmKlVKdzyeGvxTioieomYtaT31jWJcySX+9p+OncuXdRzbTQZsmeYRm1tDE3Z4a1bRrFAx5RYstuIBErWrhrMF20w9hyUGq4yES6xehHNhWCA12YGddIrJpjmSz6DI/sGE63y4CGgVe4Z1gFapQitA2j/KoIRVxSlVYpg/9r0B9q/PumkVRICf+O0Sqz97LY4+9nMzv2scz9LsJ9NVfvZVLEcTBX72SJidcXc0tjdr3VXO+1R211ta/xd7cHo9sSMNruNjWMS7G2rY+xtM+LvbTN4b1sdb287p3NvS7i3HYIT1aQaeGhHmgSjZVL0RDUJdqST99KO5Du580R1yE9UzWOBbonBkvo/31QS6z5YyS25f8v9HJsTeYVoaTtwKDASK7ciU3HLiqb+aa6fwDMTnvPgOQGelmPTXC/Asxae9cenuW6GZyI8Q+HpCs/bx6W5noZnGTxlJ6a5zoXnW/D8PSPNtROee+GZBU8hPF9kpbl2Z0E+WZAPPJfAk5MF+WRBPid16lt0/jp/nb/OX0d/sfVlZvWz2iuFagQBS5SkvfWS0pdZy/oyWclsACH0ZfKIUsoT+jLdWPQ/HET/q0H0f4SRiMzFCB4RCglqB5e6AGSnYBX4D2hpjdcrVmWAzCODKDkysDG1W2wtmeFmLZlsey2ZbBstmeFKDyCbtWSGSzn/8Obfo5bMKdGpEtamCmvJ9O6cKt/kVOl1fOdU6TA2DqYKTI2hbXRjhuu6MdnmOTFU6MZk4/QZaq8bY54zu1k3ZijpxgzFHCl9u3Rj1DlHbW0wwzt1Y/6Hfrb6MNjTxkqf1IdZeIzSh1nK+jD1Sh+GTr2KwYiDC8NYR0YPHiWCNR4ekjyhWhy/KK6QKsQLuos31KL5Ti+LFk2Tmk5We7a8OPZsebQQxobxOYDxJ4T5j9p9Q6PtYoqyKFWXTI1JjS+ZyoPZHrZKpsLRLWGT2BLCxhd90essZGVV+VtEX1ZjXcH+K0YJK+3UxbA9FwP7b7ow1ylG/l8j8f8Kvqfx/9Y=
*/