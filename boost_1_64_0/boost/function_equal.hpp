//  Copyright Douglas Gregor 2004.
//  Copyright 2005 Peter Dimov

//  Use, modification and distribution is subject to
//  the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org
#ifndef BOOST_FUNCTION_EQUAL_HPP
#define BOOST_FUNCTION_EQUAL_HPP

namespace boost {

template<typename F, typename G>
  bool function_equal_impl(const F& f, const G& g, long)
  { return f == g; }

// function_equal_impl needs to be unqualified to pick
// user overloads on two-phase compilers

template<typename F, typename G>
  bool function_equal(const F& f, const G& g)
  { return function_equal_impl(f, g, 0); }

} // end namespace boost

#endif // BOOST_FUNCTION_EQUAL_HPP

/* function_equal.hpp
+bZ544efY67dqfajzdMCp8ZuRclNpIpvaTPQ4+rpAFJDcYXMWE1pA1tgW+SQX8da9geqQKt9Y8RLl/2GMGQ61F1AvdijxrpgN63nOF01EA87/h60XPDU4AMKY/OvhggFOW3b/LKQuEnSQyrT/U70BEdUY/SeOlkZZiljfELQWOY3gKw7Mh2C+p2W/GtBhvpINFv5U3YkO+LH5V3WseQyP31eeO8PHgpTxT2VJSqzAwcK0xQiOrjahLI5+g83mxrrjcUOTwZHUopF/kO1VIcPHopAV7Saow4KbFA7WrfiolOhLxAuGOzWouvg3eWMViUoVhrnZyrft6lG1VzY98DiPKEteSvdu1+Zb9v+zvyAB4vkAEbcXSItHnyE3c6tF+V4Nu/2Y/OpDdpXlMaHAAJjFUB9ob102Z0pxngfPBUIa0dYyCV3n+KKk/NptcIqE8ziCWX4dNSLeq40MjE/5qStP3M43IVI5PBibaUWlfCKS/STw0gsg9+uOsGTol4zxyAGr9q0tKdAKNkTeeDJ9jM4g+1su6d3HcEUuRkU0NkbCfP77VlTVwqyaDwbjg==
*/