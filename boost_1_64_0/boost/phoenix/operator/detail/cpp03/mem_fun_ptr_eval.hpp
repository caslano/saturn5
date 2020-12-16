
#if !BOOST_PHOENIX_IS_ITERATING

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/operator/detail/cpp03/preprocessed/mem_fun_ptr_eval.hpp>

#else

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/mem_fun_ptr_eval_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

    #define BOOST_PHOENIX_MEMBER_EVAL(Z, N, D)                                  \
        BOOST_PP_COMMA_IF(BOOST_PP_NOT(BOOST_PP_EQUAL(N, 2)))                   \
        boost::phoenix::eval(BOOST_PP_CAT(a, N), ctx)                           \
    /**/

    #define BOOST_PHOENIX_ITERATION_PARAMS                                      \
        (3, (2, BOOST_PHOENIX_LIMIT,                                            \
        <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_eval.hpp>))            \
    /**/
        #include BOOST_PHOENIX_ITERATE()
    #undef BOOST_PHOENIX_MEMBER_EVAL

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else // BOOST_PHOENIX_IS_ITERATING

        template <typename This, BOOST_PHOENIX_typename_A, typename Context>
        struct result<This(BOOST_PHOENIX_A, Context)>
            : result<This(BOOST_PHOENIX_A_const_ref, Context)>
        {};

        template <typename This, BOOST_PHOENIX_typename_A, typename Context>
        struct result<This(BOOST_PHOENIX_A_ref, Context)>
            : result_of::mem_fun_ptr_eval<Context, BOOST_PHOENIX_A>
        {};

        template <BOOST_PHOENIX_typename_A, typename Context>
        typename result_of::mem_fun_ptr_eval<Context, BOOST_PHOENIX_A>::type
        operator()(
            BOOST_PHOENIX_A_const_ref_a
          , Context const & ctx
        ) const
        {
            return
                (
                    get_pointer(boost::phoenix::eval(a0, ctx))
                    ->*boost::phoenix::eval(a1, ctx)
                )(
                    BOOST_PP_REPEAT_FROM_TO(
                        2
                      , BOOST_PHOENIX_ITERATION
                      , BOOST_PHOENIX_MEMBER_EVAL
                      , BOOST_PHOENIX_ITERATION
                    )
                );
        }

#endif

/* mem_fun_ptr_eval.hpp
Pu2TERDwi7hrvZzLg1LRWpuSUnicqEJ51Ce6Wzre0F424KROOnYgqbi1zouFSeHZF/VRQfRPfjT9Lh9E9GP7hBfsh/mqgyiquvkijVza8tU6dAJ0kric6QLf8zU0QjARjBG5+GRWu5Z09gFn0/4ti/Cpri9glS243BVHhoN5xcjy3vYXPmp0j41eneniwdiVQf3Q2iiKkG3pnLBdlp2PcjhhsxxwqwZywsNSZGM2J6yWIhMGc0K1FNnnpYRYiPI/PIh/XUmZB3Lp2DcTlQQ+yvw9VfSU2EDKflUm/55kyT5hntXAj0dvzEM8I0YG3pG2aD+X71Jo92L4ez88j8JTD88eeA7Qu9RPO7w7DI8HvhfBs/s/+NH9+4G3x/7N5v713PAl7tvV/V2+umK7A2SPpvOxcXU2Nx4S62wz4c/QOocDde68hehXN9NijrHqbCgf7eG5EJ4APN+BZxE8S+G5tf8np4luX06q9mGzsoNu+DcvmB0bq2fmR4gn3LFsrbCe159SejUpMee/gZb6rPbhnaDrVVZHrYPDpWrkHM/iApikuga40PKhBf4QLn9nfkQBs4rD7hb3US8PEknQYELyYp8EHX0b870hw+WxJBDPW6/XBcdQ6RoTGpUarKHdqfTht8xU1845ANmSwOgEBa2P4pMCBB77e7wyB5+dKIUaqNQj73mYrhxYNNNEVIUZGxnLJeTa+yW+SatzqGn3GQ/cpwJy/RSe8+H5DTxvwGNLs6fBx5GmPk7X7v/4R/PDGo/wA3c+8V8nuXu1s/phtPe2E1kJ4N18u8+HXLCm3evykS5uAjJPokDTw9a6TLTWDyBHz3mHUN5JmXJJXGVr/XWKvHivbvusCdTTGG+BKN2KwrPEbsyElmw/jSDFFolAXqKRLPM5MGj+BsWGlvnU3b2XOc3HgsQBwifTe0DFJljEhupBOtZBrCOMwHPwXi/0/0CX78/wjIPvJfB8HZ6r4WmBx5aR+LFnOJzwx8W/0jLSd/8nP5o/Qpm9zr/e22r1+npRlsunJ6dnFSWu0cfI33YfopTzNLUKB3CeObrU2AxOmaZLbVSljtGlTnElToQ/Gxg3ETYBn56Tlfp5H97Z4O8geMbC8wV4Zmd98rn8yPL/finGFw6rsd7bMkhtAsOq1p+NwypaDH/AuA7UeMRe2dk2Ual5HPDPq/AVXvu8NbjjEKnyXGSz4LU8bcIUFLokLvjxTFoL8RdaLJ4YmKBmuGo37RMCId6v4rbH/xDvV5+ZJ/FL8GDDqORpVHBTG8umoWpJvQpTJ4pGgXEaBsj2D6msR+usOFu39ldtgdc4VC2QRuHrtrjgrXUryeiiH5kXj4WLiFVAJMgmdBqpC7fgWMR6vVLvcP0O7TRJfSGluWpLabL7DPJ8UV1X7MRKjwJgXw5lcdYRWpm1JDYUXmTDC8IgX7+4PDaFX3D15ou5sWFScVZCxbHCQKYS67SlU7eQxJ17psPSM2PKqWeYx4cNcvmmw5M2GPgYnkp4/gDPvfD8HR4fcJPNneJDiXaH05WWjt8ydv/vfcz9f1rP4+s7enzl59L4ah7q8vGicbZDGHuw7v1iSONO06FVyo2sTJpXOMdoyJG4Wz9OLj+6MEtoJN8KsCuX+vnoyYuB5mBHZ3LPD9GV/s4u69jz8E1MmcaSsTIIg7A4FxlFxRnnMfj9kqSYW/NDKu9QfD+Lg646lUBK0MjFd8dQ255w6HcM9yiqg/MN0ygWSKT4ZYSPGnOjzblJTJWG6rrUyMrVeVCNz5TRdarxeZTOgzdJuZxZ90ZaYGVsCnlGJXVTwE3dJGNzNJlyCf0o8ygL+cfogXemEFQSZnHusTrhBInbm8EL/SgqwXU=
*/