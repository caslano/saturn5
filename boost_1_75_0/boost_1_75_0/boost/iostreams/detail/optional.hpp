// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Recent changes to Boost.Optional involving assigment broke Boost.Iostreams,
// in a way which could be remedied only by relying on the deprecated reset
// functions; with VC6, even reset didn't work. Until this problem is 
// understood, Iostreams will use a private version of optional with a smart 
// pointer interface.

#ifndef BOOST_IOSTREAMS_DETAIL_OPTIONAL_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_OPTIONAL_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp>

namespace boost { namespace iostreams { namespace detail {

// Taken from <boost/optional.hpp>.
template<class T>
class aligned_storage
{
    // Borland ICEs if unnamed unions are used for this!
    union dummy_u
    {
        char data[ sizeof(T) ];
        BOOST_DEDUCED_TYPENAME type_with_alignment<
          ::boost::alignment_of<T>::value >::type aligner_;
    } dummy_ ;

  public:

    void const* address() const { return &dummy_.data[0]; }
    void      * address()       { return &dummy_.data[0]; }
};

template<typename T>
class optional {
public:
    typedef T element_type;
    optional() : initialized_(false) { }
    optional(const T& t) : initialized_(false) { reset(t); }
    ~optional() { reset(); }
    T& operator*() 
    { 
        BOOST_ASSERT(initialized_);
        return *static_cast<T*>(address()); 
    }
    const T& operator*() const
    { 
        BOOST_ASSERT(initialized_);
        return *static_cast<const T*>(address()); 
    }
    T* operator->() 
    { 
        BOOST_ASSERT(initialized_);
        return static_cast<T*>(address()); 
    }
    const T* operator->() const
    { 
        BOOST_ASSERT(initialized_);
        return static_cast<const T*>(address()); 
    }
    T* get() 
    { 
        BOOST_ASSERT(initialized_);
        return static_cast<T*>(address()); 
    }
    const T* get() const
    { 
        BOOST_ASSERT(initialized_);
        return static_cast<const T*>(address()); 
    }
    void reset() 
    {
        if (initialized_) { 
        #if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) || \
            BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600)) \
            /**/
            T* t = static_cast<T*>(address());
            t->~T();
        #else
            static_cast<T*>(address())->T::~T();
        #endif
            initialized_ = false;
        }
    }
    void reset(const T& t) 
    {
        reset();
        new (address()) T(t); 
        initialized_ = true;
    }
private:
    optional(const optional&);
    optional& operator=(const optional&);
    void* address() { return &storage_; }
    const void* address() const { return &storage_; }
    aligned_storage<T>  storage_;
    bool                initialized_;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_OPTIONAL_HPP_INCLUDED

/* optional.hpp
Nyv+6bdRtCERCPkhB6L1B+SC8boTgjC/MvIlrlyHWdZ3F7hOb85yHhlAcCApvw0JMIyt0xT+Xduf8jOb/HP6xHa/JcY+CoAsQdh/l+0UUuT7oPJufKull9xS2HtglPYn/oQbBbH6Wel5smU+hhjcmvuf+J3E8Fz1JEjHmFYm+MEmJ9WI9Axz6DHO5CCM5EJd8a85b4trJ0xBlSbrCgZJ05HoLuhvp9Dwucx8S5iZ592d/iCYJcjsXNBx1Ry1SJwVYkxrBLY0kvYdx5iOFzhVNC/YsdQ/SI/FeDv1KLuBAGaxqqtI43D2R7z3I/yjcRUqfNVk8i0ED/GSrgAebcPxw9yFBAnX9jjz0RiCXRO7kUuGDXnNM1u91CQuIUGHk2git7jiX8JxPpDF42J8QUiPC3F6fLuDDK4O6tVJpZ5yeoylaipMiY3jvZbas0//0GJQjld6ncjttiL0qVzR76wgKogCCWoyEmmZjHYO9ac6fa7HmzWEEfTJymYnXTTjs8yVPwQ+D9MDMPzVJ3Fn3iSLlkKW0UpM8+gIsR4+RrjOQcSSVLpmoyUA1xRVb0pdti2I7oZAOmLixI+c9LrZoSVjbXEwjhQqeWRfYbHzzoxe1XBCL8bDqeqlX+bCj1xD91xfLrKE3RjXe87NhB1yaWMmWR6yP2MI8jya1BIllUMLwpWcsu8Ec7zssNYFIh/8qZnVo19L8ozY/eBOaaKj
*/