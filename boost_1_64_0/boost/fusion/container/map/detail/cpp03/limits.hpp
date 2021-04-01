/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_LIMITS_07212005_1104)
#define FUSION_MAP_LIMITS_07212005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/limits.hpp>

#if !defined(FUSION_MAX_MAP_SIZE)
# define FUSION_MAX_MAP_SIZE FUSION_MAX_VECTOR_SIZE
#else
# if FUSION_MAX_MAP_SIZE < 3
#   undef FUSION_MAX_MAP_SIZE
#   if (FUSION_MAX_VECTOR_SIZE > 10)
#       define FUSION_MAX_MAP_SIZE 10
#   else
#       define FUSION_MAX_MAP_SIZE FUSION_MAX_VECTOR_SIZE
#   endif
# endif
#endif

#define FUSION_MAX_MAP_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_MAP_SIZE))

#endif

/* limits.hpp
/cUvcVjRiZTmuNcjN5QXw+tt/t1LbxgK0aA083SqCRezq/GmajSo2/Y50apOkDf2g3QX8VjRFROC8L4U69Cvi0KxkRleQZ8MlRE2xn50BaKTGvtW+IywWXsYVVBjZ/sZTFQwWOGIBjvzuVlLJFkKUTP0D+xnASw0Is9BpLYDFE9ZoMezitbu0rNM6QrbudLNlGjKHTcqkG2g/jj33JrWXAKqJz4RNbQ1AWT/cSsQRcRY2HoCuGRGnHs/OFT1QknbKqw4VUOwm7UYFVYvLV28iMwIp+50Dy4JzLptrQwCowwpEKPvghXOK3qf7yUY8PRcmfUd2kJyE30ZLp0LsdhDvg1q6pkJU7YcuIqN8Fz+ZCHctTNXWjCbvfP37j5x99owo7gvEhwAABhrinzVJgCWn1g7VrBQ2PI0DoCPHl3imtUwW9jAlE6TSdvs146B+Gyw8kNd1s8I4kLrwq6GiN2h8koa9cPmxJTX68EW2yf9csO0phtVLT9ZtRxhzrVX+4brnvjhdo56RojHEuB7UGnrYJHU/3C1D52lMNTkR18m+4XvwDxq+kCdG+ccKw==
*/