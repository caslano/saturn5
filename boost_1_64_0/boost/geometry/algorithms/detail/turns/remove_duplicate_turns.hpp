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
jijHIN5TH5qx5uk8M4J6bXjNoZTnUIinj23HV3N8vNzO+aTpnqCC30a7GPo0KQXBs8JxuNzTNeD0hg1moD0FBYseqhZ/OeI7Q4QD06a2u/WgLqb/XD0xyX3aQ4LU64GAHCXbSCAPOSVbzKcKPLCXXwTstCFZSQWn3TCn+Yhs8WwvkWSIVLZ9qHXNleKp2gcCCAxI1AakJPtVt9qMLR7437kcZ2oCebxf+e+NQ02beoOPaglR1uiKiHu9t0rQQ4wVpTXKh80rtyononEkaeOjsSRXwf+EYo+IFeh+WQCXIM1Gv8qziHmZt8DatpE77WDEoaIWQbLMYUWwQF7ut9JniSuohwvq58VtFCojZ0XTc1YeD6yEF+ozYg4PmAm3gORWOAtrVDiwZ2mFTYtMIvytTYWfl9XR0QCeglN6J3+6Xj1bqXYNZqVzRIzAjFLyr2YwMTFvspaneiy+ypzIuurmw75ucPfUmMvUnKT5C/kmbSZfbGZNc7JeNEB1hJb/Timcdfu1X+Uf3tuiCAY9TutaSZ0aH9TJU/Qy4ad/AOt34H++1yVNShmreB9BxA==
*/