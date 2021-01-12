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
ZAaZbYWHYKXchl4vt6G5chvaJOKmLqWu1td7cw6lT61PJFig+kzVw2odGTD+R/aBy4GnQ1k0JX/lRaM2ksx0Kxn50KwPiKoUoHTslhaXWbzrBsziAVNMmla6CP10vfCSNMCGqTrpUR94nvhJK//cuvcTVhvzcnQZFb2chKXU0uIKM87T86FJO/qpq5VlLS75R8wDfB36Gp+HukSM5Yx1tEx19tmWyo+sLmgvDburzodemlpN
*/