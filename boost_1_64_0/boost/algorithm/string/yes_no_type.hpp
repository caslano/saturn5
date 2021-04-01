//  Boost string_algo library yes_no_type.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_YES_NO_TYPE_DETAIL_HPP
#define BOOST_STRING_YES_NO_TYPE_DETAIL_HPP

namespace boost {
    namespace algorithm {

        // taken from boost mailing-list
        // when yes_no_type will become officially
        // a part of boost distribution, this header
        // will be deprecated
        template<int I> struct size_descriptor 
        {
            typedef char (& type)[I];
        }; 

        typedef size_descriptor<1>::type yes_type;
        typedef size_descriptor<2>::type no_type;

    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_YES_NO_TYPE_DETAIL_HPP

/* yes_no_type.hpp
aw3ZUSS+ISq2EJVm5H/TMhvHcXRzgzc4YqCN6CbcfJITEYglkN6hhaV20hcRXUIMNkfcZNKGyh0RixRP+Cx/dZCUTJV1nVUp/TznYYPUOkrdKycIfGKij7jzYbDhkGqeOIO27RpEXLwheYHSsew52gTibIHFqLpI3DM4rVpPfYccPL+yXkOoHoP1adYeRrp9oJH+rvteJMbXW0qy6SXwx2Qe9tktex6t1g65KT0WOaAYk962Qwe6n+SEWKyepdxlJ8J+rx4hCV2dmNDhvNcQijnk+BFuM2T/Wykp+G0MlcC+kjnEr4IaXiYgATfbhhdPbySwBKVmCHUqYySM6zBxz3Hpqvlr1Yu9RDa7rwj2noTLIkvn6NgEWfcRuankxT0XovdIho6Vu0a6vozgFMfZ4eiJwelkvM8PbA6TeV9B78+g9P/0Gq1UeKcGx/fxuKclUtENDzDfKcJF4GVsyW9oMk0bNOTYClMAm2ijLP/ehSNC2bzSDI8xWnkAvQHZ5U63A4HfI6+cu2ur+2BURwwN4jkGJLSkez55eQmZ8tm1YmFmm448wHXWNzSv5g==
*/