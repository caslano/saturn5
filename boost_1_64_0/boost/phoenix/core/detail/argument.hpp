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
GDPxWo3XfXi9jtdXeBVggbsEr+/j1YjXJ3gN7R4JE/nZPLxf290KtwPvD3SPxB2JIzMrEg/iaI3rvKxIPEgvEg/Sb023Nuvk8nN/Vjiekwu73wyb2QPzHryuwute6f275ns57qGirCIuM/6Ty0P37HCcsdOYmv310gnEmc4WkU7sbePd7o9SnBk9DeP8npHt5T4j+tMa2As92/Qd0Z9aeopyif4zJAf7C17X5ETqIdK/duH9PKWPHsyJr4/26IV4etG+ip/p81/Xq2P5j+YZedTGufNrxKnP68nHqYvvH18jn8N76+Mt7X3y8U6bWFzj91QHa2oD5Z7Wt0HfqEW1Xp97VL4z3+mqGLU8ONqVP07YyvFnjwpWlgU87lEBj89TFvREt/B5F2GDb01zBjzB0xOx21NhuNuL2Iyy2Ftd7qt1ix8XBwN+Z2XHgviXlgfHdTSQr7IsWBkrUHjDkC9YEs5UuVE+sdgfqFkcKKtyVHh9nqBjGCpgePEKb7W7ZkXQsdQbChbnu6Ip4a3T5cwvGDNhjNNV3FpN4W09gUBNwFl5KmJbhBoPBd3ODha9PLDKH6pxxlF2f1n5Uk+oxFdT7nN2MBEUs6NBFnlrTk29BEOBMp93cbUzjiLiFSnfyaY81nV2OOXa8kAonK63evGpiKm8JuDBvyVVnqpy/6qS4KmIMxhyn3wFt5e5Fac8xkiEJeU11RXeU1qNK8yWibNDeqtDnkB1ma/YXVbtOdl8mF2ytiq8XXXoZKNpU5zQKr8n3kKIAbWswhMMYUfuaMCVY10TSpZXrDoVOQ95q066ItttUETY4ZooC1bnn4pMVJX5MGJ0NPVgsMNjaLgFOhqm/KR7mtRhg6ND5X6v/2vGZI7GiM3rxzzAGcdoHMovCXiqPYud5XFti2mGs7xj9ROu0+VjnB2t1ZrqmPlXw9SUB2NOZcxyeFaGnPGV2FNdHs+W2OFDnirzH0xflgeccdaTGPtQZASvDpWEd7W4pgAnJBxP+5wYyI0ZV8dDlfuqY9ah2kK13g4XyRlPxjClCMXXouFNEXH823qC8dUNtg0Ey+LdtKq8uiLebeNtU2zqrfbGXTJPIGYXjW5aXhN/bsu9/sq4t/UE4s5u5FjSwe4WDhOKq8eNKakKxjUGBsfE3R5j4h47xpSUL4pry4AHx2N3+O2Yktb3HQ21qLaiwhNXw5uh8E+Jr2yVJ1ASHHNSwdwxm00KFh6K8ksWeUNVZf54gvmX1XpqPfFsWeUJVda449qX3fkYwENxpe/Oj7fjuOM6eJpnZSX4F5tWTCx2u4s9K1sPEGV+bzA6DwhPAYLupeEeL518xRkA84tyDGuhyoCnzB3EVu2HrK32Vng9bkzAwqHUqb0Is7w8VFPjCxbD8D5QWx0+fEVCeMeMP7t4ZVUVjnAIEU8A81BY0jqRibtAkfl+fIUIT+jj2rK1lHFtqp47xhWodU7bkSKGFx86sn1k3SPuAJ7l1SF0jOWaZsIxMxCq9WO1CFn3Bs3GLffXlri9QX/cfdVcQImrhnBuij0mjvwEQuGug4mxpxyHE78/zrwsrvW6MUuOu4bwo9qgJxBX3qUuURNYFUfXF59Kqj0r4iizp7K1BYKeSrSab3GBsyxYFXeo8sqyarfPEyhYjAEx7lCo3/LKpXEEqPT4/J5AayCfr6rWF85czCqIbC5+5MSP4gtSVYVtO5apWp/P7V0eV5VZnR1lD4aWxhVocRD/4QjtrwmE4qiv1s2Dtf44tw/nCdnxlC8tr1gc7/aLa8sC7g4kUhvy+ryhVcXuVdUlOCqH55YdCVYLKnF7QtgnvTXVcQTErlhW68PZbVlg8fKSqhq3J7wvxx/MfIMTJzw=
*/