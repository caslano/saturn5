
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
RzxE3xGP0WeE6NUWtNnekv3m9ICWTysQcyNjU74F2IY279uKXgHbifxge5Ef7MByOwscBp4t/RzsRB+SXQLqk6RrQH2TnUub7N1oC/88kVPaC7gJTAafBbvTNntvEG3S2JxHWzM25z8C+0u/Bs+X/ow6GSDjHTgQbA8OpQ32YWA6OFzKERwBTgRHghy/eG7R6O6I8asl2+3pbK+t/Dq/PcOv/e1M2uhuDXL84hlC6FaP8asT4zvHr/OMzrQp3sWv7SUZbAF2Z/w9/Dqv6glOB3v51ddQb/AykZ82wPv5tR/3p8+18/26Hh1AubYjDBlFX9CUq5FZd+nnSMp1FPN5NPNZx6/jCcrYjNv1/DqO1Ge/bAiOstSn9mhpv+AE+tYuoW/tOfStvULaMfttE/bbpuAGab9+1e+Jfm2fJ4IvSTtmvz7Jr/qouW27nef7ML/ymA+9zPzsoL553W/0sfF51ssyPs+MHv4zmC1lAt4seo7xr7N4xk50I+O3bYbj79TD93Ae8gB9x2Lub/TYQz7dP0CbNv35Ya5zHgELZDzkvHgzeJ2MhyDSND6jNlrqM+pBqR+flsOTPh33nvJpv33ap/snW20fyDw/hzmwxzg1nuu0dK7TMiyVdwLXoxO5rs+21FfjJEvrcbKlckJ2sz7Ltez0yqpIr4DpTWF6U5leEdMrZnrTmV4J07uE6c1gemjrnL/zLJtZQ0fO3/dRD38m/V/GERnH6St3Gn3lzqCv3KuMr1yt76+oJ78O6Lj3jegf+tDlfhnPoZnzaRH7Zd25X9aD+2W9wCbSP+nrrQ999vcL6vy0P5gk7TSo/WdgUMfnQUEdlwfTN9HQoM5bh3N/bQR9r40Kmn0nY0t+iaW25O+2zJ6omceODqqevyio89cx4NvgxbQ9Pxb8AkzjPtl4MtHHc20iE8dvqacGHOf89JUVpK+sEH0sJdBXVm36sDuSNvLrBo1eML5/x0g89L3UMKjj2TH0vdQ4qPV9HPN5PDgbbEofW79nPk8AV4ic9IHXjL7nmgeNHjE+Mv5gGR8ZZrxrCT4Dng4+D7YNqq/J9kHddzuL+40dg7pv0Ak8RcaroI57XemLqxt9cZ1n+9TnGTvsObI9OH3CZrM9TKYvqjzun+YHtd0X0CfVFPram8ryKqTvjiL6FigO6vx4Gn15TA9qOy4Br5R+EtT52gz6GLjUyMcxjGfYsjz24zKpt7K4fs+mD/1J4HkiN9hf+rvsg1jq4z1V8sF5Yz71TZLMoZnOy2wv0h46sL1czv4/i/1/Lvf95lnaD66wdJ22gPYhF1paHou4v3Yl9QHK1fRbtAHjU26ppflfBi4246369LnGUr14LfdXV3B/9TpL56/Xg/tM/ek850YwAFlvsnQdcIulPmZutdT34G0g+gHGFvXtfwc40Wfm4cbXD8rc7AOh7xkfU+vAq31mzDe+1+6z1Kf//eBD4AZwG/gA+CK40XL47BhPnxgmP24fFvc47mvD+xpWc9+Q8dF9cZzguG+cnW6V95Xa6VZ53+oY79sa431lVZTLnY77rHTGV+V9CDHel+S4rzzsvhuc5cf76lZzX2mM8a2O8b6tjvvWhd033LHvUJYefb98KvdzCn2q14uc+y8Z9B3lMX/9gvrjb6Ck/yXYlD7yW4AH6Tv/H/SZ+QP3eX4Eh9IX9Wj6ouYhGDMeBPz6fCXo13E/xPntYX57nr6RcnWmLM55+ju1VK73auk4/FewlbG9oPOB92up3v2glmNfJpO+MT3K5zmWD/qs8bH1vKN82vB3D3mUz0CWzxCfyjGU6/JhLI/hPp0/j6CeHelTvT/Kp+P7BT4d91K4T3WhT+fLozk/xN60ma+M8ek=
*/