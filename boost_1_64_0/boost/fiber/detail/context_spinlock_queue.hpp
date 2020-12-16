
//          Copyright Oliver Kowalke 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FIBERS_DETAIL_SPINLOCK_QUEUE_H
#define BOOST_FIBERS_DETAIL_SPINLOCK_QUEUE_H

#include <cstddef>
#include <cstring>
#include <mutex>

#include <boost/config.hpp>

#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/spinlock.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

class context_spinlock_queue {
private:
	typedef context *   slot_type;

    mutable spinlock   splk_{};
	std::size_t                                 pidx_{ 0 };
	std::size_t                                 cidx_{ 0 };
	std::size_t                                 capacity_;
	slot_type                               *   slots_;

	void resize_() {
		slot_type * old_slots = slots_;
		slots_ = new slot_type[2*capacity_];
		std::size_t offset = capacity_ - cidx_;
		std::memcpy( slots_, old_slots + cidx_, offset * sizeof( slot_type) );
		if ( 0 < cidx_) {
			std::memcpy( slots_ + offset, old_slots, pidx_ * sizeof( slot_type) );
		}
		cidx_ = 0;
		pidx_ = capacity_ - 1;
		capacity_ *= 2;
		delete [] old_slots;
	}

	bool is_full_() const noexcept {
		return cidx_ == ((pidx_ + 1) % capacity_);
	}

	bool is_empty_() const noexcept {
		return cidx_ == pidx_;
	}

public:
	context_spinlock_queue( std::size_t capacity = 4096) :
			capacity_{ capacity } {
		slots_ = new slot_type[capacity_];
	}

	~context_spinlock_queue() {
		delete [] slots_;
	}

    context_spinlock_queue( context_spinlock_queue const&) = delete;
    context_spinlock_queue & operator=( context_spinlock_queue const&) = delete;

	bool empty() const noexcept {
        spinlock_lock lk{ splk_ };
		return is_empty_();
	}

	void push( context * c) {
        spinlock_lock lk{ splk_ };
		if ( is_full_() ) {
			resize_();
		}
		slots_[pidx_] = c;
		pidx_ = (pidx_ + 1) % capacity_;
	}

	context * pop() {
        spinlock_lock lk{ splk_ };
		context * c = nullptr;
		if ( ! is_empty_() ) {
			c = slots_[cidx_];
			cidx_ = (cidx_ + 1) % capacity_;
		}
		return c;
	}

	context * steal() {
        spinlock_lock lk{ splk_ };
		context * c = nullptr;
		if ( ! is_empty_() ) {
			c = slots_[cidx_];
            if ( c->is_context( type::pinned_context) ) {
                return nullptr;
            }
			cidx_ = (cidx_ + 1) % capacity_;
		}
		return c;
	}
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_SPINLOCK_QUEUE_H

/* context_spinlock_queue.hpp
W+nLPyUtZ2l2GjY7I4nUN2q5xCTScqEYtuqDSqX8XdrJGpOWCxlbzoxpuVZUV6Goa561rtUdoK5HFArScqej/AH3xVhngL7mJE/pGVtOpklVKcqgVMqgPVVw4FqsIN9aQRArGAAVEEBkKt30MJi6SPBbIMP0FWv8K5H6COnD12oEG20PSHfK+6fgMBUh4CNkpUb3TvKzLDUJTBopcB8kDxMpfN9bqekVdNe16pW2Zo0wvUInHGh6hb6YS6+kzbk1NebWhOvCOaItffH8WWucdaQGzKeHJMF+IvjpIg3Bh7OA4G/5DJRJ3vLk/S+hd6lUNlQhSrEZqhqToaqxGqqzd1OvyiCkQ9HXWAC1molkML3JqpEmS8z0zTzwx/DuQdN6FuCl1+3wKnvH6fUEGiaBHgF/nG+Ulsc8PWUFIjJav/ffCHYwVrdxx7k4GGZl0HY5eQI5mkbxC/0rH4Z7p6tNXWGcjMNlVsNabTasjOHabjTwHWxr0MG2Vttt6wyrbb370Hapdlf3Z9taJPqQZ/LVbFuLDD+41JUADtPPdf/fUdHj9+c4f9uTY7ffuY2Yv3U43TJ/20Oa5crRPH+bwJplVRs1KRoUb/42LVvN3/jabq9AN86Kbjij+8Y+f5ufrZ+/Tc7m+Rvf4v3kKA3u/a0V7ntx/vaLb+w+ST7P307KUz7Jp8KJ4PnbO/I1bGnaPzo7+iTJdMF/x1Hkk6z9UjN/C9vmby3ohusvriJNbiHCD0SIM8ZieYT03CwB1YagnhZQJVaow60AalyCmuwsE2CsYX69WzkDAxJ0U54Np8WcgZOplmGilnnWWpZhLXXHZMrzt1rVpF+5j92UJ6ymPFcBUnnZgqdsEGn5ZHB5NnppVwBgTwKRbMsIVRxMjWSzmWC+0JGZM2TQtQV/dIGm9vyd7kdhIKGerjfZzhSz7Mgo/OOJdIveguJUweZ8dtb4yvpX9m6nOW55AwVP2SULXtpAwd1fyYJdRIiGxBopJH/SItYXM+HQSzcxZZ4pQp1BKnyRKDzVWngpFLYamh7QdHoKBNjQDBYoPEmFpkncax3/L+4+/3f8HOdzn5/GX4u1x/OKLMtkPI2zXv8SUvM8Y9zX220fNxjnUUsNf7pAXXX50G4qVUyvS+GVXSTzrG7dKfU0aBC7ShDuV6Uvhnx0OWnQcV+YZnVwd05r9PsRn21iN1P6/5ezEh0X8//B263dAI/oP4ESXc9K9DaCKhFQJVao5xBqjpxLFdN2IL7/xLg+qjTWT5JsMyq62+rkmBL9GdXSTNQyz1rLpVhLhyTtjCrMH2DABJ5UXZ9Jk6pyugaP6F8h6R/JkyoT/alIf6K6Ny9SxlOnwSQnA5SD/eocifchwjt0pIavdyHeqwGvvBlBIlDLveXie77yDo+G51XTrPOqsdZ51eXWedVg67zqPPOUg1tTw62Rpk9NrR7HqVVbN37vHKxAvQnqeqL5iss0ND/UAmi+LsFpalVqjHA1ZmoVamBq9f7nPLVCpLvQ1O5rzNQqpJ1aldrY4GfUaMUpSEqv8+FVdpMcs1j58g6S7L1pUrLXSFtYRDclUbkVZndjKYx19KhiUZWRgH8kRaBHJkRm4h+IQN8HmfiYFOlZW+WiwaoMWqHaqBXkHYZPg2uFnlntM+o79bypqGHgQXsJOFreQMG27XZQwUsbKLj0C8JI9vUj6kFthpN9tfSgnyRL+xqW9vUTKvxFmOyrpbA/mT/QK+83/D0oHnr6EIJ1pDQ3bqeJ3C/CponchDYUJD0xkTvufiZ7bduA27OjMtiFLrO5mQY7nvmlTy3ZxCCndK2VgTEzTCtZLGC8ebr6XsDm0/UbRtpTl7otXV1VPROeais=
*/