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
Py9nHz6ucb5rUmQtyI3bC8moDoIf0F1jqCxfyNXbW1I4na/Jzvj165j1UdkK45hUes+ZtIrx73+kA1VutWtYwtXidjq/QXen+xn5dH4RA6YmJYwVOqlLdlgqlMmiZq4iarQiYzafwIJRIKFOMa5L4GBzTb0gbwsJnuByXjZG2gSRIMEioBF5yQ+B/pB2ZNJXJrGZTVSVI2jMrogo+DfgGMcpWNIpUBckzLoUYdAMQ0nN9WL+4Xo2Fxbg2QNBzmGhIfeQ0d/9GKwMF27urtezLpM3bd5YzBOSOJA26hDetGQK1aRYTSwZin5jpCJYVEDE9K93o2tK1Qj99ZcWA4EinuXyCbICUEDUiUl7oAzVJ0PfZaaGc7FWP6m3McfhEnm9xDc/vY1F1WI+JS9P+wK6JWW/Cu3+tCVs8hLDw+OyAYOp2GaAgogERgLOIO2K8ImhyIi1AeOEufP49WV8gYRTbn4gMP0gNt2OltM5VxTB7OLXuCeM3mHfZsiwJTHP0+Byur5bzo+lFdemaWv3nCi+Hy6zY/fmsC/rNIwIzIXHSnzQeRuKfjW9mR01MNeyeFcGoeeArzN7itHFiQhQtykswFMGY1ezv08XV/MFO04x4+RSzaCdeMx8+NOnGsTnYJU3/lGa5eA5ePOi6y8i
*/