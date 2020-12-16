/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_DEFINE_OPERATOR_HPP
#define BOOST_PHOENIX_DEFINE_OPERATOR_HPP

#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#define BOOST_PHOENIX_UNARY_EXPRESSION(__, ___, name)                           \
    template <typename Operand>                                                 \
    struct name                                                                 \
        : expr<proto::tag::name, Operand>                                       \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_UNARY_RULE(__, ___, name)                                 \
    struct name                                                                 \
        : expression::name<meta_grammar>                                        \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_UNARY_FUNCTIONAL(__, ___, name)                           \
    namespace functional                                                        \
    {                                                                           \
        typedef                                                                 \
            proto::functional::make_expr<proto::tag::name>                      \
            BOOST_PP_CAT(make_, name);                                          \
    }                                                                           \
    namespace result_of                                                         \
    {                                                                           \
        template <typename Operand>                                             \
        struct BOOST_PP_CAT(make_, name)                                        \
            : boost::result_of<                                                 \
                functional:: BOOST_PP_CAT(make_, name)(                         \
                    Operand                                                     \
                )                                                               \
            >                                                                   \
        {};                                                                     \
    }                                                                           \
    template <typename Operand>                                                 \
    inline                                                                      \
    typename result_of::BOOST_PP_CAT(make_, name)<Operand>::type                \
    BOOST_PP_CAT(make_, name)(Operand const & operand)                          \
    {                                                                           \
        return functional::BOOST_PP_CAT(make_, name)()(operand);                \
    }                                                                           \
/**/

#define BOOST_PHOENIX_BINARY_EXPRESSION(__, ___, name)                          \
    template <typename Lhs, typename Rhs>                                       \
    struct name                                                                 \
        : expr<proto::tag::name, Lhs, Rhs>                                      \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_BINARY_RULE(__, ___, name)                                \
    struct name                                                                 \
        : expression::name<meta_grammar, meta_grammar>                          \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_BINARY_FUNCTIONAL(__, ___, name)                          \
    namespace functional                                                        \
    {                                                                           \
        typedef                                                                 \
            proto::functional::make_expr<proto::tag::name>                      \
            BOOST_PP_CAT(make_, name);                                          \
    }                                                                           \
    namespace result_of                                                         \
    {                                                                           \
        template <typename Lhs, typename Rhs>                                   \
        struct BOOST_PP_CAT(make_, name)                                        \
            : boost::result_of<                                                 \
                functional:: BOOST_PP_CAT(make_, name)(                         \
                    Lhs, Rhs                                                    \
                )                                                               \
            >                                                                   \
        {};                                                                     \
    }                                                                           \
    template <typename Rhs, typename Lhs>                                       \
    inline                                                                      \
    typename result_of::BOOST_PP_CAT(make_, name)<Rhs, Lhs>::type               \
    BOOST_PP_CAT(make_, name)(Lhs const & lhs, Rhs const & rhs)                 \
    {                                                                           \
        return functional::BOOST_PP_CAT(make_, name)()(lhs, rhs);               \
    }                                                                           \
/**/

#define BOOST_PHOENIX_GRAMMAR(_, __, name)                                      \
    template <typename Dummy>                                                   \
    struct meta_grammar::case_<proto::tag::name, Dummy>                         \
        : enable_rule<rule::name, Dummy>                                        \
    {};                                                                         \
/**/

#define BOOST_PHOENIX_UNARY_OPERATORS(ops)                                      \
    namespace expression {                                                      \
        BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_UNARY_EXPRESSION, _, ops)           \
    }                                                                           \
    namespace rule {                                                            \
        BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_UNARY_RULE, _, ops)                 \
    }                                                                           \
    BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_GRAMMAR, _, ops)                        \
    BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_UNARY_FUNCTIONAL, _, ops)               \
/**/


#define BOOST_PHOENIX_BINARY_OPERATORS(ops)                                     \
    namespace expression {                                                      \
        BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_BINARY_EXPRESSION, _, ops)          \
    }                                                                           \
    namespace rule {                                                            \
        BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_BINARY_RULE, _, ops)                \
    }                                                                           \
    BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_GRAMMAR, _, ops)                        \
    BOOST_PP_SEQ_FOR_EACH(BOOST_PHOENIX_BINARY_FUNCTIONAL, _, ops)              \
/**/

#endif

/* define_operator.hpp
LdxHUD4tgC2wddR46ajxvEk0SJDDtUOUJ/ga1XEPccfdk6rjyruRfPTT5uHYg0WO4GzqLJgv+8EbDFcuYRHP0sCN6Asylzh8PNced8qMwmBEVDripKeuSCXO0YOhNTS5GoAVYxWA4VQqgKV0Cu/YOz2bdP8+dJT2H2J1s1lbY8q0M2XaIRGElz7iynz4BL33e+q9Dum9Duw9JfKmfD0Rj1o1cJ0k5WQM0Rp0O6zl9QYLHLEDY3r4nnSoDgzqfMeQZHqQvubjhczYrdEDYFwi5dj58JOMK5EA5KhV23k1Wbr4CDmW/Dc9+2VbFlry3yNJH0ERt+nG03hy8MeXpPDZEgx4BqtJdc1+AeVII9CPptthR4njjMwmnBydjeKqrYigjSQFFj5bkXDX5ipo8zKacM5HZ/LibViCe9JwcByVQes3Olmp+NuNYJ4VyabUB9e6XDAxm+4g30rR/cVgwBn0mc5rnI66dQDh+i+pI/V+sQE2AA5g2s1LL/doW0gyIlDxKJ5GaHghB8UOQYrBSO0O/nmFan8dSFPEq04fnYt5I4pU43ZKa6M/PNDayIPl+8NaKAOk8pp+8OCCh3m4qKujU+CnXDztcfRC56QjwSxDevXpZ5D/IFuGbs6AtUIs2Br8yXDwLjnR2S8sndH8VN3hRE9ZCIX2GuWo/Sq78lxYItlrFk7vcvl6R9SNgP9AZVWIo3k6PByKD1OUb/3oRHg4DB/Gw8NYfChQrvWiB0upfeFhND4gnAK1a8bHwYOylj5/WSzq8v0Wvpvg+wp8/wLfT+D7V/hmAQIGfHPhC+IKwzBcLsMN/+DjSMNPelpahmH0g4+zX9LHY3uG/FTGsWmvfrA/fcT/j0u5XxfLNlTM25A+DByVo5ZhSnaicwk7cBJ6GuPdKJZyNzobGZMcy8y11adAzy9jmsp8jb32xyRLKJ8VN70vVdCLmf+U2/8qPLU7umxvrmKL/h2WWj8hyoc9jNio+aXHxgK8nZybhL93iOoOVlZK/l6OsvPxgDbBmWDwvsApDrHJVyjC4gAUITLR9FKg/S6S48CJZBaAmTSf1jLfrK2k45M/Bn/MX86hEjTufYEKtk+RaGwIQ+ejzxKQLS+PGwDwbIEfU/CrbfBPFfgxgg9LMqEHxJXLp+Q7+l/sHQt4lMXxXkmOcHAXSCBigPCSV9QoWMFgizSxFEmbILHW99vradXKHaISIIZojuNatFDxbS22tNJKK2JUtMGiIFAbEGvU1AaM9o8XbdrGGiGSzmNn//8eIam1re3n6U/u9t+dnZ2dfc3Mzmy+nzIzBitACF97KjlEaiO9QOoDYV7gXDkNXslCm+tD/zmdSp/46+FJ+j4LMfZXxpCIMT68rzt0lFyFeCNIxyRiwLOxFC0qa0ZxKRa3iUg+D3yB05qNOzWHt2a2ina5DH/rW3y4bRXxYfAkJbDqKhB7C3HQOTveQedsqiv30AibL/YNpd3azoUIFjhWtIToLz8bhfryM1x+Ng2b3FCuzWfJNCM+0wzC3UY7hIGUjt9xahlrcYy82obvB1n8JmKKLK8DA/ZAPiLXXdHF3CPn66nVB9zB6SwpnbJXVA3mT3f8z0y76qD9o4nU/1Xusa7/E0TeUPUki8o57LGHhWIiGp8lGrjzJJKuHzOsQDn6ZLwtTeRacmlAR6Eo7XCCTC21FFVucw+Lk6JutytTqldEaXOR07wA2jWZD7V36tnU+yzexgix1/SnKT69yyJsHzapS+IW3GlL4TmDGP+yiSKrKvLv18KfdP+FPNyrv6O9dbNoazxltyI7QYTnIM47lioJEujE+pAUjjjVYyuK0FliV/2cy5QhKjfPE0zM2pIxa71OY0btX34=
*/