//  Boost string_algo library yes_no_type.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_YES_NO_TYPE_DETAIL_HPP
#define BOOST_STRING_YES_NO_TYPE_DETAIL_HPP

namespace boost {
    namespace algorithm {

        // taken from boost mailing-list
        // when yes_no_type will become officially
        // a part of boost distribution, this header
        // will be deprecated
        template<int I> struct size_descriptor 
        {
            typedef char (& type)[I];
        }; 

        typedef size_descriptor<1>::type yes_type;
        typedef size_descriptor<2>::type no_type;

    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_YES_NO_TYPE_DETAIL_HPP

/* yes_no_type.hpp
t3nbcC9ch09umR+8a2RfZ76u+8Z1hyy7uHI746/BO+hdbrtuF+4tl5yzCHZZ565avrnzwcenJm9K8ytoZqSZ77CXXety7JDvuXQF9u6E04UxL2xemn5HqZS2w+sAsax9a83B92bnQ5f91kNO3NlCR3eUyNpVdjoydHnbmQCxk/4u74qtDV+Y1xaStDiBkQoHddwUuSxdKPoQ5PnKcurWViW5Ies32J2ZxssaXYbpDktdu7LPKwr2gbJChqOe+Mbi8Ed1mRILM7OrbB6sacf98+wvp6OM7RzY7jr7EUkP7xfbrq5OwQb2C3682eag4fuOdB+/OAOz5pZwge+uLRbr1trGl3bRWCjw4zVleBv85x3mV6LA0LAOKhw1o8BgE6DEuiewiD1ALfmoNUXliivq2+09JX87CfBS1mztjuIwG9dt+9W4F/2+KHwt25L/TtUwMkjarR3Wx3K7viIROcEgx0YzcCHggUiclrYFwwtV53NX2Aay5cjC7w6t22yxy9db24zmRiHvwYDsbCY6lG8gFa6/g+DwAPuiHO24pkihh2m3otohry1OSleTrXJg5VbyGVqaVzzfg+kDl+ubyoZAVSXHHCorlpkn93sXuAE9C5OXeGuqvN1AvDtnCxH8yGuRN8bvRI/r/Apcb3F0
*/