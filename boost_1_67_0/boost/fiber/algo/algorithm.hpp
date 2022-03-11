//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_ALGO_ALGORITHM_H
#define BOOST_FIBERS_ALGO_ALGORITHM_H

#include <atomic>
#include <chrono>
#include <cstddef>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>

#include <boost/fiber/properties.hpp>
#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class context;

namespace algo {

class BOOST_FIBERS_DECL algorithm {
private:
    std::atomic< std::size_t >    use_count_{ 0 };

public:
    typedef intrusive_ptr< algorithm >  ptr_t;

    virtual ~algorithm() = default;

    virtual void awakened( context *) noexcept = 0;

    virtual context * pick_next() noexcept = 0;

    virtual bool has_ready_fibers() const noexcept = 0;

    virtual void suspend_until( std::chrono::steady_clock::time_point const&) noexcept = 0;

    virtual void notify() noexcept = 0;

    friend void intrusive_ptr_add_ref( algorithm * algo) noexcept {
        BOOST_ASSERT( nullptr != algo);
        algo->use_count_.fetch_add( 1, std::memory_order_relaxed);
    }

    friend void intrusive_ptr_release( algorithm * algo) noexcept {
        BOOST_ASSERT( nullptr != algo);
        if ( 1 == algo->use_count_.fetch_sub( 1, std::memory_order_release) ) {
            std::atomic_thread_fence( std::memory_order_acquire);
            delete algo;
        }
    }
};

class BOOST_FIBERS_DECL algorithm_with_properties_base : public algorithm {
public:
    // called by fiber_properties::notify() -- don't directly call
    virtual void property_change_( context * ctx, fiber_properties * props) noexcept = 0;

protected:
    static fiber_properties* get_properties( context * ctx) noexcept;
    static void set_properties( context * ctx, fiber_properties * p) noexcept;
};

template< typename PROPS >
struct algorithm_with_properties : public algorithm_with_properties_base {
    typedef algorithm_with_properties_base super;

    // Mark this override 'final': algorithm_with_properties subclasses
    // must override awakened() with properties parameter instead. Otherwise
    // you'd have to remember to start every subclass awakened() override
    // with: algorithm_with_properties<PROPS>::awakened(fb);
    void awakened( context * ctx) noexcept final {
        fiber_properties * props = super::get_properties( ctx);
        if ( BOOST_LIKELY( nullptr == props) ) {
            // TODO: would be great if PROPS could be allocated on the new
            // fiber's stack somehow
            props = new_properties( ctx);
            // It is not good for new_properties() to return 0.
            BOOST_ASSERT_MSG( props, "new_properties() must return non-NULL");
            // new_properties() must return instance of (a subclass of) PROPS
            BOOST_ASSERT_MSG( dynamic_cast< PROPS * >( props),
                              "new_properties() must return properties class");
            super::set_properties( ctx, props);
        }
        // Set algo_ again every time this fiber becomes READY. That
        // handles the case of a fiber migrating to a new thread with a new
        // algorithm subclass instance.
        props->set_algorithm( this);

        // Okay, now forward the call to subclass override.
        awakened( ctx, properties( ctx) );
    }

    // subclasses override this method instead of the original awakened()
    virtual void awakened( context *, PROPS &) noexcept = 0;

    // used for all internal calls
    PROPS & properties( context * ctx) noexcept {
        return static_cast< PROPS & >( * super::get_properties( ctx) );
    }

    // override this to be notified by PROPS::notify()
    virtual void property_change( context * ctx, PROPS & props) noexcept {
    }

    // implementation for algorithm_with_properties_base method
    void property_change_( context * ctx, fiber_properties * props) noexcept final {
        property_change( ctx, * static_cast< PROPS * >( props) );
    }

    // Override this to customize instantiation of PROPS, e.g. use a different
    // allocator. Each PROPS instance is associated with a particular
    // context.
    virtual fiber_properties * new_properties( context * ctx) {
        return new PROPS( ctx);
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_ALGO_ALGORITHM_H

/* algorithm.hpp
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
*/