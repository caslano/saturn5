
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
IxwLu8NxMB6Ohz/B6Vix+Jkofo6BU8TPaVLvYNgCDoEnwNNhexgPu8FEaIdD4SCYBFPgMDgODhd/iu9q8ddS/DWCfcXfdDmuXDmuC8T/DPGf56lHfuPhCQb1nC31pEk9k6Sec2BLOFlVj72WejKknkypZ5rUkyX1ZKvqSZV6TjGop43U0xZGw3awLWwv/Xeitx5+M837p7PU00Xa01Xa003652Rv/jv57eMzg/x3PaUeu9TTS+rpDaNgH9gB9oNdYX/1+aulfS2l3kh4tGrsMkra10q99nhFYPkI7RW15w98JTSwsbP60EA31BjZ/3V8LNixsUDGxAIdDwtoLMzKVxPQmFdDjHc1xFiXea6a4Ma5VjCmtROrxmIuZZwLK8LuwSqxJixM3hebcpk19mVt1mZt1mZt1mZt1mZt1mZt1mZth//WUPn/FK17feX/+0aV/6/jEbLOCBaCpWNjoxjLfMUzB0C8B5ebzWfdN4+/PeLvd4nz/4qNUeKqen/kmQo8L9/WFu4catrcQ1m52Z6cgk4sqyAXUEY1j4B5Bpr1RNlFE4uMO1Kfk6yKgeCKVw1zsEk6Mv8xQc3aqwaag7si8WPoA3G+33X6dfMSNNr8Ac3N13FPM9Dmj43mP69ptfnjJiYkj0wZPrYucwXeD9e2J0M1V8BaP86KhzZEPHT0Ccrn4YMeebDzl92qOpx4/Pd7wxNTGi4e6rrHwkyDeGgLiTtFwKNhS3gsjITRMAp2hK3gQBgNk2FrmA5j4E9wP1Yifn4XPzHwW/HjjredAlvBWNgedoedYQ/YD/aEp0E7TIS9YBLsDUfDPuK3L8yB/WAe7A8vhANgMRwIb4CD4J3wVHg3HAzXwiFwA4yH5TAB7oBD4WswCe6GZ8AP4Aj4FRwJf4bJ0PWbos679KrkZ6p9nTXutYGtx8Z90Dh+J+uhrLPid1b87jCL31mxu39/7K4+4naVxOP2YRGXh9jisOzLrfictVlbXbeGev93zWNXBgDq4f3/uzCbN7+4vI/fDJvB6+E4RWe8U58DIKsgJ9OZYwto/v8Xz3rm/8truW7+v+fdbzwPsyrptOn7+j5VXoBwyQvg+95f7SdXgOTf1+UGkJwIrOuoz4t8ptIfz/n2h+RHdlXsv09knMK7Br0uR7IuBzJ/c4ySM9k506HJcV8l7Rwm7+hDsYnUHfa8bzslqX4QmnTfvukv18oB+anohe9msDtcHEn/G/hkFMTlL8rPdVL8ous6uWBOoTM9Ky8nM3+Ow/V5/oue60eaYnT9yNr0tCGnyJnuyJqVr1uf3vCce9fx79m8Zt/M/Iuor6a/uR75jPZwRIXi50s+f8vtR5JVqMe1pod6r5sQeS84S9GOv2SUS8O/Pl57rNr8Fd+Kr4Hiqz+Whq8SY1/puQHo8d3+wql71hynJzeH0j8ictdcC9NFn99O2tAGO41+q3pJN47HmhH+rz23/0FRqvUq5O9pPse/x2BuwGLKhb2sHZ9SxqaCzZ2xKEqfNz7bYF7ANZSz+/ir61gY15tmLGx7C/VYmPbYPzVoy1L2TzVoS7A5MxZF+c+ZMf0o45wZjpfNcmYEt2ZBIOsmVBmsHXCOcv2btiG4NQviorRrFiSKX4dB7v5Q/JaZ+5WrIfA1Mjh+zbWQGmWeQ2VfE5M1LF4+9PlL3H0y72h9GxrThmrTNgQ/Z8Z2EHNmrDwq/42x439qjHi+a4y4y5r4Ra9Ov+2R7YMvOGfqs3O3NswYMXlU5Dmc53ODPCoxMnbbFkbAdrA9bA+7wA5wADwJxsGOcCzsBNNgZzgVdoELYVd4C+wG18GT4QZ4Cnwc9oSvQrsqr8r7sDf8EPaFX8J+UGl0f3gUHAA=
*/