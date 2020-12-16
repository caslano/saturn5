// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2004-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the definition of the class template 
// boost::iostreams::detail::double_object, which is similar to compressed pair
// except that both members of the pair have the same type, and 
// compression occurs only if requested using a boolean template
// parameter.

#ifndef BOOST_IOSTREAMS_DETAIL_DOUBLE_OBJECT_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_DOUBLE_OBJECT_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <algorithm>              // swap.
#include <boost/detail/workaround.hpp>
#include <boost/mpl/if.hpp>
#if BOOST_WORKAROUND(__MWERKS__, > 0x3003)
# include <msl_utility>
#else
# include <boost/call_traits.hpp>
#endif

namespace boost { namespace iostreams { namespace detail {

template<typename T>
class single_object_holder {
public:
#if BOOST_WORKAROUND(__MWERKS__, > 0x3003)
    typedef Metrowerks::call_traits<T>             traits_type;
#else
    typedef boost::call_traits<T>                  traits_type;
#endif
    typedef typename traits_type::param_type       param_type;
    typedef typename traits_type::reference        reference;
    typedef typename traits_type::const_reference  const_reference;
    single_object_holder() { }
    single_object_holder(param_type t) : first_(t) { }
    reference first() { return first_; }
    const_reference first() const { return first_; }
    reference second() { return first_; }
    const_reference second() const { return first_; }
    void swap(single_object_holder& o)
    { std::swap(first_, o.first_); }
private:
    T first_;
};

template<typename T>
struct double_object_holder {
public:
#if BOOST_WORKAROUND(__MWERKS__, > 0x3003)
    typedef Metrowerks::call_traits<T>             traits_type;
#else
    typedef boost::call_traits<T>                  traits_type;
#endif
    typedef typename traits_type::param_type       param_type;
    typedef typename traits_type::reference        reference;
    typedef typename traits_type::const_reference  const_reference;
    double_object_holder() { }
    double_object_holder(param_type t1, param_type t2)
        : first_(t1), second_(t2) { }
    reference first() { return first_; }
    const_reference first() const { return first_; }
    reference second() { return second_; }
    const_reference second() const { return second_; }
    void swap(double_object_holder& d)
    { 
        std::swap(first_, d.first_); 
        std::swap(second_, d.second_); 
    }
private:
    T first_, second_;
};

template<typename T, typename IsDouble>
class double_object 
    : public mpl::if_<
                 IsDouble, 
                 double_object_holder<T>, 
                 single_object_holder<T>
             >::type
{
private:
    typedef typename 
            mpl::if_<
                IsDouble, 
                double_object_holder<T>, 
                single_object_holder<T>
            >::type                                base_type;
public:
#if BOOST_WORKAROUND(__MWERKS__, > 0x3003)
    typedef Metrowerks::call_traits<T>             traits_type;
#else
    typedef boost::call_traits<T>                  traits_type;
#endif
    typedef typename traits_type::param_type       param_type;
    typedef typename traits_type::reference        reference;
    typedef typename traits_type::const_reference  const_reference;
    double_object() : base_type() {}
    double_object(param_type t1, param_type t2)
        : base_type(t1, t2) { }
    bool is_double() const { return IsDouble::value; }
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_DOUBLE_OBJECT_HPP_INCLUDED

/* double_object.hpp
z9b0JaFjLf17pvnsqvW9k9Z3b01vN5gBu8NecBdNZy9NRxYcp+HdeqrS56X41NPF+rwlWq6XaD1dqvV0GZT+icaXa2kfAHTW+OqiQzS+tlq+7WEd2EHj6QhbwE6wA+wMO8EuGi951L/dlIHGa6PJGm8bz/PnaLjuPs8v1fyUaz5m6vNnwa1hhdb3Efpez4ZzEqzftcvfyv68leg6tEG/RCsDHYa6+0KzsNWPRsvQePv9ethkuL8df/Qf2PI3wAb7RGz6Gftsml3/Tv6/Cg3nYmtGh6ALcJ8KF8EKGG/vX6Y2/2dhNlwPXdt/2r7V2/8r4tYAXAcfQf3WAtTbL7IeoBMcgFa3LqACt8XokP74wQlwLfRbJ1CMVqK3oms8awY2jPj9dQNpI4nLcYO5qLuGYOrI6DqCOSNxQyuoZ3dNwa0jY9cVtNn/99cWVHnWFySPiq4xGAvnoEtQ73qDNdWsOWhyV/XrDkbjVoEuRu9Eq1uHsA43dy1Ce3SYrkk4JW5dwpLR7toE7uP/16LxaxSsMZTbc2FZq9CJ/89BJ6DPOuHgYrRqMHFTdpejy9G1aLh/otUKHYDmoXPQJeiK/sH+10ACCSSQQAIJJJD/i2wx+z8nAteG/d+xw7/i2Bjk/C+dqi8ZLwsBGHsa/+JY/xLSNr2oNGJ7b8vcVD+dAy60zdyvSDd3nj1i79xtv/0iR6a7MZEY5zFmLngrYpnbxNE/nu9353Lr2dXNYVY/V7n2KZmr/Oa5qz8+YWH5wttSv1yx/XVLq5/z9J/brG7OsPbOS6jpXKI7RyLlrfWQGTdHsr3OKbhzGelwW9gRZsAusBvcAZ4CcwckWsWod/3+HD3H1Htu6YfoKXouqZ6DELs2Xsessece6JmgnjFino714s8vqBwQjKsCCSSQQAIJJJBAAgkkkH+ObLnx/yF5tTH+b6br9MfK+D6vfNq0w2VM3y4tkpdbgzFXIIEEEkgggQQSSCC/sXcm8FFUZwCf2d1AgAAhhBDCfSMgBAgQ7vtGDIeAgBIMASJXTCIGvABRUdFSPAqILbaiqLSiooLFSlU8UVHRorU1KioqKiJarKj9z7ffvswus2Sj9s7w+/hn3vvem3fvHO99r+KoOCqOiqPi8Hz+P/ef/Pw/f+Z0KI//P+rZn7X/sidf8WLn2Z8Veuz67KzYTFP3i1zueQtm5hbjloTfG866/1I/cQuksCeouM2fiZrE/Wf0lqrb9JyF5y8oEndZG79S3M06c7MP2Wpxd1a45c2Yxx7wM5249B3FDeJn1sFZaeq+ttSdxZziZ+wLbFjsbV+gkeZxo/gHS1c0pGjFX/Zj23ex4+94UHTTi+Y4m7blzQymaQ/5698nzL6BsVtw2+LY7Ba0dO29uNJnceDu2pPuZaess0vXUZ5OSxk/fnRMcyNCax+Pa7yZqtDd0r0Js73XFrrnY7RK9VzPqEf09Yw3OIFd6xgG6VrAJjPKXs9oETYfkfWMVrUO1dqynrFVnFeaZI1iLGXRIVQWuiZ7KRHVgXnwacr48BSzRtHTNkQNotrr7NM41dE72x/a27+GnLeh19VEJ7h3eJuzHLdiPbetrLNl/bnX2lyu67mm26xzXDnN8a9n1moO1nOvNd8mLmN/gpx4255w60o/taSPBnVLyKfZG50+Pj1vZrHlStN1kj+fsTnwmpTBhb7tts+9L7spj42i3xL9YHncKnm4z+5n5dtOue7jeqvFrcQ24RlFa+ia7tvFr7Eta7xN+HvtOHHr64w9HDSlGfOmM/pIHg4SZ4qJi+a2YGFRyPhIiqbrekn3I74k63mrht3CFndcfivut/taWS+wr3S+nUQa9xDfL8T9dV8NStu1lnY=
*/