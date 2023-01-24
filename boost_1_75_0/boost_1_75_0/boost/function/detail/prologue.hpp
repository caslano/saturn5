// Boost.Function library

//  Copyright Douglas Gregor 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_FUNCTION_PROLOGUE_HPP
#define BOOST_FUNCTION_PROLOGUE_HPP
#  include <cassert>
#  include <algorithm>
#  include <boost/config/no_tr1/functional.hpp> // unary_function, binary_function
#  include <boost/throw_exception.hpp>
#  include <boost/config.hpp>
#  include <boost/function/function_base.hpp>
#  include <boost/mem_fn.hpp>
#  include <boost/type_traits/is_integral.hpp>
#  include <boost/preprocessor/enum.hpp>
#  include <boost/preprocessor/enum_params.hpp>
#  include <boost/preprocessor/cat.hpp>
#  include <boost/preprocessor/repeat.hpp>
#  include <boost/preprocessor/inc.hpp>
#  include <boost/type_traits/is_void.hpp>
#endif // BOOST_FUNCTION_PROLOGUE_HPP

/* prologue.hpp
iu3JbbhssbS3527Dk1vnOdiLD+DebYgTaOJ8dkHbTJz/xzkfrCU0bOisoA/81OMWMljeUWvFsJCPIJHeJOfx52hOtO88Ts/BQJzZcyB/3szLr2blm4kPuaucpOIe/JPY41TVzJ/hxy3efIouBBCRdfPtWggg1N8ddUhT8pG8T0jITp8zISFH3XjW7XzjxWznG49xScsBFeXFr4Pes4kSAbg/xvgf9gqKkEJRa2RbJLms10PsGHdfJug+0g46YZB/1h9v1207UIxn/fF2wdsFxXgV90E2BlBxyMPZgWdfTUp5ZIs3NUawfhgFcwRDrBVb5nbS0v/JGKiCbM5lMCZpJY/nsxLFRhGnpoqiE4Wj6Re5ibIjxRxNQXBYKXpImiyzYMYLSalyZfft3U2FfSBfKfuD8fu3dQc+rrDrEjbG0CD2zmFOF+F56AlfVyIzN5c/QzeCTtBjuxMfUY117EzdesaC4PsKgcDVKmhWx0OsxWVIZ0or7eaXq/SxWcyidSMWMzEuY6tVn2PzOvxJXuUOubbFAr+2yn8/H2PKAGtgwA7kxrgmkT0objyP2DqSGKmbkObwkEMeEXLoB35oKSY4Kgg9zCXz+a9K/FWMyEKGz/IL3xOy7KDPmfTMYDshIa0wXD7TnolXofIGhNwE0oGhmgtkTEypPA3C8VWtQDbQE+WphXWYvJ3PtgfO1rGFMXudFVtcdXdIaB8qd7BF
*/