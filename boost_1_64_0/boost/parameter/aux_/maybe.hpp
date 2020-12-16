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
0RnpMpl3+5i3+Zg3+pgDfMykqZL5fEZl83Ef8y4xR3E+2zD376TBQzpeahO7OV67Lh67y712HT12GV67dI9dD69dB49d274euw6dPXZJXrtOHrs4r52OI8Jrp+MI8trpON7oo+3aeexe9dqleexe0HbtdX63eu10fh/z2uk0P+S102m+12un07zWa6fTXO610+mb7LXT6SvUdu10+rK9djp9Xbx2On3tvHY6fS29djp9zbx2Kn0x8p6A0efXM/f58q5AaQD20o/LuwLm9wfw71Lt65garwunTp+cy+XK301ZbAxApmecdZF6NMLMAb5jUWExrzxX+XaE1ViDX92/11ZuS8unW58FgNuL+6aC/oaESQ+1DTvi8LwfMU6FSX+r3xmUvIbJvlkJ+BLke/JaWiWvExjN1XRAHfxXyzvuWuVX/NvVuyJL0Wcm8dAZq3NFLuU1EacjLDDI6QrFrdJJw3gjLDWx0u8azVJhNDe/r6LfQZ2jriXLuyXV66lO5Toj7w5J/uXFpXjx0BBpgmGLZf7HF5eXVcq7Ts9W5T7WShcSlryLp+YZjD8Sliev25Sb2tZntNSwPvjmM8Z8rr6O013+fST/z9b2eWdayv+wZf5lbqpqgI8eJB/HBvj/tsxhyUecUSdc6L621AlnrbAQVRks6oLo95Ty20SPl5EDVVjmuqHnWd8NcF+R93G130CeNDOf+MV1xqOzbXWs20zCQCudyb2H0tmF2w1h6HazDf0srXPx7abFQP/tptXAX6fdZIVXfqczGEkgLTmWOqhZ3nMG/rJ6bu7PsiL89GeW6Zo0s6blUmoql5HkPSHi4stlVjXlMudXKheb+p+0Ix5jU6M/s8y/+11ac971GVPKfW3K1W7dp/0KZbUtsvIZdY0lrXus0qoPOLFO7z5Jb6hleiVM0/vJm2pwdlq19V8UXEc81JZ6Zhvkm/bisuzcgtz8GtQx26BfrtP+kq4cmbRcbScemMV/zdBpgildQ6/IzM7NzzffscvSiM10P6vahf5GUV/lv4V9pLwX+zFilQfi0fOcrlHu8x9U2cp9TLK6PtR+Hf9/gPyEDLBbv+9uDmuC0reRYu8942R1/aCtDTO5ZchTSJTRPqPcm5WijPZZq2KFp8yvjJJv7Ymbjbip63bzqcfNDjkPvitmo0yjuV4P4d5JsRTGwIkmMzSbyetVar3rqSICCKqy3qXr7GaV/hxGpUE1fp9azWUpG/OcFz1jp/RsrqNYVu2jU432dXnlukDrSpOuQOl6Ir7tomuLMsZ/zeqpJ81GePUkPHNdXS3pixVP9ZH745gnVE2fRV0ts8VQjgGEUYrEGOUYzlQCesqyfrStRv2pee6fFiO6EgdBSKt4/htcJU2MajXTl23wv6cvT3mejKl6X9KatEVYpE2KU6WvdUOdPl33opWfcFuI5XlKEqapv4y9iDPYiK9S+gdJ+nfWr7zWEI60Jf1pPukvoz5aFrjk5xGlb8OyzDLthKfn27jlb2pJfrZyr+eIHZWbsBrnyQinnsRpPnNlu5zB30D2ncfCNPKU6c4TH8TNm5RdNqO4vGC8zJ7VAQQqH8cjPPmwqjcShunbSP6+wSfusNNnsEyfwQI1R2rpvnK4cuOyv0Lqv0UcdofVOqQOK0bPUSTxlMf49t7xYKRyF2Hfzv+nELvdwo+c7pAo859rlR9iJ5TGtPbOSC4t7U4056lnpRfxrSX0J2XiPfvoB9O9j0ufCaP1oe6FiwZXPhdmgY95vY/5Tyaz+dzh/Djdb6m/GKQ4irnRFe6yN1Imh2vJGKbHQ8vyxp+5zTGm1LzNTfAZA/pIGjfINwluQdz7eLGjMPa401jdIj5hqzFcnzE=
*/