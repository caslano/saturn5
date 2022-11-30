#ifndef BOOST_SMART_PTR_SCOPED_ARRAY_HPP_INCLUDED
#define BOOST_SMART_PTR_SCOPED_ARRAY_HPP_INCLUDED

//  (C) Copyright Greg Colvin and Beman Dawes 1998, 1999.
//  Copyright (c) 2001, 2002 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/ for documentation.

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>
#include <boost/smart_ptr/detail/sp_nullptr_t.hpp>
#include <boost/smart_ptr/detail/sp_noexcept.hpp>

#include <boost/config/workaround.hpp>

#include <cstddef>            // for std::ptrdiff_t

namespace boost
{

// Debug hooks

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)

void sp_array_constructor_hook(void * p);
void sp_array_destructor_hook(void * p);

#endif

//  scoped_array extends scoped_ptr to arrays. Deletion of the array pointed to
//  is guaranteed, either on destruction of the scoped_array or via an explicit
//  reset(). Use shared_array or std::vector if your needs are more complex.

template<class T> class scoped_array // noncopyable
{
private:

    T * px;

    scoped_array(scoped_array const &);
    scoped_array & operator=(scoped_array const &);

    typedef scoped_array<T> this_type;

    void operator==( scoped_array const& ) const;
    void operator!=( scoped_array const& ) const;

public:

    typedef T element_type;

    explicit scoped_array( T * p = 0 ) BOOST_SP_NOEXCEPT : px( p )
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        boost::sp_array_constructor_hook( px );
#endif
    }

    ~scoped_array() BOOST_SP_NOEXCEPT
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        boost::sp_array_destructor_hook( px );
#endif
        boost::checked_array_delete( px );
    }

    void reset(T * p = 0) BOOST_SP_NOEXCEPT_WITH_ASSERT
    {
        BOOST_ASSERT( p == 0 || p != px ); // catch self-reset errors
        this_type(p).swap(*this);
    }

    T & operator[](std::ptrdiff_t i) const BOOST_SP_NOEXCEPT_WITH_ASSERT
    {
        BOOST_ASSERT( px != 0 );
        BOOST_ASSERT( i >= 0 );
        return px[i];
    }

    T * get() const BOOST_SP_NOEXCEPT
    {
        return px;
    }

// implicit conversion to "bool"
#include <boost/smart_ptr/detail/operator_bool.hpp>

    void swap(scoped_array & b) BOOST_SP_NOEXCEPT
    {
        T * tmp = b.px;
        b.px = px;
        px = tmp;
    }
};

#if !defined( BOOST_NO_CXX11_NULLPTR )

template<class T> inline bool operator==( scoped_array<T> const & p, boost::detail::sp_nullptr_t ) BOOST_SP_NOEXCEPT
{
    return p.get() == 0;
}

template<class T> inline bool operator==( boost::detail::sp_nullptr_t, scoped_array<T> const & p ) BOOST_SP_NOEXCEPT
{
    return p.get() == 0;
}

template<class T> inline bool operator!=( scoped_array<T> const & p, boost::detail::sp_nullptr_t ) BOOST_SP_NOEXCEPT
{
    return p.get() != 0;
}

template<class T> inline bool operator!=( boost::detail::sp_nullptr_t, scoped_array<T> const & p ) BOOST_SP_NOEXCEPT
{
    return p.get() != 0;
}

#endif

template<class T> inline void swap(scoped_array<T> & a, scoped_array<T> & b) BOOST_SP_NOEXCEPT
{
    a.swap(b);
}

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_SCOPED_ARRAY_HPP_INCLUDED

/* scoped_array.hpp
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
*/