#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/core/detail/cpp03/preprocessed/function_eval.hpp>

#else

#if !BOOST_PHOENIX_IS_ITERATING

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/function_eval_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif
/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

        #define PHOENIX_GET_ARG(z, n, data)                                     \
            typedef                                                             \
                typename boost::add_reference<                                  \
                    typename boost::add_const<                                  \
                        typename boost::result_of<                              \
                            boost::phoenix::evaluator(                          \
                                BOOST_PP_CAT(A, n)                              \
                              , Context                                         \
                            )                                                   \
                        >::type                                                 \
                    >::type                                                     \
                >::type                                                         \
                BOOST_PP_CAT(a, n);

        #define PHOENIX_EVAL_ARG(z, n, data)                                    \
            help_rvalue_deduction(boost::phoenix::eval(BOOST_PP_CAT(a, n), ctx))
        
        #define M0(z, n, data)                                     \
            typename proto::detail::uncvref<BOOST_PP_CAT(a, n)>::type

        #define BOOST_PHOENIX_ITERATION_PARAMS                                  \
            (3, (1, BOOST_PP_DEC(BOOST_PHOENIX_ACTOR_LIMIT),                    \
            <boost/phoenix/core/detail/cpp03/function_eval.hpp>))
#include BOOST_PHOENIX_ITERATE()

        #undef PHOENIX_GET_ARG
        #undef PHOENIX_EVAL_ARG
        #undef M0

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#else
            template <
                typename This
              , typename F
              , BOOST_PHOENIX_typename_A
              , typename Context
            >
            struct result<This(F, BOOST_PHOENIX_A, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;

                BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, PHOENIX_GET_ARG, _)

                typedef typename
                    boost::result_of<fn(BOOST_PHOENIX_a)>::type
                    type;
            };

            template <typename F, BOOST_PHOENIX_typename_A, typename Context>
            typename result<
                function_eval(
                    F const &
                  , BOOST_PHOENIX_A_ref
                  , Context const &
                )
            >::type
            operator()(F const & f, BOOST_PHOENIX_A_ref_a, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, PHOENIX_EVAL_ARG, _));
            }

            template <typename F, BOOST_PHOENIX_typename_A, typename Context>
            typename result<
                function_eval(
                    F &
                  , BOOST_PHOENIX_A_ref
                  , Context const &
                )
            >::type
            operator()(F & f, BOOST_PHOENIX_A_ref_a, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, PHOENIX_EVAL_ARG, _));
            }
#endif

#endif

/* function_eval.hpp
/4nxlbhff8nT1yeJy/FHeEvhFXg7dX1Cjl8d4jUhXou3UP1bIe7tqz03xOP4fPV9ip+p4kND9l8T4rW4jB9NUL9X6cfHivH3PfCfRkT/2CB9/9SGeB3eVaVvsN4+gfcQ/SuFIdsn8ZaqfxNX6avCVflYHXL8GjxX5U+I5w6JyvFlCfw0ER85CD9VxEcOw49T3we4mh9sEz5P3P/P4IVi/8n9eH+K9Ufm4M+7aPtvhkZlfG5tiOcP4/4QXoCr5yuJdxZeiQ9Szw8+Rs3PiR+t5ufEj1T9k/vr+7MAV/NrjsVXi+v7O1zOT3sA72/1/OLr1fr1+EOi/6kUXyXq14XD9fErcPI/6/fRUvxox2189nI833E7v/EK/EAR/7gSP0Ct74bL9T0PxNX4CFzG7+Bq/4kQzw/xAvw28f00Fv+tWN/8WPxGsb75dPx80f6VGKHPPz/EC3AZf4b/VMVf4GNU/Ak+LyriT/BpuJlfxt/+Pfx4x+33eeuRUS/PeOGxQf48h//c29U34P79N4r2B9Bev31T27Q7OOqtifD3SOC3HhfMj98ev8P4u3jz1NE64LcbH3k89fPUr+54pfEb8HT6ckfjUTG/On6947Z9tS1+reO2f68dfo3rdn1GfIm5Pz4c666vqftnk/ip4v09Bz9ZvL/n4er9XYc/ERH1h6N4vwovPyb1/ZbFq0K8Fl8WEf4T+s+F1xQQX+C0X9v4mC34EsdtfPez+IWO2/F9W/HFeLbvu4ITaD9S70d8nJjfeTHex3Xbfoe/KtYHWI//xct+/27A/+xl/359GN8qxgfVnkj/q3p/nBTy/Y/vITw/ZPuCkO2TeGfhlfgoMX5sFT5SjB+7AT9QPT94C3F8b5z2XLy18AR+jPAKvIfw6pD91+Jy/D3eSqX/ZH1+cXxPdf3xdur9ibcQnqzfXuUP3jbW0Numfq/AY3gXxx8bEIxfWYlHjDfaJ6i/XYf/I7qrn4g3SqX6BvxL43/A/fbB02ifion54/DSmJg/Dk/i2d7vN+OHOm7b3ztOIH4qGrhtf68pinqHqPtzEu2Han1sfJAav4XL+D787kj263cJfjWe4/i6lsH1W4JfafzLlsH1uxRfavzIVsH1uwK/xHE7P0HVFF0+1uIJMb56O54n4lffwvuI75d4sW5/SODd1fOF9xJegfcR/X9X4XHx/VWNDxf1l/X4/qL+8hi+ryh/c6ea70vz/m+DH+Flf/93xPPF+3F3fJR4PybxoWp+WnyIav/DR6v+RfxHov7wDJ4Q9Yf46bTvqfZJ/Kdi/3n4QWL/FfgodX/gB6j5i/Buqv31DFy1z+C9hSfxPHV98O7i+lThB4nt78JHiPzbgPcX+edN4/4V+4/gR4j9t8WHif0X4v1F/lTiTVT9HR+lzh8fKfLPmx7V84/jQ9T4Bfwe8XwX42tE/Xcqfod4vk/Hb/dE/X5G1Oui3k/4NcLzS6Le2cJrcTk/zMz6+FNxf+DtI2J9v1k6vmspruK74rOJr1P9K/jXkeyeLK2P3xD1yzLql+r5n6vbV+L1rt5/Idvnh2xfELJ9Ycj2yZDty0O8wvcs64eFbF8V4tUhXjPX9P/Y72t8jOv2+xo/zHX7fY3ni/j2chq/5ov270X4maL9ezE+R7R/x+cTv+Zl758fgD/vxKfY+a8S+GbjXzr7PxZfbZz6pf/rJPxGx239Mn8B8W1q/AU+RdW/8Pe87NdvPf6Ol/36bcC3e9mv3+P4Ni/79as7K+o1dcdv2/FV+G6u2/Wz8Yjjtn13r5/54z98d49/Al7puB0fkb/QHN9c/6PxVPyT7+71L8D/5rhdP+oC/AHjD+D++JGziX+PNTz+8NQ26/D3udk=
*/