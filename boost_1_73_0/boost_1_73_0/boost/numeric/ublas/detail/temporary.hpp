//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef _BOOST_UBLAS_TEMPORARY_
#define _BOOST_UBLAS_TEMPORARY_


namespace boost { namespace numeric { namespace ublas {

/// For the creation of temporary vectors in the assignment of proxies
template <class M>
struct vector_temporary_traits {
   typedef typename M::vector_temporary_type type ;
};

/// For the creation of temporary vectors in the assignment of proxies
template <class M>
struct matrix_temporary_traits {
   typedef typename M::matrix_temporary_type type ;
};

} } }

#endif

/* temporary.hpp
W7C0ME7uRQOqEE2ZQZHcIEhMkd04H3UiNYiczMl5xpQmh41mgvcJG0GjrJTxYeCTUglIbhJWJmsCSjQUWtfqTRimjSwp+jATqQrTLv1+oauHTK4oiCq5B1Fr0AIahQEYzQAqkbHcrEQICetmXTJVBI/REBTPQiFBYVkaX2THULmwES5aegKjBjVFzLRZlODKQN0WotpRJB6Nl7yRnICIB1LKBNEcQMMzlFbZZt5BtJxagr9Zmsd4MxCcgoG96AKmF3uwThRTAXycrt4vLlfwMVouo/nqChanEM2vjLM/pvMxlZ4RmAS8qyUqApfAqrpkmLWYP+4JvZ8ZT8smQ9jTqKhUe94TkZZJika+K6bmKHellD8vKd5daYVVhutm4zxnmDOOsJpcrOL30fwsXk0/TAwXvwwo++FgMPC80NJ6ZvofFOMbarHL5QxuiRTRaFN8mhR+z3AReh7j1EcUj58WiYQD0ux5/3oAI2NzkMJbmF/OZket5AMcVFsiY0wUk2Tw8NlwTqAkGhpRJhrT46ngnFBjzSo02v3B1ma2LmOsFSsFP/KM+PHbuOl0wYS1uxu+hddu+4s5piX6vvPZ88kMXoK/pR2Saq8H76DTIZWeBVSaTm9sWDABUvS+k29KsU7KmHGmfZN9fDZbnESz
*/