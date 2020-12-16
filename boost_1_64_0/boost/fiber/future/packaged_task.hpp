
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
Sw3L0eqMNJ4EVsgGcJgZDTYH23ufvr0e7Z5lBOc2W/Ci9eaNF1hozesa7GGUVo/j9XLtTWNn97F3Jx0QsQhKUAot1Pmf03PUSxwddVJydFlw/isfHYIGJ3LEd/ZjgABGLUbqxOIamgsyrkesWRxeqV44I5TqoVuNSnURu4lBp1ZvLjFRqyxiwoh/IRMeRCYsl0xwzxRqdXB11dXK9GjyDx5hjRJtgv9t6L882ipF0TPoxT2+SrDIY8SztMez1XPh25J0VqGR050k1hC4FA+QdDrJdJBiWStruE2iKOjH6lj4PtHPID+4N+/7OlyLca8JcIvYgZZ04y72SV4KS6GPGOuJXGegwevN6uJSURt2fjTq1Nd64PsJ+JIwwNMI2OXvh0dzKpDu8iF7EmSKH42b/YTgwANOaHTrsliYNugBCSnombuglW2oC49axA90tKNorETxdeNEL1hbm05orflT0vdX8rwSdsbhX+ROTPU4RFplbwFKtPHFWDrImNozeIxyxwK0+3LqTt41xuOgm8jTATK1Rk/ouJTMudTtaXE+5SfApUosWBp+pk175iHlUGuslroF8AKaVYTyDTbr8sWMPrsoRluS4/Bf7AOoD/OgPPWX8XVAHxoFT1JoMYE3jS91RuNiZKUaYkr/l4tU0RC7GwHpbf0K6btGKRLxXUJkaXMYWUj7z8cF7a8An4UIqs7x8Pp0xaJw+iSp//C4Qn0tlXpG73pJ70yktzeZY6925XJVxZhcZNkPEi0WRefqzjXqHCnbWzB9WNWmG/0X90L1ghRhnoGyxWVIGdK9exuzO/FMP8q2yAs9/jEYgJVh/kaAu1PCLSS4S3Tnw+6hTbSbR8mjqF6GYHJzICBeV083miMa3a5CHK/Q0PW0hkPXNMTzkBy6ZsOmA7ZvE0g4BQU22TA1FrwjQrwcWlq164Yq/Jnex/Dln2T/VVQJVOgtjVQojyzwzltVNuIAtgqK0PFY3ROA5w6r4M+r81QdwsI+WfiheCh8RGrKdnamCSvjlWXGY5mt4Q9cAbiCODEi/kmOiJj+T0gPruDRCORkz+LwNre/Dr2rC2zYQUgnrhqvDOLUX44J2t6tBeS0oO4ljgR7chXXiNplA2EME5snkEmjhf2Nj6M9FDXkoFVS/mT/FugiPdpgFU3i73RMsSBN7XznQOXwzwnFbyP8Tb5Q8G+Nqyx+pr+XLQirvyeOKvobO0K9KKYtt4xzQjX1laNC0locaOHecrUwJkZo4TJFC4fFVKSFHkUL5fozaqGwxWseCQ0I60vq+sQBQe3UU+YTHxbnwFNP7HZbaaDMo2qkY6TQyLzo304jw49ntz4YHM9IdpnLFeXoMyx0SOq0XAxJ22OBDY3RqrrkhRiZ2u39SgPVGoLD07tufrnjb2dowB/+qTRg/tDQ8Tf6n6IBNmxAZ5L4runlOXhNxpkPtoOXVXOwLbe9JfMq9DduPqK0d+mQ0PZ2PCLaWzcG2nsdtfdAdqho42XJ7GiDt9HnbmJA9d2rctp7cG7F7S1V2vv8LSbtLRWtuBRb0RWLZ1KjX1gcXshZ2tz7zYXccky1hGxu/+eE2GcrdcEWagub2sg+R7RffCFhpRj95xsjO49iyBzjeRT3TKnEeRSN5xjPf1lcGvH692wdvRkR0rtmtpHeksmVoHfcbAO9fRZHsj+gE4Fpp4eK0mHnf0Pou2RyhPcV0fz3LCP83lHlwfcIH/8SJvJ7gyrlu1nZgOvDqYSn/i622P64gbnlTuw11C8egykUvwsKzZSF3meFfPWk3fdoOB9Z6b2Opuff5UsrcDd59O9+hh79XPToH5Ue/atgkTKwZugzRz+jPuPeFIVZ7VZE/DGKSf0=
*/