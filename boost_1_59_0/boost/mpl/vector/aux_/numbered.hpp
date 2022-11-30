
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
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
*/