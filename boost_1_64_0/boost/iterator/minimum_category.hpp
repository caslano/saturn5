// Copyright David Abrahams 2003. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_ITERATOR_MINIMUM_CATEGORY_HPP_INCLUDED_
# define BOOST_ITERATOR_MINIMUM_CATEGORY_HPP_INCLUDED_

# include <boost/static_assert.hpp>
# include <boost/type_traits/is_convertible.hpp>
# include <boost/type_traits/is_same.hpp>

# include <boost/mpl/placeholders.hpp>
# include <boost/mpl/aux_/lambda_support.hpp>

namespace boost {
namespace iterators {
namespace detail {

template <bool GreaterEqual, bool LessEqual>
struct minimum_category_impl;

template <class T1, class T2>
struct error_not_related_by_convertibility;

template <>
struct minimum_category_impl<true,false>
{
    template <class T1, class T2> struct apply
    {
        typedef T2 type;
    };
};

template <>
struct minimum_category_impl<false,true>
{
    template <class T1, class T2> struct apply
    {
        typedef T1 type;
    };
};

template <>
struct minimum_category_impl<true,true>
{
    template <class T1, class T2> struct apply
    {
        BOOST_STATIC_ASSERT((is_same<T1,T2>::value));
        typedef T1 type;
    };
};

template <>
struct minimum_category_impl<false,false>
{
    template <class T1, class T2> struct apply
      : error_not_related_by_convertibility<T1,T2>
    {
    };
};

} // namespace detail

//
// Returns the minimum category type or fails to compile
// if T1 and T2 are unrelated.
//
template <class T1 = mpl::_1, class T2 = mpl::_2>
struct minimum_category
{
    typedef boost::iterators::detail::minimum_category_impl<
        ::boost::is_convertible<T1,T2>::value
      , ::boost::is_convertible<T2,T1>::value
    > outer;

    typedef typename outer::template apply<T1,T2> inner;
    typedef typename inner::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,minimum_category,(T1,T2))
};

template <>
struct minimum_category<mpl::_1,mpl::_2>
{
    template <class T1, class T2>
    struct apply : minimum_category<T1,T2>
    {};

    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2,minimum_category,(mpl::_1,mpl::_2))
};

} // namespace iterators

} // namespace boost

#endif // BOOST_ITERATOR_MINIMUM_CATEGORY_HPP_INCLUDED_

/* minimum_category.hpp
5EcyYWGZZedFAoJ9ewP5hdsEyq05GWEEr/hHE7WOmKkDEMymk4AJZiCbCfA2EMVCxoLxBlL+qwboWACpeStdoomklGC7+U1rCHxMdTsQBEEiowuNu3mFGmO0UHy0HKIgtBvq9eht0rov/Be+pI3+9+qNlfqc6ii4SR57bjvFdhdetKggZVLS/BUEJjWcMb/UNqR5+uvPdEnNoluO1g11nBolISp3RpBAMH33oXsTlsyWVVFz7aZPlwbjwgF6/OCjbrbxUheoL7ERjBEjbpjQzBrqe6m+HC7m1EcWnMwbRt9Ls1ERq708jz0ovGwbv/3R3gwIAr/B7UkqlKFh10EylynmTxtsiIVhIOFwmUEcXW8fzL4jQoMa1TNGhaIY2sKtdlOSvu8C+cImtlaiuo3QPUQtEd2AmiqI7F1dZOiCxXixXLMNzwfmMYQtn2VMTE8pSQBpb2Oqp9K8BQ8hFA4AW/Lhswpr3IlL2pzvR6ldNGSNhI32mEM6bvV+hU1HHQX1+maHj5dm/1u9qckUrFTjUowjtIJxJ3MepTpQ3do2d/eYkLBQnFMRiXJRXA==
*/