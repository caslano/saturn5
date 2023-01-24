
#ifndef BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'size_impl' or the primary 'size' template

template< typename Tag >
struct size_impl
{
    template< typename Sequence > struct apply
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561))
        : distance<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >
    {
#else
    {
        typedef typename distance<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >::type type;
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, size_impl)

}}

#endif // BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
4jA+WjY2x/8e35iIRGh9RfGkE5QUWlWVfza79rA2UdC03IKqaOjW1HBvbeCjZBGmDUo2HxzYQxt4fxrLvMTCfzKp8p2JIGossX8mBM1ANcfVHe3Pp9tqcLT3kxgQuLRQ1ClumHnAnGkdwor+S0Z2UUz9g7BTJ+sXI48Eh55l59ru/T9Un8IcjsMojgeeb69vTtdG99ydJCWdJWMW1RlYYysd3wJ/QoqLSqwL0QU3p1HQqKLc+5OrFNkWk3P8OQCckx8SBNpv/rIY6Lb3T3cBaR4UhpZ4jnW0jk0RrLGmL68PN64LqmUSm295FrKPzzsF5jxqu33MD2DDhzm9HZNsenYRdfmf59WYyxmT8JmZy2NzbJOt9gvLNRNhoduCslTXcOooPtm0Ku1jbCZkZDAmNuDvrUU3Q+Y5of73Lpnm5cptE3QrDkmnX0NPaVBmevcHXpAiutNJOBZnrycueorqQ9Im3xpaC61lLs+DbE9neHJmeOaZ7ZRHcYG1jAVdKprqWQkFKvIJ/cfUIGfkWGIPBm5kTXFxYe3y+szYP5+UY1x7p25uuwAdV1TvpR0A8GqNb4ACN9kn43WhmFD6J6f7iaZCZerlDZcQ+Du2W0xsQthNqY/37HLbbKa+W8mPmSMmDaUM6V35+b30sjIY7G2lOqOycrQIzo+q7xBp2bumZkD72l9s4tLxfkpI6QdrPTcl+zUlw2Nr4grf5a4D
*/