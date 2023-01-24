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
WLm6E263uTFEDCVvtGy9tq3XJusq9pTUGezzY+/kEqohFz0IuuEgOalnp06875IvP5B+QCrTd+gV1E6o3qVcMnC9TCQfpc79YxrEOb/oySlrV4ZUO/Vnu95DOug2NAXRJlx+4JwGsQgSrv21Rbyu30G+SMQCszAAsxTt0O/wEK4F9JF+K/2AHJhPg6ZMTqhUe+E55vO7LMJH9OINSmmQzm4iTiENcpJ4jjkHI3ZEj7pobEkyT9eRzL1EMeN10KASEK8HaRCLR0ddMkAHhO0PGNH0bB2JAzrDdWRKD9Ezsn+xL/jzOeYFYCBy1GUFRmglnWPugRHsgPTYjpT66OiUNHTpEedvNhEK/1ZGZfnTLen4t7MZ4OEkzckXLKVoPJZydg3+Z9CV1qLF+9frV+1kheDmhMsRxm+EDvzY5cpuCYGnomgvZTWr0XIEvh3cs1dCKKgEFJ8BxXdA4bQJKGqL9pjJFo2WXAFbweqbBQSegpS9FDygmBIaVDJFa55CzUTnqSSbfUASxyPHzvsF2LU9Ny/U5+PfpXaKHmE79E2qJ1QWjwnXUImXH3qAqMGnQTIa60jpHiIhdS7djiQDW19U26/uCcIrpU8Ag2lg8DIyGYwwf3zUhbIlAeLUJyMw2Vt7D55GboCTGA9cAMwBsbFPg0x0Ez2jASAmnGOMAamX6Jne34rqmQeCxAFGlAEp0EmD7AG2dYCUco55A0iA
*/