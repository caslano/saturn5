
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_PROMISE_HPP
#define BOOST_FIBERS_PROMISE_HPP

#include <algorithm>
#include <memory>
#include <utility>

#include <boost/config.hpp>
#include <boost/core/pointer_traits.hpp>

#include <boost/fiber/exceptions.hpp>
#include <boost/fiber/future/detail/shared_state.hpp>
#include <boost/fiber/future/detail/shared_state_object.hpp>
#include <boost/fiber/future/future.hpp>

namespace boost {
namespace fibers {
namespace detail {

template< typename R >
struct promise_base {
    typedef typename shared_state< R >::ptr_type   ptr_type;

    bool            obtained_{ false };
    ptr_type        future_{};

    promise_base() :
        promise_base{ std::allocator_arg, std::allocator< promise_base >{} } {
    }

    template< typename Allocator >
    promise_base( std::allocator_arg_t, Allocator alloc) {
        typedef detail::shared_state_object< R, Allocator >  object_type;
        typedef std::allocator_traits< typename object_type::allocator_type > traits_type;
        typedef pointer_traits< typename traits_type::pointer > ptrait_type;
        typename object_type::allocator_type a{ alloc };
        typename traits_type::pointer ptr{ traits_type::allocate( a, 1) };
        typename ptrait_type::element_type* p = boost::to_address(ptr);

        try {
            traits_type::construct( a, p, a);
        } catch (...) {
            traits_type::deallocate( a, ptr, 1);
            throw;
        }
        future_.reset(p);
    }

    ~promise_base() {
        if ( future_ && obtained_) {
            future_->owner_destroyed();
        }
    }

    promise_base( promise_base const&) = delete;
    promise_base & operator=( promise_base const&) = delete;

    promise_base( promise_base && other) noexcept :
        obtained_{ other.obtained_ },
        future_{ std::move( other.future_) } {
        other.obtained_ = false;
    }

    promise_base & operator=( promise_base && other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            promise_base tmp{ std::move( other) };
            swap( tmp);
        }
        return * this;
    }

    future< R > get_future() {
        if ( BOOST_UNLIKELY( obtained_) ) {
            throw future_already_retrieved{};
        }
        if ( BOOST_UNLIKELY( ! future_) ) {
            throw promise_uninitialized{};
        }
        obtained_ = true;
        return future< R >{ future_ };
    }

    void swap( promise_base & other) noexcept {
        std::swap( obtained_, other.obtained_);
        future_.swap( other.future_);
    }

    void set_exception( std::exception_ptr p) {
        if ( BOOST_UNLIKELY( ! future_) ) {
            throw promise_uninitialized{};
        }
        future_->set_exception( p);
    }
};

}

template< typename R >
class promise : private detail::promise_base< R > {
private:
    typedef detail::promise_base< R >  base_type;

public:
    promise() = default;

    template< typename Allocator >
    promise( std::allocator_arg_t, Allocator alloc) :
        base_type{ std::allocator_arg, alloc } {
    }

    promise( promise const&) = delete;
    promise & operator=( promise const&) = delete;

    promise( promise && other) noexcept = default;
    promise & operator=( promise && other) = default;

    void set_value( R const& value) {
        if ( BOOST_UNLIKELY( ! base_type::future_) ) {
            throw promise_uninitialized{};
        }
        base_type::future_->set_value( value);
    }

    void set_value( R && value) {
        if ( BOOST_UNLIKELY( ! base_type::future_) ) {
            throw promise_uninitialized{};
        }
        base_type::future_->set_value( std::move( value) );
    }

    void swap( promise & other) noexcept {
        base_type::swap( other);
    }

    using base_type::get_future;
    using base_type::set_exception;
};

template< typename R >
class promise< R & > : private detail::promise_base< R & > {
private:
    typedef detail::promise_base< R & >  base_type;

public:
    promise() = default;

    template< typename Allocator >
    promise( std::allocator_arg_t, Allocator alloc) :
        base_type{ std::allocator_arg, alloc } {
    }

    promise( promise const&) = delete;
    promise & operator=( promise const&) = delete;

    promise( promise && other) noexcept = default;
    promise & operator=( promise && other) noexcept = default;

    void set_value( R & value) {
        if ( BOOST_UNLIKELY( ! base_type::future_) ) {
            throw promise_uninitialized{};
        }
        base_type::future_->set_value( value);
    }

    void swap( promise & other) noexcept {
        base_type::swap( other);
    }

    using base_type::get_future;
    using base_type::set_exception;
};

template<>
class promise< void > : private detail::promise_base< void > {
private:
    typedef detail::promise_base< void >  base_type;

public:
    promise() = default;

    template< typename Allocator >
    promise( std::allocator_arg_t, Allocator alloc) :
        base_type{ std::allocator_arg, alloc } {
    }

    promise( promise const&) = delete;
    promise & operator=( promise const&) = delete;

    promise( promise && other) noexcept = default;
    promise & operator=( promise && other) noexcept = default;

    inline
    void set_value() {
        if ( BOOST_UNLIKELY( ! base_type::future_) ) {
            throw promise_uninitialized{};
        }
        base_type::future_->set_value();
    }

    inline
    void swap( promise & other) noexcept {
        base_type::swap( other);
    }

    using base_type::get_future;
    using base_type::set_exception;
};

template< typename R >
void swap( promise< R > & l, promise< R > & r) noexcept {
    l.swap( r);
}

}}

#endif // BOOST_FIBERS_PROMISE_HPP

/* promise.hpp
fYP130H1D2D1z8P6l8j6O+jqH63W//LyytRPUj80k9Va5BQnBhTWvnGo04JH5edPgCwQSWMQQXdIg61nH06DJHBxR7C3PfBWFPFHGMb5xCEzFaurdS1UfB/xMcIO/deNmVrOBBE6fTVTmWl0zMJJXvqaEkhc9raYkax9L5rXB8Lsb5Y7pX2t+H1GYLz5VW+phGD/PRKBSyJwifMvmBEtSqZa846Kqf3Jjwo6PbmlgZo47MKoPwkz9NuIndTnFt/LBJYJdFHCIrAjylHW/P6we2C3VdDJfRP8DooMsNv1YMflEHxH0NJKdzUjvUVM/tPFUXl9Zsmj8lZSPI4n1u1Gvacr/NgRoXmg94VAITQnncUSC1KKEc+bQ4giTAF4OmpudyE7aq6oElcFGPm5ZZqen3Zt+0TiEO2rrwPboe5dGUtHo/nrMOv0bgEf5plvCnTu+adg+8VDKuyaxqnprlQ/3mPE0WRp74HfQfOnWh9GTYpZoIJ6TSGKJkMUhGk4QPQY2vwwSERIaEKogu/Y7A77XHudvKl0D+iMPEjIhy3/CD027Kv+RHhLHRNLb9hunJfecUQQfOktpEgoVepTlN79L8znaQdG7NvRseybTQnz9WAx3f+2D58OUPLWgYCqSEwF3xHLS18OoXuZBSwFy6rBCWHdp3grp/625/kxe9maKuWfTaGELreKu28OXYsSwp5KHWR6qZjtWpVJ/T0TP5uipF7jmU0YJ8tMhTKEJ753qHc+UJa7Ccr5HbrTaQ91Z5j+KEt0ELXhnVUEPmy4yGyI4PUEMUmU+GNfnVTvuV0Y7cxxHFF+XjKp3H0fkMqlMpW7W7zJnVaHRTUv3xxsMaczFYaKX3u5N+SnPyWVjE74fLd9e4Xy7jpZ56qjdODcbfHhz3AS1wNDlCGQ1r7TyHn4/B/oPKSjEZ0onYfTY9jadzOO1K79gwQmz0q1V51NpvuvJt5vPA9Pfrz43cjK7Q9LY/M/hI/m7/KLXT10PuZubUJf5rH4jLdgRhQ2Gih//T7prwePAn7svoi+d51+n+H7Nlwu8ECaRPRODD/IB8/mrfjbTeP9jxw/Ngo6SNUOKzW0d3+eSXu/6FvBfjsDkrl5QXGrmPJgvKrc96m0/1GH0KNiTO0Tgf4Y0B2bFI6+7QWELaJ4dyWhCULfcq0Crc43GIm4jaDJiQ+l5Mo7SyP42tFgT1zbq2BvdPlJFeQ7y9//P1HPD7u2K9ekCYbP2YcSDPkUqL8Bvf4y1S5ITJnvSSaLVPGAabSfP+WG2E+PNKBZZEDdk00MaHMyoCs+kQZ0kjSgr93KDOglwf1LTYaoFtRTVRMaYv9N6E8y0L91ggn944j+zz6W9OdJ+r/PUulP0vr3MtCf9CvRP9kXSr/TQP+n2Sb030z0Nw7Sf5+kv5OBfqeW0ddAv7OK9Bvt/wTVHqJev3Qv1+tI5lMmTzDOpyy6ozLzMV0JHu+5+lREle/1Z41FhE5KceYxF+x2WWStKEJLEA14cS8v3wPE7b8AIHpKiAf6VyaMD3//870innfxtdqzn4jwpxERRYHU8/dQ6AIiT7FMaYX/Yqc2pxMkC2sfHeC0ZMCZCRj3fCDgP+3Hqd4oUe6GJEjYKhM2QoJZNBS8q/Gv0fyE634shnsAES6T8NfPhzh9oFqewhYR+z43mFW5b2gsB2k8H8h6hAJCRNZSEtyKqHNL7BdhAmIWl7viM94piOfXSzAtJnhjB6FseqPI+zCDoewna9+ZUdVQ/Ff5Gft7QY4xPpnLD7PNRKm/ercaonz+vnDY/92XNewzmfAVJqgxy9gOwSQnJU27lYF9/5EA29A3JPg4fIPIXNrXJPiY0l0XfHx3iwg+Ph0=
*/