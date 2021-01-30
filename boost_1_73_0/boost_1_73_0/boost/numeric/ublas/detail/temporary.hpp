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
8bfZIBBG4yk4Pbo5e20XwR4+n8woql9vmNt4ECECDU06QltC6cxM+WKgLFpPI7cYXrMR4twjb2jjZzOx
*/