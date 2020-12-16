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
z7dm378RYg5trSpkRYJ0ytOJnGEZL0SBtEybyUgzbybLeTMhfWIFPSiF9tPZ9mqzGAqtQMa6/Hb6sn4r530fiANLym+Zj0SrNRB9Ge1gwK05Y8MwCR7A0xpSD05Y3zopjY6eRU1ESiDB2A0MdUB/O/jn40Edyv4w6qTf/vBmY4PB//0zmZ+2g7MFP9/jmx8v87Fie7nEXQDgm//dCc5358rslwDA17+bAkMk0KnOHGBf+DZqSpsG93Sc38oPm2xKLbMFmyJYDIWM+QLLwrXiuv217MZBIUkWad4b+fiCgSk7+WWwz6iE4IxxyIDJontMU4fpI5TgZ4CRz9C5RC+CUVjRVGYqO8VSzpZ6Wy5hQQm9dq93pJNrIkqOQUlgrSyJLlHhjw1cuGbm6qY0tOupCHM2tUOvGWRzYhUEWa3SWtY1VqLb6vHwL4z/6xgftRaAn6oqagJKUik63xOdDYkhXZWNJTFS7yOp7e5aDleSCkkyPzvtcA6Fq9vt1IyC+m9mpYRdNVW8Wg3O9cw29FbXQycQklPLWg9gkFjTEdHzatphNE7l6xpE2DpKn40dyuGaWK0Yt7t6iUp5KWqcGyNR3gOgvLVi3+fy6JqK5sh2bzkOEtLh5D58Y0kKn2zphE+i5zvpE78LcCalEY+P1gxEi1UD0Z/HzUJof+ehB9YDvvydRg829z2RaR5r+VGTe44FewsdxL/nGLoIT4RPLZIG/rGXHwkXX5XTvAkRtUeaj1IouTc0InkFX0Q/gxftnuItZ4TJ7h5shHWglf6Jwv+wSLvRZC//3AzthyNmG31zxGyXHztETaSM1jFB0pxVPmg4+GNJNaUa1WQg2wp9qWmvrdcrHLXRUvSl1HrIyB4tPvaSaTiT6XHkOUyfyOxTH6mUwwW+QE1kqUS6S3z0kS8Nr6uXu0bNzZT2s/Vyn1Vz7Zxb4puLwYilanaunfx0nLQ/gKisJLa/Dz9cMY1Nc50cuoRyM6EgAeo+u52mXk4AB0ZyUo1thM3Ps6J8JyHyY0BcSqoy6+G2JKW9V30fV5TBL2tM4ASrl6okNFmSUGsIu+5BxSChMvH4p5JARn0tCSKHPgE3+2tJSgjGKr+hZ13Vb5mio/rNLlrjm6aSQrV0dIe6l7ijVqWrlZKuJv0n0dW5/mxuR6S1vNqEWIDNs8m3HiZhzRBqwlrR3x2eQ1tQBSVHIDm8wm21lItwd3gB8uyFZeEV53/PmdXQp+o00ZYECYf0OJynHJMqFBkKR40yM4/xUqKfslecWQNkcvOPTVKPORcpHDBJhNHBe8/KSNccuaLHYAHbhxDGdYtc2ANIyKhYMgKWBR3kAm+VKdaqSNuIEV31a8N8HDf5xlAu/h80QEsSuGC3wIKr7/X3E3/uNOHe/Sw4tQLhcvm0Mq7x4y4jQz3fM2d8pJYnGsd63PS45R6dtoPDi9SJuFOsA+dEsQ6H9sITiZaHm2IAtNk0MvIeB0miCQww3BMtNuVE+elwaEYbWasaDB9h7YrdLopHi8mWSd3AFTgWm3j9pEZXtxPgssgnCz+PNK0tP2Gywnr94VfRJC8jyspl/BDbO2MDUihnLOtOxNzvNapMqgcHy3a7XMTowJzhcuFqawJyAJ80WrsCc9qw8lS8E5BjeagxeZwXqivcUorG756kFb6Pw0r0goxFyIw1dijjELpiRrJDmQs2+MWPV1Zcwl9QfEjk+x+QCN/+1WUjiAq9eVwtJrF0sYe1MMTCh4qHDlPKNlX8W7ODZZ/0bNhCyL3rkXWc0sGZx/EeeftZJNMacyUWK1e+SymusDQP/RpWJYkgU6nys2lJvIQZCohfOI3iFz5B1yXPHtaOsw9bdSdrE20Ubxg=
*/