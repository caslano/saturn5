#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        BOOST_PROTO_EXTENDS_FUNCTION_()
        BOOST_PROTO_DEFINE_FUN_OP_VARIADIC_IMPL_(BOOST_PP_EMPTY)
        BOOST_PROTO_DEFINE_FUN_OP_VARIADIC_IMPL_(BOOST_PROTO_CONST)
    #else
        #include <boost/proto/detail/preprocessed/extends_funop.hpp>
    #endif

#else

    #define BOOST_PP_LOCAL_MACRO(N)                                                                 \
        BOOST_PROTO_DEFINE_FUN_OP(1, N, ~)                                                          \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES) && !defined(BOOST_PROTO_NO_WAVE_OUTPUT)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/extends_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file extends_funop.hpp
    /// Definitions for extends\<\>::operator()
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES) && !defined(BOOST_PROTO_NO_WAVE_OUTPUT)
        #pragma wave option(preserve: 1)
    #endif

    BOOST_PROTO_EXTENDS_FUNCTION_()

    #define BOOST_PP_LOCAL_LIMITS                                                                   \
        (0, BOOST_PP_DEC(BOOST_PROTO_MAX_FUNCTION_CALL_ARITY))
    #include BOOST_PP_LOCAL_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES) && !defined(BOOST_PROTO_NO_WAVE_OUTPUT)
        #pragma wave option(output: null)
    #endif

#endif

/* extends_funop.hpp
Ght74VEXTy4syKR7FB7C2FvHQxs0O4NwKfORQ9uFWcrHSOeFF4Bvg9D9LOc9Kuq1tY/MEe9nFUeFZK74MOc9GtXrZKi71v+beiMZUq9BHQ/SQb8S7ZTnTaRziPpMQqm0ARjbdPytoOVYK4XteCXQHp7ovZHscoJxuyi0ZXpRaUPactl73i4xsd85OACzl61M+njCBp86UdBRLPjeOqnY7EyEERvjD3wUtIfjPB1QOo9s+kbrpuGs1NzAPYQ8D4V/uDCi6oNjR88b65deTOFqzpwWFhSDGKeGxA6qXUI9zraVRd8ka3oH9l4d4EKcF8hAtBc5Dhivpz7qCY+4dDEtifgTbuGZPiLzHpTWo1oVqkp4yWpXajO315A3LOoWEFeUWwgsiLfKbIo7uDR2ttLZuYmx9/QLj/bnMfjYCnl3/jml+QgjRa+lYRH9uOR7flPAqc50plczwMmCDucPBSy8SVltOoC9sgD7Nwp7ydjO+chqR1hgRhI0jlecuCJfmam7xrVthE0cCdK+ehHt+ii8ZaZRstK1AwRkT7Lu7Om4ByiO0ayRXret6LNl0YzrPnoexkO9ZpYU/RKWjmbiZDbWT8b5prTj4DWt5bIWaqC9mzepPo0PRxewltrF++QwXttQApOzGQkzpHvLa0u6rpVc2JqfS/fieXQnBd3jMd3Oh0pLey7dh59H98qM7hrqFindpmaNdrzqerOU7mwZI92CfdqKyXQ2keYjXlLKzdw6HcdWDhZhF2BGYGftQ4ywzOqmmYql+TzZxP4HSlN55iDDn/H9/z5fV3eg/w7XAaUrOtZXUsa7FecLZTvsM7JuVw4vzgrSqESd97NRjqL0eAe6eyW0qxbaSegm2u5JfT+/DFbLf66yYd3e8aV0vjiTvmusrJv/fX3N9ASrSPdVBV3NeCcbEc/h/319bR0B3TU8qyhdpSE3ZN2arl5Gty64/7wqMG3CEbaVvYzKiR1zfQiNUR2DzJwPH8avTglg84pIZiuiLyCIXco/KF3es2CNV6Zvikt3xlEuuzWJD/DLS/2NldoLVZeX9xR82ucb6kV7O4d5Gww63g1Kp9bM16FuteSUDmLtUG9ciAkfdZR/nL2rpwXLvYuBm9a1d/FPG2JQpXUpYh0Id/1FuCc5AnnPOdwNFuHap9VrWszjMvwpwpybIz7S+HP2De01ZGkGDncd9Jnzshvn+F1SCvyedchQ66byazZ/v/ngl7opHc/fb4H+pxClCfSzMdf0a6NO9JYz3TUIn9NZ/um/RNhrUJ99BM9h02x7d9vrgh4N+5H0sVlfclK8B0lrKhVCaV5GcrsM7yQU71F1XLZeWM3mQ3V2OtYF3XBa8jht1VrR0XrO5+AYqffBhQ4qVE56qWrQA6aQCuPcZpdH9RrhaiE7FTUm87QvCY+8uZNYIsP7/zOnoxjfdd2Lru4SAzrH3orrI8pbcQZyjtEcg39BDo1Qc5NGhLlmASar9DLMJQpTajuyvPrYAmbWwMLPtqblSazN9Fsqt2+GJ9UAkvJ5ZBiXZebzYTYonVKuzvLtLsCUcnMBDDwd6i9OFmGHymO8foR78VhmLgGvvYhvB3Q+HasNV9poBrThesRTqLQBORrFYYaci8E0S4SZjpxh+7jX/kzrDKxp+14K3jPJE8IqiedL673+6ci2OzSmd7IeEDFgaBEzYP/ReNcW+BUzcek67T3DB/hxh4mdyduORnEcq9p3MujFu6QMwTOWLe9ftCGwvm5FVVnx3+oa8KkReF94v7vv3eO7363T+VzaRKfz8YuzszvvHyjL5+QPZ2VZbT07a+8f6d2InMEQqQ+/Y7xEWES95kMu9bjgHhTrR3vmHHvzqDhTrTc=
*/