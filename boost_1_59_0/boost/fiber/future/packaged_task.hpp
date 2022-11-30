
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_PACKAGED_TASK_HPP
#define BOOST_FIBERS_PACKAGED_TASK_HPP

#include <algorithm>
#include <memory>
#include <type_traits>
#include <utility>

#include <boost/config.hpp>

#include <boost/fiber/detail/disable_overload.hpp>
#include <boost/fiber/exceptions.hpp>
#include <boost/fiber/future/detail/task_base.hpp>
#include <boost/fiber/future/detail/task_object.hpp>
#include <boost/fiber/future/future.hpp>

namespace boost {
namespace fibers {

template< typename Signature >
class packaged_task;

template< typename R, typename ... Args >
class packaged_task< R( Args ... ) > {
private:
    typedef typename detail::task_base< R, Args ... >::ptr_type   ptr_type;

    bool            obtained_{ false };
    ptr_type        task_{};

public:
    packaged_task() = default;

    template< typename Fn,
              typename = detail::disable_overload< packaged_task, Fn >
    >
    explicit packaged_task( Fn && fn) : 
        packaged_task{ std::allocator_arg,
                       std::allocator< packaged_task >{},
                       std::forward< Fn >( fn)  } {
    }

    template< typename Fn,
              typename Allocator
    >
    explicit packaged_task( std::allocator_arg_t, Allocator const& alloc, Fn && fn) {
        typedef detail::task_object<
            typename std::decay< Fn >::type, Allocator, R, Args ...
        >                                       object_type;
        typedef std::allocator_traits<
            typename object_type::allocator_type
        >                                       traits_type;
        typedef pointer_traits< typename traits_type::pointer > ptrait_type;

        typename object_type::allocator_type a{ alloc };
        typename traits_type::pointer ptr{ traits_type::allocate( a, 1) };
        typename ptrait_type::element_type* p = boost::to_address(ptr);
        try {
            traits_type::construct( a, p, a, std::forward< Fn >( fn) );
        } catch (...) {
            traits_type::deallocate( a, ptr, 1);
            throw;
        }
        task_.reset(p);
    }

    ~packaged_task() {
        if ( task_ && obtained_) {
            task_->owner_destroyed();
        }
    }

    packaged_task( packaged_task const&) = delete;
    packaged_task & operator=( packaged_task const&) = delete;

    packaged_task( packaged_task && other) noexcept :
        obtained_{ other.obtained_ },
        task_{ std::move( other.task_)  } {
        other.obtained_ = false;
    }

    packaged_task & operator=( packaged_task && other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            packaged_task tmp{ std::move( other) };
            swap( tmp);
        }
        return * this;
    }

    void swap( packaged_task & other) noexcept {
        std::swap( obtained_, other.obtained_);
        task_.swap( other.task_);
    }

    bool valid() const noexcept {
        return nullptr != task_.get();
    }

    future< R > get_future() {
        if ( obtained_) {
            throw future_already_retrieved{};
        }
        if ( BOOST_UNLIKELY( ! valid() ) ) {
            throw packaged_task_uninitialized{};
        }
        obtained_ = true;
        return future< R >{
             boost::static_pointer_cast< detail::shared_state< R > >( task_) };
    }

    void operator()( Args ... args) {
        if ( BOOST_UNLIKELY( ! valid() ) ) {
            throw packaged_task_uninitialized{};
        }
        task_->run( std::forward< Args >( args) ... );
    }

    void reset() {
        if ( BOOST_UNLIKELY( ! valid() ) ) {
            throw packaged_task_uninitialized{};
        }
        packaged_task tmp;
        tmp.task_ = task_;
        task_ = tmp.task_->reset();
        obtained_ = false;
    }
};

template< typename Signature >
void swap( packaged_task< Signature > & l, packaged_task< Signature > & r) noexcept {
    l.swap( r);
}

}}

#endif // BOOST_FIBERS_PACKAGED_TASK_HPP

/* packaged_task.hpp
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
*/