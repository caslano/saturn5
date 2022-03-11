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