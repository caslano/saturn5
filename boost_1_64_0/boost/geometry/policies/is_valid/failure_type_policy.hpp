// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_POLICIES_IS_VALID_FAILURE_TYPE_POLICY_HPP
#define BOOST_GEOMETRY_POLICIES_IS_VALID_FAILURE_TYPE_POLICY_HPP

#include <boost/geometry/algorithms/validity_failure_type.hpp>


namespace boost { namespace geometry
{


// policy that simply keeps (and can return) the failure type
template <bool AllowDuplicates = true, bool AllowSpikes = true>
class failure_type_policy
{
private:
    static inline
    validity_failure_type transform_failure_type(validity_failure_type failure)
    {
        if (AllowDuplicates && failure == failure_duplicate_points)
        {
            return no_failure;
        }
        return failure;
    }

    static inline
    validity_failure_type transform_failure_type(validity_failure_type failure,
                                                 bool is_linear)
    {
        if (is_linear && AllowSpikes && failure == failure_spikes)
        {
            return no_failure;
        }
        return transform_failure_type(failure);
    }

public:
    failure_type_policy()
        : m_failure(no_failure)
    {}

    template <validity_failure_type Failure>
    inline bool apply()
    {
        m_failure = transform_failure_type(Failure);
        return m_failure == no_failure;
    }

    template <validity_failure_type Failure, typename Data>
    inline bool apply(Data const&)
    {
        return apply<Failure>();
    }

    template <validity_failure_type Failure, typename Data1, typename Data2>
    inline bool apply(Data1 const& data1, Data2 const&)
    {
        m_failure = transform_failure_type(Failure, data1);
        return m_failure == no_failure;
    }

    validity_failure_type failure() const
    {
        return m_failure;
    }

private:
    validity_failure_type m_failure;
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_POLICIES_IS_VALID_FAILURE_TYPE_POLICY_HPP

/* failure_type_policy.hpp
dZa3sVyYOB0nZxZkXKCTS8neINh7T7x9o/b7BmzhSAdPOKM3iY0BVZWCO7MmxhMeSVWBuZ5dfAHDJxWzci/BEFRPvlBqLBCjRYrKb+E6YbVRR8e9wh4nsvzm/fexvTME5Iy7y68IPAB/CblmBF4AJkdq0FxRibB9QAgMNu/3f/vAsMonIENbSRdqQO5A4mPptFj1sN+ohwJYLYWv1YIlTWjPRGP2svyM0TMzMXzIRVrXw9NLRaqeLaYEsCpVZxlTlrMRFGf5c/zq/sKJdICbGLmTz+Zfh+AIZsBdBrD6Yhmx+s7S+td5ZKKzJxYIhkzKy5g0BDzVfBnZ1TcmJKlIkI1xKd56um6EmsZkdToCoI5KlYPnZDaU0NFY/VHOaWgoxHvIBMKmZ/hME/t5xUzW99Trn/DJsuw4SyIgvE9JxbetLBSS/jk3wi6LuIffMoTPk0SSybvTVf6RD38x4Ri6cADEK2LmVsotudCSj0OXOv5iWNZm9ruzCyb3Jb6ubC8noTumE9Ea204KsivGNFp/jYijSTzuOsnPqOAub4yg9gTHBiUId9j5EABvoQ==
*/