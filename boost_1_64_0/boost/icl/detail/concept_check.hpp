/*-----------------------------------------------------------------------------+    
Copyright (c) 2009-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_CHECK_HPP_JOFA_090913
#define BOOST_ICL_CONCEPT_CHECK_HPP_JOFA_090913

#include <boost/concept_check.hpp>

#include <boost/concept/detail/concept_def.hpp>
namespace boost{ namespace icl
{

    BOOST_concept(EqualComparable,(Type))
    {
        BOOST_CONCEPT_USAGE(EqualComparable) {
            require_boolean_expr(_left == _right);
        }
    private:
        Type _left, _right;
    };

}}// namespace boost icl
#include <boost/concept/detail/concept_undef.hpp>

#endif



/* concept_check.hpp
ArG+WoxcjcmAAwsASVBORASr7IkZjity+ScQFXOXrEhnDX5LBZnQ4jPhQDPNtQq3C23kJEUU4j3NCR7C9es2lyg46bR4PtltQZ5MpBiKPBEY5p6gX6vY3zjx1wbr15nUX0h6D+gzKCbaDEgljaQQB0IgvdQ7w14SN4OrZhyEm+DFQHdUWgVvakO60fZOAJbp3SQ318IY2qyUL6vDeVh7O5gzw+eTltGyytT/bD5PKevvOcrg1zKmx+Y3adqe/8hHuPDMZNuRVYQt42eDul9KJMRu41PmSGsdip8EfKiC84PyxAMZR2jkf6aUxnjA4f7ECgzOroeV5gjxO1xhB4V25MmkGnYE/ypHBkpFDMsM3h3qv/dYdTtkYUBbqTnwop/WKQQPHmsqKCOsoj1ww5xaAE+j6fDsG7a8/Tw8O4v+vRlP/HRduoD8TCPfRO3HxVUr7HVUQA8xw9VsQJ0bR/MnG9HzBxJ7feZ+AejYMDVGZSZ4eJ3u+kousAUDAjvYqzPqt7jkZq7gI7qDxpNrikN0PxMY7s98mUaVVytN3YQGvMlpjAs8+Ekmpb38xA==
*/