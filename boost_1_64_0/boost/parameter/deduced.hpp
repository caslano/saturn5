// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_DEDUCED_HPP
#define BOOST_PARAMETER_DEDUCED_HPP

#include <boost/parameter/aux_/use_default.hpp>

namespace boost { namespace parameter {

    // This metafunction can be used to describe the treatment of particular
    // named parameters for the purposes of overload elimination with SFINAE,
    // by placing specializations in the parameters<...> list.
    //
    // If a keyword k is specified with deduced<...>, that keyword
    // will be automatically deduced from the argument list.
    template <typename Tag>
    struct deduced
    {
        typedef Tag key_type;
    };
}}

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#else
#include <boost/mpl/bool.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_deduced_aux
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };

    template <typename Tag>
    struct is_deduced_aux< ::boost::parameter::deduced<Tag> >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };

    template <typename T>
    struct is_deduced0
      : ::boost::parameter::aux::is_deduced_aux<typename T::key_type>::type
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/required.hpp>
#include <boost/parameter/optional.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/if.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    //
    // tag_type, has_default, and predicate --
    //
    // These metafunctions accept a ParameterSpec and extract the
    // keyword tag, whether or not a default is supplied for the
    // parameter, and the predicate that the corresponding actual
    // argument type is required match.
    //
    // a ParameterSpec is a specialization of either keyword<...>,
    // required<...>, optional<...>
    //

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using has_default = ::boost::mp11::mp_if<
        ::boost::parameter::aux::is_required<T>
      , ::boost::mp11::mp_false
      , ::boost::mp11::mp_true
    >;
#else
    struct has_default
      : ::boost::mpl::if_<
            ::boost::parameter::aux::is_required<T>
          , ::boost::mpl::false_
          , ::boost::mpl::true_
        >::type
    {
    };
#endif

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using is_deduced = ::boost::mp11::mp_if<
        ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_optional<T>
          , ::boost::mp11::mp_true
          , ::boost::parameter::aux::is_required<T>
        >
      , ::boost::parameter::aux::is_deduced0<T>
      , ::boost::mp11::mp_false
    >;
#else
    struct is_deduced
      : ::boost::mpl::if_<
            typename ::boost::mpl::if_<
                ::boost::parameter::aux::is_optional<T>
              , ::boost::mpl::true_
              , ::boost::parameter::aux::is_required<T>
            >::type
          , ::boost::parameter::aux::is_deduced0<T>
          , ::boost::mpl::false_
        >::type
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#endif  // include guard


/* deduced.hpp
pmiy+TdXxT/JOS8Ad7K6a7n58jthsL2e9Q3W03+/q/dRz6T10fWccpDreWCwZw251HPM+obq6egrfzYZ0orSL6c0Q7+47wm5Q2O/zf3S+f4dW27z2xxljfttjrj+v80Vrvc/fhZ66v9GI77jUV77dzzb3M/Ttv1EeAfggrhjcb+CR5WxPFpcsrykinUMrrGNXUb2OWAnsFbF72vf02Hw5ZvE71rQRs8rtsOXFzKb9w5BnlE6+gSXF8Njv++/4NiYY3mxrHqxnqX5ku+tRp2/aKDOQqvOt8qjffbgpnaAtn0aRZJ1Uk3oG279v3Dr75GF0hGx9oiXnPlqbP2Xl6yoCduBDKtEXJvE+gQ2CYMvTzdkk2hEf9qxvuljm8unp328Q7nj+/0jY3n3G8cmkYh31ZxXi6asKasukTlNXB7uS8DDeoMvjzfAw/pG8LD+IPDwcR88PN39/jgqdu3cK/AwtCGWhxU1BVUl1bXLWMIqCinhe5MeK7NUWvbvPeSjeZPXAB+FVr1rbqXt60aF+2hax+b3zzzhmbsXL3eDsRfPGN+ePM5rj5e1zrH8knUZ/uYc4fj+9q7lbWi+jOi9a971a8fH6uNXqV9+bP0qq9nGWV5WsrxGC4G/uuYbdW3dQJvnH4S6kodV9944Orauv3PGYWtdwSoURyPrWmnUNbWBulYehLqmmnU192+c4HlPl/Xpay11ra2qrKguaXhettbtj3peJlHt9YM+er51qo/5pne+lW3Ot9z8PDaJ0hNj23WnM6fw1DVmbZLP9yDS8cxH1RoH+7ziILSpqqvkYcrvzDGxuugNZ+7gqadtbZPfd/kdRl3LQw3MFQ5CXcvdeZKnTY8f66mrtGl93LrK2iif9ayPaVMV2z6eH4R6qjaVPMw23TounMCpktBU+S4Y+rGlnvJKoM5urWGGk2AMPkHFD9nqTtreb4PVpEl8eztD7/02KPTywc3d75ql6MYEcknFNteRdEQfNN0mHP1NUMri/SZoltHzDtJZLnE9WzI6C7fLGQcsPGc9G4OAw/f488YaFe9w+3ggdfaul0mXPdUrVHhXG9+Jm9g2fwPhpm3+AUnLmS89jFw9Od61zR/9ndrmzXUmZh8eMTF2rvmm04dj+VyzrLKguDT+WKvrvE/FTbP3aYNf8xWvi0vtuktoZW7ZTZ3VdvDmluSNH3nL3DKw0T637DbJPkaHNsbyp6rW+RrU8BhNXI9eU1Ht/Rpasz9Oa8L4HKXfJC+zjlNPin1n2+3Mn2PqKPasBO9nQzbGfT8jPf9jtEmbZMzRLDoL2oOl+ymPca4K+VrtI8dP9siEjHv5Vn7p9aG+xrz8GB6puPZ5uEc2pvuQjYZ5oPKLWnvW52SxjUlCx4rdszK6vrWVvIouSjDe1Sj6drKPz42fY9Yfv/j7/q4S2XLr+5QP26ClvrZ9a3qsz58SjvwILoh7WL6dbfXUtbpEvX+UFfOq5cxrSsuW1/idv5GWjNXu97OoZOTMfsqg6LYERvP/zTiLDEha0efCLMFVNHEtT475nc1TLnPcuPuUcEIDJcE83Nv0gdtu03yaMXHGjJOnT1PrjpcVVdfwniZnGVHv33Vy6i3TJUN/bFLxu9r4JmnLfmw8eB+vrbGPHZo2U8+HoHWmGYZt9iFFc5hVp0j8Bu2r2cJD6gO/pD5Gn6Kc+JO30Oq5j5THu773zKmxayk/oQR7InwtWriQLhqIuvdG1+m92+KuOSCNaBtyPvriNB/rULz3mZi6YcypnvmD3A8Vuj1S3uLigQWlFc7Y2PAdUcTzrMl2Yia4cwt6Uwee7kMHeurjWY+t84saI9dOCydwtCTUF/cAeeXpesaeo2XWVZ+hpeg=
*/