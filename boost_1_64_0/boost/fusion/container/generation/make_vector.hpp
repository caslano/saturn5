/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_MAKE_VECTOR_11112014_2252
#define FUSION_MAKE_VECTOR_11112014_2252

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/generation/detail/pp_make_vector.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <utility>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct make_vector
        {
            typedef vector<
                typename detail::as_fusion_element<
                    typename remove_const<
                        typename remove_reference<T>::type
                    >::type
                >::type...
            > type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::make_vector<T...>::type
    make_vector(T&&... arg)
    {
        return typename result_of::make_vector<T...>::type(std::forward<T>(arg)...);
    }
 }}


#endif
#endif


/* make_vector.hpp
kX9HSJ3vu1I+H0r57JXy2YdRuB9j8QCOx48wAz/GeXgIF+OnuA6P4LtYhvvwOF7AzzGQTHyBHfEr7IP/xvF4Gu/E7/F+PIfL8UfciD/hPvwZD+NFvIi/Iu8XPlgoD/TBpuiLrbAmtsNa2Bv9cDzWRivWwTuxLpZgfdyLDfAj9MeTeCUq5d0QQ7ER9sarcDA2wWRsitnYDPPxb3gXXo3zsDkuxgDcgi1xHwbix9gWj2AXrO7D+wY7YAheh6E4BHvgZOyJFuyFudgbZ2E4PoZ9cSVegxsxAt/Ba/E77I9nMBJr891qANbFgdgMB2EEDsZkHIJmHIq34zC8B2PxPhyOD+IIXIkjcTWOwk04GnfiGDyF8XgOb8ALOBZr1uQ+j80wESPxFrwRx2MmJuEiTMalmIKv4AR8DdNwO07EXZiB+/FWPIWT8QJmYi3eF1l4JeZgc7Rge5yCnTBX7quRJqkDwzj5HPTFMBITzYCsjykYihNwMKbiMExD+3bKLrGdSbKddNlOhmznVtnOZNlOsUnqmLCR3OcbqvHomNT4cU3xeQzEF7A7/hPH4BaciC9iLr6EVtyK9+LLWIiv4Fp8FV/G1/BVfAO34XZ8B9/EE/gWKvfgndgA33bE9ZM6I2wt32u1cf1CNMuVyXKdLrmc1L3I710/3XIFmuUiZbnOl16OG74zf6Uk7XJjtcdxieVStMehyZ/75Zi2eba9EFmucyXLWWS5Tm6WO8n7nvhBlcYm2pJD/+GI6i79jBMtzr7GgfQntvB6MUnb79hnCn1tSfY4RJFT1H7Ihbp4RGlTKsYkCsII0lz+VkzaQwpjfiLzTLksSyrg3+3QXdyimFxn7KKZuWwDT/RX+zgX8XoL6SDpAikij3yT4vmbVdMHupB5Pt3IA/8OwpI815hHZaRmVpbjdSSmkUyRLM/rQJzJ6yUkezykmEjWwfXMO4+7UB8b6aSV9Q1iJAXkU/a8PkOyx0tKY95BnImLSRf493psNoBtYzgGhJCmqn2zLaQI/p1IssdWupt/ryDZYyyVTnXGWTJNIy/KtkireF2O+rhLESwTTzrJ67vR3s97Bf8uxeMkvyg1JtNe5tULZTsYxDy/AuR1FzSK0xTP/O0YE+WM15TIv2eTNHGbpP84svxBUjkpgtclzN9OajZd7Vceh1Y8zrw0/u0XTRmgPb5TXHTlMZ7U/ue8Zr29zIse5Iz3NBdLSHtIjXl9gmXaob6P+kxlWemrHjbD2V89jn/fTSomxfC6FI3iQh1nfiHzi0m7SCdIRrGiAnhd7zY1ZlQXtPV7x3gswAWkmdIPfjP/fhkPor5PfMBMtV98mCKvE3AmqXEM66I23tRmXkfiYQzh76a/V3fEn2rHvxOYF4MFuEDiURX83dnPfgGvS3gdQyDONNJs0gpSKekwyTSU2GCkCFIiqZBUQjpM8hnGmCZSHCmTNJdUTNo+zNt33zt5J+/knbyTd/JO3sk7eaf/t+lPGf/fJ0np/n/Z4/+Vvv/zOlDXKv0006XN4gZSa6kXvFbpp7lK7ac5aHjStNwMHgZI50TnIH5zSpbJ8zhK+j6VMQb9yuK0fdRlXoKu76W2L/1JyXdPqePqRupPvsvUfI8Zfv3wQUnkUyIPeNwnT80DB6vp83G4iW1eak621aXf967q8nwrKbsiKbvA1c48SOnZMuFJn37pd1chH+kGZWYx6LtcYNBfNdIxL9U63WJOoneh9MmTfln0/U3JZGFd7MCZ0l5zvRxftBxfuXp8GT2kcJVrQ66Kv+SaOKOUfXV3fVX+ur45xn1Y3PXZcdcHp+p9an6vvirGfXPc9SX56/rmGPdF+uP72gwcoczfceuWnwJrVlv77KM=
*/