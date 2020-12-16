// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_DISPATCH_TUPLE_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_DISPATCH_TUPLE_HPP

#include <boost/preprocessor/tuple/elem.hpp>

// Accessor macros for the input tuple to the dispatch macros.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_BASE_NAME(x)                       \
    BOOST_PP_TUPLE_ELEM(5, 0, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)                      \
    BOOST_PP_TUPLE_ELEM(5, 1, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_IS_MEMBER(x)                       \
    BOOST_PP_TUPLE_ELEM(5, 2, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_IS_CONST(x)                        \
    BOOST_PP_TUPLE_ELEM(5, 3, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_TAG_NAMESPACE(x)                   \
    BOOST_PP_TUPLE_ELEM(5, 4, x)
/**/

#endif  // include guard


/* function_dispatch_tuple.hpp
GP8T99yE3xf5HSgYLwj7b4DGhvHcinwehP2XeOfH8yrye+C8fcS7ICkvFn+TbEMQ859Biu/utvAeWxTRqKU/P8X8J3GWxHHCeiCdk/dvZYj82OM4a7H2c6MCuwX/DS0j3sqeGF6lawCL9c/ClMOuO5EbXtam7HcFv76LiPeaWF4l695yzn1byJ86CWeTopjuucR5WyynsrVOOe+o02neIMk9hSeFdBuniH8h3nlJ2stGAabc9e0479BWygGZnFf62hOcdwbx/mId0xdHh/PHN8tfd4jz/kS8G5LwRrwaVfVzaCrlK+xL5I2YsVX5EvQS733W61vE5iVYN8v2m+C87mm0RkFfAm/Ecl8q274o8l8Q75LupLxK5ilE/McZFEuWyE23llxe/nxeRrzT1ifwSu9n8f6bTvlyE9vK+ljV72gx8a5M5FVybcX6T2fS/GpMH8uf3xPvP+Jrifn9mMqfj6POopjXWF7lz8fZxDs9llf583Ho2eQXYX3fF7I5VCW/WeH/SbyXd1t55c/divkP4iuKaWdpZUlxFcu86TV99aEGuW3l3KE2sol3J3J7Woha0fXtJe7qRG4l+gFvc8M55DeYyKtcL1pJ3LWJ11qZfiL8X84lH69EbiU6io14u4h3SndSXmX3Ge/zmvMohmRtAr8ynUXEfxL3C4ltV6a3cO7KGRTPNhg3e6TJ5ebX/E3ivjg5t7LfGR93FZ1POVFWc/6qKiwKFU3EIrnNvL+XEGfJF1ZO02x0eJ1BYpZ9rXl78y8g+/jaOG5GK/e9xZ8nncT5vrW9LLEYy3yu7Pm954Vku7PwssXN/oG86x3EvUn3ADdb1yag5vqK+Y92it238sKnLMoqP5/VWOK9kXiXi7F1+VGl5cV0mYNeWn5eSV4zfm+nX0RxI+ti6qAkp9PhvN3E2RfHiYmP+GazWw/RwdLnYkT7LyZ75hexdalDBwQljwvF+ifEeZ/gLHTA9wkTm+AMIcResm3RRrxDLiHd1cJL3jiIr49WQUU+eP5smUH8l/XF8rOQFr+vxaFgvXrObcykfDTx3JSV3etxKcsd3krcH/Yk4a4P+FXlWOol3sdjr7eSMZmwf11K9tx1sZwup8+hck51JfEut/TxUVUVx7OAKbq1VeSfFf5Pl5HuwZ/lRVijjN1bp9Wr4lxGnL44ThX5SoT9axbZDSycVs9N2eOSTOJdQLyVglfdWmR7Xk65dPsEF7uLbDn54xw2m/RYVTH+Id7Zcby5OUhykTs2RzaviH+7gtaPWG/hVXzvthNng5VT0b2bTZwbiPO2LzinmjXWxPqfV5JNYKCNlCKLubZI9z/l48p+4u1eS7xIMVFZUVZaONlRPKmgTMwThzzyn4dH8nf9VZQf7A/qgKiYgOnGZlnFUdG0jnLrw/tkyGzKlfb79cl1wEs4LNkWyeswk+qw4o/qgJGvbDvVGN4PV1M+z+R1UGqraifuN5NzK7MXCf+fa2itZT42sdx1kUbL5uV9Pp14RyTykrKHBJCSbTVjeZuvpTWIB+WmJIUK6iDGv1SHYUnqoGJ9ODH+Jd781Zy3anJldYVjmtMLC5kazilzaD2vNbGcsJv4ZK+BLPLfE+e0ngRO6flb+TUtu47G270xnMpygIv4P+JdFccbMCMXVe7aGiL+73ryCY7jxCNDaVs7ifeTON4ms0n6deWcWTdQPqPuBE7peXl5/84hzilfJHAqseGL9a9upPVR49uq4Plg42MA4jwl7vlQz3437JaC+63ZKrvNvK/TbiJbRG8cv6LfLX8HthHv67G87PHPiWW3mV/nfuI+OPY9oHSs4b2ZYsDi2osfrpJ+FvFfxLt73LuAmdEV+hrbb4keXRM=
*/