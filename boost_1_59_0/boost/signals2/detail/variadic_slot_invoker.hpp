/*
  Helper class used by variadic implementation of variadic boost::signals2::signal.

  Author: Frank Mori Hess <fmhess@users.sourceforge.net>
  Begin: 2009-05-27
*/
// Copyright Frank Mori Hess 2009
// Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_SIGNALS2_DETAIL_VARIADIC_SLOT_INVOKER_HPP
#define BOOST_SIGNALS2_DETAIL_VARIADIC_SLOT_INVOKER_HPP

#include <boost/mpl/size_t.hpp>
#include <boost/signals2/detail/variadic_arg_type.hpp>

// if compiler has std::tuple use it instead of boost::tuple
// because boost::tuple does not have variadic template support at present.
#ifdef BOOST_NO_CXX11_HDR_TUPLE
#include <boost/tuple/tuple.hpp>
#define BOOST_SIGNALS2_TUPLE boost::tuple
#define BOOST_SIGNALS2_GET boost::get
#else
#include <tuple>
#define BOOST_SIGNALS2_TUPLE std::tuple
#define BOOST_SIGNALS2_GET std::get
#endif

// vc12 seems to erroneously report formal parameters as unreferenced (warning C4100)
// if parameters of variadic template functions are only referenced by calling
// other varadic template functions. silence these warnings:
#if defined(BOOST_MSVC)
#pragma warning(push)
#if  BOOST_MSVC >= 1800
#pragma warning(disable:4100)
#endif
#endif

namespace boost
{
  namespace signals2
  {
    namespace detail
    {
      template<unsigned ... values> class unsigned_meta_array {};

      template<typename UnsignedMetaArray, unsigned n> class unsigned_meta_array_appender;

      template<unsigned n, unsigned ... Args>
        class unsigned_meta_array_appender<unsigned_meta_array<Args...>, n>
      {
      public:
        typedef unsigned_meta_array<Args..., n> type;
      };

      template<unsigned n> class make_unsigned_meta_array;

      template<> class make_unsigned_meta_array<0>
      {
      public:
        typedef unsigned_meta_array<> type;
      };

      template<> class make_unsigned_meta_array<1>
      {
      public:
        typedef unsigned_meta_array<0> type;
      };

      template<unsigned n> class make_unsigned_meta_array
      {
      public:
        typedef typename unsigned_meta_array_appender<typename make_unsigned_meta_array<n-1>::type, n - 1>::type type;
      };

      template<typename R>
        class call_with_tuple_args
      {
      public:
        typedef R result_type;

        template<typename Func, typename ... Args, std::size_t N>
        R operator()(Func &func, const BOOST_SIGNALS2_TUPLE<Args...> & args, mpl::size_t<N>) const
        {
          typedef typename make_unsigned_meta_array<N>::type indices_type;
          return m_invoke<Func>(func, indices_type(), args);
        }
      private:
        template<typename Func, unsigned ... indices, typename ... Args>
          R m_invoke(Func &func, unsigned_meta_array<indices...>, const BOOST_SIGNALS2_TUPLE<Args...> & args,
            typename boost::disable_if<boost::is_void<typename Func::result_type> >::type * = 0
          ) const
        {
          return func(BOOST_SIGNALS2_GET<indices>(args)...);
        }
        template<typename Func, unsigned ... indices, typename ... Args>
          R m_invoke(Func &func, unsigned_meta_array<indices...>, const BOOST_SIGNALS2_TUPLE<Args...> & args,
            typename boost::enable_if<boost::is_void<typename Func::result_type> >::type * = 0
          ) const
        {
          func(BOOST_SIGNALS2_GET<indices>(args)...);
          return R();
        }
        // This overload is redundant, as it is the same as the previous variadic method when
        // it has zero "indices" or "Args" variadic template parameters.  This overload
        // only exists to quiet some unused parameter warnings
        // on certain compilers (some versions of gcc and msvc)
        template<typename Func>
          R m_invoke(Func &func, unsigned_meta_array<>, const BOOST_SIGNALS2_TUPLE<> &, 
            typename boost::enable_if<boost::is_void<typename Func::result_type> >::type * = 0
          ) const
        {
          func();
          return R();
        }
      };

      template<typename R, typename ... Args>
        class variadic_slot_invoker
      {
      public:
        typedef R result_type;

        variadic_slot_invoker(Args & ... args): _args(args...)
        {}
        template<typename ConnectionBodyType>
          result_type operator ()(const ConnectionBodyType &connectionBody) const
        {
          return call_with_tuple_args<result_type>()(connectionBody->slot().slot_function(), 
            _args, mpl::size_t<sizeof...(Args)>());
        }
      private:
        BOOST_SIGNALS2_TUPLE<Args& ...> _args;
      };
    } // namespace detail
  } // namespace signals2
} // namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif


#endif // BOOST_SIGNALS2_DETAIL_VARIADIC_SLOT_INVOKER_HPP

/* variadic_slot_invoker.hpp
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
*/