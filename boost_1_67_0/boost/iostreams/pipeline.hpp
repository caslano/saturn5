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
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
*/