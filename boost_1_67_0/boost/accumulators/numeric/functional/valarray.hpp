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