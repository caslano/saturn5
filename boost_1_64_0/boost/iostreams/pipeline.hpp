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
XSV/F9aLtr5IzliegYh9rJgW+kKrOvqo2kf7KTwh7J9IGFMmV4OUrL7UKMrmkKxL0YRWKzvYa9nYz7tFcaXA1YKNKpX+CpvJITIBK27xwvBm7TNzE68MUXir26wOh/sxz8pFMpuhtS/Q+oItVKpGUSB+zz4P5sp3ATCnVDA45cL1tYP+soi3G4fJ7u2prT5UbI5smUqDIn9Y0Df91Dy+FaXpM0Komfe9ZyE8UXgm0wEC/bbUaTXztaqAT8rfVya3+TNUZ4Wsg1zmcVoLgh+KD5+/mwmCa/D1IKFdjGENn3/RLgHS7m7fKNx71X1lONlBg4GoQWiMTYLCLEFUWdsNGOQ6D24v5R2T5rIapEm7PSQOiL1cvpDagFPjxXjZzsicX4I+CcjPU1TtfXXuTxRF/JkVukjTqfx5KRvbFNaIEJjHr7kGiutcbM6AYveSBWtsq3HY+0FLPIG+o54VFgwRj5OW3eqirXAejpzaeWkJK0q2cQ3OsWn8R6j8renatS7NewolTqv1wZEtavXJEMVOhX0fR+ivLFFOrTyYPk+L2yQxAbhUc48+k8v0tA==
*/