
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