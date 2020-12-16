// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_REMOVE_DUPLICATE_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_REMOVE_DUPLICATE_TURNS_HPP

#include <algorithm>
#include <boost/geometry/algorithms/equals.hpp>

namespace boost { namespace geometry
{

namespace detail { namespace turns
{

template <typename Turns, bool Enable>
struct remove_duplicate_turns
{
    static inline void apply(Turns&) {}
};



template <typename Turns>
class remove_duplicate_turns<Turns, true>
{
private:
    struct TurnEqualsTo
    {
        template <typename Turn>
        bool operator()(Turn const& t1, Turn const& t2) const
        {
            return geometry::equals(t1.point, t2.point)
                && t1.operations[0].seg_id == t2.operations[0].seg_id
                && t1.operations[1].seg_id == t2.operations[1].seg_id;
        }
    };

public:
    static inline void apply(Turns& turns)
    {
        turns.erase( std::unique(turns.begin(), turns.end(),
                                 TurnEqualsTo()),
                     turns.end()
                     );
    }
};



}} // namespace detail::turns

}} // namespect boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_REMOVE_DUPLICATE_TURNS_HPP

/* remove_duplicate_turns.hpp
eJj6eYYGblX8POSZAoZLk3kh9uXxwKkv3VZWl5AmbOQ0dhYjjj1ySj5GNtnsMBp2D7Cdeh/vzIpBmWJWnDooOSuKrDxZkNVuqgpdr/lBh4KZOaxFEZ20OnappmSvbmXmVvQ4VE9/pb3HRBqkZxqfeeNxg9dHx7bSXoO/CoI6N6xKuEBJEDI17pBXjBQYsSvxJ5rbA3YPnsBZFanSePjS8ewtbCU0KB8fTyzuIzhfXvPeQ359S3s/01c3QCTj/DKWBOoGRM6RkrBVFa3CYnfgmYTVxBW1CmY4qwK3D0isBL0RZQp/iEFxJSYTZ1wQZuOfQrl1V2SE248TSWQEa5mGMxONw4CYTPWwB44VJ3d6S8soJAOqCg1nXZgm6o3uXyvpGzfu9rN/Tpdnt41+6qMegpfO9iXcwRMgnS/ab6O1WC6cOUrL71rAjR9pf0/KqHnjK1h6eHq5OV2eue90qZ1MHZ7JtHqYYVwURZqZ1V3j56v4w2T8eB4J8R6oarEyZVCZP3Y+cluLydDKlCuzRPBJJpYvtjOMv7aChMuqmGNb9RdUfWJT3ayS4duJWdc+3BlZc+TI2nR86nr7hK7Jjar9Umcy3yoIkB8x8FRWVtn1aMh2SRKXFN5MVBLvmay2l7syU5SyQ8d32vEu0jl6bQU9Tusel0sFPU+604ne49mJv2YnLnKL0Fes9/Ahk+dgeeUhn43wiu64dKo4mYSTj66md4t7BhJrkQ4upsHBxfWpDi7+U91g///3b/Jzzr8TJYcN7nQ4Wcjd+hBq75dp9EirhKcsqVohF+RZ1ZrcUkdgZSazmiTMUH8CqBSLwQx1kvlhOlaZH+BlBkS1CtJcVPN1TpgIsaXetlZx5tw2RRMyAHLF3ySEOS5lRJvfRj5uSCf4Ju7IfZKa8v4oRdT4FlF7ff4ub25Gg0uCN25fCXNwbcprdzTCT9RLuJ4vsLLYGqZgGH/th9uilba90Jo2idmIHT3M+mqh/vIA7b5COrW2qy405yHCjWLccAK5OX6mqr5IpOrHGvxC1OA1ZjSOG0TdSpdTD0KZkipyl5uvlFrCywWHE3iffJNcztH8YJpa354QgF+Ra9XqgVirrnPWqt/v5xEEiR0R9EtRJN7NCUkagVPeaZNY3mSf8Y9MEuwbvgFZBm9mjsuTVZnfGqacAaF/PhrC1/lzxn+V8u06mWM/dHFX0dqzEaA08DcxIHSqs/uM6Sma+6Kj0dw1Nl5Tuk+28cmXJ9u2QYhbuMFqWftdIdT/cr3787aTON+m2I+XpT9Dlp5erbZItuYesmtqXMJOvDUDhaFEjzLJu/goiRVORcEbridWOBon2DKvZe7F82WV8RhnEMnOvD3IBiCP8xS3zeoxZj8ootYx+NtATB7MCZ1EOxMK8CwJ2BG1eJFlPAnAl5/M+VFI8OHrPaWhfoJMAbhnMCzU8/FSxj8ueRSdsJgymAbyUGzHmLXNzdroAe7XG8tjpWBtwOmsdz9FZaQJmhEe6/pLqRUB/IinZdS7NL5YrA4vgGkUHMfWrz5cUGfmyvm9qG0d46OLBIh25C2fBFrVIM0nI/8Pkf8IASjLWALG/fe1pq2eLAvZy1IM38/cWauPUKsSy1iQjtTFIzzGAhp3YSUE+rxduO7+oLzkWWPWZrHiHR1Qkj7lhc/y+Bc9x3NOLO00QAXJT5fcUi5HYkm870NSuDaBYjTIGYar5DDckO9m26thuAwJl4tFaQmC7EopHO8hIELszJNVFHMHH4FRl6uoXESxNsdoqo+CPdNP3Jugwsn0i731m3oK0vflyJPYzG8/JADLdijlR7AQCVfDwRHbORrp6KrIG7u0Mp6PiAqzpdx8nr7EvqdpeHs=
*/