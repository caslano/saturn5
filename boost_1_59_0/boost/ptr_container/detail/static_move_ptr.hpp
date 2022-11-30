// (C) Copyright Thorsten Ottosen 2005.
// (C) Copyright Jonathan Turkanis 2004.
// (C) Copyright Daniel Wallin 2004.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// Implementation of the move_ptr from the "Move Proposal" 
// (http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2002/n1377.htm) 
// enhanced to support custom deleters and safe boolean conversions.
//
// The implementation is based on an implementation by Daniel Wallin, at
// "http://aspn.activestate.com/ASPN/Mail/Message/Attachments/boost/
// 400DC271.1060903@student.umu.se/move_ptr.hpp". The current was adapted 
// by Jonathan Turkanis to incorporating ideas of Howard Hinnant and 
// Rani Sharoni. 

#ifndef BOOST_STATIC_MOVE_PTR_HPP_INCLUDED
#define BOOST_STATIC_MOVE_PTR_HPP_INCLUDED

#include <boost/config.hpp> // Member template friends, put size_t in std.
#include <cstddef>          // size_t
#include <boost/compressed_pair.hpp> 
#include <boost/ptr_container/detail/default_deleter.hpp>       
#include <boost/ptr_container/detail/is_convertible.hpp>       
#include <boost/ptr_container/detail/move.hpp>       
#include <boost/static_assert.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_array.hpp>

#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable:4521)        // Multiple copy constuctors.
#endif

namespace boost { namespace ptr_container_detail {

    
template< typename T, 
          typename Deleter = 
              move_ptrs::default_deleter<T> >
class static_move_ptr 
{
public:

    typedef typename remove_bounds<T>::type             element_type;
    typedef Deleter                                     deleter_type;

private:
    
    struct safe_bool_helper { int x; };
    typedef int safe_bool_helper::* safe_bool;
    typedef boost::compressed_pair<element_type*, Deleter> impl_type;

public:
    typedef typename impl_type::second_reference        deleter_reference;
    typedef typename impl_type::second_const_reference  deleter_const_reference;

        // Constructors

    static_move_ptr() : impl_(0) { }

    static_move_ptr(const static_move_ptr& p)
        : impl_(p.get(), p.get_deleter())    
        { 
            const_cast<static_move_ptr&>(p).release();
        }

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))    
    static_move_ptr( const move_ptrs::move_source<static_move_ptr<T,Deleter> >& src )
#else
    static_move_ptr( const move_ptrs::move_source<static_move_ptr>& src )
#endif    
            : impl_(src.ptr().get(), src.ptr().get_deleter())
            {
                src.ptr().release();
            }
    
    template<typename TT>
    static_move_ptr(TT* tt, Deleter del) 
        : impl_(tt, del) 
        { }

        // Destructor

    ~static_move_ptr() { if (ptr()) get_deleter()(ptr()); }

        // Assignment

    static_move_ptr& operator=(static_move_ptr rhs)
        {
            rhs.swap(*this);
            return *this;
        }

        // Smart pointer interface

    element_type* get() const { return ptr(); }

    element_type& operator*() 
        { 
            /*BOOST_STATIC_ASSERT(!is_array);*/ return *ptr(); 
        }

    const element_type& operator*() const 
        { 
            /*BOOST_STATIC_ASSERT(!is_array);*/ return *ptr(); 
        }

    element_type* operator->()  
        { 
            /*BOOST_STATIC_ASSERT(!is_array);*/ return ptr(); 
        }    

    const element_type* operator->() const 
        { 
            /*BOOST_STATIC_ASSERT(!is_array);*/ return ptr(); 
        }    


    element_type* release()
        {
            element_type* result = ptr();
            ptr() = 0;
            return result;
        }

    void reset()
        {
            if (ptr()) get_deleter()(ptr());
            ptr() = 0;
        }

    template<typename TT>
    void reset(TT* tt, Deleter dd) 
        {
            static_move_ptr(tt, dd).swap(*this);
        }

    operator safe_bool() const { return ptr() ? &safe_bool_helper::x : 0; }

    void swap(static_move_ptr& p) { impl_.swap(p.impl_); }

    deleter_reference get_deleter() { return impl_.second(); }

    deleter_const_reference get_deleter() const { return impl_.second(); }
private:
    template<typename TT, typename DD>
    void check(const static_move_ptr<TT, DD>&)
        {
            typedef move_ptrs::is_smart_ptr_convertible<TT, T> convertible;
            BOOST_STATIC_ASSERT(convertible::value);
        }   

#if defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) || defined(BOOST_NO_SFINAE)
// give up on this behavior
#else 

    template<typename Ptr> struct cant_move_from_const;

    template<typename TT, typename DD> 
    struct cant_move_from_const< const static_move_ptr<TT, DD> > { 
        typedef typename static_move_ptr<TT, DD>::error type; 
    };

    template<typename Ptr> 
    static_move_ptr(Ptr&, typename cant_move_from_const<Ptr>::type = 0);


public:
    static_move_ptr(static_move_ptr&);

    
private:
    template<typename TT, typename DD>
    static_move_ptr( static_move_ptr<TT, DD>&,
                     typename 
                     move_ptrs::enable_if_convertible<
                         TT, T, static_move_ptr&
                     >::type::type* = 0 );

#endif // BOOST_NO_FUNCTION_TEMPLATE_ORDERING || BOOST_NO_SFINAE

//#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
//    template<typename TT, typename DD>
//    friend class static_move_ptr;
//#else
    public:
//#endif
    typename impl_type::first_reference 
    ptr() { return impl_.first(); } 

    typename impl_type::first_const_reference 
    ptr() const { return impl_.first(); }

    impl_type impl_;
};

} // namespace ptr_container_detail
} // End namespace boost.

#if defined(BOOST_MSVC)
#pragma warning(pop) // #pragma warning(disable:4251)
#endif

#endif      // #ifndef BOOST_STATIC_MOVE_PTR_HPP_INCLUDED

/* static_move_ptr.hpp
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
*/