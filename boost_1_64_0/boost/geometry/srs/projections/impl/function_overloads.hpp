// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP

#include <cmath>

namespace boost { namespace geometry { namespace projections
{

// Functions to resolve ambiguity when compiling with coordinates of different types
/*
template <typename T>
inline T atan2(T const& a, T const& b)
{
    using std::atan2;
    return atan2(a, b);
}
*/

template <typename T>
inline int int_floor(T const& f)
{
    using std::floor;
    return int(floor(f));
}

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP

/* function_overloads.hpp
ttzwZlIqKHU6jsuJ/On89yYctF3Np3j0G7xG2QFWCH8yLxB6kp7CSYaPyg3Si+Soe8J+HXu2zYqc9+d88pjOxHxJJ3xjvmtljiNyg301qRvAIb9gUDdrQt6aPUTVzTZOT2Xw8xR+87KC/E7jch3q6kB4ITmLvQjyMh34HecpnCyHM5NwSglnpHoXXdOjGG+W0kt9P7ta8iN4mj3t2U7vbV2OYFvDORTn2xpeEbCpXnGU2wsUO8P5fb3uzMePy/RWVLeuqu88knbyMD7LxnsSzvZWzOlLpmjtQrS6e5Oyb0dxlP+KpihtH3ZA3O4Gr6enO24BZA/H87G5wf6p6aim5pr5zbU8EEE4ra16rBte3vcD0s7m5QfvCF/n77kYewku107Kjm9+vm9jSfbAfNZSB3wWD5Kny0fuga2Y10fyS0Sbzc6JH59J8ea8XAAfpu5SNOQH9g/Mu9AiDQmlk0V6fHfumD/I2U162Uv6ZhnbXBkL3B2s+FK2ckF/gTM9sfiUuDnmDDAejy5r67Hn4FNZtougzA3Gv4qf1JcwRokNBs6PqIO1JtWcoBnCzPti5h37u6NUf340hUN9r6S5t2DPF1Ufcmw+24Gp9nqctHmHk1TnLksCcEkvfUKba++UH5w3qjJFQ+h2Krr0BeBdFEbevxzC+/GAE02D06PomPrWOL1IJw1OTPHXpuiaT6eJI900OEklh7FKTisAHg2Br2K+Po3InETwKU7yG8f4J8u8hOBqPXYq9u9pzjhXAw7JyX2Mk2ScbzFPR4XMkygukOd3pHxu/0CPp2f4Y6LyiXgm1xPq4lkUB+1I7BfHMnydlF1gwsd6zudsNTePMr8VPJ6fky/ylLDkocb3M1VZL4D883neSn26hV1I/0PPEIfZ79izPsX7JSr/SyH/+Qp2OZe/KHdgf3Ql49J/K8eNKu2FQldwBXaN0dmAXVdSbBcbLb3OhAnP4vst1+YPZz/dnjUl++kIzp0tTZ06aaYn+wwLFQ/Xc9luSMkn0gz91Y2qv7qJwk2qvd/MNH4kuEbfRb8ljHO+hNS7C1OdC77YFWSOcPMz33bX6aZ8OD+7g+ggbsKdqSsbZ4d7F+Gauddk9t/XQHMvXFOMVHP0e7h8B6t2ZvDuVbK4Lx/2qaG8lFbCqD86r4c4L0qPY5Q9I3uEYPqNh59DnzOS6el+9BdM8zFVl4YnyieQ/ybG/YnS9V/nh9xhEt12tFCvHheYS4uwJ/JBJqAjhId9YuQg2Ld4WrXf36l10zMuP8O3pHlOpXlepXlB+kRHj+Kh7jK8FwFOaWH94OAvU5y2dU+E2Lq/AnRwbRFjOq+xzF/P1/YLbtwjmoH6fJPLsRXGNb8fcX2mmd3GvZTNUntfkiZ1/nz1Tzh/T+93UHguB/9ajn6G9xcpk+uvyxX8HQWn+AD8XdEP94d9wN9YHvNV/X2ANEwtq/q8kNO9GNJPb1Xr3W3AX0WEPqXbHwNtjZ+dJ/hC71OC1wX8wLnX99E2LJvj0M5+o91n7zcnjhbvamvLQb13u9v/ziTi/4L6irl7cL4FHd561wC5947zgr3UHPXfqv8IW0uPKBA9130r6jn1qK4NTgW7Zxq1sQ5pJGPd5/5wFIV9GMUF6nNnpjcF6O2q6O3G9DbzHGQ00KO4wPxjjwKhL7ioI9lqfzdXaOn5FO3LEMzeOwJ7iNGwT7oL/H4pd2C7LqH05apdl1Jc6B7kDtS5vYtSMLAdzFd6/QUux0a1P1teoPz2URj5J1nJuoXaluV/nMhTyhjIa+8CN+7G4H6v0qvQu0IVzGMBtmvGnUAw1OevqPDXclK6G4O7P57KYz/g3cUF6UxUZbksR61VZFxn2aj0B3E=
*/