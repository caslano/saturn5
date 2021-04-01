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
6QeDnJcBR+gcfFsHh6Zn0f5b3qKtLP3Pei30vddmbVvc/JvdCTXY/nOXRrkW1v0HOgFG7xkBdLHQiw1VmHxrdAnnrMevaoxo9DsSH39O5WXvnI0J7S85ETz8lzMonYTBi67D/CViGSrawq989J972zAiJznnOAxTf7yA4IfuugbFCadWvJJNZdBRXrLVsQ99flSrMs+KlFD8uo7jfXI9rr9w3frEE0G6ra5Bn5avQa0HJf0xK6DsyuhHgbELJkH/1Xq9TdnQHZ5jz/ejz6rN0kkkv4MuugOtUAl5YOiXn+rU/FK3k9qMgiSi4mTS1mvdq9O2XSL97/Ufd/MgGEndOfmCyGiz+tnZmIWjJMBe8H+ochjKwyjkph8kVvrbPjut7sHMOYBqGWbkkMlyVjZmA3QVBfiXKyK4OYWF+osPobyG3IcwJLGAZ5aEbb7pZsJCuy5hPIspYXx8fe9411Pv9uPJ6ERNNfvmeWkCICRh6wwCM98pAMxV6Q2jkTZsbxmw9j2dh8DCc4+oZrZyu4gfvqiceapjpepJCOEuo450AVHS1X+dzyXMEHc8tQ==
*/