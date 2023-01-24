
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Peter Dimov 2000-2002
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if defined(BOOST_PP_IS_ITERATING)

#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/enum_shifted_params.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i BOOST_PP_FRAME_ITERATION(1)

#if i == 1

template<
      BOOST_PP_ENUM_PARAMS(i, typename T)
    >
struct list1
    : l_item<
          long_<1>
        , T0
        , l_end
        >
{
    typedef list1 type;
};

#else

#   define MPL_AUX_LIST_TAIL(list, i, T) \
    BOOST_PP_CAT(list,BOOST_PP_DEC(i))< \
      BOOST_PP_ENUM_SHIFTED_PARAMS(i, T) \
    > \
    /**/
    
template<
      BOOST_PP_ENUM_PARAMS(i, typename T)
    >
struct BOOST_PP_CAT(list,i)
    : l_item<
          long_<i>
        , T0
        , MPL_AUX_LIST_TAIL(list,i,T)
        >
{
    typedef BOOST_PP_CAT(list,i) type;
};

#   undef MPL_AUX_LIST_TAIL

#endif // i == 1

#undef i

#endif // BOOST_PP_IS_ITERATING

/* numbered.hpp
fITVdDnQq0AwPwBzfkoz789YIC5NrOPnPk0uURe2Dt4TZoxgEKE/RrJxohcSwrWYjOQ1UdH3uC+yV+HamWzianJ/Uo/ZRfch528ltpJR8iOy3ZZnOnGM08HI+fp8WN8hGq9i3YQIPtif7pEI7lks8DtZPhZXmofnU8Watxm7/fi4RjZbn05Zaiyv5hHxTh2QOa0RE6iZTlmcOOs051QM+3OeCLgplSo8FYgmHJSYF2zOce+y8HWO6VjRVymd9CTlvsX+5TO0Cwfsj9n0Lu75aHWs9yrti8khasf5ambyrhh46OrWjNl8W35v9VPbxi2Nc50eqyaDa9b48/wMEb8qWwDKdca9xSsqM4z/HeN0SzZImavw0WIvc+fq2O7+6d7DNxz6A4rDUXuPMYn41E1i/PW+av8i+57jVcDaoORqVmJOAgSc9Tox5jh6Wy5M0bYuRQ1YDp3e3HnFecUae5VemQ27tOQU5kmI47ABOAByVUisyCvZmwRBeQngEk4757wjUk79/IcseyULMPryTWdeMjkXnz5djDsv7Q/L1djLg7y41byqGefz4K0T37JyFreNn7GMpyk8nt6+lzcxcbKqrco+nImGs79+J4Bf4kZUfVNWW0IZKGbKJG/8tRPXcyaVjNb7qVrSbNWsQD9J1ONdlGQ/HQs7kj2U2Wo2ieOp2diM9lTSgW9u2EcNf3JkiybHMaX1MvKhBILwXM8E
*/