
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
joB58FBYAFPh5XAkvBIeDq+FR8DFcBSsg0fCJ+FRcA1Mg+vgaLgBHg0rQpwzEG48vbPW5zdx9dbW7oevxHT5+LrD2v3kdbbOOHu255rTamkraJteMbF2I0aMGDFixIgRI0aMGDFipIPq/3nDUE/2f4ty/31U/1/V01P/7zHpLf33H1/mOz5sWAr/x398k//4iEOtx+O21/HhqQHvH+c7PmLoMI57aw4ydiemqJzjPIe5Bbn+mgPv+baZZ/Su5SWb6x1sugNscmIh5K0tdonP2ttdEGCXCxOm3QUOdmusdrmw4Y53o4Pd2gC73JgQ7frmTyxVfcBE5diPgk96gsxrvXanV5QXe+0d45K0M59eQZvOM2Pdo6Fkdkv9Re/mNdU4Rq5UefKxjMP7wCh/2sCxF3ijOy+ftHjzsU0cm7xH8/s4GDB3Y1B3+/komWsjPx/F1+dihz5r3mrpk6cqon3G9rDvM3ldS588GRHp0/fcuHvYz7txrY3MvJsNDvYT3/Lb50Mf/r2z9pG6nX0fo1v64FZtWR+LHfpoaOljeOoWnocrxr6PxpY+uP1b1kd1jN08KLi24+ZBDdNYEnrajyX3LctYuHPt+Wy3Zzx19uOhoMcyHu5AtMfzK8yOYJ3I1jIfrLPqPjqrviM+y3N8btot9+yQvmrwcXdM++ODG8sKneo7IlvHkezS7zn9FmnsFpgfL1F+vBT2hGWWvLrbUY8+pXer9G6zztNqRa9Oeo9I71GLXk0rehuk95703rfo1bai9430NknvW+k1ufSbSb+lGml78d9fSm+A6iMOhHsrT38ATIJDlJ9PgYfAdDgMZsDhMBOOhIXwcFgGj4QXwjR4IxwNF8MxsB6mw2dUv/EaHAfXwPHwCzgBfgOPV51EJtxZ+8T0glPgATALDoYnw5HwFHgUPM1yvTJ13v1srlc/Xa99YAJMtN6ft5z1LpPe5dJrqV+hrXPWe0V6r0pvubXuReOMt9HrLb09YBzsY9FLfMtZr1x6s6VXYdEb3YreXOnNk16lRa+hFb3HpfeE9J601q20ove09J6R3jLr+em69LfR21N68TAR7mWdd/mWs95F0rtYepdY78M6Z70XpPei9F6CL2wTWn1Iz1dZB4+WSsukFdLI1wfVi9jMu2yjPuRXWs9vu7dZFzKf1lt1IKr/2Kz2IwVm0VTvYV/rEVDn0XZ9x6KjnGs6ptFaq+NYQbPUbjjWbFR8zfnDaprqNFSj4a/NCKrLaL0mQ/UYqsVg7LQN33RXDUZ48xvt6ywCayxqA+sqVFOxeS3FRtp81U/8QVvAM7SItpS2nvY9refyGFcCLZk2jpZLq6BV05bQXqBtoH1P677C1FkYMWLEiBEjRowYMWLESFeXDpj/X17kLijJj8D8f98agBO9Of1ms0MPTfavATjBsgbgIIecetMafy7ZbyCUnEVAvsthDcCGNZHPuR6kPv9yWAPQvSYyucgqhzUAa9Z0XO4r0msAhrs3f7i5nXD3Bws3F2Sfg9r6c0H2c5vDzxFN8OaI6m6qfr187r0rTt1jSM/lS2ad3HE5Iu93CdzBZg5limK8I5RDOdQa+5ZePxu9faXXX7H9AdbckvTibfT6Si8OximmLT19hrFpo5cgvb1hom9fLMtcxYQVZg3A/8JcxUitARh3WI8On6cYTpy8K89PTOWzlEUrpM03MXMjRowYMdKJ0gH1/6VziosjVv8f6/X9Meld+r/Z75+0u8tfQ57gVJ/v9/vR8w6pbV/W6h/XbGZXddZR9PmbgvuUz58cIZ9/fnC9vXz+0Vuxz2/W/eqaPn+4vv0FXt/+lwF3XR23fJ9/+u9Sds+aqV9N7dz1vZJpfI84rvs=
*/