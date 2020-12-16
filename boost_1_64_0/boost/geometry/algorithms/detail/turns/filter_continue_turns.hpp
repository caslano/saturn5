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
pgftHOxZ85hI5Ao11jw2aI54OgFPc/GQCOWHn/DoYvf7u8spX2sNR6awiTtffXNB6EJ+I74eQ2rXTCB21CSdJP1ZzPDJgfD3lIHgrQ8JT+1HOEOBTdHquoADad4Rou77RWPOHhjFHaWlk66IcmdD+yiumcqYkibOr+vwvXUJvmTOf5dO0BMjZM57ug7BLd/okm+lEPGW+bJO+Hil+vhF+bHjWeBCFvyurgDE9H/uGwTQ7vdDf3aYiiao6QDlTDWtlwKFXOVM+4V1Nj4UPq0kgMyK6I14hywiJkSAto3tGZgy876kg/l/6U+ux5fOEstsq5sHdodVT0yBcvpwbXyiP7wsTxxgjsZTEZ9COa3uac7x3iEN/aSOx9DPrJfWif5fK0qBQxdAEutvTIPoqeQsl1crwoB5HuRSN1pT+mtyAaPcUQoGT8kWsxxJ/NCGD9NXckTDw1Q+eDUzTND0FeB1IxQvCNUpBROo4hvlWCfhZoWHaY6YaB95bOikehnM6SpGiBTW/TegAgwa/MUV15z9cKzwHTNOHrQfremsAPT9lGYp18cicAu8slCdttq6gITeqh2lkcEsExLCQYP+sj+K50QLSPhKFMYdPJvSX1MaNOWZs7KOtQAEvAhdFbpoCVS1SagHV0NitC0yQmva4wHVPpIlgSNa36zvIPmaflo4EWmtCiBEhkgZwHuR1QOrkXBsbInek13WVmbuth7qJ42/01pA0v6jV1psvQ2R9J4L3zJbrXnYwlkbcxNrIf38of4opb5Of8F6yR4apBcwHXSCqlVK8+zJVG0QWrf+qhZ4PjabKTFYzTGhwduLcDEcGY/tDXe3NQBZoezecKsbxdDf8+kfeRMt1n5QLnwlO4z5dEUE8CnC68zMPHcyK65XIg+2nw4bj3RyKbNxN/SyfRn7ItUaP5e5dVbuPZOL4LZMR1DoojOxOAadE/9ZKAJ766TrON/aj2XqTZlceDO56TxLB74Oi6SWZBA+BahnGDDRQYo+4b0cWkX/QR78bP3s397oTARIknJobO7cfLTuetwZcmui/E1DKEWE291XWnZ6t/rzeh4vHSs8OdGsSFN9RLhatEuSPqncNityXMD8TaNb6dXSYRYGr3UTEgaqdnBk0lmPF9qKCZrrH40X6idGHx0oyl9/f5bAjr4P509WfR/HyrfB7j5LlDjeIThp9wiXm5xvbbg7CObivgLBtCYdwftW4Sv0tjSF8M1LS7pejo2FXmpom/Um1i3GLUwT1v8RlkBcYvBq6/5q6UCasVMRCzpKKRYi6XHv9/gsWvYe44QzZviPWnBkWhKuMJOLNLgzTQ9EWS/znSO+aux7/vBbNWrWYMkON2WAjkN7d9Zth6oZnEDHMXWXucWJFR27rdysy3PwWMnvKxCDPFaWWWGupY5jPsrSl0631xHdeUPAKNvWkEblCfkMt9C0tfK531pKhUOmbXL6Nrnh7mpbIFlMb2H55EI/1oUm5M4hyUIWCcscf5PdO2+oW3oiPETiNA39cKd38sOVNACnqSSMq352EBwxUJj7cTRychoHYO2THIzCedOlzUakBe1CoL/JBRtxXTzKYXGbWDHa0J3WEhFM0zKwvGLtyJUr7y1sTLQdrVnHYnKIYfYANSaoXf2lt9er3fQYJYZYm6N9Vx67fZOQiOUba9GhUmMG0nNiXRtizbG7jd5lfcMrJHGMMiW9bG/mkXrVN0178iIe0bCJJpWSTYvUjcnUNUzd1JET0T5jSs9nTBnRAmZoG8wT9/VXbYHaph7AOJbGTZrpsZFA0Ns5/Ny67DQ26NhtGG/bzbL3/HC+xmnMgbmWDWetPkw2AmybOQn9VWXbEY89gSmth1WSQwU=
*/