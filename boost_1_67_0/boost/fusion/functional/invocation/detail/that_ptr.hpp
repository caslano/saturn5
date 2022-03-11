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
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
*/