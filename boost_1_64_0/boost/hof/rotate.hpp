/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    rotate.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_ROTATE_H
#define BOOST_HOF_GUARD_ROTATE_H

/// rotate
/// ====
/// 
/// Description
/// -----------
/// 
/// The `rotate` function adaptor moves the first parameter to the last
/// parameter.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     rotate_adaptor<F> rotate(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(rotate(f)(x, xs...) == f(xs..., x));
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     int main() {
///         int r = boost::hof::rotate(boost::hof::_ - boost::hof::_)(2, 5);
///         assert(r == 3);
///     }
/// 

#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

template<class F>
struct rotate_adaptor : detail::callable_base<F>
{
    typedef rotate_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(rotate_adaptor, detail::callable_base<F>);

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    struct rotate_failure
    {
        template<class Failure>
        struct apply
        {
            template<class T, class... Ts>
            struct of
            : Failure::template of<Ts..., T>
            {};
        };
    };

    struct failure
    : failure_map<rotate_failure, detail::callable_base<F>>
    {};

    BOOST_HOF_RETURNS_CLASS(rotate_adaptor);

    template<class T, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(const detail::callable_base<F>&, id_<Ts>..., id_<T>) 
    operator()(T&& x, Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)))
            (BOOST_HOF_FORWARD(Ts)(xs)..., BOOST_HOF_FORWARD(T)(x))
    );
};

BOOST_HOF_DECLARE_STATIC_VAR(rotate, detail::make<rotate_adaptor>);

}} // namespace boost::hof

#endif

/* rotate.hpp
So3HI/4MuJwoD6/swYADXGGNWsjI84sXi5XbtVMZCQh2hgSn1QgLunwkHVUrS6w9Ot6i+N/nxvG/0ahx+LcTiWscbe3XiawkXA0v4x+Scl3zV08xWFcQn5d8bh/O1fxtHt53ecXmyTpBEto1Jd8nFYqfwybzAVIUEBgZDzDSnaVNWRxzHIOnL4oUl60RTExSy/8Z5VGgpwp53neYeToR7B3HCEAOg1cmO3ZlsmMC2CnGIZ67zwQ71wHsVFkRIMEOAmxEikeABDsIANgpBdihXsCfYUpZ81Twugj8ocaqEwfMFxTp8+Slt5IHdVshA+wrDID2OFPJpZyxmozTC+RkIDw6Q2nRQFC5VOiBfBmK19GyDAR+kv9fx9+qYTV/PQXH6uUkVF7StOASNoYEYFBIHk4gLHMD6JQVirJ5KlM2n4wweVNP2bJ/IYQcoMC3Z3PWuMJIi92BX71L7puu5SCLAj2yF3nE4yhB2Ukl4vJxGGyU8mNXDTTkJTPIEsXTTBqbx6Lnnb3Q7FQS8j20e+zqdvGRl3xKJDNgo3MYArGL2H6zVONi9j2d1Nq9Zpb+PmT5ys5Z6ixeYkeL6wdJ0OcIX4EyvsAF5hEz/YOU/hmZXl90hynWHJjrERvVFg2ehcvDDK61YrJekemrI5eGZ1LimdMjm1itkPuCWyBNgAGaUyOt0L4+u6NpNCk4R/ubPcqMfUAyW3f1Y6YYSkxDQD6ylElYz1RYFkArmpqJVv/GbPV0arVTtjpmMBo6khX0L9YhJIIPdbd5EB4w6MzMH4GQHLF8kGIjNb6BCmcsk+KH3oLEUWqKH6W7kri+yF/vYA9iRWpwziVTXCNQTXsGyNXQBynlSNP0+QlwQbfklEHqBnUa+c9Znx9zf3It2k9HYKU4WKDURN6m5R3frfc4kslduVSF6sWO+F68bouZaxqzRgAJjxLXEXcWmGA5gIj8DbjPVRtdzjcaVWUPFcGmCQ7VdRZlSmwADUIpciQOwoC4QaAByEQqWWIEacUZ0m5CtvSkdmuNGGFJmH0q+uNvzKJRWlzpCeP7D6Rsfh918CqEq8+DWIUgTj/NrWdFwybEeuFR71wS3KVS/ZHHuId7sWI9xLkx3ochBY4PubyCZ0AHmDHcdYijRnmijcJfZrhievOl6BsTIJDsXtqqY2mwDE5G6tEJEupSeERMpJLwDyJYXN0WMYyVFFL9mw4m1H/MgbkfqVtchPmTaOgH3DVnzQjxwLnmwvkUA9P8G/Tqxf9/2v9R/FLzK36SG2fPSCTGz4iPn5YYXxEfn5kYfzriE+z9kjW7BQbJ51rit7A0ekoNMeKGEiNuMl16PKBT1kTyqsX6togSSEeQFiEAg0XmF4+aEbmmQ0nKWYf4OfZqsdSM70S5OLRlPXmg/A6Ur7jxU/7/LjjMnqmIjb/i8PhpsfGjD4/PjI3vf1i8tDJJp7JX3DnQhH8vS2MK6cuAWBZCAMqU0dDbtGdv7eaGlmMOAIgLACLUbAlMCjVjz9+ETNivGGKpQbzdYt59F7Pd3AbKuP+z1gjvajnyxNeA7wROStbbL9EO/pCSbUEyEqwYBGHvOosscKkqEAS+SuaMWogzuj0pd41HW8jyHO+fwT2EOakXBphyaOdHohIT7VfNatdnRTrzv0+PvR+4a2jREBbWX3ct2jC3W62khLmBQv72TD7wWXnIS4RMaXGDrmGjYPZvw/zcf9BQQ5IdQG65PcWzYieGwzXmOY82Cx2sERZ0sIJkEM+f95ZeSSidR6vnmE9O5643f22MKgmZ1rkhlbj1a2PZSs8jTC9FZF+iJy2cl7cTFP2F8wq6AAmEiGXokHXBZ/AhtGd+CbfEtXz0YHco0kU=
*/