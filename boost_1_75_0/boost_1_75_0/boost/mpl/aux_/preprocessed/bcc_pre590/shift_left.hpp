
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_left.hpp" header
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
852u9VKZuL9tXMyZvWeiDH2CZ5QE+Gxi+HLaWN/iGWholNQrIh5unqu9GO1sLAtAc3cFSZBHDcjYdUeRblBFpxO1EbBjrMPUgH7vMqmv5cKts016nq6D1CW3owrjaS/LCtsjrUrW5K8EQXrY9Jv67kedhNeOG5jTnxl8odedtWk45kRWsgD7gVYtTsOh5JfvonbzeEZVphETG3LBhr4pWXlucyIUica4gUt29MJ9uveCmr3xA34nFeXiJi2HUHRYSnaBe5CdKQM93q3AE+4k2+02nda1mH0vSu4x0SJ/ORuIRe2RGTdyH94h7T/R++u8IvzoCL/Z0nfDcKijqa9jTWvf22BBGDeeYb+odVptEfUklbMILbBVaM9JtHpb8JNdTpMrKez687espM9lOo2b7onU/JuX90h2OXIDE/bSOuXz5/CMrdJnXml/ujFGyx35YM7qLrShIk8umkg5MdNs0pjKnsHBNqzzcuBHWRufXKZNejv+uYniPLUe0dMvreOYSU2Cqd5Br3dYXBhc6FxAus6JlLuVD2N8vofk62l4puoHx6c6NKmUkrZNHwhdKPoGdeb9hlN8HgOKVS4bLzXG9Tqe7FQpDHM8LUEzJbb1OLkLeZ0K1x+xWx3745IeIlfFmvc4RwbKeY5lUth/h2A0L+59xlYkmnekL21VOdFc1i+4+VQcyE3hW5Vfzbp/IAT6nm75UpLbk9DL/i5u
*/