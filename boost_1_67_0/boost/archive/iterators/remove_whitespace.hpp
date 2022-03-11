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