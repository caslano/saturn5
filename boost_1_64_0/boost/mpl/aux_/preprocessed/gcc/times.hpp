
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct times_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times
    : times< times< times< times< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct times< N1,N2,N3,N4,na >

    : times< times< times< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct times< N1,N2,N3,na,na >

    : times< times< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct times< N1,N2,na,na,na >
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {
template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  * BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* times.hpp
PeEqznDr53qsOlpxIO83rnrxfiab7XJY+dpllzxkL+HjRvnmi20DGudhlLnSPI5Kea1q5Tu+4V3CVVnkVeyojIbL2NZUxiXGbsD17U73IY2ZM92nzDrFnaROqPKvQN4nXI21TjSN4gb7g3+dPNtLhM4VxEOvOunVVveXcIheOKms9Spe4rRVTRD3mNzRrntMwzrrue3Wmews70OD6+9Deuap7ltrPzHZORn5gHj7R/srD8+8AMbvHktv8/tGBNR7hMdzo+/JzsRKpJddvy0Sxzj0MoZ/OBQLZgzIswH8Vjri8VvJ915htl3lyb7rmtvisJ1TR8bDuIbGpE5PmzYx5ewGxwnGeeh7AWkVL/LMs0eE72+uLMemaX7ybHA8kGWenuOBsss8+sCaCN9yf2Tcm9w6OG7beuIYt8XA878t3rfMCfzfODoov/bIx0ZbsMxPA3uDsDN51pdZ7xcMU1f7NNnApNNq6XSidGqOHCBepqVO7gGoDepktvPRNr52/szQzToPGlfgZT5oYefytr5t6xDhKizzU8MKws7kadm2zM+9Q219y/wX4lV56dDwdxvPvF9S3ua8yiJ921Ud4Wq88lKLCjovVzmvt25PHnW9J9K3PX1JvDovXdwtKYCym8uaHOVr16/j+V+SV/q0omDq9G8Wdq2O8m1H/4gnpldezhYUfF7HujcNaOdbzm+Il+jO2/xIC+7edItFn9nRzrcNfUe4TMv8gr833eJV5soA7k0J0b5t6Sjxyi11+mn3prXRvnY2BhNUWOYR3L3pBws792jv26Yak1+VdX4MXP9pdet6N9jAuZGAxq576LLZQpdwdKmx1CX4++QPAdwne8Ro3JzejzYhTdGhTjoU2esVYJZTg+9rrU3va8VFc31+L5jfzcI7aK+QxtorBDYzyj/WkXcJli/M59N8IN/7XPnGoVyW6dtHKZLFyyrweL9FN/fvUMMuzi9Jfn7T6Xyhzuuc31E1x21Em/yznL9TX2znrN/+Kl/zjvqeqG+ae2ELo3zjVL6SQkrnLFtUAGUz8swuLnHX50eRKofK5V2O79Ezjr/nDFS5XOcD9C1Z5WA8Psl6ltU1L/FHxSkoLMlj/SV8KM5wP7jSGsS5yY72wmL3WGY79XljvDGmb/nq8+zrT38v974Haifdu/HCdH9jYIMfU/xLr8/U+FTj+nsPfJn00I0bN876vGbmr26v/dDfGOrgxxoHOyY62DHI1mOigx9Lbj0m2v8Y8yEOuw3L6XbZoi/Ke9gbvXnToF7vjjl+Y5z9jVV3jqmSf05+uyNeY6rCNTarKWwBT4AtYTPYBTaH/WALOB6eCDNMY/YOIk6fHOR/RxCjq+9T+n8lXHv4N6X3NewB/w77wCMwGX4DZ8Cj0A6/h0thI2NbX9gYrobhcBM8AW6DzeBTsAV8HZ4I98CWcD+MgBno1AbOhm3hQhgJF8MouAG2h5thR7gVdoLVMBY+DTtD95jhPvVjNI94jZH7WPY8ACPhJ7JTXSP5zeRPI55jbGEtNI4MjZ2cDdtBG4yFc2F3mA17w3lwIJwPx8JcOBEugvNhHsyDBbAY2uFVcDG8DhbDm2ApvBMugffDMrgHLoN/gRfCNui2AvaH5fB0eAV8B66C78Or4AG4Gv4VXgPDaL/XwqbwOpgAb4CpcA08D94Ic+BNcCFcC1fCW+BD8Db4R3g7fALeAT+HlfALuB42xY4bYDO4EbaG98BI+DvYAW6Bg+B9cAS8H54Bq+DZ8EE4HT4EZ8GtMAtug/Ph43AFfALeCJ+Cd8Ht8D64Az4Gn4XPwJ1wJ3wBaq9x+e3oY+of5r3Gv9CYw7/AHrAO9oZfwoEaizsbHoYl8Gt4Efw=
*/