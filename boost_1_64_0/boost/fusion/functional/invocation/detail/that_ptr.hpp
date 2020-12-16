/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_INVOCATION_DETAIL_THAT_PTR_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_INVOCATION_DETAIL_THAT_PTR_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/get_pointer.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Wanted>
    struct that_ptr
    {
      private:

        typedef typename remove_reference<Wanted>::type pointee;

        template <typename T> 
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline pointee * do_get_pointer(T &, pointee * x) 
        {
            return x;
        }
        template <typename T> 
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline pointee * do_get_pointer(T & x, void const *) 
        {
            return get_pointer(x); 
        }

      public:

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline pointee * get(pointee * x)
        {
            return x; 
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline pointee * get(pointee & x)
        {
            return boost::addressof(x); 
        }

        template <typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline pointee * get(T & x)
        {
            return do_get_pointer(x, boost::addressof(x)); 
        }
    };

    template <typename PtrOrSmartPtr> struct non_const_pointee;

#if defined(BOOST_MSVC) || (defined(__BORLANDC__) && !defined(BOOST_DISABLE_WIN32))
#   define BOOST_FUSION_TRAIT_DECL __cdecl
#else
#   define BOOST_FUSION_TRAIT_DECL /**/
#endif

namespace adl_barrier
    {
        using boost::get_pointer;
        void const * BOOST_FUSION_TRAIT_DECL get_pointer(...); // fallback
  
        template< typename T> char const_tester(T *);
        template< typename T> long const_tester(T const *);

        template <typename Ptr>
        struct non_const_pointee_impl
        {
            static Ptr & what;

            static bool const value =
                sizeof(const_tester(get_pointer(what))) == 1;
        };
    }

    template <typename PtrOrSmartPtr> struct non_const_pointee
        : adl_barrier::non_const_pointee_impl< 
              typename remove_cv<
                  typename remove_reference<PtrOrSmartPtr>::type >::type >
    {
        typedef non_const_pointee type;
        typedef bool value_type;
    };

}}}

#endif


/* that_ptr.hpp
A9pgQaWNOBbGwlgCi6A9vokdsCS+g6XQH0tjfyyLQ9AOx2BlnIpVcZFR278G+C06yhw9TlgBnbEBumAL7IZa7I5jMAgXYjDuxBD8DEPxDvbFVlwHBuBojMAJGIkzMAo3YTQewhg8ggPxAsbiHYzD1zjv4vF1TERXHIp+OAzDMAln4XhcihPwOE7Cb3Ey3scp+DtORSvOr2lYFKdjGUzG2jgHW+Nc9MV5GIILcQAuwgRMwdG4GN/HZTgLl2MyrsDtf8G2RP/OdkQhBL+/YDuivLYhKrbJ8g7EsliW/+blz3j+D9M9/v+x53/l/b+zMtYMN0hcQcMcHZxctI6NHLQxGv3fppj+rV/m31z425MMk78NzPxbQ2WbxzP/5uTg4qp14u8xRn/71ORvss1Gyt9OqP9mvE0H1d8aNjLepsNJ9d+Mt+lwyuRvAzPbL1ym7uOhrg133scnp/8c69f0GOr/Q8GPl49MffPKiRVTD+X9OSqvc1Gbfx54dc9d5p+vcn4eM//clffnKPPPRXl/vjL/HJX356X4/Ib7J3t+k70JMYQZhO2ESwTNZltNNYIXIYIwkbCMkE64RHhCKLnFVuNA8Ca86D7sEJ3ILxGeEIzvyTIIYS24x8A0zCDcIij3ZjYtDfdnQ1qav0dLYX06IeterVgr8/drGa1efM8W4MbnMQn98BCau38r09pw/zajdc73cC7u3GdhL/wBkzCdoG4bLvdzebiXs/EkbsJY5d84hbCdcIFgfI/3RPlcm8x7vQg0vd+7x7rhRvd6Dm3JX0IIIft9H7bje0b3fa78ez4h5/s/w73fEC/D/Z9lsSyWxbJYFstiWSyLZfnvW/6M5//QmNhXMv/fl0Zt+LPGBd5OsCNsJtRXnsnrZ73/7xcaFRobGB+qjYnVjQWeu7kAPqmvagugencerzE/RrJ6/re4wL6hrFPPmxcSIt9NknWGd8vyXr+8rm1AYEREUGDwANbLe2irgrr1QdrAWGoJ2IZ6/OeorO26Yt3ymZ/lf1XzBGyXW/WuklfeBAc+q9G3lQiPy8yl3M8TIPtFOo3bMQSHhQYPIEdkfkAz+1VW8k/fFkIbExgXFxqS9Z2YHPbZLvv+6ctCurz7C5T960Vw4rMx2fZP2zeQoeFD4+JzURZIv8l+huWwnzE57OeQF+xnkpn9rChlQdplRGvpfBIYodU1JAmPjpJjny0f5L17zvUS5us38j7mZF7rbf5T8+uZr1fJuT7HfH1R3uth8vr+/lX173lb975cW+XDr6OO/Tz5XNcFvw5PDtiac32U+Xq5nOupHhDvRI1cW+Wa+4T/eR2Hy0lTnsNkhxWxFtqhB1bBjlgVe2M11GJ1DMQaOABr4kK0xxSsgyuxHm7E+rgZG+ADdNXI9Qu6Snqssa6kx0XS0whdsDF6o6vR92Pk+4Fmvt9Svu+GjbE19kIPZPy8F9WPSV3c/877yv/EuAcTB9n+W95ZhlG3OZGwbIvl3aVlsSyWxbJYlv/f5U94/ufh59W0/8/g+d/JpA//hzJm1XhCcWU+h6ryzMf0Fv5aplHJ6gOQ87OezFehap9vaP/MxrrhQN125VlUPwdB3xh5BlM9b2+RtL0jaesqabunSltf5rR6+bgC8sxnnDZVXC5ZY2hKXMsViSugmnFc/ai7ePmzvfQ7MDuHn6EORB1/isQ/ilBUngfeVI5DdeP4o0IH5zJ+2VeJS/2cX1Ke8xtKXA4S1z1VXHGhwQmxobooc3ns7SROc/uXJHHOkPydnFXOaqjiVKbmyVVcJuVMNUdJSenTclDi2ksoTVyamllx+XTp4q3tGx4VHheWi317XeIrqasviDGUXZN+JfaGeXyi9HVHkqY=
*/