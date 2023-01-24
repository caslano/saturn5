
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_sign_/sign.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/nil.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/list/adt.hpp>

// PUBLIC //

// Expand: decl_traits (see DECL_TRAITS macros to inspect these traits).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS(declarations) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_NIL(declarations), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN \
    )(declarations)

#endif // #include guard


/* decl.hpp
nqy9QE7CYRxvYvORI3rKi9u9UwGMBi6mZeu/I6pLs+xjDY02vGEu5evsvrAt/4uX+gyIvfKaw09QRaejzW7MLcHsixWti00kavEcD2ED9uh8G3yYInDwaSoYL3Jl/h1zOpaQ0YC8VOON2zm9rEOu3p3DdNfc3XfzzxwHcvyKgnuuEQEaiy5tH7x6XO4xkTFIPnEAxkuk53HIo2Ndrpfo7k6hy9U4dEGNOnxezTG3nzYNbIcjd/hsDn+PO2sI8vUVC5gaodm+iOolDvylDqf84heAo2/hp4nRzp7BbLTCbvTIlrLCBbmwbsfhCYdzYdpJq9uJWyVTrmQvoYh5g67eQMOZ2c1K8XJ5QMsxS23NFaK34CHpublzwNET8AVcVuhBwDDt+VTnL9x41wUPxqFF7/vOjs8w6G73ZUzH+/5wC35iwvMz3pmVT3/9pza8maftKTgbBmfpoaR92ipiW6d4ZveB0CI8OSb0b1VdQ8A08ib3qscbLcCIdfPhCGUOvVF6xIp5axxz2nA01wGdqTlOk0ghSV7UKICwQYGC3Qtvk3pCIO6t2y0JVk4xpQkx1u3g5XDp3a2rEPF8q1QqF+eRmZTaTdyTYZ37VXGphdavZXtP3rNZTIBVOJucRdc26lPyGL2bb5n81BhNvv/Djw+VcYLJZV1ft2w6kuUza4xSukzLqyR25YqHVVmHUsrbVCVWi+JqsM/JDfCkkmWy
*/