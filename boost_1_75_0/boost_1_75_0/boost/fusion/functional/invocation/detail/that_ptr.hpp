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
rDwsYHCSazOnm0Zx9r408eNxYJSqVGWx60ZeTi+3GN4kN82MnSd9RftjCsQNJ7pjo8T+uDdn7CVWwdjzrTT9tufTcbsqUv9ppRxAVWj/W432v1TUqEbHqpX4r8zVyuTAEmOCtALWagPlmKBRcgzzNF08Y+VW9zAPl56ieTgb5uFDZpyHm1pxHnbQPNw3pTIP1jH8d5qHsz2Oj89YRZSNCT+RpX0ycG0ytN9BjTYyybqlfXJc1GupttzXRJCRbItXQncl5EztN5T1bm+LtIXunFZm5eq0KCvXVNyMYTAQj2O45mflmqquXLvxYRoV544xS4exKG2k9QZ5NzKkmhrnaZBSUTwaVYaeMHuXWdrXxySSifKTn520k1UhmC70TZjkkX5w23Bbow0NI21tZHE7DG65+3drGT+4SG3eNlI5jTbrfnCHOfcWaZfWkr1pRlwZ77dIrWoY2ZlGknhoUJO0vzHFD0B1miHBuL9QyQvjNIMbmcLOEPM9/SXXV59t93Jx+fuMVXHHZOP9tzOybbjtxtk8XP/CgjmWNYqLs8OPgldYg244oy4AFCzr04jLjNYKLMiDRe4yoWtQzuS4XgvyX35OMSNOwvdJmxeYyiWMaGYRI62ehUbRPbz8phKVn/NyUTAsoJvNIBebOZXkGTecjU2E8we39fPZdDjmOppVx+lKwNMauy5U0+icCw+45HkfzLyj0yra8875s+zE
*/