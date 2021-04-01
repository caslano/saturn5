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
Syfvai71t8hIvY2gnIpRzoDm2lakNI6sauWc15gDwmfTY/7KlwTyQv0iuFCHMsyx/W1cVnxVwOEg7z2cgVvge4JpK6lA/C/Ca3pRqzvCs7Q9tcZklodGPB73acK2IXGEdotkl3NLF7Jjx5w+5redtGa0+PxFzD7WTsY110cTrOdgIgkx4rFPDYYvMaYpFbdKpcz7EyL/G+7liUFJgCVlVxuPqkaoBW+xb+jm2cGQEC+YZ0M5VaeEuXajRpoJxRPJCYmiMkNtiwuXaIY0r6zwaAbYJ9plYciuxej774Bv4NJN0vss+oilBcOQeY2mz81mjgp+0cnBSTxY5Re3gSrwNeFRAPx5So7Pt2/s9U4r6Y1E+0g3sM3qF8L/EqVacEN35pXvS5KWUMn0vKrkuiM8fVBh4zf8MBOhl9ctfGW1bpAcc0u4Pfo3kNdaVQmHEplhfDb6IWGV6lZSHXuiSh3FUKsjhA9etADsiSuKznmnboV8EuUBfVU7lNgZw1FFZYrI8Qq4JnIqzxV0fX3xdkMDAUcxhggk+hz0Tq6x68Y2/F53sFfUGFrCGxiAog==
*/