/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR30_11052014_2316
#define FUSION_VECTOR30_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector30.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector30.hpp
L4PyEZH8LC4TD9VGIESs6sgniFZMqmqZ6c+9NMuXmxr4HOMpQrk0US6ZlXPJuUmsbDye2/kis3wzUoOrtLO2Tj+DaGMjYlNeQfJXZT/0nXBGg5Fvuy2YxP6Ow79bBjvI+1RHHcM1l29IEhw3pKXZy7JhsrzbI1y+3CQYQhfofCqTuvjEeuL4LAUujYCFT99vL78oQptgmLtt4C0YiMT5H3Crp4XTNzo1cDZkCrFE0IwlbqBXMIrAYXqVYS/fa9YXze+YMhW8v2uVTu8y+sSaqERHVLnOKZ8JPBmhrTpMzZAIGE7gXrPo3RxzaO9w+SAOpTeQaC+7RmClYuJ/gH8RYuYw6sxVwBo07PnzS1UNJDGRkA0mOuTLQvjSElJJb2ipOipwQzM8c8fZNyQwoaA+UE8H7vHuGPZvDHnsAWAWA8yBW36j6p1pC7uR2Kn0DLDqJvAu2MvgTAaadPux+h6ies9qY5UP8SpPHAmrEhzvlM9+YVU+ZBJVdudV2suuV3mvD+wT1WZgtXBOG+MZCFU+x6p0fgDoEBwJfjj2sgTqXIy9DBRYhH8I4eFeUyQbNaxYB8YwaAvQ6WwKUJHyXf+oapY8I9Xpz/rO2xBxjxVWxin/C/Ok/PuGxYS3IxqA7J1aQQFi0U1ZOx8AgwuTv/VlDRxHh1BCzZ/1v7N8hbiZk9lWrc6qg+0sZ9UFqlgJpf40+ZD+ANwtR1Gy32S8
*/