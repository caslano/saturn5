/*
 [auto_generated]
 boost/numeric/odeint/external/vexcl/vexcl_resize.hpp

 [begin_description]
 Enable resizing for vexcl vector and multivector.
 [end_description]

 Copyright 2012 Karsten Ahnert
 Copyright 2012 Mario Mulansky
 Copyright 2012 Denis Demidov

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_RESIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_RESIZE_HPP_INCLUDED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>

namespace boost {
namespace numeric {
namespace odeint {



/*
 * specializations for vex::vector< T >
 */
template< typename T >
struct is_resizeable< vex::vector< T > > : boost::true_type { };

template< typename T >
struct resize_impl< vex::vector< T > , vex::vector< T > >
{
    static void resize( vex::vector< T > &x1 , const vex::vector< T > &x2 )
    {
        x1.resize( x2.queue_list() , x2.size() );
    }
};

template< typename T >
struct same_size_impl< vex::vector< T > , vex::vector< T > >
{
    static bool same_size( const vex::vector< T > &x1 , const vex::vector< T > &x2 )
    {
        return x1.size() == x2.size();
    }
};





/*
 * specializations for vex::multivector< T >
 */
template< typename T , size_t N >
struct is_resizeable< vex::multivector< T , N > > : boost::true_type { };

template< typename T , size_t N >
struct resize_impl< vex::multivector< T , N > , vex::multivector< T , N > >
{
    static void resize( vex::multivector< T , N > &x1 , const vex::multivector< T , N > &x2 )
    {
        x1.resize( x2.queue_list() , x2.size() );
    }
};

template< typename T , size_t N >
struct same_size_impl< vex::multivector< T , N > , vex::multivector< T , N > >
{
    static bool same_size( const vex::multivector< T , N > &x1 , const vex::multivector< T , N > &x2 )
    {
        return x1.size() == x2.size();
    }
};


} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_RESIZE_HPP_INCLUDED

/* vexcl_resize.hpp
3q2ME++Xc/+qV6CQm9y1M51dMeCa3y4pUpV1y18Ciir0juUfXeqVLbjRZt0SRgIMvjsiH4FQ92uU4xbcBpbPdqpveDafVSSSVQQWFcYX79JX/z3prlvjAX3178rhp/K/LaVatVJrdeP9aq0+vFat1QHoEX8E7Wa7p2YLTRyxFz2TspcuikLkXL1IBvI+V8RJDUhCfjb5spJSlucJp054/wVFoY3YGLYRK+JG7Hri0Vki3VPQlTZij0xgVQA5Uz79jboRixxNfjxF24gVAzZiAf9pTOakVHEDMJ8si+ovux6F5Bp7SplN1SOzqiSwnVgMwp1YGzMux61Ym0ks1xLjVuEyqpd3ZCyJhDb4SUyXWolsE/a2KBszWJcfTL1MAh87yEgC4QcamSzpr267uhlxKOY1EOkvgEr/eCertLXkL9YiFvlbp1qNDFG+dB3VPCsz3fskopJOqIxLSMaOjhQ0aTXeuoWJqVVKunRQ/vZmwidD5Mj00pD5M7leqSSk6Yzj39ijWhocPddXVwUtXbf9+9qQMocF2dcdQy9r6oSr7tJ1e+3vCjiDzWj+ykSNecyUb+rHmEeOXLtOYx5DuD7vF515/FxMZG8qEdjNHrfk8Zs95q7jzOOjPurNHgf/xXWq7joFlaphicSdLey+nekSv5Tn2NpAy3/JLmrqepGp61f9K2gfUa/B7X0CtMLO61X2d5NegzWsBrEBNUhg
*/