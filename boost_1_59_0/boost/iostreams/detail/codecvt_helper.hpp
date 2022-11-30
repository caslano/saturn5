// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the definition of the template codecvt_helper, useful for
// defining specializations of std::codecvt where state_type != mbstate_t.
// Compensates for the fact that some standard library implementations 
// do not derive the primiary codecvt template from locale::facet or 
// provide the correct member types and functions.

// Usage: 
//
// // In global namespace:
// BOOST_IOSTREAMS_CODECVT_SPEC(mystate)
//
// // In user namespace:
// template<typename Intern, typename Extern>
// struct mycodecvt : codecvt_helper<Intern, Extern, State> { ... };
//
// // Or:
// struct mycodecvt : codecvt_helper<wchar_t, char, State> { ... };
// 
// Etc.

#ifndef BOOST_IOSTREAMS_DETAIL_CODECVT_HELPER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CODECVT_HELPER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // Put size_t in std, BOOST_MSVC, Dinkum.
#include <boost/detail/workaround.hpp>
#include <algorithm>         // min.
#include <cstddef>           // size_t.
#include <locale>            // locale, codecvt_base, codecvt.
#include <boost/iostreams/detail/config/codecvt.hpp>

//------------------Definition of traits--------------------------------------//

namespace boost { namespace iostreams { namespace detail {

#if !BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1) //-----------------------//

template<typename T>
struct codecvt_intern { typedef typename T::intern_type type; };

template<typename T>
struct codecvt_extern { typedef typename T::extern_type type; };

#else // #if !BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1) //--------------//

template<typename T>
struct codecvt_intern { typedef typename T::from_type type; };

template<typename T>
struct codecvt_extern { typedef typename T::to_type type; };

#endif // #if !BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1) //-------------//

template<typename T>
struct codecvt_state { typedef typename T::state_type type; };

} } } // End namespaces detail, iostreams, boost.

//------------------Definition of codecvt_impl--------------------------------//

#if defined(BOOST_IOSTREAMS_NO_PRIMARY_CODECVT_DEFINITION) || \
    defined(BOOST_IOSTREAMS_EMPTY_PRIMARY_CODECVT_DEFINITION) || \
    defined(BOOST_IOSTREAMS_NO_LOCALE) \
    /**/

namespace boost { namespace iostreams { namespace detail {

template<typename Intern, typename Extern, typename State>
struct codecvt_impl : std::locale::facet, std::codecvt_base {
public:
    typedef Intern  intern_type;
    typedef Extern  extern_type;
    typedef State   state_type;

    codecvt_impl(std::size_t refs = 0) : std::locale::facet(refs) { } 

    std::codecvt_base::result
    in( State& state, const Extern* first1, const Extern* last1,
        const Extern*& next1, Intern* first2, Intern* last2,
        Intern*& next2 ) const
    {
        return do_in(state, first1, last1, next1, first2, last2, next2);
    }

    std::codecvt_base::result
    out( State& state, const Intern* first1, const Intern* last1,
         const Intern*& next1, Extern* first2, Extern* last2,
         Extern*& next2 ) const
    {
        return do_out(state, first1, last1, next1, first2, last2, next2);
    }

    std::codecvt_base::result
    unshift(State& state, Extern* first2, Extern* last2, Extern*& next2) const
    {
        return do_unshift(state, first2, last2, next2);
    }

    bool always_noconv() const throw() { return do_always_noconv(); }

    int max_length() const throw() { return do_max_length(); }

    int encoding() const throw() { return do_encoding(); }

    int length( BOOST_IOSTREAMS_CODECVT_CV_QUALIFIER State& state, 
                const Extern* first1, const Extern* last1,
                std::size_t len2 ) const throw()
    {
        return do_length(state, first1, last1, len2);
    }
protected:
    std::codecvt_base::result
    virtual do_in( State&, const Extern*, const Extern*, const Extern*&, 
                   Intern*, Intern*, Intern*& ) const
    {
        return std::codecvt_base::noconv;
    }

    std::codecvt_base::result
    virtual do_out( State&, const Intern*, const Intern*, const Intern*&, 
                    Extern*, Extern*, Extern*& ) const
    {
        return std::codecvt_base::noconv;
    }

    std::codecvt_base::result
    virtual do_unshift(State&, Extern*, Extern*, Extern*&) const
    {
        return std::codecvt_base::ok;
    }

    virtual bool do_always_noconv() const throw() { return true; }

    virtual int do_max_length() const throw() { return 1; }

    virtual int do_encoding() const throw() { return 1; }

    virtual int do_length( BOOST_IOSTREAMS_CODECVT_CV_QUALIFIER State&, 
                           const Extern* first1, const Extern* last1,
                           std::size_t len2 ) const throw()
    {
        return (std::min)(static_cast<std::size_t>(last1 - first1), len2);
    }
};

} } } // End namespaces detail, iostreams, boost.

#endif // no primary codecvt definition, empty definition.

//------------------Definition of BOOST_IOSTREAMS_CODECVT_SPEC----------------//

#if defined(BOOST_IOSTREAMS_NO_PRIMARY_CODECVT_DEFINITION) || \
    defined(BOOST_IOSTREAMS_EMPTY_PRIMARY_CODECVT_DEFINITION) \
    /**/
#  define BOOST_IOSTREAMS_CODECVT_SPEC(state) \
    namespace std { \
        template<typename Intern, typename Extern> \
        class codecvt<Intern, Extern, state> \
            : public ::boost::iostreams::detail::codecvt_impl< \
                         Intern, Extern, state \
                     > \
        { \
        public: \
            codecvt(std::size_t refs = 0) \
                : ::boost::iostreams::detail::codecvt_impl< \
                      Intern, Extern, state \
                  >(refs) \
                { } \
            static std::locale::id id; \
        }; \
        template<typename Intern, typename Extern> \
        std::locale::id codecvt<Intern, Extern, state>::id; \
    } \
    /**/
#else
# define BOOST_IOSTREAMS_CODECVT_SPEC(state)
#endif // no primary codecvt definition, or empty definition.

namespace boost { namespace iostreams { namespace detail {
                    
//------------------Definition of codecvt_helper------------------------------//

template<typename Intern, typename Extern, typename State>
struct codecvt_helper : std::codecvt<Intern, Extern, State> { 
    typedef Intern  intern_type;
    typedef Extern  extern_type;
    typedef State   state_type;
    codecvt_helper(std::size_t refs = 0) 
    #if !defined(BOOST_IOSTREAMS_NO_CODECVT_CTOR_FROM_SIZE_T)
        : std::codecvt<Intern, Extern, State>(refs)
    #else
        : std::codecvt<Intern, Extern, State>()
    #endif
        { }
#ifdef BOOST_IOSTREAMS_NO_CODECVT_MAX_LENGTH
    int max_length() const throw() { return do_max_length(); }
protected:
    virtual int do_max_length() const throw() { return 1; }
#endif
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CODECVT_HELPER_HPP_INCLUDED

/* codecvt_helper.hpp
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
*/