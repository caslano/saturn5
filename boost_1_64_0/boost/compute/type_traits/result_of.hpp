//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_RESULT_OF_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_RESULT_OF_HPP

#include <boost/utility/result_of.hpp>

namespace boost {
namespace compute {

/// Returns the result of \c Function when called with \c Args.
///
/// For example,
/// \code
/// // int + int = int
/// result_of<plus(int, int)>::type == int
/// \endcode
template<class Signature>
struct result_of
{
    // the default implementation uses the TR1-style result_of protocol. note
    // that we explicitly do *not* use the C++11 decltype operator as we want
    // the result type as it would be on an OpenCL device, not the actual C++
    // type resulting from "invoking" the function on the host.
    typedef typename ::boost::tr1_result_of<Signature>::type type;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_RESULT_OF_HPP

/* result_of.hpp
XLk61v/Qa4IcZG5YX13Nx1SWcFs3wlP9346p0tlo5NhszeZHSF+3BtgdgD1/rvRJ3TxpO6xaQPml0DTStYW3xz6GaSnvY1dQbMVTjidJto/9aunZgO7C70EWro5kaQwP5XfuGkjWRRLl++O/h+VpVR64B9dEsng06DqKHfzotZC8iwLbXLmAziz48LUBM4rDOXddkKE4nC9eDz2PUzhZvNMNQZbF6PSyEyBLhQzv8x1vlJ6n2kw7FrI9xcN8+ZWpXpN8/vzj81C9t0TWWgtm+f/ajoa5v/n2urk8WKfZnaY3He2XdllAXj58lVLW+SDgfvKqSR6b2uSwLx7gxom0JOtMdgrKecDLWN41spxvronl5TzhXa9dysfzhOE6GJMSn8vve10sj3+5sL49q6s7rkDZrexvXwFlB2doxrLNz6JhlElNnSI+1k/sJp9ZnB60lXg7xVqIuRLXc6iNoVSY/6ee33GT+Wkt63nn+JDN4b2F9Y8kgzZSlvUnr4Llu3EDycZqt0cYvgVvuypg0Ptw36ul5zuba10Rp29NXI/LzzG5OpKvb/dyN5wV98S8nDSxrXTWN//1XFWakh3mqp6Z1hi+lsZj/URtKp9hzil/Pp12gvHjPZEstaJsjqmTxX3yuTgb4CXf+/xoVz52wmnTMMrrLlbrufjZ2a68szMLtof4xrjfddCdYy5dPcOk2gTQDBOuPQczPUEAMLe8boaJHju3dffB1vXGGDiMAOx14xjAJcC8dJ+4SYbZR/agrd7yZgkzzJSupv4QrO9+tJP957n3oX01N0/4on6ytv0JJEf1B227uUWHOdzaenqqjlls1q3g+RDKBpyf3RpkqShmPvO26XkqxDQm6NoZ9Im/+C/KriU2r6MK24mTOM+6TYFQCoQSSgoBHOdRBwqd+34/aAIEKDiOH9jgxMa/HVKJRSSQKIhFFl1EoosIVQIJFlnw6AKJLEACiUUWgLoAEQESQWIREIggsWDO/HO/f87c+5ekaRJnvu/M48zjzuPMmbdKjO6tGw0Dl+mNPD/ztjZP+9lAXL/r4OBCvdm3397mNRfq4fvkYAcH32fd/9/R5uhL9yj7yhOac2l1eb6fEdTT2DsNDIU2ZDlOhQU2dsjAdOZxj55hlGkDe5eB6cxiPsfGnVRUlV/VRXbf/lLkiYo8B+RzywujwcfrmdoNZnqKZq7xfrGNcHkm2JuVr6/PkAf+mV7fM/WccgJttOnXxonbj8OlJlQsXzb7z559A/y5SoH4pk0KOmOca88HmvnHDwmfXzLQpQarf9THLg9AyN3+ucJ6sx3Y5F+2SGzBTBG2E1f/3scuT504cfTUkDkRq4tC+GXs5mHmPnhdqDnRcB1ovK0DYF06AMZ1wLFuHRA2XAfNvujBI3Lc/K3e0x7Aq/O9Pv4Oid9a7J+nyFFldn3ewBsbVOpD/fZHK0WaQ6vPPO64brVxTKkQx+PbbI4aDoEf2G7iWB/gO/LPNq6ci60tLKzLQoF3dccQHpHwXSLfq128GVISDeUD3w7dPOLAxuj5nZ0c2arWdfcz7HnbXHnuPkX6gi5u7rY5NKjx+xBtfIb8iSFPZ/a2OD2pBz1PnaGDfuhifl+b26WL4w918RhHNrYWh7xhsPZy42HGofZGG0KTpp4O7W9xmnk+OH9rc+jO67zJ+fUbWhx8b3G38o1tDjUapSWD99KbOnmte+grBzp5Tf7Bm35zN4+UZfLEY108bL6A9/xbOnmNjQN4G4938+x7a9fe2snDWgjt522dPKyJcH/27d08ZdVDTPNe0cFuLi0m2d7bOzp5zaITvF890c27JHWz+MJgjvjnd74eb2ZdrkHkj4MyHXrX6/EpB4M=
*/