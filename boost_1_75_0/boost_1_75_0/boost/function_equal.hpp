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
xp59pTwTX221piB0vJTvqpXXG8WgnVSPn0lxn+DoVLY+hl7uKGxCDjwGNjH7Owe09Il1zDEg7j2V+TNcmf9OkKa83cMkLUfiwYPpiX88fG9vz2GqZ/Q+Ec8Px99YDk9vUMaLjjo6pd2ovpVL6D8E/dajiOfcaPeb5wWhNf4/nX+E5cxi5ieWq+35AMNmTUMqowXvwH3Yylcw0YA8zcb5iQedARiHIJfdAB+k9a71QX1oQURAWZucoCEQeQv33e91d0CS97424z2RJ1bZu3brMhIyn9z1hnRK6oGSuTOEox5+b5Awi0zofprXDJlwSnU1gB0TT6aCZ9PQUEynxJTKtk/Dn5w089yC3QK349vzPu6KLTv4IrE5HBXtPVIh5bmwrFKaOei+wLswnxdGs2N5/LryFzLfVbJN23Z3RwcrBDDqjFHKwdeSLJrWP4dG0GTrts3g/H2roH2pudGtHJGHoIqc0Bgsx6dDkOLLjzKUAdXiIVpsGfvr81cN9PcFa42KkDLxDm4+ffySFiAV0ebOEEwge8wyrcewwk92ky3e83+XdaoLxYfWVJvOV+4JowrKAsJ/H5phd5gTzDWOQ0SrSRjDaFliLb9M5JBizZ+QPoqC4rRNYHEFdjE9LaPDGgKpbbZ2rLzfi/7a+zN7tHPm3Xvzl77Cr4//mzc9jKW5SpAr87Ax2vR+NVejlNnuUh9Q+OQ/C0venPZ/f/za
*/