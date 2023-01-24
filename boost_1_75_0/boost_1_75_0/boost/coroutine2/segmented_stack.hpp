
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_SEGMENTED_H
#define BOOST_COROUTINES2_SEGMENTED_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/segmented_stack.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if ! defined(BOOST_WINDOWS)
using segmented_stack = boost::context::segmented_stack;
using default_stack = boost::context::default_stack;
# endif
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_SEGMENTED_H

/* segmented_stack.hpp
VAoiM769+WRr1DFrPPBFuN9mSpNkTQsLsZX4fiEsK7CZhzOl0dOnY+6yZfWSWXyhA2yYOVYP4P8BieL32wwOax+OijujgdCbi0kW7wW7BGlJOIhP33wXKs1hYZH3SAkwkNXWJvxDheWCsOHYiSmlnmYhQzetfsvj5jpvK/sBN3siFTmnkuGP6/rzNksxTfttdweFBbUp856xbhQSI9afI+MT24Lg5yEdjRF2TmTCQVoHYWEi25++QisbwYtf9NPxim1r3NdjkyM2B8xq5xPFPYQAdOmVV9AA308EArpRWTExOkRc70WmIFcedk7tGx+oK9joYu8/S+SvuXz8sT5WoHEsPeog+tT+uVrIHFY4yZYlIulJAO7AnlpSTGfzxqZghuFqVFVbSp2EHRutVsv5oAkoLWRkZ4ZgH1oSOvFk05XP24cOlnlVcFE7/n5lX+FuUBSwZMioFHOmVzRevl2m+aHb++HuxelMxdeTyvLlHsHJDwT3OZzmJBe+mH50aFuWNl1TAO63c/7J88n8CqejGsmLt3EcC9J6AjumgQ6+tN4BhX7PjoWrulBQuWbwStni3QjgTwECPReYJwmXM2Nl/cca+mb35gPu1eEjY01D2zGV06JbwWCQp2PpvGBoo78Q9pyRobo2I6zrY+xOikHJ0qWEPWr8u/CoBzac+iJvIeMblbsX4Jhfn053k6xUj+eYMhzjVc9vOidpXF7O
*/