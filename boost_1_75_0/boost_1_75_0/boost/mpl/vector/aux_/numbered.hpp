
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if defined(BOOST_PP_IS_ITERATING)

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/enum_shifted_params.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i_ BOOST_PP_FRAME_ITERATION(1)

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   define AUX778076_VECTOR_TAIL(vector, i_, T) \
    BOOST_PP_CAT(vector,i_)< \
          BOOST_PP_ENUM_PARAMS(i_, T) \
        > \
    /**/

#if i_ > 0
template<
      BOOST_PP_ENUM_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(vector,i_)
    : v_item<
          BOOST_PP_CAT(T,BOOST_PP_DEC(i_))
        , AUX778076_VECTOR_TAIL(vector,BOOST_PP_DEC(i_),T)
        >
{
    typedef BOOST_PP_CAT(vector,i_) type;
};
#endif

#   undef AUX778076_VECTOR_TAIL

#else // "brute force" implementation

#   if i_ > 0

template<
      BOOST_PP_ENUM_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(vector,i_)
{
    typedef aux::vector_tag<i_> tag;
    typedef BOOST_PP_CAT(vector,i_) type;

#   define AUX778076_VECTOR_ITEM(unused, i_, unused2) \
    typedef BOOST_PP_CAT(T,i_) BOOST_PP_CAT(item,i_); \
    /**/

    BOOST_PP_REPEAT(i_, AUX778076_VECTOR_ITEM, unused)
#   undef AUX778076_VECTOR_ITEM
    typedef void_ BOOST_PP_CAT(item,i_);
    typedef BOOST_PP_CAT(T,BOOST_PP_DEC(i_)) back;

    // Borland forces us to use 'type' here (instead of the class name)
    typedef v_iter<type,0> begin;
    typedef v_iter<type,i_> end;
};

template<>
struct push_front_impl< aux::vector_tag<BOOST_PP_DEC(i_)> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef BOOST_PP_CAT(vector,i_)<
              T
              BOOST_PP_COMMA_IF(BOOST_PP_DEC(i_))
              BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(i_), typename Vector::item)
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef BOOST_PP_CAT(vector,BOOST_PP_DEC(i_))<
              BOOST_PP_ENUM_SHIFTED_PARAMS(i_, typename Vector::item)
            > type;
    };
};


template<>
struct push_back_impl< aux::vector_tag<BOOST_PP_DEC(i_)> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef BOOST_PP_CAT(vector,i_)<
              BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(i_), typename Vector::item)
              BOOST_PP_COMMA_IF(BOOST_PP_DEC(i_))
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef BOOST_PP_CAT(vector,BOOST_PP_DEC(i_))<
              BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(i_), typename Vector::item)
            > type;
    };
};

#   endif // i_ > 0

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)

template< typename V >
struct v_at<V,i_>
{
    typedef typename V::BOOST_PP_CAT(item,i_) type;
};

#   else

namespace aux {
template<> struct v_at_impl<i_>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::BOOST_PP_CAT(item,i_) type;
    };
};
}

template<>
struct at_impl< aux::vector_tag<i_> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

#if i_ > 0
template<>
struct front_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};
#endif

template<>
struct size_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
        : long_<i_>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<i_> >
    : size_impl< aux::vector_tag<i_> >
{
};

template<>
struct clear_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* numbered.hpp
e835MhB2/kVUJITfyj9EsDeeOah79WzsOxdfhhImb6dYE3VssCQkHCMJMiqEdUngSbH/LHpGHWkhWdHqrJylpAORJ5wPxkFz4dZANmuMY4xRYppbrVwGOXW0LIA0hVhLLqyoMGZc4bl0/27Txxrip4f/0GFeozeRczfpPsu9HcWaMNkFpPObEUxK8wmthNOJfneUOUd19vTR5mSn77feK8QJfe0P80UKWWzqzYCfbICh01ZnpNa2EfV7vhaGkDI8o8XIGe73iVAO2RM1bRSFxe9Qq6Hx1LMGusFL1Dm6WXORam9QHaI7SGnIpwn6F+YhtKb3veWKk1PraH9X6Swdr2jXWAy91X4vTFtP0VPvDJOq2kwZtvWyhHIdb/7WxQgI3oUzV/pi1Qp8DNUYfhuEEH5Wndi4KYMt3k+SAZFjn0NNNZW2N61/pYaT/t6IxVVLr8chnsIyJUx8jxjuCJNhTeVOPFAWJP4uY2yc27kRulWDcCe7bY50MEQyQl1e8c+S1NhY31jf1oZknK5cvfQilkuduLm2QR3LXLHiHwAMLPPTiaPv00w81anyRC2gfm+rO5s4yrHvFQtfgavcANTnR1Kwk4ch6DY2rDha/gDTGPjwR+p6OnMH4jw7iLg5zJ5uhVppuYnh+m8cMUFc8CwkJvfTgj9bZAy6Sg1tZPOSCCE5Uf6gtkSTeT9g3hVi0QyK42KAJmHm1eoWTE+d
*/