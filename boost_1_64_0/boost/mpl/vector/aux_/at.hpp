
#ifndef BOOST_MPL_VECTOR_AUX_AT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_AT_HPP_INCLUDED

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

#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template< typename Vector, long n_ >
struct v_at_impl
{
    typedef long_< (Vector::lower_bound_::value + n_) > index_;
    typedef __typeof__( Vector::item_(index_()) ) type;
};


template< typename Vector, long n_ >
struct v_at
    : aux::wrapped_type< typename v_at_impl<Vector,n_>::type >
{
};

template<>
struct at_impl< aux::vector_tag >
{
    template< typename Vector, typename N > struct apply
        : v_at<
              Vector
            , BOOST_MPL_AUX_VALUE_WKND(N)::value
            >
    {
    };
};

#else

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)

template< typename Vector, BOOST_MPL_AUX_NTTP_DECL(long, n_) > struct v_at;

template< BOOST_MPL_AUX_NTTP_DECL(long, n_) >
struct at_impl< aux::vector_tag<n_> >
{
    template< typename Vector, typename N > struct apply
#if !defined(__BORLANDC__)
        : v_at<
              Vector
            , BOOST_MPL_AUX_VALUE_WKND(N)::value
            >
    {
#else
    {
        typedef typename v_at<
              Vector
            , BOOST_MPL_AUX_VALUE_WKND(N)::value
            >::type type;
#endif
    };
};

#   else

namespace aux {

template< BOOST_MPL_AUX_NTTP_DECL(long, n_) > struct v_at_impl
{
    template< typename V > struct result_;
};

// to work around ETI, etc.
template<> struct v_at_impl<-1>
{
    template< typename V > struct result_
    {
        typedef void_ type;
    };
};

} // namespace aux

template< typename T, BOOST_MPL_AUX_NTTP_DECL(long, n_) >
struct v_at
    : aux::v_at_impl<n_>::template result_<T>
{
};

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_AT_HPP_INCLUDED

/* at.hpp
dUPY+zK6LuOK18f8wcJoPPZH7zvziWcPOI573PdahY1THrR9Pm4/5frK/VONB22fd9tex7Wbb7X9O+rzfod3O8/M95BODz4/aT/wjP3u3cYTBc4bl9n+RO/XY9H3htjPR99vcbflbt5kl/nWBO+f2Z+N5lHMZ33I8aP5kVPGO4ummz9ZZN4x2XbZ5zOS7deO+/0+l/vd72OWg/m7w35u2Of7CD5iP+D68hV3GZ/+zX7gbd4vX3P+xvzoc5+0nalxu08Hn0F/b7x60XY/Yl77ReZfk+3Xs1wv+2LjrDVu55D90V99j4N5z+WJrsuMxrPHjV9+ZntlPHhlwvbKdYe7HnD+wjzXvltcD/OQ95fzD7Hu57jzMxeT7Mdt12If93i/6Xyk7e9c84Zdj5qniM7bBfnG4LPM/HjI+8T45Zjjni7b6zjHH7FvMQ6o8Dp/x3p4xryR9/VStz/9W8bxP3L8Z3t+6rj/TrsUCtqbOOPi98SZhzM+/471dsJ+8peuc/A+3Wo7PPMlxpMzvU8+bHnYvyZE12NsNI94wvVvrH+YEfz+P5wfeLPj8Ld63t92/eQfbzLfbv291zzht4wbzaNP/6r1IPq9AUudP/P+Puq8xbWfx0+Oaz5h/TCumP5a84Av9/jNcy1yuxsz3Y/55HWOmw/Qb+XcxO9/wPP9svXpcftV4/5Y2+9rthurb3H8bnuxJBSyPTA/4nra1WfNz64yzrUfmTAenvsi2wnjh7Xx9i/+/IrzVOtdN77nKcddtqsnbQcuDDi/9wrHqa4fO+L1uN3612g/dazLfKv5p1N+f9b8kP2/+cc9140LovnKZPMjtk+7i437Lpt/tz6tt74lO8962uuy0Oe5D8+8eXK/5usPW95bDjtP73ke6XQerNt1c9Hn0mx/D7MOtSvY76fMAzqvs6LA8YTnub3W/tRxfaPv+Zz+I8etvzL/Fs07Wi8P77Tcrppfe9R+4C/Wn4/a3hf7fN9Lb/bvfN+53x/XZZ7g2MP2M2ttv41jTtke7QnWuQSf9p+HvJ7To98HVWic+Rnfq/A58zae9wbjn72fN9/xYvdz2vg6+t6el5hvO+b5Oq+1/b/2B1y/xcH19jguOF+zl/v65uD35zqeM97v+o1xv+PoRfbP5wadj3wP1yl4v+ta80CxQf0J+hevk98fv9V1Abu97477vTJb7RemTTGuneG8tvFOV5Lx23zjp3PGE72ezxedR/2q46xdbsd1rGe+Zt7N94NP2+x6gneb/zGeSza+Wb9q8nvaLse4jvKY98un7T+j66ZijIde6ffbm1de7vkuOWB+6Kz3YYLvj7Md377AOOGA6+r8XrUlR1w/YXxzYKv1r9/+Kcf5OOPxcztcn24/edTrstX5wSXR70G/03yO9+2izeb3zpqfcPw3zfHoVuvZlR2Ol6yvzz84mRdfmG2+xHmPg3Ge79vs155y/tX4YIP9xWHbyYM/NW63fI/+2vrlOtk481Rnja+2/tJ+rdHy2OvnLaHJeaGbzP9u9+fmh+JSPa4ZzlMZx5/rsP963Hb/EddhGo811jjOffoW55vMr5hHSnb+aPtG13F4f+9+0Hk416mdfrvxsHHO2q2u1zUuOFPo/IzrrS6+0fzobtuTP5sHtX3ZZP57n+tDTnt95g8G7Wjw3JXrkkvsB6L5zx84/jcunN9iPPO4+2t3HJJunOo8R/IBr+cs8+Mft//3uI7u9frNdnt7vL5rbN8uer7mY8+8zPFR9D40/p671/7TdUpnj5q3H3ddi+3bc4nmVe2n46LrqTbZjqcaz5k3f8Z80eVpId87bp7X+Gm/63SW2l4mn7Sc3udx+BkbzXfX2b6ustwtr6Mzva8=
*/