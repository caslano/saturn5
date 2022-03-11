// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//
// 2009.10.21 TDS remove depenency on boost::python::detail::referent_storage
//
#ifndef BOOST_PARAMETER_MAYBE_091021_HPP
#define BOOST_PARAMETER_MAYBE_091021_HPP

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct referent_size;
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct referent_size<T&>
    {
        BOOST_STATIC_CONSTANT(::std::size_t, value = sizeof(T));
    };
}}} // namespace boost::parameter::aux

#include <boost/type_traits/aligned_storage.hpp>

namespace boost { namespace parameter { namespace aux {

    // A metafunction returning a POD type which can store U, where T == U&.
    // If T is not a reference type, returns a POD which can store T.
    template <typename T>
    struct referent_storage
      : ::boost::aligned_storage<
            ::boost::parameter::aux::referent_size<T>::value
        >
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/is_maybe.hpp>
#include <boost/optional/optional.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#include <boost/type_traits/add_const.hpp>
#endif
#endif  // BOOST_PARAMETER_CAN_USE_MP11

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct maybe : ::boost::parameter::aux::maybe_base
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        typedef typename ::std::add_lvalue_reference<
            typename ::std::add_const<T>::type
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
        typedef typename ::boost::add_lvalue_reference<
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
            T const
#else
            typename ::boost::add_const<T>::type
#endif
#endif  // BOOST_PARAMETER_CAN_USE_MP11
        >::type reference;

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        typedef typename ::std::remove_cv<
            typename ::std::remove_reference<reference>::type
#else
        typedef typename ::boost::remove_cv<
            BOOST_DEDUCED_TYPENAME ::boost::remove_reference<reference>::type
#endif
        >::type non_cv_value;

        inline explicit maybe(T value_) : value(value_), constructed(false)
        {
        }

        inline maybe() : value(), constructed(false)
        {
        }

        ~maybe()
        {
            if (this->constructed)
            {
                this->destroy();
            }
        }

        inline reference construct(reference value_) const
        {
            return value_;
        }

        template <typename U>
        reference construct2(U const& value_) const
        {
            new (this->m_storage.address()) non_cv_value(value_);
            this->constructed = true;
            return *reinterpret_cast<non_cv_value*>(
                this->m_storage.address()
            );
        }

        template <typename U>
        inline reference construct(U const& value_) const
        {
            return this->construct2(value_);
        }

        void destroy()
        {
            reinterpret_cast<non_cv_value*>(
                this->m_storage.address()
            )->~non_cv_value();
        }

        typedef reference(
            ::boost::parameter::aux::maybe<T>::*safe_bool
        )() const;

        inline operator safe_bool() const
        {
            return this->value ? &::boost::parameter::aux::maybe<T>::get : 0;
        }

        inline reference get() const
        {
            return this->value.get();
        }

     private:
        ::boost::optional<T> value;
        mutable bool constructed;
        mutable typename ::boost::parameter::aux
        ::referent_storage<reference>::type m_storage;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* maybe.hpp
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
*/