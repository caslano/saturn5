#ifndef BOOST_SIGNALS2_DECONSTRUCT_HPP
#define BOOST_SIGNALS2_DECONSTRUCT_HPP

//  deconstruct.hpp
//
// A factory function for creating a shared_ptr which creates
// an object and its owning shared_ptr with one allocation, similar
// to make_shared<T>().  It also supports postconstructors
// and predestructors through unqualified calls of adl_postconstruct() and
// adl_predestruct, relying on argument-dependent
// lookup to find the appropriate postconstructor or predestructor.
// Passing arguments to postconstructors is also supported.
//
//  based on make_shared.hpp and make_shared_access patch from Michael Marcin
//
//  Copyright (c) 2007, 2008 Peter Dimov
//  Copyright (c) 2008 Michael Marcin
//  Copyright (c) 2009 Frank Mori Hess
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  See http://www.boost.org
//  for more information

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/type_with_alignment.hpp>
#include <cstddef>
#include <new>

namespace boost
{
  template<typename T> class enable_shared_from_this;

namespace signals2
{
  class deconstruct_access;

namespace detail
{
  inline void adl_predestruct(...) {}
} // namespace detail

template<typename T>
    class postconstructor_invoker
{
public:
    operator const shared_ptr<T> & () const
    {
        return postconstruct();
    }
    const shared_ptr<T>& postconstruct() const
    {
        if(!_postconstructed)
        {
            adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()));
            _postconstructed = true;
        }
        return _sp;
    }
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template<class... Args>
      const shared_ptr<T>& postconstruct(Args && ... args) const
    {
        if(!_postconstructed)
        {
            adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
                std::forward<Args>(args)...);
            _postconstructed = true;
        }
        return _sp;
    }
#else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template<typename A1>
      const shared_ptr<T>& postconstruct(const A1 &a1) const
    {
        if(!_postconstructed)
        {
            adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
                a1);
            _postconstructed = true;
        }
        return _sp;
    }
    template<typename A1, typename A2>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2) const
    {
        if(!_postconstructed)
        {
            adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
                a1, a2);
            _postconstructed = true;
        }
        return _sp;
    }
    template<typename A1, typename A2, typename A3>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2, const A3 &a3) const
    {
        if(!_postconstructed)
        {
            adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
                a1, a2, a3);
            _postconstructed = true;
        }
        return _sp;
    }
    template<typename A1, typename A2, typename A3, typename A4>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4) const
    {
        if(!_postconstructed)
        {
            adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
                a1, a2, a3, a4);
            _postconstructed = true;
        }
        return _sp;
    }
    template<typename A1, typename A2, typename A3, typename A4, typename A5>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5) const
    {
        if(!_postconstructed)
        {
            adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
                a1, a2, a3, a4, a5);
            _postconstructed = true;
        }
        return _sp;
    }
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
      typename A6>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5,
      const A6 &a6) const
    {
        if(!_postconstructed)
        {
            adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
                a1, a2, a3, a4, a5, a6);
            _postconstructed = true;
        }
        return _sp;
    }
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
      typename A6, typename A7>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5,
      const A6 &a6, const A7 &a7) const
    {
        if(!_postconstructed)
        {
            adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
                a1, a2, a3, a4, a5, a6, a7);
            _postconstructed = true;
        }
        return _sp;
    }
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
      typename A6, typename A7, typename A8>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5,
      const A6 &a6, const A7 &a7, const A8 &a8) const
    {
        if(!_postconstructed)
        {
            adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
                a1, a2, a3, a4, a5, a6, a7, a8);
            _postconstructed = true;
        }
        return _sp;
    }
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
      typename A6, typename A7, typename A8, typename A9>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5,
      const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9) const
    {
        if(!_postconstructed)
        {
            adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
                a1, a2, a3, a4, a5, a6, a7, a8, a9);
            _postconstructed = true;
        }
        return _sp;
    }
#endif // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
private:
    friend class boost::signals2::deconstruct_access;
    postconstructor_invoker(const shared_ptr<T> & sp):
        _sp(sp), _postconstructed(false)
    {}
    shared_ptr<T> _sp;
    mutable bool _postconstructed;
};

namespace detail
{

template< std::size_t N, std::size_t A > struct sp_aligned_storage
{
    union type
    {
        char data_[ N ];
        typename boost::type_with_alignment< A >::type align_;
    };
};

template< class T > class deconstruct_deleter
{
private:

    typedef typename sp_aligned_storage< sizeof( T ), ::boost::alignment_of< T >::value >::type storage_type;

    bool initialized_;
    storage_type storage_;

private:

    void destroy()
    {
        if( initialized_ )
        {
            T* p = reinterpret_cast< T* >( storage_.data_ );
            using boost::signals2::detail::adl_predestruct;
            adl_predestruct(const_cast<typename boost::remove_const<T>::type *>(p));
            p->~T();
            initialized_ = false;
        }
    }

public:

    deconstruct_deleter(): initialized_( false )
    {
    }

    // this copy constructor is an optimization: we don't need to copy the storage_ member,
    // and shouldn't be copying anyways after initialized_ becomes true
    deconstruct_deleter(const deconstruct_deleter &): initialized_( false )
    {
    }

    ~deconstruct_deleter()
    {
        destroy();
    }

    void operator()( T * )
    {
        destroy();
    }

    void * address()
    {
        return storage_.data_;
    }

    void set_initialized()
    {
        initialized_ = true;
    }
};
}  // namespace detail

class deconstruct_access
{
public:

    template< class T >
    static postconstructor_invoker<T> deconstruct()
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T();
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        boost::detail::sp_enable_shared_from_this(&retval, retval.get(), retval.get());
        return retval;

    }

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    // Variadic templates, rvalue reference

    template< class T, class... Args >
    static postconstructor_invoker<T> deconstruct( Args && ... args )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( std::forward<Args>( args )... );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        boost::detail::sp_enable_shared_from_this(&retval, retval.get(), retval.get());
        return retval;
    }

#else

    template< class T, class A1 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        boost::detail::sp_enable_shared_from_this(&retval, retval.get(), retval.get());
        return retval;
    }

    template< class T, class A1, class A2 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        boost::detail::sp_enable_shared_from_this(&retval, retval.get(), retval.get());
        return retval;
    }

    template< class T, class A1, class A2, class A3 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2, a3 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        boost::detail::sp_enable_shared_from_this(&retval, retval.get(), retval.get());
        return retval;
    }

    template< class T, class A1, class A2, class A3, class A4 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2, a3, a4 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        boost::detail::sp_enable_shared_from_this(&retval, retval.get(), retval.get());
        return retval;
    }

    template< class T, class A1, class A2, class A3, class A4, class A5 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2, a3, a4, a5 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        boost::detail::sp_enable_shared_from_this(&retval, retval.get(), retval.get());
        return retval;
    }

    template< class T, class A1, class A2, class A3, class A4, class A5, class A6 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2, a3, a4, a5, a6 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        boost::detail::sp_enable_shared_from_this(&retval, retval.get(), retval.get());
        return retval;
    }

    template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2, a3, a4, a5, a6, a7 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        boost::detail::sp_enable_shared_from_this(&retval, retval.get(), retval.get());
        return retval;
    }

    template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2, a3, a4, a5, a6, a7, a8 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        boost::detail::sp_enable_shared_from_this(&retval, retval.get(), retval.get());
        return retval;
    }

    template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8, A9 const & a9 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2, a3, a4, a5, a6, a7, a8, a9 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        boost::detail::sp_enable_shared_from_this(&retval, retval.get(), retval.get());
        return retval;
    }

#endif
};

// Zero-argument versions
//
// Used even when variadic templates are available because of the new T() vs new T issue

template< class T > postconstructor_invoker<T> deconstruct()
{
    return deconstruct_access::deconstruct<T>();
}

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

// Variadic templates, rvalue reference

template< class T, class... Args > postconstructor_invoker< T > deconstruct( Args && ... args )
{
    return deconstruct_access::deconstruct<T>( std::forward<Args>( args )... );
}

#else

// C++03 version

template< class T, class A1 >
postconstructor_invoker<T> deconstruct( A1 const & a1 )
{
    return deconstruct_access::deconstruct<T>(a1);
}

template< class T, class A1, class A2 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2 )
{
    return deconstruct_access::deconstruct<T>(a1,a2);
}

template< class T, class A1, class A2, class A3 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3 )
{
    return deconstruct_access::deconstruct<T>(a1,a2,a3);
}

template< class T, class A1, class A2, class A3, class A4 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4 )
{
    return deconstruct_access::deconstruct<T>(a1,a2,a3,a4);
}

template< class T, class A1, class A2, class A3, class A4, class A5 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5 )
{
    return deconstruct_access::deconstruct<T>(a1,a2,a3,a4,a5);
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6 )
{
    return deconstruct_access::deconstruct<T>(a1,a2,a3,a4,a5,a6);
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7 )
{
    return deconstruct_access::deconstruct<T>(a1,a2,a3,a4,a5,a6,a7);
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8 )
{
    return deconstruct_access::deconstruct<T>(a1,a2,a3,a4,a5,a6,a7,a8);
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8, A9 const & a9 )
{
    return deconstruct_access::deconstruct<T>(a1,a2,a3,a4,a5,a6,a7,a8,a9);
}

#endif

} // namespace signals2
} // namespace boost

#endif // #ifndef BOOST_SIGNALS2_DECONSTRUCT_HPP

/* deconstruct.hpp
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
*/