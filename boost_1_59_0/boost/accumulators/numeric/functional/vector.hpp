///////////////////////////////////////////////////////////////////////////////
/// \file vector.hpp
///
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_NUMERIC_FUNCTIONAL_VECTOR_HPP_EAN_12_12_2005
#define BOOST_NUMERIC_FUNCTIONAL_VECTOR_HPP_EAN_12_12_2005

#ifdef BOOST_NUMERIC_FUNCTIONAL_HPP_INCLUDED
# error Include this file before boost/accumulators/numeric/functional.hpp
#endif

#include <vector>
#include <functional>
#include <boost/assert.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/typeof/std/vector.hpp>
#include <boost/accumulators/numeric/functional_fwd.hpp>

namespace boost { namespace numeric
{
    namespace operators
    {
        namespace acc_detail
        {
            template<typename Fun>
            struct make_vector
            {
                typedef std::vector<typename Fun::result_type> type;
            };
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Handle vector<Left> / Right where Right is a scalar.
        template<typename Left, typename Right>
        typename lazy_enable_if<
            is_scalar<Right>
          , acc_detail::make_vector<functional::divides<Left, Right> >
        >::type
        operator /(std::vector<Left> const &left, Right const &right)
        {
            typedef typename functional::divides<Left, Right>::result_type value_type;
            std::vector<value_type> result(left.size());
            for(std::size_t i = 0, size = result.size(); i != size; ++i)
            {
                result[i] = numeric::divides(left[i], right);
            }
            return result;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Handle vector<Left> / vector<Right>.
        template<typename Left, typename Right>
        std::vector<typename functional::divides<Left, Right>::result_type>
        operator /(std::vector<Left> const &left, std::vector<Right> const &right)
        {
            typedef typename functional::divides<Left, Right>::result_type value_type;
            std::vector<value_type> result(left.size());
            for(std::size_t i = 0, size = result.size(); i != size; ++i)
            {
                result[i] = numeric::divides(left[i], right[i]);
            }
            return result;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Handle vector<Left> * Right where Right is a scalar.
        template<typename Left, typename Right>
        typename lazy_enable_if<
            is_scalar<Right>
          , acc_detail::make_vector<functional::multiplies<Left, Right> >
        >::type
        operator *(std::vector<Left> const &left, Right const &right)
        {
            typedef typename functional::multiplies<Left, Right>::result_type value_type;
            std::vector<value_type> result(left.size());
            for(std::size_t i = 0, size = result.size(); i != size; ++i)
            {
                result[i] = numeric::multiplies(left[i], right);
            }
            return result;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Handle Left * vector<Right> where Left is a scalar.
        template<typename Left, typename Right>
        typename lazy_enable_if<
            is_scalar<Left>
          , acc_detail::make_vector<functional::multiplies<Left, Right> >
        >::type
        operator *(Left const &left, std::vector<Right> const &right)
        {
            typedef typename functional::multiplies<Left, Right>::result_type value_type;
            std::vector<value_type> result(right.size());
            for(std::size_t i = 0, size = result.size(); i != size; ++i)
            {
                result[i] = numeric::multiplies(left, right[i]);
            }
            return result;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Handle vector<Left> * vector<Right>
        template<typename Left, typename Right>
        std::vector<typename functional::multiplies<Left, Right>::result_type>
        operator *(std::vector<Left> const &left, std::vector<Right> const &right)
        {
            typedef typename functional::multiplies<Left, Right>::result_type value_type;
            std::vector<value_type> result(left.size());
            for(std::size_t i = 0, size = result.size(); i != size; ++i)
            {
                result[i] = numeric::multiplies(left[i], right[i]);
            }
            return result;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Handle vector<Left> + vector<Right>
        template<typename Left, typename Right>
        std::vector<typename functional::plus<Left, Right>::result_type>
        operator +(std::vector<Left> const &left, std::vector<Right> const &right)
        {
            typedef typename functional::plus<Left, Right>::result_type value_type;
            std::vector<value_type> result(left.size());
            for(std::size_t i = 0, size = result.size(); i != size; ++i)
            {
                result[i] = numeric::plus(left[i], right[i]);
            }
            return result;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Handle vector<Left> - vector<Right>
        template<typename Left, typename Right>
        std::vector<typename functional::minus<Left, Right>::result_type>
        operator -(std::vector<Left> const &left, std::vector<Right> const &right)
        {
            typedef typename functional::minus<Left, Right>::result_type value_type;
            std::vector<value_type> result(left.size());
            for(std::size_t i = 0, size = result.size(); i != size; ++i)
            {
                result[i] = numeric::minus(left[i], right[i]);
            }
            return result;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Handle vector<Left> += vector<Left>
        template<typename Left>
        std::vector<Left> &
        operator +=(std::vector<Left> &left, std::vector<Left> const &right)
        {
            BOOST_ASSERT(left.size() == right.size());
            for(std::size_t i = 0, size = left.size(); i != size; ++i)
            {
                numeric::plus_assign(left[i], right[i]);
            }
            return left;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Handle -vector<Arg>
        template<typename Arg>
        std::vector<typename functional::unary_minus<Arg>::result_type>
        operator -(std::vector<Arg> const &arg)
        {
            typedef typename functional::unary_minus<Arg>::result_type value_type;
            std::vector<value_type> result(arg.size());
            for(std::size_t i = 0, size = result.size(); i != size; ++i)
            {
                result[i] = numeric::unary_minus(arg[i]);
            }
            return result;
        }
    }

    namespace functional
    {
        struct std_vector_tag;

        template<typename T, typename Al>
        struct tag<std::vector<T, Al> >
        {
            typedef std_vector_tag type;
        };

        ///////////////////////////////////////////////////////////////////////////////
        // element-wise min of std::vector
        template<typename Left, typename Right>
        struct min_assign<Left, Right, std_vector_tag, std_vector_tag>
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
        // element-wise max of std::vector
        template<typename Left, typename Right>
        struct max_assign<Left, Right, std_vector_tag, std_vector_tag>
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

        // partial specialization for std::vector.
        template<typename Left, typename Right>
        struct fdiv<Left, Right, std_vector_tag, void>
          : mpl::if_<
                are_integral<typename Left::value_type, Right>
              , divides<Left, double const>
              , divides<Left, Right>
            >::type
        {};

        // promote
        template<typename To, typename From>
        struct promote<To, From, std_vector_tag, std_vector_tag>
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
        struct promote<ToFrom, ToFrom, std_vector_tag, std_vector_tag>
        {
            typedef ToFrom argument_type;
            typedef ToFrom result_type;

            ToFrom &operator ()(ToFrom &tofrom) const
            {
                return tofrom;
            }
        };

        ///////////////////////////////////////////////////////////////////////////////
        // functional::as_min
        template<typename T>
        struct as_min<T, std_vector_tag>
        {
            typedef T argument_type;
            typedef typename remove_const<T>::type result_type;

            typename remove_const<T>::type operator ()(T &arr) const
            {
                return 0 == arr.size()
                  ? T()
                  : T(arr.size(), numeric::as_min(arr[0]));
            }
        };

        ///////////////////////////////////////////////////////////////////////////////
        // functional::as_max
        template<typename T>
        struct as_max<T, std_vector_tag>
        {
            typedef T argument_type;
            typedef typename remove_const<T>::type result_type;

            typename remove_const<T>::type operator ()(T &arr) const
            {
                return 0 == arr.size()
                  ? T()
                  : T(arr.size(), numeric::as_max(arr[0]));
            }
        };

        ///////////////////////////////////////////////////////////////////////////////
        // functional::as_zero
        template<typename T>
        struct as_zero<T, std_vector_tag>
        {
            typedef T argument_type;
            typedef typename remove_const<T>::type result_type;

            typename remove_const<T>::type operator ()(T &arr) const
            {
                return 0 == arr.size()
                  ? T()
                  : T(arr.size(), numeric::as_zero(arr[0]));
            }
        };

        ///////////////////////////////////////////////////////////////////////////////
        // functional::as_one
        template<typename T>
        struct as_one<T, std_vector_tag>
        {
            typedef T argument_type;
            typedef typename remove_const<T>::type result_type;

            typename remove_const<T>::type operator ()(T &arr) const
            {
                return 0 == arr.size()
                  ? T()
                  : T(arr.size(), numeric::as_one(arr[0]));
            }
        };

    } // namespace functional

}} // namespace boost::numeric

#endif


/* vector.hpp
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
*/