// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_DEBUG_TURN_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_DEBUG_TURN_HPP

#ifdef BOOST_GEOMETRY_DEBUG_TURNS
#include <iostream>
#include <string>

#include <boost/algorithm/string/predicate.hpp>

#include <boost/geometry/io/wkt/write.hpp>
#include <boost/geometry/algorithms/detail/overlay/debug_turn_info.hpp>
#endif // BOOST_GEOMETRY_DEBUG_TURNS


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace turns
{


#ifdef BOOST_GEOMETRY_DEBUG_TURNS
template <typename Turn, typename Operation>
inline void debug_turn(Turn const& turn, Operation op,
                       std::string const& header)
{
    std::cout << header
        << " at " << op.seg_id
        << " meth: " << method_char(turn.method)
        << " op: " << operation_char(op.operation)
        << " of: " << operation_char(turn.operations[0].operation)
        << operation_char(turn.operations[1].operation)
        << " " << geometry::wkt(turn.point)
        << std::endl;

    if (boost::contains(header, "Finished"))
    {
        std::cout << std::endl;
    }
}
#else
template <typename Turn, typename Operation>
inline void debug_turn(Turn const& , Operation, const char*)
{
}
#endif // BOOST_GEOMETRY_DEBUG_TURNS


}} // namespace detail::turns
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost:geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_DEBUG_TURN_HPP

/* debug_turn.hpp
CVKv24HBIFPCDv1SydZnM7AXBjQgndoa3qGU07p8NVZ+ZdRdhf2OAX+N8YvQ/XxefDNH42cXR/vUn91+T91q9wCaMNEW7jhq+o8weWPTOYDA89TuieqYGLNrb8AduKs3sZVt0TrCx5ZObZKhLGfHbZ1bo/ukBpM+g6StI6YwrssXqUnfQBLtk5M0HQhFHVod25Y1+W7HcwvyTqHRJM7LQRs/zAIFYsk2ZiI+xE/H+LoGVTcjumsJLgvXS7iyEHYSLj67Mrv+tEy3jluafEvPzHj6q/4p/G+h7E1nMbgAe1JTiH1Zhj68c57uqpB9yEn1JnpAPCyLqoexC9TDNfPUw8F2msPtkGtNZ2EEnXcMQN78Mdd4XN/BdRWuabhuwFU37/OtE53lK78h6+ev4oIx0Jh7ljRo80oQSpscrI/O112s6CLcZUXDH2JG5XGT9l7CfdlcSYlL26tW+MOc0IhwfY0QIJ0EFSmdWgZxpqut0RC/VR+mh8ZwsnNHP9baORs51bcqek8Id8GIViCM2b8XQLNoLEhk2R+32PBdIk9kZtTFZPjhNlZhl2aKxmcY5WFJDgvPmOwCg/xDIzQBib8hgOxkUtA3BA+nHMEDHBipNapv1AkCH48IHY1UR4iPn1AlyA0ZCMsXYe+IMLtuHquPqNv7SVoWmzYwGnSs+x061ikFjmrWxIVD4FZjDK5mXC/h8rD1cR2J60JcrsxufiJQc+tp6Rl8Snv66/k561/MHlFcAMWg0twCf5k3VQh9aIsX6C5gMdULFBaTssy0jrjkENUJKmTweoTZBNIzwooL2P26Rd6kNDCVxkShfH5z8zxhirDXtIMB6NDOwBHSp3NIWHA/XRD1XR5ksZYdyfijXULAMDrikph3q0h4oOXfb4eYQd/O4FiAsFswaBmb1znW8iBqtxRg67863HRY9JxL7GJUMnfx0VEHgizqHqSK/aPmxPY7oL6HdVtfo24R5Ns+rc4iDAGdIQ7sHuLs4YCY0rX2RjAvBlkdXA/gasbVBw6IforrBVzv48rAsBiMqx7PI3Efj2sKLpfWq+vPrbs46F3ixdOjZ1b20/85P9IEjz83eaQ2b+H6uGulFjzNWXkWahwE6btWpoUGqD0XIsu7mtIY5g5m7WqqDGUkSTif+FNA6dTXLTDzXO+uxozQ0fjrD/ZGbKlcMNcRHKSGdzfehydBQEEOn64iLPfLZ6Kc/XI33HKs5uoa/7uU+NlHHxgfS4m/rJv4H6TEn9pNfEVKfFE38SemxHccdWB8r5T49d3EvxNJxtd3E/9MSvyt3cT/LiW+upv4WEr8Zd3E/yAl/tRu4itS4q/rrv4p8Tnd1T8l3jWwm/rPTan/kYhPWf8voOqmrQr8pEyoRt3gv0JY2w/LVuarFaYFtynRO+l31WymIxXj9kbQdP2Q5DqjwfZ5tiBbbJYDRrnh25aG2PtYmcjOb84euJBJXOTbSQcUUivwMm4VwuqxaflBRNr9gR/CBz4H4B0S4LMjk+SEXdaj+Q5I3PFtq+vUA+EGaIZZdG6+4yb5dMoZAZbwpQbQzEfJGXmtS/NTS1opIAqXg376UhSmdKkSTnk3aHzDUJ23/g+AwTLHDh0EqEZvCkXEsiH0JUDdLLlJjUC4I7Y3qiP4YM6RRRe2fO5cKOJW2055YQNM2PpfTfVwP6npZxhLabc/7obhAMz1lboNIFzDb93tB4lkfRjFZOWqX+rjM5lKVQmFnFtGku+KbFU/WUTeoiyf1XKEpspGH7coGUNVgCqnNWeAxmb5UGPMHTLpsyBMIZLSaAJOdTwhpMVPFa01E/yUfcasGvFyhD82f2BEOhuGn0XLLEWWhfv8sbTC8mhGeXQ=
*/