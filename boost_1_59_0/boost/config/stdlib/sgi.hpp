//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Darin Adler 2001. 
//  (C) Copyright Jens Maurer 2001 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  generic SGI STL:

#if !defined(__STL_CONFIG_H)
#  include <boost/config/no_tr1/utility.hpp>
#  if !defined(__STL_CONFIG_H)
#      error "This is not the SGI STL!"
#  endif
#endif

//
// No std::iterator traits without partial specialisation:
//
#if !defined(__STL_CLASS_PARTIAL_SPECIALIZATION)
#  define BOOST_NO_STD_ITERATOR_TRAITS
#endif

//
// No std::stringstream with gcc < 3
//
#if defined(__GNUC__) && (__GNUC__ < 3) && \
     ((__GNUC_MINOR__ < 95) || (__GNUC_MINOR__ == 96)) && \
     !defined(__STL_USE_NEW_IOSTREAMS) || \
   defined(__APPLE_CC__)
   // Note that we only set this for GNU C++ prior to 2.95 since the
   // latest patches for that release do contain a minimal <sstream>
   // If you are running a 2.95 release prior to 2.95.3 then this will need
   // setting, but there is no way to detect that automatically (other
   // than by running the configure script).
   // Also, the unofficial GNU C++ 2.96 included in RedHat 7.1 doesn't
   // have <sstream>.
#  define BOOST_NO_STRINGSTREAM
#endif

// Apple doesn't seem to reliably defined a *unix* macro
#if !defined(CYGWIN) && (  defined(__unix__)  \
                        || defined(__unix)    \
                        || defined(unix)      \
                        || defined(__APPLE__) \
                        || defined(__APPLE)   \
                        || defined(APPLE))
#  include <unistd.h>
#endif


//
// Assume no std::locale without own iostreams (this may be an
// incorrect assumption in some cases):
//
#if !defined(__SGI_STL_OWN_IOSTREAMS) && !defined(__STL_USE_NEW_IOSTREAMS)
#  define BOOST_NO_STD_LOCALE
#endif

//
// Original native SGI streams have non-standard std::messages facet:
//
#if defined(__sgi) && (_COMPILER_VERSION <= 650) && !defined(__SGI_STL_OWN_IOSTREAMS)
#  define BOOST_NO_STD_LOCALE
#endif

//
// SGI's new iostreams have missing "const" in messages<>::open
//
#if defined(__sgi) && (_COMPILER_VERSION <= 740) && defined(__STL_USE_NEW_IOSTREAMS)
#  define BOOST_NO_STD_MESSAGES
#endif

//
// No template iterator constructors, or std::allocator
// without member templates:
//
#if !defined(__STL_MEMBER_TEMPLATES)
#  define BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#  define BOOST_NO_STD_ALLOCATOR
#endif

//
// We always have SGI style hash_set, hash_map, and slist:
//
#define BOOST_HAS_HASH
#define BOOST_HAS_SLIST

//
// If this is GNU libstdc++2, then no <limits> and no std::wstring:
//
#if (defined(__GNUC__) && (__GNUC__ < 3))
#  include <string>
#  if defined(__BASTRING__)
#     define BOOST_NO_LIMITS
// Note: <boost/limits.hpp> will provide compile-time constants
#     undef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#     define BOOST_NO_STD_WSTRING
#  endif
#endif

//
// There is no standard iterator unless we have namespace support:
//
#if !defined(__STL_USE_NAMESPACES)
#  define BOOST_NO_STD_ITERATOR
#endif

//
// Intrinsic type_traits support.
// The SGI STL has it's own __type_traits class, which
// has intrinsic compiler support with SGI's compilers.
// Whatever map SGI style type traits to boost equivalents:
//
#define BOOST_HAS_SGI_TYPE_TRAITS

//  C++0x headers not yet implemented
//
#  define BOOST_NO_CXX11_HDR_ARRAY
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_CODECVT
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_FORWARD_LIST
#  define BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_HDR_MUTEX
#  define BOOST_NO_CXX11_HDR_RANDOM
#  define BOOST_NO_CXX11_HDR_RATIO
#  define BOOST_NO_CXX11_HDR_REGEX
#  define BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#  define BOOST_NO_CXX11_HDR_THREAD
#  define BOOST_NO_CXX11_HDR_TUPLE
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define BOOST_NO_CXX11_HDR_TYPEINDEX
#  define BOOST_NO_CXX11_HDR_UNORDERED_MAP
#  define BOOST_NO_CXX11_HDR_UNORDERED_SET
#  define BOOST_NO_CXX11_NUMERIC_LIMITS
#  define BOOST_NO_CXX11_ALLOCATOR
#  define BOOST_NO_CXX11_POINTER_TRAITS
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_SMART_PTR
#  define BOOST_NO_CXX11_HDR_FUNCTIONAL
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_STD_ALIGN
#  define BOOST_NO_CXX11_ADDRESSOF
#  define BOOST_NO_CXX11_HDR_EXCEPTION

#if defined(__has_include)
#if !__has_include(<shared_mutex>)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#elif __cplusplus < 201402
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
#else
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif

// C++14 features
#  define BOOST_NO_CXX14_STD_EXCHANGE

// C++17 features
#  define BOOST_NO_CXX17_STD_APPLY
#  define BOOST_NO_CXX17_STD_INVOKE
#  define BOOST_NO_CXX17_ITERATOR_TRAITS

#define BOOST_STDLIB "SGI standard library"

/* sgi.hpp
kl+dY13N/pdZV6/lvLQJmDel0fOOcgiyDdl6EWx3MVX5X2Z9cak1qP8i+DEGTH1lFw6TukLHDf2+/B73X2bdnjAhxCGFnzlwI0rwS4hjBtmLLscsNepQvbRBpmun3EcDJ44vrIOuf57pJvyXWf9yRFvo/yX0yYzPzvWTkqiXsq5lqZpfsSht+5cMOelBN79SLBPC3GsYXuJ63Otax4Jd63v/WtlWvPj78lfjpFT4au2sWfjvJ/Mut15dwT/lvHsOvCUPKws7wp8OiAb2PsWCzc+fDhFK3810k5pH+Gbzass9HWN/xag3zN15d0rA/yHCf+aTXp//nBoL6XHzBfW/gIX2eYXAL9ZLnoFLjq++N88+6fwe9Nme9TZoLTyxP3hdBacYssnd2B+yLTz77HK7cDciZLccxhj2qzbzNuSgtTM8dL79sth7f5Bm8ODkgzSL++GsOYvH0VLwj8PTH68e717tdiqLG5t9fe1msaedrlIjo8kDnLJA5L1UbvkUzXB0o3PPrPbCReMEcxNOM8KozV6KzEIhGJGQf6M4EdD+gyj2O3yYlnaHVla6CgnlOr60DCUZSVPMvZhhWoO/MqM7LPq+FQCYMMTIuLKS+GqrAQEi5AgnVjDdnCr9pghQZ4GADFISR51ngeHcViengm8iUuEYPs5mgH4AG6XHIoDPyojQYoGNplD7PQHjJxCSZ4S8MA8qbgxIN+1zoOZtGkVWqWT5qjswfcwD8hRHgx5tb9H7nmpJy/1JjWd0pCCj01Csas70IuJgVEFF82PWk9SMdEkMZAsgVVUc1DxADj9srPnOOhh/XEXQHwkxCth8gb+uAqpA6FmcovLwMSokFNxDkCjKDgDQsY03tm3btm3btm3bxh3btm3b5p+/OFW9yqKTVDqbznz5kC273FMgREPimKcI83pIwzvwHyhw9rRtC1C6c9YukWffbmLRshLoNUM1ya7ucROUnV9Yit0i/klGM+ftRbNTe8vZbJpMs17be/MCAwIIRzjkZ8lmnpbaEjJLukwEhFQIcjMePqiQSibQ/UqWvGEVJ3IYM8uoWsG+Yi18Zh4v0/sCYHphcTxBrtPv3ptnJqH3xY2o1CR2XFSRYJC1ya9O9Lwu/XUfeEvJGdcaz/Oi38YsavhssdSl5L1+cOkK86HEz9+LluxGxQlOQ5pdRS0aoWCzkHAErO0dSIzR8LGgcVc4rXXQZ/EzWuFY0b29vTLoLOhc+pxuIrB+6ru5GvG+E018wKkpeyFqcA+2gkTgV7netDdi2CEODBI6d7mjagB4h0TbW8vL9cYgS3WCNLU5zta1BdtXhVYxvW6e0cX1pEpl2ql2r3VDjdW7p1ab3GKyBtLJWLd8euylbomz9/wsDduccilHstDA5lFo1LPhG97je1XwCf+733bbFSvzaCC8AkP3Ob/JnZS7T5mwzZzWdMTtMf2ED96MF1IhkFKS0SkWc0P0Q07vndPWZTUQ8gtoF7vLVSKljhaUdfBL4mqJ+Y9n55EaYsVvFBWyG8uel7yvH6C21LDgrSwkVJEJC880gjGET+XIRnTMWKJw5XTE9Haa8p5haFCVAxmmlPM+X6vRBpuZaUjSjF6Sz0uMPNx/3xEeOPhRQhYInbMlhIyPZ/RO84GhLzPOjGMSl3SG3rK8M9IuBE2Otf8SRMH5EAjg7DkYcVG/eEfVLV3fxPxvoNmhGmifDbW9TqdWP+JIzCopo0ke4sQFG4FLDlclqvCpIb/51GqMlk6r8WHQLyXEZaFCBwW7tnMRasQwjLi8k92DD/yDHQdsminpPGL47m3IfdosOh+RRNs+iSly7Qg/Xg+Uor3Z3kOOSfPUJMY083kMorvzyNo5J7h4IGsOOyxER4oeWTyn3RUC3uLwEQJUsAajKmgqaSjWuNaHvkMeu2Y6wNM3pAKAoY+l/AccnWPFlCq/CTZRWoSk5+yB9UHPPjPbiUK9MGL6xiqMICBFZojLEfnLSp/xiAlxpvsh8BJGjhFrOWjULmGlKqiZiVPWWIqaW9bYnEDrG5WUixmTB83aZ4y5fctfg97Q+RJgRReKJbFLmyzSWqVj1juxnRtfl1PKfjdcCWnOwMPDCvydwWQUbQsRHRCUmasxacgmF3+TftNjdJF4iBWoe61ZyRrrm9awX17fz6PI5BFQglJOLUA/XDkDuXJMepXTcDJKaa9RoCKn0avXvC/UB4Tmc6NQqNi5vRZZDMRwnjB2b9RQbv7r8w40GC3Xts6htYkvCAjOZ1GzHLomhn/GiBhDSZ++Q9VXJrU/VqImLayL7pk3G0uAJfM86okMHlxFjuMlT4QrT9G2qek/irmFHEkgkW60A5e1jdLSoZby9CseHSK9CItO/sUxvfBnTfXjrO9N+kxdQGiwGzoQpZnz0u3mBiE0G7GXKPcGHAD0tnC11VxRRCayYW4F4OX/ZPu4wIZS7IoHdMPbq8296qfhlRn3t6v6isO+wkIEKCCz1gV55OHuoepycyO51zcGqNwcggSXPFYZGNgMW9akPeKfpQ7Gswb8rix6XyGxUMWnZZwuwXU8tuSZTzL0NMsxVwayhvduJeEeHcVznBsBBc/3yVfQr54pTkcVnYBL2gsOL1od5L02yZEdAI7S/+q7H2Ik2lAbZz/o0q3ofNsGHpbh0egirvZSpFtAbcPFpWumkRsgv4bGYxwF4sNXGbuo76lQdwpOVAQJFhQoiW++4xKPdinpkO8ajmet5W0Zxt2xjrL8XKMSXUW5HeK9oicEfpTQDzbS53UXdJrwgyOOxGWpj6N6BOBf0ZCPbl4KbC7EIIxlgk8P8Z8wyCoRC//y8WdWp0YK8mAtO8EEf/MfoG8T5ZsM6k8DBCccOoAmEscwL6aa6g48k3HekIQhXTUyxga4N4lfqSjSIq9IyrPmiU3hdrIzlg70vINZIBKueCLGxPYqPCqh5eHEhjSpbjDG1Tc82kOP4gqQC54wy8LHhYbF9hJZTSGKp4WXA6VNDKwOlVZAD+3zJlxAnwMmEHmXJTl49ka3ppy1iB6L8OtWcZ+kAE42pcqtkw+Q5ZLll7FMRGBJ4YTg6Cfe0N/yVlZCB/VYwmpfMQLglc/WDVu8Frsk5v1KLMbzygSm4oiFWIP2K+S3WSdjxdOrFF/Vkvg8UjkZrbi6aUW0lZCvBjbgNcRtmrtXL4cWlexTEDxLKDS1yarX5dsDQfg1F8zo1l3XzPMHtEPBXtQimJoGOIa3aKmKVUAJoK8BrgEJbovK17x0rw1G5vSYX/gPCPbjV6chf6RKKCh9qdrI4nGKafnknhZxLC4m6+GSus9KCdDf/osXCvFx4YvI0Pkuouqhdrwm1YCw3ERRrsudCkfXp8Ybmpg4QJdY95+VJPS8dSdanS7VycSOkyeZBRvt9G1SvmNJr0kIYF/BQPd9MgQAAkK3eeK8elrzBD6OstkcyQZuvaIRJ4aVRB3CfQ9ZtjzwNTn4nfViwZyca7SqBFC8oSG+v2/JAMgd41MpqWgV54ksdWa38GEA+BgF5GCwpZBdBE8sfUODfLGhXeluVqVD9au9DQBbjNajP6x733j46e9Bg+/ZeAcTJjAIxn8nybECA0oMt0+tAkZ7cF6u6XBB0UocTzuY8llE5yxwzgn9XAbBiTj8b2kB8ANka6eYDsun6UtiGxUVTndmExg+hsor0/vNillZQEfc/puv8OP+xH3GIGJj/nk7p7JsOFHxtutKBBf+pVMRr6GM6ABQEyBplsZnQNaTGed8G9O2eDSS+skWjcPi7SzNxdNyC0W4OjvND5neB3FJ8TJ2i4hphVrJ+6XhZvIoQ6dxPede5UBs7xHjUKbJP6W2itbv7T3HPg7rYtywIVSQ+kIGak1dF8jul9J91Qs0I7DbZlSNbTIVm8mUIY42//2uj+yk1G8zQfUN0Zu49H/E7BflWXwO5wLcndnIdCNMNHrzp56j8xa97RW/VR1P4dVCGhRICpA35p4eOB5rQpkBVyDfcgx02neQBb38s1GzvL8gV3B8UU2pAnUdcKd1HwBQEBu79ChrlF2tcedyDjwfHiiPmVPZbRMpsZi3ekzWfKRLOvF1guwceXQN/DehnIgwPzSqk1E8niG+EYI8CN/ePIea7DAA+k3EYrHI1PNVeIxnwwPvSGppjau8wssoEWi6InYJVM04HAJsg1VMHf2WXaLbqw4k/sR2n/XITpvIZ0XfaUlDH+/o1z2wBLpok7K3u+ARGOiIN4GNnZkmY7Q2XoUj7KiOsL6ZPpXHu+tLZwQhBAah01h10euCKUOYdinDQ3pv7J5X/P37+xuoAAAQ9Cf4T8if0D9hf8L/RPyJ/BP1J/pPzJ/YP3F/4v8k/En8k/Qn+U/Kn9Q/aX/S/2T8yfyT9Sf7T86f3D95f/L/FPwp/FP0p/hPyZ/SP2V/yv9U/Kn8U/Wn+k/Nn9o/dX/q//z70/Cn8U/Tn+Y/LX9a/7T9af/T8afzT9ef7j89f3r/9P3p/zPwZ/DP0J/hPyN/Rv+M/Rn/M/Fn8s/Un+k/M39m/8z9mf+z8Gfxz9Kf5T8rf1b/rP1Z/7PxZ/PP1p/tPzt/dv/s/dn/c/Dn8M/Rn+M/J39O/5z9Of9z8efyz9Wf6z83f27/3P25//Pw5/HP05/nPy9/Xv+8/Xn/8/Hn88/Xn+8/P38AFP/Of7mH97mwsDRpRdGMc1icq1/xb9OR8L1TI8aPdnvsR4EmP8CV03jpSu3LdqnMaxqUCiUpEzkxNL2103LksBHkMGCwMRT8r6MZXIoNOp+BCkKWJIeEOKGE2OkaqtwTDe+S5RsSFIJLw6bka+eYKms0HruL9xqpju32tfs3I15NFwh7G4nJpIGIvgNVX2LzUz8KH1cx0Z9Ac7qkweuKOIz56kDwefoDkklNDOsOywdIwGMvfXaFiaAISpV3jsxJnuA0ov17eBRsbaEW5kAvnCt3dtfpalWqmhSQ8j5SU+0ahrUJpGGvh4VD6HvQDguZR/r3XByGmV/Pv9YLgXSDnU0NIleHZw3oEWkB0Kuldrh2lgM4GlxIChVQVFo+zjIfnBXQjfI2XNg3k8o/kjXmduWVZgaYgpq+80YQD4RXBMpQ/aJRhIMxvC6i6hJZ0CPXzihijxu688D/fPcFeNUqr5fKgW6FhhESETGTdThLC0xS5oznSIPpdaE8DD/LQ+tw8T9pXOgn5OI45G1fXg/4ZmREkYipHuKVvfudROKW7E0QiwKkuQf4+Mt8/7wY3MnYJcHdrm8Xb9skDW2J3hUBWJ0CpRkwRdF7OOmcJYK45goMmWo0RsB5+SiCC65+sKD2GhktmlV1ge88QSaoU+hLlprLPKWWPQ29YCf/NDOe3eyikkT6Rk+orlf0FF0Lq3Lpyp23wg2hTsv8gN+VbOw+SOSgpEqwgY6rk2i2ERQBhVKuUt5tWgEuvkEC4TVpN1PpO1wA1eRylyPGCakpa5OVtQPn146KmX8hSkpZNxlBndyhTcZpRlY6pwPrMvcCQgVUHRITkoSZiLyXUPLHZqt4B8lIqg0FlFfxhie/T+ssPOLmqnBUNoAphq2oRthrKsDhE5ptTMB9tXyOkwZ33RFpAr2iD81HSjRQlamztkPIRgLZrjb0MXCtCkqOB+4iXP1uqJW4IZSGU1E+wpjtMzipda8hmCdR3dqwR4BGkQyRYjeSkvkvGx+YrIYxEOLEhFGgCUUldFiCWT7A9dcMVJ7j5umtdzYCcwT5lRUNM8Q0PbBlUp0Dzf/VraH8qumcLao2gT4Lqf04fA4MwlaytBVmp0RTmFQfJ7nIf75+C43dvq57B99dA+MeouHifiZFrHOdX6vQ/qNjXF7oFlW3OQX2+C/3/Hl2DMljCGjl/o0qH+w6zPnaS3ESiGsXDk0rl57OrdbDbSyTM+2Y0gsEyF0B0uviQwI7Nk+O597pwgmAO3r/RQp6aDlFskACtwxMjqI4LQ8EJ84VCz1W7nT5R93r9vm483pGBqcCJpQK0n/q8b9AVxvE6QU1N/T2JabhUfcC6vGpEbYIk1wAQ2XjUv3lf8WujJAh8p0HrgN4O081hSAAgZKbMGKIADKr6C5o/M2wIUE4hugP+ooWDuxCu/OKjF3YrflauS1ij9zC8W7tOiSINhRaerAkxOpxm6LaIHjgMYOJANwSuxHSwyPZLmYpQ2bJ2qbiIFLB0emICI2klF791g2X1DjXV6OE9T423F3cHpi4fmIoUwogH0suwbTHgU34cw/pGqapN69F6Eb+9NY9srhqYdunrbfVOuT+UIDa1Vmhk2quIdzU1+j5KHd1lWk6LxFfjd5fs3v3QZ8xHfCHTDwHPOC/Xf+F3bnJ3LOT5lOBKNXKGv2Cbo1xlzFH3q4sfdomp2h8F5pj59HTkURzHb+73zHZhjNk9piQ80K5PkcfUypyEhu+MMZygRjiBQ4yJ4qRhQrzdA+k6w2ThxGz6g7f6pa4hBJbhRj/QEh4YSXmYiSWoH583bsQ3lCSUTKfyoj3vLvk2pvvb85N7TWd1iMI4wJwBCBOjpwtjtw96q8p9l2M4Evkoeup8ZuYUpPTSWPjxrR10DL0BpgaIDTh71tOdaqxvYXi/5dXf6EBkFhXbUpffbQPq4DUKanrfFgFhQCfrkQ8w1nX8zENa84dqsjl6f9UesCIDW1kZEQFDEhYXzdAqbEWJnH7obctHzuq3DexwzPMXrQnVGdbOHYPAcB/JWRfocqOT5d5Y/xTwDB6oCUdPdw4vN5Gce433jgOEm5GRf2rappX8+Me+un7ZR1DGn2rBmEjYP4yeLlUMldzeFk9NHddthoCT6Tn07aDFLvlg9n++PKzx25Md+H7K3R0svCNCOP29vaTjqU25CPzmj2meDkMHlUe1RpgQsDOCY5NzHlxIjH+TJV9rL+ECmNbcAC874IqMTDSbzCFtBxaLQQZTG3YviF69grJ/HUjokOoJXQuXlr/yj2LZhkPyJBuABsdQV6u4zVvOR9HuSFAaJYwaz1RwqHH4GKUlzbmXSlIyPKxpNh3JZCr+PRTUIKLFmdgMz8DmwIu2QXJnSRK0kt7B7tWLbNyxFTasXBMxH5qgrN118315n7gdkHV56k1JQYk091Lpjecp7yPIBi9KQ3Zz0X6O6fXGM8lPsXX+y/I9r5bAy/ndJDO2C92tN6hpwsL3grv+2Gmg366T+2Cvujx/kj2VzJsxdKvaYNj0TL81nQQWrBs1+03ZXeX1/Lph+z19U6r7NeBWKn2cfxEHG5yETAkq/H7XY39k2gzpgpmIHRkvTmgqnRRSjAxaNRFgQJMtMK76QxZ8NRpEqdU3bD91840x5UpnSSCxMQ7xpne7kiMWABMTuNvX9/FU3BLjGUqHM3lHRfngT7ShlicRvVKhQqgHnWC/ZCPtcbhZdM6zexUoh8xjzbLcN52rKBeRm+STn4h+1CmywkwwggDULyhYZKUg3Z1QvV81nZCfZcdc+wlPW8n9rDQwp61YDjMtnu52EmbWddtn/WTTO8nJr8UCWmRQFXO5Vw9foauot+p9H7F3Wn92SFLGlYtW90iMSF2nFnmaqqFmzHt6OR+T3YxR01Z6aP/Cb35xv0Z+cnQ2xwvAWHZUp3vKGC5RUc3KnoMDx2EedTqvXr81TPN2WfZZcBdX+mERRK8SBVT3ItQrMBc
*/