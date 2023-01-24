
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
lpnhq/ij7g+vTfE0OkkJIvDd7y+2nNifyWVkWyZm9zJD2UbEyekx6EnNRGUpZEVlMWXf9r4oQG1PeOlaK+734vxiq0aMP5jQ/A8WtSFkWvi+g63BmWYETB/t86BbdgZHVMhfpdVRjkZ7D1/3LuBS5lGZhOtczoqboXTuX7WFzwxzBoxzkgZ5UZzNNyhDAJIKhf6TFvufI2qlZw9276/l9DySLBvNr+3iCY7oeH+R/IoZmXX6kNiT31W33dq45tkrafnoUgNE6y1MunVaW3aALdOsXuZU2eCKD2ejwv1D44t4oRzhZ2MlcqCJ/lT3b7+gbGsKAofAsXQ9LQufNddeXSsDfbidHeBzfWYI1LYUKnzohBJ5WoEJx1iMsO+7g9/dl6LtqgQhbzWgtsi3OvkdOd5vapAsG9Yhy1IvkFJYW9yhLdgW+zdE+4yc0vqRtdhmvNiU+sG1r8zIe11D/YhcX15LnzJiZG7E1KKaMcvS97KHMoR+RScJJi9AL3hV8MJMoJci1DW0EfuEiJ1okVH7eMexvwG3gKIn2PRjLX0iefLcaujmNBigpo6/LFq8Fmlp/aqa/AZM1MR4Ku1NZFZi3KWsbsS7HpdPd0rOt2HiiqzUE114a5kgX3XTEkyzsK8r3nlXnMe9cHyDLtYhuAApbmlDdQQ1t8bl6YKW9opVQvZPNBulp+6owWvV0hEfPJq90MvRUCY6WN58gqse
*/