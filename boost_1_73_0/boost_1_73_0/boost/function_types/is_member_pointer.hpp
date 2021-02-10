
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).
//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_member_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::member_pointer_tag> 
        >
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_member_pointer,(T,Tag))
    };
  } 
} 

#endif


/* is_member_pointer.hpp
sJ/BxAQAAAgKAAA6AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9TU0hfUFVCTElDX0tFWUZJTEUuM1VUBQABtkgkYK1VbXOcNhD+zq/Yof1wTglnJ5m6adNM8RnX1PhgDi7pzdwMI4MwynESIwnbN03/e1eCi+20afwh3ItgpX327dnFX7vw7Jtdjm/g4KtXYX8FXrjulVIpPtBS/7dCUXyE4YOKa1yfYGoK91ofiwN4ktZHmFitYrT1xtwXxRPMrY2T5m9qlNeFuUXJoDnqz0S3k+y60TCZHcDR69c/wXN4cXh07MEp4Yy2kGnKr6i89uBNZSW/NeTuzlf0rQdUA2n9R4B5wxQoUetbIingfctKyhWtgCioqColu8IHxkE3FGrWUpgl6Sqa/+7BbcPKZsTZiR5UI/q2gobcUJC0pOxmgOmI1CBqRED8iimNmL1mgvtonoKmcqtGGOMEaZUAckNYS67QHNHQaN2pn6fTspctRjKtRKmm5T4VfqO3n0W1Qm+2ZAei06AF9Ip6YM57sBUVq82KKUJh11+1TDXevVtokFdTIUHRth3hUJVRNYRAIRuz5ZmT0KH3TJtFCa6MtdtGbB8dxLSOQHUvOZrDtOC5SmDiPeh5RaU9bxOx
*/