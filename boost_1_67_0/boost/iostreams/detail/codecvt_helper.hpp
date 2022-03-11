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
X2aA+jjP0XYPr5Blh5V7VsecbyNBmojWTHjGSLuRyjpFM2IE7eCGBaepvRWvjbgQTwtY5kEiDNB5MKZK0jn6FLJhkmWWj5T5wN6lwTH8cQqxI/M96zzDpudb/WfFTeUDu7qJNp75GCTq/C1Nnud6TSHH6Lul6voNDCcLnluXCf6LsMVnGuBF8nYzJaXJ/16r3Y3P4DthllXkAZbwPnwrI9LU8UwmbqZkXOPFXj65sco5LNFyBblO8hM1aplcpsUaO3LFtuKCzXnXI2ocBomMyu7Hjh/6O30SBt4j9Gru7L3b5yHfIcMbE3dUwUTMf+46Xprq2/UUnlj3zkXqG/plXqlGO3KyeJRSoXtnh8RDHTdC++bYvsNHmAPN5X75vfovz0x97uMn7mKA2xqfYPZpqKeYdA5vrbjwGo0IwP/+zsGW+nP8t5HaEC8oVCtA/PKYyf/xFbja+e5XcjjI8XHtSxqL9XfqlAydtO+x3QcltFx4CgzJ/FmPl9GX4He692NSN9+ZfhruA0a3EHEJHb3KZ3sMAZwAOS7T7T6dd4tvEnL05E0CSrxux47KiVkl9/eaH2xXeJ8e7IjIDqyk8qdrXBFL5PcWCFYLNl5L2v4YBgpcmRo3ITa0j8e4EKkNH4+l3RzS1/vj3/zpnUPgA5PvkR+bO+oN3TjVV+cvFk6mDUxsmGyNrnkgyy0fX2fp2ixI/EDmDzZ7CrQbrTT6Tu8wU80bZP23LpwzQ+6Qa7kc//y1XJq0La/0xWxvCd0rmvjqtxEe4+ePBBL51ePn9y7n5eXuo/4vx7vlrTtdmeszX/6vB+zNjNQPDfgnIafvS0HGcu5r6fahyqHux78c1u9HnJOkysd+/TX+ls0gPynpAHiAyqEnbr38zQfRO3YvBdjwSJsTtSrMfkelh4kiu0Kpkm2wapUgKJ+DtTFEjvqWZnuDko/bR/hbmSCv0e6LOb/Iz56PJIpdn5LXmJO2OgjWgTlvoRyELhQ+Qh0pUmGpqVL+ruyTOaK+KCTdg4G54jBBjUJg02rxpisCemIOie0oJ3B9THEdjLrObihipjc2xEZBSRYI65mzmRQ52A8+H2/0iaExlou3vaopPs7qxo+GsJ/WZ7COL9RBPHMh4SNIR5pXdaTcwpSQE7gL+56E9QzPoae4nHBGxZmpDmDLFV21xLiXfcqz6mKggh/XhnT8uimKf/NO9lSW5axcwI0zd6joWpsZBHy+yoULHGyqg0X9ey1NYmGUNAotI8VbCvLVBKd/nZFldo7/ueC1YM14JrHYvYJ5JTlrOOvX9fbQiSDDfRb4uxiBIDK8b2ivzVBMmCdkAcBGUooDXLecQ8GcG3FaxrwHCSd5ODFxsbRPEi+lapgWlumrpC1jaTMUeH6ITFHcMLLCnmVUTrRP0AYqcIIBBxdNZG6iofhhywIfF96VZpGUx3Z41l0245AOCAD7YdbheQ6tw3ApyLSs7lwkBY+vef/uPyaACX19NDicSPtaYX1EXe0YUCXWtAIVlHU4RIf2p0iZ97L1tg6t8Vs6LZkKnPfDX6THl0ahyni+xvjM545nv9tvOXarsvvRbPXxYWGExZyV4/sGuS8DV96GRiAcWLvGXYDLevmkh+rXoZAdmPv5BjDlwveFYa8IkeQRd/M46hGqNFYlV+OvN/cHcluQrQmPq3+F5fDdUI1YaCpp/ICSFE/TAaTfIlxz0JJK2BS/X4VeHtDD7/mhUtu9LTQJ5XTo3/e81ynPGnvUVv4KTgPx0qaxNLSVWefZWEtTqnRT9smYq4853k6Zho0+tmETsGj8K9AP/sCHrfwvxjmXGc7N6QYocimhvA9k91CZL19oBmuwp/6/dro3Xq5HbaXHT2BrdXYCNBoi+HmxODao9GQNrNSaBewen8QVL4j0im4INeDyrHQmuCkoHsCL5BwhGYoAdvDwAADAAP8BACADAPABhEsqEEpCCc4JzDUdrAhW11nq42qqRryFJ6uCVOtXW9LIaTat8HHzyAl/hZn0lQEAQANsAuJh5XlcSEnlxb715UJ6LIVmy++ZKjgpEl3RaBfnXa23wxBbXn3CJFhv3nKArr14k0ae1YSGQm0WSIcyp5O8OKfZRStftgwu9gvVjcOGEo2YVcWmxiTQ2ySC+AB+Afw9ERIAVTjR156bbpMTatep64mJoyrBffKTME1UAdSI/gICq2eflpaDlH/zCpY8lt6DzQBPHs4XE35uZzd3Br/jHQzJE/S5lt/yZ8g5IYqlGEirg7MtzeP/MXAU0IQr/QcnonBMfMNEXPgRDNpNRQQSS99Nw3B2puhsdmF5FfWxVS68pzCvLHe5ebNuR7KpsAB26QbiqmhQ4DTr/pb/A+LHnWe6dZJYFl3PAN2j3/8fr6mY7RDAETp5N9DLrDcFVrZ6XlbHLko64cb5gTF8lPdyZ73tQWXIQ68xd9Zel3z7DcOw0vgXG/uw6BTVyoaXcmJQ4efHIFv1ZaRr39hiPJfFvH66wjolk6rulRkWtuLCDLrkmDZdnm07ae8BtOLVLfjPe6HPXuwSbXuj+0tkpcN/Md1VqdCJoZeZdq/BxUc4JIcMeL6+ErKHXpW3Ojnk+xiI/TY1PyBkMkqAL7U7vPiMA0PymXOyLnh2vVu/qurTY+93/wCWw05u2YF7KMXag+p976LmUPt9glIboBqHnKk8kKxqk/cpcqVnJxG2wmg4BCc5WCVXsPBrGgwu1s/LKj9OUXlUNof/yYbpHmcb5681GAyfsT90Gm+gM+C8oWezELfp/BwMWs80JhcLiVgBK+J59kCyWczvJkC6WYp9Nz3dwvVmQShIcvD3S5M/8VpPnDCcRkV7ElimgmzUeoM2R8hxCt4Lb47sKsEl4V1b2BvxwvlRvMa9GhgvZCPWMKlZPuA5iSUmIeiLJrpNX8hJe47f438QZpN9vBETwmaps4HlufDDBwO4t2K/eN3ybI+/jbuv9iTyceVui26lIElCPeoTweGEhJY+DCqO87i+m1JYCsFkpXHQ4sil0oxp0DkIdV0CyW9LUugQGL3xIlfp18s3V0uiVy0jtOp2zTNFKSbr5bLwbe1liax5JyqPM7bvNy4XOmZVJOW6oE8/rrJGrq326xKmOSDF9RStL/8a6chem25QfalD5W/zBb+eNN17MFQyOwKxrxqwKf/UR+QFl1dlNyZ8Qhidhl5cX5XcCp8MfWxdV3i/8Mmlz1Nicfj0VPqDwSQ3GjYZh8qjTByaAOI8ESyeu2i0rEdlM0bHa5y3v8q7EZ9TrF3d3l48ldrIqFPndzEi3gl5CwajFCDbW5uHp7SKI00GpWUBCiZg0mcr67lMgpyt7oS/3waUY53iuhffc2j6agOY/5DUsWhu/Y7r+OMaOKK84qGrN8IDGiPnsBBpGzuMZJ3IqNMJRiA8mCLrgyYikG5/pdR3eJ2qM6ic4QqPlokfevlAZrv6ncW6ZhRGDuj97ELwODirEYdgZ5ALMvaG3jlvEzcwsPcS7h9XHVnQ9fO68lrhw0jWELtEACf7bqNaNpLZJuggWFznFbIxLq3m9BvUrffphXjdEQOdParVQ8cgbvkoUsd0SiRkocQbr3qiS/do2DrHc9GuFtQJ04zkUdu7Gl6qOCkRYLw7RyWkcqTA+zCzkKVOkhIPuUVjycPII8S71WgHsF9ORuaSGdgill9Bl8GYnXbGXvieYRbIyNG3BJbJeZv0snV7hTHMvBKqPzi6fOQ2dkSiWp5Y3nDzNpw2R+Jlo/GxEMJeD5PSTANqSLDgK1d+gSxxH3ZlAoYg9M+rdl95Z7LNzYIgecu14OrGjAHzOsnMRN5i2r30hQ8M+Sck+4TtIrAw2uQVh3TDZmLF+LvK1TnADQotC2d5NKMNwL7J0qSeznIJvYnrOokR6OHOmeHAdDEmpaEonagaxaFHPaIv188EQUFAoLmmLxQ7jrf6OyRKJSUZGkpgRuXeREYljWW/rew2G53uU7gzNnZZL2Mrge5aGhab52lI5F9VHrAvv+D8lkUFr0zyk9ru2l0bwMRb5IIcVnMgxw+l2I7X+sMc6ycJSSV6UBZQgM9XzCAdKZOOkM7pY41mrZeY4DTPxdKKI9SfbnY1kOOa/mt+DleJMunqlDrCrSSufZiUstU3Yu7jRvmsHwnABT3z1wu9tWpn2w4+iDSXjV7ZFpcIF40ARzZma0SgFZKL56EXgfmIb9YAzI8/US2hX8vBIHxoKdq2O3RzLvDKxtLgtlU64SQrjmZJTKNBaanGUWMkxjVHaw8iqnEMtbEvsNZFkrGyA43ONK+e3PevX6L0c/EV8U+MxNNbwZEc8YPOSyr9kdfA0rNFzGcSvStAPOohPIc3du8tNWHB7pUyr62AN90oYfUs71+c5u9mNKVxxveWKYlRChNgoBNJ2CyA3ndAz/fuIgrOQTQvGHoQlESGqgi0qrAaqRJWFVsTHYy4KG+BB3tsc9FQxuGEgQadINJ+fNJ8vOvwHdO/UECa256962RqbE5jjjkwJbzS2lWXJ6q4V4esgIZE/NSQiLUHJhAsXjJYlCuUodEmQKqFW3d2Msu/pcBi/Py6C5eBnodpq69BS4OGHZW+/w5ltd4Rr4jWhls0PF6N4Al73NnNaSeNY/WW62clSD0KwSoDNn7g0eaUc45hYXi6vTNv8a/p5ukq3VqyL7HZkt+RHZXfhtgT88PFLhIfQzFV12zMMkxmiS+v5UEoMzE9i7Cl0vLPkaCgB7SM0NsloKRY6k5ADIbDSlR1Ucn6DgnItKrq86gJmxXvv+yPExRWBber+xIPnIBOmsixQ2edBsyGW94skjTk1wRIEHArWE21HhyURBi9RryXQL24GJBgnu0obthLnu8xktZluGU/UQkq92d3uAUWREeLemB0B/6seCljBW6rA8W5MCUMM5eN/GIOZcXo73e1ycfFUUBbKSGwClgM7hcUUuzgTEsMgzOdCNAXiudqbiRT5kbmaHHrnSmt4kQNAoOC1//QpxLQ7XigZ+EEPHcdkyHhpRYXLhT/GIkG6g6XJ2IeSjCJn4R04qEJyEWIRdxFy0SFCmSf++WMOKd4MtoztUtEMnWHgKZvoJEH8eAeULF/OOXOi1vx8mRjGXQXjlmkXIQKKnQAwMF2Syu6ZelSRbuuYECZ5JkeYvmwLuRKnumXTgubWPIJO0PEMRRAwq1O5fKiAL5JcC4tlVYSD9uj99LRtO+2uzoV6coS+bUflnqaRX/JpkwY8Q3Sj/NS5DW3HhHxJjOLWc2faQ7hmIczo7joZByobjvKPF7QxOHoxTTT2RzcjSOrdGZU/q+84XNma1E8rfplFlIhetoMuXCnPTM3g208djYWxBesHugiN5tsYOwsYS277b9VJ1SNOjxK/pKwV/VMKhL8LbjfYqzEB2mW2+h3/QWlwE5h/E87Ga53OHXYCilDX53zYMSdYQSstiEiqCfT2ttCdt7dO/JZAb/uVB9SqIfXE0d6ZUldk594BOP7Zp+R3xsDHU7bmt8YuRDvzp5agijrl5h2Zkv4dajf8jH9rSjDsddwy2J/oA46PHqOCZfpimmGStmq/cK6kMb/ZtA+6kRrCyEt90lg8/51JYqXiugDPTXsz/mcq4SvNK7ZAjglgOZ/7x04vtX9ABq0ct18FP2nIrWq7NYoQysFclDp/i1NSAyupQsjt6qK1Vtp6rmq4e2R3s92m/xDuVm7qw3TnJ624FZpvJxpLtOCkkZ4Ep+9PgSD5fIYnoZBhfghG6QToJSWxaNOVsRo/p2/8ygBPSG2hrWoe3GtZaRAOGYrMEi5zu2EgFiOPu7FRHmVia0JVpKEiexrzddGpSXUHA9NfbuQOd3OgCkUm6bFyFg6GXkOjIKpuuojY+wCp5S1Sp9ac01bKhR6KbvH7znBFh29nZnlbH+X2y950WQbeFdBz1w2MLdApEAx7PUhwyPLoy3sXlEhfvZ5PT1SnbAkLGM/NZSSE6UR+q+lKFJObWX7tLdPLnNIZOKwXrjYiWLVdSMSauUb+1irLGKsBEdrjvnc+JnVEqB4QauI4T0+tcumI4JanaxFq9iOSt50lOqS9Uz7HmL7DvH3DKF47hPnX5bliByiNaO2YxwPLys4sjv/1Fu7j3mVKWL4endzOtMFzXZ5m8NJde/FJDd4Q40ZIzRSjLMxpcfYz4XeQgj4HPPxpG0i2Knb2Ma5OyYQT1Wy1jQydNqsVKCy0gaMb1kuD0v1ObFQU4qnodJXNEnlKD1Cwt/iTU+iMr9h+dDkjui5+BD00eoCSRnE/aF1XIVQS8E4G3epyW0lVjNk0PBOI5UOaeM/a3dCBaEqiEivF+KiJybcrNpniBm3vszqPxBiZvVijkIuUkG7rHihBKzmn62ebJPegqPVE5cAkurqdv5naXxrAuK0vzLyX7+0TqXfbJJS+OSlhxXoTWdW5rJbAYAZsOfe8fNaIfMkqk0LOx/pqfpWyE5BRfqwUdaliIqUTFXRcBUrsebyFaNNk8Wz9qBXipQ0nsML26UfQ9V14hxb9q1l93Vx+Pflit04VA80XrIKiCA0ZSHlbgcZxzd841NDYaRoCCAVxjIGSnMqEyitlH8V6H9IVIsaTLvvGuO0kmp2IpY1P6dfkj3oDIkhKBxmFR+cabbOACS/svPMo6EbYiUic3Na9dSWNJcZhk4XUwITyr3p+LSk2h9PGondqfDFDgHH60mBQ4fe8p48a5ShdmL0VLMRSlaW1HV+xeMZdSdFb44l3wr0vPaFR1Ao5rbYCRz3cYcEbNmYrswvAAQs+9OR3M5tRPkYPv2fHrse1EfCjUvevyGc1K7OLC4zC4iWK1RykJIFXkc9sQ2lQRT9x1jD4zkdCdHEF7QM27WI7jVMwRxR9jQPJ9KIZNtx3BMOGhAlojjtRVXi5wbE3DRpEVWYMWrOktfOGwI0ph+fW/NODj7TE4ncXvoLUXc8wbcaC3e8c12CoUSoGpHDYVimAWxnCYJ0kgX6sh8ftrJI09By+N283zZN7z/OYYgWhQUeYFI1eNWmu3Iry1Om6hUG6u7kMvTHr4SEk8EwY4Xq85BIbdwG6I5bDvJPkUcbWvjMyMmErjPQGe1LiAQmZwNHmR33x2lienwcIzivX/2SDYy4JqIRD361FnGqtOIdASROr+0nhaUPBoMYgFNuvkF1aQ2gpag+9TRz27hD4lEOLNq1peMm5pcmiHwIeSQzxg9ifkq1e+O/BJeBt2RNlffbrDpd2rx75RzNQdSjjszVYU+DH6UeexGC0jGkwHuV3yf4GghI+PkepDnTT//lrhlQChhcanf8Pglrt6RAYMh4lZFZOdlb6AlLQ1Y/BLgu0Te3z0OABpWdZIkZd8DYgtPluUrE/wQWpYJyxsG+vLqhNdtHiBz0KA5mXQ97kw8qctsHoKDxpDG7Q1m5INSXk5Z1uUE9HUOd57A9ez8UokMgV+++j0qScaUCoo8jKdAIGd9ZRstNDRrVaQoXQ7H5kl0KDlCSfXNXLrNMKXDgJsRdRRvqzQnunVb1S2NP6StNhN9+bCgq2IJxxXsTEtzmPV/5yluycWELuhWrZYWyJ04cv2c5GTGnb7L2Nto90bTCWp6pUEnwSpBuzW0ghfhNX5S3WSmgNv5MAcDWaJmf1XHGbOu7F5we4WN48a0Uk3cGNdItVV52s84r4iByo/UJ6D66LGa2GOBq+wMljkwW+PVkR/OYaI6oMg4VhiWAHAQrRLVdHqiNwCwwaAXs2tOTXVHoONG5xgHwz9GfWk6wtpQ3sTNhMd3uZx2fXXuiNIzIhcP1XwGKv5TXVA6xTZODlqfKlSpOB6sZ37OVHJTGPDR4ileYTciNSIegeg27fva464QZtftyDydImr/h9snFeHxGlwdS6vssdLcoizAtS2SSJ1Lxpt6hpVDNWKFYdm5Oyfguo2gPmYsc7wmbVrxwVDDsiy02txmXFD+dQd8pMLikUzlmncmq1TvqraNznWaz5mC5T3M3ZRGqBMnKjVftz9EnX1KD5U9EEOAIW1Ozj5ul2t0hS4uiQsyRUlQ30wRPozB4cNFIjEl/hl8wOjhS24CZZEF4zvCQQI3I7h60r8bpIFSt67fPZ9SVLnTa46CfWJ8qDrXBNerRpCfYo0axeWq56Pbos2hHD+RhOsS/XyDzaGeROU1Yz9r2BGbm+Y6VJFxUWLnElUeMFenHjTeZP3DO0TScH4ZcGT/aXcsjmFyte9tWapw1LGmBlN2OzMeVLav5mIZoPpW2bThLsaG8p1rtiKeBi3dJn85Idd95WL/rB3BkDe/L9Di8cBWuVxmeQ8MKiuxv1hK/UPJkZxXaNfqF2RZF+e/BkDMVqHSPE+pOf8aVl42reQoOMk7ZT12MuvwHmsha/AzMizjglMYT+NJvbZBA06NCwqm8OmA9IwXhKSKd+cL+ipkLwQVdn4nNd1oloGEyZEw0j845PYqgU2Okmc3QdaygSGHQGXxIBMPCT75m/qqzObnhvTtFJvq1OA4dGFOhfupK2tbcMFFm9hRLEMwVJcLeM/Wv1te0L6xiJbKs+0rz47+oLRsHVlgEVEk6fdy9STBLCFbS7NcVbGdA2OBvf8n0zjD2dFyDAkRwtgOx1I99VkNBQc1ytIwsoWQM0gJQVw1fBRYhSiIG5J7/RpJb2rGh5RoSaDSCw7+jZc+0RJ4J6EkoDpINKWKMxLZ9wr24lN7LTS1LDE+txV1ighWNr6CbfHNkW/aGOjY0Tw9XEHBJRDvpu8FuaUhHO32NhMhGaZNSjnf0FgU8SKw2TjBfPkCr5FsHnF2FVcfIAYdIq1bHqgQUZuV3Zks3dtwwTMKzkWZIDB01a+f/m19EOfU6uAWcp/8EqJNCrfcxmvgBtTVtTgCMl3b9h6Wxun+BBOVsvbJTiVXr1TA6fiB79IFvyq2J27Tr/PnxiVZnUhKNCu5nLIejWVMyf09n8x7+5Njig2kq81y6Lo6fQExn0iOKHbvzcRB7FMbQBTrmuJa3yrqB5nS8j2x2BJJ7dFKxLkLCXY2BwGxUAczIYgz6y69IcUsezOAkKktnLAqU/6RY8kG4xiXVV4s+9SaGzaTuxmybzL3P+DFs5BnJ/CY4w6XaFTTSROXxoGR1wC+Y7e+zn2NMlNUAay9mXeiP6N4s/UANE1oQiXQMZ+0oCkfMH0Hyks+vhj5ZBqxgFUJXy3vRP5wRdQqLrqI3idS6fRniExo=
*/