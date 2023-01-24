
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
uIF7PFqkuJ7Rf9C0vqq36ymUPehkKV4oBbdt7DWsuSC0F6Qw5v0yktZk6UCkP3Oii4LZtF+hhMTbrkh+isZh9eGGcIe9NdVRsjZExYRCPug1JvHOSs8f4E8p1pGp4j90bKs7ib83A1PfnLI5xpQ6LDqn50gJYlqFZEJ3mvoxXKj71ib+DO7DPjB2rgysTJW0Y/lJ3vqmIaSlIc6BN2fbannSjiz9TXosiOH5xyG7dE9yrbl9sLdo6SnDDo0/h9oAWjzHxmmv3/v7A2F/f3sx77qk5dqX4ovrm962DBHvvcPEfDrf949/jHOPlSvkWQZG7fkeECVZZ91kiEw4WF2LcA/sCZaN7um+56sSmHkmTD7MAPe/g89w+VLDeJKti/56YfdLHP8+mFVuvRxw3EKSCe75fOU21mQ+fZXCfnPTfpwkcr93mIVW+3kt8jTXSMiK1pkv2dU6iCb4mGt8SbjLf+or7dWjb+XJgfUHudiUyhitIrq0IYh1nX+N04qCoJyo6O92Bbm8qQrXadBuOx43MCCHmbJn8ao4XSgQqjmaYHTyLMdRvq/HPQPeut6BGJsa1HEybA90cFbyzYSlz686D3VPeXoFgXBHhuhyXiY6FyLq2wJftL/O8EBKRNesj+DDM/jVvWMXyyPhfyJqd4lK02MUXwAZJd6JLCRdwSvX/df93q5/oeysotrq0jCMFC9W3KfQQgvFXVPcvUhx
*/