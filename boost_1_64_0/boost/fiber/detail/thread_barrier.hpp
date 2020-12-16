
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBER_DETAIL_THREAD_BARRIER_H
#define BOOST_FIBER_DETAIL_THREAD_BARRIER_H

#include <cstddef>
#include <condition_variable>
#include <mutex>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

class thread_barrier {
private:
	std::size_t             initial_;
	std::size_t             current_;
	bool                    cycle_{ true };
    std::mutex              mtx_{};
    std::condition_variable cond_{};

public:
	explicit thread_barrier( std::size_t initial) :
        initial_{ initial },
        current_{ initial_ } {
        BOOST_ASSERT ( 0 != initial);
    }

    thread_barrier( thread_barrier const&) = delete;
    thread_barrier & operator=( thread_barrier const&) = delete;

    bool wait() {
        std::unique_lock< std::mutex > lk( mtx_);
        const bool cycle = cycle_;
        if ( 0 == --current_) {
            cycle_ = ! cycle_;
            current_ = initial_;
            lk.unlock(); // no pessimization
            cond_.notify_all();
            return true;
        }
        cond_.wait( lk, [&](){ return cycle != cycle_; });
        return false;
    }
};

}}}

#endif // BOOST_FIBER_DETAIL_THREAD_BARRIER_H

/* thread_barrier.hpp
z1+IDPHFsZ1a/oaE+6utUJKYCBrRoRifs7EzDTz13+tMEfyM9vzTL4z+zWZobkT+zRKEX07wWkeu1Vly9kJx79UZL23GbuTebq3NxySGTJRSFORwv+iSDHbGJnZwTN08DrNYHNzqO66FD0OGcHM2x8r8LnuVAB3UeCwvGM3HjJWybzk67NGu+x4pobkrMf744zH2ChSLK4M8zN4MAL7gtUGOwrU2UMqB+rwxkKfclmIRt8+JC3OibY6t0fb8M70ds7tbsV3TyDq93j7RsimJ9ajnjIHJOpvuW/j0opkE8WB7bs+YV7GaD0Q5TDv5ZRJ2CqQcs5YrB2MQUH2r5AKS/lMdIj2PEND9BB4nD8GGye1y5tBvMGjqxoRAnnfvsUtjSB1VhCBZ2sYLuYl5x6rTE1U4F8qWU83iNpiytgBTIZsHOWbH6MpFUxQvuRbroEZn01yDY9ZHlqCSaJlOyqXZBZTEH8RNLGBHnfzSOq+dwvZPnMF6YuSmQEZPBtCDpZFvvPQJJ2/6+7xGm15EcgtiOPDCCzg4Rlycqe6gROzaOGKtzT9Jdruyy38JBHjgMVgywqtZ66hjRrwgx99VYqS9+73tIM4kY6ITEpOl9OQISKPaFelFb5C+ftIukVQDybvzNI7MWymnuJ0IF2+EZGrgwVJ68mgddoq5rxln6SlL69+AIhnYhbjkV7+67P/ipwtND/+9lK5m+5pcxCsuB1PkwpyEp0MnWX7EjOHSzUApkCLMt3ORJ2vN6lF2qsxOZXaAPLqm6UXfUU272ibygfwWMOeAfIUIYODeuiSL7iVZ/+LURdDZ6UVnCdn9HJlXW/q8cMpF9WnMlJGL3pmn2rWk+gInmrDjF6A5/oWQtZWUFZ9CyvwxrGBVo+OKf6bzpR4gUEv/XHiaqaVOcQlYKpK+C8MX+imrB1khiwZ59ED2WVlbUAblHN6BOwoX1gvVwCiMj5nssSE+ZuEjzcplwyMaxkM2AsjBd8esl5irOYu9bn6rFrKUh3LfQQpqBlMFGL5X2Jj9QjMny3R6hsmPhqI85k0gsrwQZM8akF1vgkxbjcio5dLRRFcD4vhnY+LZc46/D94/t4BVoX0Dxld1HX5gZh9T0OwjPeLNTqjojXBhJVkonnxQtivBqSSCs+IBdZ8d3GtZbWWUqrndGKkgGH8vQoJMpCbLMuvrqU0eapVNlmW+593Wi3Rlyn6aRdPS4OC6MwppcYNJFRuOgtaiVvI5xThml/VLH19/Igyz80M1Fj94GLB2xLC2Y3rRTTbWe/7VkqLjfU8Yo+MXJcbdH6h40LeXVTLXHOIPhZf904uGEv4/txQW6g6sQQ7gGC1CKWLqw4wZdMPvA3pcdK2aHd+z+XsavlMXkpdvUeeiOd+H/gbViMBtNrxQezfdaQMRFcYEXNjeA0R33YNi1SbwT8G079mTwLiAdV8MEtphFDnjLU/982NYJPYwDbX7io+EPUz+TNrDZMgJWUDV3uOGxINJqcKouePRfHXHRw977MhMHXtsyUwde2zKTB17rMdMHXu0S6PgJ4OCgKSfV+gCyFtLeEffoYScmHXzKh5y+p0CnEwHrUl62PvDjEoKxN56igDc2mVHSA0zMW8+88AzqXbU/GFkhsTaE5LOV24eZsRTcXIPt65mXb2uPs0LLpc/Cblo1TeNRm97kEeN1awudl88EeooFfoeI723QcdxXpkmwlBIqPVdvmBanxZ/Dmm9LhQ+cEidf+qeXtSKHNULWyRa5CzUszjtKmehcvagQ9uGyv0rRUw1zfRHONXE60cF9x4SCt79Y6ngznj0Ti4g/H8G/JuczP4tC/XQtvPBNzVejpcok/trs5HDxZy0qTFl+Sw=
*/