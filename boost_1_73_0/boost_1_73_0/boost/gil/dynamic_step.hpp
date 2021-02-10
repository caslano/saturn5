//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_DYNAMIC_STEP_HPP
#define BOOST_GIL_DYNAMIC_STEP_HPP

#include <boost/gil/concepts/dynamic_step.hpp>

namespace boost { namespace gil {

/// Base template for types that model HasDynamicXStepTypeConcept.
template <typename IteratorOrLocatorOrView>
struct dynamic_x_step_type;

/// Base template for types that model HasDynamicYStepTypeConcept.
template <typename LocatorOrView>
struct dynamic_y_step_type;

/// Base template for types that model both, HasDynamicXStepTypeConcept and HasDynamicYStepTypeConcept.
///
/// \todo TODO: Is Locator allowed or practical to occur?
template <typename View>
struct dynamic_xy_step_type;

}}  // namespace boost::gil

#endif

/* dynamic_step.hpp
9lw4UjGdu3nWbNhKe00Q2gsKdz8jjIdTKdwg7nrPOYiHnZbZ06/aNujgQ4sSjpB9Pq8bPrYadw+HbNw312J6KPF6rbWQjiTQRrvhRaIV+jY8JfK1dDPvdI+7apsdg/bh6lMqFewNSUATC3gbUKOtQkwyeVNNEyCybD844cf7j1HKYuIM2qCAFh060KQjbtaDhW1qzmfPnk9L/fFIX6YAGN/GzHph+umCAm5pBz2lw0Li7/xy6NxD9DyFobJdzEsV8N5SH0/MRd5TtdM7NJ0wds28HHT6aXhiW0jqj9VOFHUjVXL91G/XkdkulA7s7sh69hBjyDnU5i5IUkoTwXFnMkm2Ksl8TDI7nZsOdgqK2XwzVvv+UnYxaAVbx6PZshAvlACJz4KiWmQ6qoChROmdD7ryEwNUniX+qckoTY4bm0CUjEAN7oOW7fCN+JnZka99M/2HqSmxD2qfvwkBekJ8D0d12EEnmuyuJQelE2NcJGz9qYNEUCjyKYfY4iSEuzYPq9j3UkoJlriZhGQpJgXOUM6mE5rhShMTRiuIwHbJwWSJg1+gEfQUn316pL4dCavVh7gJfNpfwNRvYhqvHflNTEhO12EZUHLj0KDS9vnWsY0zA7WT7CZd5BSfjGlWQ6e2OZgZCYrS/USd3mWf
*/