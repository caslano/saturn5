
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
56c63cMJyEkrdmn3+oy79rFVPkpfF2LIgNvCghmjUJ+Mf3DNJ/d+QCryK/1tSOEggXG/pNV+eWiYlYCOGbT6TrzfxWhcNAQDbDCf6XW72ZcQKGu7z1aOiSpq6KoJhWe4NtjEAIQuJIT6XRVkhDCl65IBkqtqnp8hBsqRNk78KTD3aOum0eHIkXs2eZeDG+I3Hi1CC+zN3NJ7//SspSHnxJXWiH3xshH+ZP2iH+gIuyuSiLzqcGX5fVMcYgUbiFTdAOO8+X/eZQLHNfxHKqI1cNmRwr5PUc/YbofzULVYujaFMqyzcIbPwYsp5gVffA3xH1EamedZV2PWuW2YMo3yprr36XQsuSIcyL0pFPpzgOf0IU6e7EPEXIdn+BcNQnW+KeUI3fwitODy4CQ1kFPqKNwe8RnKmSMwz2dWNSVyWWyI+PNjl5Ovr/OWvVgm+UjkBVVRMmEothoYrZmRafBH7nuzdP55WZI6+UKzpSk6OQrMUtBiTdyJVn95bewzKNeHNLvJbWEYT0GZlDQg0vtxtOq9peenD9D42OdjbOAtbHnqzT1LoDGWNEruah8FJ3BegF0KYyhr2g0Eg1T/Zi8LV3sQU+yuYMldlD8xU/CrnBbUhDH2Uris6+wxFm0ghrsg4gflcrebICXW1NbboxsPy6mokYOWcydZPY4u2k36SRDy7FxQTcDpvv8keXzc/jGrtnK8+gr7aUG7fZri
*/