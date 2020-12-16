
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
ajER6zKQGxX+jo5+4xgJIlYN6Z4gKJR7GvCndPyaYnLMqCQppLkOoGIVkIYGUXpU9Au5cdKPybFW/m0KNDe6eqFCWEsOBnBhCB/ew5dr6kAF73VCnZgIxxanoVFMxCp5snG5SZDAZ3DqkExOGEiOHBujUfic018oF4dKJRhwRlcL/npkc/XlpGmdjROitxVUHGueFBQr4LrxrVM7scrB2IhTvqZ1+KNsLR24xIEXM8K/sSFBBTkPpAmIf9YiArlhEVDFhi8oV+CrbXBKlVf94q6Iy5qoigyhM6U8XlzPoFKPp9bTOW1cV0dLVWEFRP0KBBXqJuLvfeCfxN8V4ZQvh1NoGJwypuPS/GEQJ/mp/kT+B0cmRn9whKfw2AoE/+sjfjpYj7c2tzQKHwPzgWBIiRC8WABEoqQUiL/F5RPJHaq/xeIginCwrWtkAwxYhwSkIYHXgYK/Th185r9qKRlMywebcWx89Y9nV8vKIMrKkFi2vcz/gL2CorSCicXTCqtFEwVxZcq/8SR/iEfFISANhZC6ye3AwJ7SPKoO/4degVTgFH6iCzdwvOqbmaBCp0BydB3+D/MjFeZHgucHxfM3NVT/iUogGRZBKsrlD6LEn3UPv2VXA840takcWEAVgwaqGFpf11a9DbpDa9vIhiAd33oHlfgGeZLEhby2+CvkPBle+muTPjyeQRbl2+Nt8sfH2/hnvdvE73pzMq440Lylq7OpcSqahPtuuDa3/TQ8TA+iTA0ejFCDIwrsnDoJ490XJGEQICFKwdYMRjZs2IO5QGVg/KoMpSZAsEx4W11kyBq0pigwBIPKubxa8jzs5EUoOkxoa+9qhZFawm7mJFTgBKqvw3lvEPyxrY+J6KQuBsJn4jEtPiPnMJrOCRxGcIp/FziC4hdIQKN2rBe6d4eHxSRaVwhEd3u4tNDTn0kSCPMBjcm2Dr/RX+PgyVCeVwcIvh/kwulxKBn6Yy6RsO55Mcz/3EEdqPBGUZAcbBgMNfMbFaXx21AcjJOoPU57AQzILxmn8XCtDumwbr+nApLLRw4hjVJ1uAKNq6GNna1NHS1IwVT1MAYOMhtyKTyfJcHR4xmVU9VBxmCHoIJcQyGF57NqwOGDhgVw0a7aXPQjvumLz7jXyuI/lVDqLigIOimA4PVdwRVggfYbnQQgIkmK5Tu7GrumBYFaBlFOgXjZjsliVaB5TaCSFbW3YXxuL3StzPDxJBZ2qgL7NQqA2p2cIZeWOrIWC70os9Qu5Hyl/zinIJDcICBa28a3R63hCEoIdLIIpgcsFpJGVDg+QwBDM6q4X7OACIZUOIoAyZQ1ebClylONyTOo1uSsgkirxsF0kyjjr7MDe/VjO5gvCwzRAvzKBr6I7U/1Iqf/v+yd23brNBCGeSR2OV/2ECCL0pYkLWxustIk7TakSYiSUnh6fnkk/5oZubyAvXZ3PN9Isk6WNbIkH497TZD7GmzhyZOUmaQqztyH+bD+K1Hc4RcfZ8lUMwwZYAmCI7o6n53THxG8KaB9dfcxAXwo8WVxXH5SxIYQ1m2R4qFew9E2I0e3T/pGGuGiBuAimugCfrj9aXTF+8jRxrtkkFjb8IB+w/Wt9K4shGeH6BerG9Acpk3ODYNPS+gRff7rkXvO1ZRRZznvZq9iTAjTa2MXvrnXvdJfwT8Fvdrf9F7t73u60be+0zYOMWMXy+V6385t28NwXYdCg85Vu8fH6bh7eiKPm3Yt+Uk4C+UD247GNTunUGDptFJOPVYhMWBkf7woQQoDP4cCHne5nMScytcnwEBGs2qOOWgMQyg3h015V0JMy5J4HflqYz7nlIJM0mbwdLTbrtEuqUqUPhp0OqTCO6TPeSI=
*/