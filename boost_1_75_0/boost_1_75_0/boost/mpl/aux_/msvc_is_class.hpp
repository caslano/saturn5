
#ifndef BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED

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

#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/yes_no.hpp>

#include <boost/type_traits/is_reference.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename T > struct is_class_helper
{
    typedef int (T::* type)();
};

// MSVC 6.x-specific lightweight 'is_class' implementation; 
// Distinguishing feature: does not instantiate the type being tested.
template< typename T >
struct msvc_is_class_impl
{
    template< typename U>
    static yes_tag  test(type_wrapper<U>*, /*typename*/ is_class_helper<U>::type = 0);
    static no_tag   test(void const volatile*, ...);

    enum { value = sizeof(test((type_wrapper<T>*)0)) == sizeof(yes_tag) };
    typedef bool_<value> type;
};

// agurt, 17/sep/04: have to check for 'is_reference' upfront to avoid ICEs in
// complex metaprograms
template< typename T >
struct msvc_is_class
    : if_<
          is_reference<T>
        , false_
        , msvc_is_class_impl<T>
        >::type
{
};

}}}

#endif // BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED

/* msvc_is_class.hpp
VDLvflWA07scTr+uSzZD/2r7gVpuKGtZ2y9gueNjw3I4/6RN8oP0Mdf3ENZSS3a394H4haKXm3jOewqBq0KqTqM0Pkdk/lMFTuFqbA3wTt99G1xSZ74/iDnzcRBUf/mXDO44J4moPFeMn7GDPCN3Qi2BkhMlbQY9F2mJ9igaL1cjhOsf0WmagblASR9ZvuMLXl1nVetW7Z9zaZRWuqn9YVFN0hJ+i9K6UeQENf2ueh8NLdk1NyuQtam6+hH9K0KPDqcacERwLgR1dBjFMEXBKMRoJNHquNXYeBi7k3nIL37g1Rk0kMdviryzusJHVpn4GE2392WZYlm2DlxZAHLfdXDd/ynAIQf7q2VaTXVCLh7Jvywvzeev1ChnJCbpQ1Grz7uTn0MKHmPwEy2oj1kdyI08wBOm1ZzWqb5jGYIlX81GWn365awiWTpxNfs8P5ZCaR5BYZfBILEbEFRbi6kk53G9UrGatwU1piuo04ug8Da/b6TJWWG99wFZIchBszO5vCKlLSSn0wLW6FzKtD/AI+JxdpJkVNqfJaVt5ZJvTKYeH7ZcGsPy27rjIb5Nbjc6j3reJf5nnd8JOtWbe1IPgNnIxPKHrYBgb7XmzbzL3V2wpT4AwDu3ArhY2oUOcOIZsY1BnqYOOdtMDCnm7Wb30adVbg8sFA5xyCnmytz7klVUSdyxO9fWTZ1JACxcYqltRLv9mzSN1dlh2Izo
*/