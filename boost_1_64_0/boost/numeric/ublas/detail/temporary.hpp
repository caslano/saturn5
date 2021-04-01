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
vdkr8P/a6B7BiA8EZ5MLy1oxMW8Y9wwe6LOpOx6bizJzWyT4Na1EEG2c8Y4ufLJ7sawSQ0V3e4Kn/xQTFVgImN9v3pAQY0CbzybXmGyX1w3LdIuJhJd9/BqucMz2gHuc+cnDSeUraEUFjtPsQYHAEacZ7Wdz+ySV/lBCoMT1bTM5l9+tWdfBBZI1AJKo1VhdBws0BfbByASojFIqL2RAH4P7JExtVnoiUfuFY2Yh2RU6IekJl+YM7KSQrZAejj3XNpVyRS3Nx17DOwwVlBGsf7hzlaA9s27+SeRvoQ+LAS+zpeAbpFoqAZXz5HgWVHWJNb9JjkA/FHm3DFvhfuTDtyxrXFOJaYOZE7z1ZxCnILYpZUYsdldb/W15H50wPEjr11ff7nqzeSwoes3NTvUkeUn+up5K2UGXLuXETSDD/wL5oJNg68mY6DxFHdYu68egoXqSY56PCOxSo4SBi0nvc827VgeacCCsEriQVS9QkRYy6/Xxlw9htHn6qC214AJOFx1QdGx32jEtDCXBS2FC/0Xc+6RKzBGEpC5/XQsRd4vsf5cHNEQdpS5C9Q==
*/