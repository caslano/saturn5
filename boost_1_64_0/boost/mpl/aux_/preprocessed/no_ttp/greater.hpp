
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater.hpp
p77XdemvvgyewBvwR+yIP2FnPImnkPO9PCfBPiffxzrx7zB5DtMu9TWpWB3HYiMch+1xPEbhBIzBiWjFu3E6puECnIQrcDK+glNxG07Dj3A6fokz8CjOxLN4j/SXPQtLYwZWxnvxerwPm+D92BYfxG44F+NxHs7E+bgcF+Db+DB+gwuxEGV9BMNxEbbHxTgCl+Bd+CROw6dwIS7H1bgCt+HT+DmuxBO4CjnHGVZjNXwGm+Cz2Aufwxh8HlNxDc7FF3AFZuEGfBHfx7V4EF/CU7gOiwbzvR9r4it4C76KPXA9mnEDTsCN+ABuwtW4GbfgFvwIX8MT+DoWYj94Ayvim1gP30JH/bU8L4IN/NRfH2f/vBZ/wpvxJHbHn9GIpzANT+NiPIMv4Vl8H3/BY/grBjPvHKyO51z7vTwPggP97PfvMF0Q7sAq+C42x/ewP+6U+XQn3pD5WGQ+RbGNzOcDmc+HMp/dMp+PZD4fYzLukfkxD3legzLI/EqiSeb3qayXz/FG/ALb4n7shwcwCb/EdDyIS/ArXIfZuBO/xiP4jasc8kwGtvNTjrVSjpewLK7D6vgyNsRXsA2+is569GyZX1c/9ejfSjm+l3IckfVy1LV95FkJ7Ohn+7wh+XkTK+BbWA/fxva4FV33LTKfRn7ms0Hms1HKtUnKtVnKtUXmE15Inm2QZx60+dTk36GopZRSlAfHYWscj/1xAlpwIlpxMk7AKbgM03ETTsUPcRoexOn4J85A7bw1E2tjBjbCe7Ef3ocT8X5cgLNxJT6Aq/Eh3Ixz8GOci0dwHl7A+RhKeRbgTfgwdsCF2A8X4ThcjI/hElyPj+JOXIrvI9c+2Y/kmQi0+tmPqst1IBxrY028DWvhKKyNyVgHTyHXBHnWgbzJ/K7BLjK/G2R+dWV+9WR+N8n86uP92ADnYkOU/UKeZWBZfvaL3lJ/EIWh2AerYV8Mx35S3kyDPJ8AA2S/4PLK9UGeZZD94k68EQdhRxyCvXAoTsdhuAGH4484AuswLyMOwWicgzG4HWPxPMZhWZZrwhpoxgiMx25IEeX3HnnmACv7+b2nVmmOA6yN12IdlHoWeSbA8ayAbz3LSSnfaayJv2BT/BX7Yg4m4zm8D3+T/f53XI3n8WX8A3fiBfwCDaUd3/ML4U1YGNtgEA7EYLRgEUzDorgYr8EsLIZbsTgexBKYgyVRW1+l8HosjS2wDPbFspiAITgdy2EmlscsrIDbMRQPYEU8h5Wwgnb/jQ3xOozAyhiJVTAew3AsVsP7sDouwRq4Vfs+QJ/xbxAHiJw+xfN9R0EbbVzf4s73FMg7ChzvJ2jM+IwCvpugA5/xeT9Bgd9NcLJrkSv+boJA30vg+U6CNGL57qAr/k4Cj/cR+L6LIPd7CC7hHQTBG73fQxDJtjMRc4jlxHpiF5FN5BAh/Yob6hIdiGGEnZhNrCLeIPYSx4ng/sUN4UQLoj9hITKITGI9sZc4SYQOYF8huhDDiPHE0gHqnQcqqaSSSiqppJJK/vr/j71i/f/HxpkS4rSO/y+p3//y9F8fFOx4uC7IYEpNSpqg978/M9SR/x3qe55KKqmkkkoqqaSSSiqppJJKKuV7/3/F3v9nsulhHJeQ3DTi0t//V516gKQInqdz1AMw4ySzfZRj7mRfrxO4P5RlyDvtGsvvwiWIIKIYMYkpo47q79bp0q+3sVfX/t17dzFKeQJo7673ESDzd/YfUUPmX42YwvyjHfM3jrVZrLQgjzcmXmy+4cxX+pbDBqwbY6fU+HjK62yfflMI425LsSbF2F3t09+syLjIFFqtm/X+AEIZZwlmXEfryMgEreW/d18ws+XZt0FEaWkjOZW8znE=
*/