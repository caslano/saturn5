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
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
*/