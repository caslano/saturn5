//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_STEP_ITERATOR_HPP
#define BOOST_GIL_STEP_ITERATOR_HPP

#include <boost/gil/dynamic_step.hpp>
#include <boost/gil/pixel_iterator.hpp>
#include <boost/gil/pixel_iterator_adaptor.hpp>
#include <boost/gil/utilities.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <cstddef>
#include <iterator>
#include <type_traits>

namespace boost { namespace gil {

/// \defgroup PixelIteratorModelStepPtr step iterators
/// \ingroup PixelIteratorModel
/// \brief Iterators that allow for specifying the step between two adjacent values

namespace detail {

/// \ingroup PixelIteratorModelStepPtr
/// \brief An adaptor over an existing iterator that changes the step unit
///
/// (i.e. distance(it,it+1)) by a given predicate. Instead of calling base's
/// operators ++, --, +=, -=, etc. the adaptor is using the passed policy object SFn
/// for advancing and for computing the distance between iterators.

template <typename Derived,  // type of the derived class
          typename Iterator, // Models Iterator
          typename SFn>      // A policy object that can compute the distance between two iterators of type Iterator
                             // and can advance an iterator of type Iterator a given number of Iterator's units
class step_iterator_adaptor : public iterator_adaptor<Derived, Iterator, use_default, use_default, use_default, typename SFn::difference_type>
{
public:
    using parent_t = iterator_adaptor<Derived, Iterator, use_default, use_default, use_default, typename SFn::difference_type>;
    using base_difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using difference_type = typename SFn::difference_type;
    using reference = typename std::iterator_traits<Iterator>::reference;

    step_iterator_adaptor() {}
    step_iterator_adaptor(const Iterator& it, SFn step_fn=SFn()) : parent_t(it), _step_fn(step_fn) {}

    difference_type step() const { return _step_fn.step(); }

protected:
    SFn _step_fn;
private:
    friend class boost::iterator_core_access;

    void increment() { _step_fn.advance(this->base_reference(),1); }
    void decrement() { _step_fn.advance(this->base_reference(),-1); }
    void advance(base_difference_type d) { _step_fn.advance(this->base_reference(),d); }
    difference_type distance_to(const step_iterator_adaptor& it) const { return _step_fn.difference(this->base_reference(),it.base_reference()); }
};

// although iterator_adaptor defines these, the default implementation computes distance and compares for zero.
// it is often faster to just apply the relation operator to the base
template <typename D,typename Iterator,typename SFn> inline
bool operator>(const step_iterator_adaptor<D,Iterator,SFn>& p1, const step_iterator_adaptor<D,Iterator,SFn>& p2) {
    return p1.step()>0 ? p1.base()> p2.base() : p1.base()< p2.base();
}

template <typename D,typename Iterator,typename SFn> inline
bool operator<(const step_iterator_adaptor<D,Iterator,SFn>& p1, const step_iterator_adaptor<D,Iterator,SFn>& p2) {
    return p1.step()>0 ? p1.base()< p2.base() : p1.base()> p2.base();
}

template <typename D,typename Iterator,typename SFn> inline
bool operator>=(const step_iterator_adaptor<D,Iterator,SFn>& p1, const step_iterator_adaptor<D,Iterator,SFn>& p2) {
    return p1.step()>0 ? p1.base()>=p2.base() : p1.base()<=p2.base();
}

template <typename D,typename Iterator,typename SFn> inline
bool operator<=(const step_iterator_adaptor<D,Iterator,SFn>& p1, const step_iterator_adaptor<D,Iterator,SFn>& p2) {
    return p1.step()>0 ? p1.base()<=p2.base() : p1.base()>=p2.base();
}

template <typename D,typename Iterator,typename SFn> inline
bool operator==(const step_iterator_adaptor<D,Iterator,SFn>& p1, const step_iterator_adaptor<D,Iterator,SFn>& p2) {
    return p1.base()==p2.base();
}

template <typename D,typename Iterator,typename SFn> inline
bool operator!=(const step_iterator_adaptor<D,Iterator,SFn>& p1, const step_iterator_adaptor<D,Iterator,SFn>& p2) {
    return p1.base()!=p2.base();
}

} // namespace detail

////////////////////////////////////////////////////////////////////////////////////////
///                 MEMORY-BASED STEP ITERATOR
////////////////////////////////////////////////////////////////////////////////////////

/// \class memory_based_step_iterator
/// \ingroup PixelIteratorModelStepPtr PixelBasedModel
/// \brief Iterator with dynamically specified step in memory units (bytes or bits). Models StepIteratorConcept, IteratorAdaptorConcept, MemoryBasedIteratorConcept, PixelIteratorConcept, HasDynamicXStepTypeConcept
///
/// A refinement of step_iterator_adaptor that uses a dynamic parameter for the step
/// which is specified in memory units, such as bytes or bits
///
/// Pixel step iterators are used to provide iteration over non-adjacent pixels.
/// Common use is a vertical traversal, where the step is the row stride.
///
/// Another application is as a sub-channel view. For example, a red intensity image over
/// interleaved RGB data would use a step iterator adaptor with step sizeof(channel_t)*3
/// In the latter example the step size could be fixed at compile time for efficiency.
/// Compile-time fixed step can be implemented by providing a step function object that takes the step as a template
////////////////////////////////////////////////////////////////////////////////////////

/// \ingroup PixelIteratorModelStepPtr
/// \brief function object that returns the memory unit distance between two iterators and advances a given iterator a given number of mem units (bytes or bits)
template <typename Iterator>
struct memunit_step_fn {
    using difference_type = std::ptrdiff_t;

    memunit_step_fn(difference_type step=memunit_step(Iterator())) : _step(step) {}

    difference_type difference(const Iterator& it1, const Iterator& it2) const { return memunit_distance(it1,it2)/_step; }
    void            advance(Iterator& it, difference_type d)             const { memunit_advance(it,d*_step); }
    difference_type step()                                               const { return _step; }

    void            set_step(std::ptrdiff_t step) { _step=step; }
private:
    BOOST_GIL_CLASS_REQUIRE(Iterator, boost::gil, MemoryBasedIteratorConcept)
    difference_type _step;
};

template <typename Iterator>
class memory_based_step_iterator : public detail::step_iterator_adaptor<memory_based_step_iterator<Iterator>,
                                                                            Iterator,
                                                                            memunit_step_fn<Iterator>>
{
    BOOST_GIL_CLASS_REQUIRE(Iterator, boost::gil, MemoryBasedIteratorConcept)
public:
    using parent_t = detail::step_iterator_adaptor<memory_based_step_iterator<Iterator>,
                                          Iterator,
                                          memunit_step_fn<Iterator>>;
    using reference = typename parent_t::reference;
    using difference_type = typename parent_t::difference_type;
    using x_iterator = Iterator;

    memory_based_step_iterator() : parent_t(Iterator()) {}
    memory_based_step_iterator(Iterator it, std::ptrdiff_t memunit_step) : parent_t(it, memunit_step_fn<Iterator>(memunit_step)) {}
    template <typename I2>
    memory_based_step_iterator(const memory_based_step_iterator<I2>& it)
        : parent_t(it.base(), memunit_step_fn<Iterator>(it.step())) {}

    /// For some reason operator[] provided by iterator_adaptor returns a custom class that is convertible to reference
    /// We require our own reference because it is registered in iterator_traits
    reference operator[](difference_type d) const { return *(*this+d); }

    void set_step(std::ptrdiff_t memunit_step) { this->_step_fn.set_step(memunit_step); }

    x_iterator& base()              { return parent_t::base_reference(); }
    x_iterator const& base() const  { return parent_t::base_reference(); }
};

template <typename Iterator>
struct const_iterator_type<memory_based_step_iterator<Iterator>> {
    using type = memory_based_step_iterator<typename const_iterator_type<Iterator>::type>;
};

template <typename Iterator>
struct iterator_is_mutable<memory_based_step_iterator<Iterator>> : public iterator_is_mutable<Iterator> {};


/////////////////////////////
//  IteratorAdaptorConcept
/////////////////////////////

template <typename Iterator>
struct is_iterator_adaptor<memory_based_step_iterator<Iterator>> : std::true_type {};

template <typename Iterator>
struct iterator_adaptor_get_base<memory_based_step_iterator<Iterator>>
{
    using type = Iterator;
};

template <typename Iterator, typename NewBaseIterator>
struct iterator_adaptor_rebind<memory_based_step_iterator<Iterator>, NewBaseIterator>
{
    using type = memory_based_step_iterator<NewBaseIterator>;
};

/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename Iterator>
struct color_space_type<memory_based_step_iterator<Iterator>> : public color_space_type<Iterator> {};

template <typename Iterator>
struct channel_mapping_type<memory_based_step_iterator<Iterator>> : public channel_mapping_type<Iterator> {};

template <typename Iterator>
struct is_planar<memory_based_step_iterator<Iterator>> : public is_planar<Iterator> {};

template <typename Iterator>
struct channel_type<memory_based_step_iterator<Iterator>> : public channel_type<Iterator> {};

/////////////////////////////
//  MemoryBasedIteratorConcept
/////////////////////////////
template <typename Iterator>
struct byte_to_memunit<memory_based_step_iterator<Iterator>> : public byte_to_memunit<Iterator> {};

template <typename Iterator>
inline std::ptrdiff_t memunit_step(const memory_based_step_iterator<Iterator>& p) { return p.step(); }

template <typename Iterator>
inline std::ptrdiff_t memunit_distance(const memory_based_step_iterator<Iterator>& p1,
                                    const memory_based_step_iterator<Iterator>& p2) {
    return memunit_distance(p1.base(),p2.base());
}

template <typename Iterator>
inline void memunit_advance(memory_based_step_iterator<Iterator>& p,
                         std::ptrdiff_t diff) {
    memunit_advance(p.base(), diff);
}

template <typename Iterator>
inline memory_based_step_iterator<Iterator>
memunit_advanced(const memory_based_step_iterator<Iterator>& p,
              std::ptrdiff_t diff) {
    return memory_based_step_iterator<Iterator>(memunit_advanced(p.base(), diff),p.step());
}

template <typename Iterator>
inline typename std::iterator_traits<Iterator>::reference
memunit_advanced_ref(const memory_based_step_iterator<Iterator>& p,
                  std::ptrdiff_t diff) {
    return memunit_advanced_ref(p.base(), diff);
}

/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

template <typename Iterator>
struct dynamic_x_step_type<memory_based_step_iterator<Iterator>> {
    using type = memory_based_step_iterator<Iterator>;
};

// For step iterators, pass the function object to the base
template <typename Iterator, typename Deref>
struct iterator_add_deref<memory_based_step_iterator<Iterator>,Deref> {
    BOOST_GIL_CLASS_REQUIRE(Deref, boost::gil, PixelDereferenceAdaptorConcept)

    using type = memory_based_step_iterator<typename iterator_add_deref<Iterator, Deref>::type>;

    static type make(const memory_based_step_iterator<Iterator>& it, const Deref& d) { return type(iterator_add_deref<Iterator, Deref>::make(it.base(),d),it.step()); }
};

////////////////////////////////////////////////////////////////////////////////////////
/// make_step_iterator
////////////////////////////////////////////////////////////////////////////////////////

template <typename I> typename dynamic_x_step_type<I>::type make_step_iterator(const I& it, std::ptrdiff_t step);

namespace detail {

// if the iterator is a plain base iterator (non-adaptor), wraps it in memory_based_step_iterator
template <typename I>
auto make_step_iterator_impl(I const& it, std::ptrdiff_t step, std::false_type)
    -> typename dynamic_x_step_type<I>::type
{
    return memory_based_step_iterator<I>(it, step);
}

// If the iterator is compound, put the step in its base
template <typename I>
auto make_step_iterator_impl(I const& it, std::ptrdiff_t step, std::true_type)
    -> typename dynamic_x_step_type<I>::type
{
    return make_step_iterator(it.base(), step);
}

// If the iterator is memory_based_step_iterator, change the step
template <typename BaseIt>
auto make_step_iterator_impl(
    memory_based_step_iterator<BaseIt> const& it,
    std::ptrdiff_t step,
    std::true_type)
    -> memory_based_step_iterator<BaseIt>
{
    return memory_based_step_iterator<BaseIt>(it.base(), step);
}

} // namespace detail

/// \brief Constructs a step iterator from a base iterator and a step.
///
/// To construct a step iterator from a given iterator Iterator and a given step, if Iterator does not
/// already have a dynamic step, we wrap it in a memory_based_step_iterator. Otherwise we
/// do a compile-time traversal of the chain of iterator adaptors to locate the step iterator
/// and then set it step to the new one.
///
/// The step iterator of Iterator is not always memory_based_step_iterator<Iterator>. For example, Iterator may
/// already be a memory_based_step_iterator, in which case it will be inefficient to stack them;
/// we can obtain the same result by multiplying their steps. Note that for Iterator to be a
/// step iterator it does not necessarily have to have the form memory_based_step_iterator<J>.
/// The step iterator can be wrapped inside another iterator. Also, it may not have the
/// type memory_based_step_iterator, but it could be a user-provided type.
template <typename I>  // Models MemoryBasedIteratorConcept, HasDynamicXStepTypeConcept
typename dynamic_x_step_type<I>::type make_step_iterator(const I& it, std::ptrdiff_t step) {
    return detail::make_step_iterator_impl(it, step, typename is_iterator_adaptor<I>::type());
}

}}  // namespace boost::gil

#endif

/* step_iterator.hpp
PDrgigzFwKIiOuk46WSTXSfti0gXIy7tjMUcRQgYA4sDusyOqq91bdADfhBuAmFNyuxU+7mV/RSHUX/E/sPKq11uUkQd5eKc6+nIwXEkQyhQPlXuNvj3CpMyD1WdwfTKOeBwYx+ph0dTj9RSp0HqASAN5y+FwWAJO06xqGGJB5YYPTMT+4e3/navyAGLecV3tUPK2UYzh/RtltPlpqD3LXxn9seOAN+27A90AF9OoE0Vl1EubG3fpRdA+5T8tmUyXhyvK1KPbCz7HQ72ymyjnN9iP7Iyye4wrDyurE6VvSelSITzDdbrdNknIOW+DcoteMzGYG8r3SY9ZdAJSR9QF4U4tafag2UtMPNy6FFveqedb1n5nL2+dJ2yawzWiMy3ZLf/rpJPL7e3cQF63jP9QjW8KlMv1GKop4Xzr8aZi++iljWpowdCDP46zmek/jRaHUr+SWKj0wwNPsdOOyvzDJnH57vJRylq3XK+43SVQw19fzu3Dv1J0mp935iXXv5sAm4xnZpI0TSbgUohzFYGonCBJyFBxbhwMrM3tNgUMCCe+iF8VbzM/nbvEOmiydsPR8ee5Ny645BXdh081R7A44v91AlHiSipH9P05o8xvZxO3+Sp9E35TPkRatLeuPqz0AvsLhplkJKYvXdakk5Xx22sV+oblOVELZZS2FqSHuDrHPMjQ8fPQASR8z1Eq6kZr6FPEJbR2+7F2dI0HzDXibcHk0xQeLwIfQU+RIbOpMCjYA4mIQU92zNIakwILcIaZqmEEdK0DCBOEIZKeyJXqo7i3e0mVyerDSWcaOePNQlWJb8189A8N5mQHG0QHwz6TOErOf+qy1T++dicJV3R5ryP3rVuVGYbaOq2pGjqPIj5Gwq4nbafyX+U81dghU7ESlcalfwWf/vqoQHzBXy39Rf6wywknUUj/QcYSqZL3dzqpJ0cRa92Q/uO2I71HliSoGQp5QbZKDsMYIkcl+qMUjhBPCtNQzYmaNwkfEiARXr+bjn1Y6wSKkH20WdNVJ+urBHce4EL2k/fhtEe17BQIFDFVlq9wxX+W0Wn6Hq3qbS8VVNX/LR1GtLuMugCMJk74l3dEH+cmxsFXYwS6FoKnzoNEt8Z5L+dgVuzcc8F9biUpK+T+VanK8CbHdkn6DF7vsVBPqMX05gi+a1KW3l/6AbVlgjfEk7FSCcZNBhPakJkeQqN0sIvDsJwvLNj7/+jAC70o8O3sD0NDrIwNvsBkEejTof5D8R8SnRkwyBNACOLjMaUaSLsxcO2pl618yA90R7nBChVvJYkLo8/np62WfusHV5B3UEIJ12sGAHe5KB3e0FualHUgpA3Bv9clZ0y9V1ljaaeKqPtGfc95p0Edii/r5a+nrlWx7IEeAvGxt4J/2caa/H0mfSzfnFJ4xIeooOk2cMi0x2xO00wfp7GuK/Elf3UxJCr0UHdt8yGIhQVxQQ8FA1IdUQPXE9hJmqvUJca2qu5nL+Ib64H/xxtroe05gKxoMVAMhm1qq/2ajf9XHtN4PpurzSup73Y9ZHRxnKpDiVDeAcsE5nucEORf/tAPG649U9RkdFfFFV9kyoZiKuK6pBFIostkULEiZlGG9kp9RUTzw0pJ79Wc9QqrCfG2xOjpThmMJeT5X2loDF3qzEut9KmXAyPqkmJ3ANN8EuY+mdJd0TEQeTk/fjJdZx41ZY7yTIIlipgybjmOFqrgc3WVPpxXYj9uN5Gl8qvdkW/qxvwZP+7+Ek6kL9J9h6Txc2y2CqLO2TxpCzWyeIWWdxOJuIWw1PiTeTh++Mrbc2btNIqva/Ty/J+q14+F9LDirVmSPZe31FZPCyLzbK4tbrwK853IkWny7VBkGc3V3sQXmp2jc+YumAVx+3cxW2rzLh/WLnUwuEGB26nrz4HXus7DVJnisy/yT3rAfqI1X/92bRyMAfzT4KBskHmt8j8DpnHEUvmt4dsQAO8JJIh3CERvXCTRIzCyNmzhcHwxvmvgWgpv9UYGsQeDCEje0gIRZJ1uqr8VtwQHDqfTAMTQ2fhofLHceJIJUUKwoyHNcTv4AJHGYGhw7Mj1JiMU/iOh+v6czv3BWYaDwNF6B0kWH5SF3pT5ZAey+EkF9hAOZyMhJ6lyU/GJj8ZWklTzRFmV/64QphS+eMjwtDKH1dx/oVMSB1Ub+hemnB35eRHRC7C78ZgEwRPYqKZQhPYQ0ZoDBLm765JmHq7eHXlUwm3iYOmT0dyKKucvzuUBPFTs2nUrTRqeSuofASjzsKcN3UZ5/sSfx/ifJ/j7+Oc7yj+ipxvH/6Wc75d+LuA8/0tCe1O2fMmNOGJAL/JwW3b5ZA928nxL9VdOSNq+K8C4mHy7lAqfQ1MIrt9ddU8KMcmSKzG/hpiQ48msbbsXMatF9CVow8dwUmdTm49ng8QFklkumCCtp0Of8bZszn/rQaotl0ZQX4DvYWv8Csof47kPakLeMh2VHLZ04SbDAJ7qNV6EgHlUHIi3nbLt2YZRVGt2/AjakCKGgBmD5j7YtL7OBooV0NLIoHJiK1Z2ASig73tPyr2U4bqRoB1WNgU5JmxsStUClESgboZAfmAoEskksL5fgGMUOJKjI3hJtzAvTery0E9bqDfkQDf7CAt32jr0rQgv4WaJQNrZnVV82BZ4l0GSCnzTaFsYNajZsLNYJbBCmcsMtcZuY+gsZuEQS9m7jrSqYoX6kYEafl2XegCjhJd14LsfJODGJfCkBo6g5GdT3DrH6WV76aVv5yrbaLhD3LrXkOrs/MhoUjqfEwYKXU+zvm3QFw731oJgiFoJczBCoSwcI4yCQQDsci46agKnG+7npJmCP2KFf5wsZwcToJfOVktYmiBnupvDrDqT+221mL/Xk4ehxZziuI2SEFjaD4CfVyl96sHxRnQnrRqbDb+5Go99KIq70lcUa0eq4gnqxo9OOaRl++jpxRkfqvQX2mGwspiLTp7oZRYd2AcVSqzumTeh+obETdwO/mvIjAYeo/BW22Ar3Q6yMPbLkcUsVXanV71dSX9DoNKhnPaJpiQhM04IVGhTP52LfQQC7XfJA7AOgFpckEbnaH1UImQv5HOg5tTsATXSaSU81VfpiriQxuTDl4FVGk336CLVjHihNA5gaCG32yY18jvyarm9wb5OtxiFNoH4cUd9ToT56f+/YOG9voMYWh7fQ5qRzL30ayusAHV7cWwCQKh1IL+Rei4RyEa3gWL/+gacwUoU+lVHc3SUV3H56rgVKE2KJ8rbSJ0cyy6t59W+4PAMO6gfU1rBqVxQIOov46vC3z4DV3tnIzknwQzPxkjYOXBN7843+F0kb+eBy2vz5Iu2mRPLX5bWK3X52+u5uaGmwJ+TJkZnEVzTqS7R5qEWdAhkirvzBLumAuvjSlZOeFb5hRLk3VCck6Of694HjU9PIL1S6rbhU3KrnDKHHQRmoQUFzJ3AS/Ju0XH+UNsk9qbOcKY4j/BYiwZavOm8OA32VNm2PhmojAAnmB0qaNd27Mj09Oc6amDtkgVBzpLMgL8YfpJA4wUsQ5eAvl7SE5nJAIExiJhCPwYkC4L6YooneTdrlO8zcJd/sjqPEVs4t5LdpQkB/wEEdoAv3FuniOPfPmV2vvFa238RsFCt5sdDgSQiLR0wHI5UiR+HB4i5R+OhAcq+U1uzCAIEcD/sK6CZixoArboWMZbdeiseyt5H02I5Vt1RYr3GB2P6WAsTFTy31Q8u7Pbaw6H7oYykCeLVAsvlICvDxRp++Kz6xz4L9QGGcbZAdCZlQAaHEvpqc3CLbiF7b/ZFraIsTWtfPmXaeXPwN8R+Ov/VVr5EPibA3/3Qly81Tmhgzn/oSYrM57INR3Ry8RVe4qkdGg3ILaFB9cALbWX7oZFJJhLQgqzjr5hxtETl9E4ajLGGEe1idQ4+m0iuhZ7d1Mi7u5/9xX4yY4E8hfLngrZmyF/iP1d9s6UvRbZayXDcYtTvhCxd8jeqWAg3bUg/mv6kt+oBtIKWjHLNAMp5yrkAtYkDIlPSN4nEsR+Nq/A+SwQrogGKX8ysF1AWcve8TVpYEh5s2RvuuyFzlteXfgI52sZiJc7K2JBTeEjeTbkVcDVPj6wt01V2WNTKflZD9f147a9YvwtWlZhg3QpQfZkcX4c/CrvGMP53qZuwoWIOLOkf4Cf6nCRG1vVPWyrMxV+auVkqzja5n1CHLoiBybPgH/3xUjE7SA3LKFUQV6gg0AqiCR7BeCUIC7VOJ0GPVb2ABMgnAM8Ao4EOX+BXFggjrIf4mrrYYgC9px/O45VF5dxgbcR186fDINI/mRgGB4qXTJyvhcx+lIK9+zjqdgJsyLWV6WLYBFGUKz+mCXnK0jFYjyRwPlfSmQF4vwbEvGgaioqrJRfDrYjrEYsMp8j8zNlP21U3hoanho1H+9C8/F2NB/HwKw9lI7AXQOAWwCJjaG26LMh1Bp9Tgg1w3MVfaam5N5oVGLowwHUFuT8uBkZ1yGCyEl8hUHhK5ScLupSllVWRCwgW77E7ShYWbNt4hOBeQlYUw/YGyvmVtqs4l2Sd8Ey70w7j9XDT65vMQRqk7AxbLeIQ4J4nE/X6EtqgoBxoZXUxkcRSsaVJMwjzlx1QOH8mSAReaFQNepDs6BTACvFl7QHr4LW4ZbMHC6Q1FPUDk9OqL0/jpQ5sRZrTuhMf7QkynUhnKzR4HWzAqb2FDCc1VO6o2euLB2YSJEr8y/nAn7kDW0WqqA5l8fmXB56sD+zlQvQVs5FW9lCbeW5/bWGoOZyDk1bgOby4AhfoMagxXx9f614ptA10eeM0FWYIr+A2s3XULvZDMYxS0dN54JQuJ9ON/X/AvoFCuKPQgCAQ0vVvQt4VNXVNz6TmWQmEDjBC0TlEhUQDCAQBMKAonCSYBkYDCREG/BGxJQWCudIfGUgODM1h8MofYsttrTVT6q0pW9REWJFTQgmUagGxIqCEjXqPg5qkJBMyJDzrbX2OXNJgm3/7/t/vu97HibMnMu+rr3277fXWntn092JdPcPeJej54Xa3/HufVLR9AekgukrpfnTZekH08ulvOmLpVnowwkzwQ85QgZN8tL7gA8C1ZvEFbhLnexhv+AFRoS80A946alOXcfrD8N1bXVqtHIwI2v3psag8pNJCApW2Qyo/AFhBDoTBuAy7vKRVS9J8HFm1QuBZKeBmC/jiHkFr/zM7Ddvgf5zS0JgtQ2jCFYJgQcQXYqLfeF7hUcbuKBEZU4IuOBuvRVRTOVWkjuVElI2JzfCD+2AE2EDjTOA1T+O9Uvo7tjlPrHLqrfcpwPgpuMPSZKEQC0SGkOa8iPaeykGsD5lQ2At+Nupjg5+8DGC61EO9Etbqv62gsZbaXttulNajVLZz0hH2AdiOc2s1XcRqhXUVh4cG04OJUd7FqhIgS6vKNLexamfy6ewz2IA9QCFsAbFMR426aSJ1UvqxQzShgt75HijmWNFLMdBscb0TzCyK7OGSmOZVVI29eIYgvz0QxHnaremmMokfqy5zSyGxLIYH5fFq8mmUsB8bAvYjJtNreD/CiRNCyVHK4oDUZoAbML1tnS90V0GoZgbJRTDCbS/kIzbMA7X/pQc5RNzPazqduQTv0w2+MQUktCrkww+sTHZ4BMVF4hPCH7cGh85xQ3EKe7GklAf+k/Ui5NQxgQF94PYeIg4Hd3SfoF9DJNAXDOsioSmm81wT5g3A0wSw8xmyBH8e+0JzaBdZ4vVejzbMIlTlRGI4qjanK14DLbiQbZCnaztt5uKAwjLJCIsXOz00sAJQalDx3yY4AOVZCZYp1rVBXZfjVNxr9OSbfFlcGp3nIeyyeXB32IPG7R1riJOQpBdjpQ1JMp9Ks7fL9+kuMuR7pTjHFD+Oh2V6C1ff50ql5t8588FyHdg9gTKM5hTnrmKPClkAxTBW6svtJSvGmjPutCVMKlAU01pxzXtxTFFDLfV/LDidoJgKWIaai1dvgz0jS6Xw7dJQdEJAEQsu9OkqPCPoNKpGjFeNADKI9MLBazk95wWrQBa5Go3r1b93qRF/Y3Rz5nR3ALtjQvIjMo5M8qMY0anOjkz+oXJjG620SPEjKibgBxN4uToQSJHmUiO8oEczakXZxM5WkKO/lw2ctuislEalQ25b70V/S00PP+PBqOdTpEDLWJJl+YTWsuOS8QaS+TqhEQwDJBOBqFEkrWDKBubuYihFGjJcK+tNlNa2VY7U5qKfZJuKovXARa8aInp3e3nzEykH5mK4XWLRgdzerspmfXmS/fHXpoc0yahJZjdDxMGDLyVb741IfqWnBU3YH5pMVXTAtbHFVUZNnhao6AdU2U8GRrfPe0hZtrvtUZLtCP6QvZRLNCVrvc3DFxnd9WvSW8/fun7wDmjUmFqnijzBOHyXgMSQlp2LEc9xuyjbOfzzghctKBJ2SSlfLBwUgo4Pviqj6yK5bq7PJ6UTuKkdOjnMVI6xiSlmQYpxTeJlPJyAS8do3jnCn7crAcmgFTgpvwAU+Cnc5GfkpIyG8HfZipmwX8vDHmzIZxGeulOVK+5rreBvvajZSX3XEPNqjWh4fVWG+0JVBFXaT7ZhrLn456YQIJdXXIrOjqHhvJUSCG758LrjvmcBMMT57JqoOCE1QE+r4IxczmdWJQBpDhMmw9hFvG8OD/Ki/OjvDgfMMRszotnZpWMySqZzUeiSY09rPQ7jBADagE/gu58NkIzlSqw44H8m0mQPWwqPe3zDgcoMMYkyHNNguxPovk2nQhyzbE4gpyOBDkdswjiQ+x1FkeQPUSQ5xZhBs8yIsgeyzozb8ks6f4zPO/BxJEHsyduR448GDgywjG1ZF22jix5hRBYD6XM8Y6XoOHGO4TABXiRGjIPh82t2UdzvFPXuYIB6tf8yBxp6BzpqjlSxhyp/xyp7xxJmDNHCDTgyWIZvlpnKBn/s9/qq053LZoKfHP9IV1EcpgkbP7gDLLrOBIJk48aRMbK2XX7U8iukeO8Wbtl7emB5U/DpwY+w74eWN4JH/s3A8tl+Dz0bXdy/U1LT3L9YUsPcl1vXBJeq/awSxbhTA3NaktNqdVT/hvmhp1kbqgic8N+MjfsYXWyYW6I5CeaG9K39G5uuIbMDTFjQ7Ui7yJ7Q0fU3tAgbD7h+F5uXE3c2M+5MbP7wjAngmZbi1aYMPDNJdz88FLSoG7mhyqyQDQr4h5t2vebH64yzQ+XmOaHVNP8YHHEzA+tpvkh1Jv5oUoIvhs1P1Rp9WQGqIrnRFXaC6b54Y8XMT/83DQ/VPZmflhzEfPDnXHmh/n0YoNhfmgwzQ9TTfPDDab5YSSZHxouYn5o0FIuZn5oIAyK5ofPDPPDCcP88K5hfjhkmB9qDfPDK4b5oTrR/LCHLX6rm/lhMjkuNCC5ajDMD7+MmR8y4K72kzjzg0wr4N+Y5oddvZsfsv9V88ObceYHR8z88KBpfvjx95kf4s0F6oaI4jXtDzqo+Bk0UXgP14t7SBnXX8T+cM+/Y3+4653/efvDnjj7w57u9ofK3H/J/vDb/0/2hz+N4qD+pf8T9oer8g37w67/jv0h9Nvvsz+0/qI3+8P8rf+C/WFnHMp+tHf7w86L2B92IsQ+CBD7jXpx//+N9of9/8T+kH2iF/vDzv+W/aGe7A80Lkm2vYfV+kT7Q/332R8ORnHWwSjOwmiY/RxnVZH9YX+C/cGqcZC1n+wPB1n1qd7tDx8wDnH2/HP7wz2Hvsf+cNepi9gf8k71bn+4y8h4F2GrXSxnDmKrXYb9ocG0P0xUSxrI+HATWhtaZ5rGh7PATdnnM7sbHz6Fy7gGUo1IrBqQWM0/sUbU/ypmjQjOsTwaGVjefH5gubVzYLkHPgp8/hM+DfD5e6Q7YurfiznifFsPxPSlcUlNyZk93C7nq4JrLtxM8shjWMFsfpSE4pBt2dW4pVRaPYq2RZ9M2Uxh982lJfWQsIC9PDtixJEfUxxHRmZXz6wt0FPY2Mkwhx33depSf2FvrYdt3k+TnNys1t5JiKycEFk4fjdRP+2usJUCb7LR57VdEXcERTttE1G1BB3EvQ2Kd6fitciZbN3NidaMLT+Lbi4yoQ8iOZzogu4t7LIVER29levEbyABmJMOCn49FbLqKhD2Al488wr37x2puyNBOcLQ8czDxkAaxXl0QEcjf0A+o/0cXqu4eYQQuD0V+xc0ZaVYC8MYB53YWim2VIrfVorfgZBUimcqxc468awVAFh2GyQ0jNoh+Dee2eWq2KqLxwHaBGdnAK5p1fAUS1/nvA0/FfxP0Nfrpbt9nbk8hNPXOQekp3OufE+XeDZUvmm+taJjsnx5MC+pYuokuZ8u7lfDigwKuzF0Z0VHNuhVvDNRtqvh0G0VHfdJYkXHA9LMio6Vkquio1yaXNGxWB4YuqFL/C50va9zOcxQnSswh7VSepf4WWhgMM8K6El6FrLrEjtDKV3us13uTtDboFNv0FF+v4PG3CP3V8Ud6ngF5Lga+mnHxBNTSzoV+Zh8ySbH9ALJOX1Wndipy3b4a4W29DVkwnSoiEwaBzRTEnzhh6U+2OZvYsSFUxcjrDWb0LsiQkZzEF7Ix1TvHtV9HGZrGD+tcHkQXhYZzqmPV9tQy79Cq3T3Cn5U7mX33eE6IPifQ4j0WAMtNd+/fjLOxVdB5kIA51YsvuqNCP67YFLRHoY/yiLm81rGCoGHACjVid9atQftCNjwIuhIsbnOMnZWKAV+Zsn9dXcrljU/Gx2RgY4et6BZrFUX9oqW0GzsWncrjAhxk4hTsy6erLT3DYoNoLbsnlkFQW9zUK5iG8lVNY1cVRG+Q4LtEylBEst7q7jUPY9bPlRgoKVq2WSZJlpAzPg56mY+fKMFfH/fRDxXE9A+gMWW3vLsF8vzNCC87uWFam5yW7C8abYe7x7pjL67O4XnlxdX3hf3GeXFOU/wf03WOssy7DSLKAQ+SijwO3xCqbPblvXI54FYPvlGPqcmoFCMhazka/lrY2OvsamxFwaloN2ROulKMzc5+WqxNdQX0/nVBKO8/0a1PzwfTf3lZF4cz4RYtffvNaqtyxZQIKwVRRFaoFjwb0rmgiYErkym6uriQVBIuLHIMagCAHjxbL6HHVV5zPY5kDeYd/voYqsBXSu8nZb1MHbOWHniahd7AlIqRoGT+sdac0MSL1fVeKT47F4om5QPX9bIl/rCqes=
*/