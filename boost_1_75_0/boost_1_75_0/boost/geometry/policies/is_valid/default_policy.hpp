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
xbkLUIPK92zhESsIlcNjnQKwcIFfI2JoHkCUQVUe0HkEHPc9foLGZuSTgNgacZe9u9a1JiDEEI1bQR3wiDBfQQB1FSHbaUeomKPwVWYUNIsPCdLf3d+9ZiEI5dBI3UhzeJP6RjQ4MNDg5eF+zEegrowzMn/e1U4FRVVtyQxtv+7P6oUPTUV1koVldZLbWqjV/YiZeAdG/1irhtUVZh0uAYOxrRK/X+vYukIBoPnBbm+eh067X0WnEUiNwJArQX5MwG/VHW55iR2t+lo87GVI7vznBxxbXNx8zRogPL2ji5XQ20t+N9bb1Z6/3cM6sV1WpNhfWpye3ZDU4J7Wvw68O57WX4OqeiFyBGKWxGSWd1rDVvpFR3LcFClsKtQ86vllVHhzYNRb80/lAal+XP2Ez4KOhOJ/knjclQzDFzx9LCqh3L0zi7PLFUQNDMWZ2yStxXIk/mPaXWEF/5F9fNEbdZgnEI0HzvtAHH9RPD1z+SUmqABnHtnjW8s8jUmtXnzQ/p3es9Rdavfw4VHiMWnpsZr0ianfN3gqHAuGtqYA+KYERZGHkiTdch67ymsrAcMbmO8YhD+VS4/LqM2QfXFfGu/gmgJItfT0TXlRl0/p/KThO92u9TuusvHE80vKzcn/ShTws3YW8lm/AhzOcv5nUZeuV6pAMTUJiLrjydFlCOTH4dF64atRrjBW41XinagigPZiAEZgVEZy/HKH
*/