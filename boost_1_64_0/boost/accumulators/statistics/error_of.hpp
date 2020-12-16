///////////////////////////////////////////////////////////////////////////////
// error_of.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_HPP_EAN_29_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_HPP_EAN_29_11_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    /// INTERNAL ONLY
    ///
    template<typename Feature>
    struct this_feature_has_no_error_calculation
      : mpl::false_
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // error_of_impl
    /// INTERNAL ONLY
    ///
    template<typename Sample, typename Feature>
    struct error_of_impl
      : accumulator_base
    {
        // TODO: specialize this on the specific features that have errors we're
        // interested in.
        BOOST_MPL_ASSERT((this_feature_has_no_error_calculation<Feature>));

        // for boost::result_of
        typedef int result_type;

        error_of_impl(dont_care)
        {
        }

        result_type result(dont_care) const
        {
            return 0;
        }
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::error_of
//
namespace tag
{
    template<typename Feature>
    struct error_of
      : depends_on<Feature>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::error_of_impl<mpl::_1, Feature> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::error_of
//
namespace extract
{
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, error_of, (typename))
}

using extract::error_of;

// make tag::error_of<tag::feature(modifier)> work
template<typename Feature>
struct as_feature<tag::error_of<Feature> >
{
    typedef tag::error_of<typename as_feature<Feature>::type> type;
};

// make error_of<tag::mean> work with non-void weights (should become
// error_of<tag::weighted_mean>
template<typename Feature>
struct as_weighted_feature<tag::error_of<Feature> >
{
    typedef tag::error_of<typename as_weighted_feature<Feature>::type> type;
};

}} // namespace boost::accumulators

#endif

/* error_of.hpp
9954aDoTIOPhLOH5RQAqWl09epQ0IwmQO/iFyLhFgiDyygNY/3+zXqlFtiUU1kYR5uj28wZeactkdx3z6qXSSh5Zlg69Ia2CPwn6gIpQt/BsF/QN44hdCQ9u1wqF2U2lE6Mke3YUSBESScCztLXQZoOSivtEh+nLXQa/01QuUK15tgzgW17vL/S9US07Rn+RquU7WiRlDImjGfQ6clHcJXKjDUwm8yWzf4DcF6ufrpZLZi4ZIyX5Pcd3R6VkeRiXTAjLvga33glhvsbqqe5cJoHL7JLntAmkFqjOwUW5zTF/b325PEJfLpP3HLlfRhZ6UW/0hh/E3mmk1Jk3NA1H++XUdX+frmArINcyel/p73OlWhvGp5N74J/Q3a1ONp39+WFDPfVKD04ZiqqiWdJv1IFFCbYGnRafgZSGUqMLVbLf+mK7353X9Y6RKbPlvZIQYz5b7WxTFjyjPnfO5M9uH7BNsmkfh5XJ7oq2XsrGaTKyFOuKmSCaL30QqOSzqeiUJgGBbdnt9buwVy4x34WJqbfcwpTcDdj++rlVJrQPcnErEOacJQfUCHMlRKH64Ha+5lx5DjWyZw2rArngMC4N2gs8HdRxrA4UA4PcULuxGvBTKX3Eq0IvxySo2dCacC3vyyMZVRpgKTWMl9VRkzvW7gnmSX9Cn97qYtGnTiBLEL+cj9WO7qVRw+vaqNA7/FZ2nnWfinN9iCoNResK3rCo0t3nnpoqETUsqhhOqBSOt4chqpOgFU6qFAZ1q9K/j5K0tQzqYQcW9KFfrVnGjphmpqMPiKVV0QXa10dybQiq1n8T+NpU4vvghqubzwN0K45hy1kYZU3mc8C3LW2m37MZ26z5PC65ynyOwOpPyNBeJmTpf1SbWc6/k/jHequzbWcPvc8ZYiIoQ0yD1lPPd9Nv4YxBjMKuNGmxvZt+a1TYhUy3WvEaMKLLHOG+es5ldXP3nfD37CrPj8KTV505X1YyvqUXc/vNrfVyvTl39hoz01AnjtJku7OHpor9RYH6pf2YrUH2w+2G4YuzrclK//MEa2c3X4+/1K/R5TOttPJsuKuOXZBd9elXt1Dbhaeill+me3AxepAiPbBpxyVKB9TX6ECYaIBfosK4A1VebLEJK1fwA221Z68r/45wveuCAXoeINiAz/cWt5YAOau2tvr7JkJeL3Llj0Ih5Pdx/o1qSs+a34h5/K1Lvt50hn4yvs0uqnF8U6qOr0bP+q8EPTK+n8f9hvF99EJrfHl7lhsKkDce5qr5b5H8/oFdKxZpUFZaqYh/YEX6VQ/cWU37odNshUOWqEkMGjMl8DWwkQHeSyJ+RG0YRuNwKeyXCXm5Qc7oj8J8bq0Ihr3+WYnWKEgDaAx+r8diiNeY5OaxwGFASFNPIVhJml3ZadGsTryx5V8qjzYvwr7NzUuwWmZ1BET4NIhbZfvHnargK6VmfMWr/iwwGRTHfocu1Y2KPz2cQf+FrmFl2v6+k6kAIwcmIat4zcXO+v+IS9dV+LLsVfLTv6X4YIUYdaC81BTyxFoaCHSdB7UDNJGvTNW1PTXj0KBrSLB+BWCwJyZkE5UaB2BRwFCqDOyvKWingwaXfvoQpa9TL4Cn0CSdj34iSxGdjvZqOdhj8ZwmxcQfG2dELjUc86OknRrSRfugqz5XK81+G2GWblsL1hT1/Y4vVTeraAn2o7FAMnlOxoGN4u69nOKQh+P2Sdz5WrZ/vIOI+ul7NyqhiaavYNsWfK1pwyyxKbnEJqpeotY0JQkH8MVaHzT8N6E8/R15pcj9k3vqpzhQCak8FhZZ/r3AHgjYqE/bq7ytqdAdyf4fpzGi9T86yP2r4XFbbG9e5m51YxJf8Oj9DIs=
*/