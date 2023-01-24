#ifndef BOOST_BIND_APPLY_HPP_INCLUDED
#define BOOST_BIND_APPLY_HPP_INCLUDED

//
//  apply.hpp
//
//  Copyright (c) 2002, 2003 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

namespace boost
{

template<class R> struct apply
{
    typedef R result_type;

    template<class F> result_type operator()(F & f) const
    {
        return f();
    }

    template<class F, class A1> result_type operator()(F & f, A1 & a1) const
    {
        return f(a1);
    }

    template<class F, class A1, class A2> result_type operator()(F & f, A1 & a1, A2 & a2) const
    {
        return f(a1, a2);
    }

    template<class F, class A1, class A2, class A3> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3) const
    {
        return f(a1, a2, a3);
    }

    template<class F, class A1, class A2, class A3, class A4> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4) const
    {
        return f(a1, a2, a3, a4);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5) const
    {
        return f(a1, a2, a3, a4, a5);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6) const
    {
        return f(a1, a2, a3, a4, a5, a6);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7) const
    {
        return f(a1, a2, a3, a4, a5, a6, a7);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8) const
    {
        return f(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8, A9 & a9) const
    {
        return f(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
};

} // namespace boost

#endif // #ifndef BOOST_BIND_APPLY_HPP_INCLUDED

/* apply.hpp
JKtabSsakpmt/ywz1XU7cO5j4wqez3smWXnj0EpD/MtJsKMPwLXvwjwIfOS3vFX4r+QYKaAM/ZkQTAQhmNLGCKb4ErYt6kvPPH7P4edOSFe2HT4VEPDvE8A9OsrpzYp2enNiMjQ8MPElgQbIdszy7gmJBnq7fLUu/0vAlgus6h50RaytIDEMRY0ToPMFmZjuOJ5QJipknPc3hrryCPKTe4KOgm0U4QqmfwmaP3sgFQJDKe1XnQrQ2QAkVaDrgHSWQyZEoC9r3Pd1LU6jTniPywe7O1w0vEfskIo0jGFKm8S7ENkDIQ5jZVVYWRFX9gpIHf4MIbK4BVgVPwrrQrWIRKglPV4QimG65VzwIJ5fVVA+2Px7sLXVvCVHhNNRt4+7PZpbQtfZohWp/6RqFqXJW2ti8ICOPscdfX28M6k++3oQmQciPuiJybucfbfZ1rWdkNTB7GkjtnbIhMLdnj9SfNvqLF3L8ytRR3FS1PaU2MZjomDDvI+V0hXhMXjk01U1Gm70Q2yAsXCadoBm6gD2P4f7v5UNgn2QLs2IV1kBkzoIKXweSI9Dcx80k6aFHP7KKbKeFcMDfmSHBrtjgsoiHF6DiWddSHBhyUIBDQlU16+bGvwc1CY95FT2RD0Ii5gCaMZE1IYhXyXYSoHE8KsD1Cf70FgG1iyAl4nE0sY56MyvjD6JTZVS1q8hEPBlBPB7InycTybMxRZpSwmo
*/