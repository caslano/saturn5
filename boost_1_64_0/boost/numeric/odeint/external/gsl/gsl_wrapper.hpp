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
+1PgBep4FHT7CPN7ZnBMMn35dmFfZ0MeqNuXoUu7hfEb9V3dinEvCbmepdR3ToZuxWDP7jH4d51r/r4kxqMTaIz7PPQtcUH+Mn/b43//411BnHcu4999KPsE1CN+GNqM/KarTgX8OIz/pzLe1WjTi6j9+kHzD9eBb/gbizHG/e5m5IcNLZ+K+oWIxjo16n/7XgW5It93oM+5raABPldeCv4+AZtCPtT6udCJ1dAl9MEDkrAxsNXJE2EH4KtG1yNtd/SRadCDvZSafQ54BF9fuJvLODQG/mf5y53XDZ1YFeTnsbHm70fOKc73Ve+B/oD3R2Cj9qwysENug/ymi/GR2vPoFn/eDx4Ink+Av7XAvG84ify0KdRWwndbBZt0zZhA8QYP9njt3ub3xz8EHwR1jsI+NVRAz7qUWlOFvLBlr+6gvnwn8iBd/vvqNtg5tOknFgIPduSotFIfw7ifg92rOQTymIO+CbtxDMbc916oRvw3vxN2jeYV3xr0p7U6NPFoG3xvAT/qFsgUPla0s3g5T0Af/x6xxhHYjzfvgY9/m1VH6Pvnl6HPnsGw64i3LZDJK7eibh/155kB/DXLzO/sJebve9D/wpcjL3zd5g9j3LsUugk9umODUpcPg84N4AG6OeeTsDuQweHCh+5NoU6QdQtwN0DefXdYJhF96nXQWo6x5sRh6Cf0NQ378SBswTLSo1cK9P/vwJ6txFjXPwE6eTV06zDysRvgX4HfzmvQV0C3fnMw72zYlw9dR7q23JIx2dVTh8zfMHT+WZo3Hbye2vjoIM3nINPFF/H7DtT7rTy24b6N5u8em4JpF+wFP4z88yuq/Wn7W/bu07BF7z+C9Af5XhR9/TKyrW4Xeiaq1BDkdVGVn8bNNbC/0O+vAF/+u+RMmvMKX/azpEcrphXWz23o37nawumvnQGejkFbfYradndV0r9vg49fzleqohL+0d2QIWzI/bARHeSHTj+Lca+Yrkr6t4nmEw8UqY/WJ2ETP4n6fQTjRTIM/Xwf5In6bCbZlR8O3m4UPi/ZqF/Xw0++nsY6ZwyZbH5/7Tjz9+2D4Qsl0E9hr54+hvOPfwD+2zgal8NkK29Beci/G/Tqz+Phj6bQB7tRFp5OKuP3N0E2H8OYvQ54ZGOT9xeu37PUX+P3Wnb2dtjE44P4h5P/+OUIdELocPL9qCvKnXe5H/+ZtP+9+lKy3ZeQTjRBX7PwF8nnXQL9aURb/wr0/oJ1k8f3MvATD4V+XYg6zUA69Oc+2L0d0P9b1sCvuhPystaWXsK85Z59MQ4K2/++G9FOV0DfwePm+bCl2+BbU/qKE6Cb0J0UfPAzQfvohbB1wP96DPPWO2DD0M6Pyrntan95v0thDoLyjj0ZPif8y2H4cy/kOH3yRbAHIbK/5wbluvetyLcP7HYnfBmU92IZ9PommguPgQ6tgL1eib55FvgC/LSl0N0D4Z8/BPmFoPfQo8EM+Ef9zoetOPdG5LsMNnh31JvG2LPuhr4Nwp+IwM+gOf33qR4/vQT8O3MyawzaMy3m1YvhYzShLPjqV8YgI/w9ZKlJO+UgyPpIf977UYd+8NWB8pdDNn9DG37kEPCIMl/dBLmifTfAB7oJPN4zH7YaPK39JM0PPsx0tvcrFd3opx1hn83gI99Rc2Anz0QbXAW9noR53KE0x6Z1qMoNalT/9r0W7ezoC8aA7BLI1FkjWAwdvhL6hbZIQ0fab6BxeBGVhTY/splprLmYxozp0CuMU0/tD339GPwwzAce7vKXN+dBy0YJfuv2pXGlHGNHC8ZI6MNK8PC8saU85lJ/WXgS+H7I6utEf+9eNap/VWjH9dXoMwvEGPGJIF7znfB1LoE=
*/