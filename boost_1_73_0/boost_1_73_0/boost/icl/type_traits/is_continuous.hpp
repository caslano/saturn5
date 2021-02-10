/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_HPP_JOFA_080910
#define BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_HPP_JOFA_080910

#include <string>
#include <boost/mpl/not.hpp>
#include <boost/icl/type_traits/is_discrete.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_continuous
    {
        typedef is_continuous type;
        BOOST_STATIC_CONSTANT(bool, 
            value = mpl::not_<is_discrete<Type> >::value);
    };

}} // namespace boost icl

#endif



/* is_continuous.hpp
NLxykWWOcre7H7JXP8wMTtjWIc1Q4frzJf977IBoM6doX3LuteLa0sR9vQCejQ4W7TSqgzWc/wrX3zmNOBp+JhpvVfzUFASn14FEzufy3fHwR/h/f32FC3srNPh+8HfxcD/sL6LOBs5+blPp6mivM/edhDdfg9HWO1saL2s3cldt1eRLF979oob6htSw9B+U+uiDjP93gceK4t2s1+LMynZGxuCukG3YfMyYGFvVvKTSKX8IW+006EWEskTuymovs6rp+6QP25f3tDyddidso89hiAWWnff/xtkAHm0oMNfW+b0A7Pv2AH8JxXs7WeiiNavsn01eG/O9cuHQXklcd75m+A8ifj46H/Qnk+niI33KiKAhaVDg6aQFDPsv6t+Oo++GP/cvrz+3I8fw8TPEe4SP3E9ni/l5/5d7/H5OBdr5x8uf3l2dX55fhcTpv6465M4dbzCej24n0bDnKtWKT6tt2i5R+7jrEa7t1lQIbY8+ycgMdVR6rUrbXXQUoR2q2u6V225UvPwlHh4RLvhOkzTtPgnz38w0n7xMM9FP861kKejTrA1Q6WBz6denn130IdN5arTrbDC9u59F83k0POvMaPyVmFgZig7RkZNjpyO4p0YfNsFpbo1JxLiOn8Lg/wBQSwMECgAAAAgA
*/