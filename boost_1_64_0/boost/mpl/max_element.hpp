
#ifndef BOOST_MPL_MAX_ELEMENT_HPP_INCLUDED
#define BOOST_MPL_MAX_ELEMENT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/less.hpp>
#include <boost/mpl/iter_fold.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(max_element)

namespace aux {

template< typename Predicate >
struct select_max
{
    template< typename OldIterator, typename Iterator >
    struct apply
    {
        typedef typename apply2<
              Predicate
            , typename deref<OldIterator>::type
            , typename deref<Iterator>::type
            >::type condition_;

        typedef typename if_<
              condition_
            , Iterator
            , OldIterator
            >::type type;
    };
};

} // namespace aux 


template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename Predicate = less<_,_>
    >
struct max_element
    : iter_fold<
          Sequence
        , typename begin<Sequence>::type
        , protect< aux::select_max<Predicate> >
        >
{
};

BOOST_MPL_AUX_NA_SPEC(1, max_element)

}}

#endif // BOOST_MPL_MAX_ELEMENT_HPP_INCLUDED

/* max_element.hpp
FPHeT2xMniNf4pR1n0hKcuMm64Sj8nSl3Mz+m/gHXQJOnEKYEgXTInkMTlNMUOLiel1pYyoIZNs+icF+3TZSjVNKavMm6yU+Bk/9hEb8pZS+gE2TAFh5DKc3yaqSCZm5DisIcTsSpzWiXccSAMtDASyrKmgJQRI/roocWr95bv79bZjVsBV00oM/mzrh1wN+rL9O/zcKfiHgX/57ffFfAfjOO+uAX+VXU3378skd6cCZxrIy7kKOsDiFWMz4PfJSbfIU/LxMftZHgc36hiURaodp1Xtf1dWeK3+Gf6YY/l/O/DEVM54MayG/2OkX2I3lyJEwaSwRoOpOxaHRLfiRHQly2MpU5zefKqUXbHrPgLqbFwXrtDylyIPfvETe2FMTRRzoFCYCW8WqQUFm//R3gyXqwtdP9Z1F/zrj78HZjTn+b77m/elPyGtNIwcvnVDcp4+wz/mpdt08yttVGL9ofBnx8EGb+vHXdeAricEX2hP9e8wv0b/T90b/HhwDvyEmv1N19G9/zO8RMfhLYvK3R/+2gziswP9XOEaQRv7pnG/f4avN39cJP+jyt8Qt35byaRpqLT/D1uVPiVv+Ms63W9RaPu01Xb5B3PKVG7j8297ayj+UYPyffRmvfAHlU/9rLV/9sel/3PIff4z+11q+h9P/uOVTpP+1lm/8lul/3PJfbkP/PbWVH5Fk+l8Wr3zPJPS/tvIoaf+T65izO175LZwHqKvj4l+Bsn1qww8N2lzgcMtu2f+AuiJOfy4BrFsTdwHaVZu/t+CaWPiu+4Q//btY+MrIvuCXfR4Lv3mf8MPXx8Iv3if8Z57dMfDWPuHP/jAWf/99wt9Wo/3+fcJPfTMWfkd4X/BbfTX8/+0T/qbP3fzxlb118Ed73stu+FvrhA9+44YfXSf82s/c8MfWCW+tdcPv3VMXfEK1G/6NOuEv2eWGz/pbXfC/+8ANP65O/NOj+ntSnfDB193wzeqEX4v1rOE/qqoDnk+2eb34/sE+8hd1pZ+MxPTgldbwhEwTiLK9/dUHWi+ayhUEWwf7opKTIfAE6pZyHf93X5B+OrzO6KchAmU5q7iK9AlrHeMRVj0kBvugsnc/0QZyAcAt+oJ/19djSU3/+r1BD7e+jr4rW7AjMQBNyc/xeOjZlKYrJ9iAwHmL5XxSrx47+n/ub/+1bv1/WzW4wRtoZBe9r0e2n93+CZpwHAH9GA27rSiPqLeFPgxFwGKHXOJtvhQNqWennfsvIgJAItdxW9y2HCE/fB0GMBLdjItDUhbYtzxOTVMpfkTAoWUz4J/1boIT/3BXRN+P2ccud11TBPvrYZlEw5L/D22S9KayE+aLQXlsggu6rW84dxZ8vpw22r7wCUZXgRuMCrrBgMLNF74CGY67tZHMDqFNevtx5476RKoj2mFy4iavz9GcGHd1Cz01vJT1CI5wt33dDud6acOHaCbWa+cnIwfpNaB+58M3txlpoaa9TD4Roej4CLh2hweeYX9WiuGbV6ov6X9y33/gDP8eW1uc+qozopnWiRz4YoYQjCIhGGvewxiUzfaqCtJhKV0Bt4oYmVs3AgIBay5VL4bYQjboD1Yj9HsRrQ6JA9jRytI14NJJV3KBqiSTm/QMLWw4Y8H1BF2Wfvijo1SCS7+fsHVs5x3m298BAk3YyXjP1tXgMmeOnIDVaEksa5S7d71TDhdC5zjlyuk8/LlbB45nziju+A250CDwha9Gx72uji98VHc807o4bscvfRcdDx8FbJM/kTVmahBH1uc+h0pkiXayrtaYGMZ+Qrgbyvf/5Ndbl4fqg/UdpYWkwBd0hdTR4wE1rg88rYmHNXzt8e+JrNoJzNntlT9gXBznMCc=
*/