
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_TYPE_HPP_INCLUDED
#define BOOST_FT_FUNCTION_TYPE_HPP_INCLUDED

#include <boost/function_types/detail/synthesize.hpp>
#include <boost/function_types/detail/to_sequence.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> struct function_type
      : detail::synthesize_func<typename detail::to_sequence<Types>::type, Tag>
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,function_type,(Types,Tag))
    };
  }
}

#endif
 

/* function_type.hpp
ocihlOP0sSvCfRzUJjwlizX1isYnzOKrxWAL1tH48+hsHMXRwbvDq8WEMtxuFUgIxhS7BrYDjYuzRCBpPNMEJtpa1mzMVLaVG+7eAwDarUXoQ5uPaPKxBHbrpcL1QgtjD7dZSIexLBbKnWxhUA7ne3BpptTagsYwxbTBsy3dBxiXK/ddIPqXJ2EcOhQOA0A2L2ZR3A4OpKldNxaKqCJD7plHqWz7jME9aJccpO+jFwwmezswkSb5yra7fxIKxICdPbQSYgytQtv3K14WLHUzQdEGeS8ljfK2061Be84xZ+wEMULW5DfFvzNVAnDLkjVCCeCxzHG75VuqlnPVtryNxC6VKpBCmpcSF8alqtaUbLjtrZjGqemxouIsWwOtTNgGSL7iLmPREDmF6No+2Si3rtPGRsjPreWy4Ijw2nMYkMz9QRsRs7665VU7LXbl1Jp2nXv66PwSs8KVnEczOoCDMMvc8v4+eP8ueHP4JGcbS4nl7XmcYUFzvCfMY+AcRd4zKdpmCFqGttnxXs4O7GfHeyk78FV2vBeyYzeo4Cku9uO/hX0DKf8GoN5XAP1+6b4bh1tbH0XiVlhq6FuhZFyud3dBdO0+QmZzzGvXw7RQ2r6SbNu06+dek27XtW9kODY3DBHA+sa9jc25i50V
*/