
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitxor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_
    : bitxor_< bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitxor_< N1,N2,N3,N4,na >

    : bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitxor_< N1,N2,N3,na,na >

    : bitxor_< bitxor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitxor_< N1,N2,na,na,na >
    : bitxor_impl<
          typename bitxor_tag<N1>::type
        , typename bitxor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {
template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  ^ BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitxor.hpp
qOW6Kj+vq1FdZ/XwZZ+osi+kROyr5bpYua5RLdcl+BlfWol/9pXWcl28nz75+OPjD6v1x49ZG+S3T36g/vgpxO3LJ79kbZDffvl/h0/+zrVBf7tfvj8++Xux0+2X79sfP3xdkCUWcfjl+++TL/74vnzxxQ/f2Ac/eV2Q3374/vjgW4nPhx++ywe/jOvUfvjb+G3ki7+b8+49rgPzwz9IWK0v/v/DD7/z1UE6X/x4zuGPjy++2g8/MB98yxnBlhORJGQBsgGpQg4p53vjb4+UIFcj25B9SEifYEscMhVZgFQgO5EaJKRvsCUWSUYWIBVIFfIDEtnP9L03D/MwD/MwD/MwD/MwD/M4Usdf7/9vS1Vg9/4/At//G4SlvTy+l/+OzGnvhGe2Vyad3f6g6cUlyg7VBU4fUJvf+5A61qnzQ/DDKbZ53W/chrD1cbaiIIJzK8Qvhy0Sc7MURze59mrOK/5w6Xm56UVybj3nprRQfMscTqqKjgoJnyvXbOT3qxHYkJtVZBPf3Ls4Z+XvObmFRTa5rlzishUWu86ttusUWywe+5OL//sB2c/1M/hKJHOB57rzbnZmkTU3S7JP8i/W7/yrH5qa5rGPq+RnBsbr8lO1P/64YQN75Gc5zu3mXDTXKHtkWlT7v0YrvuPUCdnvVZNnb7n/jhex49we8TUmLzLISPu5KgnHdZSU9lsNiyV/WiP8kzxy5E9Iuit/7Bnjj3+577RrffH4p/24ADaF82CC4qvvqTcVTy/RPbIWv+IrpwdWDs5vWxTk2zfv1Oyjn6mckjTt9Nin/SC/FZ15rn13tfvs73P8Jl5pMXJdDedRio/ydHQ5yte9z6jsUyzll1HksPEPaQP5eZmu7wFskn1/82Xf+2VKwTH3mgyuzyAPPL59UJxnz3vXtXFceyrn78zkWrF5B9d2IVE2NjhNTc8j6dowJYSp5tzCbMJI/j1DmGEt+JuSADm3zfG+BudoyR5xbCWO1Uq+5UgcUje/sdd7956qu+VcLuc87ThEHN0412e6O44tYruYbk/7VomDc0p4Td17RureheLjOB8ZpPi05urrXmqO1W/fxlupPDl+1TWLvq55+SbAIX5Th3XfG0k4Tt9ud9Fua3RpyAlof2HjNGj71GDJjG8l/75ChpB/ITPdusl3XtEpLsxm29p82bc2xA/9nu1VytDgPqTNrwIv+37XyL2hyCMNrcRfvkbSsB85izQkzDJIgyMnA05DmKRB6iZV03FNiDZdrjTwW9kt2F7XGxBRMDaOV9r0LHddr3H25a5rXe+c2PsR5aT6PaMxVAxc2G0zHOlHf5/QLyW+oe21PqbLGup9AG+MIN48jY8nDr+Jg5MVB8AAfPGuj9D7tDZopPe9u4Xrygz1KY53/vtzXh/x3/G7+7f4110Xaj+fdH3ivjvz4spiql7++rfLO/37/es+iVLOL5w2P3nvk7d8OeK5A1u3Tjz0lHf/OmM/ycD96+qyh/CMevJcIM8LnRHlXj/V+Q0x2Tt4BOwER8IecBRMgKPhGDgGToJJcBo8By6CY+FtcBy8BybDJ+EE+CycCD+Fk+CPcDI8CKfAhvWwAzaG0+BJ8FzYHabC02AanATT4QKYARfDTLgOZsPrYA7cCmfAnTAXvgxnwg/gLPghzIO/wnzYhLwogGFwNoyFVjgYngeHw0KYCYvgQmiDm2Ax3A7nwJ2wxLm+X0+eJeQZQ8nvDvw7XPL7XdnTcQ+MEv+60+A+2Fv864aKf10K/BIuhPvhxfAruEr8oDbBGviw+EHtEj+ob+D38AeIkO/YAptgw4+wObT7n8FDsCv8HcZDC+kYVA/AoTAIzofHwoXwOLgGNoAPwIZwM2w=
*/