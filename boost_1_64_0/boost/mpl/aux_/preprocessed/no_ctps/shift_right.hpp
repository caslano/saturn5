
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
r/xt1tZSp0rMBpu/06RNGvVx2bQM+4GmPg5IbIFyzAywnKda2cZm2s9DlFZnRTtmlBgOtdI/Xwx40GCaBso26U9qpmwT2xi0u0eBtwv1cNfrwAatzXGt0sR1VeJykriU5Z42Em9r27hSivi3hjou9bjjshqbWDZXyf+7+LmynbSxFPH3Xa+OuEZS/y7y2eZ3kc/2fxcPSp2u1tRpXFVpAyXl6C3lyNaWo4i/78VdDrc2+uW4VVV/3/BroylHEX/f9cohY6XbxLGLhZSprrRpehjXEEdo/jjkcqNw1znEke/vUnVbUXUbeXWb0JqqulX/Dav+XexRPX8driP2rLaa2Ivhd1HnWFONK6C5/yNxbZBz4jrSeuLK1cYlv5WF+Ttfb7t+Vt12/9QbhyFYBpd2kbqqqcSnXM+2s8TUu9tw06935KSC/j1lub7f42kes1y9n8VGTLLJP0fyryP51yZtUs7RNvmnFCn/v9fWz1/qw/SehbDkaJv9PqJG/r9nnleux7wt8fTtFtijv7+pSqJiI+MiQpShne8Zk97vqfq33JWKV6Ylku9iUlUj871tx1QIi4gocF72+5/IPiHHnOqcxWf756ytplj4zdD81u+V2EMk9lGkm6wnyzb2It3XtBnngRhuSAxb5H5aFR/5rLl/FVrLvLKZEtN0kivfGeCjiSk+qcCx6NWnuv6qaOrPWVN/mRLrVs29v1yJdZLEOoH0oyfztbFy768wf7tSd/nu/RGf9d5fWHtzPNs0dbdOXvgyXeKZSnLmOxntbeOJCI8rcCxF2RfVdVeugznW7ZpYvR8ymKZQUmW5RtvBd4wdbGIt4H1KYrXGIedzndhva+5R37H0kzDYbtcDEltnqceOclzsso2t0PcqtcfEOambLepxWuQ9CMo0WfKfSPqDZQ2+tvkrp7JeScmJYyPHpPLWCs1ALUU7PvTG3VHfB5mkuQ8y2XLOkc9TUG/MnWRfc1lfNNr+5k97mP+TfbW0lLks39mgU9awKPqjRRbveDtFKae6XM4dzeXaqSlXoLzcJU3KlSLl8utYwHLd5zg791uul9XlUj/vkHKlSLnGk2rxnWxNuUxdF+/z2dxy9TlaE1+fTub4XtL8HZ5R17zyWIkvmlSb7yR1solP08OxaHHq1zXHtcT2sub31rueeYXxEts4Ul2+Y+icL7bEBNNVQsH/Prl3XPnrMKqzOc5XNHFma+OUbZyhiTM+bFykeee9vziX3yPOHyXOl7RjrdXPf+9mN99x9bOJs0j3btR1p/7d6uNqME2JpMpSN3vI06jNMy3unv3DqxXgN7am6loqWnr5Wsd1U8cp33WxXN9avqtzPra822Wvun+y/D7uM1r7J9v2u5Zyn5NynyW9plxv2Ja7QPes7JVbfo+t96hiHjNv9/2a38cTDfL/Pt5huazHNOOY/Ym/j/bHMVPfR7A5v/LZ/u9jly7msh7Q/I6sayjPl6WsR0mllO3WRVPWP+n3sSjlVJfrSynXQU25Uh+RceilXPst5epawHLd5+/j/ZbrH12lXJrfnyqN8v/+/Exeof75y5WaaP0BKsay+FQ97m+O7XXt/ctG+d+51Yjv5NrGlqI+sRfmXobeecw6JoLUsarfs871gmqMAilLejdzWQ5p/g7JfDT/tau7cj7qpi1LWlxh/kb/d439oJTVJcBc1sOasnq7GUxTB9lu7aTthF+AlNV2YJICby/1vSf1+B57Jb8GUrf15RlARoClf71pKV50pryzTvUooIj1bPM8n5iUaauUdRPp755sV0ve6rv+1oeF9x5DVXlOMpi+s3ft2y/7n2wT7fvhSsaaLBlr0lAhRpnfe1Bg8/f963zzokdMy6U=
*/