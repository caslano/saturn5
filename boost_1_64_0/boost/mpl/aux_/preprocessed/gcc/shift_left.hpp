
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
oGxkE7APlaTq/e46n4OY98BI0zz7lrJFCySFgHYrHYxdE9mSrSinoAQ9ArDFiDbFKvsdXmXfo3zN6/FPId9yP/n+HPtfKR1e6uqpg11z8LtJh67IVHSotNIhtyBXSgStg8v/fjKx1Jwcem3wY5sj0qu39EpAWhO3xkovVFoU4HyittKrCXoZ0cJUR+9Lj7R4Tz3K1cgy1D7TkXV8YI9I86cH00gCGJ/g8ul765Gc5tTjPC89mmsufJTs0RZJJ0yFlR7GncWhzE+3x81p1vbYJT0Wyx75yCzCVFnqUVpgKyyYmyN7tApAj7booSjuNvMFJTCaXpjJbhnx0lfXjmh8BKMt2NfMWYZPVQbie5QhU3Pu42XLOGQ2J4kzLMpQ/HP6HfrLtgw5ceh0rnyJWfFeax2cYF2/diudSguMojeoj7+6XTrDum7zmvlpY1Y6LC3KLcmx/Sw9bjbrYd6fS3PbY6VHR2Su0cY89MgqKWQTTGN3h2DG/JWoLtqa9uvIyi8sLSjReCCFce2xE+Whd/24m6pG/sePWO9h4H8te+u19f2voW+99n3wa9D7W4t/5YnG9ZL49O5DYtrsG71sn21T3rOvHL9xN3c4xtF0iPms8VXnvnEwL3r9rk1HSpf6H3fDg5nrjT7uUvzsY9e1Lzx03dunTX/bFvz4pq8cfgS94+jdZzh/NIWDLfxBkbAYtoelMBYucX8vR5ROX6Vj/l5+sb4/r4AJsNwUz654LS3iLVP+F8IW8CKz30Px2ljEy1a8HHgynKd4E5BKxeumeCfAUYr3K8XLgK3hBTAazoYdYSbsCrNM6dUovd4W6Q1WekOk/1DoKCdsB0fIHqOUHunrWYoOSq8FTFN6kbJjFOwG28lvEA37wA5wNOwIp8JOcAbsAtNhV/MapconSvlojVJPv6/y6wHbmvy/ZUiV4i9W/FYwT/HPVrwJajeTYCc4GcbDKfB0mApHwKlwFJwGx8HpcDKcAafB82A+TIdqt3o+oatFu82V/gvVXhcp/3wYBwtMdrDP8G+H/krnNJVngOww0GxH6/iefkHF7634fUzxqxQ/1iL+pYq/Uu3lMrXDy+ECwo6a2LjB9WKzCTOK69WvheMzcfpFViE1yGHEvEZrHrIcqUSqENdaqmnIbuJnw43G30iY1jhNQ9YiOxHnGqUIYV1rlGYgg89x+gK2IjGv8z0WGuuHrkZca4QO5vpuWIe0SiIuko5U6Zt5D2TLY/Xra64izeWmNTQPI67v2amkNRlmIKuQzUge1w7CcrjFyAsJ2803WSQVKUMqkZ1IHRLzBt+Ckew3Qt9nXb//C37p3/925x/H4xuA8Rv/OrQ9rD0RrN9Pjt9z/HjtacR9391Pm1v0R/U/+l19/ypD6EfqP559Zjli9vOEjtAROkJH6AgdoSN0hI7QETpCR+gIHWFh/2b/f0FhQY7x4/84/Pb/bei3f+i3f+gIHaEjdISO0BE6QkfoCB2hI3SEjqCPX/T3Pwt5zV3k/P/x8v2vQVPXGMoKjatfCE+C8+BCY1z9BMcYyimp41KmT2fLvEVslpRjZ2S9fZljDGVEAGMoF5BOMQOMojWG8goiGQnY5pUWzNVeShEa622MynZdb62xu/PineMrW2vcbgn/lqsxoQMnop/SNM6X6Jy0PPev0k/7q5GTjPBIXjz/O8e3fHk5JTlhAYzJdpXP0K+4xLQOJ8L4T7f+bSKkP/oVOPJjzLLXWNod0i9N+qUiiwlT5Uc/xoEU/Rwd26OT3WRj2dRz/fsmWrNDOj2BFJNO3CQfndx7gTQ/pi5N29QQl/LnFBX5tA+f+jbrUiNdzPtOlBi6TPbWZV5uQXbg43tddmlrskt2Vgk=
*/