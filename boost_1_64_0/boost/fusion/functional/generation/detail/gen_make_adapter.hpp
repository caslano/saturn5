/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

// No include guard - this file is included multiple times intentionally.

#include <boost/preprocessor/cat.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>

#if !defined(BOOST_FUSION_CLASS_TPL_NAME)
#   error "BOOST_FUSION_CLASS_TPL_NAME undefined"
#endif

#define BOOST_FUSION_FUNC_NAME BOOST_PP_CAT(make_,BOOST_FUSION_CLASS_TPL_NAME)

namespace boost { namespace fusion
{

    namespace result_of
    {
        template <typename F>
        struct BOOST_FUSION_FUNC_NAME
        {
            typedef fusion::BOOST_FUSION_CLASS_TPL_NAME< 
                typename fusion::detail::as_fusion_element<F>::type > type;
        };
    }

    template <typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::BOOST_FUSION_FUNC_NAME<F>::type
    BOOST_FUSION_FUNC_NAME(F const & f)
    {
        return typename result_of::BOOST_FUSION_FUNC_NAME<F>::type(f);
    }

}}

#undef BOOST_FUSION_CLASS_TPL_NAME
#undef BOOST_FUSION_FUNC_NAME


/* gen_make_adapter.hpp
PUMPl9g86NTeM7YYvP32iAzyfEur2NonI8wjPf3+AAGu2quznrTQh9czTZF+TOBwzZrYE1G91LYwkil/DBDdZuVC8gHhUKiS7kqWpxxdAdu4AxPSCC0Aa7v8nb0vFVOqBZSjbxKTW0OnhMxwDeW1UTXj/azglguh21si0G1NbZQEwnPKxL5LopdvQ0HnuF+FZjIZP2Z3eD1jy0RTjIh1UalN5iPJIy0obuoTd6vfge2ifu9RaYhd3gVqaAtskYCSrCtO1i5NiRDO883xA4QueubWapw4YcgoFgRjUrI4PXO4u7/IdAQfvtsXUxq8Qt5zpi5UDkZSZ/HBZpOCP7xB2o1UWssFL78UZr01Q0ODPEq83+R7sm0Zth/1aW3W5M+Nth5hsmwfPGdG3X3rb7A/Uw9Gjrjt6rjKtuK2+IiYUqLL6FgSAfLqmDOecic6K0H8JjoROwDBZnsm1NQ6ZWzFTkFKluoVGt4daqds4jpQSEcttaMoxTOeZmLpjUJgCvJyfV+WdQ+aiXZUjnaKO6//A+eZOotav8etDwDhye6Lesb8iUTkCIJvKEGy+w==
*/