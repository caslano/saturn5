/* 
   Copyright (c) Marshall Clow 2010-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

#ifndef BOOST_ALGORITHM_SEARCH_DETAIL_DEBUG_HPP
#define BOOST_ALGORITHM_SEARCH_DETAIL_DEBUG_HPP

#include <iostream>
/// \cond DOXYGEN_HIDE

namespace boost { namespace algorithm { namespace detail {

//  Debugging support
    template <typename Iter>
    void PrintTable ( Iter first, Iter last ) {
        std::cout << std::distance ( first, last ) << ": { ";
        for ( Iter iter = first; iter != last; ++iter )
            std::cout << *iter << " ";
        std::cout << "}" << std::endl;
        }
    
}}}
/// \endcond

#endif  //  BOOST_ALGORITHM_SEARCH_DETAIL_DEBUG_HPP

/* debugging.hpp
EttvXsOo8ZddHABda8a+QQ9Zh8xDld2Y2tpvoVV3ZcDJTDXYZKOI9HRRoiQiHSMcszFCC5kcrE+h0Z+q8tx3QG+OlcB9kgSWO+6yyhnmbr8LXVx/To/83bUlb7CgodfUu12v/u64um9xb1f92hO2OPERbRYYhkaglxHZlbqz6ggM8d2MKMJfVhzQCbr14IoqfSIPQS/eiVBNROk8o4TzpSnNHOH5allHS1xjzIKDG/DMlXsaCooAKSE/EqDnO4LqVz/XLCzShKnhDGleI4FMnu/uizR/MD2C3gzqv1d3vHZwB31UZmzVLRvH07NMnS1wiNfwHzW3S4BmsBjLP2TTwGm0QcRsEeygCv7W8dRbaeOc/VRapwmPKnVMEdkE6Pp7QVmYySxEllccbkY6sx6JlPAvrssqLApHieJ/CVEaQRpWRbqkGwQJRVJKuru7WaV7pUG6uzsXpEG6c+leYmGpZXdvvN37MvN95/zmzLyOj45ab/cDr9/7jW43TYwpLe6bld+Kj4UfjmtXXvmk6fisZcr8+1DD+0cZjMNhMTynlF8oaqXqMQ0MIGO+dSU4XmW01i4bq2bLqrX15tUC2L05Foueysdqsmu/CPwi02COKb6y+Xs2rC6J6aqM2oAWzeXoAsumOwb249tzR+1W7rEVPDmyBLHZQQdcvySEDdLt7F2bnn3ewHDtGnL5sFX1bsH4S3ak8KZk3rToY+wN
*/