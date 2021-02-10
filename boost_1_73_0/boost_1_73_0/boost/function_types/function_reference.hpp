
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_REFERENCE_HPP_INCLUDED
#define BOOST_FT_FUNCTION_REFERENCE_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/function_type.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> struct function_reference
    {
      typedef typename function_types::function_type<Types,Tag>::type & type;

      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,function_reference,(Types,Tag))
    };
  } 
} 

#endif


/* function_reference.hpp
ff/x451b0/6v/V7sQ/cIq8l2NsqLVEmJ1xioj7cNJhQRzqsKwzjqbms46Z/2pz6QBkw2qbD805QjUsL4gPkCK9TH5Cu8L/UK2bf15O1rUAgS5p0r45RhUWlg1lzfWWq8QMV7VShKspXQfCcWWImigDmHgi/QPWlYul8JN+mjUC280/5kGPb63p/H23xYTjcIuQjj3lkyPvfbRn/kaN/U6s5cDCJ7YVmw+bFQWLA+3PA1LIW2Yn97Ui6yPZLkpHrIKtLRJWGrhwTJWazfGvlt3KXH5CzCgwbTnCGzeO+YdJUKwbFthoGsi+I1NQ0hGdU+dQE0wWWqMvy5woregyH2Bf7TjyAWiLekFvI7r7AVbbCjLEGdiq06e3RkzDAXuBa/88SQqmP8tQm8WZecoKLvYxspeg9a5wnebCvwgICDI6pk/0lbDofHGB3ZssWrF4pZ6PeKPUqcp4/dKoH0pdghpSkPMTKKgoCH3b7UxJfjtChwaOzpSU9bcZ8dwNAataWTftSbDiYk7E2YpmK02UHTRNFArjaaXC2bnmGHdjuqXdYT02WljCKaPHyEvZDN1S3OHW9g4JobbTVRTuXcbQIW+mS7Y+Y46+ccD2RKYqCUo0WBPQPPe6zEYZIyW+v0IDV2emY8FQgZ9eC2v+ck
*/