// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_FILTER_CONTINUE_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_FILTER_CONTINUE_TURNS_HPP

#include <algorithm>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>

namespace boost { namespace geometry
{

namespace detail { namespace turns
{


template <typename Turns, bool Enable>
struct filter_continue_turns
{
    static inline void apply(Turns&) {}
};


template <typename Turns>
class filter_continue_turns<Turns, true>
{
private:
    class IsContinueTurn
    {
    private:
        template <typename Operation>
        inline bool is_continue_or_opposite(Operation const& operation) const
        {
            return operation == detail::overlay::operation_continue
                || operation == detail::overlay::operation_opposite;
        }

    public:
        template <typename Turn>
        bool operator()(Turn const& turn) const
        {
            if ( turn.method != detail::overlay::method_collinear
                 && turn.method != detail::overlay::method_equal )
            {
                return false;
            }

            return is_continue_or_opposite(turn.operations[0].operation)
                && is_continue_or_opposite(turn.operations[1].operation);
        }
    };


public:
    static inline void apply(Turns& turns)
    {
        turns.erase( std::remove_if(turns.begin(), turns.end(),
                                    IsContinueTurn()),
                     turns.end()
                     );
    }
};


}} // namespace detail::turns

}} // namespect boost::geometry



#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_FILTER_CONTINUE_TURNS_HPP

/* filter_continue_turns.hpp
rWXbdEAGNvr207Edd+Jk9PgQf096QXYVqC5jhOmR3QV02QHXkOlmK1zAdx7NK7LuPI7IWIdmB8edwTAZR3d31EEGQbiDu+Puyv4AUEsDBAoAAAAIAC1nSlK3Jn5KcQMAADoHAAAbAAkAY3VybC1tYXN0ZXIvbGliL21ha2VmaWxlLmRqVVQFAAG2SCRgrVRfc9o4EH+OPsVOw0PcM3aavjFJGwI05Y4CB6SZzGTqEZbASmXJlWQnzOTD38qYEm56l5eawZJX+/uj1drHb3/fRY7h1Sup/wleOHrA1OgHnrpfJyfJM2x/CLrH8RWJGPaI5ySAVxHPcFIjkkbj3M+T5BWZe2/M32IPvE/8FCPkGHE9XWyMWGcOTnoBnJ2evoc2DmfvQrgWVnL4ShXP4Xxd+fFyQzOtI6U/RP+DPQ2hT5XgEuaOqyU36xDOWR25zOjTU2T5hxC4Ayqj2sQiExasXrlHajjgXIqUK8sZUAuM29SIJT4IBS7jsBJoqzeZ3g3H1yE8ZiLNkGOjS7CZLiWDjFYcDE+5qLYUBTUO9ArRyM2EdchXOqFVhNIcHDe5RQovTqXVQCsqJF2iDHWQOVfYThynpZHoPGY6tXG623qUubzZxR06yOkGdOHAaSgtD8HnhZBrJlZ+xFJgsCiX
*/