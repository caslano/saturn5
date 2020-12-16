// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_PIPABLE_HPP_INCLUDED
#define BOOST_IOSTREAMS_PIPABLE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp> // BOOST_MSVC.
#include <boost/detail/workaround.hpp>           
#include <boost/iostreams/detail/template_params.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/static_assert.hpp>

#define BOOST_IOSTREAMS_PIPABLE(filter, arity) \
    template< BOOST_PP_ENUM_PARAMS(arity, typename T) \
              BOOST_PP_COMMA_IF(arity) typename Component> \
    ::boost::iostreams::pipeline< \
        ::boost::iostreams::detail::pipeline_segment< \
            filter BOOST_IOSTREAMS_TEMPLATE_ARGS(arity, T) \
        >, \
        Component \
    > operator|( const filter BOOST_IOSTREAMS_TEMPLATE_ARGS(arity, T)& f, \
                 const Component& c ) \
    { \
        typedef ::boost::iostreams::detail::pipeline_segment< \
                    filter BOOST_IOSTREAMS_TEMPLATE_ARGS(arity, T) \
                > segment; \
        return ::boost::iostreams::pipeline<segment, Component> \
                   (segment(f), c); \
    } \
    /**/

namespace boost { namespace iostreams {

template<typename Pipeline, typename Component>
struct pipeline;
    
namespace detail {

#if BOOST_WORKAROUND(__BORLANDC__, < 0x600)
    template<typename T>
    struct is_pipeline : mpl::false_ { };

    template<typename Pipeline, typename Component>
    struct is_pipeline< pipeline<Pipeline, Component> > : mpl::true_ { };
#endif

template<typename Component>
class pipeline_segment 
{
public:
    pipeline_segment(const Component& component) 
        : component_(component) 
        { }
    template<typename Fn>
    void for_each(Fn fn) const { fn(component_); }
    template<typename Chain>
    void push(Chain& chn) const { chn.push(component_); }
private:
    pipeline_segment operator=(const pipeline_segment&);
    const Component& component_;
};

} // End namespace detail.
                    
//------------------Definition of Pipeline------------------------------------//

template<typename Pipeline, typename Component>
struct pipeline : Pipeline {
    typedef Pipeline   pipeline_type;
    typedef Component  component_type;
    pipeline(const Pipeline& p, const Component& component)
        : Pipeline(p), component_(component)
        { }
    template<typename Fn>
    void for_each(Fn fn) const
    {
        Pipeline::for_each(fn);
        fn(component_);
    }
    template<typename Chain>
    void push(Chain& chn) const
    { 
        Pipeline::push(chn);
        chn.push(component_);
    }
    const Pipeline& tail() const { return *this; }
    const Component& head() const { return component_; }
private:
    pipeline operator=(const pipeline&);
    const Component& component_;
};

template<typename Pipeline, typename Filter, typename Component>
pipeline<pipeline<Pipeline, Filter>, Component>
operator|(const pipeline<Pipeline, Filter>& p, const Component& cmp)
{
    BOOST_STATIC_ASSERT(is_filter<Filter>::value);
    return pipeline<pipeline<Pipeline, Filter>, Component>(p, cmp);
}

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_PIPABLE_HPP_INCLUDED

/* pipeline.hpp
2v44W9s3uRq/+VDOf4cnwLlwMJwHR8DN2h45B2bAhXAqPF/bG4vhxXApXA2XwbV6nvLt8CI9t/liuAOu0P2CLoGv6LnKf9J9qz7Qfau+gpfrPkC/hqnwt7AbvFL3+1kDh8C18FS4DmbCa+CFcANcBzfCa+DNeh7yrfABuAk+BjfDnfA23Qfodvg70dd63/H6Bfn+1XitJ+dmR6+9yIXhu7ASfA9WgR/AOvBD2AD+BQ6CVbQ9tE/bdx/BAvgxPFfNF8L9ur7rU7gRxmg5/0z3XfpC22lfwj/Cr+Dbeo43yhyGYSfqXgQa2BqG4CAYgcNgHLwZVoabVf5OWBHerfcHjMhp/w7UeHC7CL43XLofmMQRrAi3a7v5XpgG79N27v16nsif4clwB5wJH4I58FE9L/0xuAk+DreovBv+J7W9+hR8W/XfgbvgX+Fz8CB8Hv4AX4CtdN+v9vBl2Bm+Crvq/l/jdP+vCXAPnKT7gE2Gr8MZ8A2YLfpa3rx+CthL46cC9MZbx2p8jIOV4ela3ibCRDgetoZnwJ6q3z4muk5v9+eRo67V276o5HkhYxcXPTNkFverUd751t8/4a3pg0tCJhXlre3bzzO7Lyn9vOuMJaWfLbIcs42oF1DeOSPfL8FsaXQ9YBosuSYQou+tC5y/tOjZI+u53456FXUI1XkZcijvTJK6X0RkDWFvOJ37ZcuQXRU2+1DBc0q2oJ+DTPHzSpIu1LWGMAMVPLtkPvdXoIqfYbIJvZVwFyyxHvHCkueZpF5UeKbJWvywExV/edhfr5iBeXc4H65GZfTEXZiGzD7s7Lqo8NyT1IsLzz7pzO+xKF3fSAWM+6i6TxaudXyY+908z1vz+P3FJc9GOYh58XWQjQ9EZF+szssJF2ol+otgf/zknZuydnnJs1POwHw3+lv4vR8eQj+yIrqGsjm0raMcuaL0M1W6P1n0XJUrkH0VtR8VPGMl6RL84LoHvbNWMlw9uBp+78q5fse9SB/8/2TZz1/ZecmRz2D54JIjn8OSfmnh2s3hl0b38RpM/C7i90ZUKvoPQ9uazr2X6jktByJlPqslbiVhQf5N7pvzewvhjhtLPkBv5MroGS75cCXKO8tlq3sPX4W2M11SL8MfMB3uQm80nI/6YCzPh8E1pFu53wD36IfD93An92mroue+9IfBs1/yVxU9/2UL9+bLiElD9UadgZqPWovagdqDOohKOhgx6aiRqPkHy9enll/lV/lVfpVf5Vf5VX6VX+XXf+L1S+3/N7Ptz7P/31mBc/7W6njnTFSshIM+6Cb0M8Yd4cw4d9nTxLaBeV352cE1Zi+J3bq2+TK4W2ItLzN3rPNlVDY4p2tqbvZsy/wvq7tTi6yXuFnMs0wT41jnhKn94Fn6/pze28VsojnOhEyz4ufla5i/FZlYf43ba3Lf2F8jsOgY1pvJnCiJ0xJrPTVMwXO3JE50jpTKadiD5zNt1c/JazWd12s6p1c8WjqfaEtnCWOG2K1qS2fcLXs6p1csezoja03n2jqXvKuYXy5p1Q+fXAIt6e27U+SMHU3vZa4ZtnuaSDA/+HNeO4j5GslLJ5iwGQZXo4L5wt8TUWRPx78xZgyyus7GO78NVfZ52T9nvvDOjMysYOSq50RZF3Zpwo9KJfKF7ANStAYwxfOGfU/QSmXPC6aSNS/4a/DjxLyHqcT/tva19rhhzSN+mqSKecRpLqd13W7JHzY35hTgDf8swYiYV3c64IfTzCbrvFFTqWQeq6/2x4vZDaYp9gejpqFWoYL5za9PRTbkzy8dJ/e3mTb8PwWVg5qL+RronzGFblOdc11J5Cs7bXB/HmodagfqHdQB6jPdI5M8aVHHsNc=
*/