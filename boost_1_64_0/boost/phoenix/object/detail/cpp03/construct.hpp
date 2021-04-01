
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_HPP

#include <boost/phoenix/object/detail/cpp03/preprocessed/construct.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_HPP

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/construct_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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
    <boost/phoenix/object/detail/cpp03/construct.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

    template <typename T, BOOST_PHOENIX_typename_A>
    inline
    typename expression::construct<detail::target<T>, BOOST_PHOENIX_A>::type const
    construct(BOOST_PHOENIX_A_const_ref_a)
    {
        return
            expression::
                construct<detail::target<T>, BOOST_PHOENIX_A>::
                    make(detail::target<T>(), BOOST_PHOENIX_a);
    }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* construct.hpp
3QML2L7pw7qVgTtsOk4FiCpaSrEOagVIgx6SdlEP3Z+LIscIqCsprddmKjb7qcptmEZxzVMoTXZMAGsLWi8Fxlv6QB8KKcdbsmAVD6Vke5N1QNI0OrOW2IecPmLahAuB0Q4pKFuCyLzyIeQSfGPevQhVplQJJufGL65KPnKaAgsfHtSpv1HVJCUYykGvtXtT9lJPwIYEXC6NSt6S/vrWXmLuy0ws0JF6xeDZ6J4O4qD1gc/biXWb7F+Rg5ajtHHJ2PHpAZWqEn/iVm+29vxagfBtskc1TKebXKjvzBpifVstDD5UMsvYgvr+3X73dW2Kf/2PvedYpjy+LG0z7gtK+xVSxW75mT9b/Us8u/XBpGgg29HKIUPAC8ryB/Qcuc2vWthT1dLUKJThchuNRD23r67Hr4ABKJh5m0Pi0Rc90+p+pfK8ynOexDL5zqI78TB0JYeyilQEgQDPzy2kPyrgzN1w+PnQ/E8pIfXwVTFzmW5xmHZ+cmyzYjV9YuVk7kKoHM9ZBLsNFF3GVUR0N4Ca5LemC7IaDqeA7ZvyxwdZFscKQiYfVBzyEH99yg==
*/