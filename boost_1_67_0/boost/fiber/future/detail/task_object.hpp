
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