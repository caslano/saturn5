#ifndef BOOST_MP11_DETAIL_MP_FOLD_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_FOLD_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/config.hpp>

namespace boost
{
namespace mp11
{

// mp_fold<L, V, F>
namespace detail
{

template<class L, class V, template<class...> class F> struct mp_fold_impl
{
// An error "no type named 'type'" here means that the first argument to mp_fold is not a list
};

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, <= 1800 )

template<template<class...> class L, class... T, class V, template<class...> class F> struct mp_fold_impl<L<T...>, V, F>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = V;
};

#else

template<template<class...> class L, class V, template<class...> class F> struct mp_fold_impl<L<>, V, F>
{
    using type = V;
};

#endif

template<template<class...> class L, class T1, class... T, class V, template<class...> class F> struct mp_fold_impl<L<T1, T...>, V, F>
{
    using type = typename mp_fold_impl<L<T...>, F<V, T1>, F>::type;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class... T, class V, template<class...> class F> struct mp_fold_impl<L<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T...>, V, F>
{
    using type = typename mp_fold_impl<L<T...>, F<F<F<F<F<F<F<F<F<F<V, T1>, T2>, T3>, T4>, T5>, T6>, T7>, T8>, T9>, T10>, F>::type;
};

} // namespace detail

template<class L, class V, template<class...> class F> using mp_fold = typename detail::mp_fold_impl<L, V, F>::type;
template<class L, class V, class Q> using mp_fold_q = mp_fold<L, V, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_FOLD_HPP_INCLUDED

/* mp_fold.hpp
29GQM/Z1oBm6Zm92NFyif/r7aLyjexqPabqbGgNYpc2oci9Qs0C/l+pMUp1JtcLV1DiJle6GSkSdF0NVbTVge8UodulCZuqXfp/T4NxY7UZXwDY3vnQdvZSP3EIrPF+tLmxqLMCf2HqBWlFAjUlVWLygRu8bN4gN7z4PSPrliSpkVUQteBe5o0+OCGqXNzVOOOpvRDeDoqOFr2cZn9htKKzNzRKj4921OB5ggDz/FL059jEcC4A//pc9fgF9h7wF/AJ349xCghQ66lcRNgDzcuy9uqCG2Q9JiSFxE3TZVuAKzw829eYDYNnjpeNLNMXL2RLj4bZUdVfrJ7/OaGDtHA34V0CszYO6NfpdXya6zsxomvkHxicCC5BvgAmA2Fz4jDEQ3NpqV5Xu5J/oXKmG2R44yT9lN1JDf/akWbmoSt99mn7WvYHYRd+ffvrHNKynirPxff2V+fBCbHkzZ2BK8uYqhAxHe1HEbOdvjFNDP/8qsQ0n3B0okrbh5Kn9mkUU3QUjre3nhigaLzZEDoxjbs9FMoOwVMNtTZPDBr4Vnmr9NV87fb5Kf/NhmkDcglleVK0XDxNxocSGrwfxvQXmkjHI6ooYgWL95LOGTGFZUlC3iEtW1b0VUHvkhJCyZ7CFG2BO4W7UqiKaOUWOhmvqSqz17+P6dUsokz6THeqnDqCJ70AT8Ha1/sYggYmjqn4hEfrIo5SDiyq5LFFsBXHIbSMGFZKUfogrmbIN5VYAa9WQmG/kcotck0CuYfl1dS6qcalYCOoXQA5PV72ARBz6bPtWe8/Dg/NzHsH+ky9iESwa0+HXdB/gj37vQSSsW10FgzYO/32SWpEfWRrF/3c/Hof/buI/mCPhD9u7jfXVTevri+reIkb03cDGR4+z7HyCP2pNS+sceMdYWmmme3kj0NifrPDC8ClsWEa1ga0lBFJ+08nshkJcu5CB+D8toVvBEhCy8x3jm6i5/KZnshrWGbOPJ6Kbl10Su25cOW77silFr4+siosFyyPOdNXo+ZbauYB3loH3Nm8hIIMf7WZk5ODMcpf5UUXrUG3w0gKP3vMrIeAS1K/bWLsHK39MVLa314PtbbsMqmyZSnu1DlwTly+E+iunVH8n1S+E+p4p1XdkQ/09Xqg/8vSU6jux/sVQ/9DU6ruw/guh/k5RP7E83wBgE4OLHPULaBQUgTGJZkJV0fhtZGN6q/XHZjkcJCVC7PwvW1249WKqXViihFjHezAH67iNnZzqQhr6xY6pfdHdXC+vJSPDW6WP5VCftA7ckk3p2m8gO9cWFXhIAP7iBwLF+Pg1Ph3Gr4FnbrGjHjXaN9PIX8LrzEPUvlsI9MVQ1re6OAt7Oym6rHtHXT1M8yd/KhYumKMk8KoeI1nI5Gg6wsQrnN6CFYb3iV+ePl/7QLjPpXrDbyPXmlotXLiqrg4AWh0G6DIC57DToFuIWHfcRT+nB44Jzy0Aj34QRLoBQD3apn0rl7gTaF38fhTVF7A6A7tMJLWLxsspo7BKjLJPQI+s5L609jGT7LX3sXK67glC1NbK1HBCfCTE5x1DMB5YkL9fyHUUlCCVx3mrzssbgLiDJzbDYcX0bL0YSvE1iZbjDayhjQ+QsMUmdpXDeFGrXbUwbhh0Q/O75jBxECqyzFXnjN0LK+Z02EHwexH+r4I28VpoB3usksqqPfNbQkiq60WntRVZUO2nT0eMGvSrvDyLIzOZcaA1jPOOuJf32fE6ELE7CxqAZ2sRlFbrn/yjoYlKTc+46+fVYRxhlX7pMA358ceBFsQPt3rfyizSVPruQzrgAwVoXBWI1c5tbByudhkyYsH4i4ki9GM3vha7ajW6H2hWeXjxEpNMQq0=
*/