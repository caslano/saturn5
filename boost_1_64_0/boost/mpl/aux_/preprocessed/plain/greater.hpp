
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
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
IszSlBBHmEiwEVYQir4Itk37X17+pN//Gcrw/H//V8b/v56T+rz6yrMa508fzPCvjIDo4Hu6+veHunMf2MDr73nWFHtujt3ZNqCPH/P/F90T5j3/v8REZuz+PP9xPVuI/h+Y/9/k3tz0WUSqem+++42q3z+14OfPbzvz5ap5dT651PQZgrRRlzqXfVFG0F5Dh8t3kyuwOSZgZxyFcZiIA3EsFuGqU2GW3QTPNctzvQqVa5L+emSRa5DrmnOY0Ml9ffG+ljSV68Qa72sD1wXP+V977l+IRXJ+157bbYTSU8Hza3AJLsEluASX4BJcgktwCS7B5c9Z/qT7f5pFXpj7/27KWOFplbjHVu/KHdfarK42l56/p3v/fW5mTo/u8nxgl9J/QH1+oGupydJY/h6n/n3CiNE9ustfnc8O+kVZ3G1YFlfyHSu9O2nHL9W0YVGj8O95gavdx1GTeBM18UqB/Z6zxjU3xjRp1z9ffrOZg7E9ed0Zd2qWNSWPxhvZ2dYchz2AtjdG7YVkbheveShOVtbN5SXtformq+lTquRUHtY4rAGkXVG7n2PzPW0StXmZWEV+n5N67kp4RMnLAldeqGWe+eReW3EdG9WDtt73SVrRklZzSavMJ63A5lLTp9dF0ouXimsl6UVL+9ySJZ70aA3rdzpna5erLWdRiHGd2jzlVKd6UT8Wfhy7FdVrdFXj9GJ06cnH5bzTK5T0mkh6jQjbeK9lqSc9uzRi9eezebb6tRFSdfs1Udr8r5fPz2ppNxm90J2+8rzynNr5mc/dguxXaeqn76egb/vn9Rm7VzLxGc80G+B7uFE57jX5lRaUap75zc+veWeUuYuaF6if65QZKeRCyRev/esm1zw9Fbe3ZCuj8qmvFavlkcjltSPy2vT8dHawM65CXqvCthkS9yZ5T2am97w00zX9Ikpd75F4S1hPjlLjde+HZ6V9m9q0TbbbL6/Z5T1F0v9I2wbzhG5Ord2yrk7DJu/ZKXMFOuY41/fKul3WH5FtyI+6flTWmbRN5uiRuQYljcPyd3efIl7b58qHvOjqo5PE8buCnVKFnfTrDewrydMWVxwyJ6H2GIqQx6Ph8pmrLp+5GM9nzpGrTOB2AT9v/STtFZJ2gqQ9ktBLucbf4kybc6hzCovktFzGN0pmfrwK81BL8tCMOkwxPJ960o+Udvur5fN+P6E36Rc60+dKmZySZctIUU451rzM1EDay5pes3XnnOWSh+FSB5dLHmy3uvMw1595Yv1Nt7/r3F7Dd2ynfqRb4kw3K0Mzj4hU/6ARY/yfS0Tt55PhyUMf4k6X81mE7A/2p9exuEXytFj2R4HURZkzT/bUlJzktNn5uQ4/2rz6Ux/aflSzCdq89JG2/tskL5tdx8ZtnryQlYC+SwWaF9cxckbayu+qKvNpYhx5KVjuzItD+VZpu1bNR5xZPuQc3vpu7Tnc/DqlOee499kvNIjgtsPZv0Pek56Xm+0qz2HJf56s75XzTh4F1J7rcmT9uKzr52Gd7T4nS3x5+vOv9xyHVlkv85zr1fUS+XuqpPc7i7LtHHn/EVf+yKB2jlOK6HUtybI6+3LGUTHlNZ3f8xPulDZ3cj7Ot6jtpe1Mh+4+x5bzWvw5tH82bOds3o434HG0LlQ750DnwAn0t1Hj9tKBt382+c3XdJy0+9XfWAeWl0fOtF70zqGPj3zdeqf1l8DbP1+o35Tdc8As9YwdXVTJe86QRPkNdyyGItF55oA5y3ZXyHYJst0olLkc5L5VvZ9lO++5HOzSTiofO+Ic7IZzsRdei2NxPo7DhTgFr8OpWIAL8UZchItwKS7GR/Fm3I1LcA8uw3fwFjyBt+I3uFzGnr8=
*/