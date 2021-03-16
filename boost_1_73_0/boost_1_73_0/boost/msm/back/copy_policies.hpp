// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_COPY_POLICIES_H
#define BOOST_MSM_BACK_COPY_POLICIES_H

#include <boost/noncopyable.hpp>

namespace boost { namespace msm { namespace back
{
    // deactivates copy
    struct NoCopy : ::boost::noncopyable
    {
    };
    
    // allows deep copy
    struct DeepCopy
    {
    };
} } }//boost::msm::back


#endif //BOOST_MSM_BACK_COPY_POLICIES_H

/* copy_policies.hpp
3lnYXwXOPbe46+G7i88C571b3PXO4R8d/uvuemehX70HnEfY3FhXQ+888H4DnOfT7noJ4H0IHD9bgVxSQy8GvApwnjvmrve3wPslcP70uHncWkPvAvACkDw62Tu3S2rojUKFHQHOX82ax2019I4AzwCr5wrmca34fo7xAeefiuZxSw09bKhUCfaKTW9OXpdg/f9hhUjbUEvPkHhnHTe8gX438O5j3EUWz0HvjEe9Z4H3oge9X3rU+xh4C06Yx24=
*/