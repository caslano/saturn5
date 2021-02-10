// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_POLICIES_IS_VALID_DEFAULT_POLICY_HPP
#define BOOST_GEOMETRY_POLICIES_IS_VALID_DEFAULT_POLICY_HPP

#include <boost/geometry/algorithms/validity_failure_type.hpp>


namespace boost { namespace geometry
{


template <bool AllowDuplicates = true, bool AllowSpikes = true>
class is_valid_default_policy
{
protected:
    static inline bool is_valid(validity_failure_type failure)
    {
        return failure == no_failure
            || (AllowDuplicates && failure == failure_duplicate_points);
    }

    static inline bool is_valid(validity_failure_type failure, bool is_linear)
    {
        return is_valid(failure)
            || (is_linear && AllowSpikes && failure == failure_spikes);
    }

public:
    template <validity_failure_type Failure>
    static inline bool apply()
    {
        return is_valid(Failure);
    }

    template <validity_failure_type Failure, typename Data>
    static inline bool apply(Data const&)
    {
        return is_valid(Failure);
    }

    template <validity_failure_type Failure, typename Data1, typename Data2>
    static inline bool apply(Data1 const& data1, Data2 const&)
    {
        return is_valid(Failure, data1);
    }
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_POLICIES_IS_VALID_DEFAULT_POLICY_HPP

/* default_policy.hpp
Mve21JXUjRE+jgossYM1Sn1kv0xfKHUzhLGHMBtDWFEi9skDBF21m94HoKiQcVBhzWSE7yhHFc5mTgIhQJxgNAJQDk8o5AJHrtvvD276Zz1yeUfgf153h923vXFvyNJk908f2h37U7ZI5ZsczdSnAkP0k9L7WMYxhrjA73VN3MlELush8GsH1EKIucXadpEb3Mn6txLIF0GkU4soxTtOGnm1TWgzkoLuuhape8f6qfo1yM/XewiGouWqnhzF99CAmNZWvgX1l7FbvWNxku+mNOShth8jjMRJEe2aRd3lGBO3vEN6BfiDkyiyVcct7eAOhRUgeKi4IUpm9lZNYqoNUFuRU4HBZBth8aY4hAa4wwHwGUacLom+E4gcw0UGw/c+S7JtHWpHfJwJWAjsEYTObQiemSISTmkB0pGBABLukrAnuP/nCmpNgGJQR5N5U4kpa7GpnLkg6sc7BRXP6swLwHf1prmJNpTSyunjl91z5wKkaXw56Dvd4aubt73+mJbcjaVRvYNrfD/iwWyRaqg3DQZ9Cxz6udT7vDc6G16+7FV0169U/zqKmTiybgitEyqG0K/Woghq5Oa6ojM9X9vz+qr7vqIjPl7fr3szqkKXnq/tOe51h+eDd/2KzvrV2v6vbJV5rF2c3NNdZHwm
*/