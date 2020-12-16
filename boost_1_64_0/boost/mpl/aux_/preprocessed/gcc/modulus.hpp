
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
o5Xy6XQ2bPy/6NT4tEJ0WqT+c5ExnJeq10m3tC9t0VGHRuWzNJO230jaPoznvBqdLs24HZ/WLvnrmvrbmg1hXonVY0ymzJGRGH9yzGj+zulm+vk749FRudbIfkfoX3/GfIi9+jVI5DqYJnZskPH3F0o76YRMVOrsVmM7GEtM4OfCzPQcpTs/JSNnQY7NnzkAYperP74IcWXnMTZmoNwUMsRHqc77ibFtGZlZck/xyU9N271zq/d6DlPdU1QZa8d2GswjmEz64HWG9jGWNDPf7rX0+X77y3nfHcA+yaXNoTdIYvJ6+C63hd62qaSNNbRNhtVgWEN+p5y2xfho22mxbb7YlopMI63Z2DYJ403rbcA90SB+t2ZM94qWHmMO5Te0qk5baPaZVr/GTBv/fmr90rqV9JWKLf0QM+lq6rRlUeaSs7BjOprJQWNHrdjRU+6tF8EZStu5TW+Hdi6Xb7FVL1jv4/3VnrG7PfE/iaerj7sfpnoWLbJlDU2RE7XPcdq6391aH+deKWfF+vrKmaJMKPThuaXhZTujW1PA+FnU3EZ/nSehL+p2fRlk7BtXecPbS7+6r3H33GQZ936/tKF74UzSxmntSi/MTLNlutYWqz+2stJ+sjeQh8Tm9ebjvGDHWgOseOWKZa8Z9yjxjz3jxIeo4+BLzGWlXJPlvStXxrjfigHhcDlMRrf5Dk25FF8T2jpJcfc1ObZs90+mXKuxULt5j8W+80739RIm5VXaeZo1v78MOpT6wX7HcwmkfmS/iANA1rDQ/+aGSZzx2ZRDjKaxF9rzOOyMR52Cu0VPtfOYpK1iX7l/2huX6HLGFJ9LnrY8bbzmM+LDHtJm7bFXFR/eZfchP7fn5rfSMefNZtBWtfaUB+ufM3qT1zqXPe7fR9+ewZq2e+Wu+u9xantCVGNJHcq08ejN7fTPi33JL3ijy0a5tn25B9dvT1tn+wlyt6dQ2Zf2JO/7UveIOlb4UBlXf6dcJyvhPPRVYK+sp+ZagCrzGm6qOY7vEzF+XBfNfk9empjc2rjhHd33W4kbjq7MDOJye4+lHyLt2zMG/TF3HH3NGNYRMtb9fLnPtYJXKeXENimnshwSC33Zy+surMm3dTzuuFt37bueZaScRs/42jjhqt8U7bcb7doAI1A6lPKM4fyp6FXHlVf7lfLbpa/4YKf4IESu52BkfjTcZPfBgjxapi9jdp11mEralCS5rxGPPtyeD99AorXrp0SE6ucsV9PYYjdp1lpjcuC4sQ7P5xfl5tZvh7odrwzVrwF1Txi/Y0Y6/FxLbXOYfm2x0A76MdH3cl6qkT7XgGjfdc71GA89pJ1mPLR2TUQDW77Ev6XGthRZs/23o616ToKtUKM/NEyv/z6OlRvp93NdOXxvtC6V5touCdO3rwXKO/omL2v5+dnGpM65QerLmYOeKm96/PT141HasvYTX6ttyAjXl3UhNtRsMljDz89yOuvzmEE5c9FBZeh1+FnG7R5lLI6SMqp+580R+ms5H/1Rbv0zzSmXx/s7x+DiaP2aiBURen8WcF6cVpfblT7oU5cl8gJ9Wazkb9blX5Tnz3pti6Usal0bL9DXWxHnWbS6HFXmhy7xm+qdWF9noR31uq8h3TpP3crl78d9cHF0/evSbTDQrax5U7HZcJ1HpfQ+67+5vVb/wfb6a7J5J30dvx7GfWGz8fwYf+t6n8HvT1knfZnf4LwaLzr99fu+sPrXd6ztZLzuYvCWc7vuYnGk8bqLsVt+vXUXayON1100b/nl1l3sJbqzL9Q/t33DMYtDN09t9Zc5RPSdvFD7zHaNPQ/GDV6ovS8eFp1m0TlN+l3WiU6r+3tFem5mWn6Rxf9vFWo=
*/