
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_COMPONENTS_AS_MPL_SEQUENCE_HPP_INCLUDED
#define BOOST_FT_DETAIL_COMPONENTS_AS_MPL_SEQUENCE_HPP_INCLUDED

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/pop_back_fwd.hpp>

namespace boost { namespace mpl {

template<> struct size_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S > struct apply
    : mpl::size <typename S::types>
  { };
};
template<> struct empty_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S > struct apply
    : mpl::empty <typename S::types>
  { };
};
template<> struct front_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S > struct apply
    : mpl::front <typename S::types>
  { };
};
template<> struct back_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S > struct apply
    : mpl::back <typename S::types>
  { };
};
template<> struct at_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S, typename N > struct apply
    : mpl::at <typename S::types, N >
  { };
};
template<> struct begin_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S > struct apply
    : mpl::begin <typename S::types>
  { };
};
template<> struct end_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S > struct apply
    : mpl::end <typename S::types>
  { };
};
template<> struct clear_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S >
  struct apply
    : S
  {
    typedef apply type;
    typedef typename mpl::clear< typename S::types >::type types;
  };
};
template<>
struct push_front_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S, typename T >
  struct apply
    : S
  { 
    typedef apply type;
    typedef typename mpl::push_front< typename S::types, T >::type types;
  };
};
template<>
struct pop_front_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S >
  struct apply
    : S
  {
    typedef apply type;
    typedef typename mpl::pop_front< typename S::types >::type types; 
  };
};
template<>
struct push_back_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S, typename T >
  struct apply
    : S
  {
    typedef apply type;
    typedef typename mpl::push_back< typename S::types, T >::type types; 
  };
};
template<>
struct pop_back_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S >
  struct apply
    : S
  {
    typedef apply type;
    typedef typename mpl::pop_back< typename S::types >::type types; 
  };
};

} } // namespace ::boost::mpl

#endif


/* components_as_mpl_sequence.hpp
cCHrLW9wkZePIOM5Gb7MYCOUSJXgaer1KCQiB4bLXkP+lnBcQ1INJd1fhknfYQcSljK4UnAGPLe3ALcpD+RqqOEQnAjlbOO4wbdXaJPTDNj4SaD7vLPvHvuZEM8YPZboKYqSE6aA4m0ecvtEjNdPcoNi+geM6loCOIofgysbjsI6PRu0md8KvmbLgeLheFgjgcMFRns4WHEQNRHfBd722ee8RieQXvh1/PUpH1T26TPIuuqib+ZtOO7JCWHORGgHw1MIpmGG7b3GUBClDGSt6VCpLYqfnd4F7drDSKCrG96djkY5/FuQepYrlAMv8i20QIo9ctBHpoftySWFbIE+jIpTCYksW45O1tJBdOkg3qkoAiPi6Vj7cX4Ij92Eh/bzos3SHGhn7CQym/299pssR0iy5MY8b3SC58lHuPt7DpCtfIbfLMpAaTcHQGqKEu1QNwb0ORP1bD+ErJUl0bgQGybiOgLPC6XxiYNFwHGrA1XKiyD6kECwrORCNyRuAYfUIHoxZQMrB69BtMYh7PhhMxTDswxD09eAhHoEP8kqCE0V3PiksxiqdlTBq20UEZ3iJEbfeA1yTHNAdsoeuGySkQyXIoCeFH7gdAyqVujGxnm2AF/jKIr1u4Ve8n9DjKaJYPztFbbbeTMizd+Fthc0gk/pF+z1a1MIXPkAv1xzGzUVUOFJb6+AGpcOYvMIQVG3+rANTySh/aYveiO4A1W58OOJ12iRqNQo3jRSC7fe7IBc9nOokqoMtyAyRJFDnDgf4wq09vYlcJsUAPn2eHR+JQ26eaEPS2MkgZXqt7GNd3tAOIoPv3N2B3pVR4PFhqbAjGs2Htv7DsborcG2uAINOGzGVXJG0WBpH9J4sQZuWftj/s1mICh2F2u7won0iA4i8cRIMLqJEL96PeBKStiE72VoUgjHfDqUwFyuHqcWew2uL6LxxilvEKfJQ+WJF5Dom4dY2uuN6AszI6ZQJQ2/EkIII1giQhWOEEIAMIMQQvBbv/Vbv/Vbv/Vbv/Vbv/Vbv/Vbv/Vbv/Vbv/Vbv/Vbv/Vb//cSFNSf/bN3MLNzdrYR2Cy4WVDYXN/UydPBxV7fzHT2T8TQ1tXGRdD039/O3vTPmwEGAIkYgI8UBGAAwCI+Z59LzFmzHXP2ouCcvaYyZ3coz9khizkbu3POapjN2TjmOXuCgcDXzVlV3n/aP2vfwbl6TZl/2p9LQXKOqxAs+XqCX8JzloNzzuoR+MrNc7aIMJ6dhPFs55qzT6jnbADNnL1KsLTUf+3HXYM5/oJqYTulDXNl9v1zNkZ/6X40/hW//73+Rh442zrYLEgERXmAvbNbaGmpsirKsxrbWNg7HXWxtIUllIT96/NdE1Y8/xrHFMEaWVD/y6aZzdkaS4J1JNQfnbNgPWdZneZsgO2cLSDY9wQb4EBoN7+9HYETbIH9nDWa4z/i60Codyb040Tox5n6fxL3X8bZ0NjWzMXyTwtOUV5BS1ZAw9jpn9jMyXm+novf2cHpqJskxR/KriazxV9ofT7X3PjYFuYTOcGmNXEv4BgAUAFAms3cfC2DhaKaty6zfKn9EeqjuRfuj5hgWb/zpf3h/M4X+kNlO1dPBAu1kmB5/7Xdn/2UIdS/MIJ/2exlS49Hg9COhXCcyvlJOyNCu4I9c+2u/KSdA6GdRtSPfCKHH6pZNJ40W56/lXc+v4ifhsXcfDexEjgG8Mf3yAGE7Y2iqBfE18Fu6fgy/Nhu4f5+Et8EDACWyrNFcUv8SbsCQjuHqKXXIav9ory0/+u41bjw/GU8HhJ4wKJ4pNn/df4//En+UxHW226mpeeHdRHHFvVbdpN77nxItSj/Hf56frp/4o+eOddf5ss=
*/