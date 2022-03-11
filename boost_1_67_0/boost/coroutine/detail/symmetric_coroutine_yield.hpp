
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