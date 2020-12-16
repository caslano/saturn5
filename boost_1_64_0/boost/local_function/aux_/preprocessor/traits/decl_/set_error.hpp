
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SET_ERROR_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SET_ERROR_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_returns.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_params.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_const_binds.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_binds.hpp>

// PUBLIC //

// error: `[ERROR_message_text] EMPTY`, no ERROR_message_text if no error.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SET_ERROR(decl_traits, error) \
    ( /* return types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    , /* params and defaults */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    , /* const-bind names */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits) \
    , /* bind names */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        error \
    ) 

#endif // #include guard


/* set_error.hpp
uhfnBONPQ8JBnb3Q9oW2AYeIsXMRvx3lnIU2IFgcWZmhNm8RPPAS2oMrgEEf+ly0CbAXPhT2RlXPgudHPhEm8inKYALLYGFyOJ8HY9boW3bi89gri57Xc94hHbye2SjnApzn5bXM67npECs/4flDusfrueEQ/b2iraeWx4HKqvORxj8aLkfi5DAuB9LTcjkQ3imXA335kbkc0FF9hbH7qLgcUfF7MiZLP1rq2ohUvR9LJzvwYcJcqfdlpcaXpQ6+LI3gy9kufDnb5svLovNlVLyYWdKX1rY9wRvOlWqGzhKbL+0+dMOZQhqSM3WoM2cKehHvAZ1ypg4lZ0qtI4u9er5P22Q938dmniveT9vktcP7Mcsid8OQYhnb0BLm2Zii8H7sGS2ZVl9ZGf58n4loG4l4+azLTAepDzVGK3YwHP+UZyHZ/m4pjm2nPN/4p88wtO2qf3qouom46cBNRdxROJd5jVBFeR8YKnR2lT5s1bSxXhd1PpgX8bzD/GVYrgOel+3zkCnW5549p1ivjf3Jw1q6oZ6H1TjFmYdlK54u8bG24/nzeVHewHNfB7kQeWwKnb+mrm46HmNAVTvccPUegXiyzTpfXI8N0xEsn2dvF8dPM4424nXXqRqfdQ3tq+7ZxqYbj5Oj3tUfwXNlAq8Uxy8y5hlxon76ZJwbwM+YLtNiuL1+4jif/cWxk416WKg+P6TxneTF4HHsH2IkIi8Iw94SEbaB9pkd5+Pxo1FW+/VahjowB4GvBN85E7K8nkRvcrzXc7g3Oc4wnw3acRwinhfSGOdG7L8q3lNzZPmvpo69fvtcvLuZz2koN4Sh3BjmldcByoJhPiB8jjD43AzTvA8st10HPQqtz/87sh7+zHqYCDHxWsQpFfqNDdNL2JziFmc+U18t65fDWvc2rnt7p+/v2RNUvyBt+sCaz7a08HxeD12/PZ+zympmVrrLpz9sLkR1xWynOeo2m1Z30SZrvwTOp/A0W/9Bnma94Glu/lXKGaf0emTunmNHvLfo/B0fivE0TZ7meaNEeP7l41feXDOyaUTrS9/8cdbwGH/TDX+TnEXRZiZ7QvzMV5TfL5PLORTyIn+XSV4n+x2BYzX8wIPIwzuY/MlDgNnkFw4FFpPXORm4K3mIuzNc8gMLnPmBE5j+RPID8xivKSiM9wjjbQSZw3jzyQs8m/zMc4B9gZcCBwKbOOf4XPIWzwPmAc8HTgJeAJwGvAh4NcNvBl4CvI3p3Am8GPgA92kP+l2c+aaltKeM/jpctYfx7tPY8wDnTD8CTAM+SruWAHOBjwPLgU8AK4EvA6uBTwMDwGeAZwCXAi8APge8FLgM2Ax8EXgL8CXgXYxPHiz6GZx5sDn08/bMz0jgBO4XAXcAsh6hEuh5puoc9aHkmW5Knulw8kw3I890K5bXCKB4N1XSL+0k/VFMf2emP4bp78L0d2X6ezL9PYAQ7EueLd6lnHm201iuR9AfVeTZVqv85cnO9bwv42exnvdT/cZniTKNXUfxfAH6/2jg5sDZwBzgMcCJwGOBkxleAjxRra9TnHm2A5mvQTxPNuNVQZoY7wbGS4EUM9611L8BmAW8ifm5GbgT8FbWk9uBc3j8IuA9wIXAFuB13F8tzsvnGtY/tF3idzrPt5ei54+g1x4PW6uTjRyIyRcuwO8ApBPecNSc4eXf/nd4wwntXecON8NvKn84p/2f4RAXt8f9q3jEC9rXDZf41nb3fGLfA/9+TnH+KwmueMVLUM9WQjKPRJ2G+CELIcsgv0NypqMOQBZAFkNWQZJrcB3UxPjG3dnWz/g/IDQ43+3x/+D8/5nIa5sY/xdplkyrKTuiwQiN+781wJDzgUdybb0=
*/