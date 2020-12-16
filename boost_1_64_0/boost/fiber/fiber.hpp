
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FIBER_H
#define BOOST_FIBERS_FIBER_H

#include <algorithm>
#include <exception>
#include <memory>
#include <utility>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/predef.h>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/disable_overload.hpp>
#include <boost/fiber/context.hpp>
#include <boost/fiber/fixedsize_stack.hpp>
#include <boost/fiber/policy.hpp>
#include <boost/fiber/properties.hpp>
#include <boost/fiber/segmented_stack.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4251)
#endif

namespace boost {
namespace fibers {

class BOOST_FIBERS_DECL fiber {
private:
    friend class context;

    using ptr_t = intrusive_ptr<context>;

    ptr_t       impl_{};

    void start_() noexcept;

public:
    using id = context::id;

    fiber() = default;

    template< typename Fn,
              typename ... Arg,
              typename = detail::disable_overload< fiber, Fn >,
              typename = detail::disable_overload< launch, Fn >,
              typename = detail::disable_overload< std::allocator_arg_t, Fn >
    >
#if BOOST_COMP_GNUC < 50000000
    explicit fiber( Fn && fn, Arg && ... arg) :
#else
    fiber( Fn && fn, Arg ... arg) :
#endif
        fiber{ launch::post,
               std::allocator_arg, default_stack(),
               std::forward< Fn >( fn), std::forward< Arg >( arg) ... } {
    }

    template< typename Fn,
              typename ... Arg,
              typename = detail::disable_overload< fiber, Fn >
    >
#if BOOST_COMP_GNUC < 50000000
    fiber( launch policy, Fn && fn, Arg && ... arg) :
#else
    fiber( launch policy, Fn && fn, Arg ... arg) :
#endif
        fiber{ policy,
               std::allocator_arg, default_stack(),
               std::forward< Fn >( fn), std::forward< Arg >( arg) ... } {
    }

    template< typename StackAllocator,
              typename Fn,
              typename ... Arg
    >
#if BOOST_COMP_GNUC < 50000000
    fiber( std::allocator_arg_t, StackAllocator && salloc, Fn && fn, Arg && ... arg) :
#else
    fiber( std::allocator_arg_t, StackAllocator && salloc, Fn && fn, Arg ... arg) :
#endif
        fiber{ launch::post,
               std::allocator_arg, std::forward< StackAllocator >( salloc),
               std::forward< Fn >( fn), std::forward< Arg >( arg) ... } {
    }

    template< typename StackAllocator,
              typename Fn,
              typename ... Arg
    >
#if BOOST_COMP_GNUC < 50000000
    fiber( launch policy, std::allocator_arg_t, StackAllocator && salloc, Fn && fn, Arg && ... arg) :
#else
    fiber( launch policy, std::allocator_arg_t, StackAllocator && salloc, Fn && fn, Arg ... arg) :
#endif
        impl_{ make_worker_context( policy, std::forward< StackAllocator >( salloc), std::forward< Fn >( fn), std::forward< Arg >( arg) ... ) } {
        start_();
    }

    ~fiber() {
        if ( joinable() ) {
            std::terminate();
        }
    }

    fiber( fiber const&) = delete;
    fiber & operator=( fiber const&) = delete;

    fiber( fiber && other) noexcept :
        impl_{} {
        swap( other);
    }

    fiber & operator=( fiber && other) noexcept {
        if ( joinable() ) {
            std::terminate();
        }
        if ( BOOST_UNLIKELY( this == & other) ) {
            return * this;
        }
        impl_.swap( other.impl_);
        return * this;
    }

    void swap( fiber & other) noexcept {
        impl_.swap( other.impl_);
    }

    id get_id() const noexcept {
        return impl_ ? impl_->get_id() : id();
    }

    bool joinable() const noexcept {
        return nullptr != impl_;
    }

    void join();

    void detach();

    template< typename PROPS >
    PROPS & properties() {
        auto props = impl_->get_properties();
        BOOST_ASSERT_MSG( props, "fiber::properties not set");
        return dynamic_cast< PROPS & >( * props );
    }
};

inline
bool operator<( fiber const& l, fiber const& r) noexcept {
    return l.get_id() < r.get_id();
}

inline
void swap( fiber & l, fiber & r) noexcept {
    return l.swap( r);
}

}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_FIBER_H

/* fiber.hpp
UEYWdY7TcnTaPbUt+1lGU2pVLea/x3izij1eg/UQrJQLoNP743wS+vl6hAyVouGPn5ImAh+/J7M7uhxO7TVEqeHLseDLR3yP1AafjF/q2F71+Cd6Ui74EtpjhSLWh4mJsBj1yJqO8loZl35RRjOcLsoo0vPAj6qfLJb4F2dp9G9H+ivt6U9E+qsD9PvY0d/zYQ3op4j6M32MIgM4cWaB8jhONENr/CUYaoy/HsZf8hWmxqQ8ktztc4cVGNOm/o3N/b3YzcM49PhvbDf+4XBT/XsuAr5BY63Nt4G0S5h2G0sUjjD2/xSx/3s4klglCSWpxkS3WKuQM7g0crjEmyo3iycNW8q4DjF0Abznb2VaQEHSWGG8PFbB1BdRSUsQRRwGBZxvuIQCphfgIw1M4s5IpwNL7TvmXYE6OfQu2iMizggPKPbBelnCe1foYPGVu7UEaVhf3yt9jOLp+tgn7aF9oqAUFBLD7+3q/yytOj6G+hcacP5BJ0in2DCvQQ6mrEx6bd8xbFNpToNpqhapUFssHy2qVoKlzO9/UjecR91wtCF1wyXvmrsB59c1ofrAKzqgvegAbO99P9m3956g1j2NrWaRQvs1Uu2VGWivD8nwMd6hDSgsIfi/o4DYz0zaTZ5h9A4O+ZClCzc0iGwSW4d2XdEsM5sE/AuOghRbMR0IYE5kXkNqIvFMkLW9EnEcSZe9+Io7YOWgQZaEvPB49FHH5cViqmo1n7U3eR79RdoLN6AOnLvfLKth9T9yVFH9GVVVH73z4oVtl/LOg9WB2oTOGUDxRCS1TE3rf3tt6t9I1FqsVjiOaiNAnuG/jFD2Pk/WFyOTOoKsduQ6mWVcHiHaMFsPusqenl1xbmGzyWbMxn6LKUTZT/ZdtqnvsqT7YyFQKthrNIQBCpAYgbKrY+bZGXxIDRwpv/wExnAdF73qW1npcUzFYfODkxLQY3Yy9msi9Wuivz59uPCj4jroR+1bPn08iYblY/VoWH7+tlkQrcsWRsqUIJwqN3CGV+VWh6jKivuYeSupseK74ScOP/woNaKjHO+TYI3fHSuhG6IcH2MKOfaWGmQ/tdhp9yw6DMLFblNGAcBVB9PbAuNHSvHVQcVboCoOoGoXU3Za3my3T0QrLLmd5eMqrKyhaDujWLRyO0v9jVsYhSNPCXvNZDfNODLNFPd2wkUuN25uP0yaM6W5SKRGgmEViUtrZLz/XfgVU/zNOeE8Lmcf/7+uoBy4fGspLwlc6n1jN5ubjyuhGwVc4eC1xy2UuMcJ4xoTG0TXL1VyKAxWGMtPQAHxdRC+5j8gVV+RCvMf5brQDUsjJH6UHozGn4qiy45ihJliPM4enAyTo/EXUpss5d0raSpBHs5TfFhS0YmS8ytOsDQrGhe0SBFgTynV0rFY4I3rpp+V1UBYrsVfUPy3OnTI3wrKlwwxRZRnfPEnZWG8H/FRlHz/Igj+0OfhwD8i4S8Mgv/nwXDgR0j4E82s8Pf77eAJqiNBFXnUiCts+M7rTR0FDZzGOz8AGOy3bWC5fhXSQNjp5BLufVftEV8t4Su8t05t7f8jid/u75dZ3tt466/Mb+j7/MCcuokQ4f4RkddaOqOQ9kPd08cZ06q9hcf3gzzm94C2uM3fzzQyf3euZ/7eY4FvGW0pX9/y3pAl/9qG5u8PGtB3yPp7Rf0j+HSYzUE1M9lCScXhjM5tjv/Uz70R/2mQ2wX/aZg71D9RCt0lHnlUboyDZuSHaNQj/KmHUoECDx9Af8FxQAedNDrpkJ0mlu7obyvL+9wM8PHPjC2q5q5N4dh3BMbD1a5qx0OK0eZQWfXj4ZZGlvFg6e+f+Nty/+OkoV3RUHvPqGJHWRj3Sw8=
*/