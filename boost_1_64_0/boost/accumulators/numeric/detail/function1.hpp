// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_DETAIL_FUNCTION1_DWA200655_HPP
# define BOOST_DETAIL_FUNCTION1_DWA200655_HPP

# include <boost/concept_check.hpp>
# include <boost/type_traits/remove_reference.hpp>
# include <boost/type_traits/add_const.hpp>
# include <boost/mpl/apply.hpp>

namespace boost { namespace detail {

// A utility for creating unary function objects that play nicely with
// boost::result_of and that handle the forwarding problem.
//
// mpl::apply<F, A0>::type is expected to be a stateless function
// object that accepts an argument of type A0&.  It is also expected
// to have a nested ::result_type identical to its return type.
template<typename F>
struct function1
{
    template<typename Signature>
    struct result
    {};

    template<typename This, typename A0>
    struct result<This(A0)>
    {
        // How adding const to arguments handles rvalues.
        //
        // if A0 is     arg0 is       represents actual argument
        // --------     -------       --------------------------
        // T const &    T const       const T lvalue
        // T &          T             non-const T lvalue
        // T const      T const       const T rvalue
        // T            T const       non-const T rvalue
        typedef typename remove_reference<
            typename add_const< A0 >::type
        >::type arg0;

        typedef typename mpl::apply1<F, arg0>::type impl;
        typedef typename impl::result_type type;
    };

    // Handles mutable lvalues
    template<typename A0>
    typename result<function1(A0 &)>::type
    operator ()(A0 &a0) const
    {
        typedef typename result<function1(A0 &)>::impl impl;
        typedef typename result<function1(A0 &)>::type type;
        typedef A0 &arg0;
        BOOST_CONCEPT_ASSERT((UnaryFunction<impl, type, arg0>));
        //boost::function_requires<UnaryFunctionConcept<impl, type, arg0> >();
        return impl()(a0);
    }

    // Handles const lvalues and all rvalues
    template<typename A0>
    typename result<function1(A0 const &)>::type
    operator ()(A0 const &a0) const
    {
        typedef typename result<function1(A0 const &)>::impl impl;
        typedef typename result<function1(A0 const &)>::type type;
        typedef A0 const &arg0;
        BOOST_CONCEPT_ASSERT((UnaryFunction<impl, type, arg0>));
        //boost::function_requires<UnaryFunctionConcept<impl, type, arg0> >();
        return impl()(a0);
    }
};

}} // namespace boost::detail

#endif // BOOST_DETAIL_FUNCTION1_DWA200655_HPP

/* function1.hpp
g7tEBg3AfXvn4HTYnDIHe52De0YGeXHz3jk4IwKzioMDzsG9IoMCKkmhpOH5XvOqVNPpNccXO2u85rQ0rznjcPOqCea0Eq95SToKN2d0IWJtDiqMEClyrqWyBxHJziGphjl0FD59nEOhol8XGdqHdw2oFWjRSahTNOV0VMiIpri9Zl5PqtIlk4iOZyOoG21EMrALwiKT9ZnXHIFj4i+9phGCHA9vwORC0IATX1p48nrB4/ASzfQFaF9qZPmS4M6Huw/cKXCP8kUmFhuRyROMSLjEiIyd5IsUlPoivpCJameBkiJNIckPcRYNZxGcnixahWhZoBUHCwPcKXD74abkqXAH4O4L9+G0cYQ7B+40uEfBTXm7kLwSbg/c6XAXwe2Fuyede8HthzsD7glwB+DuZWAxMnr7yvAdhe9MfAuN3hVEmeAsgnOeOIvhrBTnBDjni7MEzkXinATnEnGWwrlMnCE477RO0eky0TY2OiQ6jpjdpf9FNG2f90nwy8QvG78c/Dz4+euMTHk93MjHrxC/YvxK8CutM/J1FJ4Zm0vDgE+lfBbJh3r2oLoK9ICo5ONs/2SzRQUWnGSbeBDLPLsMvpjBt8WgqBzrmtK9B3wjM+Phftht6MaB+fHA0ljXtzmQzzteVbP2xOiVKYGKkW56n0ea9/HYcVM1ftjV2MT3NN7fxPXHDdBUMccd6zq2W/NqDs+Mdc1rXksQtPg7GLhqcgqif+D4yX2gHziK+72PmLh0FFh02h99uNcOmH2vSkum+/8brZH6qJceqYokFMTPdl/gCEQragi1VqbRf9fTI2LBqCcFjvbBaF4y7VI+TunlMirzvzUqPXuwp+vlqm5Igfs7o9K/Nw82bcMvnlntbjK3LEqa17War23INyW1emcK7ttVb0/JnM8h/thqf/nu82duSaqIsWryIzX8RMkL0m4nmSjELw2/dPwy+OkUEGT8cvDz4AdDchSUj18hfsX4leBXGplBQZjj5TLHyyvls0g+NMcX4fKfD2MY9JhvbvpYbXCyzrsHQlmequrUL2MxBCzjhwJGIWDmaxSAYw14SYMLLwtfgSBOg5BShOSrMTqRn/MgqEx5EVRelxyMTk4uj3lmVlqTJ0jGbmNdvz6qRxIH8WxDsIp13Z4Ylo+wtFjXVxCGbUe11O7qnfGSMwiW+uPmZtUDHPUSguzqERRVhZA4kFNaAVnWGkhFKyDTmgH50zctgYxsDcTTCshpzYCs+KZFZ7s2t+rsbze17OyPN7Xq7DcRBOkoTS8vDA7x8G7B8H7maDG8wz5vUeLyTa1KvLlViWWtS5yIoPJ1ybBrlFy+1zMz4jejSQ4hUSPfaYqRwn1aMivc50Dh3gOFez+U7a116Ue/Kv39f66njWQQGAdoi9zHWi0fy7AJ4hBvOHXkgZJK+udr5KJma/sCY4zRsk59s96ifn8+rtk65a42XM/vIAIdPXXaJBeR3VScSP/DpLrm0+NIuNS01Ti+Ornaewo0mFaDmm71Yp9cvsNhxOqhzlQN2mOg7nnRLllqYm0shljgRhlSJOc5X0MiXOGgBMpvRS4l81mIdzaPz7TjSxwcn9I8PtWO3ybxbZrHq9VWfGEyx7dtHl9vx2+U+HaIpBgkQxp1P+LLv0xFvB9tkkCYWYpxZhORCcwA7Vpgn+kIIXUS6M8jQxofIIxkKIxk32z1ogPpLgVgkTzlm63whEiewq4ykqWwaybJUeASrVESo7BnnnhK2FMpnknsmS+eUvYsEk+IPcRpqndqmnMc894UdH5c7s9AO+WqbELln477D5bKtbL/U99k2+/pgID9ye+Eb8iOgW/Y6EC+P9RbmPNwT4tvIJ1gsm8QCVb6o9E=
*/