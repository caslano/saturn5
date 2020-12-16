/*=============================================================================
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DEFINE_ASSOC_STRUCT_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DEFINE_ASSOC_STRUCT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_assoc_struct.hpp>
#include <boost/fusion/adapted/struct/detail/define_struct.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0(X, Y, Z)                      \
    ((X, Y, Z)) BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_1
#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_1(X, Y, Z)                      \
    ((X, Y, Z)) BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0
#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0_END
#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_1_END

#define BOOST_FUSION_DEFINE_ASSOC_TPL_STRUCT(                                   \
    TEMPLATE_PARAMS_SEQ, NAMESPACE_SEQ, NAME, ATTRIBUTES)                       \
                                                                                \
    BOOST_FUSION_DEFINE_TPL_STRUCT_IMPL(                                        \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0(0,0,0)ATTRIBUTES,_END),   \
        3)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_TPL_STRUCT(                                        \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME)\
            TEMPLATE_PARAMS_SEQ,                                                \
        ATTRIBUTES)

#define BOOST_FUSION_DEFINE_ASSOC_STRUCT(NAMESPACE_SEQ, NAME, ATTRIBUTES)       \
    BOOST_FUSION_DEFINE_STRUCT_IMPL(                                            \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0(0,0,0)ATTRIBUTES,_END),   \
        3)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT(                                            \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME, \
        ATTRIBUTES)

#endif

/* define_assoc_struct.hpp
KT0j2oAN4IJ6Q9xxy3wysJ73ScbnO/WtT4FzjWs3Orhy+PU0cQ2Do4E03ATcS8Nn8Gyn4WbCE4S70uBZcK40eE5xTt3p88TPB2/HdQs4V1xfcHDl4H7r4MQ2mF3EdyZzS/9QqG3Gr7fufu28eUNTicpdB1558+PzQk2/pl/Tr+n3P/1rTqY2lNFO/J03coa4LF7usZF/JuoGzEpF68IDBg0cNDC7dsD8xODsQSf43MLhQwck6H7jSHhAODIrNdvjaxoXxZMNM8J1dfXV0dhAOkBCuD8yNLpdaGYotDXUIXRQ6JHqkG9PidY0NiQaapNZfcr6ZpXEabNh9Eyafs3Kpbvpo3W0o7NlqKjd6XQ+1sBQWw7rqgwZ/lvIHEnmRjKDx4ZC6wp7hojKq6ubgnNP27ctcEd9Qjtuy9q1KyX78axQqCRjTjSWSOYVFUm8kvUTAq8NLyiLVCdou2QXwmcS1qylwOvi88siiUjj/EiY3WrWbh3ZP6cAiMHthzIs/I44U3zoWPFOjI4j4mv0EyFwfcgezly4IQFScJkUazLczozPDIXObibamZumbWp+yIXf3N3jgdd69PnFSfTeIa0Enp19a8UHL33TuWzbWV3LftF1cyh0QUjg87r3zXqg08p7v1704NIXL/6sjMLBeMmDa4r/+MPawk/uuOqag+7sdUModEaGwHdOKOma6rN82W86j15+4I7v/xIK/cDtW5cnFi/79pjKxy5aeNK9Fz5yz5ZQqGCAwF866+Vnf/jisl2LLune6f5lp1K6XMX46Y+cdUvb1w6/7aSffHha3e5K+kAPM/7gZfN+1n/Z+tq3O3131xd9jqbAfM74Ua/VHFx3+uTz3jrwwnjPvqW/DIXGDBT44a3DhS+e/FH9cb2uvnjxoju+CIVe4PCf2f7qJ5+c12Xq1pvO+PWOvqcOD4UuZPlbr64te6D5x3947ObeP1y3cunNodCbjN8/rmjXtyOHv3zln99+piaj5reUX44X+Lfbn2x17dnnrpj0xpfV0VN77QiFtmQKfFxW5Msfz5jdr9n82Qcv/nPk5VDoasZfv/zdZydEojee+/mZs+7rcXuLUGgJu/PRsqzrB2yMfXvuZ7c89JNbuq8Nhb7j9Ixvrb/wi53HPvvyFbld+7874vFQ6DmWz7w52qPn2V+e2GV3l3aH/XrWm6HQUdkCv/3GW/POa97s+wk1J9wRe+cEKh2zGZ9YXNPl3cpd/Q+Md91xzrDd5M4DjNd0H7zyk02/LFxw52v3HrCohr7LawcK/OnWHR6tGjr0qbEt+p04r1s+FZLPQhTWEMoIyk5bitMhZCdRKI4iEVGeupE9hOwsskeQfQzZE8QeW7LFAONYskWh7kv2RWT3J/tysrPJ/pkoi2RfKfI82deRfSLZooyOJHsbeT7zuMzQUjK3kNlC5lsy2f0yQzPJrCSzgcxuMp37Z4aGkqkkkySzjMwaMpvJbCOzi0zbAZmhLDJDyRSQqSOzhMxKMuvIbCCzlcwuMs0HZob6kBlPpoLMQjJLyawhs57MZjI7yOwm0/F4kiUzgkwFmTCZJJkVZNaR2UxmG5lvyXTNzgz1JzOazAwydWSWkLmFzAYyr5D5KJtkybQeRO6SqSATJrOYzDIyd5HZOIhkybxHZheZ5oMpHGR6khlNppJMksz5ZFaRWUdmI5lXyLxHJjSE5Mn0HELyZGaSWUxmGZm7yGwgs5XMDjK7yLQaSmlMZjSZIjJ1ZBaTWUHmUTLbyHxIZjeZtsMonclkkxlPZiaZOJklw0iezCoyTb+mX9Ov6df0a/o1/Zp+Tb//7V9zMqf/28f/9YkZKboMJzZXDP3/pXF/+1Drdh1pjDvzbRo=
*/