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

#if defined(BOOST_MSVC) || (defined(BOOST_BORLANDC) && !defined(BOOST_DISABLE_WIN32))
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
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
*/