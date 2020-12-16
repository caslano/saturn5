
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "unpack_args.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< int size, typename F, typename Args >
struct unpack_args_impl;

template< typename F, typename Args >
struct unpack_args_impl< 0,F,Args >
    : apply0<
          F
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 1,F,Args >
    : apply1<
          F
        , typename at_c< Args,0 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 2,F,Args >
    : apply2<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 3,F,Args >
    : apply3<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 4,F,Args >
    : apply4<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 5,F,Args >
    : apply5<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        , typename at_c< Args,4 >::type
        >
{
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply
    {
        typedef typename aux::unpack_args_impl<
              size<Args>::value
            , F
            , Args
            >::type type;

    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
XeXObcmkFdQ/hVG+a+41lS/XbxvXPnbd86LRBXO6PFOblr4B24xh35/K9MTsX0llZ2lDGxto/5Pa0Fb4ZyMvi515cS1CeNtQSHZlryyztqEnloXWhhDGMQR5Nm1I9WrTZioCtxGuvf2HtJ1tIINcz0ZWjqHwYqtdmPOccdaEzG0mQ/4B2hDxyBKr7wlvu/f3PbFF9v7TZac3Bc4w5mf3mXw7uHpoCPb+9vNH9RWSCM33hJGf0gau9+F2xt58py7qe2rztF1nvFHE2UhgjzQbe01+EdS2aI5ce+3IdP6+grd9FShj9VUOp8BbjDFqhakcjArNHJeZnhtKn7Evi1380UiGPhLAjwh5NLUfDae+ZWSpw92yqW+svhENZ6J7wlyn7rntMq3PiJZB+kWbeZa+rWdGcNs//uPy4aC8lVvaqtcfhZ41RhHY2V3KJpA49LKIEPqLcc8urv36odo+OiFLPloo13LKawnXd92hfqKxVH3bGETUPkw+6Gx8CsTzb1ErLef4Y9Xe+7LeSeHZlV/YyP8c/R02PgXaN0KmrbzwbLnn+dhy00/8bLlH2tjxd0R+oq388G25LwzBln8rOtj56XCs/HX8dBhrwXZ+OgpXHn8/HTvQxc5PR/HK4+Ono3MTnzUTrR2XueWbpvtV9dPBNl2/+p2NjHIbGeHW762x/vXb3sZO/zajnB/wl1eV+mVcs9Tvc5XU7zobXebGkqKNLuH66UAPS/1utvHT0d7GR8CdxjPDRn647YuyD9i+ekj+0mb+7Wse96WY5euVriptzF3nUc3929gC5Dhs5FSlnd3l387YY+tftncTr9BGZlXqlzmEpXxHx/iP37Gn++twDzoU2+hQlTq+K1Adyx5/b7U9/u/eHj/FaRd/Vs3VI144ZffZ/W+b0HfStpGP/XZ2+nc79Umf8Wq/p1pN7RfZaOnhJ884/M/jZ6dfUOi1v3b42Im2NdvtKF49m3htzPYzihcdJL3SSuQOM9v3VCI3yWxnY5YbOD0GgcByO5vtvCqR29FcLndJbpD0HJWk181s91SJfn3M8SpJr5e5/Nz6BUmvoBK5g8x2bZXIHWBuBxa59ullEEoVb4fi1YOjFO8p2dusld3s32Q3+zTsAUvgUNkB3yn733tk/7tWdr9l8Fmz/4X5sk+vvH3ywFW8IO0p3h0vSP2nuOMFqYdCd7wg9VCqeM2C5KPCFC9wPggLFS9IPhLd8YK1J0s8+3w4IrQmrLVih4/ddLrqP1P2y9fCnnCC7LmzYA6cCAtgNpwDc2TP7YCr4XXwMZirdrD3BK3jan3XkNvFZZ/u/B2Qvd1h2Ez2cnHwiOybuRH7ZiD790iYBWvC62AtOBXWlv17HbgO1oXb4Ynwc1hPdlwnwQayk2ssO7nOMAomyD5usOzjhso+7moYA0fDhjBddnITZCd3g+zj/iL7uMdlH7dW9nE7YBzcBc+UfddZ8DvZyR2QndyPspM7gTI6B0bDP8Lz4LnwMngezIfnG/LgBfA22BqugBfCJ2Eb+DSMhxthW7gZtjP0gBfBE6mP9vAk2BFGwc6wNewCB8BL4SDYDSbBHnAi7A1vgH3gNHiZ6nt2hNaP4Ta1s1PhdLWz/mpniWpnl6udJamdDZWd/DDZyV8B75LfkQVwJLxbfhWWwlFqd6PhCzAFvghTpc9Oo261Prpd7a+z8f9qfw+o/T2s9veI2t+j8DLZLV8lu+Vc+AScC4vlh+IpuAOuhe/Dv8E9stevgYwSeBJcDxvBDbAlfAaeBzfCBLgJ9oab4Vj4LLwJlsJb4POyP38BLodb4Db4Enwdvgy/g9vgYfgKbEZet8O+8DU4CL4Bx8EymAXfhLfBt+HTcAc=
*/