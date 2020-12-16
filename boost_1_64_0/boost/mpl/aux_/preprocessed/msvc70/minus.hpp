
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct minus_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct minus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct minus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct minus2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , minus2< N1,N2 >
        , minus<
              minus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct minus2
    : aux::msvc_eti_base< typename apply_wrap2<
          minus_impl<
              typename minus_tag<N1>::type
            , typename minus_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, minus2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct minus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 - n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::minus_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* minus.hpp
Yu8GfqIvr+VLbHofY7Km/iFpP++Al2lt8Rc+tksT6tmr4oRA21CX/UtjvD6Qmr7DFslHZ13j3B7pbTP3c67WtSPy91J33ZPzSnfd5HzbSdyrqiJnvYr80lWvOnRz1bMJPucbfM6/8Tk/44j3XG3jhpqsq1+l1YN/ePJqUaEjRXsU5wXjt0SeH/oyZaLrcnQ1eHXhQmqRo/gH6smUtfNXSdm9XPsR6W5S9JSl8vwVPUMD0OMsm3K+i3KQ0x29Srup1atyu9w79/OvwO5pR512lnvb4fnOv9t0dm8Xu4eI3QOR9thd+5XHbnnpCHxuopRJQ3uv6p0va+2fE73PIFdobY9XLzpTPe1y/0D1Imb5sdedfwulLljkxxGx6xmx60nkSs2uf+rs4vb/tHatkbX6z4pdT0t+NTTr7Kr8qfOrv/jD3yR2bUSWaXZ97bGLvNIKfiDzSpW5rQGW8yYLu+LEB/x3Ea72+BC8SmtjvtHZ5agWP9hZQbzL1nxvfK7YI13tprp/EOda4yLPFm+61PersvLcsrylhfIOK+25hNkh51W8pi0s87YDapu+h/O+/L9UftPI+dWk06EZI2Ee5dqHXbFRzrdIHO79jurkvKikotIhYXZybRtGLix1nddLGNLj3McomUQ+yg2fx7We35If8rvt8r5WKfXdHbaRsO9rz0cl7N8ImyTvfmrYmE6uNeJjviOspGsrYZ15XFZQKOF193tnJ/P2t+6Y535X/ie2v9nibz9d7B4vdi8g1WI3ZVQzPJB3Hh+7lXcYCrvY7bn3YofeD/+QVvIcgNdo9UVnh7fdSwzCDqkThvK+X2wjD3W2lfh8S6DSk4dJlAG7kjZJiyfPk6Qeauf7pNzn2/XfBRn862y7tLQKryetKSc40+r8mNZaB9eM/EDarWhXvBH8HnahjRjm+n//zJnDR9vk2pcneK6l2uQd9WnPtdHO80s95yM9+XgttuXnyVx/97nSLuu+pyRPF/rcf36uzwPxc9+MdBLeQLy1ET55UJzn2ecmTu2PsciD1ZHePDg30pPeFHd6J3mujXWen+I5H+M8fzfCkx/G9Et6+sraBkP61TKi5McZJumvk/QPlPfCAciN6GnEHtKfX1qYV1ZlH55bUJ5XWhrEuyFtgEFXovje7ym6EkRXTGtVV+qPomu16DpP2pPZoitFp2uE6Ar8na7aZP+yRtGVLbqyZE5KrUtXSVmJI9dZkALQo+5LVBBnfGe/WcuvNs54S4tzJ2ZkTMnQ5roEkGf6fYlyiKe02NsmreVc4tDZsCvOuBfTOi0fjTY4t6QKZC8sXxtUfdnxxjTfSrgsE30lZZWFFY7g9Un7wb0kzT7lpsFE/+2Es5vo54MgYN23EUdxUZlH93rO8zlX9wDL7mbUXUu4GhPd1PuKksJlIeW3p/1U0j9JbNhrYsNdhKszsaGy0EG5u6hMm3EVzJ5vvnb0RQpK9XvzZXU39ldu5HcNYkdZkPsBZvqsE+OdxbBX4pHu5nvx2aJEp9lOfAH1wQS2F5/Y5GmvxWZdn0GWdHI6JF8qZA/MdJeN2pNK2jaqh8N//qh5fkTiXiTpz5c8b1Tidq/Niw4gvU777T557vOOs1jp79Sv3ZPnlc89WtfD/B4taOu28fjuZ2l1j9R8jBY/+33lHiVJPta6bKw8HmW3rqd5vjSIzn9n2T0C7ZZrHq3WNlqtPTz+ax6DXcMY7JrBYOd0mq8ltF4L2ZiuXb/3tE8+PzT3mnmRC26/rShqyUyrNZJWa06DXzv5gFNvYnTp+mGdD204+sshM5NueOB6q7WiP94cWfM1kuLrtZWM3cmYXmMr17MkDmrHw7Lf2iNwBHwUjoePwSnwjzA=
*/