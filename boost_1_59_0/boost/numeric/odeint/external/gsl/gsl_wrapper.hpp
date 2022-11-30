/*
 [auto_generated]
 boost/numeric/odeint/external/gsl/gsl_wrapper.hpp

 [begin_description]
 Wrapper for gsl_vector.
 [end_description]

 Copyright 2011-2012 Mario Mulansky
 Copyright 2011 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_GSL_GSL_WRAPPER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_GSL_GSL_WRAPPER_HPP_INCLUDED

#include <new>

#include <gsl/gsl_vector.h>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/range.hpp>
#include <boost/iterator/iterator_facade.hpp>


#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/copy.hpp>

class const_gsl_vector_iterator;

/*
 * defines an iterator for gsl_vector
 */
class gsl_vector_iterator : public boost::iterator_facade< gsl_vector_iterator , double , boost::random_access_traversal_tag >
{
public :

    gsl_vector_iterator( void ): m_p(0) , m_stride( 0 ) { }
    explicit gsl_vector_iterator( gsl_vector *p ) : m_p( p->data ) , m_stride( p->stride ) { }
    friend gsl_vector_iterator end_iterator( gsl_vector * );

private :

    friend class boost::iterator_core_access;
    friend class const_gsl_vector_iterator;

    void increment( void ) { m_p += m_stride; }
    void decrement( void ) { m_p -= m_stride; }
    void advance( ptrdiff_t n ) { m_p += n*m_stride; }
    bool equal( const gsl_vector_iterator &other ) const { return this->m_p == other.m_p; }
    bool equal( const const_gsl_vector_iterator &other ) const;
    double& dereference( void ) const { return *m_p; }

    double *m_p;
    size_t m_stride;
};



/*
 * defines an const iterator for gsl_vector
 */
class const_gsl_vector_iterator : public boost::iterator_facade< const_gsl_vector_iterator , const double , boost::random_access_traversal_tag >
{
public :

    const_gsl_vector_iterator( void ): m_p(0) , m_stride( 0 ) { }
    explicit const_gsl_vector_iterator( const gsl_vector *p ) : m_p( p->data ) , m_stride( p->stride ) { }
    const_gsl_vector_iterator( const gsl_vector_iterator &p ) : m_p( p.m_p ) , m_stride( p.m_stride ) { }

private :

    friend class boost::iterator_core_access;
    friend class gsl_vector_iterator;
    friend const_gsl_vector_iterator end_iterator( const gsl_vector * );

    void increment( void ) { m_p += m_stride; }
    void decrement( void ) { m_p -= m_stride; }
    void advance( ptrdiff_t n ) { m_p += n*m_stride; }
    bool equal( const const_gsl_vector_iterator &other ) const { return this->m_p == other.m_p; }
    bool equal( const gsl_vector_iterator &other ) const { return this->m_p == other.m_p; }
    const double& dereference( void ) const { return *m_p; }

    const double *m_p;
    size_t m_stride;
};


bool gsl_vector_iterator::equal( const const_gsl_vector_iterator &other ) const { return this->m_p == other.m_p; }


gsl_vector_iterator end_iterator( gsl_vector *x )
{
    gsl_vector_iterator iter( x );
    iter.m_p += iter.m_stride * x->size;
    return iter;
}

const_gsl_vector_iterator end_iterator( const gsl_vector *x )
{
    const_gsl_vector_iterator iter( x );
    iter.m_p += iter.m_stride * x->size;
    return iter;
}




namespace boost
{
template<>
struct range_mutable_iterator< gsl_vector* >
{
    typedef gsl_vector_iterator type;
};

template<>
struct range_const_iterator< gsl_vector* >
{
    typedef const_gsl_vector_iterator type;
};
} // namespace boost




// template<>
inline gsl_vector_iterator range_begin( gsl_vector *x )
{
    return gsl_vector_iterator( x );
}

// template<>
inline const_gsl_vector_iterator range_begin( const gsl_vector *x )
{
    return const_gsl_vector_iterator( x );
}

// template<>
inline gsl_vector_iterator range_end( gsl_vector *x )
{
    return end_iterator( x );
}

// template<>
inline const_gsl_vector_iterator range_end( const gsl_vector *x )
{
    return end_iterator( x );
}







namespace boost {
namespace numeric {
namespace odeint {


template<>
struct is_resizeable< gsl_vector* >
{
    //struct type : public boost::true_type { };
    typedef boost::true_type type;
    const static bool value = type::value;
};

template <>
struct same_size_impl< gsl_vector* , gsl_vector* >
{
    static bool same_size( const gsl_vector* x , const gsl_vector* y )
    {
        return x->size == y->size;
    }
};

template <>
struct resize_impl< gsl_vector* , gsl_vector* >
{
    static void resize( gsl_vector* &x , const gsl_vector* y )
    {
        gsl_vector_free( x );
        x = gsl_vector_alloc( y->size );
    }
};

template<>
struct state_wrapper< gsl_vector* >
{
    typedef double value_type;
    typedef gsl_vector* state_type;
    typedef state_wrapper< gsl_vector* > state_wrapper_type;

    state_type m_v;

    state_wrapper( )
    {
        m_v = gsl_vector_alloc( 1 );
    }

    state_wrapper( const state_wrapper_type &x )
    {
        resize( m_v , x.m_v );
        gsl_vector_memcpy( m_v , x.m_v );
    }


    ~state_wrapper()
    {
        gsl_vector_free( m_v );
    }

};

} // odeint
} // numeric
} // boost




#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_GSL_GSL_WRAPPER_HPP_INCLUDED

/* gsl_wrapper.hpp
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
*/