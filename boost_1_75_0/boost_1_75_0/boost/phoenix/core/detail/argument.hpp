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
Z3TeOz34zF8661+/4b4TfjU8fMLHf73SZTut0Ge9tfSMdOi0N+kJOQ/uGTz98VLyK3STseAP3sHTA3Cu7wH9FhPQ2U+okjdgGLkArhag/wL0ncCzAq7XITwujD0LvR6uV0FWN8j5FOJsmEbDvu+Kv5OGn4Rzw/0j/FofxL0IfHqQ3wUyfsTfhzSxb942Av02uP4J11bAS4B/k4E9J51FJ1OEbAc9TCD7bgivgCsD0uJPmTVB/t/g5qf6WL6Snvizw7ijf7Z6J0RaMNJGfwgp9HcQ86VHpUMxqQ8HJ3H9SJOyXNyfNPWh4IvAmI6Mrj4eNXhFyi6YQa3TW31JkfT5oS8pal1W8sfo4NnNH8OD5wuPVivJBpcfrVZqW8UO9uA5YSgHz5mDPXieMZSD5wekj61iNu1i8UP3gh0a8SmVvlnV+j47sGRJ448HlqzW+Xj8jHaozqM+s8FnnMaEZgo8rzHq+mAMPoYJA8b0UIySpNv6khR8/DJX34ck6egFnWN6cHdUl+54YEgOZqiiCq8kOvxOZnDk4J4HuBeS5gUn7e8JgG2QwBKcINhy2w0htJWshj8O3EtCsMX+bjxGR644DB3jI9dbYbRqPPIjV4XOPuTmF9P6yJ2mY3iWe+2xPMudHHEMznKPiziGZ7kfD+WI9ouIQRzRHuhPYrB1Zw3miPbjqCEc0Z47mCPaC/Hjl307TXXDfwxYc/pjDTSR
*/