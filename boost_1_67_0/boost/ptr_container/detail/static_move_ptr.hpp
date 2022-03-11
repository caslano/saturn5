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

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))    
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