#ifndef BOOST_LEAF_DETAIL_OPTIONAL_HPP_INCLUDED
#define BOOST_LEAF_DETAIL_OPTIONAL_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/leaf/config.hpp>

#include <utility>
#include <new>

namespace boost { namespace leaf {

namespace leaf_detail
{
    template <class T>
    class optional
    {
        int key_;
        union { T value_; };

    public:

        typedef T value_type;

        BOOST_LEAF_CONSTEXPR optional() noexcept:
            key_(0)
        {
        }

        BOOST_LEAF_CONSTEXPR optional( optional const & x ):
            key_(x.key_)
        {
            if( x.key_ )
                (void) new (&value_) T( x.value_ );
        }

        BOOST_LEAF_CONSTEXPR optional( optional && x ) noexcept:
            key_(x.key_)
        {
            if( x.key_ )
            {
                (void) new (&value_) T( std::move(x.value_) );
                x.reset();
            }
        }

        BOOST_LEAF_CONSTEXPR optional( int key, T const & v ):
            key_(key),
            value_(v)
        {
            BOOST_LEAF_ASSERT(!empty());
        }

        BOOST_LEAF_CONSTEXPR optional( int key, T && v ) noexcept:
            key_(key),
            value_(std::move(v))
        {
            BOOST_LEAF_ASSERT(!empty());
        }

        BOOST_LEAF_CONSTEXPR optional & operator=( optional const & x )
        {
            reset();
            if( int key = x.key() )
            {
                put(key, x.value_);
                key_ = key;
            }
            return *this;
        }

        BOOST_LEAF_CONSTEXPR optional & operator=( optional && x ) noexcept
        {
            reset();
            if( int key = x.key() )
            {
                put(key, std::move(x.value_));
                x.reset();
            }
            return *this;
        }

        ~optional() noexcept
        {
            reset();
        }

        BOOST_LEAF_CONSTEXPR bool empty() const noexcept
        {
            return key_==0;
        }

        BOOST_LEAF_CONSTEXPR int key() const noexcept
        {
            return key_;
        }

        BOOST_LEAF_CONSTEXPR void reset() noexcept
        {
            if( key_ )
            {
                value_.~T();
                key_=0;
            }
        }

        BOOST_LEAF_CONSTEXPR T & put( int key, T const & v )
        {
            BOOST_LEAF_ASSERT(key);
            reset();
            (void) new(&value_) T(v);
            key_=key;
            return value_;
        }

        BOOST_LEAF_CONSTEXPR T & put( int key, T && v ) noexcept
        {
            BOOST_LEAF_ASSERT(key);
            reset();
            (void) new(&value_) T(std::move(v));
            key_=key;
            return value_;
        }

        BOOST_LEAF_CONSTEXPR T const * has_value(int key) const noexcept
        {
            BOOST_LEAF_ASSERT(key);
            return key_==key ? &value_ : 0;
        }

        BOOST_LEAF_CONSTEXPR T * has_value(int key) noexcept
        {
            BOOST_LEAF_ASSERT(key);
            return key_==key ? &value_ : 0;
        }

        BOOST_LEAF_CONSTEXPR T const & value(int key) const & noexcept
        {
            BOOST_LEAF_ASSERT(has_value(key) != 0);
            return value_;
        }

        BOOST_LEAF_CONSTEXPR T & value(int key) & noexcept
        {
            BOOST_LEAF_ASSERT(has_value(key) != 0);
            return value_;
        }

        BOOST_LEAF_CONSTEXPR T const && value(int key) const && noexcept
        {
            BOOST_LEAF_ASSERT(has_value(key) != 0);
            return value_;
        }

        BOOST_LEAF_CONSTEXPR T value(int key) && noexcept
        {
            BOOST_LEAF_ASSERT(has_value(key) != 0);
            T tmp(std::move(value_));
            reset();
            return tmp;
        }
    };

}

} }

#endif

/* optional.hpp
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
*/