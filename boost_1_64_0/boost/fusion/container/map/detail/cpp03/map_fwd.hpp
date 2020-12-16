/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_FORWARD_07212005_1105)
#define FUSION_MAP_FORWARD_07212005_1105

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/limits.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/map/detail/cpp03/preprocessed/map_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map" FUSION_MAX_MAP_SIZE_STR "_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct void_;
    struct map_tag;
    struct map_iterator_tag;

    template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_MAP_SIZE, typename T, void_)
    >
    struct map;
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* map_fwd.hpp
vH9Js9y3RCWiH5mAfNkn/L5kb6L9XuSg/FNDEd13cM9R+33GHMTp3qIb4tE9xIQx9m8f6z7Bdn+QbvMZOd0L2K7/uvbbrvv2a739Gq9reuRreDJsB8Ov2TVfrxMQy3VZ12Tqud699rrFLW5xi1vc4ha3uOV/r3xXz/+eZQUn5fnf8MVOSLF825+KsxbNzzZS4nbW31Mc/q40sWYd/8I54WUNngj0x2Be6uB3BNLNOvT3QF5klJRqDmFT+6igz3lXo/C8js/zj8T+5vOmMWmAo3hAv4AfvDWkRMzLFxv0ObOllgH5vKkKWn3emYqhL21MLeL9tLHS1F/dSMww9eexTmQ/fDN/XP6QQG6zJi0+GMS/MSl5av/+UVp2c3BZv2GBZSuqlw0NLOtSvWxQcL2BwWX9AssmVi9LMP3kLLt7QGDZYDM+wBsSq1Aa9MOz/6CxTplZn3KO8hsfjPzyXvN3eTBf5rygL79DV7MOn1FfG5Yl+etVbuL5WUQe5HhM39ipLXZj0JxT/flp+g7GPthS/n+vqce3yMseV+5EWz5Hn2ITfox0Qu4xbEN3ylDbfjJHGtaY2SXNua06xCq0tOXa9nJImqli1cbg8uB4SoGNzHZneQLrpTvk7840qbiGfP+yvGB9LPP6+8VDn3hp37IoxGyPxnJI/9Iftpyoh9Un0UgTpKliaWKHWftE7600IO+3Ne/rFuXd/0hteg/piG0Jdl0k3g/ug3rHrSiGxtZmo3/epZ2b0L/R6EtTX+j7Mkbu0mAeVNvxzT8d+yhzuM1uY7A2qH8Cer6SnpfZl63gc7AT7fDa9JjzoaYexV9Fji1qFNIvjWz9ovgairmMs69lzL3sz6/vXab+a4xtB5FfG77lEdgD26j/Opv9t8TM1ctcb7Hy7pqxLEVa92vqM35ferH/d2t0WsfGduXsv7ORv+1bYBzrJI6ytb34RMdGumFvSB8khLzf1dw+hmzHy3maVvqN5qv367sOKaMNO+0XvbqcN3SMYqPz+2UbpG+U9A1HjPzUmZdY9ZlT5NXjsI45u6v1+tjeYxuLx6W3j47V7kgrRnalXy86/KdHzrS1zsUrzk3nZ3+8WB/p2auc/4Mb+fX0g13pz2NBPWbjat3XOqeGje+46uO7ZFGg3ZZ82YU6f35Je6tO98fUrR2Dbovduhcwt+0WbMeinKJc8/i15TUfoRz+ndRv7ZDu2FSWFMgZPC1l7NTp05MzpqelTpw6vva85vZ8wW2q8wXbrm3bzwjP19yDdSsj6A2maq6Dbmv72p0Z3r4+6DkQSQ/dXp+81b0itK/yzPBczAmsGzU2gl7SQ59I3wbyQ7eOseWHtu/rZuE29aeOxIg2kRq6gfYErmve4H2E3ZZ9sqU70hKJQwYa4y6SLUuy8kvqkTvbsl8cvjXivrvpximevDjFbzsesdAcn/fGTSm8p+tbST9YM/iZZe/0u6f2eETzeVLPmdEh/suDih98DV4A/wT7wNfhWHgIJsM3IPXxzKrnQz0vVpziH787jQXKWxwLu8C+MB4OgV3hbNgNzoU94DrYC94Ee8NfwD7wcZgA/wIHwOaN0AHbwEEQiRoME+EQmAOHwSI4HP4IjoB74MXwBZgIj8DR8Di8BJ6N7WNgG5gER8FxMBmOh8VwIlwHJ8EH4WT4CzgF7oFT4QswBb4JU+Hf4HTYivNGGuwAL4O94Uw4BM6CaXA2LIVz4FUwA94FM+H9MAvuh3Phb6EHHoE58N9wHuzSmLEEu8IFsA8sgKmwEKZBL9Q7onpu5HnS4R3R65Wv/AbYHd4IB8ANMBFuhLPhTXAJvBneCMvhPfBWSx5mnsUi5ru+QPm1O8CmsKPs24IkaLs=
*/