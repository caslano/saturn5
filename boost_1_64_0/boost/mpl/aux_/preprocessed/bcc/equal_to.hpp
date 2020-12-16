
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "equal_to.hpp" header
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
nHFJbioRtxvJ/XBfhB/SHTmaNT56gemls/Mr9XI+r69UnwHqhZudp/hlrDpddyhdyrMqr37YUZVWH8b/rKP+SJxO/wTxfJ2kP6NI0Ddg7S1oACvPVUg/pTUa91zchUi/urzAcxH019PBIV6AMv3EC2X8q+1UZ1MKcOPG4gFdyNK56l9/5qK8d5utEFHN949NGhkTzZ7RSLPDi0QZzRCQW8W7JDqIij/XTr+Va3pq1m/l2ZbmKSiTTF5udA7rKvXZr+Pw7KaoW/fVdN4l5+GZ1auO8KpEU65+q+9dzrQ1VfMuTJLJu9K18tQa81eF6ZQXi0LnwlaT/dJz+Bp6pisNz137yXmZoUn7BMiVeXfgufIVnyr32zTuZ0DOqPCyj15P7kpf8NFnbPHRl+CZhaX0cJH8r1lTN93UvFcTeSnRrJC0svgYXnKJgE+1HEdrxaQkRiRowqyd7hEa13wVve2j1/IqgUXas4ejn1CfKXud6ug8KMOlNMg1wSjeO6jfy9G7vFq2D/SWUJMLpX6UHFTnwYvwVIvfe54UVNjpjbvySjt9g0E6/RKFLS09307fuZ2c15InJP1aC8ows+xJGRP9CeuctSEX4K6MxUc8XyeY7ucEE0Phz425Bw1keXmybnonz31p3pUSfqG7T2dzyTJtufJrMO6V92qnqK1U8rwpT8p8+irbLuIKuDevFfQOb+IwN9p6ovINfcEX9SSfER2Iu2Qt00nwKN2hzC/xnqC+WpiTNs7jKemc5UrEE8cwaq1cnxm4d+MuOly9jbsAd4dGgEO8OCdtXLKT+nSHPzfmFvHuYba0vGOd67NGnKZ1Z7qq95hj4qPl+seDsg2DAtCcqagAtbM/Wlt3r7GK1SoMkY7fEGbMEHriUXUaB131FL+vPy21C8sUGHObeKrzx8FTnm/txdw+w9pCyW9Vnb7lK9YDf06GP2U/zQt+7lWO9C6YzoVBHtmCMmnO8R/snQl8FNUZwFdApah1gQRICDCQBBJIyAkJIQnZJJtkybGb3SQkENlsspuj5jKbYLBobasVFRVbtLZiSxWv1ioeqPXEG2+sVmlrFY9arVq11hu1/7fzJjszSbh6/H79lejjzXzve9/77nn75s1Mh1/qT90sZKutPwC9rclo7OV9cmLP8EHtAZb9xLaXA36fvK5fN7eMDqUfS3NaP/M90YX64xxfcwu3s8P3SedIw1jHR+1Tv66vmPOOgrPlcREvxuvN1seNMdR4qXGO//5mxYA/7jJlGI1pwG7OD/922GKikUS7Hr+A84gMC7k+DKsA9rE/TON1Ew2/pKH9DXKObxrorgeW5w3LkrDZSGMz7eP01zPOL54Vnu90SlnD7Qd/PTiQP4fLpi6XuX3dbdr35xfKJTRXX6C1Y1APk3imvs4+DQqe3Kqi7xPQMILGfkXtPR3yJSASs8THe8REYuvoNeLIfiYsDVYo3hQdIh7vX6j9bwmdD8YDl/tBEWVVvP8EcZ4i32nIvlGHa02mJXy8WDvWtmnbShxK/IC2DzaB7bct/FhI1M4r2eYhIfr2FCNc4roqPInyuGagm51VnHFcp4MXlrqUyuKaRH2f5NAXv1kNqnNVaXgaex6VP4mfo0j9T5DnEw4oH6hbBOXjEqPnfG57su01gfX6JLFQnyTv4SQquXJlax99fT19yflGN9IuIPvs15qcb3CO5HyRKM0Xm5H7hnc/9rEri8zc3SOs05kgIIb7UpoTCAfQzpOFaiVMO04SP5LkO9KTmGmLw6D6VrEQUGp/ZH7k3VbJemhR8ER1BxcLdwmhxkQlX2ryAN+PJS6+rA0fmD7op7toq2uG2kawZo3EfsYeHIa3Uua8P06xjJ6j8qI=
*/