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
        #if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564)) || \
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
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
*/