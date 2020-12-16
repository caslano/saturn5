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
/+ROtkyYi8Fze/L/Z8/9f6ut/ef+U0e45CUMuZS4919dMgfar9OEHKLJyZ5b8fwr7xpuvOlq/pgwxH8GbAAX23PcpfHOzcybQJZK5tDo/OHOT20O7R/KbyP1rkQZS9iZ+lwabrq9cpkzNX8/A7/G+Wf3eq+usM/XdMe6MtTvsaa5VuLS5tb8gXMpNVW4H9000VvKcL41Xgda6nys53FroHutx5Ubv2XMI139flCbu5vupvM0da6v+30J5Zdf+vUY73DnXfPV+fNJd12rHeKMnbyt3KPc+eAG6vcXzN9Ow49zXfVpXTfMDOUnyx3XeU/9bqF0w1+J91e7nhNVPQd/A5J6E7cYw5z9MdxaeEPbrTbbQ6/6PoaqvpOa7ZuHtld+9wu2+4fL77j/1OMrWn6z55aRQ1peOKnq9sTN78JVf+c1vztX3Z54Ve2nm+2YV32MIpR9fOfdVrVj0r7tCHq3jRNbWHVgGExwbfDJ/S3tF+ECbPClyLtdMxgLW8IzYAeYDjvBXNgZ3gq7wCdgV/gX2A3a7eGZcAPExlWF9q2cfksDxLFPtQ7ZhuxC+ncJw85UWZtSoxG9j7Mdcew+KTtPiGPPKQ9ZhdwnfaBDyAnEscnUE0lHFiFFiGNP6UhQXykPWYWsQzYiuxCTbaMMJA9ZgqxGNkgf6x3kGOLvW2pvqA8yCxH7QbrdIPpgZe0BZSDBNn/2BfXT+iNpiG6TZz2yAylG9iOjKdfcLtX9t+qj+qg+/snemQBYNYUB+N43byrTXjPTSFKqaTEyqTRl2sNIMpQUpW0mDdM0zVKDUEjZByGE7Nmz72QPkSVkH2QP2bP77v/+e959rzs0TNnuz+9zzzn33LPdN+ec/5xzAwkkkED+lvE/3/OrnbX/P7agP63j9LE6aHs3gXElfBsen87/zHPH6RuPz7vouPLlEwjDFwvCnNK7Gytz5qNPoPXtftbe6Ol2H2sXHTc2kvhWJ3SyKuzb7PbWt2hWqL11BHov+gs6IKG9dTT6aAKrxXQsHZ7v3LfYTma1wyh0Efoq2sruim2si1m7sovEf4ldZm/t/y3ReX5rq/3nCTQsbu48QUGRjEQ9305uKWEeSbgtIdFvfsAbh+6VmF5eppG4Y/zbpPy6hty1IM3lnmcSvrA7Wd1Dnaxy9A70e3RXSu5w9IGEkN833uLzh5RRVZzzLnUFxX9CQh0sU90o3XHoieht6NtoQzsdG99o1hvtaq2xszkfOtsai16EVqHbJ2R55iIqzPg/VeJ9OsFvnqKD+DW1WmsdtZPr28nBPPtkO8FaQj6v4s5mEt7WOjwSn3LbXat2g5RRgimzDAlzoh193uFm/qK140cJLSOXnnKosJCu7rpnCVOcUMSXu6+yO1ofkoYulG8hegO6Ht2ZNqjr4TVNSX9pfsO77jzVO7/htit1b+LuITFt5b819/GizH3Ma3N2ZatRZz+S9fTVl52w9PKiYO5jc8x9ZNn6m6C/7cuh91z/NJ3D2BY2hl3gLjADToQ7wlNhV3gX3Am+BzNhU+LoBvvCnWEB7A7PhD3gItgTXgB3gTfIXIeeFw8fgH3hB7AftEK8l7A3HAgHwcHwSDgEHg93h/fBPeBjcE/4KxwK6yVQZ3Ag3BsOhfvA42AuXAD7wuWwH3xC7eLPw1HwFb1+W6+XBHMy/+g5mVOC+ZhAAgkkkED+AbLZx/87Ozp9yqRdetSK/f+XFpbZ571M/5Q63zzKhg/Ck9NxP1bH/zuPlwcz+yDJkb3tnnGx5dkbcsZxzj0r/cbfxKfjU+94WMfCqxnXrRT/u2137PiEXNc1e11PlbgriLufutnWEnF7DIv2cN9xvD4Tt36E1zH/IWVT+V8=
*/