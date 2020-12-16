
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/unpack_args.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< int size, typename F, typename Args >
struct unpack_args_impl;

template< typename F, typename Args >
struct unpack_args_impl< 0,F,Args >
    : apply0<
          F
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 1,F,Args >
    : apply1<
          F
        , typename at_c< Args,0 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 2,F,Args >
    : apply2<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 3,F,Args >
    : apply3<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 4,F,Args >
    : apply4<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 5,F,Args >
    : apply5<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        , typename at_c< Args,4 >::type
        >
{
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply
    {
        typedef typename aux::unpack_args_impl<
              size<Args>::value
            , F
            , Args
            >::type type;

    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
34DC+GKS+32BMyMPVWxKy5dilqfSclbSJ2n5coKHaTk76ZG0fCXNkRaMMYrHfrKiNH5N6bVqkwNF+r8uTIZzwb4hLBpHOkeYt2feuaIXb0nynieaN6fyfNGDT0wYZxSON2S7ZYLkcy9DZrota4IxqAvEE04eIf5tj3M74BbA97hQ8+gnIsYhA0/WrCGXMA4Z8rXyLvlewPR1FwVMfw+/WFiRlr7xLv/uu0R0N+f8+6LFT2bc69LAo+91mWKtWqcYJ+VxyUAvst/m+w+FhU9MHpsUjp4o9vEVPerDXuGzNZRosB+HrCVn3FwpzH8yg/9E80Qd+KnmPerAVdqTqANXax7UgWsCpq+71mdc/cGuC5iOz/U+002D+A0hl2ZB83x+1pNXqhPm81Zmcsm8KRtNE6gdc7lRrsFPWM6/m1jXz9+JRjaFwxIwxske/gpPywywZ7DWi11D6XXFabxZs0T//hbNVf/+l1pX/ftbPb0+PgX/r7Su+v2/1jrdmfPuN1qn5B42024VpyE21nj5Rm923ovituiaOJupswD/7f+f37WdO7Sfdm2kjCR2p2Z2c3DU/bt8lleqHXtaq3vG/jb0tJr8gAG/2+PFoV6ILOJ2j+ZBf/Nen3VtmdyndXUe8P1ap6eSpPMBj5Fe7H1H7MEU604Q+12CmRwk9lCCmbtSPXjYY/n/VQ9+71/zP+vBI/+fvwie4vRo6HdrQLN6dA9c89j/f43bL+QP0TWdlqs4qBd/1J5cVwyMvwa8izPQ/gQdL7FGva/4ssDsCZ8Z3UA8E59kxr90u42pTgP1NOdr/0x8cMh8ghlb6QYsmT0VMfkm9JeIyT5ZTxMbXjA0XKKnGo3F+hotWtXnLj8rnGftIk//qvTadL3SKEbQslqXDm5Gu/ibeOwnVD7XM9CLAGz7/UeCYd4ThflP4RjZwDpe0f0xWNEprwcXsv6fUC/3k/5coJcGOM4bbOzro/3Dg278NWTlfrrm+Vp3x31w/m2YZG7Aka7fKOnh9fQbh2yaZk03c5TPJj6nvHSTxJHXm4pH9ydNHjHfLMkpr4hvnuYmzzgOW6Q58o7vsWXSQ3lIv3m2Eq5PoZKkIK+29n3Y9gPrepPMz+ttkp6c2LbCorU82/kMddJFj67fPvK0c9vHfKFmwbyRHQLWqGMdb6ib55i7I8LdMfBMVemW9Lv7xT6jIQXqlK3OJGPh3Snp7Y57Vtxz58Crz6baJWTZWvde3zVgMyZw6hjT+5fjsdt6Pa4sqc68ZP3evIM2+NL1+rid7Z7wELbrfpNcouTGi3v58LzfI+Rmf0q799orApbn5rE45bYgknJAfu4Z+jvVTqNG/7j47BV46Lmtfk+/Ujh/OEB6XyU61wW8vJBc953q1YEv9Xv4NaFHOvZ0r9cGPEy4/Y3/OvG535mvF03KtWid9DbhPH+D8rSzyeIgvrZ5+FHc9k6ycr+tz29M8dIAXbtPguGhR3xWkpuwwftS3Ky5MXGjtM3uySWMfXt5SgO83rcH53hivW9PD92Hymj/Xh68rKxvbk9fqxhs6WTwHdDLhweybRNv6uGLGjHCPXB9frZSmg9K+SQt5Dk46UE64HlzyoM02OfwIQlPFH+Ed2gvL9m4zfZ7nunWGvRd5yk9z6QPNBDq6AMNerr0gUqBrvtA80OGPtCCQNd9mIUei/swQx6P+jAU/mHaI/0HCn9Rkkn/ZnGSS/9mSZJL/2Y44nH/ZmnSQ/nDa4GT3OUTrwVOe2x1oro0mvaE1YnaQnk9XtjovmNpn+2OU1jLIk+6f7Zc+4L+1RGaBf2rFZr16F+t1J6gD3WkZqoPdZTW4z4U5enR2vM/+knHxN64n4TfsMcmvD0=
*/