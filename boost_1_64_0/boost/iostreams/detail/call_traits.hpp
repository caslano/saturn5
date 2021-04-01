// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename T>
struct param_type {
    typedef typename mpl::if_<is_std_io<T>, T&, const T&>::type type;
};

template<typename T>
struct value_type {
    typedef typename mpl::if_<is_std_io<T>, T&, T>::type type;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED //-----------//

/* call_traits.hpp
VOkhORFS4HMkStbp7e1aXVLCH5gsZAIti8agCGs4GWfRxqUP0GbC1xtH79t0NbxNaa1FaG6z/NbBwrnWu3IuAxlxCzeTvceBH1yYjv0iV5Ufc00laMwSuTUHwi8pqRTmQPAGE1qxvLc0Ed092KByDbe4rfPqoNlwXAVdGyGMcicTb87peDuauwcJ9HPo2tn5M+Mxj3WwO6lQ42UJUGfkjGQaJLU2KoFAh9Y60jksylRrkn0gool6MrtlnFLrqWLJ2ubWz3ocoSQdvIe2+BHVd7DC5eEIwLB+r35nELDNmWV8kWme11RDNhX/nMpiDvMKfkzm/TTzSBJAXzRCwNFK5BETxTTcLgo8BUIDFVNizct17CL4vbeZ/d7m4xMbMQy4Vjxt4OU79+xu6/Cj6KRfVBufGSNWp1YIDrma2KHL8k4Lnh8EH2UexJg5CUb9QyAcnlx7DBpDhOAmxWl74nTWY/MSyduQlwX9ZlM8BKWhSngtlq4WdoCP6X93mZ/WRo/I3xrWrOHWblzyDMw2FaTDtSaHsXrAkw3IPVtTaxoAri/2i7vQPKjRH5LQCQ==
*/