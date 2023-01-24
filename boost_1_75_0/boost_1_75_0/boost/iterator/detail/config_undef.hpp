// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// no include guard multiple inclusion intended

//
// This is a temporary workaround until the bulk of this is
// available in boost config.
// 23/02/03 thw
//

#undef BOOST_NO_IS_CONVERTIBLE
#undef BOOST_NO_IS_CONVERTIBLE_TEMPLATE
#undef BOOST_NO_STRICT_ITERATOR_INTEROPERABILITY
#undef BOOST_NO_LVALUE_RETURN_DETECTION
#undef BOOST_NO_ONE_WAY_ITERATOR_INTEROP

#ifdef BOOST_ITERATOR_CONFIG_DEF
# undef BOOST_ITERATOR_CONFIG_DEF
#else
# error missing or nested #include config_def
#endif 

/* config_undef.hpp
yzsGorlxQItwf5G2+ju2+Q7gCN6d5+FqIQ8oR3OvKffAOmB0IvvDk+nSUKxSomyiJZbkv4NkW0l+q6PT12+/1GPxswBcxLjb95wz+q7afQ4pUGsAKA+BL+Vq1y3FpzGw2oqN3z6jjd77YCH0FXMMMEsSNx6XjekR3RUPRtmJNpKKoBjB1ZdRMy0c8NN6mrwHd0KD8pgO9iATaREK4pOaKiDHeAHNsaSK3pBjYLcovsgb8WJeyTdA5B1IBPn16VMYjp5yoMqLwZoD88hfYtpkSzHmGFal1547LffuzzW//S03bBk/ijlmRdPGX5xi5CfmicXW2Y3h8kS7sLs7RLOsTkRR4hm5GWzTOyAJyHsXh9zN/YxSSW+hl5syejr5A9tL0Uk4tjBmH4VgGfnDI7NpUN2VvxvVeXEq6rXYOoa92WHO5NtgO2F1QvLBE683oTUnZsWhK+Ps0RSfnAPG/Y0JkRcra38P4L9FCU+63S6zPBJQ+WgAceaiNSM0Nw5bJK72KJDzyo1F+4Eezue16XmDyEUdB0sYOn1eGAMqJx1jgxgBQ7ogMbYtrHCP9mAn8a4bvHa2v+Kc78AVwr1OOo22wel+AgQypJ5hRivnrc4tm2ss2tRpGDCXhvVfsU/+nk/wkxdaOEv4zjjZVi6AC7R9VsxWfQUEtFEmi0Tj3swNzUXke/WKzf0PoM2fXTDJd3bbKmzRZ3Xg1gLBSCv4
*/