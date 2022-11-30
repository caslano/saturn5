#ifndef BOOST_ARCHIVE_ITERATORS_REMOVE_WHITESPACE_HPP
#define BOOST_ARCHIVE_ITERATORS_REMOVE_WHITESPACE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// remove_whitespace.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/iterator_traits.hpp>

// here is the default standard implementation of the functor used
// by the filter iterator to remove spaces.  Unfortunately usage
// of this implementation in combination with spirit trips a bug
// VC 6.5.  The only way I can find to work around it is to
// implement a special non-standard version for this platform

#ifndef BOOST_NO_CWCTYPE
#include <cwctype> // iswspace
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ using ::iswspace; }
#endif
#endif

#include <cctype> // isspace
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ using ::isspace; }
#endif

#if defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
// this is required for the RW STL on Linux and Tru64.
#undef isspace
#undef iswspace
#endif

namespace { // anonymous

template<class CharType>
struct remove_whitespace_predicate;

template<>
struct remove_whitespace_predicate<char>
{
    bool operator()(unsigned char t){
        return ! std::isspace(t);
    }
};

#ifndef BOOST_NO_CWCHAR
template<>
struct remove_whitespace_predicate<wchar_t>
{
    bool operator()(wchar_t t){
        return ! std::iswspace(t);
    }
};
#endif

} // namespace anonymous

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// convert base64 file data (including whitespace and padding) to binary

namespace boost {
namespace archive {
namespace iterators {

// custom version of filter iterator which doesn't look ahead further than
// necessary

template<class Predicate, class Base>
class filter_iterator
    : public boost::iterator_adaptor<
        filter_iterator<Predicate, Base>,
        Base,
        use_default,
        single_pass_traversal_tag
    >
{
    friend class boost::iterator_core_access;
    typedef typename boost::iterator_adaptor<
        filter_iterator<Predicate, Base>,
        Base,
        use_default,
        single_pass_traversal_tag
    > super_t;
    typedef filter_iterator<Predicate, Base> this_t;
    typedef typename super_t::reference reference_type;

    reference_type dereference_impl(){
        if(! m_full){
            while(! m_predicate(* this->base_reference()))
                ++(this->base_reference());
            m_full = true;
        }
        return * this->base_reference();
    }

    reference_type dereference() const {
        return const_cast<this_t *>(this)->dereference_impl();
    }

    Predicate m_predicate;
    bool m_full;
public:
    // note: this function is public only because comeau compiler complained
    // I don't know if this is because the compiler is wrong or what
    void increment(){
        m_full = false;
        ++(this->base_reference());
    }
    filter_iterator(Base start) :
        super_t(start),
        m_full(false)
    {}
    filter_iterator(){}
};

template<class Base>
class remove_whitespace :
    public filter_iterator<
        remove_whitespace_predicate<
            typename boost::iterator_value<Base>::type
            //typename Base::value_type
        >,
        Base
    >
{
    friend class boost::iterator_core_access;
    typedef filter_iterator<
        remove_whitespace_predicate<
            typename boost::iterator_value<Base>::type
            //typename Base::value_type
        >,
        Base
    > super_t;
public:
//    remove_whitespace(){} // why is this needed?
    // make composible buy using templated constructor
    template<class T>
    remove_whitespace(T start) :
        super_t(Base(static_cast< T >(start)))
    {}
    // intel 7.1 doesn't like default copy constructor
    remove_whitespace(const remove_whitespace & rhs) :
        super_t(rhs.base_reference())
    {}
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_REMOVE_WHITESPACE_HPP

/* remove_whitespace.hpp
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
*/