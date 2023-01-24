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
o3JqYMVvHb6klmV/bMdE/aG0dXf/7ntuqwht+nKo2+scAkfEHgm9GsEbcjbRL45n6zOUh7c3N0AgzqOk5IoY3PMBw/ix+b7lV1MTlv+yZGh3c1wNwYhVt64gdcJlYsUqow/kr0q5YUm68/D274z7XTQ1YnVfHJ1XCOYi+pgrFfeIz1yDJGg8j662SIVd1qL3a4ylJNuJDDg8lJT0NcWz+L1/3ZZ+9v4hAGPciDQTS1m6ZWMqaKVoI7d5rgR/97k0zvmR59qHJVflDavNcdG9nhDGwdXpal6oXTLAsNCbJYCp9FS8QJ7BO/Z70mJ3Y8XR1Iu9SHgme6nzr6IKXNm+3Bexlx5sbc3+WWZpDaan4L5pYuKY8wMbcvqX+IPYvJY25OrpU7xyBHBXoo9uH3VtXOoiSy6V7Usp+NaDh4IgNPEsPpKst5vXpUUtlgLP+yP7khZ5cCHLwdMDj+lfA0d7kLvpvsn+BgLaIMG5Qz92k7RVLFXVtKw80Dfs9DJag7gyVbjxd/fBTCsPzeM6P+xlFZODeWiWKrAi2ZkLaIjldYL3RyvGhaqevoazZJwz+gxUQSuy2m10zFQPxT+9x/BHjXmBHI34h28pZvQGhWchZXi+ofdzJX4GVS8kKO2W73cf0kYug5Mc9s1RmdoUimXajwyPunPcAUeS6hA0TcDzOm7IdWQgKNA35fbSCDbi4ZwLW/JtCG4pFmGhe/xS
*/