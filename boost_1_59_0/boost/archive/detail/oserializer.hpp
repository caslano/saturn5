#ifndef BOOST_ARCHIVE_OSERIALIZER_HPP
#define BOOST_ARCHIVE_OSERIALIZER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#if !defined(__clang__)
#pragma inline_depth(255)
#pragma inline_recursion(on)
#endif
#endif

#if defined(__MWERKS__)
#pragma inline_depth(255)
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// oserializer.hpp: interface for serialization system.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>
#include <cstddef> // NULL

#include <boost/config.hpp>

#include <boost/static_assert.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/bool_fwd.hpp>

#ifndef BOOST_SERIALIZATION_DEFAULT_TYPE_INFO
    #include <boost/serialization/extended_type_info_typeid.hpp>
#endif
#include <boost/serialization/throw_exception.hpp>
#include <boost/serialization/smart_cast.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/static_warning.hpp>

#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/type_traits/remove_extent.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/type_info_implementation.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/void_cast.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/array_wrapper.hpp>

#include <boost/serialization/singleton.hpp>

#include <boost/archive/archive_exception.hpp>
#include <boost/archive/detail/basic_oarchive.hpp>
#include <boost/archive/detail/basic_oserializer.hpp>
#include <boost/archive/detail/basic_pointer_oserializer.hpp>
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
class save_access {
public:
    template<class Archive>
    static void end_preamble(Archive & ar){
        ar.end_preamble();
    }
    template<class Archive, class T>
    static void save_primitive(Archive & ar, const  T & t){
        ar.end_preamble();
        ar.save(t);
    }
};

namespace detail {

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

template<class Archive, class T>
class oserializer : public basic_oserializer
{
private:
    // private constructor to inhibit any existence other than the
    // static one
public:
    explicit BOOST_DLLEXPORT oserializer() :
        basic_oserializer(
            boost::serialization::singleton<
                typename
                boost::serialization::type_info_implementation< T >::type
            >::get_const_instance()
        )
    {}
    BOOST_DLLEXPORT void save_object_data(
        basic_oarchive & ar,
        const void *x
    ) const BOOST_OVERRIDE BOOST_USED;
    bool class_info() const BOOST_OVERRIDE {
        return boost::serialization::implementation_level< T >::value
            >= boost::serialization::object_class_info;
    }
    bool tracking(const unsigned int /* flags */) const BOOST_OVERRIDE {
        return boost::serialization::tracking_level< T >::value == boost::serialization::track_always
            || (boost::serialization::tracking_level< T >::value == boost::serialization::track_selectively
                && serialized_as_pointer());
    }
    version_type version() const BOOST_OVERRIDE {
        return version_type(::boost::serialization::version< T >::value);
    }
    bool is_polymorphic() const BOOST_OVERRIDE {
        return boost::is_polymorphic< T >::value;
    }
    ~oserializer() BOOST_OVERRIDE {}
};

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

template<class Archive, class T>
BOOST_DLLEXPORT void oserializer<Archive, T>::save_object_data(
    basic_oarchive & ar,
    const void *x
) const {
    // make sure call is routed through the highest interface that might
    // be specialized by the user.
    BOOST_STATIC_ASSERT(boost::is_const< T >::value == false);
    boost::serialization::serialize_adl(
        boost::serialization::smart_cast_reference<Archive &>(ar),
        * static_cast<T *>(const_cast<void *>(x)),
        version()
    );
}

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

template<class Archive, class T>
class pointer_oserializer :
    public basic_pointer_oserializer
{
private:
    const basic_oserializer &
    get_basic_serializer() const BOOST_OVERRIDE {
        return boost::serialization::singleton<
            oserializer<Archive, T>
        >::get_const_instance();
    }
    BOOST_DLLEXPORT void save_object_ptr(
        basic_oarchive & ar,
        const void * x
    ) const BOOST_OVERRIDE BOOST_USED;
public:
    pointer_oserializer();
    ~pointer_oserializer() BOOST_OVERRIDE;
};

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

template<class Archive, class T>
BOOST_DLLEXPORT void pointer_oserializer<Archive, T>::save_object_ptr(
    basic_oarchive & ar,
    const void * x
) const {
    BOOST_ASSERT(NULL != x);
    // make sure call is routed through the highest interface that might
    // be specialized by the user.
    T * t = static_cast<T *>(const_cast<void *>(x));
    const unsigned int file_version = boost::serialization::version< T >::value;
    Archive & ar_impl
        = boost::serialization::smart_cast_reference<Archive &>(ar);
    boost::serialization::save_construct_data_adl<Archive, T>(
        ar_impl,
        t,
        file_version
    );
    ar_impl << boost::serialization::make_nvp(NULL, * t);
}

template<class Archive, class T>
pointer_oserializer<Archive, T>::pointer_oserializer() :
    basic_pointer_oserializer(
        boost::serialization::singleton<
            typename
            boost::serialization::type_info_implementation< T >::type
        >::get_const_instance()
    )
{
    // make sure appropriate member function is instantiated
    boost::serialization::singleton<
        oserializer<Archive, T>
    >::get_mutable_instance().set_bpos(this);
    archive_serializer_map<Archive>::insert(this);
}

template<class Archive, class T>
pointer_oserializer<Archive, T>::~pointer_oserializer(){
    archive_serializer_map<Archive>::erase(this);
}

template<class Archive>
struct save_non_pointer_type {
    // note this bounces the call right back to the archive
    // with no runtime overhead
    struct save_primitive {
        template<class T>
        static void invoke(Archive & ar, const T & t){
            save_access::save_primitive(ar, t);
        }
    };
    // same as above but passes through serialization
    struct save_only {
        template<class T>
        static void invoke(Archive & ar, const T & t){
            // make sure call is routed through the highest interface that might
            // be specialized by the user.
            boost::serialization::serialize_adl(
                ar,
                const_cast<T &>(t),
                ::boost::serialization::version< T >::value
            );
        }
    };
    // adds class information to the archive. This includes
    // serialization level and class version
    struct save_standard {
        template<class T>
        static void invoke(Archive &ar, const T & t){
            ar.save_object(
                boost::addressof(t),
                boost::serialization::singleton<
                    oserializer<Archive, T>
                >::get_const_instance()
            );
        }
    };



    // adds class information to the archive. This includes
    // serialization level and class version
    struct save_conditional {
        template<class T>
        static void invoke(Archive &ar, const T &t){
            //if(0 == (ar.get_flags() & no_tracking))
                save_standard::invoke(ar, t);
            //else
            //   save_only::invoke(ar, t);
        }
    };


    template<class T>
    static void invoke(Archive & ar, const T & t){
        typedef
            typename mpl::eval_if<
            // if its primitive
                mpl::equal_to<
                    boost::serialization::implementation_level< T >,
                    mpl::int_<boost::serialization::primitive_type>
                >,
                mpl::identity<save_primitive>,
            // else
            typename mpl::eval_if<
                // class info / version
                mpl::greater_equal<
                    boost::serialization::implementation_level< T >,
                    mpl::int_<boost::serialization::object_class_info>
                >,
                // do standard save
                mpl::identity<save_standard>,
            // else
            typename mpl::eval_if<
                    // no tracking
                mpl::equal_to<
                    boost::serialization::tracking_level< T >,
                    mpl::int_<boost::serialization::track_never>
                >,
                // do a fast save
                mpl::identity<save_only>,
            // else
                // do a fast save only tracking is turned off
                mpl::identity<save_conditional>
            > > >::type typex;
        check_object_versioning< T >();
        typex::invoke(ar, t);
    }
    template<class T>
    static void invoke(Archive & ar, T & t){
        check_object_level< T >();
        check_object_tracking< T >();
        invoke(ar, const_cast<const T &>(t));
    }
};

template<class Archive>
struct save_pointer_type {
    struct abstract
    {
        template<class T>
        static const basic_pointer_oserializer * register_type(Archive & /* ar */){
            // it has? to be polymorphic
            BOOST_STATIC_ASSERT(boost::is_polymorphic< T >::value);
            return NULL;
        }
    };

    struct non_abstract
    {
        template<class T>
        static const basic_pointer_oserializer * register_type(Archive & ar){
            return ar.register_type(static_cast<T *>(NULL));
        }
    };

    template<class T>
    static const basic_pointer_oserializer * register_type(Archive &ar, T* const /*t*/){
        // there should never be any need to save an abstract polymorphic
        // class pointer.  Inhibiting code generation for this
        // permits abstract base classes to be used - note: exception
        // virtual serialize functions used for plug-ins
        typedef
            typename mpl::eval_if<
                boost::serialization::is_abstract< T >,
                mpl::identity<abstract>,
                mpl::identity<non_abstract>
            >::type typex;
        return typex::template register_type< T >(ar);
    }

    struct non_polymorphic
    {
        template<class T>
        static void save(
            Archive &ar,
            T & t
        ){
            const basic_pointer_oserializer & bpos =
                boost::serialization::singleton<
                    pointer_oserializer<Archive, T>
                >::get_const_instance();
            // save the requested pointer type
            ar.save_pointer(& t, & bpos);
        }
    };

    struct polymorphic
    {
        template<class T>
        static void save(
            Archive &ar,
            T & t
        ){
            typename
            boost::serialization::type_info_implementation< T >::type const
            & i = boost::serialization::singleton<
                typename
                boost::serialization::type_info_implementation< T >::type
            >::get_const_instance();

            boost::serialization::extended_type_info const * const this_type = & i;

            // retrieve the true type of the object pointed to
            // if this assertion fails its an error in this library
            BOOST_ASSERT(NULL != this_type);

            const boost::serialization::extended_type_info * true_type =
                i.get_derived_extended_type_info(t);

            // note:if this exception is thrown, be sure that derived pointer
            // is either registered or exported.
            if(NULL == true_type){
                boost::serialization::throw_exception(
                    archive_exception(
                        archive_exception::unregistered_class,
                        "derived class not registered or exported"
                    )
                );
            }

            // if its not a pointer to a more derived type
            const void *vp = static_cast<const void *>(&t);
            if(*this_type == *true_type){
                const basic_pointer_oserializer * bpos = register_type(ar, &t);
                ar.save_pointer(vp, bpos);
                return;
            }
            // convert pointer to more derived type. if this is thrown
            // it means that the base/derived relationship hasn't be registered
            vp = serialization::void_downcast(
                *true_type,
                *this_type,
                static_cast<const void *>(&t)
            );
            if(NULL == vp){
                boost::serialization::throw_exception(
                    archive_exception(
                        archive_exception::unregistered_cast,
                        true_type->get_debug_info(),
                        this_type->get_debug_info()
                    )
                );
            }

            // since true_type is valid, and this only gets made if the
            // pointer oserializer object has been created, this should never
            // fail
            const basic_pointer_oserializer * bpos
                = static_cast<const basic_pointer_oserializer *>(
                    boost::serialization::singleton<
                        archive_serializer_map<Archive>
                    >::get_const_instance().find(*true_type)
                );
            BOOST_ASSERT(NULL != bpos);
            if(NULL == bpos)
                boost::serialization::throw_exception(
                    archive_exception(
                        archive_exception::unregistered_class,
                        "derived class not registered or exported"
                    )
                );
            ar.save_pointer(vp, bpos);
        }
    };

    template<class T>
    static void save(
        Archive & ar,
        const T & t
    ){
        check_pointer_level< T >();
        check_pointer_tracking< T >();
        typedef typename mpl::eval_if<
            is_polymorphic< T >,
            mpl::identity<polymorphic>,
            mpl::identity<non_polymorphic>
        >::type type;
        type::save(ar, const_cast<T &>(t));
    }

    template<class TPtr>
    static void invoke(Archive &ar, const TPtr t){
        register_type(ar, t);
        if(NULL == t){
            basic_oarchive & boa
                = boost::serialization::smart_cast_reference<basic_oarchive &>(ar);
            boa.save_null_pointer();
            save_access::end_preamble(ar);
            return;
        }
        save(ar, * t);
    }
};

template<class Archive>
struct save_enum_type
{
    template<class T>
    static void invoke(Archive &ar, const T &t){
        // convert enum to integers on save
        const int i = static_cast<int>(t);
        ar << boost::serialization::make_nvp(NULL, i);
    }
};

template<class Archive>
struct save_array_type
{
    template<class T>
    static void invoke(Archive &ar, const T &t){
        typedef typename boost::remove_extent< T >::type value_type;

        save_access::end_preamble(ar);
        // consider alignment
        std::size_t c = sizeof(t) / (
            static_cast<const char *>(static_cast<const void *>(&t[1]))
            - static_cast<const char *>(static_cast<const void *>(&t[0]))
        );
        boost::serialization::collection_size_type count(c);
        ar << BOOST_SERIALIZATION_NVP(count);
        // explict template arguments to pass intel C++ compiler
        ar << serialization::make_array<
            const value_type,
            boost::serialization::collection_size_type
        >(
            static_cast<const value_type *>(&t[0]),
            count
        );
    }
};

} // detail

template<class Archive, class T>
inline void save(Archive & ar, /*const*/ T &t){
    typedef
        typename mpl::eval_if<is_pointer< T >,
            mpl::identity<detail::save_pointer_type<Archive> >,
        //else
        typename mpl::eval_if<is_enum< T >,
            mpl::identity<detail::save_enum_type<Archive> >,
        //else
        typename mpl::eval_if<is_array< T >,
            mpl::identity<detail::save_array_type<Archive> >,
        //else
            mpl::identity<detail::save_non_pointer_type<Archive> >
        >
        >
        >::type typex;
    typex::invoke(ar, t);
}

} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_OSERIALIZER_HPP

/* oserializer.hpp
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
*/