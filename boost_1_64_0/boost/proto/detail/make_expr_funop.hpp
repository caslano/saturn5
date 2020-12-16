#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/make_expr_funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_expr_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr_funop.hpp
    /// Contains definition of make_expr\<\>::operator() member functions.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                     \
        (3, (2, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/make_expr_funop.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct result<This(BOOST_PP_ENUM_PARAMS(N, A))>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
            >::type
        type;
    };

    /// \overload
    ///
    template<BOOST_PP_ENUM_PARAMS(N, typename A)>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
    >::type const
    operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, const A, &a)) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
        >()(BOOST_PP_ENUM_PARAMS(N, a));
    }

    #undef N

#endif

/* make_expr_funop.hpp
HwehgOS+9NQkPhcXaZnY1Ij+/Q35Rdc4Up43ROURrMxlVsmcY5sfH7gOh3s08qG+X0l5PhWVR7KiEInOVMWmJ93fcHBMDuj69LukdwYTScGV4CyZL0sKDjkolOqLLDuZzF15dC9PkyyDm1cY906QgVFddnHcP4RHOvNVbuHU45MczoL/qiS87/FYhmCSpsmyJsO1FIYZnujpdZOOWDrGGt67u5aysbYpkF+Ch1d4wfa6+KQFuj59UY+PKnXCa6n6fPCochKfj/KebC+1mSysPwS2nUEWa6zW2cW3wm9GfBrG6ySpG9FQ+1mqcoy2BrSNzuH4oLxqpupc1a5uvpPQ0lHIhbfyP/f6SnMtmpQnbJNqLPh+wvb1Jdu5HOpE+uq2ItZB5jzJG2EwuJ80/vgbdqFt2H6IyC3Fc6foxSdORZGJRHaM8Mi9nBXyOdvjkxfKNrkuOz54zO/z6d0ZRXymExCaLeV5x2fzeOpE+zsncSJ2fM8UPV9qma0zXVQdL/SVE3Mi7Z0EnW8R9XspC1vkJmOgKI2SDzynPwjnAU2zJkyqbcYrdvaiB87O4f4V87a1NiaVdqHp+uffN4jY7t+U1iZlWjKsFgj/UIO+N+0LvNuJXtzupE6VKmrUnUAhDI0C0GOVhHkmejFuVVpDkLSOl28t9GCFE3bdOMEJmOY+rYs3/VfK67TOea6z0jXJas8Xwd/itkubpOYqVyzogboz0gWfZh/T3FDG7a2FVblO2Na5014jdEma28ZpSpVVqi4008n6QprwZi/j8VdXdWlNXTKigBon7fxIrcb5qcLkFbgsSDaNe8/ybbe206V8GN7taLq1PAGzPC1YO7YxjxBbXkb2cFXNYfKzJ64F8/xYPyiPeEurRNJkMJtSC2dTXFsCvqL4MzqVjVXceDwpTyh7E/Gv81QWNhHMVfHcgo3uoezphJmiEcJUDG/xZEXHd9v+HTCcQSJeEIczk4muM+TVTSGw0F3cP8NblIz3q6zKs7zgks2Vh5fZmXguRC4l4/nIuZEwzsb/83TsfKf9plceK5SsRKaxPNTkAycnqn4U+L4g4zuKTFMr08xigZbx6Jfnzs5v2Avu4N7WW79h7l4HF+H59xnoK7ffUS2u+/7D9nswC239JeXBD4R3zDXYVBs6qVwaoKGPsMZWWoAPq/D9NujfKdWVCt/Rb9emqlLwWYbf0feWcxEl9UbHB/1uGbvlVEPhO5bpHj7fDeXK82QlDU1zz3ma1gBXmvD9XhhPyS3TFH/v9nu9qdUgT0QZvt8H4zLJ5GmbBH8Kv+f20sZm9/2++H1TCcr/fu13baApKJ/7+7bYbN1jke8PhO9zzVngc/v59wd5f21JpWXAep9gPqaU5B2Ph2NZXLttknZ7BH53/JNNG7XbIwMtt5WEdvHfH4XfvR82W+tNKFegP7qjJxQC/uu0oz/kejCu0CrN+wEBv1qFoz3V04boIoT6SNq9gTvnAA1cgRCfSs98OHyfu3AAXu476qiF796HdaDNHktp08PrhtuB39kUaC5G8eXJzjWSzxeeOf/uz82B1+6z59/RshBsDOa0m24DDVSniSRh4I0XV0hZ8xHg/IvnYD4/7zev97uuAG2JSjHxlTIbUwwcGDvfT6f2gDbZmyuFo3OoEFd25QDo/qYHqZ2R8IT6l1o9Arp3Yg96mKQmnS/f+/d8ueZ5WibKsMiPK7ibIV4ypNqgAWjXcN9+QKQDnQtVW3DzTJ5GF+JxPoKmESWr0oZXuUijmLX+nBk78sR3Adb5lnoq5XW6BI8R1rLxgl/LZyIuyGCbrBHt2gybA0rhabTVK0F2GqUtWSMFdw2Wsp3OwcJk53jbpQcdI2QSnTU=
*/