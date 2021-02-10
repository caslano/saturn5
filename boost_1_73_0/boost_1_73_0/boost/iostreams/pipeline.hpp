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
07XK7uu3y3BZf7WahHqhb5I/GnNavqkZ8logSaSEThD60fO1tbPzxhvwav1YLaKWKfYkRSlHL2FYFZX0iGuxMT+uxBOttnaqG+xml58cy+il2+x/NNJuZJ0gGbaiHjw6yqyupYN60t/Jc3q7ol9nl+yTLqur4UzokWk3mNoghUfCkh629T4NSDf7leQRPDfMB/Z4DI5Oa6ijqK75Q4Dh2h1C89v9p8rS/iK56Y6pWSjdybPi9XJTHfV6DL12xy7QzdkwyLqA4/W7RfrRlUeDaQP44ebYPSnKwhS7BUm4vwsSikrC+Dmru4+277lRb6pVdsBIMBKM/GBG5o2RBRj5BZDkDkmtcQzBKCEmAcPJMPyq3DS1ln59dN1QWN8HG8FG6EegMQ+N0I+ygBH6EcgEMoVDJuSkNMxUSTu8h5iUiJn8ybj1MeRrvSBfvHt809DUiRCMu4/hNEnci0dBdmxQ20xRqDwQ8xfN5hkvAbkzHX2l+FFquNEagbghTuKNQR4ByNiSnIzWbGi0+MjJ9MEmL7vLaI9k1bz3jW40gLSZohlcx7QHuWe1IVUXELsQqrJAV2ShChwDx0uL41ypyhfHkMH8eRwtPYIMlo3I4K4K0AK00L3QvcJxFrpXFspC94K/4K8I/IXQBYCLAri8
*/