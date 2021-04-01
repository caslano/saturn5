// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_DEDUCED_ITEM_HPP
#define BOOST_PARAMETER_AUX_PACK_DEDUCED_ITEM_HPP

#include <boost/parameter/aux_/void.hpp>

namespace boost { namespace parameter { namespace aux {

    // A typelist that stored deduced parameter specs.
    template <
        typename ParameterSpec
      , typename Tail = ::boost::parameter::void_
    >
    struct deduced_item
    {
        typedef ParameterSpec spec;
        typedef Tail tail;
    };

    // Evaluate Tail and construct deduced_item list.
    template <typename Spec, typename Tail>
    struct make_deduced_item
    {
        typedef ::boost::parameter::aux
        ::deduced_item<Spec,typename Tail::type> type;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* deduced_item.hpp
UKjPVE2m02vdkC3Na6cITBvTR4P9Ao9H7dZ4SUiX1hE4TZUOFKOmwMUZAIvh/xi9r/1XYYn6mZ9oa/NeBizSc0n+FlhqP4m4qgwUNQpySLmZuZgntTvwZ6fr49ssF22eeQpqz+LA+n8IdKDUx/tXLaJD/N7okQqKjlDjkP+kuBlvH7ldtt9h6NSVx30+mQ3///M4aiYyG38nRJh3/HKZWpOra/K06y4a1xltMmfOWUKlYzK3IaCD3w+RNueujTT0hzoIu7RjS4RURMXMMKq6YM6xqwuc40MNldlu5B8liPu3G4zGjLfZ8ZiagN40jTnfVADfrtgly7osbCSmIHztD/UHStOLu6rCVN7S/3s6hLAOX62H1CV9tI6gL2H6QRzCQyWE4jUyTeVGYPaAT4ri2hE99k2TfL9j81i5IfiZJKm5hK074K6bK/tgED5Ee9u8wfgFSA5xWK7dlp1sglNvbHO8j/8LIDuoFChGB1qMelIyUnl7E9AglN4AvVlqKHCGQmCFOaiqlgCt8wzwcUtqJEaJbGsYPwzuC4/vm5iz1gaLC7Rr67Tb7KQuwg==
*/