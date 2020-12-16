
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_HPP_

#include <boost/preprocessor/tuple/elem.hpp>

// PRIVATE //

// Param 2-tuple `([auto | register] type name, default_value)`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_DECL_    0
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_DEFAULT_ 1
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_MAX_     2

// PUBLIC //

// Expand: `[auto | register] type_ name_` (parameter declaration).
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_DECL(param_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_MAX_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_DECL_, param_traits)

// Expand: `default ... EMPTY()` if default value, `EMPTY()` otherwise.
// Leading default is kept because default value might not be alphanumeric
// (e.g., -123) so failing `CAT` for `IS_EMPTY` check.
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_DEFAULT(param_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_MAX_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_DEFAULT_, \
            param_traits)(/* expand EMPTY */)

#endif // #include guard


/* param.hpp
SbjDNPIeKPk+SNrlWHAYeAg4HDxM2t84a38t/E7WtKN+wq8/mARuI+U4ANwV3BbcExwIjga3Aw8Gs8FCcBA4WfyniLtE3JXgULAWHAZK+ck8Gd84mvK7VtrRdWAyuMDSHjwSby9Ne6iXeJeDav8DcGvwSmn/VwmfWofMVcjcU62M1SrFGOxBeV88CsaDy8GMoPN5B4NPgjuBTVLuT4EjwKfBUeAz4FjLub3PgUeCG6S8XgQrwJfASrk/E3wZPB58FTwTbAbPBV8HLwDfAOvBN8EG8G1wEfiOjAdWg4+C74HLwffBJ8APwCbwI/Al8BPwDfBT8G1wLRgn5+ymgRvA3uAXYBa4DhwMfgnuBH4F5kr43SX8HuA3YD74LXiw+I8Tf3lfyNyEmusIeV/cKPqLm6VfuwXMBBdKf3YruCd4O7g3SN7N56tJ+HaBWiDr8/WqJVxzmOHWhBmuJcxwxhnth2uI4buokD1ej+CcPWgiVANdAS2FVkHZ3vNOwH7jfWc6jgHbOwulcnxCp5+HMh+e/jNRFh3QZYuei/J7c9w/djZKyiObcD5KO2ejFL4eZzkfhXuUWxO0FkqYkGAMhcZAlVA9tBhqhlqh7InUL+SG5kGLoBeg9VDapAQjD3JB86HF0AtQC5RyJH5QMVQLLYCaoLVQ8mTShAqhSmg+tARqhjZCGUXEhYqgOmgR1Ay1FkX3HI5e0St6Ra/oFb2iV/SKXtErekWv6BW9NueKg2Ztwf3/Zx2DSXJxzTRnVXWp7xSAzTsHwLuP/765yK32roepd4lbZbm6/1cK880YCsWo9azsMHesW+1Tf0d/w1wXXOsIXOvRVRaiNZcr28LR4w46eNxoZeY8fgL2QcpG8IM0233YiBfZmgt4qbXL1vVg6xyh666+IoE1wTJhXzy99IRKkc20S7wzwnWijTFiG2SeC8dv5DKmW9OrKj/m2Oqa8iqVmCqH7bcKXE8fp8IPxco/Tlc28Au0n7yrf8drxfzlRFoh5VQUK5sEQw5oFHQKbSFfLzdnTgbKblj3v1Zx9lZrmRZSHtnwXox83o3bk/vFW2QOtEO/G/c9Ya6r87e54eKJw6znh9KohwC5q61tDnnt2xzxzH0mlsLHoZ6DmeU1FVq7XcJH1kb9ZZ8udqukgdtMI6BOWuL0bakpMG9BbVffnlZ00J6aImtPozpqTw1dQs9/KMvl3zFW2U+YFfAkhFE/xA+Q895NlFPsodm/IXDNb5KsV8zyyenrY5EzpOVb+oglYcjgt0teFmNvB6w/fzJyO12780ifn+Tg/gOxv8TcdcGgnW7fcc6+jx2y+kN7O2O9Pa79eaF6O117++bLlDyDar4ccvtt96Uuemz/N9771lhvZ7cduZ1xpPbQevtmu3NcI7cL19ud29tD6+3R7e2/9fbQnXdO7E+W9+hisV3uC8ncr7yvVb8YMve7v8zh5oNdwZGgxONdbD/nvpfE2xvsCe4j8cb434HSPwbPpWdKvL5gItgPHAxmgUPAAWCOuE3bT+F3ABQ8B72dzF0OBlPAIeCu4h4FDhU+ef53gvR5wTbDo0WuA8Ek8CDhN8aSr6Z28rWDxM+RfO0o+dpF8pUr+cIt5cvVjg14ivDrBUKEsdhCSLxkTbzeEi9d8tEHXEQA7xxmPtTevOXyo5jvhDTn35pn37aAy+S826D5TfN8W+Y55YxbwnoJ92rwBdB/xu3auWoOVJ1vOwbyz4WuJ33/fKiH+/XQxBEB59qqc2yzoYQpzNlBh0IFuOcRpgKU82sD5k/l7Fo1h9oMjgBbQJlH5cxa61xq4Jm1tZB3XvUKsBWU82qD5lgJw72KKepcWuZbzXNp1byrGwyaew0+i9Y=
*/