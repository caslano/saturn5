
#ifndef BOOST_MPL_AND_HPP_INCLUDED
#define BOOST_MPL_AND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/aux_/nested_type_wknd.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>

// agurt, 19/may/04: workaround a conflict with <iso646.h> header's 
// 'or' and 'and' macros, see http://tinyurl.com/3et69; 'defined(and)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'and' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(and) 
#   pragma push_macro("and")
#   undef and
#   define and(x)
#endif
#endif
#endif

#   define BOOST_MPL_PREPROCESSED_HEADER and.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(and) 
#   pragma pop_macro("and")
#endif
#endif
#endif

#else

#   define AUX778076_OP_NAME and_
#   define AUX778076_OP_VALUE1 false
#   define AUX778076_OP_VALUE2 true
#   include <boost/mpl/aux_/logical_op.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AND_HPP_INCLUDED

/* and.hpp
PZAGziSbwioWaw8DZedct0xd4GBy9hHnQIWkuUVxlvxWiIa+I5yFk2ssTsgjS0ea80xO0KHo9fI0u14nTDs8vb7botdfnePQK0IpNThDGxX09dFzDk+vRazXCknzBcVZ6RB6vU84GyULnXN4en23RRunnZNKGx92K21I29h/9uFpg1uZSrPtbMVZGjpHYAX/NxeYyx7pnRe9RXukt9OPx5OFGfz+x/to/a0P4y7sPibSuPI4BvpdRkAjAnbuUs8Jfa5IZ2usxxsJNugTUpoKiOuTRyZW4W5adulCxikeQzqP8SrJJp2HwVTTeUxQPGrNjHrBo19lVAUMGhmV55iZUS94dqmMqoBmM6NeCKk3MwoeuJjRzCtS4SpVlV0VVoAwlWMwww5+VWAwJ1LZe5CoYCwnEs3jsFBXDl3Cithmip0+wrH1FLuUKVxmmUNry1WV54MKNK0i/kwFO1eBaw4WrI07Y3IhLi2Bd+6KRBfAhr1l5+4IBnFa0TJgGQC1DChEaHJzdVf1P2hhu3lJ4WWLtePfG+dD14O8auk5aAUMCmBoFgPKAKiwAWICeBaA8wGYaQN0CeB7AMQOMKD/gBXQLIAoALUAbLQB6gWwGoC5ACywAlBBglkIzFCSMfGkFXO+gckHph6YBhumwMC4gCkEZqkN4zMwfRcyxgVMBjCNdq3+GIC10Mk61gkqyq7YrwFTAMz0g2BiV+xNAPSi1H0HFBO7bpcAUwVMzQEwsev2XQDMAmCOg4lS77HAaCjOoCqOQ7173sOYTcBsSRp8nBp+GrCFgC1SrBwa/gYwif2MSe53ZKlPMJ8HpgvK2QHlJOwavhyAPADyBWBX7ywAulHwngMA2NV7EgBlAFQIwK7bVy9AwwZgpgDsuv0VALEkGnYSALtiWwCoBWCjAjgUWwvMXGAWKIxDq6uBGYLG4vutgjoF8GEA2qGNTtGGXZ/nALAGgBIAGuz6nABAFwq7A+1kwagW+8eZaNXArDsAJnaVdgJQAMB0xcTRYuuB6U2iVSfBxK7VWwGoAqAmKUycLfYTwMwCZo5i4lDshcBoUNrgfgefJsHkANMKtbSJWuyK/ccMBoQBWH1QmDjb6jPA+IHJBZO4XbcPA7AGaik5AIBdsTUA5AGQLwC7YlcB0J1EY04CYNfqpQCUAVAhALtWzwbgfABmCsCu0iwAYlBX/34rYKMA/vxuBjSjmC1STLsytwKwAoAiAdiVeR8AXgB8ArBrsgKA9gNoxtDDFrsmPwOAH4BcNLDlo1rpRcB0JdGSk2BiV+Y7AFgLwLqkMHG20n3vQksGZrowsevzNwD0Ql19++1McGO8wB4FrBFFbjoIPnatfhmAZQAsPyh8nK30OmCygPEIE7tiFwHQCrW0KbU4WmkBMGFgVkO3Q3bdjgegPQnlJwGwK/ZP56MZA1AiALtifwZAHgD5ArBrtQGAbiitZ78FgEWQYMqAqUdhGw4KxqnV5cAUArNUMHatzgbABUCGAOwqPQWAZmijRbRhV+ne89CYASgSgF2fvQB4AfABsMmuzx8BEE5C4Whmy0a11buB8QOTmwQTu0pvAKALGtux384EV/jr4z9gm1DeLQeFj1OxZwGzEJhFB8EqVYt1AZZAuZJSLrtuf/9ONGkAmg4IH2eL/TEwy4BZLkzs6r0HgCwAPIqJo8XeBExrEq0aytHsGg4B4AXAJwC7emcC0L4fTXq/BVCZZ5TXC0wt1LIRqtNGqXfwXMzRwCxQGId6u4AZQoniKLI2SrcNwNQD0yAYu27LASgEYKkA7Iq9CgAXABkCsCt2HgDNSTRs0Yldq3kArACgCIBau1ZHpkPtUFobmlyhUTXYyujtH7Aq6KTmoPA=
*/