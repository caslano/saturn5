
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_YIELD_H
#define BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_YIELD_H

#include <algorithm>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/move/move.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/explicit_operator_bool.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/exceptions.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename R >
class symmetric_coroutine_yield
{
private:
    template< typename X, typename Y, typename Z >
    friend class symmetric_coroutine_object;

    typedef symmetric_coroutine_impl< R >       impl_type;

    struct dummy {};

    BOOST_MOVABLE_BUT_NOT_COPYABLE( symmetric_coroutine_yield)

    impl_type   *   impl_;
    R           *   result_;

    symmetric_coroutine_yield( impl_type * impl, R * result) BOOST_NOEXCEPT :
        impl_( impl),
        result_( result)
    {
        BOOST_ASSERT( 0 != impl_);
        BOOST_ASSERT( 0 != result_);
    }

public:
    symmetric_coroutine_yield() BOOST_NOEXCEPT :
        impl_( 0),
        result_( 0)
    {}

    symmetric_coroutine_yield( BOOST_RV_REF( symmetric_coroutine_yield) other) BOOST_NOEXCEPT :
        impl_( 0),
        result_( 0)
    { swap( other); }

    symmetric_coroutine_yield & operator=( BOOST_RV_REF( symmetric_coroutine_yield) other) BOOST_NOEXCEPT
    {
        symmetric_coroutine_yield tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_; }

    void swap( symmetric_coroutine_yield & other) BOOST_NOEXCEPT
    {
        std::swap( impl_, other.impl_);
        std::swap( result_, other.result_);
    }

    symmetric_coroutine_yield & operator()()
    {
        result_ = impl_->yield();
        return * this;
    }

    template< typename Coro >
    symmetric_coroutine_yield & operator()( Coro & other, typename Coro::value_type x,
                                            typename disable_if<
                                                is_same< typename Coro::value_type, void >,
                                                dummy*
                                            >::type = 0)
    {
        BOOST_ASSERT( other);

        result_ = impl_->yield_to( other.impl_, x);
        return * this;
    }

    template< typename Coro >
    symmetric_coroutine_yield & operator()( Coro & other,
                                            typename enable_if<
                                                is_same< typename Coro::value_type, void >,
                                                dummy*
                                            >::type = 0)
    {
        BOOST_ASSERT( other);

        result_ = impl_->yield_to( other.impl_);
        return * this;
    }

    R get() const
    {
        if ( 0 == result_)
            boost::throw_exception(
                invalid_result() );

        return * result_; 
    }
};

template< typename R >
class symmetric_coroutine_yield< R & >
{
private:
    template< typename X, typename Y, typename Z >
    friend class symmetric_coroutine_object;

    typedef symmetric_coroutine_impl< R & >     impl_type;

    struct dummy {};

    BOOST_MOVABLE_BUT_NOT_COPYABLE( symmetric_coroutine_yield)

    impl_type   *   impl_;
    R           *   result_;

    symmetric_coroutine_yield( impl_type * impl, R * result) BOOST_NOEXCEPT :
        impl_( impl),
        result_( result)
    {
        BOOST_ASSERT( 0 != impl_);
        BOOST_ASSERT( 0 != result_);
    }

public:
    symmetric_coroutine_yield() BOOST_NOEXCEPT :
        impl_( 0),
        result_( 0)
    {}

    symmetric_coroutine_yield( BOOST_RV_REF( symmetric_coroutine_yield) other) BOOST_NOEXCEPT :
        impl_( 0),
        result_( 0)
    { swap( other); }

    symmetric_coroutine_yield & operator=( BOOST_RV_REF( symmetric_coroutine_yield) other) BOOST_NOEXCEPT
    {
        symmetric_coroutine_yield tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_; }

    void swap( symmetric_coroutine_yield & other) BOOST_NOEXCEPT
    {
        std::swap( impl_, other.impl_);
        std::swap( result_, other.result_);
    }

    symmetric_coroutine_yield & operator()()
    {
        result_ = impl_->yield();
        return * this;
    }

    template< typename Coro >
    symmetric_coroutine_yield & operator()( Coro & other, typename Coro::value_type & x,
                                            typename disable_if<
                                                is_same< typename Coro::value_type, void >,
                                                dummy*
                                            >::type = 0)
    {
        BOOST_ASSERT( other);

        result_ = impl_->yield_to( other.impl_, x);
        return * this;
    }

    template< typename Coro >
    symmetric_coroutine_yield & operator()( Coro & other,
                                            typename enable_if<
                                                is_same< typename Coro::value_type, void >,
                                                dummy*
                                            >::type = 0)
    {
        BOOST_ASSERT( other);

        result_ = impl_->yield_to( other.impl_);
        return * this;
    }

    R & get() const
    {
        if ( 0 == result_)
            boost::throw_exception(
                invalid_result() );

        return * result_; 
    }
};

template<>
class symmetric_coroutine_yield< void >
{
private:
    template< typename X, typename Y, typename Z >
    friend class symmetric_coroutine_object;

    typedef symmetric_coroutine_impl< void >    impl_type;

    struct dummy {};

    BOOST_MOVABLE_BUT_NOT_COPYABLE( symmetric_coroutine_yield)

    impl_type   *   impl_;

    symmetric_coroutine_yield( impl_type * impl) BOOST_NOEXCEPT :
        impl_( impl)
    { BOOST_ASSERT( 0 != impl_); }

public:
    symmetric_coroutine_yield() BOOST_NOEXCEPT :
        impl_( 0)
    {}

    symmetric_coroutine_yield( BOOST_RV_REF( symmetric_coroutine_yield) other) BOOST_NOEXCEPT :
        impl_( 0)
    { swap( other); }

    symmetric_coroutine_yield & operator=( BOOST_RV_REF( symmetric_coroutine_yield) other) BOOST_NOEXCEPT
    {
        symmetric_coroutine_yield tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    inline bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_; }

    inline void swap( symmetric_coroutine_yield & other) BOOST_NOEXCEPT
    { std::swap( impl_, other.impl_); }

    inline symmetric_coroutine_yield & operator()()
    {
        impl_->yield();
        return * this;
    }

    template< typename Coro >
    symmetric_coroutine_yield & operator()( Coro & other, typename Coro::value_type & x,
                                            typename disable_if<
                                                is_same< typename Coro::value_type, void >,
                                                dummy*
                                            >::type = 0)
    {
        BOOST_ASSERT( other);

        impl_->yield_to( other.impl_, x);
        return * this;
    }

    template< typename Coro >
    symmetric_coroutine_yield & operator()( Coro & other,
                                            typename enable_if<
                                                is_same< typename Coro::value_type, void >,
                                                dummy*
                                            >::type = 0)
    {
        BOOST_ASSERT( other);

        impl_->yield_to( other.impl_);
        return * this;
    }
};

template< typename R >
void swap( symmetric_coroutine_yield< R > & l, symmetric_coroutine_yield< R > & r)
{ l.swap( r); }

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_YIELD_H

/* symmetric_coroutine_yield.hpp
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
*/