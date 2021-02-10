/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010-2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

    #define BOOST_PHOENIX_ARGUMENT_N_TYPE(_, N, name)                           \
    typedef                                                                     \
        expression::argument<BOOST_PP_INC(N)>::type                             \
        BOOST_PP_CAT(BOOST_PP_CAT(name, BOOST_PP_INC(N)), _type)                \
        BOOST_ATTRIBUTE_UNUSED;                                                 \
    /**/
    
    #define BOOST_PHOENIX_ARGUMENT_N_INSTANCE(_, N, name)                       \
    expression::argument<BOOST_PP_INC(N)>::type const                           \
        BOOST_ATTRIBUTE_UNUSED                                                  \
        BOOST_PP_CAT(name, BOOST_PP_INC(N)) = {{{}}};                           \
    /**/


    namespace placeholders
    {
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_TYPE, arg)
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_TYPE, _)
#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_INSTANCE, arg)
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_INSTANCE, _)
#endif
    }

    namespace arg_names
    {
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_TYPE, arg)
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_TYPE, _)
#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_INSTANCE, arg)
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_INSTANCE, _)
#endif
    }

    #undef BOOST_PHOENIX_ARGUMENT_N_TYPE
    #undef BOOST_PHOENIX_ARGUMENT_N_INSTANCE


/* argument.hpp
rvDTBmgPC48CKdfQxTwCfF6sTk+PsfMFITeo2LBoUNxhXPmHThPjB7t/b6lXBBkWPcMD9trtjE/VvSwDjIPNCkHAktiepfBC00MnwwLUDuN5keNGqI6b+JCJFaCtc00v1Id5cLDh7rRDJjcboNuS9kuyj7wqTq0lm1TvWp5xjpX+s1JsWdF1+wB51FLfBJgjN97mC6Ah6J3Ntc/485fjo8dRiM8vNNsRcUVWjOSSjgnNcxKOa3qKVZ71zZIM/US7BjAMiExDgGoAsESGz5sJZMLbCTrcoxNXDjI6cUF/4qFWMZtzlb+RQ8AizLUcBWYlFsPUL9fHDzBvP61ZQclhVu4gcMGEYAXrl2eo+IAOt70BPqukfQHvXTC+MNhQFPAztsyWEHGpnWHmlbsP+y6JNVCytscx2xGhqvY0NehKEPgUE3sRZoz/kBmlmXBEEcgsWVLMgsV/9WSn4vFXD3ZOTt2Xl69eDc/4gdS9YSf2FBPltTPK6lAHrrHL1dqJfVI680IsLtYIBPrqEdBD89zxeO8X92LvtXs0PFE729vmGMgHOTr91b4LqOm3AZYIqVyKpmBulHlF1YHpUY8GcpsepzSRgsJNlDYpTGmgnOfeZB1ltUeGSTaNl+d308Akfm6dWaTV2YZpsDwseIYv
*/