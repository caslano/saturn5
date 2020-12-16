
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
7+rOs4hN/L/1+f8Cc/a/USw7ZP+/Ovt8yP5/id/qfMj+f+MC53OyzPNl9nlFd+3z1eb5lPq1AqVGDH2ew5z+BWlmnCv62J9t9zsHu5WGXVU2Krt2XG6IU2w+yG7z4ol2nRc42K5pZDulWXbXONitDbIbfYwyMP/BKSYfZDf6+KTt2+wi5/jmGs91lW+w2zDbN7hu/OlnGf70CcMMf7pR9+9UkWn67VKouteMCNTdDFP6695tHcYpt+B4tbkuIlzs0tznUDH1TfXZbKz2+Ybb7Yt9rKCO91Z2xiDnLhoewWer967gvRM4v/WI6NZ7zFIsfonu80c8ipGMMtucEtO1Nn1Uty0Vyx+mOMCRiuXXDGmoG6H85n1H2mBvxhrVq0z1KlWfJR1l12v9i630U93LVJHRqvsIxVYyAn0a+7jKWVHGvUs2Cr8WpjbQ77GPqZRjIG2j+nO/HhXh+6n3ztqovu+nDm06puKuhYldTKW9Yycv+GMn/cee9f0ZB/RY8XbGMxvvtMHk69d97GRBmvMak2fka30KenUciLlE0Htees9K73lDr7qF16uJoPey9F6U3stmzKWF16trgV65R7/j9PvuBdPHIx9NV/lo4uWb6QknyIeXIR/eRPnwsuDNcDK8B+bCJfBk+Kx8gc/DU+GrMA96uaYPdoWnqV6LPPqNBqepXlvI3+WR720z+d56wKvgjvBq+fSvgQPhtfBEeB281dKHtfBGuD82b4YHwlvg4XAhHAlvhWPhbTAd3g5z4CJ4CrwTFsK7jH702b91wvTjNPXjdPnKZshXVgxPli/zdHgmtHTOguVwNqzQnno3wbPh7fAc+DA8F/4CL9CeeBfCjeFFgdiEfhfBJbovzNjEvbovKmEXeB8cCh+Cx8GHYSZ8BObDKlgIl8Bpim3cD5+Aj8AnA3vD6TcPHBZmb7jP1R9fwu3hSrg3/Br2hd/Ag+C3cDD8Hh4J6wK+VP12gWVh1ngNkP2BcLTWXJ0LD4al8BDZSUMyVM/RshMHB8vO67JTI1/qG/Klvgn3UQxyCKyFI+Anxv1Qq/qtQsz7IdTX20O+3t3gEXCcfL658vkWwWFwNhwOL4Yj4CVwpHyto/S9S4PL4THypR4Lv5Yvtkp5uzLwFxUj5cgipBp5t6u3yfVizfGRtoV/tD19o7H2i7prxuhDpI77rMum7OWIDEYykFnIfKQKeRdZg2yzGX5PJA3J28z1b7rFLW5xi1vc4ha3uMUtbvmXvXuBi6LaAzi+IsqqqKioqKj4xveKqJiWlC9SSnylJiUIKCjChqD4yCjJKKmovOU1NcpHaqZYVnavFXat1MzwUan5oDTTriYpmpm37m+W/y6zj8FdNOp+7s6n09edx5kzM2cPs3MeY13/P+OPrf+PiY/mvyDDBGNy4qxu3Q09SloD3Jz2AIGmen/zLkr75l/rrDzHs9u1qd4+W1VvH65Rvx4aZqn7NUdy3fowD2K/TeLN04g3QhWvbeKcrWe/TepIiqU+fEFV6gAxHU39SUNM+7CLX12XGSiR/pH95BLjkkz1PCelfsrIDGCed51BPN+ONF272XEpyTpLf7onOEfR7MhcT1co26bETTPVqyjvYSjiuDdwUsf0UY6TbaXfYRYJSY2jIx5TA+lruJD4EqijS4pNiE6S86eEO8z1TFL330/qmfoQdnKs+aFa5zAxLjopzagrR3299A9WHaP19ZwrddKb0U/8nG19btdKCzWiko4Q9Xe6zOvpXTL23yB55iqfswaZz2WVOokl/24dfndQT53Me2eAZV6QeV66ZV633uZ5XUvn9TDP++AOy7zu5nnPl84zmK418zpa5vUyfR5xu/lz8E3rn22bx0w=
*/