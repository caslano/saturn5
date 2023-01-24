// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_STD_QUEUE_HPP
#define BOOST_ASSIGN_STD_QUEUE_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <queue>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::queue<V,C> >, V >
    operator+=( std::queue<V,C>& c, V2 v )
    {
        return push( c )( v );
    }
    
    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::priority_queue<V,C> >, V >
    operator+=( std::priority_queue<V,C>& c, V2 v )
    {
        return push( c )( v );
    }

#else

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::queue<V, C> >, V >
    operator+=(std::queue<V, C>& c, V2&& v)
    {
        return push(c)(boost::forward<V2>(v));
    }

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::priority_queue<V, C> >, V >
    operator+=(std::priority_queue<V, C>& c, V2&& v)
    {
        return push(c)(boost::forward<V2>(v));
    }

#endif
}
}

#endif

/* queue.hpp
gvWwE+n47pqdnFxbkzDS4t1r4jzBKDzF0KFD/+kUPZP+y2Mn/0vauViRs7KTkLC+9cI+JX4dMMV5YZ+hBxPikoInXdSb9Kvj//m54Polr3foW/6AN7d9yuvbO2ff9aB/7/tksOvZ1T93UdwX+75eU3Tvok8bDXjbe/aia6dGFgRl8SfGdr7/c/YAoXl2R6/2fwy6tvjxr55hqlH/xJmT99tUSXzmWsl5VcuFO6bHTComzE5gPXasWf9pes6By9OqlNh78OqYC1FLn/1SsDKwva/vN/czJyQnDFz4XcGjA4ldVl/q10qMnt9qeEgO17ljtQ2975Rv3dQ9K7VmpeW+01eyS6r+9Hxr01F593vMS2tpuGXUz/L/tsOKjQ0ipnm6+datdVRxDwuot4b+NCouc8GJzLnzak6Zmzbx9jfbgFG7gFHL3mGUW9mvbfAs/68YNfR/BAcq24GGxPf/8L716Oy6Ecnd+iV+QCgiMjxDOIaWLYRigE/vXpIvv/1/A6FqkGqOlxX7N+qTGN8zKbBxRJPAJhGtFbmJKNWVBK5hXcLKjelqpKqjRQH/2KKInklD+vTo+d8i2tnjasSyJY2Xj1jXKmpgxJSha8VZXzgZr9c5L49Y8/b0piqHqbSbg/vf98//sljJw7ndqH2V0oeorkVdD7umZ7xqFOG+1NV1p/fMec7dpQfn2BLPauufP1jfpP34OYFLLvTgFnVv
*/