// See http://www.boost.org/libs/any for Documentation.

#ifndef BOOST_ANY_INCLUDED
#define BOOST_ANY_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

// what:  variant type boost::any
// who:   contributed by Kevlin Henney,
//        with features contributed and bugs found by
//        Antony Polukhin, Ed Brey, Mark Rodgers, 
//        Peter Dimov, and James Curran
// when:  July 2001, April 2013 - 2020

#include <boost/config.hpp>
#include <boost/type_index.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/throw_exception.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/core/addressof.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/conditional.hpp>

namespace boost
{
    class any
    {
    public: // structors

        BOOST_CONSTEXPR any() BOOST_NOEXCEPT
          : content(0)
        {
        }

        template<typename ValueType>
        any(const ValueType & value)
          : content(new holder<
                BOOST_DEDUCED_TYPENAME remove_cv<BOOST_DEDUCED_TYPENAME decay<const ValueType>::type>::type
            >(value))
        {
        }

        any(const any & other)
          : content(other.content ? other.content->clone() : 0)
        {
        }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        // Move constructor
        any(any&& other) BOOST_NOEXCEPT
          : content(other.content)
        {
            other.content = 0;
        }

        // Perfect forwarding of ValueType
        template<typename ValueType>
        any(ValueType&& value
            , typename boost::disable_if<boost::is_same<any&, ValueType> >::type* = 0 // disable if value has type `any&`
            , typename boost::disable_if<boost::is_const<ValueType> >::type* = 0) // disable if value has type `const ValueType&&`
          : content(new holder< typename decay<ValueType>::type >(static_cast<ValueType&&>(value)))
        {
        }
#endif

        ~any() BOOST_NOEXCEPT
        {
            delete content;
        }

    public: // modifiers

        any & swap(any & rhs) BOOST_NOEXCEPT
        {
            placeholder* tmp = content;
            content = rhs.content;
            rhs.content = tmp;
            return *this;
        }


#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
        template<typename ValueType>
        any & operator=(const ValueType & rhs)
        {
            any(rhs).swap(*this);
            return *this;
        }

        any & operator=(any rhs)
        {
            rhs.swap(*this);
            return *this;
        }

#else 
        any & operator=(const any& rhs)
        {
            any(rhs).swap(*this);
            return *this;
        }

        // move assignment
        any & operator=(any&& rhs) BOOST_NOEXCEPT
        {
            rhs.swap(*this);
            any().swap(rhs);
            return *this;
        }

        // Perfect forwarding of ValueType
        template <class ValueType>
        any & operator=(ValueType&& rhs)
        {
            any(static_cast<ValueType&&>(rhs)).swap(*this);
            return *this;
        }
#endif

    public: // queries

        bool empty() const BOOST_NOEXCEPT
        {
            return !content;
        }

        void clear() BOOST_NOEXCEPT
        {
            any().swap(*this);
        }

        const boost::typeindex::type_info& type() const BOOST_NOEXCEPT
        {
            return content ? content->type() : boost::typeindex::type_id<void>().type_info();
        }

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    private: // types
#else
    public: // types (public so any_cast can be non-friend)
#endif

        class BOOST_SYMBOL_VISIBLE placeholder
        {
        public: // structors

            virtual ~placeholder()
            {
            }

        public: // queries

            virtual const boost::typeindex::type_info& type() const BOOST_NOEXCEPT = 0;

            virtual placeholder * clone() const = 0;

        };

        template<typename ValueType>
        class holder
#ifndef BOOST_NO_CXX11_FINAL
          final
#endif
          : public placeholder
        {
        public: // structors

            holder(const ValueType & value)
              : held(value)
            {
            }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            holder(ValueType&& value)
              : held(static_cast< ValueType&& >(value))
            {
            }
#endif
        public: // queries

            virtual const boost::typeindex::type_info& type() const BOOST_NOEXCEPT
            {
                return boost::typeindex::type_id<ValueType>().type_info();
            }

            virtual placeholder * clone() const
            {
                return new holder(held);
            }

        public: // representation

            ValueType held;

        private: // intentionally left unimplemented
            holder & operator=(const holder &);
        };

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS

    private: // representation

        template<typename ValueType>
        friend ValueType * any_cast(any *) BOOST_NOEXCEPT;

        template<typename ValueType>
        friend ValueType * unsafe_any_cast(any *) BOOST_NOEXCEPT;

#else

    public: // representation (public so any_cast can be non-friend)

#endif

        placeholder * content;

    };
 
    inline void swap(any & lhs, any & rhs) BOOST_NOEXCEPT
    {
        lhs.swap(rhs);
    }

    class BOOST_SYMBOL_VISIBLE bad_any_cast :
#ifndef BOOST_NO_RTTI
        public std::bad_cast
#else
        public std::exception
#endif
    {
    public:
        virtual const char * what() const BOOST_NOEXCEPT_OR_NOTHROW
        {
            return "boost::bad_any_cast: "
                   "failed conversion using boost::any_cast";
        }
    };

    template<typename ValueType>
    ValueType * any_cast(any * operand) BOOST_NOEXCEPT
    {
        return operand && operand->type() == boost::typeindex::type_id<ValueType>()
            ? boost::addressof(
                static_cast<any::holder<BOOST_DEDUCED_TYPENAME remove_cv<ValueType>::type> *>(operand->content)->held
              )
            : 0;
    }

    template<typename ValueType>
    inline const ValueType * any_cast(const any * operand) BOOST_NOEXCEPT
    {
        return any_cast<ValueType>(const_cast<any *>(operand));
    }

    template<typename ValueType>
    ValueType any_cast(any & operand)
    {
        typedef BOOST_DEDUCED_TYPENAME remove_reference<ValueType>::type nonref;


        nonref * result = any_cast<nonref>(boost::addressof(operand));
        if(!result)
            boost::throw_exception(bad_any_cast());

        // Attempt to avoid construction of a temporary object in cases when 
        // `ValueType` is not a reference. Example:
        // `static_cast<std::string>(*result);` 
        // which is equal to `std::string(*result);`
        typedef BOOST_DEDUCED_TYPENAME boost::conditional<
            boost::is_reference<ValueType>::value,
            ValueType,
            BOOST_DEDUCED_TYPENAME boost::add_reference<ValueType>::type
        >::type ref_type;

#ifdef BOOST_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4172) // "returning address of local variable or temporary" but *result is not local!
#endif
        return static_cast<ref_type>(*result);
#ifdef BOOST_MSVC
#   pragma warning(pop)
#endif
    }

    template<typename ValueType>
    inline ValueType any_cast(const any & operand)
    {
        typedef BOOST_DEDUCED_TYPENAME remove_reference<ValueType>::type nonref;
        return any_cast<const nonref &>(const_cast<any &>(operand));
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    template<typename ValueType>
    inline ValueType any_cast(any&& operand)
    {
        BOOST_STATIC_ASSERT_MSG(
            boost::is_rvalue_reference<ValueType&&>::value /*true if ValueType is rvalue or just a value*/
            || boost::is_const< typename boost::remove_reference<ValueType>::type >::value,
            "boost::any_cast shall not be used for getting nonconst references to temporary objects" 
        );
        return any_cast<ValueType>(operand);
    }
#endif


    // Note: The "unsafe" versions of any_cast are not part of the
    // public interface and may be removed at any time. They are
    // required where we know what type is stored in the any and can't
    // use typeid() comparison, e.g., when our types may travel across
    // different shared libraries.
    template<typename ValueType>
    inline ValueType * unsafe_any_cast(any * operand) BOOST_NOEXCEPT
    {
        return boost::addressof(
            static_cast<any::holder<ValueType> *>(operand->content)->held
        );
    }

    template<typename ValueType>
    inline const ValueType * unsafe_any_cast(const any * operand) BOOST_NOEXCEPT
    {
        return unsafe_any_cast<ValueType>(const_cast<any *>(operand));
    }
}

// Copyright Kevlin Henney, 2000, 2001, 2002. All rights reserved.
// Copyright Antony Polukhin, 2013-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#endif

/* any.hpp
Va9KQzcOwjlkEWX2yuYqoPN+nzH8JN+ClXA+9YEmg7RncqeC+HAI4C1FLryM5MsDq+OzaG2GykYN132uQzXGgbLPLwAPfWj3ntSPBbkhXp2Xaj3LUnZgHjVGaIjHaQmE16VspDOp34OQ2a4a2JyVqXaiCxL4vAJY6QpsW4oOBsaCTZpCa8N1jd0/YIF8shIq7jKF31tSthvpzID6pOJlSNhpajtqr/YJgWmLQ9BNVV1TXdYXtekWTIHzKR3ShofQjR4I+xGXAMPs6dH0J5Tl8NJ9OQFWMzSwT7erv+JSYxpl584A2qqNUn2pcWsBndndUffRQEjSzRjn070g8RY22Z/Wrs9kIRlXhmTxfOlr8ZAUiCc1NAzpi23VfZ7Lifl4A2L/Qzvka+TK/B6kR4OvIMuec7CqvZXUkHdwHukOIrgO1ew2kup4FAlCvFylH8BvameyrtrspWZp/bUmlT0A0Uq3IbUwP4LPNUGg1jnBTu8C8ZPC1HV2pyxvjPTxurThUo+x6r4aIfdlQ9K3KMO59RJNbmiPGMM70K3702CaOxhExclUezsasOkBJGvVZO9EGBzSaZsoWVrqKB06hVSmFsOuO2ADq9OtZ7oqzfqDCOpG1neK9PtsUk53qVtSbawd7AC/ZMq63WCEpqwnu9Ibulc7pO8eItu2IExLxeu+PGRJf89Rdn8cXX1eE/buPkb0d4zWs0H2jFLjG1Jj8RGNn4fshXEAe+2KTm1BPNTAllK3kjaRqm/FQCyLo24Jla15yAgNq6D7KJzWErQDxncH3JFAidpRBXRStzBF3H17tCbH0P2lHoxz1csgHpWnrkGL/+saiEcMlz4u7WuRBieHzLQdhe3pbzCpokvAmsiWfGUGcWM77bcNjMa9lohr/TvZ7EmwauVNjdzzKauo5Z0RQN2SbalxJswVfq1JddMMrlM25AwMWkgn3NcXUG8dQl7UDG44B0l9idazFimbSq5az4C30iy/SYebfA9QR2WHatPfedUAO+1gEKH7LVcCQxK6irKaxaEbdFPzOxNW2/ZoPVcHMWm3zucLSDBEI1mpH9XeraCXdl5M1NOiNJT2k8nrfh+639aCKO9F3Yt71N/c0l/ear0UBAz4zR35NEe9Uu2Rb7PsrWKkeo9TfweQujEWcGIjiJjGsDo3Qv0trPX81BL5pHPVr0/q/hFma/RjUiNOyV/SUvN7lLLJPykzHkhDmwPZpo3eMrp1c0Ny+KQp51UjJD25jmzL2nTmljOp7AgAe4rz/gIy9+8j/dmabLNWcEmQot77Iu2OkU6TeJ4eTRgD+JETkqm/mcCvLNnXh2goeoAF8l2F2MuTLnxdKv1lI+0eK6P9+wdAh7kQj18B0+rJ1DjbEAYrf7eEnwbCKof8G6aAiwIbVMNttfwbumwWRtvA7wb8tmsQm41Cvo9ejvAroPUX4sb8SoMqF03P796FZJ8XZX21WO/ZIdCzjXR1eATtHj0ne9WM1LWmcL6UpvN0PLIUsSF7fC3ZP+xiNCrngkGfA7DKl4mQuXqQcj0IvyPdYZUUQENme3Vfqsz3GSNkPg0w7gHEXY/Q1b0azvh6gOb+9CNnJmK8XwZokVfrT3XLF6DJsRNpvMktEFd9mKMgaVW5o2CwZjUp78NM7aZk+a+mQWJ8BPlS+tCFdQF0IW0JiBqFId43AnGzHCC5d5DWog9Dly1LLnYco5buifTtd0BcOwLspt1kBzRBtPyDaaObFKVPx+BSTmrAK932U9uSzRoAcY+3Ln/WN3aH6z4agZBN5VBrYI3gb4fD4HaS7LeG1Dg+GDHyTkWMeY+pm/Yc8GM/xJkxYNtmkD0izXJQdeiunoLpmywYlGgFeHw=
*/