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