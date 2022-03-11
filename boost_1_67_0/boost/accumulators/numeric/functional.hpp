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