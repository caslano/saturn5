
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_REFERENCE_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_REFERENCE_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function_reference
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::reference_tag> >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function_reference,(T,Tag))
    };
  }
} 

#endif


/* is_function_reference.hpp
oDdLuEMORrwxNioj/P4Z8ofxUd3Dl0UV1htiteUY5micvJmlhfsziVLtEESZkoKHTXufv/A6TaVUG0lH+qb1y3UnbjCYgZBnO0q2sFKw/h9i6J0udmL29/PxHphR3duuGMLUNFSnyGmfAvrB1itxioGo1ZKgfBt5Pep0HPNY0/g71qGguDTurFSVPwjltKbDPLtCyqzkY9I3TD2XNhyqGbJABYpJelIik53OtArqTgEERbGhTGSpN5XGswfMoytHm1RCnzxyOIo0bZwigMeX0zaa5lXfGwrUqhgcY6EdF1Nqw/p4JcBt9ksgJ5lKXrUv1QWVEnpU5wW/czTTZ6Cat7v2YpGM2OKlli85paW4eXOlenMfsC0nRU4SFTC6h9pFVEkf9IxJgq0NHRKMq3TyfOpIY3I6Rr9/KP4RHYGsMi6C3/HDP5WQqyQxodK9P9Fo02wjuc79mDQPJTDRuZZZODRAXYUc8+tAdC+v+99Z6pYLZpsgYPtQKwxha7/dxGWGfEQzRFuNkReF1sr+YjE3zee30X9qzaKMPhY74wpmujdpvsJdyoEFemPfTQ==
*/