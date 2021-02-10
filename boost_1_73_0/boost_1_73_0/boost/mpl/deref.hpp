
#ifndef BOOST_MPL_DEREF_HPP_INCLUDED
#define BOOST_MPL_DEREF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/msvc_type.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct deref
{
#if !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename Iterator::type type;
#else
    typedef typename aux::msvc_type<Iterator>::type type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,deref,(Iterator))
};

BOOST_MPL_AUX_NA_SPEC(1, deref)

}}

#endif // BOOST_MPL_DEREF_HPP_INCLUDED

/* deref.hpp
QnEJfFZKcNpv6QOWxuq3AmNJfgNZUC1evGPOoN6L7jdm0T/SsJf2j2E5Kjr8DKuH9nx4uncW3TUuWh0flV3orHYrKTqLRRzwxTRUTucdKpiGq3iWhbbjJy7O/ke2ClTnP4AQeyVM15q/oGx9qZvmMw9gXP2/Davon60hrouu61wjgfQlFiJ2VJb+AC9ZmFIHqkxwb+KGHey8SAzXjU6Rd7RvhC923zzC927W/SSn7TNxxNog6PUn/+kTlzL6mST+7LDoNb9E0E8k7W85/wFQSwMECgAAAAgALWdKUlNXLeFqAQAARQIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTM5VVQFAAG2SCRgTVLLTsMwELxb6j+sirhR3BQqQWR6AUR5qRWNuLvOhlhJ18g2rcrXs4lL4ZJksuN5bKIihmh0wJlQlirHtwb3O+fLMBPzolj2F1guVoW4dRSR4ugF6SPWwtRf1GAJhdcUKvSjezKutPQhlPzTUDLJihNYod8yLdgShfL42e55XOqogZyp0TQ3wz2GYfKV2XkGk/EYFs8Dcacj5rD6ojPIruFJE0+yS8iu8uk4n17Bw2sxEEk+h67RKPRAVrpBCLtgWhdw0DUgNNE6yuHwSskuQZfzkIiD3ra2
*/