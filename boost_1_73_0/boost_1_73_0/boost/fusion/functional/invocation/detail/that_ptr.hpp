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
bA5TH56AyKBAi4WlL6OkIVXLVOVbhBhHkpKUWqIijAMSxQrDHECJraQdsfO8VuFj6gL8ZGoae2NQEo2B7mgKk2kX5swIE8CHyez67v0MPozu70e3s09w9wZGt59I2G+T29eYeoHKNPBVoblB5RpEXmSCx17n3/cZdJ4JGWVlzKFLyQsNt2XRT7ud5uKSLqrUpq86HXSuxE69Uuqr4PBXB2D75ETylR3C4ATooS7JKGX4hPqAHjVSsZwPNw17ApdUea/gF3hgWcnblO5g2FASJ9J5hhZhwWy6EUmUdNBQuj6gBKEhU257lb0v2xLMlgiUYLArrfgTMxlV3jmRLY5Y5ejYcMNQve+aR5FVSRJayqnApA4dsX/Z64y/s3pYCaYgFhnJthTWB6xr7E7i6Lj7+zdXcH52+gK+8vVS6dj04d8VzS9n2FIMe4Cue5GiUmLS1h4ZLmMhF1sRrxiHtVNeENnpkrFlaM5WbMGbCLxlq95owbeJkXquVAYWQSNnNqqCjNTLlLtaX3JqPbruuXuyyDedD6lLu9PrJBmOUW2XRS2JWH6obn+ogwFLhLiS4LIRkCH0VSHwES6LmFHPJhpxgqECjXEIQCpLb1ZpuiNkbWQQ7imZrTeRwk5ADKjsri8REBBpLaqj4qOW5hh9
*/