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
7yh/aRG0XPdPBXbA/Ftscz4DuPj6cdr02Y1h32OfQ1983rE9mpU/tx8avC867zQ2KNvUh62tlYb258oWSOO45l8LvVlwfR7h/d3G8Pu7ukYvHGuG7AGd+BrOOz7EDtyo2qhoGKDpvrdRxwmZj3a59wOXVtmmubQ/8stHW69qQr5OH/9kY/hddz1sJ38G+8e1/I139267WpXvHrf9v3T6+u0bq22jf+3Y1scxt442BTw31xTw
*/