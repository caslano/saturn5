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