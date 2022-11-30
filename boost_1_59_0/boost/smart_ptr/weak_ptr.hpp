#ifndef BOOST_SMART_PTR_WEAK_PTR_HPP_INCLUDED
#define BOOST_SMART_PTR_WEAK_PTR_HPP_INCLUDED

//
//  weak_ptr.hpp
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/ for documentation.
//

#include <boost/smart_ptr/detail/shared_count.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/detail/sp_noexcept.hpp>
#include <memory>
#include <cstddef>

namespace boost
{

template<class T> class weak_ptr
{
private:

    // Borland 5.5.1 specific workarounds
    typedef weak_ptr<T> this_type;

public:

    typedef typename boost::detail::sp_element< T >::type element_type;

    BOOST_CONSTEXPR weak_ptr() BOOST_SP_NOEXCEPT : px(0), pn()
    {
    }

//  generated copy constructor, assignment, destructor are fine...

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

// ... except in C++0x, move disables the implicit copy

    weak_ptr( weak_ptr const & r ) BOOST_SP_NOEXCEPT : px( r.px ), pn( r.pn )
    {
    }

    weak_ptr & operator=( weak_ptr const & r ) BOOST_SP_NOEXCEPT
    {
        px = r.px;
        pn = r.pn;
        return *this;
    }

#endif

//
//  The "obvious" converting constructor implementation:
//
//  template<class Y>
//  weak_ptr(weak_ptr<Y> const & r): px(r.px), pn(r.pn)
//  {
//  }
//
//  has a serious problem.
//
//  r.px may already have been invalidated. The px(r.px)
//  conversion may require access to *r.px (virtual inheritance).
//
//  It is not possible to avoid spurious access violations since
//  in multithreaded programs r.px may be invalidated at any point.
//

    template<class Y>
#if !defined( BOOST_SP_NO_SP_CONVERTIBLE )

    weak_ptr( weak_ptr<Y> const & r, typename boost::detail::sp_enable_if_convertible<Y,T>::type = boost::detail::sp_empty() )

#else

    weak_ptr( weak_ptr<Y> const & r )

#endif
    BOOST_SP_NOEXCEPT : px(r.lock().get()), pn(r.pn)
    {
        boost::detail::sp_assert_convertible< Y, T >();
    }

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    template<class Y>
#if !defined( BOOST_SP_NO_SP_CONVERTIBLE )

    weak_ptr( weak_ptr<Y> && r, typename boost::detail::sp_enable_if_convertible<Y,T>::type = boost::detail::sp_empty() )

#else

    weak_ptr( weak_ptr<Y> && r )

#endif
    BOOST_SP_NOEXCEPT : px( r.lock().get() ), pn( static_cast< boost::detail::weak_count && >( r.pn ) )
    {
        boost::detail::sp_assert_convertible< Y, T >();
        r.px = 0;
    }

    // for better efficiency in the T == Y case
    weak_ptr( weak_ptr && r )
    BOOST_SP_NOEXCEPT : px( r.px ), pn( static_cast< boost::detail::weak_count && >( r.pn ) )
    {
        r.px = 0;
    }

    // for better efficiency in the T == Y case
    weak_ptr & operator=( weak_ptr && r ) BOOST_SP_NOEXCEPT
    {
        this_type( static_cast< weak_ptr && >( r ) ).swap( *this );
        return *this;
    }


#endif

    template<class Y>
#if !defined( BOOST_SP_NO_SP_CONVERTIBLE )

    weak_ptr( shared_ptr<Y> const & r, typename boost::detail::sp_enable_if_convertible<Y,T>::type = boost::detail::sp_empty() )

#else

    weak_ptr( shared_ptr<Y> const & r )

#endif
    BOOST_SP_NOEXCEPT : px( r.px ), pn( r.pn )
    {
        boost::detail::sp_assert_convertible< Y, T >();
    }

    // aliasing
    template<class Y> weak_ptr(shared_ptr<Y> const & r, element_type * p) BOOST_SP_NOEXCEPT: px( p ), pn( r.pn )
    {
    }

    template<class Y> weak_ptr(weak_ptr<Y> const & r, element_type * p) BOOST_SP_NOEXCEPT: px( p ), pn( r.pn )
    {
    }

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    template<class Y> weak_ptr(weak_ptr<Y> && r, element_type * p) BOOST_SP_NOEXCEPT: px( p ), pn( std::move( r.pn ) )
    {
    }

#endif

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1300)

    template<class Y>
    weak_ptr & operator=( weak_ptr<Y> const & r ) BOOST_SP_NOEXCEPT
    {
        boost::detail::sp_assert_convertible< Y, T >();

        px = r.lock().get();
        pn = r.pn;

        return *this;
    }

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    template<class Y>
    weak_ptr & operator=( weak_ptr<Y> && r ) BOOST_SP_NOEXCEPT
    {
        this_type( static_cast< weak_ptr<Y> && >( r ) ).swap( *this );
        return *this;
    }

#endif

    template<class Y>
    weak_ptr & operator=( shared_ptr<Y> const & r ) BOOST_SP_NOEXCEPT
    {
        boost::detail::sp_assert_convertible< Y, T >();

        px = r.px;
        pn = r.pn;

        return *this;
    }

#endif

    shared_ptr<T> lock() const BOOST_SP_NOEXCEPT
    {
        return shared_ptr<T>( *this, boost::detail::sp_nothrow_tag() );
    }

    long use_count() const BOOST_SP_NOEXCEPT
    {
        return pn.use_count();
    }

    bool expired() const BOOST_SP_NOEXCEPT
    {
        return pn.use_count() == 0;
    }

    bool _empty() const BOOST_SP_NOEXCEPT // extension, not in std::weak_ptr
    {
        return pn.empty();
    }

    bool empty() const BOOST_SP_NOEXCEPT // extension, not in std::weak_ptr
    {
        return pn.empty();
    }

    void reset() BOOST_SP_NOEXCEPT
    {
        this_type().swap(*this);
    }

    void swap(this_type & other) BOOST_SP_NOEXCEPT
    {
        std::swap(px, other.px);
        pn.swap(other.pn);
    }

    template<class Y> bool owner_before( weak_ptr<Y> const & rhs ) const BOOST_SP_NOEXCEPT
    {
        return pn < rhs.pn;
    }

    template<class Y> bool owner_before( shared_ptr<Y> const & rhs ) const BOOST_SP_NOEXCEPT
    {
        return pn < rhs.pn;
    }

    template<class Y> bool owner_equals( weak_ptr<Y> const & rhs ) const BOOST_SP_NOEXCEPT
    {
        return pn == rhs.pn;
    }

    template<class Y> bool owner_equals( shared_ptr<Y> const & rhs ) const BOOST_SP_NOEXCEPT
    {
        return pn == rhs.pn;
    }

    std::size_t owner_hash_value() const BOOST_SP_NOEXCEPT
    {
        return pn.hash_value();
    }

// Tasteless as this may seem, making all members public allows member templates
// to work in the absence of member template friends. (Matthew Langston)

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS

private:

    template<class Y> friend class weak_ptr;
    template<class Y> friend class shared_ptr;

#endif

    element_type * px;            // contained pointer
    boost::detail::weak_count pn; // reference counter

};  // weak_ptr

template<class T, class U> inline bool operator<(weak_ptr<T> const & a, weak_ptr<U> const & b) BOOST_SP_NOEXCEPT
{
    return a.owner_before( b );
}

template<class T> void swap(weak_ptr<T> & a, weak_ptr<T> & b) BOOST_SP_NOEXCEPT
{
    a.swap(b);
}

#if defined(__cpp_deduction_guides)

template<class T> weak_ptr( shared_ptr<T> ) -> weak_ptr<T>;

#endif

// hash_value

template< class T > std::size_t hash_value( boost::weak_ptr<T> const & p ) BOOST_SP_NOEXCEPT
{
    return p.owner_hash_value();
}

} // namespace boost

// std::hash, std::equal_to

namespace std
{

#if !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)

template<class T> struct hash< ::boost::weak_ptr<T> >
{
    std::size_t operator()( ::boost::weak_ptr<T> const & p ) const BOOST_SP_NOEXCEPT
    {
        return p.owner_hash_value();
    }
};

#endif // #if !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)

template<class T> struct equal_to< ::boost::weak_ptr<T> >
{
    bool operator()( ::boost::weak_ptr<T> const & a, ::boost::weak_ptr<T> const & b ) const BOOST_SP_NOEXCEPT
    {
        return a.owner_equals( b );
    }
};

} // namespace std

#endif  // #ifndef BOOST_SMART_PTR_WEAK_PTR_HPP_INCLUDED

/* weak_ptr.hpp
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
*/