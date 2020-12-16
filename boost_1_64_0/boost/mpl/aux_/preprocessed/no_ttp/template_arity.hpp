
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

}}}


/* template_arity.hpp
BizDW7ASb5P6uh2340Z8EX+Fh/Euqa9NUl93499wM/4Dt2BXyrYV9XgP9sRtGIbbcQjei9F4n9TfDjThTlyGu/AOvB834QP4CO7GfbgHD+KDeBL34t+xFoOpo99iCD6G4bgPR+LjmIW/w4X4BBbgU1iDv8fb8QD+Gv+A27EO9+Kz+Bw+h8/jQfmcUnVyDgPz5fvmCkwiKuEh+b5/GL3xEQzEWhyIv8Uh+Bjm4uO272k5L4FDXXxP75fvyScxGJ/CQfh7HIwHUMrHuYaWy/e9XPP2TxyI/8KxqOP9E6A9GrCDlM/N9vtDzg2gv4vv/yukfB2xF3ZSva9B1quPi/e9Iu/7I/rjYXmfUSd97Fgo7/sF5sr7PpZ6/kTq9zMMxb9hHDbiKPw7TsbPcTp+iXPxK8zGU7gQT6NcAyr95ub+dPJ1vAb0Lqm/e1CP29EP78PhuAMTcRfOwgcwA3djFv4Gq3APrsS9eAM+hDX4MG7CR/BxrMWncB+exMdRJ/ektscn0QufQj0ewMH4BxyOdZiIBzEdn8dcfAGN+CKW4kso6y992hz7XKz/H2X9D6Me/yTr/yoG4es4EN/ECDyKyfgWTsFjWIR/RhO+i+vxON6G7+FmbMBH8UPcjx/hETyBb+Bf8WP8FL/Ez/A0NuLAdnzeGI5NGI1f4yRsxpl4CrPwG8zBb1G2V/q9W95e35bt9R30x2O2/U76ojHZxX73jLyvDn3wWfTD53AkHsQx+DxOwBds26P0NeNSF5/HEPk8YlGPcfJ5DMfhOAITcSTOwlGYgaNxCV6JFTgWq3AcrsEk3IATcA9OxGcwGQ/hZPwAU7AZp+A3OE2eYzgdB+EMHIyzcDjOxumYjnNwLuZhBi7BeViGBvk8+PykX5g8ZP2V9Tsh658t65+HesyX9V+EwVikejZ/FBbjRCzBFFyC+ViKRiyT9TfhzVgh22Ul7sJl+CAux4ewCutwBR7Gatk+V+JneD024hrsQ/lvwP54M47EdTgRN+AkvEW1HXqcYzs8ItvT6+iPb6DlfdJHi3oX71sg71uIXpgv72N50teq9MFa3hcnv+2U4C7H2y6ox67oh54YiF4YjnqMRm8cjj6YhD1xMvpjEfbGMuyDlRiIKzAIb8B+uAGD8U4Mwa0Yho/iADyOA7EBB+GnOBg7UuYh2AWHYjhGYCRG4QyMxnSMweUYi9fhMNyDcfgIxuO7OBw/wBHYiAnYTrmsGb1wNEbjlTgWx2AZjsVKHI9P4wR8Difii5iM7+Mk/Bgnowf1n4JeOAX9cCpGYCqm4DScimk4E2djCabjEpxj+10hfcIY7eJ3RZC0//thNwzGQOyPkRiC8n0sfbrk6eL7eKlsH8uwOy7HILwGw7AKw/FaHIIrMBavw3FYjZNxJabi9artubZXy9vzACn/QPTCQVLeYzrpi8UUOW748vqwvG+NlHetlPcGjMIbMQVvwhl4My7GdWjC9bgCN+AmvAW34a34JNZgHd6Gf8bb8SO8A/+OG/Eb/BX6U647sT/ehQNwE8bi3RiHm3EcbsFk3Kqul3Ps5xmyn89DL5yPVZdZ7iXIva8TD4HtdN4xLAJWco05DbL1ROs9BIdWqu4jmMp148o0UbmnIGmq/Z4CUxPvJW010Xp/QfzXbrrd19vvM1jvMF4w8fqz7zcIx0RiM3/zWMUyiM2kZ5KWz+tKYhWv16OrexJqV9nvSzihzIuNTOtTmX8160hMJOYSdxLriOmpLJeYT3m3M/963MJ002rKemsH3UvEWtL3knYUfWl0HWAe9T0O25vID6v5Wwxpu/Ew0Y37GdKU+fAE07q19vsgUkhbj3rSdmIMOt8TkUbaXtW9EYfJx4PXq0k=
*/