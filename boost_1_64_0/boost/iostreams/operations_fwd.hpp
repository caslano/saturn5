// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_OPERATIONS_FWD_HPP_INCLUDED
#define BOOST_IOSTREAMS_OPERATIONS_FWD_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost { namespace iostreams {

template<typename T>
struct operations;

namespace detail {

struct custom_tag { };

template<typename T>
struct is_custom
    : mpl::not_<
          is_base_and_derived< custom_tag, operations<T> >
      >
    { };

} // End namespace detail.

template<typename T>
struct operations : detail::custom_tag { };

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_OPERATIONS_FWD_HPP_INCLUDED //--------------//

/* operations_fwd.hpp
CpRzTJ4aU/SYQ01Vlrc4b/fqv/CbsoVdue+Kr0DQTszER44vbpVTpK90vW80lI3+arpQ2yKuhZbmZ7+QoSEvns0gTxiAM2u0BmpS6YSAIO9jTOhnbRdZX3qHx5kqDvVJYzl4SJBLIFrbp7vcDwXqMQQgOrexPqDIbhkst5nDH8q6MWx24nLBCmSN/Zy8k6wdYFusEy5br5Pt1osZ9eOwxrt/CNRvf/ukVKKBhab5RPX8SfSJ/7jHYGZ1URqtpmO2jN9jVcG+z1Aqwcqywp8PuOFfSIbe38JusjskfECnEpifh5RK4ui24/UzIdLAhXypR0Zle8PO/adgIqqvzrR1xLbPXyA32+AgkWBtKWf1/03tHlAuUZlzeAqU1ECAfqN6XvOe6nwpRPZ3VbV0nI+0WWOjPOZeP+WYMjwmbjv9cJzjXER8+cFS9N3gIe5VVWnN3u8INOM4LCzeYfGwjEQGomy/a7r7zA71BNwq8r3h7iWB+T8BlopWzhyv9u8pF8PV27dRm4n6Oh6NcqjupJU820jXKtYDUbddseUSAza3Vj3wLAEnOrCeoHfExg==
*/