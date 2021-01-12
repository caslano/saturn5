// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_UNMATCHED_ARGUMENT_HPP
#define BOOST_PARAMETER_AUX_PACK_UNMATCHED_ARGUMENT_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct unmatched_argument
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        static_assert(::std::is_same<T,void>::value, "T == void");
#else
        BOOST_MPL_ASSERT((
            typename ::boost::mpl::if_<
                ::boost::is_same<T,void>
              , ::boost::mpl::true_
              , ::boost::mpl::false_
            >::type
        ));
#endif
        typedef int type;
    }; 
}}} // namespace boost::parameter::aux

#endif  // include guard


/* unmatched_argument.hpp
n2EzQj/DZoV+hs357FQ7PnSOYJ2azQsW16wiWJdmVcG6NVvgDMeH9gjWo9m5nOH40F7O0I/dxxn6secxxv3Y50veafn5ksctf4HkXZa/UPJuy1/EOPdjL2Ccv3+9WMYn/hJpX+IvlTYmfqG0M/GXSVsTf7m0N/FXSJsTv0janfgrpe2Jv4px/hx5teSdll8sedzy10jeZflrJe+2/HWSb7T8EuQ4LpEZRH6p4J3ELxM8Tvz1
*/