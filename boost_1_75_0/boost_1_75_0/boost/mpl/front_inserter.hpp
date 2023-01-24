
#ifndef BOOST_MPL_FRONT_INSERTER_HPP_INCLUDED
#define BOOST_MPL_FRONT_INSERTER_HPP_INCLUDED

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

#include <boost/mpl/push_front.hpp>
#include <boost/mpl/inserter.hpp>

namespace boost { namespace mpl {

template<
      typename Sequence
    >
struct front_inserter
    : inserter< Sequence,push_front<> >
{
};

}}

#endif // BOOST_MPL_FRONT_INSERTER_HPP_INCLUDED

/* front_inserter.hpp
JK1qzOG+/KC2qwPUCm4FXz5qnI0AW8tNx6FdOZCJcJ380Ul+Id/eIB9393MzQ/QFMj0tCkWoLAQeKNA7rl51118HmJQebAixq8EPhcbLx7tD/eN6uic5ErzzYSg3FzynYd7pK+w9T5MJVxdcRjsbljdmNwEHcj+842ElV0dBhj4PhdPvLlWgqDsb0X1sPX6/Vw+JFgN3/Dgid2/shkH4LPjN0wx3AcbLToC9Db+bXqv+1N/t9ZSeGlygRakDl3XKHRbOjaeE2eLQ8klw+FL+paIW75ZWDmdSGbtzJEZvT6D/oe8AqcdZScDcQmgbt4Of98eqXFgciXW4Oi2Bv+GYiSvPzQc52n838+sPozL09nOcr5y3WoO+sUyIg8tY+VTBNBNlgn5898xLTartSwopsUjn+5LTvwAmOMNKMFv1R81BRmX/k8sVBkHi+sG6xbR7Iq24K/gOFOE8IBK8sMs+YNcofbV2MEs24RZ9/rAif/+UCjU/3lIV8mkb0kYUr69m4rxxKnM/znfu5w1OvRK6/QrOM852kpeifc+iGTcmadYXmGft8v7wg5vTks/0rJvmc0Zb2jvwa+wFvqNZ5uM7rai1YTKoSYtkDV71thBf5MbysV/DKEtDf/oEwvgHRR8+44DC2f0Ps5eWAQh/EXH8EgYk86A3I/22UnYqGV8OhshvR2p1Mmj7snb8MV30SxDW1lCnSY8UPLm1AgEI
*/