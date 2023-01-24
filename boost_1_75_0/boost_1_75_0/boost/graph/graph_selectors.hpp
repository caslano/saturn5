//=======================================================================
// Copyright 2002 Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_SELECTORS_HPP
#define BOOST_GRAPH_SELECTORS_HPP

#include <boost/mpl/bool.hpp>

namespace boost
{

//===========================================================================
// Selectors for the Directed template parameter of adjacency_list
// and adjacency_matrix.

struct directedS
{
    enum
    {
        is_directed = true,
        is_bidir = false
    };
    typedef mpl::true_ is_directed_t;
    typedef mpl::false_ is_bidir_t;
};
struct undirectedS
{
    enum
    {
        is_directed = false,
        is_bidir = false
    };
    typedef mpl::false_ is_directed_t;
    typedef mpl::false_ is_bidir_t;
};
struct bidirectionalS
{
    enum
    {
        is_directed = true,
        is_bidir = true
    };
    typedef mpl::true_ is_directed_t;
    typedef mpl::true_ is_bidir_t;
};

} // namespace boost

#endif // BOOST_GRAPH_SELECTORS_HPP

/* graph_selectors.hpp
0dC53f+ELxGAhT7Chy5LNCDI8xQqJyVL0F4kWJRf8YMBiDVDkLk19oM9Y0lrPmKVk05/rBiApal+u4b+kVul5safETwZWt2IxsA9MBpRHfajnIX6jMN1PO7RmOKhV/LVGH+O8mjGNAHzr4vC+eVCmj4HTxV7cBSR82jcFEVyR38dWSP88TApurt1SoeHKQMBJoPpJYBvmuBR9ebbROrhasIkGF82rS2FdJz0Wa0RFGR2EW4Dh3X5SpIre53RX14EP46qyXMyX0cHEUsJFUpgz1Fj58AM99EXsSoiXxShePlcqIszayVljbJRN52E0WBl//vnwTnm/BjWo2RbMP2qqhZ1jXk9xln/Y5WtF7uYvVJ7+2f5kfFvcsGkWjIY3qLSCe0ZfBooM3WfXy0RFbbWr83aYGllhTaDrtbJFsQErAgUODFfboVv6R76FLMLkS1jgy0Jv3IwQZm/lADuvwj9HTOL8A7Xhal/D/eOLURT8EB7vCw7tE8e99stuHqe9kT13gqSGZlXM/YpjWqPFZQzmzPB+6TDru79a7hQJL4OfEbt/enVQIPo4ynCIQFa5fTG+gryGSEXUdpxI+D3SXm/44j2/WjczzGA+O75ot1VlkQfzfvwXflmZDV2DVKlTDNmHY+IPN/2k3fT2R+BbJp+rV2s8ds1NYuuV1YRgK0KUhUV40S3vxB7yVKdIg252mFezA6PMavnDi9gWOtf
*/