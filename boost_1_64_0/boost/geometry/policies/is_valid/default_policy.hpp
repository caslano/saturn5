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
jVvAk6+ItkefvZH4XRbB3kbyvmOmPoTs8E+5SQsnupVuUOSvcaObou2/nqU4eCXs0ZsB9v84dwFKdvUW54S2Y8+vqgOF7OF7biFgVleH8yORfKhNSTAwfV5uydu3cBWZvhJztxLtU5nS/byvhYO+zdzW2yPNa3HriXY5XkTrF5Mw5JRgfPejbjMJN9oeL5tjP3PbSRhTZWj2d6PdPbDQgJnj9EGCkUtLHEbU/uzb2e3g3MDfc/uJ9u01g4dP2u3a1YL6OHeHCRh8NbWP7mi3i6+g9mvfyWrv3Kf0Wv6+bG9nWIyUse9edue2DfFLbav8euJ/Zg/azbsP62n1VFuqXc/JB+9pwcA7ZRVhJ8YdpmGX9/XDyj+OzfvkJ/exYLEljOJi+rx631wP3NLJkfkdH32ABdNVMERHxNsvHkgwfYXpzTX9kVjC9haQx/5Xd2Iu4eTwYuL7zi2ws0V3kcTpK15ujk9yXMKZl5rw60QZYPO+bU4AblJvS36Jy2jXchfNxE1k+2BNtrdY5PP3RvU7Buq4bpM6uysY/qiI6FvfwFwofdqA2uKlrWJ+vBWKmD/RpnTNt2B2gSA93PqcDjZV++6J9iUxlZtKN569m+wB3XrYETtXrhyi89wWrnWEOnK0PhwOt0egdFzr619ktZNX5mBJwbyiD0bMtAFz1oLR+eYBczcJ8+Y+GBxuOsftMbIjvMOGxa3e7g2MgervvdP6w1ggZe98u5Yk7IUe2G7c2pmZV3AfmgI30wV46v4+OgVurwX3iT448lbVcJem0m0dkAfqm784pT96glGfX5kCO9MWAIXeVcJ9n+AeEh5Oo4cPG/ewWwJUiqWrS8g0iv0i4f/Swq/MLrYOdoNIzdm/qB9wDvHj2OOWFiyb0q7zGkYc1GO1Tm8lf5cOe9jJ7b24rtpvT+1GRuTBuqJ9+dHSdiMTyNCM0ZraNeQwNFs0ZruPMBisOtlPR29ZwQ2O2nB7e+G+/yiLZncZbG/iNMVkLWu72WMtOA1E33ixkjCtSNNtB/kB65rexDd2/yHdMJd1vYsHWPp6H9rzxG1rGslKZarat123RvvCXzT78EUtojzwEEjy/xvEljbNmIrfmP0VDrwKERoFP0aAyrQW3B9t8EAGXwYwzMPuJeBlgCjXJe4y4Q/EEfKGwdbtdD6Re9t/6boQ2oZt4swmGTzksjhwDpEaifIj7AYsqzVV+lBywpJuH/PATfF3LMprzMApc47roxyzH5TFQfl1WO99GR+lUjjv0zYHocu4gdgDWr8gguy7KRde7Eq5IOCeB7l/a7YfDgL4TvsGkjqVr0zrT5zrpE5p3833xJtB3kahvBwmf5cXi/j9jex3SNxin+L362AE+IlFt4P5LpzB/Xv9gSzcjO1n1Agd3E3CYBAljDxMCUbJGhr2jQx23ANL8sRXriRhOV0tE527stm+uCIrxsrzcDzcEl7R2FAA1Tj7r2biiGi2qUgk11xT4phFhw35af+1ZXvvtxPtTxIcXZ5DPgtybei+netInL4CrQbcP64n4XrHlPzF91wfcPSe1bL9V9rf2Tjrd8HRG4q21WXy8+Y+3n+YbEc+9laG0H1cvJEN0y5S3cfLbjzRjjW/uYIbUcM89iYCZtqake/tmwKG+6QL4Vz30dwM7f1+7cRrD8z2mvG+vLndTo8x1cf9bzEJg8eYlvt33dJuZ89PGtsJOPkoM7750q0MGPocPbczt2bt+BRqu8Ta8BlGv4+9jdGmP5Fw527L2vF51Hbl3WbbeHnl+JZuO2e2yc9R3zu6nWwTopPIG9LlFhVc6zPpRrdvYcarWljV4oXuZ/XOEzBbbWll42y7+x7A9N/zpPe7B2Cmyyk=
*/