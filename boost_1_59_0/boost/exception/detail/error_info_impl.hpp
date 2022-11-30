//Copyright (c) 2006-2010 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_CE6983AC753411DDA764247956D89593
#define BOOST_EXCEPTION_CE6983AC753411DDA764247956D89593

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
#include <boost/type_traits/is_nothrow_move_constructible.hpp>
#endif
#include <utility>
#include <string>

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    namespace
    exception_detail
        {
        class
        error_info_base
            {
            public:

            virtual std::string name_value_string() const = 0;
            virtual error_info_base * clone() const = 0;

            virtual
            ~error_info_base() BOOST_NOEXCEPT_OR_NOTHROW
                {
                }
            };
        }

    template <class Tag,class T>
    class
    error_info:
        public exception_detail::error_info_base
        {
        exception_detail::error_info_base *
        clone() const
            {
            return new error_info<Tag,T>(*this);
            }
        public:
        typedef T value_type;
        error_info( value_type const & v ):
            v_(v)
            {
            }
#if (__GNUC__*100+__GNUC_MINOR__!=406) //workaround for g++ bug
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        error_info( error_info const & x ):
            v_(x.v_)
            {
            }
        error_info( T && v ) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible<T>::value):
            v_(std::move(v))
            {
            }
        error_info( error_info && x ) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible<T>::value):
            v_(std::move(x.v_))
            {
            }
#endif
#endif
        ~error_info() BOOST_NOEXCEPT_OR_NOTHROW
            {
            }
        value_type const &
        value() const
            {
            return v_;
            }
        value_type &
        value()
            {
            return v_;
            }
        private:
        error_info & operator=( error_info const & );
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        error_info & operator=( error_info && x );
#endif
        std::string name_value_string() const;
        value_type v_;
        };
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* error_info_impl.hpp
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
*/