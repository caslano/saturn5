
#ifndef BOOST_MPL_UNIQUE_HPP_INCLUDED
#define BOOST_MPL_UNIQUE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright John R. Bandela 2000-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Predicate, typename Operation >
struct unique_op
{
    template< typename Pair, typename T > struct apply
    {
        typedef typename Pair::first seq_;
        typedef typename Pair::second prior_;
        typedef typename eval_if<
              and_< is_not_na<prior_>, apply2<Predicate,prior_,T> >
            , identity<seq_>
            , apply2<Operation,seq_,T>
            >::type new_seq_;

        typedef pair<new_seq_,T> type;
    };
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct unique_impl
    : first< typename fold<
          Sequence
        , pair< typename Inserter::state,na >
        , protect< aux::unique_op<Predicate,typename Inserter::operation> >
        >::type >
{
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct reverse_unique_impl
    : first< typename reverse_fold<
          Sequence
        , pair< typename Inserter::state,na >
        , protect< aux::unique_op<Predicate,typename Inserter::operation> >
        >::type >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, unique)

}}

#endif // BOOST_MPL_UNIQUE_HPP_INCLUDED

/* unique.hpp
VsM6PDpfxA+rqjayDLNqpcorcJW957tqa8veO373GI2lJ3/5KMNG0DWirMP+XPJdU2xQhYSUFJ/bvaYs3Y771MOkU/fyrSNtntMiqJYAjSHpKUk60Usns9toSNCegZtJmrfI8XzILKLe7kJ1c26FklSOEXzzhUvTRfvTENcuZx3laYrZ0PiFuVi2SKPA4BPJofZU9cVZo/duI9JzbR3KabY1w1nCvZX2hhamJZbHbjS10v2DWXm6nqO9VdGvzejz3LSsP3KjcVu4mZUppPvJGyElxOAKsGeEd6SzeTgyB372+QVnEVdW2ri0YHK1BYdK74PMcBs2UZPW1W95kKGk1PJ2Mvmgq5ODEyc1tZffPJ/wfQ+HLP271BpuxBdhirUNa+ciJhaGomwN+X4R5B0KhCslgWsLLvZyoo7j1D9OLNwR+t2qN1RT9bFU0IAT7egVXBRWXXBIdCgu2vRGNaqsQ/ojnewU1J+aW0+YblMLTkfvfOzR7PB/rGmd/FaQik6qmRD2ffnx6adpbL1u0VL2Db7exR98nV6+l0WJrzNNB4mfCTQYAjIITpxc1IvqF/bc01k1v+t3aZYhL6ZHkL3/dG5Rd1mU08DjQXCfw6xp4npgBTPLKU8P5Vj4nj5w2S99OcolAAy+dbvfR18dOsxb+j5fk8OOnGhDcVYX9UN7RLd0dLSekgPRCM52dj/S6AkmvOHekjmhyf9AtCk4
*/