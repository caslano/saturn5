
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_member_function_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::member_function_pointer_tag> >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_member_function_pointer,(T,Tag))
    };
  }
} 
#endif 


/* is_member_function_pointer.hpp
AzQs9izHkCDuflmezxfjX31ZEZktfEDGcR+g4OT5vBp/9XV4lmNQJHc/h+dl0gz3ZpVQWTJ7DchG8luF0Ux09lzayWIjk/Ea+WCpRViP72F/prs/IcYOL16/p0JAxdXiz03yV6XgeuIRWpgoxbbqXpABP4E3VRlxHZAQfsePxAmaQ2K8llzSkEvCIblhKskKbQMRYMMhSULOjHK4v6lUJWFWUKZ1br8XfFq+IaWCtFArSKQCMrtW4/ixAjMVLKaCaq2g+R4sIMWYVKsV7KUCUgpICMvuhXDSSTooVFClevq6TitYRAV1Ps0+pWvWMJCJhoEEhEKFrqBCX7BEV7BEX6CDQuQ9eijo4NaUo4ebDtI7c/SQnqPrY46+j1m6gllagef27LSUKYmF7dPmTGHk7Nhwq8k9NU4Xqdo734KIDZH0g0oZcoRnrhpD+a4c3xjKWZ5llSaKogNBCiv22kzpnltD5DFbTmGIwouChHzSbTVEf0SXwXCyymRMzZJ9sDu6aEbuf6OCAolBuOAk1u2xmdSAgj/jlvETilCo3B08Do6DfRlUYDWpac4/M3zp0IciRNdiIfOMu5uzAw6HcAx26PwJs9W32Xp3YYePfFRFrAfkf71Ii3XhFWmQHSfyJFRHHJhETMIu+vnEE/Tze/r58BO6mE3b2TF7XjGbgvQxm/z4ZPff1q21WAn3DvcJ7y0NzhWsBoZiGZjrE4fl
*/