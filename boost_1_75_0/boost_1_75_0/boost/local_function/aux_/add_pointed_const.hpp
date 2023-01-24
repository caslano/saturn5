
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_ADD_POINTED_CONST_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_ADD_POINTED_CONST_HPP_

namespace boost { namespace local_function { namespace aux {

// Metafunction to add const to pointed type `T` (i.e. converts
// `T* [const]` to `T const* [const]`). `boost::add_const<>` cannot be used 
// instead because only adds outer const.

template<typename T> struct add_pointed_const { typedef T type; };

template<typename T> struct add_pointed_const<T*> { typedef T const* type; };

template<typename T> struct add_pointed_const<T const*>
    { typedef T const* type; };

template<typename T> struct add_pointed_const<T* const>
    { typedef T const* const type; };

template<typename T> struct add_pointed_const<T const* const>
    { typedef T const* const type; };

} } } // namespace

#endif //#include guard


/* add_pointed_const.hpp
etP143OP9R1y7ZsB5iw8X/iofeAPi7g+ArRQjERY4IY/GwCNEt/HkIrbPvP3ngNhjHD5rVF+s7fGogboYBgFYfWtOP6bk4HAhmAsNhgGgBYabcm061bvNwth89bGjwymmhiuU1oY3sPWeL5rnYy5x9EavWH60DQ/4dU/TsMw4JhDEyA3+DON8A67CG9KTcIYEOgHUKIe2RPRwL0TDaBp1mEk4FCJWBn0g7T+qZOhEiky6IvV+rOebpExIqH7RMKhy49B0wqjipiJfO8vFh3r62/b7+0zL7gKuyPILOb6DDACbkdZAI3ihfrqvuVuq3+UsW+nvLzbgPc4tEMNQo6BB8KVDBhEYX0EGIVsRzn0EePCmY1jZbIy/VN3gjOTwf6r3u8x/Qs6II85aTiLDIMTOehuOlEUWByoQO7j+D6TKIfQpQi/6QEi7mjleSyf4UTtg+74kr73w0kC5MXPoZ+KLz/E2YEJJvcUmZCwM/8aLmHbSODSeVQ4PUciK14TDdrKo9xtpOcr5UB/eEmkWIUmvC9ZtSgqQaql1IUi+Ab45UhVCuLfgulE6JSxdfMi3iG4d0k6LwLr76RGEfy8d1KFggni76xujWC6/ndYKU86dYCI6ps9UTAdkLAcKU9B/B9SgYL4lQj+Dl45UpGCOFIwHU79/xictB+R5L7hkkXCocSIw8APUxsA5+A9Si7f19FPi1LGnuF9Jj+8xwll
*/