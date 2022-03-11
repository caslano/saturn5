
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