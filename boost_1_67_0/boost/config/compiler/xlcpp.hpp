// (C) Copyright Douglas Gregor 2010
//
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  compiler setup for IBM XL C/C++ for Linux (Little Endian) based on clang.

#define BOOST_HAS_PRAGMA_ONCE

// Detecting `-fms-extension` compiler flag assuming that _MSC_VER defined when that flag is used.
#if defined (_MSC_VER) && (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 4))
#   define BOOST_HAS_PRAGMA_DETECT_MISMATCH
#endif

// When compiling with clang before __has_extension was defined,
// even if one writes 'defined(__has_extension) && __has_extension(xxx)',
// clang reports a compiler error. So the only workaround found is:

#ifndef __has_extension
#define __has_extension __has_feature
#endif

#ifndef __has_cpp_attribute
#define __has_cpp_attribute(x) 0
#endif

#if !__has_feature(cxx_exceptions) && !defined(BOOST_NO_EXCEPTIONS)
#  define BOOST_NO_EXCEPTIONS
#endif

#if !__has_feature(cxx_rtti) && !defined(BOOST_NO_RTTI)
#  define BOOST_NO_RTTI
#endif

#if !__has_feature(cxx_rtti) && !defined(BOOST_NO_TYPEID)
#  define BOOST_NO_TYPEID
#endif

#if defined(__int64) && !defined(__GNUC__)
#  define BOOST_HAS_MS_INT64
#endif

#define BOOST_HAS_NRVO

// Branch prediction hints
#if defined(__has_builtin)
#if __has_builtin(__builtin_expect)
#define BOOST_LIKELY(x) __builtin_expect(x, 1)
#define BOOST_UNLIKELY(x) __builtin_expect(x, 0)
#endif
#endif

// Clang supports "long long" in all compilation modes.
#define BOOST_HAS_LONG_LONG

//
// Dynamic shared object (DSO) and dynamic-link library (DLL) support
//
#if !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32)
#  define BOOST_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#  define BOOST_SYMBOL_IMPORT
#  define BOOST_SYMBOL_VISIBLE __attribute__((__visibility__("default")))
#endif

//
// The BOOST_FALLTHROUGH macro can be used to annotate implicit fall-through
// between switch labels.
//
#if __cplusplus >= 201103L && defined(__has_warning)
#  if __has_feature(cxx_attributes) && __has_warning("-Wimplicit-fallthrough")
#    define BOOST_FALLTHROUGH [[clang::fallthrough]]
#  endif
#endif

#if !__has_feature(cxx_auto_type)
#  define BOOST_NO_CXX11_AUTO_DECLARATIONS
#  define BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#endif

//
// Currently clang on Windows using VC++ RTL does not support C++11's char16_t or char32_t
//
#if defined(_MSC_VER) || !(defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)
#  define BOOST_NO_CXX11_CHAR16_T
#  define BOOST_NO_CXX11_CHAR32_T
#endif

#if !__has_feature(cxx_constexpr)
#  define BOOST_NO_CXX11_CONSTEXPR
#endif

#if !__has_feature(cxx_decltype)
#  define BOOST_NO_CXX11_DECLTYPE
#endif

#if !__has_feature(cxx_decltype_incomplete_return_types)
#  define BOOST_NO_CXX11_DECLTYPE_N3276
#endif

#if !__has_feature(cxx_defaulted_functions)
#  define BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#endif

#if !__has_feature(cxx_deleted_functions)
#  define BOOST_NO_CXX11_DELETED_FUNCTIONS
#endif

#if !__has_feature(cxx_explicit_conversions)
#  define BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#endif

#if !__has_feature(cxx_default_function_template_args)
#  define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#endif

#if !__has_feature(cxx_generalized_initializers)
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#endif

#if !__has_feature(cxx_lambdas)
#  define BOOST_NO_CXX11_LAMBDAS
#endif

#if !__has_feature(cxx_local_type_template_args)
#  define BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#endif

#if !__has_feature(cxx_noexcept)
#  define BOOST_NO_CXX11_NOEXCEPT
#endif

#if !__has_feature(cxx_nullptr)
#  define BOOST_NO_CXX11_NULLPTR
#endif

#if !__has_feature(cxx_range_for)
#  define BOOST_NO_CXX11_RANGE_BASED_FOR
#endif

#if !__has_feature(cxx_raw_string_literals)
#  define BOOST_NO_CXX11_RAW_LITERALS
#endif

#if !__has_feature(cxx_reference_qualified_functions)
#  define BOOST_NO_CXX11_REF_QUALIFIERS
#endif

#if !__has_feature(cxx_generalized_initializers)
#  define BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#endif

#if !__has_feature(cxx_rvalue_references)
#  define BOOST_NO_CXX11_RVALUE_REFERENCES
#endif

#if !__has_feature(cxx_strong_enums)
#  define BOOST_NO_CXX11_SCOPED_ENUMS
#endif

#if !__has_feature(cxx_static_assert)
#  define BOOST_NO_CXX11_STATIC_ASSERT
#endif

#if !__has_feature(cxx_alias_templates)
#  define BOOST_NO_CXX11_TEMPLATE_ALIASES
#endif

#if !__has_feature(cxx_unicode_literals)
#  define BOOST_NO_CXX11_UNICODE_LITERALS
#endif

#if !__has_feature(cxx_variadic_templates)
#  define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#endif

#if !__has_feature(cxx_user_literals)
#  define BOOST_NO_CXX11_USER_DEFINED_LITERALS
#endif

#if !__has_feature(cxx_alignas)
#  define BOOST_NO_CXX11_ALIGNAS
#endif

#if !__has_feature(cxx_trailing_return)
#  define BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#endif

#if !__has_feature(cxx_inline_namespaces)
#  define BOOST_NO_CXX11_INLINE_NAMESPACES
#endif

#if !__has_feature(cxx_override_control)
#  define BOOST_NO_CXX11_FINAL
#endif

#if !__has_feature(cxx_unrestricted_unions)
#  define BOOST_NO_CXX11_UNRESTRICTED_UNION
#endif

#if !(__has_feature(__cxx_binary_literals__) || __has_extension(__cxx_binary_literals__))
#  define BOOST_NO_CXX14_BINARY_LITERALS
#endif

#if !__has_feature(__cxx_decltype_auto__)
#  define BOOST_NO_CXX14_DECLTYPE_AUTO
#endif

#if !__has_feature(__cxx_aggregate_nsdmi__)
#  define BOOST_NO_CXX14_AGGREGATE_NSDMI
#endif

#if !__has_feature(__cxx_init_captures__)
#  define BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#endif

#if !__has_feature(__cxx_generic_lambdas__)
#  define BOOST_NO_CXX14_GENERIC_LAMBDAS
#endif

// clang < 3.5 has a defect with dependent type, like following.
//
//  template <class T>
//  constexpr typename enable_if<pred<T> >::type foo(T &)
//  { } // error: no return statement in constexpr function
//
// This issue also affects C++11 mode, but C++11 constexpr requires return stmt.
// Therefore we don't care such case.
//
// Note that we can't check Clang version directly as the numbering system changes depending who's
// creating the Clang release (see https://github.com/boostorg/config/pull/39#issuecomment-59927873)
// so instead verify that we have a feature that was introduced at the same time as working C++14
// constexpr (generic lambda's in this case):
//
#if !__has_feature(__cxx_generic_lambdas__) || !__has_feature(__cxx_relaxed_constexpr__)
#  define BOOST_NO_CXX14_CONSTEXPR
#endif

#if !__has_feature(__cxx_return_type_deduction__)
#  define BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION
#endif

#if !__has_feature(__cxx_variable_templates__)
#  define BOOST_NO_CXX14_VARIABLE_TEMPLATES
#endif

#if !defined(__cpp_structured_bindings) || (__cpp_structured_bindings < 201606)
#  define BOOST_NO_CXX17_STRUCTURED_BINDINGS
#endif

#if !defined(__cpp_if_constexpr) || (__cpp_if_constexpr < 201606)
#  define BOOST_NO_CXX17_IF_CONSTEXPR
#endif

// Clang 3.9+ in c++1z
#if !__has_cpp_attribute(fallthrough) || __cplusplus < 201406L
#  define BOOST_NO_CXX17_INLINE_VARIABLES
#  define BOOST_NO_CXX17_FOLD_EXPRESSIONS
#endif

#if !__has_feature(cxx_thread_local)
#  define BOOST_NO_CXX11_THREAD_LOCAL
#endif

#if __cplusplus < 201400
// All versions with __cplusplus above this value seem to support this:
#  define BOOST_NO_CXX14_DIGIT_SEPARATORS
#endif


// Unused attribute:
#if defined(__GNUC__) && (__GNUC__ >= 4)
#  define BOOST_ATTRIBUTE_UNUSED __attribute__((unused))
#endif

// Type aliasing hint.
#if __has_attribute(__may_alias__)
#  define BOOST_MAY_ALIAS __attribute__((__may_alias__))
#endif

#ifndef BOOST_COMPILER
#  define BOOST_COMPILER "Clang version " __clang_version__
#endif

// Macro used to identify the Clang compiler.
#define BOOST_CLANG 1


/* xlcpp.hpp
UTNVuzLCxvMEr/bjdRLOtUwA8h2C9m3+pTd1foof2kEKDI+jD4I8wAzXYRc6FN7QmaRuAl9mD+35uQ1z5jY/ZpYyYNE/GBeZKee3CZs/JYeMSJCsxmx5tALACMvzVZwFeY5FT6bWEXS6PSeDxsY5V95M2oMZWuseBMF9T5u16w9pqRC3ekVqGR6XQVfV0l1NEOTd9AEDzFMI5fs0shMkxA7X9twXxIyTm9RMF6iajRR+DADhsG2PreALtE4YTkP2G+HsfDtEM5pZj9Ux/X5zi2viXdxFZaaRmAYUsFZ6F9n5pOykwSgdR+WbcHgPZmDmwDTqrWKPihuBfx7+bSJYRfbRAdNH78A5g4DwIBaFduhpeo6lhgXgToVpLhhTcLdpRi83scHOe7yA7V5Fm1TZNsNS2OzvkGNNIq/mNbBv7i3Deqyvbi/FjV9eWntuMNa2tFT1ytr2M26YbdG3dhyhXXfoeG7d0u+3UGVfu21w013FNDPdiCO8bnUGnNQ89sLUpHj1Zu7C6kv1XWTfhlAM7x78bRvK5bgxLXTbx9aXbd4iuIvy3KRA6H0dFf9GD7vJPKQE+UqOTWfdp/iaHLz/bZ/qVXJwjvQ65uAPH3eacUqs6joRIBqfCZR75F3S2RWV7xAOqXksyT0/RXT1WEinf6oAhRv9MGtfypZ7qnYiOGd/eV809LGvf/g8MU31WFmQc25q1D2z8vX8t0X/0pLYfeDiylmRBpw8PSY48bz52DnRw+u5GboJXPHcg8p162P4vo127epCjEUdEs859BdXY5D3cQ8vlGKIu/GaZOan83/UfCRUJ7dq8fdXOk1FhEQd9FCMvV0POmIjCQOPs7Cz+/JSf7LwuXIQbfTc5v4kz7QsGYu0S7LCJcqc54G4braNE/318eZMdi3eRJRwETv3toAlAaLhQEG9MSKKPpHsfQ+9+OT33mHdU5f4WJEHXWTpp7ri+I6v6q/foYRmDmGivpUSPqn7PRr6ue3hgMGSzTsgfaHCB/r5QVMCzf1Jr1BRq+uINgHE32Zsm/nEK/b4oyQ+BvmEBxRcVaoBgw4BJJCk5Bz4dGUB7JCBZBL4NBKBVOaBzGEB9G6BPJSBtBqB03uBTGWBgmmBwm2BomlB4quBUpRBk49BEtjBsrBBHKdBquZB6ubB/GXBumNB2qfB0hLBhrAh+hIhZm2ESmHBJmEhRmUhmuYhdq+EVmPBTq8BFhKhDmHoMLOhPAIAMzSK/Dwk8b7f3m5gvthhGr/DLP+G+YI0IMjsYaT8YJEUwlPcwtPSwjPawrPKwOXqyGWAEZKkEZYFZOrzZJGoEHKMEbJCETVjZEVj5HLAcKm+8Ba3yDa3cGkBCOM+gAix+mG+GfksbFVb2GA9p/Nv8mFYVYC/HIiRXBotYsTtB0R+VD5l2EtClJ9b9IKE/1Jb9Dys6tpr9GQb4/Zr1G5Y9GJYzBFHzOVY9H5bzDJ2zLEb141E7DVH7LlbzPtq9PNq7N1Y7Nlp7PpqzD1HHPhbLKxmLBRcLKJkDHJ6LAJVPDRVHGZ5HNZa3Kvbf3M9eBbxqOPxJHAJROHxPy0SfpXHf4Ql0JQnAM7iaTSxh0a1UPY8t8BpsUHHqMyciSwOFoelwAYzoOAakCQRKDwOFG8HSsIlNYoDpS2SZHE8FamA8uFAVXegOlWSMtxv7fRkqL1kubXkP2dAA6pkY84UkfAUifIUqfEUGfcU+/QUh/YUp7WU+PrEIkyy++REAv/UqVG02macl4bkl1SxzmAu3wKcCXHv4HCbDlGeuhAvjLHUaBw7EVPZTYcfcWh/ky3SwzV1ktbSX36QyaH+XlSJLdC0FVFz48tzb0nOSHlzK4bJBIl5mAhmQpplet+ltqXbdFikdJdnNLhnqkim9Zcb9mpmjUrajo8nT77ZTL9lTb25Jb9kzFP9eRDPHnLPPlKjD2HP3OTMjgH9gbjJA8/CyVkgNwCwyZ9S5RSReD4VmF2dZUKYQnAIQDv+zt1e9skvz/UpwflTl/N2ljuhJqWDkwvIyIFoQXrhzIN7z/3EcUGRMrzCgiesQ+LnzEdK8WUv9IetyDcM8f/1HIW0LtLxC5qojpEHiAgSMALdwq4CzSBIkFgD4ZsEEC6V0fjgCubQ8g3v6UzChYr8f/DkcUg9cEH2I5QRc0KAs3OPFOox6Zg55CNnCA2bxXDnQTI8cLU9o/jdFv+Og4Xo52sRRk5mZDXKMGKzLFTwwMTP8CcWFhR1N7aJg5SDZ4YT5J4lt4GK523ygx96Nqlc9rF5t2dnLngOzyUAWISBfnJbLyPMzaJ2D5pbSpVs7IIT7sL25ZlC3IEHV2BC/NXKzSeCTzKF6DeGuOPqApYT1kPS7ppfQ5qC6sozH8rtSIoxJIpfE4k8/paoMiL+Y0aUZy6M/4m00shaM4HqColYCW3VQo1lB1/kqMXHqcDZDTSq/cmrN2GF3MfnxQVMfK8qJymoTi5TreBZEaGghqxavkUxROcFgLM7j7CqiZUbr/M5O4GhKsBkNHJ6G/nsw2PnU1MWRTDRRlTkiAHrnYBeFdyHxKzs7yhjfuUqcHLg3DWhFvmXnIz5u+VB5EB6ZsTVWZZ6Zc5RKYR+cmvNn5BcP8BQblHSneqpncvsIwTMQUylB7+R6E2tQH2Isj+ZI59Lzd+BfT+BDdSNeGKN4YoFu0d2EpOyUIJ1HB9Nx8GVmfmVKtz6c7ilRMzNmpW6hx1NEe/Nl6x1bYp1xnh6apX1Jxkti83NbHiltp26htrRMtytzheFMn4tbty6VpHN3h8tLDTVunhtPpVNf7lbQjJ1TLkr9Drbjh5b8SL5I4+b4qxw7bmrQUbtqZ44LtIFERvtrUttnh9tBZEyCRstpR8y6dptlZmyuVY1tVZyRZOtjZEdOAhtrZMdgZPNFkYdnRdS9Z6t/Z4yzQhdw5lS5ZldY4sdvZNdvSxd+QjdTc5di5nSk57dbYdd7JXdjWTdFaCL7mzj7v0NqTXtnvKhbsfInjxAz2Vll4dV502k5Al3b1ZRz5hVb/Bhz/uk5OFGb7JKLxi+5Ct3X9JQLzS+JCizL4qsDzFKAuqzLzyoDy1KAkGn3/+wD3tTHLWr30+kn3BTHAt/wK2on0xGnMBrwAUwQJ3lfZfZS4cvRo4/aJE0wDIlRus1GPI2wIUvzrw5aGA8KEA7GIbQscc9pMMyILEpyt81pE42JBclyok/rDQ1qIIoJus1LAcY1rIumPRHT6KQvl8bllXB16cFJqmD9/weMc4SeRDEMuwasbkUMf30BcWNOPKMyjyOmONLu1eNSqiM2iNiWm5G+V2O6E/hOoCsx0K9RAI2R7EUxyD7R6Ivhb28Rn2mxpJpRWKjxuM/RzOtx8N5xrjBJ/KrhLOjRjO8Jricxy263JOmJpiTJoLwdetpJ+mCfthF/ajgGW/7FEr9y5UZGGWxPNn7KUQbaKrCORFHC5bgNUWPMWnKM5VzOZXp6jHrJdSxGUajHOY8B0uSB8BRAJcDs1jLmhyoMr02HM3qg7bMAwiDefZ4zZA6T+pHRVX3A3JQIVe9Jh8/BZ51RksL//X0/XOArwPxCBhZV4Tjw0dN/BeiCYQYhPPmHzQKg/I3HanH4ZKeFQH+8A6ZlorPx4ymG3f4AbyChJ7WIs3GuNaYb0ebIpP11wdtmh2Cz1kKANimzaRJFp5hF/Yd59/w55gUkhimZX9SYjAjLdrWLyLvLchdoZoiWnEg4e5ALFWTzEpNL/obVvDrohnWTxcJi524cRl+Acfrp99pHed1fHRsqPXxp5oU8ZW+lhwIVsy9RyAFZ/NQA+joVjS/lgsSlifqJ4N5J4JsViOyx/TplsbqV9Col5eTVsO8V5O811Kq8QN0HQM211yv/g+Pi+56Gd06CDiXuTdd/rVeSrBRh7RezbvBWo0/OGdmyFQGvb/u1TDddUUw9InfiLrZI7vZKZsxmG06vkUwOr0JMticRNqciF4d1t2y8N6a4d1a39rYBG1tbtts7dJt7hNsrX6tHnxtLnZvHdFtXXlvj9lsX2ZvnX1t3RNsP3rvHGbvXE/v3CJtfUVvv1dvb3XvQBDu3kXvgn3vXETvwMzsQsntPn1tP3ztYubsojFtCkIRTeTvwfTtne7t/bsiiIxe+5WzZiezn+y9j9oP0LAfvUZFZerZL+ziJCFUCb6apZQ7II9ZxZebIuJDCi47YGc+qBU9vKnnZO4h2sZHzWwk+tN3OMN7pEh41M17pK53pORzpKl3pFOzT1ZzpC+XAb1/ZCB3/MfnWMX22Hj7SK3m2LbnyDLn2Ibw2Drm6O/3scs2gSvfsUnNf/kav+sTZ8JTX/oTc9D2iVPNaTjfaeT1f6M9VshnifRnDtcnqcgn7rZnmTFn2TVnATNn+ddnhcjnoXLnpcjHZxjwJBIAY7SIGlsI7K+96u/zntdIItuwKkL4mhmAsR+4HGNkEPCSTACWjPhyVO9y3PZybPty4vpy6vtyeDtyReNqxfxi2Wc0RvEqkgkg1xe9THi9FHPVc3phvAsY5IvsEbic276e/L6e6bk+J7yUI74hq7s2no1k8ruIbrtYFyA3brhpkAN+E97W0V/gzUTBzF7Mhym3x3B0ztzKBtwSIas2I19joNxh7dzi2N112V5Iz9+hotwj597+jL1DublDI7qn8r3H37nH479jBIHuKO3umf7ds8k/MOQ+0OjfY97c//73QMZwz37zgFv7IAh6EJV/lIh9kNp5FKu9F+Z/4P33qCr/pMzwyAp6VK994v73pInyrO37qMvwrC//bBj7bMTwpB1b/nEOzkEMQdoH7swAwbELbhf74gL24ij/gm/w4nHz7En0gpsHwATC+BCDaeW9RvW+xuy8xoFeE4jeknpfofLANfrANexhIuxh8Hff8nrfcvnf8+Tfc2vBkfIAuIzvzvrvNXbvrn5QGrNvmfqvmHHgibkfyb0fHbUfmHngrvYwfjfgnrUvqMCXAtCLq/xngO+n0877oD4MqsHn2M3bRGz5fO7XTO7nHKi3dlv/y6X3c53ha9f3a+jm65ABYpPh+7T3a3nna13/+xb0dQ76viQCPRF9r+5836MAOXjcytDzDQTxSes29/oEgwQCoH+R66ze7vUFomP+doZl+jkQ/YNXCqBZ/1MsAZXSsQub6UAqnlI/hOdMqXA8hUh1fiodzVQ2m99zZogzgVK6kD1+QgV3wXS8WN71hwn8koVCjmQ1xFN68/limUa5FOb5nX6iL+iRgCOTzabMIl+oWXXyx5V2G+i4gLfumYiCLUjiFVZw1d5wKBSTwrRrlekPq8jmt5G2e4PelF1sEJfj1U6zggzH658/nNUmi0lURAY0IY6UpMZZiMiK2rIgo81YlxMxmYAxf4Wck4bszBa4i599WxO8jup2ZRP9C7bbiF/tZrvWIMXUSPaOv9fDRz65M+0fTvcb05GtOd1eLje1/bWxN3q8Xo/3O7lEtSA+0HPVR2z340ClvADkQyND//ePInlBAJE1o9AneVbtABgDoE4AjnkzVgCE/WjfB8kKmBNE5JRhGkJW3YwbxlT0UhxBp8qaG8GVpb0bJFjqvPy/PC5KY2o8ePPNrZtcu7CU6Z+h4dxexMLcSzFDDWN0sWT3YSfkAGXE3qApq98L3/H3LEvzn0ys7NnWTjPsJ1GJshz+U43SPFeLC/J84NP3DbygqcYZYThMEIYiP47stCIXpizGtOgvm8V5cabopHnJo8umfzKc3SqLCrwES4tKglsYS6qq3cqzAgjBj6qarEiL0jpOS5jq/zxYHWsPY4A/OafKVApZOFfI5tX1LzafxnZn8JvkGemc6JS1WqWlEX8hqVZr2a1BYM07sNKlqtgYZT/oqK2pLuny78nKbruU2qxsu95Fq++4v1Wr606eIq3u+IN/p+wGIv3A2gvGlGPfDB034fjjRPGDwzCMwZbDKBLV59koTvgvzbhOrpejBq0oAvharOT3qEm8Q3AlL6uVqZN25pHzszxVcnGTGYm20+SJcSgyl1nBGoBLIt/BFPesMPV47bS0uAa0YCla/51+Xp59zXVS2Y68cVHfP6N12Tgut3FZvWSbeVWwFYNnWzznw22x1JSDd1NyNrNx3V0I3WXbDhf7Zj8UbPxD/TpMNFJKMo3Sa+0f9Q2bA/MBxPTvpr6h/03WzEuzfzkvKqt7uyxru3656LJ/KD5/5EXFTCQbrni7bnu+fLn+L7Imkp3vuD2is6pt5C5Ax7E39n+RNd8el40rPp4LFqXev8/zdORMTtv/h6xR9/V+3nAlGjtkUvb5/cDlKccyT+7r6/v98QLyBYOe9VXYl7kawMJFPpTzQzA2gCR4FYAVY3Teqdxh5aHA+hREsUM7/N9kTcit21Sm3KsxDPl9uEIwjbEhgu6rUPy0PEO0sh40FZQw/rFCKPfhHsQJWrFhOy2LaoCevt+c8H/JGmnj/RtK2F+G7jMAEfsA6BD74knrunDt/5I1r8PEX4wRP2QQ0IXyAHQYfgCNDkzsrf+SNfHB8lVE8MKzYOAqfoARnCz8r1dxAegE3z+HUa8lzuLgZQ6/tTCMfxK8SUigMbhPc5MRPrkNSpgqJWYeGl/Awg63p6HGRixqUsi6S6mUOKo/Mcv/emgbVapQSmksOqLix/mlnnBv2nxowuD9Jq7mIZdUa73MEO0uY/z7LmVApIj+KVnGXEw5gwDRFAfVfVwDJKecuXF4DEqxmFYccEzdIjPjnB7vtuxAyzzgMePeepvZ9WZO3fci57lyl/dKoM8e1DHjfXiT94Nm+UsOMCM9WxPzJ1fJR1iS+YJflw/6rVKAHlzK83YGkFFSKcRzOeGrhZMWc1Qp+slbIlobPpchmlREY1JOzWspqXFfXMxcfEYrizvTrlNZwn1U/vNgReG6LBEw8aAjH+2xKIAc6fdwmSKnGqFSJuYSSp6o+1MiL4hDpQ+O03tVufhdta7CXmMwIxJuLA/6F2I+QGc4XX3wXa1NjDHizioIlnQwpcSSpsbzqBImnwNHbtcPjjwNOk5oXX2IPMU797MchoMkW/RcFVSfWFz1kYTLN+HWB/hdZW3G28k3IjdSvzx3ZibrqXWp+0OW0HwoBTlSa3Xk2SU/W/pnxy5gHF+mpfOI7kbl4sd9cUXr4C/bFx+uX53fJaaidLZO2QgdvUJMdTK74ClSHzqXpi+a+S6RRr8QGK5C1LvsImybWazYWmPUu4dthBRqWdcfa9R7pr3nleQPwEmBLaoPRzdOuYtSK6s/Wi8v7fxzESbOWEj9RVnsA+svOPeJV7CY+mL4CbwM//34zQwihkBmZIwY+6MxVNfMYIoMBEdXsR2iCbkyYfXan27QGCn1ToDy/BUC6ZaHVLREn2upEIjz0NJDxmxnVdtf9NqD2S8L4hKiXh2AI17dJ+pO+80MVh85PgaGaREvuJ+GZxyzvOpjgWpvC6ejmVEvigdiBAc6GwQ3CQRiOX7DMGySIrXOBuDnBk6+9FUpUqK6S8FF+SclbCrj/LHwSdaAiXtRMDM30IRJnXNKXdj3873cJSSNHGHMeDyJn6gJGcdMkeGNLFZU+YPFeirK4FaPoC1QOGMhCUjdajCDARNcQF4FLzH6e0Tr8GMRnu7whWsKAHxBrQmZeuSvYjKhXcjAUvoWT63+QnG8NPgHWn3kx/ezcMwbmB+8vlA6SD0YbTib1O/eNP6bB0ns6YHlJ4FAbK14IZ0oDP0Cxt5S323h55oOZesAALV/nP+hHHDzqa0+Y0HOQ5KTCcHJkZssKpa5anLmpttYdmvt7DKh/CxE0UkbyUCaUWfa4cCgpJfrLD5vF7TGGQOFNWUzfaPwTApA98ywAekLbbIn/aA2XkchIfqCD/Dz6wb43tRDL3EeqFtLDajlaB7XgwS9DCbbJp6LQYpwvhcb4O89MHQyQMdWlnwOb06nheIMx9aktTPQmD/yc9851waOugGMZ2P3l43xZyHyiOIDf0qPYesD66wCkTMsfPdCmww5DCt2CGuIQ5jH4LvmzjMrI+w9Cn3W8W0um8M+pq8OOdkKfcIvKisRpnTdU+95j3+YJRb1TsaL+cjiqbFlqaBW/IWH5tUJ7r8NT+pzWS7jJ7b5r8M2d5/jj1vSOrd9/BB5FSRUsWf9sRXtsjxaLtJNZUSr/fyWdTCmlxCT2CucM63ZZ/cXE3tDuLwv2ogTQY08QxCYCqlmhJ6kZ78dVxtfE/l+cvoNTFB+CNO1cTckRzJhTpbSr3X4GoQQx/+GwWb3s2ohOBWo6+z2zQvW1+zb9+hw7q8VfvjPVI1+4wxge4VRyevCXQ3Wy2vl6uSAf2QjPmPtWWj0xeZAcfPzFQhhE0BOVIy++im4GsD9u5OO2ar0JrytyZxVEx0N9bBPZpLV9oBNZuP3j1V/LJlIKEqhbsoqF+UBSG4IQeX0Ue5SkMJqFZtnI9VBMGcmi91kP1E4/+sDa7YwFIwGWL9TJLqQ8Pd992+l7hYOYaOMXFcnhPUPGMtOoZ9UvXof/QRgQ7CvMAZp0MU/E8jIRLZx+Vope76UBQc9hdk2/HHLIKgvgs13obiDRLT6GqXwEu4XOGadIn/iAk7AhqEfevbA+LfefzX5gf8o42kN480sZKNaYOb9CaPTFSXV1jIuEJkwSa5/yRDUSPClzKYZ0Chc1+cRONTUNuAwyGbDjEYJ22392QiNEQhj3a4/j/xY2efe2Ar8RNUbZOF97BgX6Gy0j3n/INa3GjX+3V8mLagwNEjHMqb3Z8A3jjs0ayxCSXjESBgUUijReioerfJLWKSmU2ooBiMhC09SC224iVjUjkUy5VFiB2HEGW8kJWtca33k8HTkoFAye7HINWq0yb49G3FCTmhsKoErn0dKJUAiXESq5LJoeOFHlLVU+WJRrEx33GVW+ZSUgJAkMjrtQSRhNeIkOcTIVMR4MKp00ydppkqbkox0q05BzqVYnpd0xyFJwRRTYZV0twxpsfNA9+ckmYcUBmlTFEBmMCmvQkSkikdmBIOkRmU8y1pmHIO4QaS12ah7fEoGRks6CyA9/Tn1FS4NmyU9Syv73S6NwSK7pJPXg1+35CVr1yBRRiazWjX9JTlVOSSzsTl96S5Tay0dAiEIInhk377sSaWdnFQRCUbjgsFu2/+kngnqG/sszTxoPgminksaTU4YuhChXpyavEb8d2YxTYEh/8BC2G/dxcYj/4w=
*/