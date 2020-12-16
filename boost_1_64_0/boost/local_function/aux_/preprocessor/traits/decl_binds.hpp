
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/list/transform.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_APPLY_( \
        d, bind_macro, bind_traits) \
    bind_macro(bind_traits)

// PUBLIC //

// Expand: pp-list of non-const bind-traits.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_BINDS, decl_traits)

// Expand: pp-list non-const bind-this-traits (size <= 1 after validation).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_BIND_THIS_TYPES, \
            decl_traits)

#endif // #include guard


/* decl_binds.hpp
jI6yJg2iR+I873xa9EhCxFNJ5Cny3TMzT5n5yUyO89qom7z0NOVliionvlGznms2u5XnbbhbXRzcmvsV5jbz3q+Y1lSN+Uy1L7ukTeYzaXvO/c8VWN2W//nJ/M5/Ws83up/P1HvqmHdt7vvFquhXSyZktNm6plnfZe7mMz3zlrd63lL9BsJgi3mYKJm3bASDYGPT3rOnxN/vFnvPlpD5okqwPqwCY2BVmACryZ6oNeALYv85rC3h32H0M/RfEn4hpIWE30zmq5pLulrAENgaRsA2sKZpnrW+45mEIbns6VwSNoCMrfK0H6uVXvkG5CAi4xTXMYqMTazHJe7HJLhDvkQsxiEyBnE//khFliMW4418jTUYYxhjijaIaRzhMoawGjdYjxmMccI/vHMdK8g4gUkLzglG2iFjWnnGBZ7Lc3kuz/UfMP5HJb5gxv9J4bwcy3jG8U1wZ2EnuM2uHzonc68I4k2cFJ8Qm5mWWF6gCS4llhEB8768hxOUNpk/yUgKkopMQaYi05DpyAxkJjILmY3cidyFzEHmIvOQ+cgCZCGyCFmM3I0sQZYiy5B7kOXIivDc3/vN7+7XPiQ/emz61G0JpyYejgp/Y/HBt99q4u7d0f27YMdidvPUsKU/zuu1btCimv03BUb5nWNfoH+zdy7gcQ1RHL+bpGmapG0aaRppq1HpiyAogiKtlCoq+tCopLtpNhWatisJgiLqVRTxDoqgKIqiKIqg3kVQ1LsfRVFEFfH229mzN3d35ya7berxfXvznfx37sycOfO4c++cOTOj7o/4eeiQiT/NOW/xQVMy1ne98Az7b+Vdj3BwP/OINUX7p/Z89qmaV8tWreq60P6bW2/rEPm3aZ8e3vs333ftU2+8dHzrqanL0nZI+Pkw+zHAwSr8M28UfX1HZd91f13WWPDedg/w4bdjT+/9JZ8ete01rjsTz0la6Uj/6fZHmHe6ynv/8t0H7D7z0+pHCm+6sPWCF6cgJxYj3O+ysc8vMw+vKHkvcchFnkvP7GE/JnGr8ol9spd72vE73nTtXfdP/nPgSiYkf13mDX9wwcOjnXv+Oa/3zTmnfFazzwmRf+unqvo6+/br3vrs+dzcM5+fUHvsRbcxeSbfyNL21TMR8o2cI9+0x4Aj8a8EDwRnggeBx4EHizsDuZYykZF3GN9dUA3k19EXndmmpy+a28XImR1ntOCu5H49lDLO//0LzkVnDNXxe31LHAeJxBojcOeNIy7k1+W7uNeI3zJ+r4ZaoWSvnp77C6GVUA7u38Hks3x6/iywBb4riOfBXYDbhSz1/K49y/c9vYzfa6AFuJdCq6BWKK4QGc7mGxTKLiQu1O/7OPX9nQ9W4D4bvwbctYXkm9/rvOngx3e5mitYAqWdw/c25ILmUBbN3GuBanFfAWUcwXc6OH9fygwMmEPAXcd3au0RhIUyziUdcAXUQDpp+8GXewl3UWb8boR/Le56aBG0jnAvgAvgkTCe+OcxngDzoTx+F0Hu8aQBNkDLoWb4Zu1POfK7Fr8FUAHuJnAjfi5+rx0PH9KMm0CZQ9kb4oy8ecgM1XmRex6ogd/14FJoNdSMez3U6r2HTHHnwweKk3FE4fnIOJE8wTsHLITO5n4FuBC8Av9G6q8O/1XnwwtinMFAET8o7QLS8fICl3r5gKvBevB3MGtS21xHE3z88x0vQGtkrqOJsGlHUmdQMVQHNUJrub+ROP65j9XQchm35F7YNv9x6IWER74xG5CT3wuhjMmEBYeDa8AisBb/WnABtAxyE38lZbKKuMyTMN4hPX6v53fCfOQkfBpGmUPn4y6iLL3uxZxdgTsbdw04HzpU5lGWeN3gKtA6p9LIvYw=
*/