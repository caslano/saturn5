// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_OUTPUT_SEQUENCE_HPP_INCLUDED
#define BOOST_IOSTREAMS_OUTPUT_SEQUENCE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <utility>           // pair.
#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>  // is_custom 
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename T>
struct output_sequence_impl;

} // End namespace detail.

template<typename T>
inline std::pair<
    BOOST_DEDUCED_TYPENAME char_type_of<T>::type*,
    BOOST_DEDUCED_TYPENAME char_type_of<T>::type*
>
output_sequence(T& t)
{ return detail::output_sequence_impl<T>::output_sequence(t); }

namespace detail {

//------------------Definition of output_sequence_impl------------------------//

template<typename T>
struct output_sequence_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          output_sequence_impl<direct_tag>
      >::type
    { };

template<>
struct output_sequence_impl<direct_tag> {
    template<typename U>
    static std::pair<
        BOOST_DEDUCED_TYPENAME char_type_of<U>::type*,
        BOOST_DEDUCED_TYPENAME char_type_of<U>::type*
    >
    output_sequence(U& u) { return u.output_sequence(); }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_OUTPUT_SEQUENCE_HPP_INCLUDED

/* output_sequence.hpp
8vnJPNZa7EqkMQTYfJSef5zEMzNDBz5ZYd48j6Xt9u/82t88h0KwfMlhlWQ1aB+71b3DCayo4zWvA84sZ/gkS51LqSviTh2TSfoygxhmBLn085dV9IqyWLqPfAMFCJGz3cRydY98r+B7zf44e47NoFGjL+1pDzs+YpNNCIGraAabw5G9ElUo0p33VOsGZLfyzXEorec70r1Vz894yKL/4SM9w3XIBGkidIp+OC0cr7Aknzd/+LxwFOp35SKXeNDyEO75PXvkn8f36BzZJyxDcMhMVUQf3vhmqQBzOo5920mQxLMu4TSqBdUABNmnCnqVCBaNXqeCgU4hhLO84F1+RiJQcs7upfk0N1y6RGXNZ7MttH8liSwTAmnCPfon3x+dT2lnhXLyI8ouwqGlHHq3qfByDcVYz9SLL6yunGCKOsKtzPIdd0STlhxiNKuw4uYcUIWqlV6YO/7XCHdL0HAGn9hYNPTln5R5mHe1vfcs6moZtSlILRpag8o4owrhUCFB0EhAKzggQVmx8euBerHkS5gd5tdwLEz3RmxG6SMqkNVcJLWqQYfN6COvlQ==
*/