
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_TASK_OBJECT_H
#define BOOST_FIBERS_DETAIL_TASK_OBJECT_H

#include <exception>
#include <memory>
#include <tuple>
#include <utility>

#include <boost/config.hpp>
#include <boost/context/detail/config.hpp>
#if defined(BOOST_NO_CXX17_STD_APPLY)
#include <boost/context/detail/apply.hpp>
#endif
#include <boost/core/pointer_traits.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/future/detail/task_base.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename Fn, typename Allocator, typename R, typename ... Args >
class task_object : public task_base< R, Args ... > {
private:
    typedef task_base< R, Args ... >    base_type;
    typedef std::allocator_traits< Allocator >  allocator_traits;

public:
    typedef typename allocator_traits::template rebind_alloc<
        task_object
    >                                           allocator_type;

    task_object( allocator_type const& alloc, Fn const& fn) :
        base_type{},
        fn_{ fn },
        alloc_{ alloc } {
    }

    task_object( allocator_type const& alloc, Fn && fn) :
        base_type{},
        fn_{ std::move( fn) },
        alloc_{ alloc } {
    }

    void run( Args && ... args) override final {
        try {
            this->set_value(
#if defined(BOOST_NO_CXX17_STD_APPLY)
                    boost::context::detail::apply(
                        fn_, std::make_tuple( std::forward< Args >( args) ... ) )
#else
                    std::apply(
                        fn_, std::make_tuple( std::forward< Args >( args) ... ) )
#endif
                    );
#if defined(BOOST_CONTEXT_HAS_CXXABI_H)
        } catch ( abi::__forced_unwind const&) {
            throw;
#endif
        } catch (...) {
            this->set_exception( std::current_exception() );
        }
    }

    typename base_type::ptr_type reset() override final {
        typedef std::allocator_traits< allocator_type >    traity_type;
        typedef pointer_traits< typename traity_type::pointer> ptrait_type;

        typename traity_type::pointer ptr{ traity_type::allocate( alloc_, 1) };
        typename ptrait_type::element_type* p = boost::to_address(ptr);
        try {
            traity_type::construct( alloc_, p, alloc_, std::move( fn_) );
        } catch (...) {
            traity_type::deallocate( alloc_, ptr, 1);
            throw;
        }
        return { p };
    }

protected:
    void deallocate_future() noexcept override final {
        destroy_( alloc_, this);
    }

private:
    Fn                  fn_;
    allocator_type      alloc_;

    static void destroy_( allocator_type const& alloc, task_object * p) noexcept {
        allocator_type a{ alloc };
        typedef std::allocator_traits< allocator_type >    traity_type;
        traity_type::destroy( a, p);
        traity_type::deallocate( a, p, 1);
    }
};

template< typename Fn, typename Allocator, typename ... Args >
class task_object< Fn, Allocator, void, Args ... > : public task_base< void, Args ... > {
private:
    typedef task_base< void, Args ... >    base_type;
    typedef std::allocator_traits< Allocator >    allocator_traits;

public:
    typedef typename allocator_traits::template rebind_alloc<
        task_object< Fn, Allocator, void, Args ... >
    >                                             allocator_type;

    task_object( allocator_type const& alloc, Fn const& fn) :
        base_type{},
        fn_{ fn },
        alloc_{ alloc } {
    }

    task_object( allocator_type const& alloc, Fn && fn) :
        base_type{},
        fn_{ std::move( fn) },
        alloc_{ alloc } {
    }

    void run( Args && ... args) override final {
        try {
#if defined(BOOST_NO_CXX17_STD_APPLY)
            boost::context::detail::apply(
                    fn_, std::make_tuple( std::forward< Args >( args) ... ) );
#else
            std::apply(
                    fn_, std::make_tuple( std::forward< Args >( args) ... ) );
#endif
            this->set_value();
#if defined(BOOST_CONTEXT_HAS_CXXABI_H)
        } catch ( abi::__forced_unwind const&) {
            throw;
#endif
        } catch (...) {
            this->set_exception( std::current_exception() );
        }
    }

    typename base_type::ptr_type reset() override final {
        typedef std::allocator_traits< allocator_type >    traity_type;
        typedef pointer_traits< typename traity_type::pointer> ptrait_type;

        typename traity_type::pointer ptr{ traity_type::allocate( alloc_, 1) };
        typename ptrait_type::element_type* p = boost::to_address(ptr);
        try {
            traity_type::construct( alloc_, p, alloc_, std::move( fn_) );
        } catch (...) {
            traity_type::deallocate( alloc_, ptr, 1);
            throw;
        }
        return { p };
    }

protected:
    void deallocate_future() noexcept override final {
        destroy_( alloc_, this);
    }

private:
    Fn                  fn_;
    allocator_type      alloc_;

    static void destroy_( allocator_type const& alloc, task_object * p) noexcept {
        allocator_type a{ alloc };
        typedef std::allocator_traits< allocator_type >    traity_type;
        traity_type::destroy( a, p);
        traity_type::deallocate( a, p, 1);
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_TASK_OBJECT_H

/* task_object.hpp
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
*/