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
yAwbhjVdGy0rWq9kuV7/bHAOX7YXlEK0ZVZ5U8MqSSmgm8nLJmSNeFaKRhHFrWRjR5uFcji5aYBCMkJVcN6AMdjvUrjHUZBYUG0W1VDf4s4TbRi6CRdgY+HpROeP23pXjLHyklLfNM7qtilq1GkK6AoSCdZnJbn5HaZXFBMxOMquYEeMJPddG0VjrtrYX0boB/EQ8gvukvj3YuFSslLHdYJCto4RrFrezOhBbFmmKsfGeQenlg1V45yHW3xrRdD27lS9+BRQtJRhJT9CpDDsvgL9ZZlrM3INTrbCik1I7aZYK5XoTVeFlqoXMDklk0MFnbtMEwd7KdQ5C258mjbFwira2GIXyfYP2uwRG9NNw+e2rLXnSB5BIWVRmrb9/oR6rGls2jGBhjonw8UIGyy4nGmcVXZujgmfDiV2AAa6GrUrP+RGjVZ5t0QDB3yN4lLNSworPyShg1y3DqbJ4eRSUFWNFVUowSGGlMx6baR6TwywFI4si6RzCxgCtwXFs23BcRY15NavQuEiDSiLlyopZ6Bxks5mlGnBswNkR5GbqF/FjhZ0Vqm1kucPrn/TDtQtH5/wsn4zguz0a0Oo0v7oVqPgZlkhV/CAWMStdKBKCOUkZ4OxpNmWdRGB3t5vxNa+R7uDNYbQNMlxED4s
*/