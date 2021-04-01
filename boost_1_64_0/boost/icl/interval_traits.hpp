/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_TRAITS_HPP_JOFA_100926
#define BOOST_ICL_INTERVAL_TRAITS_HPP_JOFA_100926

#include <boost/icl/type_traits/domain_type_of.hpp>
#include <boost/icl/type_traits/difference_type_of.hpp>
#include <boost/icl/type_traits/size_type_of.hpp>

namespace boost{ namespace icl
{

template<class Type> struct interval_traits;

template<class Type>
struct domain_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type type;
};

//------------------------------------------------------------------------------
//- Adapter class
//------------------------------------------------------------------------------
template<class Type> struct interval_traits
{
    typedef interval_traits                     type;
    typedef typename domain_type_of<Type>::type domain_type;

    static Type construct(const domain_type& lo, const domain_type& up);

    static domain_type upper(const Type& inter_val);
    static domain_type lower(const Type& inter_val);
};

template<class Type>
struct difference_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type domain_type;
    typedef typename difference_type_of<domain_type>::type type;
};

template<class Type>
struct size_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type domain_type;
    typedef typename size_type_of<domain_type>::type type;
};

}} // namespace boost icl

#endif



/* interval_traits.hpp
oXxhAsjELgbf0xcdbd0gK7hnaA23XAU6A2pdhHi6Y/a4rrKxnC7kDBTnlZzUuEaKFvs3pzBUL35G2uA1gvqn3gE1el4YEqWpKoclXEwsUpLiPPsgjnfVbSG+XVzLKB05IeGdkbjW//yg3V0RaNYfMxrbA7x7mfE8Y+Md7AZVASIQkX0bwraaYRCdt5dYXOktz0zi+VEmZxc+HyCDh1eOIYBRsM09zB+99v89aQNZzI9RJNcF5in0t0idqN26iq/9xtxS+MjltL/XbZ9WtOhK9Kb1x3UCIZLzYXEZGaIMTaxIPesVJnKCdilSUEbBl/k22EH+E6ZHXeZrXOkKFTSZB3156B0f8dHti2zfFhrQi4aGIfMcPMBnPWO+zfuxT3HDG8TpWWfIM1MIEyDVCJDIN7gLkKz/Ab+EpXcFqMbLtDe4ba7ItTV/FeVkX5/1B3+g0DJH9pGOM2OPqT7ISuJGeEGYETF1o1YJHXFIaEAU5eFnndocwJubGHw3QVIaBhvpLWkTCLPMstxfLp3j0NOYMAZlUz66srqiS0cCQNJQscoh2aJqnABicr9Afg==
*/