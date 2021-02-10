// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

#include <boost/config.hpp>                     // BOOST_STATIC_CONSANT.
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Device, typename U>
struct forward_impl {
    BOOST_STATIC_CONSTANT(bool, value =
        ( !is_same< U, Device >::value &&
          !is_same< U, reference_wrapper<Device> >::value ));
};

template<typename Device, typename U>
struct forward
    : mpl::bool_<forward_impl<Device, U>::value>
    { };

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

/* forward.hpp
+bbo1W5YWQPqdby/AVBLAwQKAAAACAAtZ0pSX4pORucDAAA7CAAAIwAJAGN1cmwtbWFzdGVyL3NjcmlwdHMvY29udHJpdGhhbmtzLnNoVVQFAAG2SCRgrVTbbts4EH3XV8wqAewUusTZt9QpajjeTdDCKWIHRlDXLi3RFheSKJCUL4U/fg8l2XGKFnmpfCE5mjln5nDIs7/ChchDnThn7/7c45zRm8+8+s3xYLQBX5T8j0fm187z+Z7qD4KmGN+gCOklYj+/oDcj9tSuIuYNR9fO5/M3aKY2MfsX2sDp3E5hcc4Q15fFTolVYqjdv6Cry87f5GO4uvToluWCpzQyPF9wtfKoG1eWjwnbbgPNP3jEDbE0qIDGidCk5dJsmOKEeSoinmseE9MUcx0pscBC5GQSTkuRcuo/fHm+H/7r0SYREfaWdrIkncgyjSlha06KR1ysa4iCKUNyiWhgx0Ib4JVGyDwANSfDVaYBYclZqiWxNRMpW4CGGUqMKfR1GEalSpF5GMtIh9Gh9CAxWVPFMzLI2I5kYchIKjX3yPp5lMlYLO0IKWAsykUqdOK9pAKiPA6lIs3TFFAIE1zXKXMaNcp41osKZCuMHbTMtWXaJDJ75QgJAbIsVQ4aSACfWEJgj8o85qryrYo+MDRq
*/