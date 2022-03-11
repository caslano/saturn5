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
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
*/