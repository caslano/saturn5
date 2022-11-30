///////////////////////////////////////////////////////////////
//  Copyright Jens Maurer 2000-2021
//  Copyright Steven Watanabe 2011-2021
//  Copyright John Maddock 2015-2021
//  Copyright Matt Borland 2021
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  https://www.boost.org/LICENSE_1_0.txt
//
//  This is a C++11 compliant port of Boost.Random's implementation
//  of uniform_int_distribution. See their comments for detailed
//  descriptions

#ifndef BOOST_MP_UNIFORM_INT_DISTRIBUTION_HPP
#define BOOST_MP_UNIFORM_INT_DISTRIBUTION_HPP

#include <limits>
#include <type_traits>
#include <boost/multiprecision/detail/standalone_config.hpp>
#include <boost/multiprecision/detail/assert.hpp>
#include <boost/multiprecision/traits/std_integer_traits.hpp>

namespace boost { namespace multiprecision { 
    
namespace detail {

template <typename T, bool intrinsic>
struct make_unsigned_impl
{
    using type = typename boost::multiprecision::detail::make_unsigned<T>::type;
};

template <typename T>
struct make_unsigned_impl<T, false>
{
    using type = T;
};

template <typename T>
struct make_unsigned_mp
{
    using type = typename make_unsigned_impl<T, boost::multiprecision::detail::is_integral<T>::value>::type;
};

template <typename Engine, typename T>
T generate_uniform_int (Engine& eng, T min_value, T max_value)
{
    using range_type = typename boost::multiprecision::detail::make_unsigned_mp<T>::type;
    using base_result = typename Engine::result_type;
    using base_unsigned = typename boost::multiprecision::detail::make_unsigned_mp<base_result>::type;

    const range_type range = max_value - min_value;
    const base_result bmin = (eng.min)();
    const base_unsigned brange = (eng.max)() - (eng.min)();

    if(range == 0)
    {
        return min_value;
    }
    else if (brange < range)
    {
        for(;;)
        {
            range_type limit;
            if(range == (std::numeric_limits<range_type>::max)())
            {
                limit = range / (range_type(brange) + 1);
                if(range % (range_type(brange) + 1) == range_type(brange))
                {
                    ++limit;
                }
            }
            else
            {
                limit = (range + 1) / (range_type(brange) + 1);
            }

            range_type result = 0;
            range_type mult = 1;

            while (mult <= limit)
            {
                result += static_cast<range_type>(static_cast<range_type>(eng() - bmin) * mult);

                if(mult * range_type(brange) == range - mult + 1)
                {
                    return(result);
                }

                mult *= range_type(brange)+range_type(1);
            }

            range_type result_increment = generate_uniform_int(eng, range_type(0), range_type(range/mult));

            if(std::numeric_limits<range_type>::is_bounded && ((std::numeric_limits<range_type>::max)() / mult < result_increment))
            {
                continue;
            }

            result_increment *= mult;
            result += result_increment;

            if(result < result_increment)
            {
                continue;
            }
            if(result > range)
            {
                continue;
            }

            return result + min_value;
        }
    }
    else
    {
        using mixed_range_type = 
        typename std::conditional<std::numeric_limits<range_type>::is_specialized && std::numeric_limits<base_unsigned>::is_specialized &&
                                  (std::numeric_limits<range_type>::digits >= std::numeric_limits<base_unsigned>::digits),
                                  range_type, base_unsigned>::type;

        mixed_range_type bucket_size;

        if(brange == (std::numeric_limits<base_unsigned>::max)()) 
        {
            bucket_size = static_cast<mixed_range_type>(brange) / (static_cast<mixed_range_type>(range)+1);
            if(static_cast<mixed_range_type>(brange) % (static_cast<mixed_range_type>(range)+1) == static_cast<mixed_range_type>(range)) 
            {
                ++bucket_size;
            }
        } 
        else 
        {
            bucket_size = static_cast<mixed_range_type>(brange + 1) / (static_cast<mixed_range_type>(range)+1);
        }

        for(;;) 
        {
            mixed_range_type result = eng() - bmin;
            result /= bucket_size;

            if(result <= static_cast<mixed_range_type>(range))
            {
                return result + min_value;
            }
        }
    }
}

} // Namespace detail

template <typename Integer = int>
class uniform_int_distribution
{
private:
    Integer min_;
    Integer max_;

public:
    class param_type
    {
    private:
        Integer min_;
        Integer max_;
    
    public:
        explicit param_type(Integer min_val, Integer max_val) : min_ {min_val}, max_ {max_val}
        {
            BOOST_MP_ASSERT(min_ <= max_);
        }

        Integer a() const { return min_; }
        Integer b() const { return max_; }
    };

    explicit uniform_int_distribution(Integer min_arg, Integer max_arg) : min_ {min_arg}, max_ {max_arg}
    {
        BOOST_MP_ASSERT(min_ <= max_);
    }

    explicit uniform_int_distribution(const param_type& param_arg) : min_ {param_arg.a()}, max_ {param_arg.b()} {}

    Integer min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return min_; }
    Integer max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return max_; }
    
    Integer a() const { return min_; }
    Integer b() const { return max_; }

    param_type param() const { return param_type(min_, max_); }

    void param(const param_type& param_arg)
    {
        min_ = param_arg.a();
        max_ = param_arg.b();
    }

    template <typename Engine>
    Integer operator() (Engine& eng) const
    {
        return detail::generate_uniform_int(eng, min_, max_);
    }

    template <typename Engine>
    Integer operator() (Engine& eng, const param_type& param_arg) const
    {
        return detail::generate_uniform_int(eng, param_arg.a(), param_arg.b());
    }
};

}} // Namespaces

#endif // BOOST_MP_UNIFORM_INT_DISTRIBUTION_HPP

/* uniform_int_distribution.hpp
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
*/