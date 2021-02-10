
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL_HPP_

#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL \
    ( \
        /* returns: list of `return result_type` */ \
        BOOST_PP_NIL /* nil list */ \
    , \
        /* params: list of 2-tuples (param_decl, param_default) */ \
        BOOST_PP_NIL /* nil list */ \
    , \
        /* const-binds: list of 2-tuple `(var_untyped, var_typed)` */ \
        BOOST_PP_NIL /* nil list */ \
    , \
        /* const-bind this: list of 1-tuple `(type)` */ \
        BOOST_PP_NIL \
      /* number of const-bind `this` */ \
    , \
        /* binds: list of 2-tuple `(var_untyped, var_typed)` */ \
        BOOST_PP_NIL /* nil list */ \
    , \
        /* bind this: list of 1-type `(type)` */ \
        BOOST_PP_NIL \
    , \
        /* error: `[ERROR_message_text] EMPTY` */ \
        BOOST_PP_EMPTY /* no error */ \
    )

#endif // #include guard


/* nil.hpp
ublX5edOl/qTLbCUVjImlVPr1/ZWEmUtlUxpA1xiIkLeklE/PA0Camup5L67KXJmMMGZpu7seRQuJb4OP85YCXvTKk156YMWf3EkNOfy1mRd728PqOymZFKjS74hChqsfbbjiA3gEIQsKhMVBkH2sF71zTHO15ioKx9rHk0fDV2hjbvEGtogVMGtcjd0EYgUY4hRoKx8dOAi7Sx1x1J7dIEShJX+cfME19lYZ9/b+CBav/ZiFE66x3bld4UGyIvB3dC6G1jBR+f94HJw5px88dyXhMbyvG1pkn5NMubUMo43rtjH1sRx7Cyaa1d+MijtvXW6GKwPuwv1pJu6bCuU7La4vr1xZpYATL9j3WPergVs2k/43G/C+uUNHHbnVGwi4ovnrRiM3h97X1Z1R+27XXlWbthN+KAiEVEjO1m1Taf/nd6WcP+j4r4SVy26ZSX+FIpb2LnXd/WiwXa9kWY2i22jTlu5bY3rJ1JbG+v/R2x3SiRNz8c5Z7IqOjTY9HWcK823HgRWi/XLcrFsgM6vG7VeFxbMU17cXr/Px8KKrk3JPb8p9PZYYw87VmNNrnjToY0kEjJV5rHAHOsL36mRDk3WjKhAbwmnUyydJTJ1745UuuCxSPFYQ2Ysxvn5q8GU0wkWN5lHPL9afvS9
*/