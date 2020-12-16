
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
hr54AkfgBZyAF/FF/AzX4SV8Bz/Hk3gZczEP/4lfYYXyfC+iM17FhvgNDsTrOBK/x7GYj7H4A87HH/ElvIOvYgG+gT/hdryLO7EQj+AveBoZ4DfpCpbF77Ec3sXyWIgVsHwFzhd0wUrYGetiD6yHM7A+xqMrvoINcQM2wjewMb6FTXAHeuBebI9nsAOew474HXbGH7Er/hO7YaWKfL/gQ9gX62M/9EBv/Bv64BwcjG+iH76DQ5T8cChm4TD8B/rjRxiAl3E0/oRjsDo3qoHojGOxIT6CzXEctsEJ2Bsfw2E4ESdgCC7BMFyB4fgCRuBqnIYbMRp3YwwewMfxE4zFqxinlAfjkT5DhznohnOxBSZiO1yA/TAJB+NCDMXF+BI+hTvwaczGJfg1LsVv8RksX4V2Bh/Gv2MrfFZZLz6PSvtEGyLjSbIuaf+r4kRph9lXtE8cN1w/9cJK2A8dcRxWx2B8CKfiwzgXnXAe1sJF6IxyHyRjRXKsGNwHzXSQ/nWshfHYGGdhG5yDHpiArI+ysw5Z3y1ZX3WMl/XtlO+Rd7ERvodtMRO74l4cg+/jNDyEr+IH+Boex4t4Ai/jSbyC2XgdT0k50spYxnY0j/kYQ+io9BPKc8mB5SgHDkJXHIxN0A/b4hD0wWE4FP0xEIfj33AERmAAzsZRmIRjMBUDcQ2Oww04Hg/gBLyAf8MvMAjzMRh/wsn4O4aiM2UNw/oYjo1wKjbHCOyF09AHp+MgnIHBGIlTcCZGYBROx2h8HGNxDsbhcxiPq3AWrsEE3IRz8R18AjPxSTyISXgCF+JnuAg/x2T8Cp/G27gEf8WlWL4s5wFWwmX4o4z54iljI5aR58e9lWNH9tN7ZdhPmInOuBddcT+2w+PYBU9iH8xGXzyFw/AjHI6n8XE8g/MwF1/Bc/gOnsdTeAGv4Wd4G6mTqf/oMrpiHjbBr7AjXsGB+A0G4TWcgtcxBm9gLN7EufitXJd8hwvxNqbg9/g85uNK/EEpH/6Ir+JdPIyF+A/8BT/GX/ET/Cdewt/xHv4Lyyn9nWW5XsKy6IkVcSJWwtlYGedhNUxBR3wOa+J6bIjp2Ah3ojuewiZ4BpvhRWyBV7Al3sRWeAtb4x1sg4XYFn9DDzT1Gyn7WcaBHC3nKdfIXMdJf7u0dxnojO+gK+7AZrgTe+BuNPWz43Dch2NxP8bgQXwaD+FO/AD34oeYhcfwBGbjp3ga/4VnsCJl+Rib4yfogecxGC/iVLyEpn5wXIZf4ja8ouSH3+BhvI4X8SZexlt4Fb9D9pXD9+iK+dgIf8SBWIBD8C6OwJ9R+n9lXEzOeYP+33KW7wv0wIo4DCthEFbGKVgFI7CqrHe1g4xViQdkvU64XNZ7sTzrxS/QBfOwAX6JPvgVDsKrOBK/wXC8jjPwBsbjLXwav8PleBtX4A+YjnfwPSzAvfgTUj6+syxjU9Lmyf1KUweOHTluUqV9X4m18EV0w5ewDa5CL1yNfrhG2vdX8DF8FefgOpyH63ExpuEz+BquxQ34Om7CLbgZ38Y3cDem43Hcgqdxm7T7b+E/8W1U2pcMrITvYDXcgQ1wJzbG3dgJ30MvzMTeuAdH4F4cjQdwPB7EyXgIp+JhlO9nGR+Tuhh8P79ele2GG7EebkJ3TMfuuAX7YgYG4js4B3fgfNyJybgLU/FdXIWZuBb3oFKOLAcZ5xJHyP6rraSTcuyTcuyXchzEJpiFvfAQDscjOAOP4kI8jnvxBO7DU3gSP8JP8Ax+hWfxNn6MP+M5rKI858JGeB574EX0xs9wIH6OQ/Gy1INtKONa0obI9qyBKy3ve3C8lsMW6IgtsRa2Rjdsg03RA4dgOxyOHTAUPXE=
*/