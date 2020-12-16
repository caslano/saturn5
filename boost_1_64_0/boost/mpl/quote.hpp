
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_QUOTE_HPP_INCLUDED
#define BOOST_MPL_QUOTE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/void.hpp>
#   include <boost/mpl/aux_/has_type.hpp>
#endif

#include <boost/mpl/aux_/config/bcc.hpp>
#include <boost/mpl/aux_/config/ttp.hpp>

#if defined(BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
    && !defined(BOOST_MPL_CFG_BCC590_WORKAROUNDS)
#   define BOOST_MPL_CFG_NO_QUOTE_TEMPLATE
#endif

#if !defined(BOOST_MPL_CFG_NO_IMPLICIT_METAFUNCTIONS) \
    && defined(BOOST_MPL_CFG_NO_HAS_XXX)
#   define BOOST_MPL_CFG_NO_IMPLICIT_METAFUNCTIONS
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
 && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER quote.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>

#if !defined(BOOST_MPL_CFG_NO_QUOTE_TEMPLATE)

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename T, bool has_type_ >
struct quote_impl
// GCC has a problem with metafunction forwarding when T is a
// specialization of a template called 'type'.
# if BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4)) \
    && BOOST_WORKAROUND(__GNUC_MINOR__, BOOST_TESTED_AT(0)) \
    && BOOST_WORKAROUND(__GNUC_PATCHLEVEL__, BOOST_TESTED_AT(2))
{
    typedef typename T::type type;
};
# else 
    : T
{
};
# endif 

template< typename T >
struct quote_impl<T,false>
{
    typedef T type;
};

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template< bool > struct quote_impl
{
    template< typename T > struct result_
        : T
    {
    };
};

template<> struct quote_impl<false>
{
    template< typename T > struct result_
    {
        typedef T type;
    };
};

#endif 

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(1, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/quote.hpp>))
#include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_QUOTE_TEMPLATE

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_QUOTE_HPP_INCLUDED

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

template<
      template< BOOST_MPL_PP_PARAMS(i_, typename P) > class F
    , typename Tag = void_
    >
struct BOOST_PP_CAT(quote,i_)
{
    template< BOOST_MPL_PP_PARAMS(i_, typename U) > struct apply
#if defined(BOOST_MPL_CFG_BCC590_WORKAROUNDS)
    {
        typedef typename quote_impl<
              F< BOOST_MPL_PP_PARAMS(i_, U) >
            , aux::has_type< F< BOOST_MPL_PP_PARAMS(i_, U) > >::value
            >::type type;
    };
#elif !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
        : quote_impl<
              F< BOOST_MPL_PP_PARAMS(i_, U) >
            , aux::has_type< F< BOOST_MPL_PP_PARAMS(i_, U) > >::value
            >
    {
    };
#else
        : quote_impl< aux::has_type< F< BOOST_MPL_PP_PARAMS(i_, U) > >::value >
            ::template result_< F< BOOST_MPL_PP_PARAMS(i_, U) > >
    {
    };
#endif
};

#undef i_
#endif // BOOST_PP_IS_ITERATING

/* quote.hpp
9/e/Y9X9XUjH0H1OlO7noqqh+zlIx9B9ilX3WRG6v1rqPgW6v1rpHr9UiH6w1Rqiv99qDdFfb40boivdF5p0j0GkrlXpHoPIKkU0HYPIEplWIwjGDzGzEbo3VhLIx0H3dTF174rS/chWq+4HtsbRff8o3be/bdV9C9IxdJ9q1b0nQvdXSd2nQvdXKd3jl1pZvR3kjZXVHyBtrKx+E+mYK6tK9zMio/1RaGRE+4OQNqJ999uHG+2bdR/M7OjqUhulsVfbUVov91TzuYAcl3U3uAO7wWWG35muXimKxrUqTW1tckurLF2r3qqZSdsl6TUqA6Tl5kpZvEodyiii4r5y66EkvkLtMQdx6wZzR9FyuYePibvtwXeb+N4MnH4rvjiB02/H/o79Hfs79nfs79jfsb9jf8f+jv0d+/tv+uPzsrtx/8nkmPdpFPN9GtVDaX5UrO1Lt1ypIbN35IlbNWo4KS7WeHMIZ7l8zURZVqvvZ71eY+/Uw5lgmO9H+ZF4CkiY5XGJqZo47c73oWyZnu684p4//w0l2BdLJTa+F2XLdJvz1FN++a0nXdirKU6t8/0oW6Z7nF+zXX7nEy5xWFCU8D0pXNLcNqY/l2BehsfwfSn8mGtO9l6jM5AsSvjeFC75yYXrf6qXpIgSvj+FS/qMdr+ml6SKEr5HhUsGFz7+FRwBn5JEf1umTOf/4EB9ITKmzkAGtVnUlCT+uPrCXfRj7GGeuE9A/6b7WV4cEn0/C/D0/KSYeFpowtOlX4qJp9uGROHpzkHReJrjseLpV5MPE08Ng4D/Sfr9LcX6FSR3skbp/k/czxLGFS7GhRzX0xUuC3GFS1he4RKmtzcvOsUVLuGIK1y+nCaO+l+Po/5heYVLmHaviiZU645pU56wAWy3UeESZ19coDIlMGv6oy4tNHpPl156a2SpR3veKK2MLM3VHjFKF0SW5ml3GqU/iiwdod1olN4SWTpWKzVKb44sHa+dbZTOF6WQslDP+6GpRWFg1gySMtlocVNkqUd77zRVWhFZmqs9Z5SWR5bmaQ8apTdGlo7QaozSGyJKScp5RukPIkpJyhKj9HpRWmbjC+PZS2kXi6t7qipdSRV8e8qZdH8FsMUGiqsjOsbypTQdU7IWu4lIMMMe51KalKyqdylTXkyzje+BnbHNyfdZ0K/SduJky6g9XXyrjF3dKiOKSIR6LrJepoIikv3OeEV52k3xinK1r8cr8mhT4hW5tGFRRXdQkSUjmMq3zrji3c3jilJDq1CDFqBfpRqpoXFklBpQRGr47cho1lA0QrsjXlGeNi9eUa42O16RR5sQr8ilDRkZrYbWGGoIOb2NoeR/730a/+1/UfGA67kNH2OgpntxrPHAxPu3LeZ4gO/HscQDI8MrDvGoz/fkWOOBD88a/A0u4ftyrPHAzkXvPsSP4XtzrPHAiXPPG8klfH+ONR64duPUz7iE79GxxgM3f+nWbC7h+3QONx6YcqTiAdP9PFfGvJ8nl8fXjeP2dMEii3GBjBt36RgX9fyG/vW+SIP5ow7t5nGwD8fUKdkl0+lCbLq9i0TCbWq0tN82sXD6D4fdkBHgtDZx2pQbc3GPTyHf4zN1RlUTK8RfUuifOsP7YvkQQfRc7ffDdaKF2SUzcDVOoZ9+kFnSA6ZN4Y92XTid7e9JaC5r8W+F8p7AML+EM8WNOBPpiqvzRAzUWYL2HQ5ou1g7fxsGc6IuogcHLvDxL+ffQswN7NEuxpU5GCNcfHkPiNO5fdE6ovc8I/m6co+IF0hpPLp0cEt6pyPu7bm90sM83jAe9xelgjLKm0Q5mnqoKRGjG2MW4sYYuvCG6o2kW3xK0Q/leYZIHbRv6Tnwwgw=
*/