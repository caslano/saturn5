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

#if BOOST_WORKAROUND(BOOST_BORLANDC, < 0x600)
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
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
*/