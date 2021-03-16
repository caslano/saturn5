
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_DATA_H
#define BOOST_COROUTINES_DETAIL_DATA_H

#include <boost/config.hpp>

#include <boost/coroutine/detail/coroutine_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

struct data_t
{
    coroutine_context   *   from;
    void                *   data;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_DATA_H

/* data.hpp
A+6c22g+rn6k/afdlu4nQ/0WA/fq7TQf17/k/P6bO9L9yPlvIHA976T5uPr9DJICzKQcF7f+I+03D5gVd9F80nh+/y4ObXHz9wvgjt+d7NcFknFPut97kGzgzlxL83HHS9pvytp0vw8hXQacdW+yHzne6+9N9yPX89uBW7Qu3W/LunS/I5BeA+75+5L9yA+avr4v3W8PpB+Be/N+mo/zmwWpYD2c19bTfNx4IY9GWbGehM7TfNx43gLp0gc5tMU=
*/