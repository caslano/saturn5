//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_GENERATE_N_HPP
#define BOOST_COMPUTE_ALGORITHM_GENERATE_N_HPP

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/generate.hpp>

namespace boost {
namespace compute {

/// Stores the result of \p generator for each element in the range
/// [\p first, \p first + \p count).
///
/// Space complexity: \Omega(1)
template<class OutputIterator, class Size, class Generator>
inline void generate_n(OutputIterator first,
                       Size count,
                       Generator generator,
                       command_queue &queue = system::default_queue())
{
    ::boost::compute::generate(first, first + count, generator, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_GENERATE_N_HPP

/* generate_n.hpp
W+l1sxXB+pSlPr+7Yny62DZgAnWwnYZHPcT461tLxsSlGB1r6Fdz6FZz6FU7Tr+MeDnSSsKkYWZjNmAOYE5gog+iaw0zGlOI2YI5hDmNSXgl0krBzMaswezFHMacxMS9Gml1wmRglmF2Y45jol8r12NR/lf+V/5X/lf+V/5X/lf+92/b/69Li38O/X+ePfxF5LaLrtUq0r3P7zCtlW/i8AwvkMlbRG4oskK/1c0iB0S2IOupHfJaCd9b7GnYrxf7SncVwiPPN+tyBpqwPc0Z+wvEfofrIKuRzncNUHeXNfB+ORfRVY8vB9ut+SKDT5a0PMupxxXMnJ5lzp2cK2mscOtaSL1Gd7/zQKlKex2k+l8o9suwzxH7Wrcn/JEYsw5N8jIE/yniH+V+nzxe4erov0ZS03IRtndMobEX812iEqcTR/idETx+5sT0bLJhn0W+X8p41GpGCXV9pOT59hryBa1gtt8ekC81DyqLdayZiYO54n+Xn3/2tBy9Vjx8Tq51HrlfY8WLm6+O91HH0a5LXVdZJi7ln5adGWQNTW4m7rpfDZvEX8v69dGm/JslHwWccZ3EXa4icY96AvvWAOl9r/mAS9pFqPs9BJky0cz5l3ExXp7G3Kq/l2IgV0A+gFmBuV39GsHGmDsw8THnPjvTs4fl1AMBZ/6qLG2oS9u7nI+JXdzIu57Xnyx20y4lLvdOz2SVtmfO6z8iYbV9Oc71Ne0jYP+M3IuA8/7lPsj+yg1Sb8jLa+r6Oe3bByrpejQ3MiP4NwKFE+bYVrtva7eWe/R2rPTrDpl2v9awLUy/rrhN9Be4gvRrDdvU3N8wCfu62l3WS9tlf/1Z+7ElcU66tB9rmgnm7FT0LYwrGKf92Pg3MP34O7F/7Arox/79VeO4pG0jWwraP6tpvz8q+fk0ZJ+MEf+jruB9Eor/71wBfdKsQXtW/GPNGeeHxf6N2k2dOfeNa9wUCVupxFnmtJugfW4k6Y+RODNd/elb0ZazT2kfMv0tXdk8xvQlsa8Ulr5Pvbbd0aekv9DWaMPa1qSvOPtUYYg+tcScNyvtQNyKnH1K0kuyz8qWPvK0lFuuK/Ya243d7yzMsq8DCb6uI9T6hFDrN8q+bqGs6zSCrysIve7iOVnX8eSeuzYkRL2W9cL1h+7p9ca8FaHWY4RaFxFqHUiodRf/+nU+wdd1lH09T/B1Oz/f2Zk/13oeOUvNN9/ReV4EP85XfUqWyombwAx4CRwHJ6ncZRrMgnNV3rJO5S1bVb6yE05V+X+OyvlzVZ5+NfwOToeNudYM2ALOhJ3hLDgAXgez4EI4Da6G8+FaeAtcB3fC9XA3vAbug3Pgc/BX8E24GL4Nl8AT8NfwE3gL/B4uh1Fu6gPGwNtgO7gCpsLb4XB4B0yD98B0uBFeBzfBBXAzXAq3wCK4Hd4LH4RbYTHcDnfAHXAXfBo+Ap+Bj/rkN+b5xZik96WxnNlon/3TAiao3LopbA+bwy6whcqhW6ocuhWcDFvDa2EbuAC2hevheXAjTILFsD08BDvAN2Fn+AHsAs/AC6CLvHTV+3eh3r+LYRfYA06AveA82AcugH3hetgP3g0HwL1wIDwKB8E/wsHwGBwKP4PD4LdwOPwbHAGXhFlnk0ep7ErlUSFlUf8+OdR/kgzq9PvhP0oOVRoZ1C8tfzqb7Cn69FnlT+WypzLKnpYhC9pWLg8q/yv/K/8r/yv/K/8r/yv/K/8r/yv/K/8r//s//gvHTPmXy/9nFkzs6pH+/3TZ/y0xlpEP5qv+/u3KbXB4DdK+R+SDI9P6d/XoaJng2x8cXlIXiIataORxb4l9sztQP3IL2S+s4bliLSvKGozrer5aVnd1szY=
*/