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
Iu5y5k9c0XH7zxlMTyNOkMxHF6DGfrMcLvuT5tgDcgDjGbuH7efX9et3/Py7seBmBG+lhgeAYr1oIOsWSQGFAFjWK1cQ6MUcE2gkqnHA0FSmdt6i9x0jSFS8GywoILc8l25hp4I4s1L0WnWn3G3553kfJBFxKASaQP6iGQUNZU20yp+uw2ErVcYFFJzAS1q0YexqjIjigfDow4VI6t/+++FfZTA1K3OS+Akyno07KcU5iUrwQKdKjbepZfr26f4=
*/