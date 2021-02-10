// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_TEMPLATE_KEYWORD_060203_HPP
#define BOOST_PARAMETER_TEMPLATE_KEYWORD_060203_HPP

namespace boost { namespace parameter { namespace aux {

    struct template_keyword_base
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    using is_template_keyword = ::std::is_base_of<
        ::boost::parameter::aux::template_keyword_base
      , typename ::std::remove_const<
            typename ::std::remove_reference<T>::type
        >::type
    >;
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_const.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_reference.hpp>
#else
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

#if !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
    template <typename T>
    struct is_template_keyword_aux
      : ::boost::mpl::if_<
            ::boost::is_convertible<
                T*
              , ::boost::parameter::aux::template_keyword_base const*
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

    template <typename T>
    struct is_template_keyword
      : ::boost::mpl::if_<
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
            // Cannot use is_convertible<> to check if T is derived from
            // template_keyword_base. -- Cromwell D. Enage
            ::boost::is_base_of<
                ::boost::parameter::aux::template_keyword_base
              , typename ::boost::remove_const<
                    typename ::boost::remove_reference<T>::type
                >::type
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
#else
            ::boost::is_lvalue_reference<T>
          , ::boost::mpl::false_
          , ::boost::parameter::aux::is_template_keyword_aux<T>
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* template_keyword.hpp
vXt/fLeQkuZuMR/2Tk6PDt/fQXF49/TJyYcHGFxT3a3N6ft/Nqd5to+QMcUUDAY1hivlA/jGM7gHTo8OERfeXCodmj5uxpsJ0tOsykTqHLjQfcU0XeRTLnqTIN2rg9d2IIiVEc5Bv1yGuOKcS6BNwKkYf7OzFYc5cpgjgp3h+dlg/yOSDlGJpJRBHzlznvTmGIP9Utvqk2kMWDg5xb05hu6BNIbzXpnb8YhEsZg3WOmztLu7sriMox9+WA7fdOz3DUVWEAlEPsWGjRqKLCNMh51xzM7gkO1iCXfNC0MpoJvaBM/RimdWLJxXx68rxdEStHKrZOjQZjlHH0+vaceuD/CpPzm7/KEPzuBpf9i0tscB8q03uhn3nu/WalqHH5PDyZUkGINst36hsFu+JTzX0J/y1Lr6MqXkyhu9wYQAa5as3v9ePIbeZLcyrhfD+N8wvN2wp87nZ96Pgy9P60ev8fylZTWjkk5I6OWLDLHZw8MWv0OR4bcWCaHU6Y3wZQf/nuPfC/z7SwXASqvSecjppg2hLYuhLk1StDRpVyBzUz+J2BBTFt9iBsyG8hvOqgt7OhNli8xQXZdu5w2QUVbdLEy0pJBwcgeIP6CLru221eDQKExUA8JlvdwVopuVt9Kmmi3t2z18CVuPZ3xw
*/