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