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
LyEMQv9f3IrLgQ3jdyb/B6Qv+H2GRYNlGL8bOnsW43dWERiG4vGRng3jGTZfSDD6V4MQvxj0iBltF3gtP3gMndk8ZpWWzg73949YDT8HR1V2tuRezEN24ZnLaRnogQA93K+ytuk53GWjmHsTHs6q7KMtZj7NzYeHesR/qTIeM9OtC57juROxyJ/GKzPkDM+uY3Ev4jYzI2bzyAqdCQaOx+I5Z1PH5ax1Nfjc7Z9V2WruWHPQePSXLJr7S9dmc/Oes5Bb3LmXJAIzjJk/BTZo204Ug94ydnyvDtacYU2LCCSIuelGPjPvTcc1J2Bjxmwex0F03GhYy9CF5A3bt6KGlSy9Po8XahWfIcHCfGR+ELPYZ8uIVxnBVdnCt50p/UIVmAyWE9eJ5tVMFDDy7IYfsoi7LkgBzeGRFJmzkdJMlaBYAGmdmH4i34uI02ruLwqAUCGITJehBzZQAWBsHwqusqVnYwPjZNEJB6VNodotW5LJajPfgyRspzli3dEOm5iRE1XZTXd8fnU9ZjfN4bDZH39mV6es2f8MWhfdfhv77YBTyPhDEPIInEPmLALX4bZg+Ee6sbb72j+SaJddmndcGNsUwk6Wjms73owJO/DcBav0eXxD2rnHVsCYYPwzj0zgjuvarqBwHfFjMcFq
*/