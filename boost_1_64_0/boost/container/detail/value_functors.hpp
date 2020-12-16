#ifndef BOOST_CONTAINER_DETAIL_VALUE_FUNCTORS_HPP
#define BOOST_CONTAINER_DETAIL_VALUE_FUNCTORS_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//Functors for member algorithm defaults
template<class ValueType>
struct value_less
{
   bool operator()(const ValueType &a, const ValueType &b) const
      {  return a < b;  }
};

template<class ValueType>
struct value_equal
{
   bool operator()(const ValueType &a, const ValueType &b) const
      {  return a == b;  }
};

#endif   //BOOST_CONTAINER_DETAIL_VALUE_FUNCTORS_HPP

/* value_functors.hpp
sFgym5k594YlkvmZBVb6q2AZIs5zds+XsFzRi3nHC6yIzGl8JSLngtat6bAqMh8z8+wjrJHMC5PrSLFOZXl2s15uItu7+I2ZsJj7qRdmi9a0rIEFyHjchvfnZ8BCZFiei8h+mtUZhKWToZecqF5WDcgkwz45171qwOPjG7+BFbK4m8nMbyRgxWQ2s33tJ6XCKlncLWRmPcCqTRyzp//6l7WwRjKLx2188kpYG5mXmXmfAKxL5Fz4TtbxMFdZtO18ePvlMB8Z75Mvl4BicWS8F7PeYSERZ7YHWJJiKUrOdGEti7L3wCJlzss6W7E8xQoUK1KsRLEyxSoUq1KsRrE6xRoUa1KsRbE2xToU61KsR7E+xVwPOJtHMUsxn2IBMuyzbiWbf2rWy7BEE8fMvIcclkwWYPbUMt/bsAiZzeymB468ElZAZjEzzxTCSnk9sd2WK1YpcppjHKxOxJlzIliDsLjdL0yBNTHLk3OJ1VtMtuTx51+FdZL5mSXET8+FxWyk5cLs11sKfoP5yXhOd/pDu2FBsgCzB/pL/w5L43Fivxsh88DEMstWLI/nFMuzWIzhzazaFbBKkdN8WxxWLcbw7vlLxsFaWL3bRL1OxfoU8z5I+12Y2Cf7yZzigmQ2M3PeA0thcUtEXAaZh9nnrTcuhYXJbGYzbz96MyxfWGON/3VYqag3ZeU7f8KqhJnrfli9yPnC7iOOgbWS+ZhtPm/FXFiPyHnVyWlPwWLKo+PM+5dgAcUSybx87FfseQY2iYz3eVHg1CxYWNjvez5Og+WT8T5v+vyI+bASYea7NLBKYXOOKQrC6kS9U8/cEQtrEXbzC7GzYV0i577lP18D6xe2ZVnnpTDroWi7+dKH98BiybwwMXcTyJyWdarI6b/q2WmwMJnN5+fPz2yD5Yuctw/qfwVWJnI+lRzphFULM+8+hTWQYXvIF/uXJhPHzDwnBWsn8zHz/rzm/9Yn4sw7ZWDeh2l8zMy1KCyWzAMT+/J4Mi+zOft2hGCJZLHMTl3xzJuwMBnv5a8PxX4KyyPDGG4nu/WNw3bDSlkvS+UxjsyCieVSY3LCxHJp5nFiuXSQ2TCxXPp4L/I8ZBMtF2bzdjacBbPI4pj99P65/bBEMgsmlksqGcZwh1guWWTos4Asfm7dnv1254BCZsvcdw4wz+rBysm8zMy2AqsWcXNvqN0JaySLZXZU7B2zYd1kFjMzr2GuigPLbDmZWWYwD5kXJnrxKXEBMovZjm3BYliCEpdIZjMbXl90CyyNxa2IilszIIPZSveaKAuTeZmZMcBylbh8NoZVZDsfGz0GVkJmM+vx3L8JVkXmY3ZrzBVJsEaRc/G3dzbC2oQlrfrr/61b5Fxz/iXDYZ7N0fbnfb1nwGKF3X5xXiMsiYzXG/Fo3RhYmrA3Tv5zFixChmV2J5nZ3mHZZDazKbfsbYEVCatY3f5/qyCzmJlnsmG1ZAFmz4897zRYm7B1v/VcCesXtnrYuH/BAo84WzKZ0/gmkWF5FpFte2nYdliEzM9s4uePfQ4rIrOZPfbo+zthFWQWM9/gozfCakW9rpyh7bAWsgCzLyrKroT1ipxbrZMPzJct0Tk/qO7+ARZLxvv86ruXr4MlCnuu8o0TYGlkvN77azasg0WEjR6ftHK/FQ/IZ73c5S4ecNWwKy+AlQn7rLS5D1ZLhmW9miz+ptJ2WKuwSf5n/gnrNTmZ3XHr6PNgViX1yWzr+D2XwGLJeM6PTp5yPyyZzGYWHH/pP2AZIqd5fwEsW+T84LKqVbASkfOVp3ojsCqlz3qR8/ktpRasXZh5Fw2sX9TzneYJw+xHo+vVnvBpABZHxnMet2X5/bAUMp7zmGOunwA=
*/