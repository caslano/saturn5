
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
f80p/C2z1gSkYKaZNK+T3pCKENFXrNr/HKa8GyOYH4fdhwPZ8VCwS5uPjbZFceBxbvikP4zzxFwQDLbRTqsvVDYXpjqXcXWbyQjVOKHJK0zqCVtl0frWKtYISvZsyKDEG9YZ2MFKwFKS3Zc8I7Y/hKyE0Qg1WX71vX/b5cCyI//WXiqeMAf2nXsPmC5OTpKlJYa8tlHv6GFSkOQgknOHrI1qVBE9Xkc98IU4fCiIzaHgE46MVIPjWCjf9rTcSO9f7FscZVqiGIZbmxf+kr7PmvxHk37Fm/d04sW9l04n4o741g55tsHfKVnVzrmFKb/7ey4l1szlspI6A5O7UdsRjQGndT7rmWLXYglXlbdY8UdrTs9FQFHXR32c42OksQXbI2ua9UTPXO430ywbqNZIF6euZ7QJRITpnn3tMe0eODLab+3Z8zNNrhnje1YSqUJ+WFgWFyAZ72c9nJ3hJi0nEwsQCzwJr6Sy5Bqbh3MJXNPkOo30fmd37j+xd+42hdqjPUC13dBl9jbfgr6drD54uOW0+mdnQiOyjX1NuGB+Z7TXsHX5NJhA7bUJ6zD0dYZRkgbrfqvVCzYWgtE576RW7cHYFNJgiR73NYeCQOJsmAiPIRQ2insNS6UFwvQNt30ix2NvnmEAm1aNeueX3PqH37MlplCR1Cq5BAxAhaDwRLG5EAzw7tRkzLNhMrf2+I2I8Yx7xs87hiZ0CvM+
*/