// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_POLICIES_PREDICATE_BASED_INTERRUPT_POLICY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_POLICIES_PREDICATE_BASED_INTERRUPT_POLICY_HPP

#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template
<
    typename IsAcceptableTurnPredicate,
    bool AllowEmptyTurnRange = true // by default, allow an empty turn range
>
struct stateless_predicate_based_interrupt_policy
{
    static bool const enabled = true;
    bool has_intersections; // set to true if there is at least one
                            // unacceptable turn

    inline stateless_predicate_based_interrupt_policy()
        : has_intersections(false)
    {}

    template <typename Range>
    inline bool apply(Range const& range)
    {
        // if there is at least one unacceptable turn in the range, return false
        has_intersections = !detail::check_iterator_range
            <
                IsAcceptableTurnPredicate,
                AllowEmptyTurnRange
            >::apply(boost::begin(range), boost::end(range));

        return has_intersections;
    }
};




template
<
    typename IsAcceptableTurnPredicate,
    bool AllowEmptyTurnRange = true // by default, allow an empty turn range
>
struct predicate_based_interrupt_policy
{
    static bool const enabled = true;
    bool has_intersections; // set to true if there is at least one
                            // unacceptable turn
    IsAcceptableTurnPredicate const& m_predicate;

    inline
    predicate_based_interrupt_policy(IsAcceptableTurnPredicate const& predicate)
        : has_intersections(false)
        , m_predicate(predicate)
    {}

    template <typename Range>
    inline bool apply(Range const& range)
    {
        // if there is at least one unacceptable turn in the range, return false
        has_intersections = !detail::check_iterator_range
            <
                IsAcceptableTurnPredicate,
                AllowEmptyTurnRange
            >::apply(boost::begin(range), boost::end(range), m_predicate);

        return has_intersections;
    }
};




}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_POLICIES_PREDICATE_BASED_INTERRUPT_POLICY_HPP

/* predicate_based_interrupt_policy.hpp
cQXz/XsqGPRAhcRn0XRcjjH82yUMZY0eQs8zWyl98yOtmoIxPAbd9P9X/a2MWA6qc6w/BJHACxORAJCKxrBvs4QBCOTp3o4Lsv4yOhrqvBBmPwgbQynhBDUj8un9yLrea7yfPY8y+6kd2LFwgvrN/9uPOk92zH7mhI9iXKG0W+uFe5ASyq3q/F2P4vZCvFeiKKoNhIPqzNqnz3pGA6EALiSgpkWZnYFQa/tnnDfhK+FuW9cgJBEQ8U/n7T5ti+U4AV5GReOHhHMAbFk4lyw6EMs9P85b4ehgIi6Ag2VwgOv6v/Eo7msBxpoGD6D29senz7XHi0LHGbPXih+08KsM3u1xh43P6sc2874+2srRghrJcG73p9KnsdrStT6tPuISLnkITiEupveh5vRhZh9zVQ5/ZrFujhw9DEeko/oeOKjlEBP+YJ5BGgxEmi/4xIQPCQutQQeor+UQE6eGWQWWx1Skbn9wejT08K11VTy8xSKcMyZOCXulD9+otCAcf1bT0euT8Yb7KQ/SvCYU27fnPIOPQ99F5dlIwR+ctWsOnb2nlXvETZAkyo3kS+Vg92Y8KGXNg0I4PGgKCrp2kUk3gOGtimHcD4vJfsA09SM63Rf61M/I5qeE1OUW6f/Rjykz4EIyZZEy9lH4GsI4aYYM2DkT9t5pg2mBROSYqgvSXZiwcxFilaG+cTvuCJrkp4L17SVFJLweHII2ZJejJux+TEKICvKdfDghuyyyfqH2KrwSVbHNp7ijbfhsLBqhEIiRlbx9kvmpGDk/UyZabcN/DNsTAaytojLBPom0995zGots+GxsmqqE8C+PLIEySyiGDZ/hZDVKGUDvJ95203EuMN6CysWI+ql853EksuEzOrUruAvak2k6ncsMB+XqQnieegpn1hg40mt+38QpcS7gCIZkKx9WE7RiXZ+D4yUepghOQRKP6Nl4gyH3ASmxcpFGRz64ptPbxfF85FKA2buQeNPp7R6yewlnMRxZk5weeBZBXced4zUepPjEywiPCPJ8HiZejTOzBJu4031IggjqmTcI6nNd4TYcN0qES0lQES4RnbgTHmviHgzTEpTrSioIpnzjiI9pLMSVTD7ZemhR/dAh93OMMBURzLf04tzb1MXD9+6bOWB1Q2fYG80+9nuRyDtVi/XtBopeo++IIVvX4tkTpmHLqBBHFPxeNRYfNOHvHaR16ZbwOBS8VNDvmN906DbqLHgo/IiFnX08P9T18tCu3n5bj+hpH8rMkIDTdgJBG3A7a2vOTPe/vdP+DfBZvQ8n8fbJf89aeDMtHuzfWwLvYYKvxY3OvVkUfka8u1kHdDzcEBLrJqT/Vp8EvE/dDN/b2kyMQqlb4oPkHwB3e8B9GnC/Ef0bcLKsaGdbBMwHwP1PCAZ0CeJuaN8W+kLVPsnkcANOEQNJ7zOgN3Ooly8Iwx3MJcH7w2V/Ug4nih3MZwVMfz+P35EwnwPM9/th5re3lttv+zxgTs8qWmChzeaLjHmiD9n+G8mL+UYZiigSOT5fAMxuR9CRNOaxkcfSvivHZ3e7thDpKMgvisclOhs/XrffkbWjTbbfXrbvsdrBZAuAJg1zdw4jvlHCdL4SPwCffooKkIeH9eEgPGz6SuyCf8MNWju+hFhcGi9srkhbHfkD/OWqFpx43Br9fOFqVjuepB0n692YSriLV++BO7ayNTb6OnONHhg5xOiNfBCu2QMnlw3gNO8fvVYPHNoVT8m1J9uxmtAHwdz/OhyGNAvE96U+GBn8YvpwLF7XglsZD+fhndP6U0qY3xDM9ALARp+Xd5nwrUpBskd9Ll7fhunpc2z4gHB4OWrU/uwbmO00IoreHW/I2sfgqZfgTZQ=
*/