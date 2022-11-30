#ifndef BOOST_SERIALIZATION_SHARED_PTR_HELPER_HPP
#define BOOST_SERIALIZATION_SHARED_PTR_HELPER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// shared_ptr_helper.hpp: serialization for boost shared pointern

// (C) Copyright 2004-2009 Robert Ramey, Martin Ecker and Takatoshi Kondo
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <map>
#include <list>
#include <utility>
#include <cstddef> // NULL

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/mpl/if.hpp>

#include <boost/serialization/singleton.hpp>
#include <boost/serialization/extended_type_info.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/serialization/type_info_implementation.hpp>
#include <boost/archive/archive_exception.hpp>

namespace boost_132 {
    template<class T> class shared_ptr;
}
namespace boost {
namespace serialization {

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
template<class Archive, template<class U> class SPT >
void load(
    Archive & ar,
    SPT< class U > &t,
    const unsigned int file_version
);
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// a common class for holding various types of shared pointers

template<template<class T> class SPT>
class shared_ptr_helper {
    typedef std::map<
        const void *, // address of object
        SPT<const void> // address shared ptr to single instance
    > object_shared_pointer_map;

    // list of shared_pointers create accessable by raw pointer. This
    // is used to "match up" shared pointers loaded at different
    // points in the archive. Note, we delay construction until
    // it is actually used since this is by default included as
    // a "mix-in" even if shared_ptr isn't used.
    object_shared_pointer_map * m_o_sp;

    struct null_deleter {
        void operator()(void const *) const {}
    };

#if defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS) \
|| defined(BOOST_MSVC) \
|| defined(__SUNPRO_CC)
public:
#else
    template<class Archive, class U>
    friend void boost::serialization::load(
        Archive & ar,
        SPT< U > &t,
        const unsigned int file_version
    );
#endif

    #ifdef BOOST_SERIALIZATION_SHARED_PTR_132_HPP
    // list of loaded pointers.  This is used to be sure that the pointers
    // stay around long enough to be "matched" with other pointers loaded
    // by the same archive.  These are created with a "null_deleter" so that
    // when this list is destroyed - the underlaying raw pointers are not
    // destroyed.  This has to be done because the pointers are also held by
    // new system which is disjoint from this set.  This is implemented
    // by a change in load_construct_data below.  It makes this file suitable
    // only for loading pointers into a 1.33 or later boost system.
    std::list<boost_132::shared_ptr<const void> > * m_pointers_132;
    void
    append(const boost_132::shared_ptr<const void> & t){
        if(NULL == m_pointers_132)
            m_pointers_132 = new std::list<boost_132::shared_ptr<const void> >;
        m_pointers_132->push_back(t);
    }
    #endif

    struct non_polymorphic {
        template<class U>
        static const boost::serialization::extended_type_info *
        get_object_type(U & ){
            return & boost::serialization::singleton<
                typename
                boost::serialization::type_info_implementation< U >::type
            >::get_const_instance();
        }
    };
    struct polymorphic {
        template<class U>
        static const boost::serialization::extended_type_info *
        get_object_type(U & u){
            return boost::serialization::singleton<
                typename
                boost::serialization::type_info_implementation< U >::type
            >::get_const_instance().get_derived_extended_type_info(u);
        }
    };

public:
    template<class T>
    void reset(SPT< T > & s, T * t){
        if(NULL == t){
            s.reset();
            return;
        }
        const boost::serialization::extended_type_info * this_type
            = & boost::serialization::type_info_implementation< T >::type
                    ::get_const_instance();

        // get pointer to the most derived object's eti.  This is effectively
        // the object type identifer
        typedef typename mpl::if_<
            is_polymorphic< T >,
            polymorphic,
            non_polymorphic
        >::type type;

        const boost::serialization::extended_type_info * true_type
            = type::get_object_type(*t);

        // note:if this exception is thrown, be sure that derived pointern
        // is either registered or exported.
        if(NULL == true_type)
            boost::serialization::throw_exception(
                boost::archive::archive_exception(
                    boost::archive::archive_exception::unregistered_class,
                    this_type->get_debug_info()
                )
            );
        // get void pointer to the most derived type
        // this uniquely identifies the object referred to
        // oid = "object identifier"
        const void * oid = void_downcast(
            *true_type,
            *this_type,
            t
        );
        if(NULL == oid)
            boost::serialization::throw_exception(
                boost::archive::archive_exception(
                    boost::archive::archive_exception::unregistered_cast,
                    true_type->get_debug_info(),
                    this_type->get_debug_info()
                )
            );

        // make tracking array if necessary
        if(NULL == m_o_sp)
            m_o_sp = new object_shared_pointer_map;

        typename object_shared_pointer_map::iterator i = m_o_sp->find(oid);

        // if it's a new object
        if(i == m_o_sp->end()){
            s.reset(t);
            std::pair<typename object_shared_pointer_map::iterator, bool> result;
            result = m_o_sp->insert(std::make_pair(oid, s));
            BOOST_ASSERT(result.second);
        }
        // if the object has already been seen
        else{
            s = SPT<T>(i->second, t);
        }
    }

    shared_ptr_helper() :
        m_o_sp(NULL)
        #ifdef BOOST_SERIALIZATION_SHARED_PTR_132_HPP
            , m_pointers_132(NULL)
        #endif
    {}
    virtual ~shared_ptr_helper(){
        if(NULL != m_o_sp)
            delete m_o_sp;
        #ifdef BOOST_SERIALIZATION_SHARED_PTR_132_HPP
        if(NULL != m_pointers_132)
            delete m_pointers_132;
        #endif
    }
};

} // namespace serialization
} // namespace boost

#endif // BOOST_SERIALIZATION_SHARED_PTR_HELPER_HPP

/* shared_ptr_helper.hpp
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
*/