
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_OBJECT_DETAIL_NEW_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_NEW_HPP

#include <boost/phoenix/object/detail/cpp03/preprocessed/new.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_OBJECT_DETAIL_NEW_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_NEW_HPP

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/new_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS                                                \
    (3, (1, BOOST_PHOENIX_COMPOSITE_LIMIT,                                            \
    <boost/phoenix/object/detail/cpp03/new.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

    template <typename T, BOOST_PHOENIX_typename_A>
    inline
    typename expression::new_<detail::target<T>, BOOST_PHOENIX_A>::type const
    new_(BOOST_PHOENIX_A_const_ref_a)
    {
        return
            expression::
                new_<detail::target<T>, BOOST_PHOENIX_A>::
                    make(detail::target<T>(), BOOST_PHOENIX_a);
    }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* new.hpp
b2/gw/NSU5BdA9bRSGzcIuI03LjTTeEmWNNwY+KArLA0U1iGlcWctED1soltxhuq8oXEddXZrAHoFqKFXQ2vcQ/71/XUFuKca+0/hFgSbta4myqw4GY3Ik735FSSFkszbaJI7sTAzVrpGWxDbMAiPodBfCqalxhuemeT4cOfWTx66mpuHePtGeXhFu7iGursDLJxEWsHm/wEgnVNfrywOIXy22Tgppw29NsilWeBW2FJek1hEkFcBDqVyMZZ8boqX2K8hpvGF8NNOWisRTMMWfG6tfED8bqTrEMksKYKLP4MT95O1ux13HhJrw2r0cnO0LwNaXbNitoSWVs+0nQzs4719gKpeBhk7cTFOgZOJZWYm7U50C7PFtCiNgCNltjTU/F2scbpGTVBpZFeJu0wazGmaUyJ406hmbbEYhptamK8r2TWbmSvkz61mDYhjWh+WdK2uqWVTIlUnOx8eXeQtbltrI83Zo0K45B1bnISxRpkZW2OudpiDVJxYOOUGwcpGVFO6RRrCjdKwv8h1intYJ3QNmtXwroj6JtrMVkH01byklEbzleh2zV3i7Mt1u4WBOsIV7dwV5cQJ8w6OS8tNQjkZglBdUXJXWEN5yoUpWLcpFF3ljWupVQVtLZRS+ko6zQuibtxjkE3fW6DGGtGDc2TWOzJYk248bZZU01tdDkhRtuLeX0ojp4XB+s4X98YOOxyDXd1A6Yd6+sL
*/