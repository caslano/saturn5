
#ifndef BOOST_MPL_INSERTER_HPP_INCLUDED
#define BOOST_MPL_INSERTER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

namespace boost { namespace mpl {

template<
      typename Sequence
    , typename Operation
    >
struct inserter
{
    typedef Sequence    state;
    typedef Operation   operation;
};

}}

#endif // BOOST_MPL_INSERTER_HPP_INCLUDED

/* inserter.hpp
3uVnIbfJZiJfTe3eHOz285/c5iPDz0KXn0XcBksqpNk9h7JFykw/i1n8/bPI5SfKbXBoCK/ZmsoHX3anZwm3OW1c96jLz1Juk8lEvi7eHql0+1nGbbYb6Vnq8tPAbV5nohfs6JcfdXb7+Tdj5wJeRXH28YkitCpKLhAgBJIQUPFScuESvGTP2bPnfjMEiuhjmssJxISTfLlAoAqKFAER0VI+QD6LSJEiKlKgCIioiLZarNUWrVe8I1arUr+C5fM=
*/