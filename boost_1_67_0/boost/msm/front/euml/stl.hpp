// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_STL_H
#define BOOST_MSM_FRONT_EUML_STL_H

#include <boost/msm/front/euml/container.hpp>
#include <boost/msm/front/euml/algorithm.hpp>

#endif //BOOST_MSM_FRONT_EUML_STL_H

/* stl.hpp
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
*/