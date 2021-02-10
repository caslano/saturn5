
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

}}}


/* template_arity.hpp
pLWSJgF6vd4TWKenp09g9fv9lkVvrpWjeQBdtDbBNpuApZQC/Fqoe/hwdAg7t0KjBaUdTSmnegCu6FI6fhY50O22qUgUPg5xuLuvfwNQSwMECgAAAAgALWdKUmhGP5cQAgAA8gYAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q1NzVVVAUAAbZIJGDtVV1r2zAUfRfkP1xS+rBBqn2kCXQirLQZC4zVi512ewqqdY21ypaR5DT+97u2k2bZXvo4toGxraNzr86RdCUR0IdUepwxocvM0ucBm0frlJ+xD0nElvNkyYraBM0etVGpdKqQIc1ZFiqjfaik8+iY4IcwwftM7ARidBt0I68VMuGwMg11Kxlky9p/dzjRr4zGMuzoadcggu+SzNoRib1viWCtmTGj78+n54T3TRClLLCTDnu9oOxjaaxUMAJVV+tclsog0Bs6Y6DLgC6TKVI47+NBpLYoiNINe8H56cebOFlEF6eUObpZJjyrjWnWXlMKGVDx1efFV/6ShDwF0u/OwgncotNZA61lkBkNByFHaCcfcunhHrGEoc9tGDKx6bgUj85Zl1pFel5Rtp+aonI22LR1vIrnS/Jiy6awtR+w6DKOgTS/x60sKoNnpIfQu+sBu7q7hl9k92Cr
*/