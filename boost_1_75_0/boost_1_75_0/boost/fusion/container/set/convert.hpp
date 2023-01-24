/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09232005_1341)
#define FUSION_CONVERT_09232005_1341

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/as_set.hpp>
#include <boost/fusion/container/set/detail/convert_impl.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_set
        {
            typedef typename detail::as_set<result_of::size<Sequence>::value> gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_set<Sequence>::type
    as_set(Sequence& seq)
    {
        typedef typename result_of::as_set<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_set<Sequence const>::type
    as_set(Sequence const& seq)
    {
        typedef typename result_of::as_set<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* convert.hpp
2jfwsivdTaLCyW1fwEYbzae58eNvyF6/eQUb1tLTk7l+vKpfTfUlVH811//nFSovotvDqTiPirOoOI2Kk+ARv2Ds+/GzPZbg/S5UJEKx0RxNr3FwmwK6PJ+KXW9ikcUvzaS7x1FxNN9du5i+n+4upatXqTj4sjMsHrQVc+bNZMuLIh+iQP8S8j3RIFjYvWwB91yQjMwKgX+FYOqCf101G/nXF59F/jUxlISS30KzRz1ZqxWK86uBVRqF5gllLnRrsBwpJj+sO1JsREcKf9abxLbe4UCy1FuNIWHQThIdKgpj2kLk/jB8/25Md54l8F+5P/Trnoj6oUzUxMrwkIO5j0LkcsmTobWbxuLiSUQRXgoxAKc8CTrxk7r3xHEveizvid9xH0w+rS1JHG4rp5MeDWUdICD9ArHDjdmq4WFOGwI4iEHU14d8N4tnUPi53OAPzas7V/lDXDqdY8NEz8ZdqO5K9wqSVWGgG+kgoQRV7CHxwmWHDg3z6UIJ9+sXElit5vLthQhJoxfT5UJoCH5sZrfBu0MgCBq6uGMYuzgxEsZOn6bBmL9Og7FPCcaufAJhbOLTCGPz/5Qw9saDCsZ+qFcwtu6OcBjr3fAPYOzH0G6Gse/3RoGxVV0PF8YeOOKfwth78yNh7KOfAMZGPfT3Ycz90KFg7Jdp//dhLHfkoWHsjhcljN3wIgHTGC4vfxFhrP1Vugy8KGHstdMJ
*/