#ifndef BOOST_ARCHIVE_DETAIL_ISERIALIZER_HPP
#define BOOST_ARCHIVE_DETAIL_ISERIALIZER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#pragma inline_depth(511)
#pragma inline_recursion(on)
#endif

#if defined(__MWERKS__)
#pragma inline_depth(511)
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// iserializer.hpp: interface for serialization system.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <new>     // for placement new
#include <cstddef> // size_t, NULL

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/static_assert.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/core/no_exceptions_support.hpp>

#ifndef BOOST_SERIALIZATION_DEFAULT_TYPE_INFO
    #include <boost/serialization/extended_type_info_typeid.hpp>
#endif
#include <boost/serialization/throw_exception.hpp>
#include <boost/serialization/smart_cast.hpp>
#include <boost/serialization/static_warning.hpp>

#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <boost/type_traits/is_polymorphic.hpp>

#include <boost/serialization/assume_abstract.hpp>

#if !defined(BOOST_MSVC) && \
    (BOOST_WORKAROUND(__IBMCPP__, < 1210) || \
    defined(__SUNPRO_CC) && (__SUNPRO_CC < 0x590))
    #define BOOST_SERIALIZATION_DONT_USE_HAS_NEW_OPERATOR 1
#else
    #define BOOST_SERIALIZATION_DONT_USE_HAS_NEW_OPERATOR 0
#endif

#if ! BOOST_SERIALIZATION_DONT_USE_HAS_NEW_OPERATOR
#include <boost/type_traits/has_new_operator.hpp>
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/type_info_implementation.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/void_cast.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/serialization/wrapper.hpp>
#include <boost/serialization/array_wrapper.hpp>

// the following is need only for dynamic cast of polymorphic pointers
#include <boost/archive/archive_exception.hpp>
#include <boost/archive/detail/basic_iarchive.hpp>
#include <boost/archive/detail/basic_iserializer.hpp>
#include <boost/archive/detail/basic_pointer_iserializer.hpp>
#include <boost/archive/detail/archive_serializer_map.hpp>
#include <boost/archive/detail/check.hpp>

#include <boost/core/addressof.hpp>

namespace boost {

namespace serialization {
    class extended_type_info;
} // namespace serialization

namespace archive {

// an accessor to permit friend access to archives.  Needed because
// some compilers don't handle friend templates completely
class load_access {
public:
    template<class Archive, class T>
    static void load_primitive(Archive &ar, T &t){
        ar.load(t);
    }
};

namespace detail {

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

template<class Archive, class T>
class iserializer : public basic_iserializer
{
private:
    virtual void destroy(/*const*/ void *address) const {
        boost::serialization::access::destroy(static_cast<T *>(address));
    }
public:
    explicit iserializer() :
        basic_iserializer(
            boost::serialization::singleton<
                typename
                boost::serialization::type_info_implementation< T >::type
            >::get_const_instance()
        )
    {}
    virtual BOOST_DLLEXPORT void load_object_data(
        basic_iarchive & ar,
        void *x,
        const unsigned int file_version
    ) const BOOST_USED;
    virtual bool class_info() const {
        return boost::serialization::implementation_level< T >::value
            >= boost::serialization::object_class_info;
    }
    virtual bool tracking(const unsigned int /* flags */) const {
        return boost::serialization::tracking_level< T >::value
                == boost::serialization::track_always
            || ( boost::serialization::tracking_level< T >::value
                == boost::serialization::track_selectively
                && serialized_as_pointer());
    }
    virtual version_type version() const {
        return version_type(::boost::serialization::version< T >::value);
    }
    virtual bool is_polymorphic() const {
        return boost::is_polymorphic< T >::value;
    }
    virtual ~iserializer(){};
};

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

template<class Archive, class T>
BOOST_DLLEXPORT void iserializer<Archive, T>::load_object_data(
    basic_iarchive & ar,
    void *x,
    const unsigned int file_version
) const {
    // note: we now comment this out. Before we permited archive
    // version # to be very large.  Now we don't.  To permit
    // readers of these old archives, we have to suppress this
    // code.  Perhaps in the future we might re-enable it but
    // permit its suppression with a runtime switch.
    #if 0
    // trap case where the program cannot handle the current version
    if(file_version > static_cast<const unsigned int>(version()))
        boost::serialization::throw_exception(
            archive::archive_exception(
                boost::archive::archive_exception::unsupported_class_version,
                get_debug_info()
            )
        );
    #endif
    // make sure call is routed through the higest interface that might
    // be specialized by the user.
    boost::serialization::serialize_adl(
        boost::serialization::smart_cast_reference<Archive &>(ar),
        * static_cast<T *>(x),
        file_version
    );
}

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

// the purpose of this code is to allocate memory for an object
// without requiring the constructor to be called.  Presumably
// the allocated object will be subsequently initialized with
// "placement new".
// note: we have the boost type trait has_new_operator but we
// have no corresponding has_delete_operator.  So we presume
// that the former being true would imply that the a delete
// operator is also defined for the class T.

template<class T>
struct heap_allocation {
    // boost::has_new_operator< T > doesn't work on these compilers
    #if BOOST_SERIALIZATION_DONT_USE_HAS_NEW_OPERATOR
        // This doesn't handle operator new overload for class T
        static T * invoke_new(){
            return static_cast<T *>(operator new(sizeof(T)));
        }
        static void invoke_delete(T *t){
            (operator delete(t));
        }
    #else
        // note: we presume that a true value for has_new_operator
        // implies the existence of a class specific delete operator as well
        // as a class specific new operator.
        struct has_new_operator {
            static T * invoke_new() {
                return static_cast<T *>((T::operator new)(sizeof(T)));
            }
            static void invoke_delete(T * t) {
                // if compilation fails here, the likely cause that the class
                // T has a class specific new operator but no class specific
                // delete operator which matches the following signature.
                // note that this solution addresses the issue that two
                // possible signatures.  But it doesn't address the possibility
                // that the class might have class specific new with NO
                // class specific delete at all.  Patches (compatible with
                // C++03) welcome!
                (operator delete)(t);
            }
        };
        struct doesnt_have_new_operator {
            static T* invoke_new() {
                return static_cast<T *>(operator new(sizeof(T)));
            }
            static void invoke_delete(T * t) {
                // Note: I'm reliance upon automatic conversion from T * to void * here
                (operator delete)(t);
            }
        };
        static T * invoke_new() {
            typedef typename
                mpl::eval_if<
                    boost::has_new_operator< T >,
                    mpl::identity<has_new_operator >,
                    mpl::identity<doesnt_have_new_operator >
                >::type typex;
            return typex::invoke_new();
        }
        static void invoke_delete(T *t) {
            typedef typename
                mpl::eval_if<
                    boost::has_new_operator< T >,
                    mpl::identity<has_new_operator >,
                    mpl::identity<doesnt_have_new_operator >
                >::type typex;
            typex::invoke_delete(t);
        }
    #endif
    explicit heap_allocation(){
        m_p = invoke_new();
    }
    ~heap_allocation(){
        if (0 != m_p)
            invoke_delete(m_p);
    }
    T* get() const {
        return m_p;
    }

    T* release() {
        T* p = m_p;
        m_p = 0;
        return p;
    }
private:
    T* m_p;
};

template<class Archive, class T>
class pointer_iserializer :
    public basic_pointer_iserializer
{
private:
    virtual void * heap_allocation() const {
        detail::heap_allocation<T> h;
        T * t = h.get();
        h.release();
        return t;
    }
    virtual const basic_iserializer & get_basic_serializer() const {
        return boost::serialization::singleton<
            iserializer<Archive, T>
        >::get_const_instance();
    }
    BOOST_DLLEXPORT virtual void load_object_ptr(
        basic_iarchive & ar,
        void * x,
        const unsigned int file_version
    ) const BOOST_USED;
public:
    // this should alway be a singleton so make the constructor protected
    pointer_iserializer();
    ~pointer_iserializer();
};

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

// note: BOOST_DLLEXPORT is so that code for polymorphic class
// serialized only through base class won't get optimized out
template<class Archive, class T>
BOOST_DLLEXPORT void pointer_iserializer<Archive, T>::load_object_ptr(
    basic_iarchive & ar,
    void * t,
    const unsigned int file_version
) const
{
    Archive & ar_impl =
        boost::serialization::smart_cast_reference<Archive &>(ar);

    // note that the above will throw std::bad_alloc if the allocation
    // fails so we don't have to address this contingency here.

    // catch exception during load_construct_data so that we don't
    // automatically delete the t which is most likely not fully
    // constructed
    BOOST_TRY {
        // this addresses an obscure situation that occurs when
        // load_constructor de-serializes something through a pointer.
        ar.next_object_pointer(t);
        boost::serialization::load_construct_data_adl<Archive, T>(
            ar_impl,
            static_cast<T *>(t),
            file_version
        );
    }
    BOOST_CATCH(...){
        // if we get here the load_construct failed.  The heap_allocation
        // will be automatically deleted so we don't have to do anything
        // special here.
        BOOST_RETHROW;
    }
    BOOST_CATCH_END

    ar_impl >> boost::serialization::make_nvp(NULL, * static_cast<T *>(t));
}

template<class Archive, class T>
pointer_iserializer<Archive, T>::pointer_iserializer() :
    basic_pointer_iserializer(
        boost::serialization::singleton<
            typename
            boost::serialization::type_info_implementation< T >::type
        >::get_const_instance()
    )
{
    boost::serialization::singleton<
        iserializer<Archive, T>
    >::get_mutable_instance().set_bpis(this);
    archive_serializer_map<Archive>::insert(this);
}

template<class Archive, class T>
pointer_iserializer<Archive, T>::~pointer_iserializer(){
    archive_serializer_map<Archive>::erase(this);
}

template<class Archive>
struct load_non_pointer_type {
    // note this bounces the call right back to the archive
    // with no runtime overhead
    struct load_primitive {
        template<class T>
        static void invoke(Archive & ar, T & t){
            load_access::load_primitive(ar, t);
        }
    };
    // note this bounces the call right back to the archive
    // with no runtime overhead
    struct load_only {
        template<class T>
        static void invoke(Archive & ar, const T & t){
            // short cut to user's serializer
            // make sure call is routed through the higest interface that might
            // be specialized by the user.
            boost::serialization::serialize_adl(
                ar,
                const_cast<T &>(t),
                boost::serialization::version< T >::value
            );
        }
    };

    // note this save class information including version
    // and serialization level to the archive
    struct load_standard {
        template<class T>
        static void invoke(Archive &ar, const T & t){
            void * x = boost::addressof(const_cast<T &>(t));
            ar.load_object(
                x,
                boost::serialization::singleton<
                    iserializer<Archive, T>
                >::get_const_instance()
            );
        }
    };

    struct load_conditional {
        template<class T>
        static void invoke(Archive &ar, T &t){
            //if(0 == (ar.get_flags() & no_tracking))
                load_standard::invoke(ar, t);
            //else
            //    load_only::invoke(ar, t);
        }
    };

    template<class T>
    static void invoke(Archive & ar, T &t){
        typedef typename mpl::eval_if<
                // if its primitive
                mpl::equal_to<
                    boost::serialization::implementation_level< T >,
                    mpl::int_<boost::serialization::primitive_type>
                >,
                mpl::identity<load_primitive>,
            // else
            typename mpl::eval_if<
            // class info / version
            mpl::greater_equal<
                        boost::serialization::implementation_level< T >,
                        mpl::int_<boost::serialization::object_class_info>
                    >,
            // do standard load
            mpl::identity<load_standard>,
        // else
        typename mpl::eval_if<
            // no tracking
                    mpl::equal_to<
                        boost::serialization::tracking_level< T >,
                        mpl::int_<boost::serialization::track_never>
                >,
                // do a fast load
                mpl::identity<load_only>,
            // else
            // do a fast load only tracking is turned off
            mpl::identity<load_conditional>
        > > >::type typex;
        check_object_versioning< T >();
        check_object_level< T >();
        typex::invoke(ar, t);
    }
};

template<class Archive>
struct load_pointer_type {
    struct abstract
    {
        template<class T>
        static const basic_pointer_iserializer * register_type(Archive & /* ar */){
            // it has? to be polymorphic
            BOOST_STATIC_ASSERT(boost::is_polymorphic< T >::value);
            return static_cast<basic_pointer_iserializer *>(NULL);
         }
    };

    struct non_abstract
    {
        template<class T>
        static const basic_pointer_iserializer * register_type(Archive & ar){
            return ar.register_type(static_cast<T *>(NULL));
        }
    };

    template<class T>
    static const basic_pointer_iserializer * register_type(Archive &ar, const T* const /*t*/){
        // there should never be any need to load an abstract polymorphic
        // class pointer.  Inhibiting code generation for this
        // permits abstract base classes to be used - note: exception
        // virtual serialize functions used for plug-ins
        typedef typename
            mpl::eval_if<
                boost::serialization::is_abstract<const T>,
                boost::mpl::identity<abstract>,
                boost::mpl::identity<non_abstract>
            >::type typex;
        return typex::template register_type< T >(ar);
    }

    template<class T>
    static T * pointer_tweak(
        const boost::serialization::extended_type_info & eti,
        void const * const t,
        const T &
    ) {
        // tweak the pointer back to the base class
        void * upcast = const_cast<void *>(
            boost::serialization::void_upcast(
                eti,
                boost::serialization::singleton<
                    typename
                    boost::serialization::type_info_implementation< T >::type
                >::get_const_instance(),
                t
            )
        );
        if(NULL == upcast)
            boost::serialization::throw_exception(
                archive_exception(archive_exception::unregistered_class)
            );
        return static_cast<T *>(upcast);
    }

    template<class T>
    static void check_load(T * const /* t */){
        check_pointer_level< T >();
        check_pointer_tracking< T >();
    }

    static const basic_pointer_iserializer *
    find(const boost::serialization::extended_type_info & type){
        return static_cast<const basic_pointer_iserializer *>(
            archive_serializer_map<Archive>::find(type)
        );
    }

    template<class Tptr>
    static void invoke(Archive & ar, Tptr & t){
        check_load(t);
        const basic_pointer_iserializer * bpis_ptr = register_type(ar, t);
        const basic_pointer_iserializer * newbpis_ptr = ar.load_pointer(
            // note major hack here !!!
            // I tried every way to convert Tptr &t (where Tptr might
            // include const) to void * &.  This is the only way
            // I could make it work. RR
            (void * & )t,
            bpis_ptr,
            find
        );
        // if the pointer isn't that of the base class
        if(newbpis_ptr != bpis_ptr){
            t = pointer_tweak(newbpis_ptr->get_eti(), t, *t);
        }
    }
};

template<class Archive>
struct load_enum_type {
    template<class T>
    static void invoke(Archive &ar, T &t){
        // convert integers to correct enum to load
        int i;
        ar >> boost::serialization::make_nvp(NULL, i);
        t = static_cast< T >(i);
    }
};

template<class Archive>
struct load_array_type {
    template<class T>
    static void invoke(Archive &ar, T &t){
        typedef typename remove_extent< T >::type value_type;

        // convert integers to correct enum to load
        // determine number of elements in the array. Consider the
        // fact that some machines will align elements on boundries
        // other than characters.
        std::size_t current_count = sizeof(t) / (
            static_cast<char *>(static_cast<void *>(&t[1]))
            - static_cast<char *>(static_cast<void *>(&t[0]))
        );
        boost::serialization::collection_size_type count;
        ar >> BOOST_SERIALIZATION_NVP(count);
        if(static_cast<std::size_t>(count) > current_count)
            boost::serialization::throw_exception(
                archive::archive_exception(
                    boost::archive::archive_exception::array_size_too_short
                )
            );
        // explict template arguments to pass intel C++ compiler
        ar >> serialization::make_array<
            value_type,
            boost::serialization::collection_size_type
        >(
            static_cast<value_type *>(&t[0]),
            count
        );
    }
};

} // detail

template<class Archive, class T>
inline void load(Archive & ar, T &t){
    // if this assertion trips. It means we're trying to load a
    // const object with a compiler that doesn't have correct
    // function template ordering.  On other compilers, this is
    // handled below.
    detail::check_const_loading< T >();
    typedef
        typename mpl::eval_if<is_pointer< T >,
            mpl::identity<detail::load_pointer_type<Archive> >
        ,//else
        typename mpl::eval_if<is_array< T >,
            mpl::identity<detail::load_array_type<Archive> >
        ,//else
        typename mpl::eval_if<is_enum< T >,
            mpl::identity<detail::load_enum_type<Archive> >
        ,//else
            mpl::identity<detail::load_non_pointer_type<Archive> >
        >
        >
        >::type typex;
    typex::invoke(ar, t);
}

} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_DETAIL_ISERIALIZER_HPP

/* iserializer.hpp
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
*/