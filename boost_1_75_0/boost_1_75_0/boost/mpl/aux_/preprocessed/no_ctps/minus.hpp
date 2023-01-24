
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
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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
{
    typedef typename T::tag type;
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

    : if_<

          is_na<N3>
        , minus2< N1,N2 >
        , minus<
              minus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

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
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, minus2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {
template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  - BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* minus.hpp
Zz6LXu1qizzzo13P/eHqTn8rTqVkneO52/RJN0E8rVrrOYABiRhKQfYjHkM4qrZo6kguq78suzVdKaMccF0ByA9fdHovyP8AaPCcu+5yi1siHw3HRa8ZkDc/rvixjCOf6K7swpCGJX1tvIvI98PApBqtMo3nOTxk1NPrV5zPTOS/Vqr8+deCQJnq1vrq1eXdKvdRNO2VS6MaiNnMNoTvPc2Lvw1/eb6QUMTG+4tW/D8Pf/H88Z+JqWBrbunkZvkvu8pdY9Dn+cAujIHhk0kw6nXrC/qeeXvGYItXwY349SY9QREOWG6/pfx+1DQsa96ivsB6ZOV0TNwRxaBJahR04BMdLJbdEeVUMmRWPGn7aAspdVwNzymV1WemVVwRqFZ0U2v37EDs11ey1RPqzTEzizJf5wHPVjOA+8AxcW5kzhppN/g+ZaOt48qPh9ERROjLrP/5mtJDoeDrHAb2w7MSX9a4pjUw5dm4JA+dd2xF0Y5a/nLXzQjzA5YWygE6W7Bmzx96wnqkotYz7FRaGj8hamc4AEJfCT5lu1+pv518H6u4hm2lMFrG070PBoqoGTIeGSeMdyot75OKz/lD//xnSEfWRi0MWW5UQ6RRvm92vlKjDP+iqkrE/GrvAueJ/wef7WRG7BiqSSfT6FpwuBeGX6aIPnrDwlJGRU9e7csuJavRbhodecFnYaFaH2H/NITbgXHVc3UP6Ap+vugy
*/