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
#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
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
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
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