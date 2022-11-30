#ifndef BOOST_SERIALIZATION_VOID_CAST_HPP
#define BOOST_SERIALIZATION_VOID_CAST_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// void_cast.hpp:   interface for run-time casting of void pointers.

// (C) Copyright 2002-2009 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// gennadiy.rozental@tfn.com

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstddef> // for ptrdiff_t
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>

#include <boost/serialization/smart_cast.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/serialization/force_include.hpp>
#include <boost/serialization/type_info_implementation.hpp>
#include <boost/serialization/extended_type_info.hpp>
#include <boost/type_traits/is_virtual_base_of.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/serialization/void_cast_fwd.hpp>

#include <boost/serialization/config.hpp>
#include <boost/config/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4251 4231 4660 4275)
#endif

namespace boost {
namespace serialization {

class extended_type_info;

// Given a void *, assume that it really points to an instance of one type
// and alter it so that it would point to an instance of a related type.
// Return the altered pointer. If there exists no sequence of casts that
// can transform from_type to to_type, return a NULL.

BOOST_SERIALIZATION_DECL void const *
void_upcast(
    extended_type_info const & derived,
    extended_type_info const & base,
    void const * const t
);

inline void *
void_upcast(
    extended_type_info const & derived,
    extended_type_info const & base,
    void * const t
){
    return const_cast<void*>(void_upcast(
        derived,
        base,
        const_cast<void const *>(t)
    ));
}

BOOST_SERIALIZATION_DECL void const *
void_downcast(
    extended_type_info const & derived,
    extended_type_info const & base,
    void const * const t
);

inline void *
void_downcast(
    extended_type_info const & derived,
    extended_type_info const & base,
    void * const t
){
    return const_cast<void*>(void_downcast(
        derived,
        base,
        const_cast<void const *>(t)
    ));
}

namespace void_cast_detail {

class BOOST_SYMBOL_VISIBLE void_caster :
    private boost::noncopyable
{
    friend
    BOOST_SERIALIZATION_DECL void const *
    boost::serialization::void_upcast(
        extended_type_info const & derived,
        extended_type_info const & base,
        void const * const
    );
    friend
    BOOST_SERIALIZATION_DECL void const *
    boost::serialization::void_downcast(
        extended_type_info const & derived,
        extended_type_info const & base,
        void const * const
    );
protected:
    BOOST_SERIALIZATION_DECL void recursive_register(bool includes_virtual_base = false) const;
    BOOST_SERIALIZATION_DECL void recursive_unregister() const;
    virtual bool has_virtual_base() const = 0;
public:
    // Data members
    const extended_type_info * m_derived;
    const extended_type_info * m_base;
    /*const*/ std::ptrdiff_t m_difference;
    void_caster const * const m_parent;

    // note that void_casters are keyed on value of
    // member extended type info records - NOT their
    // addresses.  This is necessary in order for the
    // void cast operations to work across dll and exe
    // module boundaries.
    bool operator<(const void_caster & rhs) const;

    const void_caster & operator*(){
        return *this;
    }
    // each derived class must re-implement these;
    virtual void const * upcast(void const * const t) const = 0;
    virtual void const * downcast(void const * const t) const = 0;
    // Constructor
    void_caster(
        extended_type_info const * derived,
        extended_type_info const * base,
        std::ptrdiff_t difference = 0,
        void_caster const * const parent = 0
    ) :
        m_derived(derived),
        m_base(base),
        m_difference(difference),
        m_parent(parent)
    {}
    virtual ~void_caster(){}
};

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4251 4231 4660 4275 4511 4512)
#endif

template <class Derived, class Base>
class BOOST_SYMBOL_VISIBLE void_caster_primitive :
    public void_caster
{
    void const * downcast(void const * const t) const BOOST_OVERRIDE {
        const Derived * d =
            boost::serialization::smart_cast<const Derived *, const Base *>(
                static_cast<const Base *>(t)
            );
        return d;
    }
    void const * upcast(void const * const t) const BOOST_OVERRIDE {
        const Base * b =
            boost::serialization::smart_cast<const Base *, const Derived *>(
                static_cast<const Derived *>(t)
            );
        return b;
    }
    bool has_virtual_base() const BOOST_OVERRIDE {
        return false;
    }
public:
    void_caster_primitive();
    ~void_caster_primitive() BOOST_OVERRIDE;

private:
    static std::ptrdiff_t base_offset() {
        typename boost::aligned_storage<sizeof(Derived)>::type data;
        return reinterpret_cast<char*>(&data)
             - reinterpret_cast<char*>(
                   static_cast<Base*>(
                       reinterpret_cast<Derived*>(&data)));
    }
};

template <class Derived, class Base>
void_caster_primitive<Derived, Base>::void_caster_primitive() :
    void_caster(
        & type_info_implementation<Derived>::type::get_const_instance(),
        & type_info_implementation<Base>::type::get_const_instance(),
        base_offset()
    )
{
    recursive_register();
}

template <class Derived, class Base>
void_caster_primitive<Derived, Base>::~void_caster_primitive(){
    recursive_unregister();
}

template <class Derived, class Base>
class BOOST_SYMBOL_VISIBLE void_caster_virtual_base :
    public void_caster
{
    bool has_virtual_base() const BOOST_OVERRIDE {
        return true;
    }
public:
    void const * downcast(void const * const t) const BOOST_OVERRIDE {
        const Derived * d =
            dynamic_cast<const Derived *>(
                static_cast<const Base *>(t)
            );
        return d;
    }
    void const * upcast(void const * const t) const BOOST_OVERRIDE {
        const Base * b =
            dynamic_cast<const Base *>(
                static_cast<const Derived *>(t)
            );
        return b;
    }
    void_caster_virtual_base();
    ~void_caster_virtual_base() BOOST_OVERRIDE;
};

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

template <class Derived, class Base>
void_caster_virtual_base<Derived,Base>::void_caster_virtual_base() :
    void_caster(
        & (type_info_implementation<Derived>::type::get_const_instance()),
        & (type_info_implementation<Base>::type::get_const_instance())
    )
{
    recursive_register(true);
}

template <class Derived, class Base>
void_caster_virtual_base<Derived,Base>::~void_caster_virtual_base(){
    recursive_unregister();
}

template <class Derived, class Base>
struct BOOST_SYMBOL_VISIBLE void_caster_base :
    public void_caster
{
    typedef
        typename mpl::eval_if<boost::is_virtual_base_of<Base,Derived>,
            mpl::identity<
                void_cast_detail::void_caster_virtual_base<Derived, Base>
            >
        ,// else
            mpl::identity<
                void_cast_detail::void_caster_primitive<Derived, Base>
            >
        >::type type;
};

} // void_cast_detail

template<class Derived, class Base>
BOOST_DLLEXPORT
inline const void_cast_detail::void_caster & void_cast_register(
    Derived const * /* dnull = NULL */,
    Base const * /* bnull = NULL */
){
    typedef
        typename mpl::eval_if<boost::is_virtual_base_of<Base,Derived>,
            mpl::identity<
                void_cast_detail::void_caster_virtual_base<Derived, Base>
            >
        ,// else
            mpl::identity<
                void_cast_detail::void_caster_primitive<Derived, Base>
            >
        >::type typex;
    return singleton<typex>::get_const_instance();
}

template<class Derived, class Base>
class BOOST_SYMBOL_VISIBLE void_caster :
    public void_cast_detail::void_caster_base<Derived, Base>::type
{
};

} // namespace serialization
} // namespace boost

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

#include <boost/config/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_SERIALIZATION_VOID_CAST_HPP

/* void_cast.hpp
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
*/