/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    is_unpackable.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_IS_UNPACKABLE_HPP
#define BOOST_HOF_GUARD_IS_UNPACKABLE_HPP

/// is_unpackable
/// =============
/// 
/// This is a trait that can be used to detect whether the type can be called
/// with `unpack`.
/// 
/// Synopsis
/// --------
/// 
///     template<class T>
///     struct is_unpackable;
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     int main() {
///         static_assert(boost::hof::is_unpackable<std::tuple<int>>::value, "Failed");
///     }
/// 

#include <boost/hof/unpack_sequence.hpp>
#include <boost/hof/is_invocable.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/detail/unpack_tuple.hpp>

namespace boost { namespace hof {

namespace detail {

struct unpack_impl_f
{
    template<class F, class Sequence>
    constexpr auto operator()(F&& f, Sequence&& s) const BOOST_HOF_RETURNS
    (
        boost::hof::unpack_sequence<typename std::remove_cv<typename std::remove_reference<Sequence>::type>::type>::
                apply(BOOST_HOF_FORWARD(F)(f), BOOST_HOF_FORWARD(Sequence)(s))
    );
};

BOOST_HOF_DECLARE_STATIC_VAR(unpack_impl, unpack_impl_f);

#if BOOST_HOF_CHECK_UNPACK_SEQUENCE
struct private_unpack_type {};
template<class Sequence>
struct unpack_impl_result
{
    static_assert(boost::hof::is_invocable<unpack_impl_f, decltype(boost::hof::always(private_unpack_type())), Sequence>::value,
        "Unpack is invalid for this sequence. The function used to unpack this sequence is not callable."
    );
    typedef decltype(boost::hof::detail::unpack_impl(boost::hof::always(private_unpack_type()), std::declval<Sequence>())) type;
};

template<class Sequence>
struct is_proper_sequence
: std::is_same<
    private_unpack_type, 
    typename unpack_impl_result<Sequence>::type
>
{};
#endif
template<class Sequence, class=void>
struct is_unpackable_impl
: std::true_type
{
#if BOOST_HOF_CHECK_UNPACK_SEQUENCE
    static_assert(is_proper_sequence<Sequence>::value,
        "Unpack is invalid for this sequence. The function used to unpack this sequence does not invoke the function."
    );
#endif
};

template<class Sequence>
struct is_unpackable_impl<Sequence, typename detail::holder<
    typename unpack_sequence<Sequence>::not_unpackable
>::type>
: std::false_type
{};

}

template<class Sequence>
struct is_unpackable
: detail::is_unpackable_impl<
    typename std::remove_cv<typename std::remove_reference<Sequence>::type>::type
>
{
#if BOOST_HOF_CHECK_UNPACK_SEQUENCE
typedef detail::is_unpackable_impl<
    typename std::remove_cv<typename std::remove_reference<Sequence>::type>::type
> base;

typedef std::conditional<base::value, detail::is_proper_sequence<Sequence>, std::true_type> check;
static_assert(check::type::value,
    "Unpack is invalid for this sequence. The function used to unpack this sequence does not invoke the function."
);
#endif
};

}} // namespace boost::hof

#endif

/* is_unpackable.hpp
2JkElnCXGtfJ36+y2wKDtZtVAcSg3jmSm1P7gvIkddUiNpV9meUdHKfdejRIv8pnkOiO+9adBMoGrOShA9bwqL4/DO2zgZVO22qSICQj7FUufMrDVRQ/uIlbCxmP1A6MAve9ieGz32P4ZmnfoPwG+bwi4yTFk5qrPXg0DD4Jg/ZoYoVeAH9S+47ygfYEuNFk6rzbHR9Vn+re6z/rp1lGu1xGRz0lO6qzF7mUQGBafL+B0FzokGNj34i9PGLnPgdGNrt87NT0EoGp50FqfF9xBh9n5UYqYjSos/Cl1pHDOttDvRLax16RbA+G9aWZalgH/hja7ThGS6q+zmRBiQ6v+CmDBhogDXQ9nV+hIZLhfWaS1BfliVQxwL3wjZ4swQ14eEtMiwQgbe9lQupGmfSlsZgXLpSrEIHuXysH1tVaRA6sj8eqrf5xx8jdzbSdQFnhfvSvIz3+cCp4McNHofj80D4HK0jVCA+K+sMxmm5cWmKNTkmokbOFuDRGraJ2s1ZXGrW6BKPCzYp9d1PGXtCRsf0qUxoqeRSI4UKhxpBJipQ4ft6YzPlTiqMzU76+2GCqMryP30wn/OvaNSVF/1XKeUF3RrJ7Rkr8QIpbK0l2f3tkCv/n6PMEnSXUdYdum5BKgZryyUVAd/dZAwX3EUZ9OhEBLXBLjPpMHAeVunsST5b08KEa53UkEoGNed4Yl6ttJVJ1tGn8vpPfP+C34HfuZHpX8ns1v2/h98P8/im/u/mdPYXeefxezO8d/N7N725+W0o4T34v4ncLv3eVcG78fpvfjqn0LpzKufE7MJXz5PdD/H6d3+5p9Pbyu4nfO/m9n9+H+F1YSu8V/L69lNOWMiRl9F7G7wC/ry/j2vG7m9850+ldzO8Av+/k9w/4/RG/82fQu2YG14vfzTM4nxkMyQyOye+Cs7hEfgf4vYPf9/H7eX53n8XllnPL87uxnOvFb8Hv7Aq8VwKd+/GsxrMOTxOea/Bsw7Mdzy147sCzE8/X8TyE51E8bXiexvMDPM/h2Y/n53h+jecPeASeP+F5F89hPJY8lysTTzaegXjceEbh8eA5FU8hnsl4yvDMxFODZwGeRXiW4FmB52I8q/CswdOIZxOeFjyteHbguRXPnXi+iuc+PN/CswvPE3h249mL53k8L+F5Bc9v8byO5y083Xjex/MRHhvGtANPfzw5Y/5+Hs9/0k/q2ysfHFcvlStNK5VVkHop/yosJ98abXKOTfVFlM4tvj9CbvlcUtHez6YfV9Fein69fHGlYj+M1L5qlluBkvuKyaNTlestw/5qNQphTuWa045SrleGVf7xmFTdmkMmViQd5yZ9HI5IlcMrvJKhcGx9eyvfO/hZ9e3RUlq0G6BkTq2wp9nBmftPJiDS6KebR7wEvhyBujxh1MWBuuwJV9iTN7Mp8Qnpy4pWoKKf75XmHlZafWqjywx9amMKPoM+NWnFKsdQqDbBr8kenOXX0IOBkYY2tYHvHsQOsPOjg6aMt6lO7StFhjq1Umj3LZRiSbqgzdSPN2fBAGnNj/UuHmy7i+KK1r5Zh2OHHTYldttfa46PnWhLvFc/9W4qQR/UW6en0wd1gzVBH9Qx0z+QNv3cicfXJ/XIgHT6pDb3+fT6pMadfrQ+qX2nSX1Szad8Bn1S2EWivFe5vKVcniqulsp7DLWTnffexnEAzY2j/MV8v15exdpEsA6mwwXMNhT7XtNvMRY4rxPrLXO+MPOmGsUlhpJ8RexgEn1UezjZvdSSTD+NnpQi/3FasvuOgkS30n8LAlsKLoY2rsDF8N/TaTyd0Gwi18twhTYug8nc++jfJvr3FfzziY7hUsMMLvQb/4QwhRHHaPdm0Y0=
*/