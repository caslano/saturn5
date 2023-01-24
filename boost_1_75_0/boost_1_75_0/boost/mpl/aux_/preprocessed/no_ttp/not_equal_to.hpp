
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value !=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* not_equal_to.hpp
UAuvha0zrxkvf4Bzy53dc9apM+6m72Q5GcZ53HAQUPiCc9m/g7rW99Q1c0N7OkVUQVo1cMtCppx4WVnsbZ4ys63mbQm1wIf0Y+cwulsaRkqoqEAETdVRbT1uRvTD+0+Firy3Mrssle+lXYvOyFN746ZmAyFALIHr2wMTHKU051EDeMaC+EMQ6RRWHE2hSaFJKcMTkdrsew+azke+qeg8G13Fi3ITWdWj0J6MDQ1SVnnav3QoHoXC393rbNNbH5UmDLU88jQ/4kPucuBkAvYVm3L6goGpNBXM8nXhUgoaMdmbo4FthQUaMm2bg6Pwl5KqBcWHmv2KnDIAlCrpiTgjLwchi7+FZ89kKyr2i9XdGiN9Z9AKuDX/KUxffk4WgPqoek8lSTgFUAOENgrPbs7isTxJuBbcXEBi4Ag44z1fYPgzqiA1PIEMfwOqdltVThruYFKWAbHfcg3vVd8sBBQ7z0rPgfbuKrn7majrVQRXnFALHt5e08Mvpq/9M9/PteaIV2gcafWWXnRfBDD9XcJOLuNTxZ4XXMGqspUAJcoHA4TULT8TNeN1xz6Upe49Oxn2KuY6hTKvMhnMoHczVpyqCKq7bpLWzsXlFuxMPG3UCK9lvu69mMNDtIVzB9apQmB+m5QtlRMM+WCW428iWconRnOjHymouK21QY6jsYkteH9votd5MOHnbafZH5ZiJ6Sn9P5wqeJiHKsgYi07
*/