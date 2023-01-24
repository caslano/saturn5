/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_DEQUE_02032013_1921)
#define BOOST_FUSION_BUILD_DEQUE_02032013_1921

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/container/deque/detail/cpp03/as_deque.hpp>
#include <boost/fusion/container/deque/front_extended_deque.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_deque
            : detail::as_deque<result_of::size<Sequence>::value>
        {
            typedef typename
                detail::as_deque<result_of::size<Sequence>::value>
            gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence>::type
    as_deque(Sequence& seq)
    {
        typedef typename result_of::as_deque<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence const>::type
    as_deque(Sequence const& seq)
    {
        typedef typename result_of::as_deque<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* build_deque.hpp
Ao72GR2F4riF0CeNFz9Gix9DxQ/YEav7jJPscgXfkKHTsan0AHpZvELCyz5TyVZSC9A745KUBoIhvGD/l8+Br8zUTvnskrgHo5W/WspbcvUtufLJJbwlR9+SI39y8yVqyda3ZMvzXmf3aK4UyIUtDSLpK2DgZeFeQmsllzOasZ1C7Rx6ua/o5f7VTDmLVAqdeb4oUtAAKrruMJWcFvrVX6/5UFeAQiYvXSBukUGDqAzJSbF30uwoJSdV3ZRMNEmggYW8dkeSB0cBd/7QpOZqUIPFh/+Ih5I7cdxlRElGugETUKYl08ubSm4yNkrKz1wVpJy12h9SnlFKpPwm42y1Ow2woLHXBeDaZZD0LsLk6AMVQb8/r7lchBHoZ1X7qRuBXOi3C/sB0hgq2rmFhVO/e6DfSuwHeGUYbOeehAv7tYN+pdiPUG8qeQbP3CkI9ZMjr0GB3lcoGRRfWVM2g8e3mKw/lxCz+D5Ag2HbiEawezhIMPO/VvmD3Q4lhN05AVpGcUMJOtEfw+kKWmaDbpdroV3ucuzrKqaSz3Clv26UH4ujuMYsCcMUeHkh/zhe3HFBJjf69SI5xfQiJ4xaEB5kV5XE/Dg/TWtKZX7uBxQ3HxVQLPvIHyj2zSIoxumgOMCuZjidVmIoGdIBkPVQ9KfsjyR5YfzTLF2m3UWzhKyYrQ34/v+YexO4qKo2YPwCIgMMDqijmJqYppSlpKUQ
*/