
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
t6v9n6n2R5q1r5a1X5xviT+xI/WgxZ9offwlPn4DWa3H57hxRKv8iXS14U8X4k/mHZI/Vwj+oKqq8+fijIPGH9vz8VeHW5wAl/SN5wSYZYwGwUg7wMxq1X6a4HpyIP1lPf8Y3vy+9vdF3MSbSLwJP1LZOkyLLxLU44t0SDl48UVmD7PWNxg0xg5LKL5I3rDm8UVucqvXEKammvFFgokZivV4Eq3y+6Yim/r/KaVt8UJOLrLE45CUgslvH0i8kGSFYFCn6Ehue7yQR4fGq981k95OPF5IFZExsY+IRRKPF3LUULt4IZJWSr+3E7paovVv8EDWPyUfx3l8f58VR6nxaQoPLD5NsC3rdW4r+Xmt5Ae2tHj+M0SPb/Jhoc5y+/gXhKSJAQWW+Be72ttsELc56Dz9JrlBrDHjXxymb/8FxrPjLNt/wQFuEc32/8LW43c4htvU/wz+nrNZ/1/K+ld3t4pj/8w5OOJY8/gvg5vX32+p/7JBNvVPIkPd/Btl/cNm/Jduev39Rjunpf7+A6y/JT7OmMGJxccpPND4OK8Paj0+zug+Nvwp5e9Z3yD5s1by59quVvH0Xs/BEU+b1b/boNbj49wyMP6dtrXXy/qvM+1fXazxcQbFIocmPs6sI5vXP89S/2y79SHM75NukPX/lax/jqX+ecbvrOtD3kGq/40Dm9c/YKn/js8jzeufS/Mrw6z/r2X9T8zV6x8wzvzKwv/AAdbfsqu+MaC5vPjiEW2I73PjAKs/wkO9EvT3of4nfDLA8aPdQvErC38VCOGSmPmc8PTvzcwISoRaJ5zz6hHEDyDgrK2/6OosjH9/hHC1vG2QdFCvghz9rr/4UoFflDOqIu0wF52lrwRcbuKbS4N56nXyVORcORiCYBlp6kPHrwyHTcjRvfDovFOIoZ9L6FkMfaGOnoro7zm5DQ0bsqtAvy/kI4Pa1eAlj34J/ZXYz0/8Bimer1N8NAcoXs2sloS52su97yloCVnsRGmXdEEDDlENEdVKRvVcneoZSBXtf0ABT6o3ZClEHv06op7MUpX9xnJeZTCdy+rAvVJenSCdNeMRjkrwNiQ4rCtZX9kzF9LqXWnsz+Dpf3QgQVmBLZxnZcV1DvjN3Ntp1K3wM6+LcmbQWOaOvhl9Q8qolVgu4hPoGz0p9ANbBZb3U56NPOla5MgCnSNTO4Jl9UgcKRtxpIS64gDAr9JlEv8ay0FCwfFlujJOO5rd9h6FphiKrZ8inE8Oo8dYirBhVVnkSv/bYeRnmvW/YDG1qrLf9mOzllgVyIMf2pJCgoVYSuT53yOQZ8aBntw98ScIlKJXUNEUBINij3wa0eyqeFv1CG4DDXhlLGqZUhJmI60AXB7qRrQaOjn+ezF7+lqCksiD+UCAzRTNyaRcXbHUc9yqsAOHbxiHcCQAk1o47WZiUl+kCInpLL/RKUDJV+AInIwBRoXOj+ALxp/h7x5140dgL8MoJiQXII2WZ/VH7o7E5OI0n7bOXlfjpLkQJ821ctJ0zYZlZC2nQic/PXEWrhBtYKvnMSl8mp8pIb0AOaSUyiPIknCgUNSzgH2h82I3x+0ncbMAF57XApax3sWmlpfCzzJryX4jI5MxKU+UVEKzUT6SMVtQb3QI6nl2bQgYT3k45C0IKfukmPokNFKe5QSND5MZKFtxVhDz3rsSmXeBzrx/+mDFma525liiwgsNGjcrlFYRpRsYpSqd0jVIyYuDxylH/z1FwrfiAideJFgHWRjfDvBpa58CC9YhfMrzR/mo/o+9Ff/Ojz+NJOJPWtrb6v86NGH/zCy1vCWJlfdGL0t5m45KuLzbCJfwMhIrb761vGMTL69QLe+mTxIq77s8a/w=
*/