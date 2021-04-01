// ----------------------------------------------------------------------------
// workarounds_stlport.hpp : workaround STLport issues
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// see http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_MACROS_STLPORT_HPP
#define BOOST_MACROS_STLPORT_HPP

// *** This should go to "boost/config/stdlib/stlport.hpp".

// If the streams are not native and there are problems with using templates
// accross namespaces, we define some macros to enable a workaround for this.

// STLport 4.5
#if !defined(_STLP_OWN_IOSTREAMS) && defined(_STLP_USE_NAMESPACES) && defined(BOOST_NO_USING_TEMPLATE)
#  define BOOST_IO_STD 
#  define BOOST_IO_NEEDS_USING_DECLARATION
#endif

// STLport 4.0
#if !defined(__SGI_STL_OWN_IOSTREAMS) && defined(__STL_USE_OWN_NAMESPACE) && defined(BOOST_NO_USING_TEMPLATE)
#  define BOOST_IO_STD 
#  define BOOST_IO_NEEDS_USING_DECLARATION
#endif


// ----------------------------------------------------------------------------

#endif // BOOST_MACROS_STLPORT_HPP

/* workarounds_stlport.hpp
Lb78i4/gNb9wsOFGsCjqH6SGmTcIHMqhajxe5GQ1fNUP4fIlO5UKpCkKn2/F7q6+MrmHVzykRkJnlj5JbvytL5BpgBfXhQZsiDDjP8eF1HlriQpZvAc08KJCG5QUfIyVQXWFWr+D6El1XRQE1EraAc+d7I8kwg17DxIYWqOw8+FX7R08N1552hBYUmEq4YPsCYqbpiJSfFp80K5hTGeuDcxlAG6lp/NqOevzNLJWSh1Pz2zv6ZvZ+X1ti2JfbeqWhjfQWQPr5mb/AngMU15BsK/8NkWZLW34/R6L2WuyRDrLJ9djepf1UB4ZsKLo6CfaqWc9nCVOHL1V5Rh0S5dOdCmCYDHsRkpqELRJPW0r3jB51ODM10uNtKUP2/onw6ZlXRNqADf4dzazNrwBMT0jZk+ntW9gfsHWoOjv15oQ+gM30MqXNXnTU1v1b6y3qMfvoOl4GlvRYwG27rOJPTdPYKn5qQW5h0QQI2vS+YjptdOvqXMHezNKFmpcb+JAILL3nTPdPzdZOdFF/bQeIxF5ZOTIY+xYgWceAh5OWM1pdn+BuGC22WEmaKbSZQ==
*/