// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2004-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the definition of the class template 
// boost::iostreams::detail::double_object, which is similar to compressed pair
// except that both members of the pair have the same type, and 
// compression occurs only if requested using a boolean template
// parameter.

#ifndef BOOST_IOSTREAMS_DETAIL_DOUBLE_OBJECT_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_DOUBLE_OBJECT_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <algorithm>              // swap.
#include <boost/detail/workaround.hpp>
#include <boost/mpl/if.hpp>
#if BOOST_WORKAROUND(__MWERKS__, > 0x3003)
# include <msl_utility>
#else
# include <boost/call_traits.hpp>
#endif

namespace boost { namespace iostreams { namespace detail {

template<typename T>
class single_object_holder {
public:
#if BOOST_WORKAROUND(__MWERKS__, > 0x3003)
    typedef Metrowerks::call_traits<T>             traits_type;
#else
    typedef boost::call_traits<T>                  traits_type;
#endif
    typedef typename traits_type::param_type       param_type;
    typedef typename traits_type::reference        reference;
    typedef typename traits_type::const_reference  const_reference;
    single_object_holder() { }
    single_object_holder(param_type t) : first_(t) { }
    reference first() { return first_; }
    const_reference first() const { return first_; }
    reference second() { return first_; }
    const_reference second() const { return first_; }
    void swap(single_object_holder& o)
    { std::swap(first_, o.first_); }
private:
    T first_;
};

template<typename T>
struct double_object_holder {
public:
#if BOOST_WORKAROUND(__MWERKS__, > 0x3003)
    typedef Metrowerks::call_traits<T>             traits_type;
#else
    typedef boost::call_traits<T>                  traits_type;
#endif
    typedef typename traits_type::param_type       param_type;
    typedef typename traits_type::reference        reference;
    typedef typename traits_type::const_reference  const_reference;
    double_object_holder() { }
    double_object_holder(param_type t1, param_type t2)
        : first_(t1), second_(t2) { }
    reference first() { return first_; }
    const_reference first() const { return first_; }
    reference second() { return second_; }
    const_reference second() const { return second_; }
    void swap(double_object_holder& d)
    { 
        std::swap(first_, d.first_); 
        std::swap(second_, d.second_); 
    }
private:
    T first_, second_;
};

template<typename T, typename IsDouble>
class double_object 
    : public mpl::if_<
                 IsDouble, 
                 double_object_holder<T>, 
                 single_object_holder<T>
             >::type
{
private:
    typedef typename 
            mpl::if_<
                IsDouble, 
                double_object_holder<T>, 
                single_object_holder<T>
            >::type                                base_type;
public:
#if BOOST_WORKAROUND(__MWERKS__, > 0x3003)
    typedef Metrowerks::call_traits<T>             traits_type;
#else
    typedef boost::call_traits<T>                  traits_type;
#endif
    typedef typename traits_type::param_type       param_type;
    typedef typename traits_type::reference        reference;
    typedef typename traits_type::const_reference  const_reference;
    double_object() : base_type() {}
    double_object(param_type t1, param_type t2)
        : base_type(t1, t2) { }
    bool is_double() const { return IsDouble::value; }
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_DOUBLE_OBJECT_HPP_INCLUDED

/* double_object.hpp
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
*/