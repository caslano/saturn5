
#if !BOOST_PHOENIX_IS_ITERATING

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/operator/detail/cpp03/preprocessed/mem_fun_ptr_eval_result_of.hpp>

#else

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/mem_fun_ptr_eval_result_of_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_MEM_FUN_PTR_EVAL_RESULT_OF_CHILD(Z, N, D)                 \
            typedef                                                             \
                typename                                                        \
                evaluator::impl<                                                \
                    BOOST_PP_CAT(A, N)                                          \
                  , Context                                                     \
                  , proto::empty_env                                            \
                >::result_type                                                  \
                BOOST_PP_CAT(child, N);                                         \
        /**/

        #define BOOST_PHOENIX_ITERATION_PARAMS                                  \
            (3, (2, BOOST_PHOENIX_LIMIT,                                        \
                 <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_eval_result_of.hpp>))
        #include BOOST_PHOENIX_ITERATE()

#undef BOOST_PHOENIX_MEM_FUN_PTR_EVAL_RESULT_OF_CHILD

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else // BOOST_PHOENIX_ITERATE

        template <typename Context, BOOST_PHOENIX_typename_A>
        struct mem_fun_ptr_eval<Context, BOOST_PHOENIX_A>
        {
            BOOST_PP_REPEAT(
                BOOST_PHOENIX_ITERATION
              , BOOST_PHOENIX_MEM_FUN_PTR_EVAL_RESULT_OF_CHILD
              , _
            )

            typedef
                typename boost::result_of<
                    child1(
                        BOOST_PP_ENUM_SHIFTED_PARAMS(
                            BOOST_PHOENIX_ITERATION
                          , child
                        )
                    )
                >::type
                type;
        };

#endif

/* mem_fun_ptr_eval_result_of.hpp
c7PfzzDrlvXnphyXbzk8a+F5Cp4BQ1y+ofBshKcDnlzgxAJ4vgBPGJ4GSLsb/j4Cz+vw2OzexA+N1wx3P/qR2d8zYODu/5+Pkq+5nSTvDGfyhm4y/5qTWn5kXeWukUmbeXQg7fbo5QFXqDxppLjicjiCxyflmBk6WrStlDbbV73fF8rQndyrhKIn+TfMDPGVyV2P/ekYFb2r+sDs4CBq2w5E7sk2UhoPhjdVB7BxITduvprzg4BL3y8TiDzuiq/ZRWqX8r3vjB7fG+/PsYuEVed/aU7P8GSztgPyHEneuCrFe4F/TR/glx2h/HF9KO9LXd44/NXk9r751d7hjT7jyO2t+2rP+G44o3f4F6UuX1dA+t/Dh7rFPGMmzMfsVYudphkS2ctw0GRq0EnPA2aKrRLr7zj/9zyy8XiCjUFo4/Gz2SpYZe52+/FshvYCQCPDgWaDSk/Z+2Gos2Zv8Dj/DzSIOy0grlQgSnIhwC6DwMXJ+CFc1JewZZP990nZwGlS8DhL3WVccI6TW+VdPteusDjHggV4pIN2KR3ePvCv4H9UwEL0nz3NIL0mmB6LcWoHOGsHsrA3L11X616HaYYxH8lGgiPQ7YEzFXJjuG+e8cc/KfJ5b33axvFRoxAmxbjtgCgwp5LSfUjAgV5IohgR/9z9SmkYzMV3wQsDDiozWMqESiMVuSq08a8Fe5k5ysg+Yunp1Ajp7jJCLxnd1oHwhRDQUxq+ghg0/DNMP1snoOb+ZLGOwCQxzUDArB85qUVUnQM1dq2P2mmbVaYudQNezSqXd3mZXbHfYKtDjy5gE0dsFxRC9xAHa14MnUfXa4pzDp3ajdNdKe03DJrLC/xNmp++aTf5aSi1PpvwmIB4jCc8hPWVROhSaJWCfbC68yyE3IkoHAKTwNPYc/TfD0nwfP/7uqaQpaafl5gMeBYCfQb/6QeQqWlZ4tYiWpzTFS5piaUDJcKlLXCjj8+m53xwyOpR4hQIP0X3Lo3fH5TOPsb/UTLjn1Rijhi6PTS7dTV7CAZx8NuK5xYeY/KJfYDAKBYYfykmGKABLaGLMqibjg2k2t0Huz9rZiyf2Y/p/+GjQ3J/gkyXr4Mv8RsFT/X+/OCptAFtJwY+gTbzXXQ8GARlHWK+voAui2sRxuUfKzbp6rPaL/k89Hwnz/+1qyhOAful0ieWaWBeq6y4y430L0uUizSWybLpOUu65lwGk6ezfBoLeyBxxe2XYWxFnzZmpQ0U1rL1oI89VskQhyzkiVm/T+noio73+P5IXqIEBiFdu1Lufxq5V6mpr5Mtc61SvBnde3mOcsTUHmkgW+h8dOjfxu863mzJh8AfHJ6O6QwL0BEICyuVVWXGjLD7z4oROs0IYU0rSsGhBRoxQBeKryx7kjWpw7sczfj50hUGfVVWlS+DbS+vdxZ/ch0wqTea92ltRB8frYkdKRyMtbGDsQRvGm3UX20U0awN7dnpbniEQrVE5/ocyICIcYMOe4bm5FsxnSM0tlGvwLyJRmUc1Q/W9Rw7GWWr5bbEoMYa6OjVyP+7sng0vNH3eSMDDYDo1uPhBc+zARvOsbTKU0J7whiASTA61+GAtsPyfessGQf5/sYMmUEz/EGWuTz6JbZynAQ/U96kg0sn1Kr2Hp2ytR8pChwtmxjXd+VXCA/IDhSC+ISOMCEKncE/OlrR730PKDQQCh09+4U7Egp4Xy8wIOHm3wyl6A4N9/9JU6VYqHLXF3ldGcqT3/ZbUOSH0K0jzv/3f9+I++9+KiIUy7Kni4CT/dOcJslCTLIrTiWSsQeNDxRlYml9tZepu478X/z1kDXeDgdb3F6yj/80yLxTu4Wurm0JmFJU2Ie0qXmlvro=
*/