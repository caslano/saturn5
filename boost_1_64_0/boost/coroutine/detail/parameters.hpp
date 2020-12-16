
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PARAMETERS_H
#define BOOST_COROUTINES_DETAIL_PARAMETERS_H

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/coroutine/detail/flags.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename Data >
struct parameters
{
    Data                *   data;
    bool                    do_unwind;
    void                *   coro;

    parameters() :
        data( 0), do_unwind( false), coro( 0)
    {}

    explicit parameters( void * coro_) :
        data( 0), do_unwind( false), coro( coro_)
    { BOOST_ASSERT( 0 != coro); }

    explicit parameters( Data * data_, void * coro_) :
        data( data_), do_unwind( false), coro( coro_)
    {
        BOOST_ASSERT( 0 != data);
        BOOST_ASSERT( 0 != coro);
    }

    explicit parameters( unwind_t::flag_t) :
        data( 0), do_unwind( true)
    {}
};

template< typename Data >
struct parameters< Data & >
{
    Data                *   data;
    bool                    do_unwind;
    void                *   coro;

    parameters() :
        data( 0), do_unwind( false), coro( 0)
    {}

    explicit parameters( void * coro_) :
        data( 0), do_unwind( false), coro( coro_)
    { BOOST_ASSERT( 0 != coro); }

    explicit parameters( Data * data_, void * coro_) :
        data( data_), do_unwind( false), coro( coro_)
    {
        BOOST_ASSERT( 0 != data);
        BOOST_ASSERT( 0 != coro);
    }

    explicit parameters( unwind_t::flag_t) :
        data( 0), do_unwind( true), coro( 0)
    {}
};

template<>
struct parameters< void >
{
    bool                    do_unwind;
    void                *   coro;

    parameters() :
        do_unwind( false), coro(0)
    {}

    parameters( void * coro_) :
        do_unwind( false), coro( coro_)
    { BOOST_ASSERT( 0 != coro); }

    explicit parameters( unwind_t::flag_t) :
        do_unwind( true), coro( 0)
    {}
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PARAMETERS_H

/* parameters.hpp
xpei/3U0kfYAGAb/M5qD0r+9pYgb8VMpjCV7rypuHKqJm1nb7WnkOBnTbGzjW+QdIr/nd4QqMtCrNfiERPzvHbsUUaDPjcP48TvxV0nYYnjW/Di2BL/aBZ/79UuqmHilKhoMU0VYO01Mupl3Ph9UxSDsS9lmxvyKJvphG5ys21Rkf2MpOCmZNcdXvL8HOcnFDmATv8X2pWQoovAsOChCEzvQt+3reH72LU1UUxVxAGw0q6Yihj9Inhi5fXk4fN/JObJnVTHsR9aK+b/9uibcyO+bqZqouZF1/55cGTw7TKmFzhfC/xbfMh5s2pjTQuw/pIrFL2qiFXb2NlUTw4bh31uBebDZG2droiqy0WyWJu4mT1V8Gh/ZB/udiu3aBy/zmHMjRbzQFVxwCzgL/j18HbZinyImP6CI1vRX/RHyLdDq/6qJzvjJSBdzekYVfxWaOPI+4/tJE50KkPkXVdGhAz6vObJ+A7jqDWw86/TZcr6n0wlZ6qyI239XxIbf4F9r1vZh3kY9AT1hrn3xb3HtuJ/+9v4F/e6CbO5nD5wx32zHRi4Eu3bGl07UxMBictg/0Bay9xJ6teFr2sD/XqaAuxbAa2xu1reM7U70g3GdQr982IKT6OEe9K/ZWEWsnK2K+F9VsXwVOoNMzR2qiA+f4zq4OGeFIpIYRxplcUdsCz7n0hRVTEGvSnphk19RxNYOrNsv+MYmdLoO/vVApvAXM7lnCr5kvF0RY74CS23kexnMNRV9zANLZFH/Aeqkd8VnMpaTHygi4q/4TmSjkHE2iVJEhweR58OqaI4PbY0tvZv6eruLLwUTKpp4ggT+/TuQveX4FNb4BHJ3KX6i2Q5sIbZ8bLIqHrkef/65wlls5giWan0SbM+aX9sXe/044wSrT71UFbWPqWLTfvAG7f9lHFgNHLIAPYvdznpxSOk0/m70crAPfOhyhSLGzQaDliniEPW3Uz6lfEzZRzlIOUD5kqJfb4TsN6M0oVxFaU15cb8mCmlLgx9dX0N2mOfpfOQtDr0BS2TMh44vb0hdJ2MfiM3UbU4bbI+nLXZwsSLS4PVpfFzxe8haGD6auu0pc7sTF4D3t7XEz4Mjex3m/dsRqsjkWiIllbJ6DZj1HXDwd9ilz8BdJ5Gz5fB3Cm0gq7XgX3Y7bEtz5LQP/fclVnhdiC+uYNz013Aic6yDveD+vU1ZP3ibXAgOB090ZNyFtcF69OPm7wLkur2miJ4PgWEbI4uMe2Me8rCPuQwCH9P2473BGmyqODco4r1P0M2v0TfkV9+XiaujCrUm60MMd+9Tirj0ae7/kHjrEUU0pc4uDsh0Ga8K7y7inK2KmEe/x5DhBujjwF7EKbeDO7BtE47jn7N51vWgIh6zq2LWIcYIv6eX4VvWodtTFDEbW7JsriYGbdbETjBr52vwWbdgdxnnz+D98N+4DubdTR/P02/2Yk1cMhOdc2KTesLbZmBQ7GpfxrJnKnLKx6eOLaMefsoFdj+Vq4ke+OsI/FdTMGIVF3P6FHm9mzgMvHHtaUWMYr5JhxQReasquoEJVnRFJ8PZc+rIL+v+bS8wxx2MdakmFqxGdneB5zvih7B7mZOwNZM0sT0KeS3iXQX5yPJrirgEbB+zH7wILv4zbW8vBVf/gu87pNsT/Mkr1O+Fb1sNvhrAXN/QxNcPgMsXgK/bg8GWYufXg2ncYDxs+1T4nch9k+HVzyeQdXxq/ALiC+zmsOHYGGS2Oraixlj09U3sjAt/xnwOTCVGAF9MWIV/bq+JGv000XWsKmZkaKI5vif1M+YG5r2uJvqeS7xRQxHfK+DZBqrIz1DFda8g08RJlxEbNKvKmrEOH1IakePv+yyx8Qw=
*/