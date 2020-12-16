
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
/ezlfg/uqrH1AT9u1StyTnlQcv29VXxLCcd5yIM3m72NemU7jvOwyVXrKs4jPlzEk9yjfq7sbC37z2MhnBn3cT8P7yuVcZ8I4cy4T/p5p6bSfSrIedJ92s9X2xUZ95kQTsSV/LN+3q1XtratrdrFMo4Jz3XmhRl6/hXQbKXsvxDCmXl/MYSXc9NLYRxFpudhJi/qvVdzrzA3mM3wwxK9f+xVH2fe437Nx5l7sF73caKJynK+EcLh2GPT84w3mYdv8Q/503zL4Pxpvu3jzPcSvsPcBssvBY+V4ZHT1vhWyio8vlb3+N7VGuMx8gaNrdjGeyG8tkL96H3WFEdcMexuU2+WY1OK52YSL9N49aH+jSI5Xn0kcbfUO8L3hz5mDF6Oq7BPJAaQw8/mPvVgjaJc832mcbh9T9jnGttc5v0LjVVssoDaLzVebTik/UphOInD/UHSfk0439Em7TcmZulng9+aOFUy+uo7iVfpeuR7+k27D3B7irtNsUHl+EFxDXX/80fGyrbwIdn8SWLO1pj2z/o3rDVK6j7MLxrneqH4sXEZbzfw9zj0WwxNmOa49Nuz/208hdVFn6y1xupVu7kdxh+fubESzZUT0G/drMpuUSzVSjx3TEi8r9lRu50olIOsyedJxNM2zRrcR2FBz/K9yE/Sge/t7UN+0k780ssgP1kHfqnlKP7kHfile+le5xSS18sDxKfUOK2rXOqHUxl4c7TU29e9vCxRd28faabuqFl2meW4P0/j1Sy1dO8y0s7SSy1Dmmk7anq7+5YjzXQdNUt1L9tLmuk7aiBnnNYMHTXL9PRxuWbsqFkOqpP8NpPWeMaWmRmHDg/9grSzMOa4omPq/XazarxmjxVbMF6ijdk0Xi/zNf3sBlbjNfocCpMtlfA5Fa5aKbaRufz4aNFtiaGF62ruTjwYkOWbR2mw2IjNq7Ht7WYd8zAfY1s2IbulLdU99PkZr9g00kq7C0jc3dwZbRG2oAejdrwQYbQFd8RR1/0LE07LpzLNcYt4MVgkOKUtWb+o5sT4gvrFvFgvjic8zizu5QSl3wccwumBlJ8nBTXUcNj+kl6exkvmun2c68CL/LgN9GiOLlFcukfTq3HpU8SXCuA9mL++IC79hfzSAZ5oWX/LEC+XdBhnWS9mDs/IL+flRZmdRlN8R49sLk+8XGph/lfwYuq5yYom3ubnRF5MZhjtrKw5T/9dReINR81rq0qsTfdoVtO/PfNXnHD9jl36jcOxSEhMBrJOEz5OTASSSwa4pZeRXMrPLbWcitfv48TgL7k1/Nxou1biMq8puRoQ7J+0xNpV7GbSzlo+HB3AdtYmzrPHYIAwusXHtgdNzNj3l5G4a7fLdVzvYDvJBnHxrzF5f3WIeCSkrXUY02LCc4QH2lpe4sb4U1CYHn/WZUxfv5Jf1jNxp7WdOTatr7iWgNHOBhJT8zHZ2VDjalKQZdpIcmquJnxjjXva47DEt2ri703k7/YIxttU//b0AUvi2xTV9eJmjLXqtKNMv1Wc8l308OpNyMiNaE4PAZxWiTm4flPplyUGi1OJ2RKDzEp/jDK2dbHStsW0yPgY49s4rc3JuWRjc8JxkoKBFLUOYuv2W4OpQfN55xYmPtasy33VW/px2vKFcSoGZz7bqPpwmXZN4k2bBm5Ooy7wRDxf8Owe4ucxkvPuIEJ7WymubJtxmhL3fsgC47iS86XTUng9kE5bcrxzSNbl1oirzUM4N26DWCpXSPenE9BchrID6UQ6lTfv023bQSNtbNeBN69Lt0fNYDwhLkrlNjwu4w6SUxfehO/owfXzzJ1MHFfUfHccd+VR3J1NjcgI+2AXhfc7tWKFntsoLF1zeB4=
*/