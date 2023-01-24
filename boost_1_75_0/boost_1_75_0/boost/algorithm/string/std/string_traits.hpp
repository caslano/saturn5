//  Boost string_algo library string_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_STRING_TRAITS_HPP
#define BOOST_STRING_STD_STRING_TRAITS_HPP

#include <boost/algorithm/string/yes_no_type.hpp>
#include <string>
#include <boost/algorithm/string/sequence_traits.hpp>

namespace boost {
    namespace algorithm {

//  std::basic_string<> traits  -----------------------------------------------//


    // native replace trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_native_replace< std::basic_string<T, TraitsT, AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true } ;
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )

        typedef mpl::bool_<has_native_replace<T>::value> type;
        };



    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_LIST_TRAITS_HPP

/* string_traits.hpp
gmM7iUvoKPMvR1zjHP6jjEfCUMVuk/XbcDIH27lhNiojyETJBE5cXeQiL9uHPidkwHKf90soHfC0BtP+yPXLY/k0kIf6z8Lwmy7PV70FtXb3WaSM0kOWCTjN7d85+iVluTFO2/YhJjFP7TsjNBKY60JmkkNHMtKz0yhnb3LJujkkew6r0GuUIGH2HtHrAiXi0FyhArtOEWqtILhTpgj+Ketyv6j671fnMHAw+GccRDk6f37lDce7sBPlEJx9ttIGPH5Hb0D4cLmc9UfUqfDbe+B1DgxjmcLpY9O9AYZ90kKUzrvwRfYWRrtvfXelTWqqtcyveemwFWo4BcJuJ2/Zt41fKxpD3lJ9s8vGdUnz+Yo/bKY23tno9yNFnXr+V0siYcTEVkCN0LGWuX+b8TilLvKvLlA9fzDmRkSmn6uzMuaHoC4J2ICGdK/vWN4j5rvIs3S/tYE7tynBjwxgAoyx2hiuVayzPEthd0j4551KDxmnedPGED5XkJRQ2Sd+Q0Vu0jrgghEBxcVE33fgU0tD0cDdAgBPuLnjH4vx+kxe+/3vxnQ1EzY/Y7/uJps1+JUQeTGZUm3Pju4rte5l5GAGS7THMfDRDTvlHa0ekr2WgGcfA0D1r+DXdN4r4uZ9j/4m3OummFpq6dD29mIEic+w9Xd8o20fvVkLJUDByarvCXYl8sWPSXKrFTU+mtbaAbEc7e9asIj788Y1ddO1
*/