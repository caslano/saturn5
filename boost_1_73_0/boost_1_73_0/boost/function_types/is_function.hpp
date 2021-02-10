
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).
//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::function_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function,(T,Tag))
    };
  }
} 

#endif


/* is_function.hpp
rVVRb9s2EH7Xrzh4L06hyk2zLcvWFVMdZ9HiSIIltzNgQKAlKuJCk4JIJTHW/fcdSRmJswztQ2XYkkned3fffXcK1iN49c0uLzBw8MWrsN8CL7zvjdJO/kVL/bJBUXwG90HDNd6/wtUEHq0+F0fwVVafYWytisHXO/NcFF/hbm2CND8TY7wuzCOuOMvBfirbXcduGg3j6REcn539BK/h7ZvjUx/OiWCUQ6ap2NDuxod3lV35rSEPD4Gi732gGggPDgDzhilQstb3pKOAz5yVVChaAVFQUVV2bIN/mADdUKgZpzBN0lUU/+7DfcPKZsDZyR5UI3teQUPuKHS0pOzOwbSk0yBrRED8iimNmL1mUgTonoKm3VYNMCYIwpUEckcYJxt0RzQ0Wrfq58mk7DuOmUwqWapJuaciaPT2WVYrjGZLdiBbDVpCr6gP5rwPW1mx2tyRIlxs+w1nqvEfw0KHoprIDhTlfIBDU0aVS4FCNrDlm5PQYvRMm5uSQhlv943cHhxEWgeguu8EukNa8FwlkXgfelHRzp63ROy9DCxbyr9QssfYK5ACo4JRmEGUjWBDFFM+fIryy2SZw6dwsQjjfAXJBYTxasC7iuJz1AZDrx3Qh7ajCqPogG1bzmh14PybdroX5JcwXS7mSZoX
*/