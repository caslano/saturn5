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
VO6Lf1J3zTHPR9d1ozOT45tb4lyXIT1yLWldh9DrNdi6UjfgnHovq3qv1AG4X71D0rpxzvFuQVflSfKy0nXPd+oji9jnc72rcJ69TlOqqx42cenyBcXR851UGQWnK/0TgsOwyIbAbOtQ4ATzGFml54tcI17K+x2Ec5a6PiwYLo9zOnJMze0VnsBvrGTzWNpUw9pb4uZu3Jyrrg8Icl2vC8E7RL9TP1PXT/afRC3vbXZZ2+sr1e+D7yr/X7KW4T9zuFS9chdufqXuKQsMZ3RHLT0YwwPJrnq7LltZz8vWzdBzw6aE/AuOpBzcwWiJfr4rfX/zB3wfBU7QdZ/Xlb/T6urx6aH3iNsu96ODXeT9wepKSm80z25yxBzEVCn7XlR+Px64PZBimd77tR2UP1Hzh3rIO/wDdf/4QBLpPB69q600at9t0Oc6V05R/vexHH0+hYukjrPdrkPq8+TP+cpMqg6xjWvLldvpwSyru+caLH9U4Uvz/Vr6ajpp22RIX1S4DymyfpqXVrfO/078cvU3qXSt4vx+5X6Vv7vvx1aSP4+3bldxV+oeylmeV9Efq9JhqO82K4/xPiHd86Vd5pwnukfinqrcsSenSvgkXgEVhyyJZzgdTyWNusoc/fB92EL8/oPy+y7rPNLafjccJe8dTbPdssvwNevVO6fiPV46Hu8GuSezY2gP7OTWaz52l/nponMGOjyUlPlrqpIDLaPWCLmJ4ywp97M7OueM6XKeUId4HccbkOuRuZ1C5fEN/H0pslW9N8z3DOpoYZ26d8aNGaFyeaOQ+7lX9bOpcrrAXE6P43bCf7Kqt3a0fHrOWkl63VzEf6bpOYYnWXLuog763MjwuePqzo0In6tN1eeGhc8drDuXE56zOCU9vveEa98H9Rydn8E5ebYo+1WeVn2B4bwv56v0eWfeba/yI/mU83X5NFX01ZoHktec74pdMje2kOuDhKUkelUn17ti8vKl3GpYI2CsCvvvlP7xwXB5uE8djw5OYTTTFcgo3ye+BwInW7WBUbq8K+1q66yww2gN4D/j2p6djO8W4ztD67rLbMJYSRj/rK4PCJraZOdnqLqyPKv8Oqs2me8J6xmP8Hb3bEed1lm371TZ8Gvlb7bvdMqzMuQ2axPX0OXsHKWb62/PCKV7fJew73mG7q/+SIUpSZUNmwn/m8qdvsFXfCf43GW5ugf2V2HsoN0Yr45pM0h5/KFyo2PQ1Z7T7Z2eSr8Xd3TS7Y+n1D2PBFJ4N14XaKPrBy+r8y9Tw37ct883ztcm8JS6lqb9/YHVBrfGUkbPsoZI/w4tvy6htZRG4Us+droIna2EoAdh3EgYX1fuDgneRlv2ad9M3z8CAetooLtXu1KvP/KLkH18Z2Hjq5Dv0zv4KbZIlffc+crWPXzHWS11G+grZeO9/hbWz/1qPSkdvi+5P4Xxe92U7bYSrreV+72C7nZrlrj/iro+LJjLfaXIDfj0K18n/7uBUfpdulvZZaBn2/EO5Xe7iLxFB4tuW21W4Z3sy8T9POtd9KT+oe4bInrOeL1tfYUVw++gS5TeRb5m1iTVr7KFeH2gwt056G5bpYqf1ym3TiUt+0k8qL8rd4ots836oxd6n72v3KZ9qd+hVI0d78+2uu8kVLdNlzxwkUqr9f4s0mqsP1QP25CintlVlty/w/nth/MUhdoeT6j7Ky1TvFP1PbrLSz9jD6v7xvi/8GWodSn741hxt3D7bU2Jof2mdKq6hduFa85X7bcBnu03fc+r3aRtFlz7enLLZsm+Ed73hMNypFu4nba2Nsb7WsloeU9vErna0e65ib9vRpYhpSTyC+mhttK1CFRrM1TCW5CHbLcc7bpblTs=
*/