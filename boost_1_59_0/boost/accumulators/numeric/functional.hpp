///////////////////////////////////////////////////////////////////////////////
/// \file functional.hpp
///
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_NUMERIC_FUNCTIONAL_HPP_EAN_08_12_2005
#define BOOST_NUMERIC_FUNCTIONAL_HPP_EAN_08_12_2005

#include <limits>
#include <functional>
#include <boost/static_assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_empty.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>
#include <boost/accumulators/numeric/functional_fwd.hpp>
#include <boost/accumulators/numeric/detail/function1.hpp>
#include <boost/accumulators/numeric/detail/function2.hpp>
#include <boost/accumulators/numeric/detail/pod_singleton.hpp>

#ifdef BOOST_NUMERIC_FUNCTIONAL_STD_VECTOR_SUPPORT
# include <boost/accumulators/numeric/functional/vector.hpp>
#endif

#ifdef BOOST_NUMERIC_FUNCTIONAL_STD_VALARRAY_SUPPORT
# include <boost/accumulators/numeric/functional/valarray.hpp>
#endif

#ifdef BOOST_NUMERIC_FUNCTIONAL_STD_COMPLEX_SUPPORT
# include <boost/accumulators/numeric/functional/complex.hpp>
#endif

/// INTERNAL ONLY
///
#define BOOST_NUMERIC_FUNCTIONAL_HPP_INCLUDED

#ifdef BOOST_NUMERIC_FUNCTIONAL_DOXYGEN_INVOKED
// Hack to make Doxygen show the inheritance relationships
/// INTERNAL ONLY
///
namespace std
{
    /// INTERNAL ONLY
    ///
    template<class Arg, class Ret> struct unary_function {};
    /// INTERNAL ONLY
    ///
    template<class Left, class Right, class Ret> struct binary_function {};
}
#endif

namespace boost { namespace numeric
{
    namespace functional
    {
        /// INTERNAL ONLY
        ///
        template<typename A0, typename A1>
        struct are_integral
          : mpl::and_<is_integral<A0>, is_integral<A1> >
        {};

        template<typename Left, typename Right>
        struct left_ref
        {
            typedef Left &type;
        };

        namespace detail
        {
            template<typename T>
            T &lvalue_of();
        }
    }

    // TODO: handle complex weight, valarray, MTL vectors

    /// INTERNAL ONLY
    ///
#define BOOST_NUMERIC_FUNCTIONAL_DEFINE_UNARY_OP(Name, Op)                                      \
    namespace functional                                                                        \
    {                                                                                           \
        template<typename Arg>                                                                  \
        struct result_of_ ## Name                                                               \
        {                                                                                       \
            BOOST_TYPEOF_NESTED_TYPEDEF_TPL(                                                    \
                nested                                                                          \
              , Op boost::numeric::functional::detail::lvalue_of<Arg>()                         \
            )                                                                                   \
            typedef typename nested::type type;                                                 \
        };                                                                                      \
        template<typename Arg, typename EnableIf>                                               \
        struct Name ## _base                                                                    \
        {                                                                                       \
            typedef typename remove_const<Arg>::type argument_type;                             \
            typedef typename result_of_ ## Name<Arg>::type result_type;                         \
            typename result_of_ ## Name<Arg>::type operator ()(Arg &arg) const                  \
            {                                                                                   \
                return Op arg;                                                                  \
            }                                                                                   \
        };                                                                                      \
        template<typename Arg, typename ArgTag>                                                 \
        struct Name                                                                             \
          : Name ## _base<Arg, void>                                                            \
        {};                                                                                     \
    }                                                                                           \
    namespace op                                                                                \
    {                                                                                           \
        struct Name                                                                             \
          : boost::detail::function1<functional::Name<_, functional::tag<_> > >                 \
        {};                                                                                     \
    }                                                                                           \
    namespace                                                                                   \
    {                                                                                           \
        op::Name const &Name = boost::detail::pod_singleton<op::Name>::instance;                \
    }                                                                                           \
    /**/

    /// INTERNAL ONLY
    ///
#define BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(Name, Op, RetType)                            \
    namespace functional                                                                        \
    {                                                                                           \
        template<typename Left, typename Right, typename EnableIf>                              \
        struct result_of_ ## Name                                                               \
        {                                                                                       \
            RetType(Left, Op, Right)                                                            \
        };                                                                                      \
        template<typename Left, typename Right, typename EnableIf>                              \
        struct Name ## _base                                                                    \
        {                                                                                       \
            typedef typename remove_const<Left>::type first_argument_type;                      \
            typedef typename remove_const<Right>::type second_argument_type;                    \
            typedef typename result_of_ ## Name<Left, Right>::type result_type;                 \
            typename result_of_ ## Name<Left, Right>::type                                      \
            operator ()(Left &left, Right &right) const                                         \
            {                                                                                   \
                return left Op right;                                                           \
            }                                                                                   \
        };                                                                                      \
        template<typename Left, typename Right, typename LeftTag, typename RightTag>            \
        struct Name                                                                             \
          : Name ## _base<Left, Right, void>                                                    \
        {};                                                                                     \
    }                                                                                           \
    namespace op                                                                                \
    {                                                                                           \
        struct Name                                                                             \
          : boost::detail::function2<                                                           \
                functional::Name<_1, _2, functional::tag<_1>, functional::tag<_2> >             \
            >                                                                                   \
        {};                                                                                     \
    }                                                                                           \
    namespace                                                                                   \
    {                                                                                           \
        op::Name const &Name = boost::detail::pod_singleton<op::Name>::instance;                \
    }                                                                                           \
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(Name)                                                      \
    /**/

    /// INTERNAL ONLY
    ///
#define BOOST_NUMERIC_FUNCTIONAL_DEDUCED(Left, Op, Right)                                       \
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL(                                                            \
        nested                                                                                  \
      , boost::numeric::functional::detail::lvalue_of<Left>() Op                                \
        boost::numeric::functional::detail::lvalue_of<Right>()                                  \
    )                                                                                           \
    typedef typename nested::type type;                                                         \
    /**/

    /// INTERNAL ONLY
    ///
#define BOOST_NUMERIC_FUNCTIONAL_LEFT(Left, Op, Right)                                          \
    typedef Left &type;                                                                         \
    /**/

    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(plus, +, BOOST_NUMERIC_FUNCTIONAL_DEDUCED)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(minus, -, BOOST_NUMERIC_FUNCTIONAL_DEDUCED)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(multiplies, *, BOOST_NUMERIC_FUNCTIONAL_DEDUCED)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(divides, /, BOOST_NUMERIC_FUNCTIONAL_DEDUCED)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(modulus, %, BOOST_NUMERIC_FUNCTIONAL_DEDUCED)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(greater, >, BOOST_NUMERIC_FUNCTIONAL_DEDUCED)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(greater_equal, >=, BOOST_NUMERIC_FUNCTIONAL_DEDUCED)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(less, <, BOOST_NUMERIC_FUNCTIONAL_DEDUCED)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(less_equal, <=, BOOST_NUMERIC_FUNCTIONAL_DEDUCED)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(equal_to, ==, BOOST_NUMERIC_FUNCTIONAL_DEDUCED)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(not_equal_to, !=, BOOST_NUMERIC_FUNCTIONAL_DEDUCED)

    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(assign, =, BOOST_NUMERIC_FUNCTIONAL_LEFT)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(plus_assign, +=, BOOST_NUMERIC_FUNCTIONAL_LEFT)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(minus_assign, -=, BOOST_NUMERIC_FUNCTIONAL_LEFT)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(multiplies_assign, *=, BOOST_NUMERIC_FUNCTIONAL_LEFT)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(divides_assign, /=, BOOST_NUMERIC_FUNCTIONAL_LEFT)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP(modulus_assign, %=, BOOST_NUMERIC_FUNCTIONAL_LEFT)

    BOOST_NUMERIC_FUNCTIONAL_DEFINE_UNARY_OP(unary_plus, +)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_UNARY_OP(unary_minus, -)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_UNARY_OP(complement, ~)
    BOOST_NUMERIC_FUNCTIONAL_DEFINE_UNARY_OP(logical_not, !)

#undef BOOST_NUMERIC_FUNCTIONAL_LEFT
#undef BOOST_NUMERIC_FUNCTIONAL_DEDUCED
#undef BOOST_NUMERIC_FUNCTIONAL_DEFINE_UNARY_OP
#undef BOOST_NUMERIC_FUNCTIONAL_DEFINE_BINARY_OP

    namespace functional
    {
        template<typename Left, typename Right, typename EnableIf>
        struct min_assign_base
        {
            typedef Left first_argument_type;
            typedef Right second_argument_type;
            typedef void result_type;

            void operator ()(Left &left, Right &right) const
            {
                if(numeric::less(right, left))
                {
                    left = right;
                }
            }
        };

        template<typename Left, typename Right, typename EnableIf>
        struct max_assign_base
        {
            typedef Left first_argument_type;
            typedef Right second_argument_type;
            typedef void result_type;

            void operator ()(Left &left, Right &right) const
            {
                if(numeric::greater(right, left))
                {
                    left = right;
                }
            }
        };

        template<typename Left, typename Right, typename EnableIf>
        struct fdiv_base
          : functional::divides<Left, Right>
        {};

        // partial specialization that promotes the arguments to double for
        // integral division.
        template<typename Left, typename Right>
        struct fdiv_base<Left, Right, typename enable_if<are_integral<Left, Right> >::type>
          : functional::divides<double const, double const>
        {};

        template<typename To, typename From, typename EnableIf>
        struct promote_base
        {
            typedef From argument_type;
            typedef To result_type;

            To operator ()(From &from) const
            {
                return from;
            }
        };

        template<typename ToFrom>
        struct promote_base<ToFrom, ToFrom, void>
        {
            typedef ToFrom argument_type;
            typedef ToFrom result_type;

            ToFrom &operator ()(ToFrom &tofrom)
            {
                return tofrom;
            }
        };

        template<typename Arg, typename EnableIf>
        struct as_min_base
        {
            BOOST_STATIC_ASSERT(std::numeric_limits<typename remove_const<Arg>::type>::is_specialized);

            typedef Arg argument_type;
            typedef typename remove_const<Arg>::type result_type;

            typename remove_const<Arg>::type operator ()(Arg &) const
            {
                return (std::numeric_limits<typename remove_const<Arg>::type>::min)();
            }
        };

        template<typename Arg>
        struct as_min_base<Arg, typename enable_if<is_floating_point<Arg> >::type>
        {
            BOOST_STATIC_ASSERT(std::numeric_limits<typename remove_const<Arg>::type>::is_specialized);

            typedef Arg argument_type;
            typedef typename remove_const<Arg>::type result_type;

            typename remove_const<Arg>::type operator ()(Arg &) const
            {
                return -(std::numeric_limits<typename remove_const<Arg>::type>::max)();
            }
        };

        template<typename Arg, typename EnableIf>
        struct as_max_base
        {
            BOOST_STATIC_ASSERT(std::numeric_limits<typename remove_const<Arg>::type>::is_specialized);

            typedef Arg argument_type;
            typedef typename remove_const<Arg>::type result_type;

            typename remove_const<Arg>::type operator ()(Arg &) const
            {
                return (std::numeric_limits<typename remove_const<Arg>::type>::max)();
            }
        };

        template<typename Arg, typename EnableIf>
        struct as_zero_base
        {
            typedef Arg argument_type;
            typedef typename remove_const<Arg>::type result_type;

            typename remove_const<Arg>::type operator ()(Arg &) const
            {
                return numeric::zero<typename remove_const<Arg>::type>::value;
            }
        };

        template<typename Arg, typename EnableIf>
        struct as_one_base
        {
            typedef Arg argument_type;
            typedef typename remove_const<Arg>::type result_type;

            typename remove_const<Arg>::type operator ()(Arg &) const
            {
                return numeric::one<typename remove_const<Arg>::type>::value;
            }
        };

        template<typename To, typename From, typename ToTag, typename FromTag>
        struct promote
          : promote_base<To, From, void>
        {};

        template<typename Left, typename Right, typename LeftTag, typename RightTag>
        struct min_assign
          : min_assign_base<Left, Right, void>
        {};

        template<typename Left, typename Right, typename LeftTag, typename RightTag>
        struct max_assign
          : max_assign_base<Left, Right, void>
        {};

        template<typename Left, typename Right, typename LeftTag, typename RightTag>
        struct fdiv
          : fdiv_base<Left, Right, void>
        {};

        /// INTERNAL ONLY 
        /// For back-compat only. Use fdiv.
        template<typename Left, typename Right, typename LeftTag, typename RightTag>
        struct average
          : fdiv<Left, Right, LeftTag, RightTag>
        {};

        template<typename Arg, typename Tag>
        struct as_min
          : as_min_base<Arg, void>
        {};

        template<typename Arg, typename Tag>
        struct as_max
          : as_max_base<Arg, void>
        {};

        template<typename Arg, typename Tag>
        struct as_zero
          : as_zero_base<Arg, void>
        {};

        template<typename Arg, typename Tag>
        struct as_one
          : as_one_base<Arg, void>
        {};
    }

    namespace op
    {
        template<typename To>
        struct promote
          : boost::detail::function1<functional::promote<To, _, typename functional::tag<To>::type, functional::tag<_> > >
        {};

        struct min_assign
          : boost::detail::function2<functional::min_assign<_1, _2, functional::tag<_1>, functional::tag<_2> > >
        {};

        struct max_assign
          : boost::detail::function2<functional::max_assign<_1, _2, functional::tag<_1>, functional::tag<_2> > >
        {};

        struct fdiv
          : boost::detail::function2<functional::fdiv<_1, _2, functional::tag<_1>, functional::tag<_2> > >
        {};

        /// INTERNAL ONLY
        struct average
          : boost::detail::function2<functional::fdiv<_1, _2, functional::tag<_1>, functional::tag<_2> > >
        {};

        struct as_min
          : boost::detail::function1<functional::as_min<_, functional::tag<_> > >
        {};

        struct as_max
          : boost::detail::function1<functional::as_max<_, functional::tag<_> > >
        {};

        struct as_zero
          : boost::detail::function1<functional::as_zero<_, functional::tag<_> > >
        {};

        struct as_one
          : boost::detail::function1<functional::as_one<_, functional::tag<_> > >
        {};
    }

    namespace
    {
        op::min_assign const &min_assign = boost::detail::pod_singleton<op::min_assign>::instance;
        op::max_assign const &max_assign = boost::detail::pod_singleton<op::max_assign>::instance;
        op::fdiv const &fdiv = boost::detail::pod_singleton<op::fdiv>::instance;
        op::fdiv const &average = boost::detail::pod_singleton<op::fdiv>::instance; ///< INTERNAL ONLY
        op::as_min const &as_min = boost::detail::pod_singleton<op::as_min>::instance;
        op::as_max const &as_max = boost::detail::pod_singleton<op::as_max>::instance;
        op::as_zero const &as_zero = boost::detail::pod_singleton<op::as_zero>::instance;
        op::as_one const &as_one = boost::detail::pod_singleton<op::as_one>::instance;

        BOOST_ACCUMULATORS_IGNORE_GLOBAL(min_assign)
        BOOST_ACCUMULATORS_IGNORE_GLOBAL(max_assign)
        BOOST_ACCUMULATORS_IGNORE_GLOBAL(fdiv)
        BOOST_ACCUMULATORS_IGNORE_GLOBAL(average)
        BOOST_ACCUMULATORS_IGNORE_GLOBAL(as_min)
        BOOST_ACCUMULATORS_IGNORE_GLOBAL(as_max)
        BOOST_ACCUMULATORS_IGNORE_GLOBAL(as_zero)
        BOOST_ACCUMULATORS_IGNORE_GLOBAL(as_one)
    }

    ///////////////////////////////////////////////////////////////////////////////
    // promote
    template<typename To, typename From>
    typename lazy_disable_if<is_const<From>, mpl::if_<is_same<To, From>, To &, To> >::type
    promote(From &from)
    {
        return functional::promote<To, From>()(from);
    }

    template<typename To, typename From>
    typename mpl::if_<is_same<To const, From const>, To const &, To const>::type
    promote(From const &from)
    {
        return functional::promote<To const, From const>()(from);
    }

    template<typename T>
    struct default_
    {
        typedef default_ type;
        typedef T value_type;
        static T const value;

        operator T const & () const
        {
            return default_::value;
        }
    };

    template<typename T>
    T const default_<T>::value = T();

    template<typename T>
    struct one
    {
        typedef one type;
        typedef T value_type;
        static T const value;

        operator T const & () const
        {
            return one::value;
        }
    };

    template<typename T>
    T const one<T>::value = T(1);

    template<typename T>
    struct zero
    {
        typedef zero type;
        typedef T value_type;
        static T const value;

        operator T const & () const
        {
            return zero::value;
        }
    };

    template<typename T>
    T const zero<T>::value = T();

    template<typename T>
    struct one_or_default
      : mpl::if_<is_empty<T>, default_<T>, one<T> >::type
    {};

    template<typename T>
    struct zero_or_default
      : mpl::if_<is_empty<T>, default_<T>, zero<T> >::type
    {};

}} // namespace boost::numeric

#endif

/* functional.hpp
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
*/