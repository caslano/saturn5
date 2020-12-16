/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_TUPLE_FORWARD_14122014_0051
#define FUSION_TUPLE_FORWARD_14122014_0051

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

#if  !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
#   undef BOOST_FUSION_HAS_VARIADIC_TUPLE
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
#   define BOOST_FUSION_HAS_VARIADIC_TUPLE
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
# include <boost/fusion/tuple/detail/tuple_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    template <typename ...T>
    struct tuple;
}}

#endif
#endif


/* tuple_fwd.hpp
22Z/XLLMSdPAqd8NgzhkNQ96wxYe1Dul03TW1DWbOrHHi8Bnp+vjDMdw3e7RRL4XJ67r5SHKPzFL5eN5JpIXPssTj8dBJoNj5bv5WxBeehFC8geYJvONAaoz8bLMLfxS64S5DtHpPFnzkXLK4kykRZawQs9z8K0WYptgIY+dNE+sN75ODWS7UG8U23eMEX6XhS7PS5Gm5I7jJmEDjOUjfAGL8oCnuSio3tOjwTIMglFr40t/TcssS30/cFxWvKRCnsC1E6KHs1K4URGFDtFDAg6Ns3pW3qROljlOZl3fDCcrttvvmh2+L9WbOaEbZ6GgemkQKfp/i9fnnuckuUd4aTAo5osweY97QZ5lvpvKoSC1r7R0eEXuZbETUh00+BPvNjZ5M5YUbpnlUaE63Lr/RBYcp5g8KXN5ksVF5sjJGezEncB3bUyeKyZPyWIeuo7rhqjHLDWsjyRdLiv9JBGuH2tF1b1IHqrDMTTVlQRuJALXRV1YUuZ5PaLLZ4ETRSIrtarBBtxnvTlCbSQPb1J9XPhJ4SUB6jNLF/33/ejcM818P+NlSNMGQxefaKbvpN+P6A3SJOGOcFAvlriRp4LodRmP88AVXoSFN7wwGG933PNK+BwWpjyNw1AwqGF9WcH6Zgkad64TPrVknzhBnGt9eHS1UbmEd29aOoMs4AUPHaoT2xyet/qSyTfPnZSXhRtIjbhxLnB+ZmJPeH6YeI6fsjesDrfWRpuba9pFYt2ieS54Frmu77KVVTjD7VzYGhjvWWsdvyA6Si7iIE8jVp0NHm213vK4YeKfFxU8jd1EnUskexyI/xeRH4duXopQywdnb8vff8CUn/JUOJxzeYSE7IMcDbT/M/HcZwF3CjcquOq4wk14XP74HOw4nzgxV/sa/DgDK3hNPgiiN8mj1MliPCOE6ToR6zU3olewrEyS0g05C4vTizCcOjl/fO6k1jyvNM9TkrEeQXTHrivi0g3wPJDWfQzP4RHdnKXcKUMvub00n2j0LjxyysxrL47jwIkYTkjsNF8jegNWOqErwuL/SvNNkuaodAInjCKZZrKveAxjs+5P1jijIg7DwIOZbv8CpA03hhE/ImnLfB64buHgESaUj/Ot+9P2nHi+W7pZ3k4b6sL37J9q8j6vjNI44mFz7Kmla4Ho8pnvukXihZEqP5E5nJYhjWE107UQ+EmQ8CDGdGkfMofnl4kuj7kiScMkD5nUUxcPTRp9S2TV5F9IY+6meZFg2rS+k/i2LMEnWelkLi+ZLKTZmRmML0J8j6xtZXHuR47HIs93SB08ifsfJD2cRW4eCTcixVS1bdTGMO9oWnjpBDFXpwaWzEp3Uvvqr5r457plXIZlEDOjwhnv5BPZLo/K3I0LnRB0IJiOH1j1LS64TEneTggWCsN1CCuPC545aa7TgQ5jBs+NkHQkaemJlHsqHQsnrHT8i8j2XF76WRKrdJgOfgbvLHkAXRMsEpGnXlonY3bh2Bx0pKDFXrc7bPItRKXPgzxKVBpMR38Sz74CnpwtCIskLMs6EZDsjfZ7+wtQt8yzGF7g+6EL66sYa2HhiU0xz/0wD7hSAQtWS8t2OYgHEL/NnSDnuYB1VhqPwXDPEPF4b1Ho+LFrZ5axWIG6RlSXHwnfyVKZFtLvnsC9a6LLZWkcRbnjyEeYz588IZO0hQ7GzofPEl1JmYo8FLlMF+mDT+J9TkSXz4LAT2M3d7v7hfJUoCQY7xURfangIs/LrC6nwG35z+uWvsJN/JjHrtH/oQvwBPWfN4iuKHOFn/qJTBvpa0/otP2L6ApYkZROXqbJLg5n3tZ3+IGkb8hLN+S+D2mj+50zuJ/9QDsuLfO8IE9o2mROesI=
*/