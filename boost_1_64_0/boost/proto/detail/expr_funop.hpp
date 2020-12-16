///////////////////////////////////////////////////////////////////////////////
// expr1.hpp
// Contains definition of expr\<\>::operator() overloads.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define N BOOST_PP_ITERATION()

        /// \overload
        ///
        template<BOOST_PP_ENUM_PARAMS(N, typename A)>
        BOOST_FORCEINLINE
        typename result_of::BOOST_PP_CAT(funop, N)<
            expr const
          , default_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
        >::type const
        operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a)) const
        {
            return result_of::BOOST_PP_CAT(funop, N)<
                expr const
              , default_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
            >::call(*this BOOST_PP_ENUM_TRAILING_PARAMS(N, a));
        }

        #ifdef BOOST_PROTO_DEFINE_TERMINAL
        /// \overload
        ///
        template<BOOST_PP_ENUM_PARAMS(N, typename A)>
        BOOST_FORCEINLINE
        typename result_of::BOOST_PP_CAT(funop, N)<
            expr
          , default_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
        >::type const
        operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a))
        {
            return result_of::BOOST_PP_CAT(funop, N)<
                expr
              , default_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
            >::call(*this BOOST_PP_ENUM_TRAILING_PARAMS(N, a));
        }
        #endif

#undef N

/* expr_funop.hpp
atzJPkwFbstULbvacMfKEw09DRH/3nlPID7mlWtF7Squ2YsmJ4cpe05krynLeOVadGOHrUJzyr0TaaE/Vdv54DpXzguQw1kp99SnKb4HN95GaScYIAz5whbtRb44GgPfm1Zr3Zf1wsFFKh7LGQUNw3SlVZChHvlQ4vkwPvv2cD/9jtJZ5UEYyN3FEocu3Bx80FX8mcI/wndVUNx7jJZV7tV/FLB9XYGRYTUbnoL2RZRjXlPwMq5Wxngt07Kab/Dx3rotxakVk65yhgfLrsBawjtg9s/DYQguHxycjWk8eERDO9kJbxzSgL0V3fIWCawMvveC0uAV61RXad7Z/1Z/vhVDlKDMieO3TWleAutJ0UGEjkelTGgXV0e5gY8RHm2IhJMVF5LBcsLsUnBNLyoOp5eQf6M0AnNSeV5ZB4zXEx4FdIBx28/TcAB6kx/cbXmOH9DD/Ohu6M/lfKhEfJuHb4Ov1nrVo39P/I5+WE8KIXI/gXy/JfleJXve+B39q54+h0OfqvpJaj2GFMtw6E/V5TbdLv0Gu6WMe3tSR0fafwf0UZNDe+5IYNczLPpb6ahxSvqfn8RvyCBSG4ebRmbrAaWNQ3qgI0YOaMfwnhksptodvp/eFr4nLOq/8tXbwXewLY8TRnQ8v7sDfIfnbXycIrzdM0Y+r3VjpGst8yN7ZPCdRZE/2SNXFY1nfVrS8ZEQF4IzTe6T1REZ6H66twf76NPSVspaG5T1vNCj7GxRg8nBjjbpgjOt7xW0wJZXGc1Ng7QmYE/BwX4Cc4sMPpVQE/XTuP5ZeQ9bzbngncF4xjtLm1bKzvegNCxzmiulTctSFpKzk+ibvWCz8GCKww3johWVq0zqw3TWiYOcBhvSP6zOKEHX4oyf0Lz9T6W0Hsm5cdy37Sy6/w6m3c72hGej2O685kZqy/QukM4x4S+T7uL7dUwwW8zDB85Kftb2bad73ww6nuPzJnfB5/6LRbs4a1pVq9CAjd7yKUg6kbkIOtxRn51S+dZXTZCtMgzCVmzCkkeZPscFmpbrkvvO1jw0bH0u2k7RKv0odgXjX0yTNzV52zst6m2si7x91yebfciqPdbxvWpa2h7Ipm17EeqFel80uXax/wM//7ejInZ3G/p4rYAZ/KDzXL2EvEExX5BPoeKd62piAw91ZEyDd/JxOUYuSBM6383ilU/RbB2NQCC/19Hzh6ggKR9Bnp+Tgt93baPaXnUsvoRFm5DpFNcr9u/bFP6S4b1srLBs79orJ/sJdJA9fk5hLyteub6vDRvlOSC5uJNNpeSbzZp/UooMR+X3t5Tlcyed6E0SbdhRF/BOhJk/CMzNLXYOtlPeH4R734gWGHGipecRid32kUW4zSMw6Y9LDGl9YgnM1tHuZAsokbzanx7BxRskGePDa0Esv4j5t5fAzZb75rDaZ5snyuyI8/mFNpyPg3370pJ64ISKRUfY5q8u0k1H6Gajjkkc0W+UcCn+YjRdQZvYb5fl4GQFEUATKXhtJTYa30XYFCc0pSZNoMD2PB/b/0OEQzLxfL54mOxaEOZnGSZ47TbSmFy8ckhhfvmSHE9Q8tANVu4E5o4vwZiC58P8NsGU5YnryPqfPyAMuNfDKJAx/GtRBrNx9eTo7DivxafTNgzGxGAznPfQLS+AeWeqNBZcjbs+RsE8ybbJ133pgr3xuEOHCPucl5R2zMuAEfZgGSxtJYn7/4/yfu6cUg4O53S/Fhf0SX6/fmEpl2pV607J+r/k/2e5M6n9zIMLehVTvXCQsJXxJ609WUIo+HW+pgNkNIu+LX4j6paeXOkeMsnlWA14jveU1qMaFekobdNbfMqpfM2UGN5s4Pn4zALPeW+CE2w=
*/