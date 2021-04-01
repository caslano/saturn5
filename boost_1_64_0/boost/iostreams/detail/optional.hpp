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
LgB4vbQxMonVQEi1nYmUlvWVZEFSM8U5mWSK8R83d8Jv/t8BofgV0cDPD+ORAN0bdy9OMxVUHuXhAV3A5gJ5s+1bkj8F7rjk4coE/Xu3hPS+8tTT4FmdqIicgwga83KmaLM5X3UaiPJyOx32OyQFe188Hk1KiXFBTBXEV1Cx/RH4Bcp44geEbjzjmsCeBE6U9BH2GDV6BLleWS7+DD+UdYbOZxt+TR+tG8bmEm2qyi+qW5K1Rp8fCtJGnDAF3T2ZwsSso5v0NiAl5/uncBxruhZqnuKWYbhcEiFen8yF9RIIVyLb6eiN0Y02P3g3PP2OuUuv1YgL/4AiIztm68siTQ0lwRv9H6+UXQrzPyQnWpI1xbu5yGLgRubVdIUQaXZEl9JcUpQQmGQJG4WFx1b32abZerRXebA2zzVJGySNxqKGpQ9dTwKJR9XiYQvk4wjsy5+l96eL4cCkFc3K2lubz9Mii+kExHfUiSfqkaFjps5JAtiQSyFE5HeVh9X7jSOJBEVk4Im3O5LTAVmzndqeFY5Gzj6jH533wlDmFC/5mOmPD2BYIAuVEdMNUw==
*/