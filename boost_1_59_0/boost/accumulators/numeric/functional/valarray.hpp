///////////////////////////////////////////////////////////////////////////////
/// \file valarray.hpp
///
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_NUMERIC_FUNCTIONAL_VALARRAY_HPP_EAN_12_12_2005
#define BOOST_NUMERIC_FUNCTIONAL_VALARRAY_HPP_EAN_12_12_2005

#ifdef BOOST_NUMERIC_FUNCTIONAL_HPP_INCLUDED
# error Include this file before boost/accumulators/numeric/functional.hpp
#endif

#include <valarray>
#include <functional>
#include <boost/assert.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/typeof/std/valarray.hpp>
#include <boost/accumulators/numeric/functional_fwd.hpp>

namespace boost { namespace numeric
{
    namespace operators
    {
        namespace acc_detail
        {
            template<typename Fun>
            struct make_valarray
            {
                typedef std::valarray<typename Fun::result_type> type;
            };
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Handle valarray<Left> / Right where Right is a scalar and Right != Left.
        template<typename Left, typename Right>
        typename lazy_enable_if<
            mpl::and_<is_scalar<Right>, mpl::not_<is_same<Left, Right> > >
          , acc_detail::make_valarray<functional::divides<Left, Right> >
        >::type
        operator /(std::valarray<Left> const &left, Right const &right)
        {
            typedef typename functional::divides<Left, Right>::result_type value_type;
            std::valarray<value_type> result(left.size());
            for(std::size_t i = 0, size = result.size(); i != size; ++i)
            {
                result[i] = numeric::divides(left[i], right);
            }
            return result;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Handle valarray<Left> * Right where Right is a scalar and Right != Left.
        template<typename Left, typename Right>
        typename lazy_enable_if<
            mpl::and_<is_scalar<Right>, mpl::not_<is_same<Left, Right> > >
          , acc_detail::make_valarray<functional::multiplies<Left, Right> >
        >::type
        operator *(std::valarray<Left> const &left, Right const &right)
        {
            typedef typename functional::multiplies<Left, Right>::result_type value_type;
            std::valarray<value_type> result(left.size());
            for(std::size_t i = 0, size = result.size(); i != size; ++i)
            {
                result[i] = numeric::multiplies(left[i], right);
            }
            return result;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Handle valarray<Left> + valarray<Right> where Right != Left.
        template<typename Left, typename Right>
        typename lazy_disable_if<
            is_same<Left, Right>
          , acc_detail::make_valarray<functional::plus<Left, Right> >
        >::type
        operator +(std::valarray<Left> const &left, std::valarray<Right> const &right)
        {
            typedef typename functional::plus<Left, Right>::result_type value_type;
            std::valarray<value_type> result(left.size());
            for(std::size_t i = 0, size = result.size(); i != size; ++i)
            {
                result[i] = numeric::plus(left[i], right[i]);
            }
            return result;
        }
    }

    namespace functional
    {
        struct std_valarray_tag;

        template<typename T>
        struct tag<std::valarray<T> >
        {
            typedef std_valarray_tag type;
        };

    #ifdef __GLIBCXX__
        template<typename T, typename U>
        struct tag<std::_Expr<T, U> >
        {
            typedef std_valarray_tag type;
        };
    #endif

        /// INTERNAL ONLY
        ///
        // This is necessary because the GCC stdlib uses expression templates, and
        // typeof(som-valarray-expression) is not an instance of std::valarray
    #define BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(Name, Op)                   \
        template<typename Left, typename Right>                                         \
        struct Name<Left, Right, std_valarray_tag, std_valarray_tag>                    \
        {                                                                               \
            typedef Left first_argument_type;                                           \
            typedef Right second_argument_type;                                         \
            typedef typename Left::value_type left_value_type;                          \
            typedef typename Right::value_type right_value_type;                        \
            typedef                                                                     \
                std::valarray<                                                          \
                    typename Name<left_value_type, right_value_type>::result_type       \
                >                                                                       \
            result_type;                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return numeric::promote<std::valarray<left_value_type> >(left)          \
                    Op numeric::promote<std::valarray<right_value_type> >(right);       \
            }                                                                           \
        };                                                                              \
        template<typename Left, typename Right>                                         \
        struct Name<Left, Right, std_valarray_tag, void>                                \
        {                                                                               \
            typedef Left first_argument_type;                                           \
            typedef Right second_argument_type;                                         \
            typedef typename Left::value_type left_value_type;                          \
            typedef                                                                     \
                std::valarray<                                                          \
                    typename Name<left_value_type, Right>::result_type                  \
                >                                                                       \
            result_type;                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return numeric::promote<std::valarray<left_value_type> >(left) Op right;\
            }                                                                           \
        };                                                                              \
        template<typename Left, typename Right>                                         \
        struct Name<Left, Right, void, std_valarray_tag>                                \
        {                                                                               \
            typedef Left first_argument_type;                                           \
            typedef Right second_argument_type;                                         \
            typedef typename Right::value_type right_value_type;                        \
            typedef                                                                     \
                std::valarray<                                                          \
                    typename Name<Left, right_value_type>::result_type                  \
                >                                                                       \
            result_type;                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return left Op numeric::promote<std::valarray<right_value_type> >(right);\
            }                                                                           \
        };

        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(plus, +)
        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(minus, -)
        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(multiplies, *)
        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(divides, /)
        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(modulus, %)

    #undef BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP

        ///////////////////////////////////////////////////////////////////////////////
        // element-wise min of std::valarray
        template<typename Left, typename Right>
        struct min_assign<Left, Right, std_valarray_tag, std_valarray_tag>
        {
            typedef Left first_argument_type;
            typedef Right second_argument_type;
            typedef void result_type;

            void operator ()(Left &left, Right &right) const
            {
                BOOST_ASSERT(left.size() == right.size());
                for(std::size_t i = 0, size = left.size(); i != size; ++i)
                {
                    if(numeric::less(right[i], left[i]))
                    {
                        left[i] = right[i];
                    }
                }
            }
        };

        ///////////////////////////////////////////////////////////////////////////////
        // element-wise max of std::valarray
        template<typename Left, typename Right>
        struct max_assign<Left, Right, std_valarray_tag, std_valarray_tag>
        {
            typedef Left first_argument_type;
            typedef Right second_argument_type;
            typedef void result_type;

            void operator ()(Left &left, Right &right) const
            {
                BOOST_ASSERT(left.size() == right.size());
                for(std::size_t i = 0, size = left.size(); i != size; ++i)
                {
                    if(numeric::greater(right[i], left[i]))
                    {
                        left[i] = right[i];
                    }
                }
            }
        };

        // partial specialization of numeric::fdiv<> for std::valarray.
        template<typename Left, typename Right, typename RightTag>
        struct fdiv<Left, Right, std_valarray_tag, RightTag>
          : mpl::if_<
                are_integral<typename Left::value_type, Right>
              , divides<Left, double const>
              , divides<Left, Right>
            >::type
        {};

        // promote
        template<typename To, typename From>
        struct promote<To, From, std_valarray_tag, std_valarray_tag>
        {
            typedef From argument_type;
            typedef To result_type;

            To operator ()(From &arr) const
            {
                typename remove_const<To>::type res(arr.size());
                for(std::size_t i = 0, size = arr.size(); i != size; ++i)
                {
                    res[i] = numeric::promote<typename To::value_type>(arr[i]);
                }
                return res;
            }
        };

        template<typename ToFrom>
        struct promote<ToFrom, ToFrom, std_valarray_tag, std_valarray_tag>
        {
            typedef ToFrom argument_type;
            typedef ToFrom result_type;

            ToFrom &operator ()(ToFrom &tofrom) const
            {
                return tofrom;
            }
        };

        // for "promoting" a std::valarray<bool> to a bool, useful for
        // comparing 2 valarrays for equality:
        //   if(numeric::promote<bool>(a == b))
        template<typename From>
        struct promote<bool, From, void, std_valarray_tag>
        {
            typedef From argument_type;
            typedef bool result_type;

            bool operator ()(From &arr) const
            {
                BOOST_MPL_ASSERT((is_same<bool, typename From::value_type>));
                for(std::size_t i = 0, size = arr.size(); i != size; ++i)
                {
                    if(!arr[i])
                    {
                        return false;
                    }
                }
                return true;
            }
        };

        template<typename From>
        struct promote<bool const, From, void, std_valarray_tag>
          : promote<bool, From, void, std_valarray_tag>
        {};

        ///////////////////////////////////////////////////////////////////////////////
        // functional::as_min
        template<typename T>
        struct as_min<T, std_valarray_tag>
        {
            typedef T argument_type;
            typedef typename remove_const<T>::type result_type;

            typename remove_const<T>::type operator ()(T &arr) const
            {
                return 0 == arr.size()
                  ? T()
                  : T(numeric::as_min(arr[0]), arr.size());
            }
        };

        ///////////////////////////////////////////////////////////////////////////////
        // functional::as_max
        template<typename T>
        struct as_max<T, std_valarray_tag>
        {
            typedef T argument_type;
            typedef typename remove_const<T>::type result_type;

            typename remove_const<T>::type operator ()(T &arr) const
            {
                return 0 == arr.size()
                  ? T()
                  : T(numeric::as_max(arr[0]), arr.size());
            }
        };

        ///////////////////////////////////////////////////////////////////////////////
        // functional::as_zero
        template<typename T>
        struct as_zero<T, std_valarray_tag>
        {
            typedef T argument_type;
            typedef typename remove_const<T>::type result_type;

            typename remove_const<T>::type operator ()(T &arr) const
            {
                return 0 == arr.size()
                  ? T()
                  : T(numeric::as_zero(arr[0]), arr.size());
            }
        };

        ///////////////////////////////////////////////////////////////////////////////
        // functional::as_one
        template<typename T>
        struct as_one<T, std_valarray_tag>
        {
            typedef T argument_type;
            typedef typename remove_const<T>::type result_type;

            typename remove_const<T>::type operator ()(T &arr) const
            {
                return 0 == arr.size()
                  ? T()
                  : T(numeric::as_one(arr[0]), arr.size());
            }
        };

    } // namespace functional

}} // namespace boost::numeric

#endif


/* valarray.hpp
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
*/