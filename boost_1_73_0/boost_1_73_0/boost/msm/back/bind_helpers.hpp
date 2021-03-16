// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_BIND_HELPERS_H
#define BOOST_MSM_BACK_BIND_HELPERS_H

#include <functional>

namespace boost { namespace msm { namespace back
{
    // helper to replace std::plus as the lack of implicit conversion makes it not usable in one of our bind
    template<class _Ty,class _Tz>
    struct plus2
    {
        typedef _Ty first_argument_type;
        typedef _Tz second_argument_type;
        typedef _Ty result_type;

        // functor for operator+
        _Ty operator()( _Ty _Left, _Tz _Right) const
        {
            // apply operator+ to operands
            return (_Left + _Right);
        }
    };
    // helper to dereference a pointer to a function pointer
    template <class T>
    struct deref 
    {
        typedef T& result_type;
        T& operator()(T*  f) const
        {
            return *f;
        }
    };
} } }//boost::msm::back
#endif //BOOST_MSM_BACK_BIND_HELPERS_H

/* bind_helpers.hpp
ltgRe/39N+w/Bd4PA+YxLW8L1IuD3vvA6dfM40U19F6G/QBwto246+G7SweA8+2Ri+s9DpzToxfXexz+fD7qrvca7GvGCPl0zF3vAOzrg4QUgu56WH+ngXP7fnc9LOZDwPmQ8RbW0MPyLh6HOMfd9fDOyuIQITMhd73/gP0UcDJhdz08/Ufw5xXGq1XeD2H/FDjvRNz18D58c5RIm5PeY7CvA96Po+56+M75J8DZHjOPa5X357BfD5zlB9z1lsM=
*/