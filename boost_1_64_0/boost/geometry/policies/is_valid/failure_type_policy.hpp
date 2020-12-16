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
dTTuxnExcRViTUJzoUzD3W3hlqhIhkdQ4kz1UCfcORu38as6RbzNVG97qnfVMNwcOeubFPl7S2O8pnKg+hjZfXgNHE9Tz+hjGif67p/5sFhP6+3V33kVDkpdn8fqX+SpblAjR6+J/4PH/7B33UFSLkV8yQfC48yY8FRUzHcHIuZN3+bweXcgxmW5XbjVC+vtnR6WATPmnLXEnBVDKWbMr4wYi7K0xIyZMlLm38w30z0zO9/eWeWf3nu8x339m57c09PT03PW5ZHCZrRY53EVX0YeWxaPfLJYr5dymUzRHhtuEXgvdcVNn6nXUsVSTqf3Z8/yZPhOzv67UglyxYCGSAYp9Vqn04zYaWrFUildK5XU0LDT0JseSGPtg2v1HAZjyu5PO0udtuCkDcSbLtlszUprZ836z51sH/RaHWtJkacA3/zluzBdO02pXgpgxMir+tlpdD+cssoIhaKKQpbKRbuMbpbcj69w0gdhpZItZDwyxk6v15OzZvoQw7maT0ErEJflrZxde8G1drp8rR7k0mFRpeMc++KLO31SxvwOoLNE5fXnSmuuk7ZWT9fTQbFsp7VzprsBd7btGyJycr6a6q/oQWe9ddKVg1KAaRZYFeV0/J6QlS5IFkq5SjGfS9llje/XI076dBkjo1hL99fVn75rpS8k07VMrVjN23eXPG1Na6eTHm0V1oJC3kpvlcGRcVb6IvS4eiZTKhes9P42IB4XHB44XhbvMfrL4PAgOWfxyAnDInYl2arDw9F/WYcYvovdDvUaWqGSLvnrwRzojrWTvoT1IpNNBd46ePTh0EqfTYb1oIqT+bJOP2GV3s57xkqbS1ZyxSwKX+e0vpIbb7466atBOZ0Oy1k3vaskk03RTB8mw6rQQWolFbSDS+3qEOetfNPirm0du+eMSugpMqe96KSt5wMMvVrIad3isv5xxUpbFhuIarlYtcZbnM6Y1uPlrjaPUr2SKRVLRW9/89pq8Ri1eECm5mqFXL3G7R5bCuYROjyqQaGEVqwxj7hSsE9Q4t9ar3YfGU5k6c0ZK59qslIK6tl6WtR3DVobv/102eWTC8p52APAZw2aW4L9WO5m22DLRfESSFaKa3fEkb57N3vMYMSkoTLymtQ/Vguk7zppq2XoCXkYfFDguLTaHyn5O92+vsfMWQcKrTyyyWK1XBcxcZ21K53x1G3GSQv1QrxHkLXXLzst3eGy0hZkMOJ6Kav28W7m/jl1xuFRLUT3IfvXsXge5x0euRQsCsWKbOO1luOSwyONvVgmLFg84spBbxuNOvvBWqlaxty0+8Ed5LyWjLjp06ViGObLOr1/cPOduuSoI1uCSi2XL2aoLdew9zjq8ihWSqlqNrR5uAVxxoXDI1Oq5qHD1UVbrrUcZ1weuWomjZWReKxhD3Teac9MOcjl82Gpf17490CX3PT5IA1tNPDNDc6edefEmBPvLxeW6tVanoWNnbFOt8tJlxNx7Mv5DKfzt/uolQ5qbz4o5cpV/3SMWZ9Ch0eYT1XDtKVWxtWb7TVjzpsx4qHdfDHLTOzKu/PotJO+XkpnS6msK285d1emOHWo1LHzwGGKXx74x995l0cmjcmUqjGP+Iag8ePUo1LD6lfI8Rj2tgOPv6tO+mxYr9TS9YKT3s4c6fV5Rvh3Wj9OINr1orguEJ1/q0uGcEclvWTceRusEAS1dF7ooatKcxp/Do8qjFGZfFnwWFWa5/T4s3hUMfZrmVJQFPrCWoYx8Vlx+VRgf61nhb6wlqHMtupxx1ZdrYTlas7iE6dfn7PS5pPVTDGXLYQVb1quxH6KbeKkD1K1grhc70vPhef0V630QbKcLZSzeaQXEezuyQFKnK7YT2M=
*/