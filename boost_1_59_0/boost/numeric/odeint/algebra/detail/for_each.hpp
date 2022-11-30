/*
 [auto_generated]
 boost/numeric/odeint/algebra/detail/for_each.hpp

 [begin_description]
 Default for_each implementations.
 [end_description]

 Copyright 2010-2012 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_FOR_EACH_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_FOR_EACH_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {


    template< class Iterator1 , class Operation >
    inline void for_each1( Iterator1 first1 , Iterator1 last1 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ );
    }


    template< class Iterator1 , class Iterator2 , class Operation >
    inline void for_each2( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Operation >
    inline void for_each3( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3, Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Operation >
    inline void for_each4( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3, Iterator4 first4, Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Operation >
    inline void for_each5( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Operation >
    inline void for_each6( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Operation >
    inline void for_each7( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Operation >
    inline void for_each8( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Operation >
    inline void for_each9( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                           Iterator9 first9 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Operation >
    inline void for_each10( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Operation >
    inline void for_each11( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Operation >
    inline void for_each12( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Iterator13 , class Operation >
    inline void for_each13( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Iterator13 first13 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ , *first13++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Iterator13 , class Iterator14 , class Operation >
    inline void for_each14( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Iterator13 first13 ,
                            Iterator14 first14 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ , *first13++ , *first14++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Iterator13 , class Iterator14 , class Iterator15 , class Operation >
    inline void for_each15( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Iterator13 first13 ,
                            Iterator14 first14 , Iterator15 first15 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ , *first13++ , *first14++ , *first15++ );
    }


} // detail
} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_FOR_EACH_HPP_INCLUDED

/* for_each.hpp
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
*/