#ifndef BOOST_SMART_PTR_DETAIL_LOCAL_COUNTED_BASE_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_LOCAL_COUNTED_BASE_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  detail/local_counted_base.hpp
//
//  Copyright 2017 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/ for documentation.

#include <boost/smart_ptr/detail/shared_count.hpp>
#include <boost/config.hpp>
#include <utility>

namespace boost
{

namespace detail
{

class BOOST_SYMBOL_VISIBLE local_counted_base
{
private:

    local_counted_base & operator= ( local_counted_base const & );

private:

    // not 'int' or 'unsigned' to avoid aliasing and enable optimizations
    enum count_type { min_ = 0, initial_ = 1, max_ = 2147483647 };

    count_type local_use_count_;

public:

    BOOST_CONSTEXPR local_counted_base() BOOST_SP_NOEXCEPT: local_use_count_( initial_ )
    {
    }

    BOOST_CONSTEXPR local_counted_base( local_counted_base const & ) BOOST_SP_NOEXCEPT: local_use_count_( initial_ )
    {
    }

    virtual ~local_counted_base() /*BOOST_SP_NOEXCEPT*/
    {
    }

    virtual void local_cb_destroy() BOOST_SP_NOEXCEPT = 0;

    virtual boost::detail::shared_count local_cb_get_shared_count() const BOOST_SP_NOEXCEPT = 0;

    void add_ref() BOOST_SP_NOEXCEPT
    {
#if !defined(__NVCC__)
#if defined( __has_builtin )
# if __has_builtin( __builtin_assume )

        __builtin_assume( local_use_count_ >= 1 );

# endif
#endif
#endif

        local_use_count_ = static_cast<count_type>( local_use_count_ + 1 );
    }

    void release() BOOST_SP_NOEXCEPT
    {
        local_use_count_ = static_cast<count_type>( local_use_count_ - 1 );

        if( local_use_count_ == 0 )
        {
            local_cb_destroy();
        }
    }

    long local_use_count() const BOOST_SP_NOEXCEPT
    {
        return local_use_count_;
    }
};

class BOOST_SYMBOL_VISIBLE local_counted_impl: public local_counted_base
{
private:

    local_counted_impl( local_counted_impl const & );

private:

    shared_count pn_;

public:

    explicit local_counted_impl( shared_count const& pn ) BOOST_SP_NOEXCEPT: pn_( pn )
    {
    }

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    explicit local_counted_impl( shared_count && pn ) BOOST_SP_NOEXCEPT: pn_( std::move(pn) )
    {
    }

#endif

    void local_cb_destroy() BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        delete this;
    }

    boost::detail::shared_count local_cb_get_shared_count() const BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        return pn_;
    }
};

class BOOST_SYMBOL_VISIBLE local_counted_impl_em: public local_counted_base
{
public:

    shared_count pn_;

    void local_cb_destroy() BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        shared_count().swap( pn_ );
    }

    boost::detail::shared_count local_cb_get_shared_count() const BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        return pn_;
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_LOCAL_COUNTED_BASE_HPP_INCLUDED

/* local_counted_base.hpp
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
*/