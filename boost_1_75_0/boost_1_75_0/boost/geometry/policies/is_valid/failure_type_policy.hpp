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
nrr15+6j9f5DynGS3/Bicyz4buM40GIcuBe0hzyeKFoWAOJkKjgi2yfB3gcSMiPCXsLW0yQalKDfI27oaLTgB+j7zuIVr+AgxpGe360Pr/IdAGs1d7HFjogHPvaCudL+m/fiVuripe6HUtNqQee2/LkF+j/Ac04zB7aNzShrGo7iIvKYq/S5XZ+exV9nOmzJxtdW3Rypqmf8xsA1UtE1zXbG55+qv7D2oXtKrldtKiMzGyOYq2VE+C3O1SvC7mzPEf7wTIRE5lnXb7F9sil7SvG4QwTJ+igcEfkSWCtQQLYMVPMhnUYAlpBOdalhz5nOFd7xAgcUFDC3DS+o/u6pS9NdF73jpCpC6d5erDZxV0LyFSEQEE8SHyJecKARC/exNo6ILpw+Jo4LCSIY8+Q4dnY6vskzAg6B5vzdAh5GYmwdEBJ2by4ajqZvX39A0cCXCddACavMt88BAJeZo32A0hwqQ2Ab/OIxcOO21Rp4m3YwEnjB7fIR8w58a9F0d6oAXx5WBTpNXB/wbfGxmxsh8YzUw50YoZBCgBYpKwzg2Zp+/I8fq/rhFDWXf9MROP7HLPxfdQS+f+kIyrbmlk7u/87CY7t8XfYUf1T4jI9PW9cbDPUd1Q2u7kkjpjd4VwLDw0SNwyNu4aajXou8G7TT2QyM1RVaUYu2JUj0fked0kTlxZ/HbTvn82G44rQ13gjE4LjWFP9iXm47t+Qq
*/