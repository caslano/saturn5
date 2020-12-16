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
mIO7S8nbsMkLaGMfu+sR1Kn9LeP99ejeG/gWfGm+0dhq4pp3yd36xuM7exA31aNe2QVfTI0gPC16VhCbV5/4tylx1QTWS/C3HYj1bHH401h8xiV86klsYSgxOnrxzg7s6DjqgzHEJsQtg/Dx08dgO0JY2ytBHceDmDQP8f154rjs9JNcsxy1/D5XiVvJz4dexPYTh3z+FvF6LYtcAn+7gTb0/yO+SxnYAJ80C79NHXDzPXJq5rZWMeb6c44dIkbxJ2+8TmzC2tvg7fjslsjQRGqp66nrM7Z3id824fe21yXPQT9GhmA7LzC+6FAU/76FWnoW6l5x6OOjifiiG8RaXdG/5/hYdGFFJ/I2/KXBMzfy74f7If9FkMMl1JESqW0zjjPwr4Ho5XX0KoG6Vnni7E/JUZImMCe3aM+6nx/v04B1+62NbUZV/IgRydxDG8Z71lByQPrTnPe/iW7ZKvEu6P9tYsVChfCBtw1yNeS+LDJ6Bvv2DP/VmzgE+/wB+r+cvKrkaOrUt4nnyvO3FYPQFWpnAVlN8m2b41knNhAbvIl9Q1Z/7Iy+0995N4n18b837TnvSPLfj1mrIldoxRj+SM57n/MRvP9w6qMRtbE/D8hRYrAr5NRevsSRHYkLhvE3FeQ9bS1qUOuwiVzXGnn36cK8JzJexMgLkOFJ0aw7rCJXQz6X0reSxO5ewcQfbvh0xtKKQr7OYQs/QjaCyVMGY0OxmR6M9/Q62I1PiOOSiIfnYTebUcOYS00xALvMe7z9FjYHX9eR2PZMeeauBTm2vZ7SzjBC8B0teeenXagPMbbLIlnjR5YHfkOMVR97dwudqELs2BS7j1wXYYyax/PMinzn8Ro1PvSuF2NchDaXC9jX++kPY9T0PDq1mZoq+WqTbZzDTnQnYJ5NruG/hnE9RzwTiV2qjQywBlU8kPxgOrIyFrmlxlOC3yXIG6ozVlW+517EF2P2U3crSbyxlhhjADXcoTbsNblTbcbuCXLsioyjk0W7Ej/WJ4fjvp6V0BnmviLjEs142/UwYyty7PvYanK1EGQumRyjT13sVC4LWSb334NPI+7waclaeRV0eRkxLOO/Gd29eRm7w/p1OsbmShLfCHji47Avxd5mPHhmTexl6bLE9yPJn7FPtVj/fpdx22QnjpoIa9A9IvjbX3KGe4vQaZ71XjnsOP4onpjeZRixe3XGhhwyGD8zayrrcsSBY7E9OZYxhvn5PseLtRZsRllX7LUbc3QYPzKe929C7E7+HIwsVcCGZcYvLke862Qnf3mJf2duGlbBVZDXTUTeP40mzq/NOsluExk1+F4H+brFvH9Mf2da+HdqGMSddSpiN7BDeRjvgfiNIPqR1BGd3ojtJmYfEkiN+QD5Qih1H3KsvIzBsBjUags+Yj968g7xNGPReRK+ezK1vsF2+2gY+ZGfRGo1uSYj/6fwqe3ICYpRzxvAusJE+lKC3IMxqDMJ3+eBDVyKjM9k3Z7nGXz/0SwbdYoK2LbGyA15oFspcgNkLQ5bX/YQaxE8/wE2uUlNvhnDLx07jd3Frn5Nn/fWMB2xQueviPufYJM/x163xF/y7+e8kIEp2CPkJhM+bg0+7A38ejmDPK8Dc3qEWuU18lrmuZQ/+WMp8g58tIHdS3BnzZ46SClyn52M+dkD1Hm/Qq8rY3v4NigXc/AJ77oQm3nlBjFBf8aR+l/m5tQtkf1aOalpXmEu06MD+Fs/H2Qe3/9wLbamE362Nc9nLWdKeWKX6cjnMOIV/MOOCJ6TD3/3JnWBeeRh6E5a3vGLsqzlxDK+5CWuyLE3MUUk37D04LuKOTw/jH9/iRrQm+OJgRpSs6CeEdCY9bChXIeNLtk=
*/